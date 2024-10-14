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
#include "wpn_ump.h"

//extern cvar_t ak47_damage;

enum ak47_e
{
	mp5k_IDLE,
	mp5k_SHOOT1,
	mp5k_SHOOT2,
	mp5k_SHOOT3,
	mp5k_RELOAD,
	mp5k_DRAW,
	mp5k_ATTACH_SILENCER,
	mp5k_UNSIL_IDLE,
	mp5k_UNSIL_SHOOT1,
	mp5k_UNSIL_SHOOT2,
	mp5k_UNSIL_SHOOT3,
	mp5k_UNSIL_RELOAD,
	mp5k_UNSIL_DRAW,
	mp5k_DETACH_SILENCER,
ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5,
ANIM6,
ANIM7,
ANIM8,
ANIM9,
ANIM10
};

LINK_ENTITY_TO_CLASS(weapon_ump, CUMP)

void CUMP::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_ump");

	Precache();
	m_iId = WEAPON_GALIL;
	SET_MODEL(ENT(pev), "models/w_ak47.mdl");

	m_iDefaultAmmo = AK47_DEFAULT_GIVE;
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;

	FallInit();
}

void CUMP::Precache(void)
{
	//PRECACHE_MODEL("models/billflx/cityforce/v_ak47.mdl");
//PRECACHE_MODEL("models/billflx/rebel/v_ak47.mdl");


PRECACHE_MODEL("models/billflx/v_ump45.mdl");


//test

	PRECACHE_MODEL("models/p_ump45.mdl");

	PRECACHE_SOUND("weapons/ak47-1.wav");
	PRECACHE_SOUND("weapons/ak47-2.wav");
	PRECACHE_SOUND("weapons/ak47_clipout.wav");
	PRECACHE_SOUND("weapons/ak47_clipin.wav");
	PRECACHE_SOUND("weapons/ak47_boltpull.wav");

	m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireAK47 = PRECACHE_EVENT(1, "events/ak47.sc");
}

int CUMP::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "762Nato";
	p->iMaxAmmo1 = MAX_AMMO_762NATO;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = AK47_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 17;
	p->iId = WEAPON_GALIL;
	p->iFlags = 0;
	p->iWeight = 25;

	return 1;
}


BOOL CUMP::Deploy(void)
{

	m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	iShellOn = 1;

if (m_iWeaponState & WPNSTATE_M4A1_SILENCED)
{
return DefaultDeploy("models/billflx/v_ump45.mdl", "models/p_ump45.mdl", mp5k_DRAW, "rifle", 0);
}
else
{
return DefaultDeploy("models/billflx/v_ump45.mdl", "models/p_ump45.mdl", mp5k_UNSIL_DRAW, "rifle", 0);
}

}

