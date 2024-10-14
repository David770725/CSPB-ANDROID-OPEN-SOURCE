
#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "weapons.h"
#include "game.h"
#include "pm_shared.h"
#include "observer.h"


int GetForceCamera(CBasePlayer *pObserver)
{
	int retVal;

	if (!fadetoblack.value)
	{
		retVal = (int)CVAR_GET_FLOAT("mp_forcechasecam");

		if (retVal == CAMERA_MODE_SPEC_ANYONE)
			retVal = (int)CVAR_GET_FLOAT("mp_forcecamera");
	}
	else
		retVal = CAMERA_MODE_SPEC_ONLY_FRIST_PERSON;

	return retVal;
}

CBaseEntity *CBasePlayer::Observer_IsValidTarget (int iPlayerIndex, bool bSameTeam)
{
   if (iPlayerIndex > gpGlobals->maxClients || iPlayerIndex < 1)
      return NULL;

   CBasePlayer *pEntity = static_cast<CBasePlayer *>(UTIL_PlayerByIndex (iPlayerIndex));

   // Don't spec observers or players who haven't picked a class yet
   if (!pEntity || pEntity == this || pEntity->has_disconnected || pEntity->IsObserver () || (pEntity->pev->effects & EF_NODRAW) || pEntity->m_iTeam == UNASSIGNED || (bSameTeam && pEntity->m_iTeam != this->m_iTeam))
      return NULL;

   return pEntity;
}


void UpdateClientEffects(CBasePlayer *pObserver, int oldMode)
{
	bool clearProgress = false;
	bool clearBlindness = false;
	bool blindnessOk = (fadetoblack.value == 0);
	bool clearNightvision = false;

	if (pObserver->IsObserver() == OBS_IN_EYE)
	{
		clearProgress = true;
		clearBlindness = true;
		clearNightvision = true;

		if (pObserver->m_hObserverTarget->IsPlayer())
		{
			CBasePlayer *pPlayer = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(pObserver->m_hObserverTarget->entindex()));

			if (pPlayer)
			{
				if (pPlayer->m_progressStart && pPlayer->m_progressEnd > pPlayer->m_progressStart)
				{
					if (pPlayer->m_progressEnd > gpGlobals->time)
					{
						float percentRemaining = gpGlobals->time - pPlayer->m_progressStart;
						pObserver->SetProgressBarTime2((int)(pPlayer->m_progressEnd - pPlayer->m_progressStart), percentRemaining);
						clearProgress = false;
					}
				}

				if (blindnessOk && pPlayer->m_blindStartTime && pPlayer->m_blindFadeTime)
				{
					float fadeTime, holdTime, alpha, ratio;
					float endTime = pPlayer->m_blindFadeTime + pPlayer->m_blindHoldTime + pPlayer->m_blindStartTime;

					if (endTime > gpGlobals->time)
					{
						clearBlindness = false;

						fadeTime = pPlayer->m_blindFadeTime;
						alpha = (float)pPlayer->m_blindAlpha;
						holdTime = pPlayer->m_blindHoldTime + pPlayer->m_blindStartTime - gpGlobals->time;

						if (holdTime <= 0)
						{
							holdTime = 0;
							ratio = (endTime - gpGlobals->time) / fadeTime;
							alpha = pPlayer->m_blindAlpha * ratio;
							fadeTime = ratio * fadeTime;
						}

						UTIL_ScreenFade(pObserver, Vector(255, 255, 255), fadeTime, holdTime, alpha);
					}
				}

				clearNightvision = false;

				if (pPlayer->m_bNightVisionOn != pObserver->m_bNightVisionOn)
				{
					MESSAGE_BEGIN(MSG_ONE, gmsgNVGToggle, NULL, pObserver->pev);
						WRITE_BYTE(pPlayer->m_bNightVisionOn ? STATUS_NIGHTVISION_ON : STATUS_NIGHTVISION_OFF);
					MESSAGE_END();

					pObserver->m_bNightVisionOn = pPlayer->m_bNightVisionOn;
				}
			}
		}
	}
	else if (oldMode == OBS_IN_EYE)
	{
		clearProgress = true;
		clearBlindness = true;
		clearNightvision = true;
	}

	if (clearProgress)
		pObserver->SetProgressBarTime(0);

	if (blindnessOk && clearBlindness)
		UTIL_ScreenFade(pObserver, Vector(0, 0, 0), 0.001);

	if (clearNightvision)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgNVGToggle, NULL, pObserver->pev);
			WRITE_BYTE(STATUS_NIGHTVISION_OFF);
		MESSAGE_END();

		pObserver->m_bNightVisionOn = false;
	}
}

