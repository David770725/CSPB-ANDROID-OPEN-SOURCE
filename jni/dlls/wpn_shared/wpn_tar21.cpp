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
#include "game.h"
#include "wpn_tar21.h"

enum aug_e
{
	AUG_IDLE1,
	AUG_RELOAD,
	AUG_DRAW,
	AUG_SHOOT1,
	AUG_SHOOT2,
	AUG_SHOOT3,
OFF,
ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5
};

LINK_ENTITY_TO_CLASS(weapon_tar, CTAR)

const float tar_ammo = 45;
void CTAR::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_tar");

	Precache();
	m_iId = WEAPON_GALIL;
	SET_MODEL(ENT(pev), "models/w_aug_a3.mdl");

	m_iDefaultAmmo = tar_ammo;
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;

	FallInit();
}

void CTAR::Precache(void)
{
	
PRECACHE_MODEL("models/billflx/v_tar21.mdl");

	PRECACHE_MODEL("models/p_tar21.mdl");

	PRECACHE_SOUND("weapons/tar21-1.wav");
	PRECACHE_SOUND("weapons/aug_clipout.wav");
	PRECACHE_SOUND("weapons/aug_clipin.wav");
	PRECACHE_SOUND("weapons/aug_boltpull.wav");
	PRECACHE_SOUND("weapons/aug_boltslap.wav");
	PRECACHE_SOUND("weapons/aug_forearm.wav");
PRECACHE_SOUND("weapons/zoom_generic_in.wav");
PRECACHE_SOUND("weapons/zoom_generic_out.wav");
	m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireFamas_g2 = PRECACHE_EVENT(1, "events/ak47.sc");
}

int CTAR::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "556Nato";
	p->iMaxAmmo1 = MAX_AMMO_556NATO;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = tar_ammo;
	p->iSlot = 0;
	p->iPosition = 17;
	p->iId = WEAPON_GALIL;
	p->iFlags = 0;
	p->iWeight = 25;

	return 1;
}


BOOL CTAR::Deploy(void)
{
m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	iShellOn = 1;

return DefaultDeploy("models/billflx/v_tar21.mdl", "models/p_tar21.mdl", AUG_DRAW, "rifle", 0);

}

