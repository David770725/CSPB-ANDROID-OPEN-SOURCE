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

//this is dual off

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "weapons.h"
#include "game.h"
#include "wpn_kriss_sv_crb.h"

#ifndef CLIENT_DLL
#include "gamemode/mods.h"

#endif

enum scar_e
{
	SCARL_IDLE1,
	SCARL_RELOAD,
	SCARL_DRAW,
	SCARL_SHOOT1,
	SCARL_SHOOT2,
	SCARL_SHOOT3,
	CHANGE_SCARL, //dualon
OFF, 
	SCARH_IDLE1,
	SCARH_RELOAD,
	SCARH_DRAW,
	ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5
};

LINK_ENTITY_TO_CLASS(weapon_kriss_sv_crb, CKriss_sv_crb)

const float SCARL_AMMO = 40;

void CKriss_sv_crb::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_kriss_sv_crb");

	Precache();
	m_iId = WEAPON_GALIL;
	SET_MODEL(ENT(pev), "models/w_scar.mdl");

	m_iDefaultAmmo = SCARL_AMMO;

	FallInit();

	m_pLink = nullptr;
	m_iSwing = 0;
}

#ifndef CLIENT_DLL
void CKriss_sv_crb::AttachToPlayer(CBasePlayer *pPlayer)
{
	CBasePlayerWeapon::AttachToPlayer(pPlayer);
pPlayer->GiveNamedItem("weapon_kriss_sv_dual_crb");
	// find the linked weapon
	while (!m_pLink)
	{
		for (int i = 0; i < MAX_ITEM_TYPES; ++i)
		{
			CBasePlayerItem *pItem = m_pPlayer->m_rgpPlayerItems[i];
			while (pItem != NULL)
			{
				if (!Q_stricmp(pItem->pszName(), "weapon_kriss_sv_dual_crb"))
				{
					m_pLink = pItem;

					m_pLink->m_iSwing = 1;
					m_iSwing = 0;
				}

				pItem = pItem->m_pNext;
			}
		}
		if (!m_pLink)
			pPlayer->GiveNamedItem("weapon_kriss_sv_dual_crb");


pPlayer->GiveNamedItem("weapon_kriss_sv_dual_crb");
	}
}


void CKriss_sv_crb::ItemPostFrame()
{
	m_iSwing = 0;
	if (m_pLink)
		m_pLink->m_iSwing = 1;
	return CBasePlayerWeapon::ItemPostFrame();
}

CKriss_sv_crb::~CKriss_sv_crb()
{
	CBaseEntity *pOther = m_pLink;
	if (pOther && pOther->m_pLink == this)
	{
		pOther->m_pLink = m_pLink = nullptr;
		pOther->SUB_Remove();
	}
}
#endif

void CKriss_sv_crb::Precache(void)
{
	
PRECACHE_MODEL("models/billflx/v_kriss_sv_crb.mdl");

	PRECACHE_MODEL("models/p_kriss_sv_crb.mdl");

	PRECACHE_MODEL("models/w_scar.mdl");

//test
m_iSprBeam = PRECACHE_MODEL("sprites/trace.spr");

	PRECACHE_SOUND("weapons/kriss_sv_silence-1.wav");
	PRECACHE_SOUND("weapons/scar_l.wav");
PRECACHE_SOUND("weapons/zoom_generic_in.wav");
PRECACHE_SOUND("weapons/zoom_generic_out.wav");

	m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireKriss_sv_crb = PRECACHE_EVENT(1, "events/ak47.sc");
}

int CKriss_sv_crb::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "556Nato";
	p->iMaxAmmo1 = MAX_AMMO_556NATO;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = SCARL_AMMO;
	p->iSlot = 0;
	p->iPosition = 17;
	p->iId = WEAPON_GALIL;
	p->iFlags = 0;
	p->iWeight = 25;

	return 1;
}


BOOL CKriss_sv_crb::Deploy(void)
{
m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	iShellOn = 1;

	if (m_iSwing)
	{

DefaultDeploy("models/billflx/v_kriss_sv_crb.mdl", "models/p_kriss_sv_crb.mdl", SCARL_DRAW, "carbine", 0);

	}
	else
	{

DefaultDeploy("models/billflx/v_kriss_sv_crb.mdl", "models/p_kriss_sv_crb.mdl", SCARL_DRAW, "carbine", 0);
	}
	return TRUE;
}


