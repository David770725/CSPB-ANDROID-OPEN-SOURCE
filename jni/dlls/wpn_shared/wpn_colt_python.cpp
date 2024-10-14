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
#include "wpn_colt_python.h"

enum p228_e
{
	P228_IDLE,
	P228_SHOOT1,
	P228_SHOOT2,
	P228_SHOOT3,
P228_RELOAD, 
P228_DRAW, 
P228_IDLE2,
P228_IDLE3,
P228_IDLE4,
P228_RELOAD2, 
	P228_SHOOT_EMPTY,
ANIM1
	
};

enum p228_shield_e
{
	P228_SHIELD_IDLE,
	P228_SHIELD_SHOOT1,
	P228_SHIELD_SHOOT2,
	P228_SHIELD_SHOOT_EMPTY,
	P228_SHIELD_RELOAD,
	P228_SHIELD_DRAW,
	P228_SHIELD_IDLE_UP,
	P228_SHIELD_UP,
	P228_SHIELD_DOWN
};

LINK_ENTITY_TO_CLASS(weapon_colt_python, CColt_python)

void CColt_python::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_colt_python");

	Precache();
	m_iId = WEAPON_DEAGLE;
	SET_MODEL(ENT(pev), "models/w_p228.mdl");

	m_iDefaultAmmo = P228_DEFAULT_GIVE;
	m_flAccuracy = 0.9;
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

	FallInit();
}

void CColt_python::Precache(void)
{
	PRECACHE_MODEL("models/billflx/v_colt_python.mdl");

	PRECACHE_MODEL("models/p_colt_python.mdl");
#ifdef ENABLE_SHIELD
	PRECACHE_MODEL("models/shield/v_shield_p228.mdl");
#endif

	PRECACHE_SOUND("weapons/colt_python-1.wav");
	PRECACHE_SOUND("weapons/p228_clipout.wav");
	PRECACHE_SOUND("weapons/p228_clipin.wav");
	PRECACHE_SOUND("weapons/p228_sliderelease.wav");
	PRECACHE_SOUND("weapons/p228_slidepull.wav");
PRECACHE_SOUND("weapons/zoom_sniper_in.wav");
PRECACHE_SOUND("weapons/zoom_sniper_out.wav");


	m_iShell = PRECACHE_MODEL("models/pshell.mdl");
	m_usFireColtPython = PRECACHE_EVENT(1, "events/usp.sc");
}

int CColt_python::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "357SIG";
	p->iMaxAmmo1 = MAX_AMMO_357SIG;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = P228_MAX_CLIP;
	p->iSlot = 1;
	p->iPosition = 3;
	p->iId = WEAPON_DEAGLE;
	p->iFlags = 0;
	p->iWeight = DEAGLE_WEIGHT;

	return 1;
}

BOOL CColt_python::Deploy(void)
{


   m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
   m_flAccuracy = 0.92f;
   m_fMaxSpeed = 250.0f;
   m_pPlayer->m_bShieldDrawn = false;


if (DefaultDeploy("models/billflx/v_colt_python.mdl", "models/p_colt_python.mdl", P228_DRAW, "onehanded", 0))

{
	m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.6;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.2;
	
	return TRUE;
	}
	return FALSE;

}

void CColt_python::QuickDeploy()
{
SendWeaponAnim(P228_SHOOT_EMPTY, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CColt_python::PrimaryAttack(void)
{
	if (!FBitSet(m_pPlayer->pev->flags, FL_ONGROUND))
		Taurus_raging_bullFire((1.0) * (1 - m_flAccuracy), 0.3, FALSE);
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
		Taurus_raging_bullFire((0.0) * (1 - m_flAccuracy), 0.3, FALSE);
	else if (FBitSet(m_pPlayer->pev->flags, FL_DUCKING))
		Taurus_raging_bullFire((0.0) * (1 - m_flAccuracy), 0.3, FALSE);
	else
		Taurus_raging_bullFire((0.0) * (1 - m_flAccuracy), 0.3, FALSE);




}

void CColt_python::Taurus_raging_bullFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	flCycleTime -= 0.05;
	m_iShotsFired++;

	if (m_iShotsFired > 1)
		return;

	if (m_flLastFire)
	{
		m_flAccuracy -= (0.325 - (gpGlobals->time - m_flLastFire)) * 0.3;

		if (m_flAccuracy > 0.9)
			m_flAccuracy = 0.9;
		else if (m_flAccuracy < 0.6)
			m_flAccuracy = 0.6;
	}

	m_flLastFire = gpGlobals->time;

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
	SetPlayerShieldAnim();
#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif
	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	m_pPlayer->m_iWeaponVolume = BIG_EXPLOSION_VOLUME;
	m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;

	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecDir = m_pPlayer->FireBullets3(vecSrc, gpGlobals->v_forward, flSpread, 4096, 1, BULLET_PLAYER_357SIG, 75, 0.8, m_pPlayer->pev, TRUE, m_pPlayer->random_seed);

EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/colt_python-1.wav", VOL_NORM, ATTN_NORM);
SendWeaponAnim(P228_SHOOT1, 0);

	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(),m_usFireColtPython, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), m_iClip != 0, FALSE);
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;
#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;
	ResetPlayerShieldAnim();
	m_pPlayer->pev->punchangle.x -= 2;
}

void CColt_python::Reload(void)
{
	if (m_pPlayer->ammo_357sig <= 0)
		return;

if (m_iClip == P228_MAX_CLIP)
return;

	if (DefaultReload(P228_MAX_CLIP, NULL, 2.3))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif

}
SendWeaponAnim(P228_RELOAD, 0);
}

void CColt_python::QuickReload()
{
	if (m_pPlayer->ammo_357sig <= 0)
		return;

if (m_iClip == P228_MAX_CLIP)
return;

	if (DefaultReloadQuick(P228_MAX_CLIP, NULL, 1.3))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif

}
SendWeaponAnim(ANIM1, 0);
}

void CColt_python::WeaponIdle(void)
{
	

ResetEmptySound();

	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	if (m_iClip)
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 60;
		SendWeaponAnim(P228_IDLE, UseDecrement() != FALSE);
	}

}
