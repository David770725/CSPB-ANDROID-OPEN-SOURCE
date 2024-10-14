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
#include "wpn_dual_handgun.h"

enum elite_e
{
	ELITE_IDLE,
	ELITE_IDLE_LEFTEMPTY,
	ELITE_SHOOTLEFT1,
	ELITE_SHOOTLEFT2,
	ELITE_SHOOTLEFT3,
	ELITE_SHOOTLEFT4,
	ELITE_SHOOTLEFT5,
	ELITE_SHOOTLEFTLAST,
	ELITE_SHOOTRIGHT1,
	ELITE_SHOOTRIGHT2,
	ELITE_SHOOTRIGHT3,
	ELITE_SHOOTRIGHT4,
	ELITE_SHOOTRIGHT5,
	ELITE_SHOOTRIGHTLAST,
	ELITE_RELOAD,
	ELITE_DRAW,
ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5
};

LINK_ENTITY_TO_CLASS(weapon_dual_handgun, CDual_handgun)

void CDual_handgun::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_dual_handgun");

	Precache();
	m_iId = WEAPON_ELITE;
	SET_MODEL(ENT(pev), "models/w_elite.mdl");

	m_iDefaultAmmo = ELITE_DEFAULT_GIVE;
	m_flAccuracy = 0.88;

	FallInit();
}

void CDual_handgun::Precache(void)
{

PRECACHE_MODEL("models/billflx/v_dual_handgun.mdl");

	PRECACHE_MODEL("models/p_elite.mdl");

	PRECACHE_SOUND("weapons/dual_handgun-1.wav");
	PRECACHE_SOUND("weapons/elite_reloadstart.wav");
	PRECACHE_SOUND("weapons/elite_leftclipin.wav");
	PRECACHE_SOUND("weapons/elite_clipout.wav");
	PRECACHE_SOUND("weapons/elite_sliderelease.wav");
	PRECACHE_SOUND("weapons/elite_rightclipin.wav");
	PRECACHE_SOUND("weapons/elite_deploy.wav");

	m_iShell = PRECACHE_MODEL("models/pshell.mdl");






	m_usFireDHANDGUN_LEFT = PRECACHE_EVENT(1, "events/elite_left.sc");
	m_usFireDHANDGUN_RIGHT = PRECACHE_EVENT(1, "events/elite_right.sc");
}

int CDual_handgun::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "9mm";
	p->iMaxAmmo1 = MAX_AMMO_9MM;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = ELITE_MAX_CLIP;
	p->iSlot = 1;
	p->iPosition = 5;
	p->iId = WEAPON_ELITE;
	p->iFlags = 0;
	p->iWeight = ELITE_WEIGHT;

	return 1;
}


BOOL CDual_handgun::Deploy(void)
{
SetThink(&CDual_handgun::WeaponName);
	pev->nextthink = gpGlobals->time + 0.01;
	m_flAccuracy = 0.88;

	if (!(m_iClip & 1))
		m_iWeaponState |= WPNSTATE_ELITE_LEFT;

return DefaultDeploy("models/billflx/v_dual_handgun.mdl", "models/p_elite.mdl", ELITE_DRAW, "dualpistols", 0);
}


void CDual_handgun::QuickDeploy()
{
SendWeaponAnim(ANIM1, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CDual_handgun::PrimaryAttack(void)
{
	if (!FBitSet(m_pPlayer->pev->flags, FL_ONGROUND))
		DhandgunFire((0.1) * (1 - m_flAccuracy), 0.2, FALSE);
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
		DhandgunFire((0.0) * (1 - m_flAccuracy), 0.2, FALSE);
	else if (FBitSet(m_pPlayer->pev->flags, FL_DUCKING))
		DhandgunFire((0.0) * (1 - m_flAccuracy), 0.2, FALSE);
	else
		DhandgunFire((0.0) * (1 - m_flAccuracy), 0.2, FALSE);


if (m_iWeaponState & WPNSTATE_ELITE_LEFT)
{

if (m_iClip > 0)
{
SendWeaponAnim(ELITE_SHOOTLEFT1, 0);
}
else if (m_iClip == 0)
{
SendWeaponAnim(ELITE_IDLE_LEFTEMPTY, 0);
}

}

else
{

if (m_iClip > 0)
{
SendWeaponAnim(ELITE_SHOOTRIGHT1, 0);
}
else if (m_iClip == 0)
{
SendWeaponAnim(ELITE_SHOOTRIGHTLAST, 0);
}

}

}

void CDual_handgun::DhandgunFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	flCycleTime -= 0.125;
	m_iShotsFired++;

	if (m_iShotsFired > 1)
		return;

	if (m_flLastFire)
	{
		m_flAccuracy -= (0.325 - (gpGlobals->time - m_flLastFire)) * 0.275;

		if (m_flAccuracy > 0.88)
			m_flAccuracy = 0.88;
		else if (m_flAccuracy < 0.55)
			m_flAccuracy = 0.55;
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
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;
	m_pPlayer->m_iWeaponVolume = BIG_EXPLOSION_VOLUME;
	m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;

	Vector vecDir;
	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif


EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/dual_handgun-1.wav", VOL_NORM, ATTN_NORM);


	if (m_iWeaponState & WPNSTATE_ELITE_LEFT)
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif
		m_iWeaponState &= ~WPNSTATE_ELITE_LEFT;

		vecDir = FireBullets3(m_pPlayer->GetGunPosition() - gpGlobals->v_right * 5, gpGlobals->v_forward, flSpread, 8192, BULLET_PLAYER_9MM, 1, 36, 0.75, m_pPlayer->pev, TRUE, m_pPlayer->random_seed);
		PLAYBACK_EVENT_FULL(flags, ENT(m_pPlayer->pev), m_usFireDHANDGUN_LEFT, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.y * 100), m_iClip, FALSE, FALSE);
	}
	else
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_ATTACK2);
#endif
		m_iWeaponState |= WPNSTATE_ELITE_LEFT;

		vecDir = FireBullets3(m_pPlayer->GetGunPosition() - gpGlobals->v_right * 5, gpGlobals->v_forward, flSpread, 8192, BULLET_PLAYER_9MM, 1, 36, 0.75, m_pPlayer->pev, TRUE, m_pPlayer->random_seed);
		PLAYBACK_EVENT_FULL(flags, ENT(m_pPlayer->pev), m_usFireDHANDGUN_RIGHT, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.y * 100), m_iClip, FALSE, FALSE);
	}

#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;
	m_pPlayer->pev->punchangle.x -= 2;
}

void CDual_handgun::Reload(void)
{
	if (m_pPlayer->ammo_9mm <= 0)
		return;
if (m_iClip == ELITE_MAX_CLIP)
return;
	if (DefaultReload(ELITE_MAX_CLIP, NULL, 4.5))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		m_flAccuracy = 0.88;
SendWeaponAnim(ELITE_RELOAD, 0);
	}
}

void CDual_handgun::QuickReload()
{
	if (m_pPlayer->ammo_9mm <= 0)
		return;
if (m_iClip == ELITE_MAX_CLIP)
return;
	if (DefaultReloadQuick(ELITE_MAX_CLIP, NULL, 2.5))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		m_flAccuracy = 0.88;
SendWeaponAnim(ANIM2, 0);
	}
}

void CDual_handgun::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	if (m_iClip)
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 60;

		if (m_iClip == 1)
			SendWeaponAnim(ELITE_IDLE_LEFTEMPTY, UseDecrement() != FALSE);
		else
			SendWeaponAnim(ELITE_IDLE, UseDecrement() != FALSE);
	}
}
