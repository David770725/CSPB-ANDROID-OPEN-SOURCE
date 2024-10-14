/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "weapons.h"
#include "hltv.h"
#include "gamerules.h"
#include "wpn_c4.h"

#ifndef CLIENT_DLL

// CSBOT and Nav
#include "schedule.h"
#include "archtypes.h"
#include "scriptevent.h"
#include "enginecallback.h"
#include "entity_state.h"
#include "nodes.h"
#include "screenfade.h"

// SDK
#include "usercmd.h"
#include "weaponinfo.h"
#include "customentity.h"

// Globals vars
#include "globals.h"
#include "saverestore.h"

// GameInit
#include "game.h"

//PM
#include "pm_shared/pm_defs.h"
#include "pm_shared/pm_materials.h"
#include "pm_shared/pm_movevars.h"
#include "pm_shared/pm_debug.h"
#include "pm_shared/pm_shared.h"

#include "shake.h"
#include "decals.h"
#include "hltv.h"
#include "world.h"

#include "sound.h"
#include "basemonster.h"
#include "monsters.h"
#include "ammo.h"
#include "mortar.h"
#include "effects.h"
#include "lights.h"
#include "items.h"
#include "healthkit.h"
#include "vehicle.h"
#include "func_tank.h"
#include "func_break.h"
#include "doors.h"
#include "bmodels.h"

#include "debug.h"

#include "observer.h"
#include "client.h"

#include "trains.h"
#include "pathcorner.h"
#include "plats.h"

// CSBOT and Nav
#include "game_shared/GameEvent.h"		// Game event enum used by career mode, tutor system, and bots
#include "game_shared/bot/bot_util.h"
#include "game_shared/bot/simple_state_machine.h"

#include "game_shared/steam_util.h"
#include "game_shared/perf_counter.h"

#include "game_shared/bot/bot_manager.h"
#include "game_shared/bot/bot_constants.h"
#include "game_shared/bot/bot.h"

#include "game_shared/shared_util.h"
#include "game_shared/bot/bot_profile.h"

#include "game_shared/bot/nav.h"
#include "game_shared/bot/improv.h"
#include "game_shared/bot/nav_node.h"
#include "game_shared/bot/nav_area.h"
#include "game_shared/bot/nav_file.h"
#include "game_shared/bot/nav_path.h"

#include "airtank.h"
#include "h_ai.h"
#include "h_cycler.h"
#include "h_battery.h"

// Hostage
#include "hostage/hostage.h"
#include "hostage/hostage_localnav.h"

#include "bot/cs_bot.h"

// Tutor
#include "tutor.h"
#include "tutor_base_states.h"
#include "tutor_base_tutor.h"
#include "tutor_cs_states.h"
#include "tutor_cs_tutor.h"

#include "revert_saved.h"
#include "triggers.h"
#include "subs.h"
#include "doors.h"
#include "explode.h"
#include "gamerules.h"
#include "career_tasks.h"
#include "training_gamerules.h"
#include "maprules.h"
#include "monsterevent.h"
#include "plane.h"
#include "skill.h"
#include "soundent.h"
#include "spectator.h"
#include "talkmonster.h"
#include "animation.h"

#include "com_model.h"
#include "studio.h"
#include "r_studioint.h"

#include "shake.h"

#endif

//#define C4MADNESS
#ifdef CLIENT_DLL
extern bool g_bInBombZone;
#endif

enum c4_e
{
	C4_IDLE1,
	C4_DRAW,
	C4_DROP,
	C4_ARM
};

LINK_ENTITY_TO_CLASS(weapon_c4, CC4)

void CC4::Spawn(void)
{
	SET_MODEL(ENT(pev), "models/w_backpack.mdl");

	pev->frame = 0;
	//pev->body = 3;
	pev->sequence = 0;
	pev->framerate = 0;

	m_iId = WEAPON_C4;
	m_iDefaultAmmo = C4_DEFAULT_GIVE;
	m_bStartedArming = false;
	m_fArmedTime = 0;

	if (!FStringNull(pev->targetname))
	{
		pev->effects |= EF_NODRAW;
		DROP_TO_FLOOR(ENT(pev));
		return;
	}

	FallInit();
	SetThink(&CBasePlayerItem::FallThink);
	pev->nextthink = UTIL_WeaponTimeBase() + 0.1;
}

void CC4::Precache(void)
{
	PRECACHE_MODEL("models/v_c4.mdl");
	PRECACHE_MODEL("models/w_backpack.mdl");

	PRECACHE_SOUND("weapons/c4_click.wav");
}