// Find the next client in the game for this player to spectate

void CBasePlayer::Observer_FindNextPlayer(bool bReverse, const char *name)
{
	int iStart;
	int iCurrent;
	int iDir;
	bool bForceSameTeam;
	CBasePlayer *pPlayer;

	if (m_flNextFollowTime && m_flNextFollowTime > gpGlobals->time)
		return;

	m_flNextFollowTime = gpGlobals->time + 0.25f;

	iStart = m_hObserverTarget ? ENTINDEX(m_hObserverTarget->edict()) : ENTINDEX(edict());
	iCurrent = iStart;

	m_hObserverTarget = NULL;

	iDir = bReverse ? -1 : 1;

	bForceSameTeam = (GetForceCamera (this) != CAMERA_MODE_SPEC_ANYONE && m_iTeam != SPECTATOR);

	do
	{
		iCurrent += iDir;

		// Loop through the clients
		if (iCurrent > gpGlobals->maxClients)
			iCurrent = 1;

		else if (iCurrent < 1)
			iCurrent = gpGlobals->maxClients;

		m_hObserverTarget = Observer_IsValidTarget(iCurrent, bForceSameTeam);

		if (m_hObserverTarget)
		{
			if (!name)
				break;

			pPlayer = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(m_hObserverTarget->entindex()));

			if (!Q_strcmp(name, STRING(pPlayer->pev->netname)))
				break;
		}
	}
	while (iCurrent != iStart);

	// Did we find a target?
	if (m_hObserverTarget)
	{
		// Move to the target
		UTIL_SetOrigin(pev, m_hObserverTarget->pev->origin);

		if (m_hObserverTarget->pev->health < 0.0f)
			m_hObserverTarget->pev->health = 0.0f;

		MESSAGE_BEGIN(MSG_ONE, gmsgSpecHealth2, NULL, pev);
			WRITE_BYTE((int)m_hObserverTarget->pev->health);
			WRITE_BYTE(ENTINDEX(m_hObserverTarget->edict()));
		MESSAGE_END();

		// Store the target in pev so the physics DLL can get to it
		if (pev->iuser1 != OBS_ROAMING)
			pev->iuser2 = ENTINDEX(m_hObserverTarget->edict());

		UpdateClientEffects(this, pev->iuser1);
	}
}

// Handle buttons in observer mode

void CBasePlayer::Observer_HandleButtons()
{
	// Slow down mouse clicks
	if (m_flNextObserverInput > gpGlobals->time)
		return;

	// Jump changes from modes: Chase to Roaming
	if (m_afButtonPressed & IN_JUMP)
	{
		switch (pev->iuser1)
		{
		case OBS_CHASE_LOCKED:
			Observer_SetMode(OBS_IN_EYE);
			break;
		case OBS_CHASE_FREE:
			Observer_SetMode(OBS_IN_EYE);
			break;
		case OBS_IN_EYE:
			Observer_SetMode(OBS_ROAMING);
			break;
		case OBS_ROAMING:
			Observer_SetMode(OBS_MAP_FREE);
			break;
		case OBS_MAP_FREE:
			Observer_SetMode(OBS_MAP_CHASE);
			break;
		default:
			Observer_SetMode(m_bObserverAutoDirector ? OBS_CHASE_LOCKED : OBS_CHASE_FREE);
			break;
		}

		m_flNextObserverInput = gpGlobals->time + 0.2f;
	}

	// Attack moves to the next player
	if (m_afButtonPressed & IN_ATTACK)
	{
		Observer_FindNextPlayer(false);
		m_flNextObserverInput = gpGlobals->time + 0.2f;
	}

	// Attack2 moves to the prev player
	if (m_afButtonPressed & IN_ATTACK2)
	{
		Observer_FindNextPlayer(true);
		m_flNextObserverInput = gpGlobals->time + 0.2f;
	}
}

