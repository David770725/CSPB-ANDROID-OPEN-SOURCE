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
#include "wpn_k1.h"

enum mac10_e
{
	MAC10_IDLE1,
	MAC10_RELOAD,
	MAC10_DRAW,
	MAC10_SHOOT1,
	MAC10_SHOOT2,
	MAC10_SHOOT3,
ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5,
ANIM6
};

LINK_ENTITY_TO_CLASS(weapon_k1, CK1)

void CK1::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_k1");

	Precache();
	m_iId = WEAPON_MAC10;
	SET_MODEL(ENT(pev), "models/w_mac10.mdl");

	m_iDefaultAmmo = MAC10_DEFAULT_GIVE;
	m_flAccuracy = 0.15;
	m_bDelayFire = false;

	FallInit();
}

void CK1::Precache(void)
{
PRECACHE_MODEL("models/billflx/v_k1.mdl");

	PRECACHE_MODEL("models/p_k1.mdl");

	PRECACHE_SOUND("weapons/k1-1.wav");
	PRECACHE_SOUND("weapons/mac10_clipout.wav");
	PRECACHE_SOUND("weapons/mac10_clipin.wav");
	PRECACHE_SOUND("weapons/mac10_boltpull.wav");

	m_iShell = PRECACHE_MODEL("models/pshell.mdl");
	m_usFireK1 = PRECACHE_EVENT(1, "events/ak47.sc");
}

int CK1::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "556Nato";
	p->iMaxAmmo1 = MAX_AMMO_556NATO;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = MAC10_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 13;
	p->iId = WEAPON_MAC10;
	p->iFlags = 0;
	p->iWeight = MAC10_WEIGHT;

	return 1;
}

BOOL CK1::Deploy(void)
{
	m_flAccuracy = 0.15;
	iShellOn = 1;
	m_bDelayFire = false;


return DefaultDeploy("models/billflx/v_k1.mdl", "models/p_k1.mdl", MAC10_DRAW, "rifle", 0);

}


void CK1::QuickDeploy()
{
SendWeaponAnim(ANIM5, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CK1::PrimaryAttack(void)
{
		K1Fire((0.03) * m_flAccuracy, 0.07, FALSE);

}

void CK1::K1Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	m_bDelayFire = true;
	m_iShotsFired++;
	m_flAccuracy = ((m_iShotsFired * m_iShotsFired * m_iShotsFired) / 200.0) + 0.6;

	if (m_flAccuracy > 1.65)
		m_flAccuracy = 1.65;

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

	m_pPlayer->m_iWeaponVolume = NORMAL_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = DIM_GUN_FLASH;

	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecDir = m_pPlayer->FireBullets3(vecSrc, gpGlobals->v_forward, flSpread, 8192, 1, BULLET_PLAYER_45ACP, 17, 0.82, m_pPlayer->pev, FALSE, m_pPlayer->random_seed);

//Vector vecSrc = m_pPlayer->GetGunPosition();
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/k1-1.wav", VOL_NORM, ATTN_NORM);

if (m_iClip > 0)
{
SendWeaponAnim(MAC10_SHOOT1, 0);
}
else if (m_iClip == 0)
{
SendWeaponAnim(MAC10_IDLE1, 0);
}

	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usFireK1, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), FALSE, FALSE);
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;
#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;

	if (!FBitSet(m_pPlayer->pev->flags, FL_ONGROUND))
		KickBack(1.3, 0.55, 0.4, 0.05, 4.75, 3.75, 5);
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
		KickBack(0.9, 0.45, 0.25, 0.035, 3.5, 2.75, 7);
	else if (FBitSet(m_pPlayer->pev->flags, FL_DUCKING))
		KickBack(0.75, 0.4, 0.175, 0.03, 2.75, 2.5, 10);
	else
		KickBack(0.775, 0.425, 0.2, 0.03, 3.0, 2.75, 9);
}

void CK1::Reload(void)
{
	if (m_pPlayer->ammo_45acp <= 0)
		return;
if (m_iClip == MAC10_MAX_CLIP)
return;
	if (DefaultReload(MAC10_MAX_CLIP, NULL, 3))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		m_flAccuracy = 0;
		m_iShotsFired = 0;

	}
SendWeaponAnim(MAC10_RELOAD, 0);
}

void CK1::QuickReload()
{
	if (m_pPlayer->ammo_45acp <= 0)
		return;
if (m_iClip == MAC10_MAX_CLIP)
return;
	if (DefaultReloadQuick(MAC10_MAX_CLIP, NULL, 2))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		m_flAccuracy = 0;
		m_iShotsFired = 0;

	}
SendWeaponAnim(ANIM6, 0);
}


void CK1::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
	SendWeaponAnim(MAC10_IDLE1, UseDecrement() != FALSE);
}