void CKriss_sv_crb::QuickDeploy()
{
SendWeaponAnim(ANIM1, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CKriss_sv_crb::SecondaryAttack(void)
{


switch (m_pPlayer->m_iFOV)
	{
		case 90:

SetThink(&CKriss_sv_crb::Fov2);
	pev->nextthink = gpGlobals->time + 0.0000009;
break;

		default:
SetThink(&CKriss_sv_crb::offFov2);
	pev->nextthink = gpGlobals->time + 0.0000009;



 break;
	}

	m_pPlayer->ResetMaxSpeed();
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}


void CKriss_sv_crb::Fov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 

SetThink(&CKriss_sv_crb::Fov3);
	pev->nextthink = gpGlobals->time + 0.0000009;

#ifndef CLIENT_DLL
if (weapon_sight_kriss_sv_crb.value == 0)
CLIENT_COMMAND(m_pPlayer->edict(), "EotechCrb_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 1) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 1; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 2) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 2; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 3) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 3; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 4) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 4; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 5) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 5; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 6) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 6; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 7) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 7; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 8) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 8; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 9) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 9; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 10) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 10; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 11) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 11; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 12) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 12; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 13) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 13; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 14) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 14; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 15) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 15; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 16) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 16; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 17) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 17; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 18) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 18; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 19) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 19; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 20) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 20; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 21) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 21; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 22) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 22; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 23) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 23; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 24) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 24; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 25) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 25; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 26) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 26; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 27) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 27; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 28) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 28; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 29) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 29; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 30) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 30; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 31) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 31; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 32) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 32; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 33) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 33; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 34) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 34; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 35) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 35; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 36) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 36; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 37) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 37; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 38) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 38; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 39) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 39; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 40) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 40; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 41) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 41; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 42) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 42; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 43) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 43; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 44) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 44; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 45) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 45; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 46) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 46; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 47) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 47; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 48) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 48; Custom_Scope\n");
else if (weapon_sight_kriss_sv_crb.value == 49) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 49; Custom_Scope\n");
#endif

}

void CKriss_sv_crb::Fov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 80; 

SetThink(&CKriss_sv_crb::Fov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CKriss_sv_crb::Fov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CKriss_sv_crb::Fov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CKriss_sv_crb::Fov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 65; 

SetThink(&CKriss_sv_crb::Fov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CKriss_sv_crb::Fov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 55; 
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_generic_in.wav", 0.2, 2.4);

m_pPlayer->pev->viewmodel = MAKE_STRING("models/sight/v_muzzle_bottom.mdl");
SendWeaponAnim(SCARL_IDLE1, UseDecrement() != FALSE);
m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
}

//offfov

void CKriss_sv_crb::offFov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 60; 

SetThink(&CKriss_sv_crb::offFov3);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CKriss_sv_crb::offFov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CKriss_sv_crb::offFov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CKriss_sv_crb::offFov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CKriss_sv_crb::offFov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}
void CKriss_sv_crb::offFov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 
SendWeaponAnim(SCARL_IDLE1, 0);
SetThink(&CKriss_sv_crb::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CKriss_sv_crb::offFov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90; 
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_generic_out.wav", 0.2, 2.4);

m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/v_kriss_sv_crb.mdl");


}


void CKriss_sv_crb::PrimaryAttack(void)
{
	
		Kriss_sv_crbFire((0.0) * m_flAccuracy, 0.057, FALSE);
}

void CKriss_sv_crb::Kriss_sv_crbFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	m_bDelayFire = true;
	m_iShotsFired++;
	m_flAccuracy = ((float)(m_iShotsFired * m_iShotsFired * m_iShotsFired) / 220.0) + 0.25;

	if (m_flAccuracy > 1)
		m_flAccuracy = 1;

	if (m_iClip <= 0)
	{
		if (m_fFireOnEmpty)
		{
			PlayEmptySound();
			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.2;
		}

		return;
	}

	m_iClip--;
	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecDir = m_pPlayer->FireBullets3(vecSrc, gpGlobals->v_forward, flSpread, 8192, 2, BULLET_PLAYER_556MM, 20, 0.97, m_pPlayer->pev, FALSE, m_pPlayer->random_seed);
if (m_iClip > 0)
{
SendWeaponAnim(SCARL_SHOOT1, 0);
}
else if (m_iClip == 0)
{
SendWeaponAnim(SCARL_IDLE1, 0);
}
//Vector vecSrc = m_pPlayer->GetGunPosition();
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/kriss_sv_silence-1.wav", VOL_NORM, ATTN_NORM);

	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(),m_usFireKriss_sv_crb, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 10000000), (int)(m_pPlayer->pev->punchangle.y * 10000000), FALSE, FALSE);

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;

#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.9;

	if (m_pPlayer->pev->velocity.Length2D() > 0)
		KickBack(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	else if (!FBitSet(m_pPlayer->pev->flags, FL_ONGROUND))
		KickBack(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	else if (FBitSet(m_pPlayer->pev->flags, FL_DUCKING))
		KickBack(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	else
		KickBack(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
}

float CKriss_sv_crb::GetDamage()
{
#ifndef CLIENT_DLL
	if (g_pModRunning->DamageTrack() != DT_NONE)
		return 44;
#endif
	return 32;
}

void CKriss_sv_crb::Reload(void)
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;
if (m_iClip == SCARL_AMMO)
return;
	if (DefaultReload(SCARL_AMMO, NULL, 2.3))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif



SetThink(&CKriss_sv_crb::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;

m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 3;



		
	}
SendWeaponAnim(SCARL_RELOAD, 0);
}

void CKriss_sv_crb::QuickReload()
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;
if (m_iClip == SCARL_AMMO)
return;
	if (DefaultReloadQuick(SCARL_AMMO, NULL, 1.3))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif

SetThink(&CKriss_sv_crb::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;

m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;

	}
SendWeaponAnim(ANIM2, 0);
}

void CKriss_sv_crb::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
	SendWeaponAnim(SCARL_IDLE1, UseDecrement() != FALSE);
}