void CBasePlayer::Observer_CheckTarget()
{
	if (pev->iuser1 == OBS_ROAMING && !m_bWasFollowing)
		return;

	if (m_bWasFollowing)
	{
		Observer_FindNextPlayer(false);

		if (m_hObserverTarget)
			Observer_SetMode(m_iObserverLastMode);
	}
	else
	{
		int lastMode;

		// try to find a traget if we have no current one
		if (!m_hObserverTarget)
			Observer_FindNextPlayer(false);

		if (m_hObserverTarget)
		{
			int iPlayerIndex = ENTINDEX(m_hObserverTarget->edict());
			CBasePlayer *target = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(iPlayerIndex));


			// check taget
			if (!target || target->pev->deadflag == DEAD_RESPAWNABLE || (target->pev->effects & EF_NODRAW))
				Observer_FindNextPlayer(false);

			else if (target->pev->deadflag == DEAD_DEAD && gpGlobals->time > target->m_fDeadTime + 2.0f)
			{
				// 3 secs after death change target
				Observer_FindNextPlayer(false);

				if (!m_hObserverTarget)
				{
					lastMode = pev->iuser1;
					Observer_SetMode(OBS_ROAMING);
					m_iObserverLastMode = lastMode;

					m_bWasFollowing = true;
				}
			}
		}
		// no target found at all
		else
		{
			lastMode = pev->iuser1;
			Observer_SetMode(OBS_ROAMING);	// don't overwrite users lastmode
			m_iObserverLastMode = lastMode;
		}
	}
}