void CTAR::QuickDeploy()
{
SendWeaponAnim(ANIM4, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CTAR::SecondaryAttack(void)
{
	
switch (m_pPlayer->m_iFOV)
	{
		case 90:

SetThink(&CTAR::Fov2);
	pev->nextthink = gpGlobals->time + 0.0000009;
break;

		default:
SetThink(&CTAR::offFov2);
	pev->nextthink = gpGlobals->time + 0.0000009;



 break;
	}

	m_pPlayer->ResetMaxSpeed();
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}


void CTAR::Fov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 

SetThink(&CTAR::Fov3);
	pev->nextthink = gpGlobals->time + 0.0000009;


#ifndef CLIENT_DLL
if (weapon_sight_tar.value == 0)
CLIENT_COMMAND(m_pPlayer->edict(), "eotech_scope\n");
else if (weapon_sight_tar.value == 1) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 1; Custom_Scope\n");
else if (weapon_sight_tar.value == 2) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 2; Custom_Scope\n");
else if (weapon_sight_tar.value == 3) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 3; Custom_Scope\n");
else if (weapon_sight_tar.value == 4) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 4; Custom_Scope\n");
else if (weapon_sight_tar.value == 5) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 5; Custom_Scope\n");
else if (weapon_sight_tar.value == 6) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 6; Custom_Scope\n");
else if (weapon_sight_tar.value == 7) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 7; Custom_Scope\n");
else if (weapon_sight_tar.value == 8) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 8; Custom_Scope\n");
else if (weapon_sight_tar.value == 9) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 9; Custom_Scope\n");
else if (weapon_sight_tar.value == 10) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 10; Custom_Scope\n");
else if (weapon_sight_tar.value == 11) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 11; Custom_Scope\n");
else if (weapon_sight_tar.value == 12) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 12; Custom_Scope\n");
else if (weapon_sight_tar.value == 13) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 13; Custom_Scope\n");
else if (weapon_sight_tar.value == 14) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 14; Custom_Scope\n");
else if (weapon_sight_tar.value == 15) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 15; Custom_Scope\n");
else if (weapon_sight_tar.value == 16) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 16; Custom_Scope\n");
else if (weapon_sight_tar.value == 17) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 17; Custom_Scope\n");
else if (weapon_sight_tar.value == 18) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 18; Custom_Scope\n");
else if (weapon_sight_tar.value == 19) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 19; Custom_Scope\n");
else if (weapon_sight_tar.value == 20) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 20; Custom_Scope\n");
else if (weapon_sight_tar.value == 21) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 21; Custom_Scope\n");
else if (weapon_sight_tar.value == 22) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 22; Custom_Scope\n");
else if (weapon_sight_tar.value == 23) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 23; Custom_Scope\n");
else if (weapon_sight_tar.value == 24) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 24; Custom_Scope\n");
else if (weapon_sight_tar.value == 25) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 25; Custom_Scope\n");
else if (weapon_sight_tar.value == 26) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 26; Custom_Scope\n");
else if (weapon_sight_tar.value == 27) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 27; Custom_Scope\n");
else if (weapon_sight_tar.value == 28) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 28; Custom_Scope\n");
else if (weapon_sight_tar.value == 29) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 29; Custom_Scope\n");
else if (weapon_sight_tar.value == 30) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 30; Custom_Scope\n");
else if (weapon_sight_tar.value == 31) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 31; Custom_Scope\n");
else if (weapon_sight_tar.value == 32) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 32; Custom_Scope\n");
else if (weapon_sight_tar.value == 33) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 33; Custom_Scope\n");
else if (weapon_sight_tar.value == 34) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 34; Custom_Scope\n");
else if (weapon_sight_tar.value == 35) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 35; Custom_Scope\n");
else if (weapon_sight_tar.value == 36) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 36; Custom_Scope\n");
else if (weapon_sight_tar.value == 37) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 37; Custom_Scope\n");
else if (weapon_sight_tar.value == 38) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 38; Custom_Scope\n");
else if (weapon_sight_tar.value == 39) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 39; Custom_Scope\n");
else if (weapon_sight_tar.value == 40) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 40; Custom_Scope\n");
else if (weapon_sight_tar.value == 41) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 41; Custom_Scope\n");
else if (weapon_sight_tar.value == 42) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 42; Custom_Scope\n");
else if (weapon_sight_tar.value == 43) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 43; Custom_Scope\n");
else if (weapon_sight_tar.value == 44) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 44; Custom_Scope\n");
else if (weapon_sight_tar.value == 45) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 45; Custom_Scope\n");
else if (weapon_sight_tar.value == 46) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 46; Custom_Scope\n");
else if (weapon_sight_tar.value == 47) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 47; Custom_Scope\n");
else if (weapon_sight_tar.value == 48) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 48; Custom_Scope\n");
else if (weapon_sight_tar.value == 49) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 49; Custom_Scope\n");
#endif

}

void CTAR::Fov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 80; 

SetThink(&CTAR::Fov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CTAR::Fov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CTAR::Fov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CTAR::Fov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 65; 

SetThink(&CTAR::Fov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CTAR::Fov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 55; 
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_generic_in.wav", 0.2, 2.4);


m_pPlayer->pev->viewmodel = MAKE_STRING("models/sight/v_muzzle_bottom.mdl");
SendWeaponAnim(AUG_IDLE1, UseDecrement() != FALSE);
}

//offfov

void CTAR::offFov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 60; 

SetThink(&CTAR::offFov3);
	pev->nextthink = gpGlobals->time + 0.0000009;

}

void CTAR::offFov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CTAR::offFov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CTAR::offFov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CTAR::offFov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}
void CTAR::offFov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 
SendWeaponAnim(AUG_IDLE1, 0);
SetThink(&CTAR::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CTAR::offFov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90; 
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_generic_out.wav", 0.2, 2.4);


m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/v_tar21.mdl");


}


void CTAR::PrimaryAttack(void)
{
		Famas_g2Fire((0.0) * m_flAccuracy, 0.0825, FALSE);
}

void CTAR::Famas_g2Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	m_bDelayFire = true;
	m_iShotsFired++;
	m_flAccuracy = ((float)(m_iShotsFired * m_iShotsFired * m_iShotsFired) / 215.0) + 0.3;

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
	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecDir = m_pPlayer->FireBullets3(vecSrc, gpGlobals->v_forward, flSpread, 8192, 2, BULLET_PLAYER_556MM, 20, 0.96, m_pPlayer->pev, FALSE, m_pPlayer->random_seed);

//Vector vecSrc = m_pPlayer->GetGunPosition();
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/tar21-1.wav", VOL_NORM, ATTN_NORM);

if (m_iClip > 0)
{
SendWeaponAnim(AUG_SHOOT1, 0);
}
else if (m_iClip == 0)
{
SendWeaponAnim(AUG_IDLE1, 0);
}



	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(),m_usFireFamas_g2, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), FALSE, FALSE);
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

void CTAR::Reload(void)
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;
if (m_iClip == tar_ammo)
return;
	if (DefaultReload(tar_ammo, NULL, 2.3))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
			SetThink(&CTAR::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;

m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 3;

		
	}
SendWeaponAnim(AUG_RELOAD, 0);
}


void CTAR::QuickReload()
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;
if (m_iClip == tar_ammo)
return;
	if (DefaultReloadQuick(tar_ammo, NULL, 1.3))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
			SetThink(&CTAR::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;

m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.3;
}
SendWeaponAnim(ANIM5, 0);
}

void CTAR::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
	SendWeaponAnim(AUG_IDLE1, UseDecrement() != FALSE);
}