int CC4::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "C4";
	p->iMaxAmmo1 = MAX_AMMO_C4;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = WEAPON_NOCLIP;
	p->iSlot = 4;
	p->iPosition = 3;
	p->iId = WEAPON_C4;
	p->iWeight = C4_WEIGHT;
	p->iFlags = ITEM_FLAG_LIMITINWORLD | ITEM_FLAG_EXHAUSTIBLE;

	return 1;
}

BOOL CC4::Deploy(void)
{
	m_bStartedArming = false;
	m_fArmedTime = 0;

	if (m_pPlayer->HasShield() != false)
	{
		m_bHasShield = true;
		m_pPlayer->pev->gamestate = 1;
	}

	return DefaultDeploy("models/v_c4.mdl", "models/p_c4.mdl", C4_DRAW, "c4", UseDecrement() != FALSE);
}

void CC4::Holster(int skiplocal)
{
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;
	m_bStartedArming = false;

	if (!m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
	{
		m_pPlayer->pev->weapons &= ~(1 << WEAPON_C4);
		DestroyItem();
	}

	if (m_bHasShield == true)
	{
		m_pPlayer->pev->gamestate = 0;
		m_bHasShield = false;
	}
}

void CC4::PrimaryAttack(void)
{
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		return;

	int inBombZone = (m_pPlayer->m_signals.GetState() & SIGNAL_BOMB) == SIGNAL_BOMB;
	int onGround = (m_pPlayer->pev->flags & FL_ONGROUND) == FL_ONGROUND;
	bool bPlaceBomb = (onGround && inBombZone);

	if (!m_bStartedArming)
	{
		if (!inBombZone)
		{
			ClientPrint(m_pPlayer->pev, HUD_PRINTCENTER, "#C4_Plant_At_Bomb_Spot");
#ifndef CLIENT_DLL
			m_flNextPrimaryAttack = GetNextAttackDelay(1.0);
#endif
			return;
		}

		if (!onGround)
		{
			ClientPrint(m_pPlayer->pev, HUD_PRINTCENTER, "#C4_Plant_Must_Be_On_Ground");
#ifndef CLIENT_DLL
			m_flNextPrimaryAttack = GetNextAttackDelay(1.0);
#endif
			return;
		}

		m_bStartedArming = true;
		m_bBombPlacedAnimation = false;
		m_fArmedTime = gpGlobals->time + C4_ARMING_ON_TIME;

		// player "arming bomb" animation
		SendWeaponAnim(C4_ARM, UseDecrement() != FALSE);

		// freeze the player in place while planting
		SET_CLIENT_MAXSPEED(m_pPlayer->edict(), 1.0);

#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_ATTACK1);
		m_pPlayer->SetProgressBarTime(C4_ARMING_ON_TIME);
#endif
	}
	else
	{
		if (bPlaceBomb)
		{
			CBaseEntity *pEntity = NULL;
			CBasePlayer *pTempPlayer = NULL;

			if (m_fArmedTime <= gpGlobals->time)
			{
				if (m_bStartedArming)
				{
					m_bStartedArming = false;
					m_fArmedTime = 0;

					Broadcast("BOMBPL");
#ifndef CLIENT_DLL

float tmRemaining;
CHalfLifeMultiplay *mp = g_pGameRules;
tmRemaining = mp->m_iC4Timer;

MESSAGE_BEGIN(MSG_ALL, gmsgC4_hud);
WRITE_BYTE(1);
WRITE_BYTE(tmRemaining);
MESSAGE_END();

					m_pPlayer->m_bHasC4 = false;

					if (pev->speed != 0 && g_pGameRules)
					{
						g_pGameRules->m_iC4Timer = int(pev->speed);
					}

					CGrenade *pBomb = CGrenade::ShootSatchelCharge(m_pPlayer->pev, m_pPlayer->pev->origin, Vector(0, 0, 0));

					MESSAGE_BEGIN(MSG_SPEC, SVC_DIRECTOR);
						WRITE_BYTE(9);
						WRITE_BYTE(DRC_CMD_EVENT);
						WRITE_SHORT(m_pPlayer->entindex());
						WRITE_SHORT(0);
						WRITE_LONG(DRC_FLAG_FACEPLAYER | 11);
					MESSAGE_END();

UTIL_ClientPrintAll(HUD_PRINTCENTER, "#Bomb_Planted");

					if (TheBots)
					{
						TheBots->OnEvent(EVENT_BOMB_PLANTED, m_pPlayer, pBomb);
					}

					if (TheCareerTasks && g_pGameRules->IsCareer() && !m_pPlayer->IsBot())
					{
						TheCareerTasks->HandleEvent(EVENT_BOMB_PLANTED, m_pPlayer);
					}

					UTIL_LogPrintf("\"%s<%i><%s><TERRORIST>\" triggered \"Planted_The_Bomb\"\n",
						STRING(m_pPlayer->pev->netname),
						GETPLAYERUSERID(m_pPlayer->edict()),
						GETPLAYERAUTHID(m_pPlayer->edict()));

					g_pGameRules->m_bBombDropped = FALSE;
#endif
					// Play the plant sound.
					EMIT_SOUND(edict(), CHAN_WEAPON, "weapons/c4_plant.wav", VOL_NORM, ATTN_NORM);

					// hide the backpack in Terrorist's models.
			

					// release the player from being frozen
#ifndef CLIENT_DLL
				m_pPlayer->ResetMaxSpeed();				
				m_pPlayer->SetBombIcon(FALSE);
#endif

					if (--m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
					{
						RetireWeapon();
						return;
					}
				}
			}
			else
			{
				if (m_fArmedTime - 0.75f <= gpGlobals->time && !m_bBombPlacedAnimation)
				{
					// call the c4 Placement animation
					m_bBombPlacedAnimation = true;
					SendWeaponAnim(C4_DROP, UseDecrement() != FALSE);

#ifndef CLIENT_DLL
					m_pPlayer->SetAnimation(PLAYER_HOLDBOMB);
#endif
				}
			}
		}
		else
		{
			if (inBombZone)
				ClientPrint(m_pPlayer->pev, HUD_PRINTCENTER, "#C4_Plant_Must_Be_On_Ground");
			else
				ClientPrint(m_pPlayer->pev, HUD_PRINTCENTER, "#C4_Arming_Cancelled");

			m_bStartedArming = false;
#ifndef CLIENT_DLL
			m_flNextPrimaryAttack = GetNextAttackDelay(1.5);
#endif

			// release the player from being frozen, we've somehow left the bomb zone
#ifndef CLIENT_DLL
			m_pPlayer->ResetMaxSpeed();
			m_pPlayer->SetProgressBarTime(0);
			m_pPlayer->SetAnimation(PLAYER_HOLDBOMB);
#endif

			// this means the placement animation is canceled
			if (m_bBombPlacedAnimation)
				SendWeaponAnim(C4_DRAW, UseDecrement() != FALSE);
			else
				SendWeaponAnim(C4_IDLE1, UseDecrement() != FALSE);

			return;
		}
	}
#ifndef CLIENT_DLL
	m_flNextPrimaryAttack = GetNextAttackDelay(0.3);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + RANDOM_FLOAT(10, 15);
}

void CC4::WeaponIdle(void)
{
	if (m_bStartedArming == true)
	{
		m_bStartedArming = false;
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1;
#ifndef CLIENT_DLL
		m_pPlayer->ResetMaxSpeed();
		m_pPlayer->SetProgressBarTime(0);
#endif

		if (m_bBombPlacedAnimation == true)
			SendWeaponAnim(C4_DRAW, UseDecrement() != FALSE);
		else
			SendWeaponAnim(C4_IDLE1, UseDecrement() != FALSE);
	}

	if (m_flTimeWeaponIdle <= UTIL_WeaponTimeBase())
	{
		if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		{
			RetireWeapon();
			return;
		}

		SendWeaponAnim(C4_DRAW, UseDecrement() != FALSE);
		SendWeaponAnim(C4_IDLE1, UseDecrement() != FALSE);
	}
}

void CC4::KeyValue(KeyValueData *pkvd)
{
	if (FStrEq(pkvd->szKeyName, "detonatedelay"))
	{
		pev->speed = atof(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "detonatetarget"))
	{
		pev->noise1 = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "defusetarget"))
	{
		pev->target = ALLOC_STRING(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseEntity::KeyValue(pkvd);
}

void CC4::Use(CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value)
{
	if (m_pPlayer)
		return;

	CBasePlayer *pPlayer = (CBasePlayer *)UTIL_PlayerByIndex(1);

	if (pPlayer)
	{
		edict_t *target = pPlayer->m_pentCurBombTarget;
		pPlayer->m_pentCurBombTarget = NULL;

#ifndef CLIENT_DLL
		if (pev->speed != 0 && g_pGameRules)
			g_pGameRules->m_iC4Timer = (int)pev->speed;
#endif

		EMIT_SOUND(ENT(pev), CHAN_WEAPON, "weapons/c4_plant.wav", VOL_NORM, ATTN_NORM);
		CGrenade::ShootSatchelCharge(m_pPlayer->pev, m_pPlayer->pev->origin, Vector(0, 0, 0));

		CGrenade *pC4 = NULL;
		while ((pC4 = (CGrenade *)UTIL_FindEntityByClassname(pC4, "grenade")))
		{
			if (pC4->m_bIsC4 && pC4->m_flNextFreq == gpGlobals->time)
			{
				pC4->pev->target = pev->target;
				pC4->pev->noise1 = pev->noise1;
				break;
			}
		}

		pPlayer->m_pentCurBombTarget = target;
		SUB_Remove();
	}
}