void CUMP::QuickDeploy()
{
if (m_iWeaponState & WPNSTATE_M4A1_SILENCED)
SendWeaponAnim(ANIM7, 0);
else
SendWeaponAnim(ANIM8, 0);

m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CUMP::detach(void)
{

SendWeaponAnim(mp5k_DETACH_SILENCER, 0);
}

void CUMP::attach(void)
{

SendWeaponAnim(mp5k_ATTACH_SILENCER, 0);
}

void CUMP::SecondaryAttack(void)
{
	if (m_iWeaponState & WPNSTATE_M4A1_SILENCED)
	{
		m_iWeaponState &= ~WPNSTATE_M4A1_SILENCED;
SetThink(&CUMP::detach);
	pev->nextthink = gpGlobals->time + 0.0001;
DefaultReload(AK47_MAX_CLIP, NULL, 1);
	
		strcpy(m_pPlayer->m_szAnimExtention, "rifle");
	}
	else
	{
		m_iWeaponState |= WPNSTATE_M4A1_SILENCED;
		SetThink(&CUMP::attach);
	pev->nextthink = gpGlobals->time + 0.0001;
DefaultReload(AK47_MAX_CLIP, NULL, 1);

		strcpy(m_pPlayer->m_szAnimExtention, "rifle");
	}

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 2;
	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 2;
}


void CUMP::PrimaryAttack(void)
{
	if (m_iWeaponState & WPNSTATE_M4A1_SILENCED)
	{

			AK47Fire((0.025) * m_flAccuracy, 0.0955, FALSE);
	}
	else
	{
			AK47Fire((0.02) * m_flAccuracy, 0.0955, FALSE);
	}


if (m_iWeaponState & WPNSTATE_M4A1_SILENCED)
{

if (m_iClip > 0)
{
SendWeaponAnim(mp5k_SHOOT1, 0);
}
else if (m_iClip = 0)
{
SendWeaponAnim(mp5k_IDLE, 0);
}

}
else
{

if (m_iClip > 0)
{
SendWeaponAnim(mp5k_UNSIL_SHOOT1, 0);
}
else if (m_iClip = 0)
{
SendWeaponAnim(mp5k_UNSIL_IDLE, 0);
}

}

}

cvar_t *weapon_damage_ump = NULL;

float CUMP::DamageOptionUMP() const
{
    float flDamage;

#ifndef CLIENT_DLL
    flDamage = (float)CVAR_GET_FLOAT("weapon_damage_ump");
#endif

    return flDamage;
}

void CUMP::AK47Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	m_bDelayFire = true;
	m_iShotsFired++;
	m_flAccuracy = ((float)(m_iShotsFired * m_iShotsFired * m_iShotsFired) / 220) + 0.3;

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
#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;

	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecDir;

//Vector vecSrc = m_pPlayer->GetGunPosition();
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/ump45-1.wav", VOL_NORM, ATTN_NORM);

	if (m_iWeaponState & WPNSTATE_M4A1_SILENCED)
	{
		vecDir = m_pPlayer->FireBullets3(vecSrc, gpGlobals->v_forward, flSpread, 8192, 2, BULLET_PLAYER_762MM, 20, 0.97, m_pPlayer->pev, FALSE, m_pPlayer->random_seed);
		m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
	}
	else
	{
		vecDir = m_pPlayer->FireBullets3(vecSrc, gpGlobals->v_forward, flSpread, 8192, 2, BULLET_PLAYER_762MM, 20, 0.97, m_pPlayer->pev, FALSE, m_pPlayer->random_seed);
		m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
	}

	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usFireAK47, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), (m_iWeaponState & WPNSTATE_M4A1_SILENCED) ? true : false, FALSE);
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;
#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.5;

	m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomFloat(m_pPlayer->random_seed + 4, 1.5, 1.75) + m_pPlayer->pev->punchangle.x * 0.25;
	m_pPlayer->pev->punchangle.y += UTIL_SharedRandomFloat(m_pPlayer->random_seed + 5, -1.0, 1.0);
}

void CUMP::Reload(void)
{
	if (m_pPlayer->ammo_762nato <= 0)
		return;
if (m_iClip == AK47_MAX_CLIP)
return;

	int iAnim;

	if (m_iWeaponState & WPNSTATE_M4A1_SILENCED)
{
		
if (DefaultReload(AK47_MAX_CLIP, mp5k_RELOAD, 2.5))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		m_flAccuracy = 0.2;
		m_iShotsFired = 0;
		m_bDelayFire = false;
	}
}
	else
{
		
if (DefaultReload(AK47_MAX_CLIP, mp5k_UNSIL_RELOAD, 2.5))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		m_flAccuracy = 0.2;
		m_iShotsFired = 0;
		m_bDelayFire = false;
	}
}

	
}


void CUMP::QuickReload()
{
	if (m_pPlayer->ammo_762nato <= 0)
		return;
if (m_iClip == AK47_MAX_CLIP)
return;

	int iAnim;

	if (m_iWeaponState & WPNSTATE_M4A1_SILENCED)
{
		
if (DefaultReloadQuick(AK47_MAX_CLIP, ANIM9, 1.5))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		m_flAccuracy = 0.2;
		m_iShotsFired = 0;
		m_bDelayFire = false;
	}
}
	else
{
		
if (DefaultReloadQuick(AK47_MAX_CLIP, ANIM10, 1.5))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		m_flAccuracy = 0.2;
		m_iShotsFired = 0;
		m_bDelayFire = false;
	}
}

	
}

void CUMP::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;

	if (m_iWeaponState & WPNSTATE_M4A1_SILENCED)
		SendWeaponAnim(mp5k_IDLE, UseDecrement() != FALSE);
	else
		SendWeaponAnim(mp5k_UNSIL_IDLE, UseDecrement() != FALSE);
}