void CBasePlayer::Observer_CheckProperties()
{
	// try to find a traget if we have no current one
	if (pev->iuser1 == OBS_IN_EYE && m_hObserverTarget != NULL)
	{
		CBasePlayer *target = static_cast<CBasePlayer *>(UTIL_PlayerByIndex(m_hObserverTarget->entindex()));

		if (!target)
			return;

		int weapon = target->m_pActiveItem ? target->m_pActiveItem->m_iId : 0;
		int targetBombState = STATUSICON_HIDE;

		// use fov of tracked client
		if (m_iFOV != target->m_iFOV || m_iObserverWeapon != weapon)
		{
			m_iClientFOV = m_iFOV = target->m_iFOV;

			// write fov before wepon data, so zoomed crosshair is set correctly
			MESSAGE_BEGIN(MSG_ONE, gmsgSetFOV, NULL, pev);
				WRITE_BYTE(m_iFOV);
			MESSAGE_END();

			m_iObserverWeapon = weapon;

			//send weapon update
			MESSAGE_BEGIN(MSG_ONE, gmsgCurWeapon, NULL, pev);
				WRITE_BYTE(1);	// 1 = current weapon, not on target
				WRITE_BYTE(m_iObserverWeapon);
				WRITE_BYTE(0);	// clip
			MESSAGE_END();

			// fix observer client weapon prediction
			MESSAGE_BEGIN(MSG_ONE, gmsgBTEWeapon, NULL, pev);
			WRITE_BYTE(BTE_Weapon_Active); // type, reserved.
			WRITE_STRING(target->m_pActiveItem ? target->m_pActiveItem->pszName() : "");
			MESSAGE_END();
		}

if (FClassnameIs(target->m_pActiveItem->pev,"weapon_colt_python"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"       COLT PYTHON\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_deagle_dual"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"       DUAL DEAGLE\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_dual_handgun"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"       DUAL HANDGUN\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_taurus_raging_bull"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     Tarurus Raging Bull\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_deagle"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     Desert Eagle        \"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_usp"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"         K5\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_glock18"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     Glock 18\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_bow"))
CLIENT_COMMAND(ENT(pev), "weaponName \"  Compound Bow        \"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_ak47"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"       AK47\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_m1887"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"       M1887\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_aksopmod"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"       AK SOPMOD\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_aug"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 0 ;weaponName \"       AUG A3\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_awp"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 3 ;weaponName \"       L115A1\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_aug_hbar"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 0 ;weaponName \"       AUG HBAR\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_augblitz"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 0 ;weaponName \"     AUG BLITZ\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_cheytac_m200"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 3 ;weaponName \"     Cheytac M200        \"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_dragunov"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 3 ;weaponName \"     Dragunov\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_p90"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 0 ;weaponName \"     P90 Ext\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_aug_a3_silencer"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 0 ;weaponName \"     AUG A3 SILENCER        \"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_m82a1"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 3 ;weaponName \"     BARRETT M82A1\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_f2000"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     F2000\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_famas_g2"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     Famas G2 Commando\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_g36c"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 0 ;weaponName \"     G36C\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_groza"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 0 ;weaponName \"     GROZA\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_k1"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     K1\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_k2"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     K2\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_kar98k"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 3 ;weaponName \"     Kar98k\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_kriss_sv"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     Kriss SV\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_kriss_sv_silence"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     Kriss SV Silencer\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_m4_cqb_lv1"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     M4 CQB LV1\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_m4_cqb_lv2"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 0 ;weaponName \"     M4 CQB LV2\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_m4_spr_lv1"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     M4 SPR LV1\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_m4_spr_lv2"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     M4 SPR LV2\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_m4a1"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     M4A1\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_m4a1_s"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     M4A1-S\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_mp7"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     MP7 Ext\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_oa93"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     OA93\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_p90_mc"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 0 ;weaponName \"     P90-MC\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_pindad_ss2_v5"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 0 ;weaponName \"     PINDAD SS2 V5\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_rangemaster_338"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 3 ;weaponName \"     RANGEMASTER 338\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_sc2010"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     SC 2010\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_scar_carbine"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 0 ;weaponName \"     SCAR CARBINE\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_spas_15"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     SPAS 15\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_tactilite_t2"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 3 ;weaponName \"     TACTILITE T2        \"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_kriss_sv_batik"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     KRISS SV BATIK        \"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_kriss_sv_crb"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     KRISS SV CRB\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_m4a1_s"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     M4A1 S\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_zombie_s"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     ZOMBIE SLAYER\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_mp5k"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     MP5K\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_m4_azure"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     HK 417\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_mp9"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 0 ;weaponName \"     MP9\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_m3"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     870MCS\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_scout"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 3 ;weaponName \"     SSG 69\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_sg550"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     SG 550\"\n");
//new
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_aksopmod_cg"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     AK SOPMOD CG\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_aug_esport"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 0 ;weaponName \"     AUG E-SPORT\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_t77"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     T77\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_apc"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 0 ;weaponName \"     APC9\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_fg42"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     FG42\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_msbs"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     MSBS\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_as50"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 3 ;weaponName \"     AS50\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_m1887_w"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     M1887 W\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_pgm"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 3 ;weaponName \"     PGM\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_ump"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     UMP 45\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_sig"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     SIG SAUER\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_spectre"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     SPECTRE\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_tar"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     TAR-21\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_xm8"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     XM8\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_water"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     WATER GUN\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_knife"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     M-7\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_amok"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     AMOK KUKRI\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_saber"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     SABER \"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_arabian_sword"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     ARABIAN SWORD\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_fangblade"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     FANGBLADE\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_combat"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     COMBAT MACHETE        \"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_knifebone"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     BONE KNIFE\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_brass_knuckle"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     BRASS KNUCKLES\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_candy_cane"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     CANDY CANE\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_dual_knife"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     DUAL KNIFE\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_keris"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     KERIS\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_mini_axe"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     MINI AXE\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_knife"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     M-7\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_ice"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     KNIGHT SWORD        \"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_karambit"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     KARAMBIT\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_butterfly"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     BUTTERFLY\"\n");


//grenade
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_medkit"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     MEDICAL KIT\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_hegrenade"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     K400\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_smokegrenade"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     SMOKE\"\n");
else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_gasbomb"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     WATERMELON PALESTINE\"\n");

else if (FClassnameIs(target->m_pActiveItem->pev,"weapon_c4"))
CLIENT_COMMAND(ENT(pev), "pb_crosshair 1 ;weaponName \"     C-4 EXPLOSIVE\"\n");

int body;

switch (target->m_iModelName)
{
case MODEL_TERROR:
body = 0;	
break;
case MODEL_LEET:
body = 1;
break;
case MODEL_ARCTIC:
body = 2;
break;
case MODEL_GUERILLA:
body = 3;
break;
case MODEL_MILITIA:
body = 4;
break;
case MODEL_URBAN:
body = 5;
break;
case MODEL_GSG9:
body = 6;
break;
case MODEL_SAS:
body = 7;
break;
case MODEL_GIGN:
body = 8;
break;
case MODEL_SPETSNAZ:
body = 9;
break;
}

MESSAGE_BEGIN(MSG_ONE, gmsgPlayerUpdate, NULL, pev);
WRITE_BYTE(body);
MESSAGE_END();


		if (target->m_bHasC4)
		{
			if (target->m_signals.GetState() & SIGNAL_BOMB)
				targetBombState = STATUSICON_FLASH;
			else
				targetBombState = STATUSICON_SHOW;
		}

		if (m_iObserverC4State != targetBombState)
		{
			m_iObserverC4State = targetBombState;

			if (targetBombState)
			{
				MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, pev);
					WRITE_BYTE(m_iObserverC4State);
					WRITE_STRING("c4");
					WRITE_BYTE(0);
					WRITE_BYTE(160);
					WRITE_BYTE(0);
				MESSAGE_END();
			}
			else
			{
				MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, pev);
					WRITE_BYTE(STATUSICON_HIDE);
					WRITE_STRING("c4");
				MESSAGE_END();
			}
		}

		if (m_bObserverHasDefuser != target->m_bHasDefuser)
		{
			m_bObserverHasDefuser = target->m_bHasDefuser;

			if (target->m_bHasDefuser)
			{
				MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, pev);
					WRITE_BYTE(STATUSICON_SHOW);
					WRITE_STRING("defuser");
					WRITE_BYTE(0);
					WRITE_BYTE(160);
					WRITE_BYTE(0);
				MESSAGE_END();
			}
			else
			{
				MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, pev);
					WRITE_BYTE(STATUSICON_HIDE);
					WRITE_STRING("defuser");
				MESSAGE_END();
			}
		}
	}
	else
	{
		m_iFOV = DEFAULT_FOV;

		if (m_iObserverWeapon)
		{
			m_iObserverWeapon = 0;

			MESSAGE_BEGIN(MSG_ONE, gmsgCurWeapon, NULL, pev);
				WRITE_BYTE(1);	// 1 = current weapon
				WRITE_BYTE(m_iObserverWeapon);
				WRITE_BYTE(0);	// clip
			MESSAGE_END();
		}

		if (m_iObserverC4State)
		{
			m_iObserverC4State = 0;

			MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, pev);
				WRITE_BYTE(0);
				WRITE_STRING("c4");
			MESSAGE_END();
		}

		if (m_bObserverHasDefuser)
		{
			m_bObserverHasDefuser = false;

			MESSAGE_BEGIN(MSG_ONE, gmsgStatusIcon, NULL, pev);
				WRITE_BYTE(0);
				WRITE_STRING("defuser");
			MESSAGE_END();
		}
	}
}

// Attempt to change the observer mode

void CBasePlayer::Observer_SetMode(int iMode)
{
	int _forcecamera;
	int oldMode;

	// Just abort if we're changing to the mode we're already in
	if (iMode == pev->iuser1)
		return;

	_forcecamera = GetForceCamera (this);

	// is valid mode ?
	if (iMode < OBS_CHASE_LOCKED || iMode > OBS_MAP_CHASE)
		iMode = OBS_IN_EYE;

	oldMode = pev->iuser1;

	if (m_iTeam != SPECTATOR)
	{
		if (_forcecamera == CAMERA_MODE_SPEC_ONLY_TEAM)
		{
			if (iMode == OBS_ROAMING)
				iMode = OBS_MAP_FREE;
		}
		else if (_forcecamera == CAMERA_MODE_SPEC_ONLY_FRIST_PERSON)
			iMode = OBS_IN_EYE;
	}

	// verify observer target again
	if (m_hObserverTarget != NULL)
	{
		CBaseEntity *pEnt = m_hObserverTarget;

		if (pEnt == this || !pEnt || pEnt->has_disconnected || ((CBasePlayer *)pEnt)->IsObserver() || (pEnt->pev->effects & EF_NODRAW) || (_forcecamera != CAMERA_MODE_SPEC_ANYONE && ((CBasePlayer *)pEnt)->m_iTeam != m_iTeam))
			m_hObserverTarget = NULL;
	}

	// set spectator mode
	pev->iuser1 = iMode;

	// if we are not roaming, we need a valid target to track
	if (iMode != OBS_ROAMING && m_hObserverTarget == nullptr)
	{
		Observer_FindNextPlayer(false);

		// if we didn't find a valid target switch to roaming
		if (m_hObserverTarget == nullptr)
		{
			ClientPrint(pev, HUD_PRINTCENTER, "#Ready_game");
			pev->iuser1 = OBS_ROAMING;
		}
	}

	// set target if not roaming
	if (pev->iuser1 == OBS_ROAMING)
		pev->iuser2 = 0;
	else
		pev->iuser2 = ENTINDEX(m_hObserverTarget->edict());

	// clear second target from death cam
	pev->iuser3 = 0;

	if (m_hObserverTarget != NULL)
		UTIL_SetOrigin(pev, m_hObserverTarget->pev->origin);

	MESSAGE_BEGIN(MSG_ONE, gmsgCrosshair, NULL, pev);
		WRITE_BYTE((iMode == OBS_ROAMING) != 0);
	MESSAGE_END();

	UpdateClientEffects(this, oldMode);

	// print spepctaor mode on client screen

	char modemsg[16];
	Q_sprintf(modemsg, "#Spec_Mode%i", pev->iuser1);
	//ClientPrint(pev, HUD_PRINTCENTER, modemsg);

	m_iObserverLastMode = iMode;
	m_bWasFollowing = false;
}
