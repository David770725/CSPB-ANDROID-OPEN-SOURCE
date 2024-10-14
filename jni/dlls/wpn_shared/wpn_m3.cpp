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
#include "wpn_m3.h"

enum m3_e
{
	M3_IDLE,
	M3_FIRE1,
	M3_FIRE2,
	M3_RELOAD,
	M3_PUMP,
	M3_START_RELOAD,
	M3_DRAW,
	M3_HOLSTER,
ANIM1
};



LINK_ENTITY_TO_CLASS(weapon_m3, CM3)

void CM3::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_m3");

	Precache();
	m_iId = WEAPON_M3;
	SET_MODEL(ENT(pev), "models/w_870mcs.mdl");
	m_iDefaultAmmo = M3_DEFAULT_GIVE;

	FallInit();
}

void CM3::Precache(void)
{
	//ct

//PRECACHE_MODEL("models/billflx/v_870mcs.mdl");

PRECACHE_MODEL("models/billflx/v_870mcs.mdl");


	PRECACHE_MODEL("models/p_870mcs.mdl");

	m_iShellId = m_iShell = PRECACHE_MODEL("models/shotgunshell.mdl");

	PRECACHE_SOUND("weapons/870mcs-1.wav");
	PRECACHE_SOUND("weapons/m3_insertshell.wav");
	PRECACHE_SOUND("weapons/m3_pump.wav");
	PRECACHE_SOUND("weapons/reload1.wav");
	PRECACHE_SOUND("weapons/reload3.wav");

	m_usFireM3 = PRECACHE_EVENT(1, "events/m3.sc");
}

int CM3::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "buckshot";
	p->iMaxAmmo1 = MAX_AMMO_BUCKSHOT;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = M3_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 5;
	p->iId = WEAPON_M3;
	p->iFlags = 0;
	p->iWeight = M3_WEIGHT;

	return 1;
}

BOOL CM3::Deploy(void)
{

m_fInSpecialReload = 0;

if (DefaultDeploy("models/billflx/v_870mcs.mdl", "models/p_870mcs.mdl", M3_DRAW, "shotgun", 0)) 
{
	m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.6;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.6;

	return TRUE;
}
	return FALSE;

}

void CM3::QuickDeploy()
{
SendWeaponAnim(M3_HOLSTER, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CM3::PrimaryAttack(void)
{
	if (m_pPlayer->pev->waterlevel == 3)
	{
		PlayEmptySound();
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.5;
		return;
	}

	if (m_iClip <= 0)
	{
		Reload();

		if (m_iClip == 0)
			PlayEmptySound();

		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.5;
		return;
	}

SendWeaponAnim(M3_FIRE1, 0);


EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/870mcs-1.wav", VOL_NORM, ATTN_NORM);


	m_pPlayer->m_iWeaponVolume = LOUD_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;

	m_iClip--;
	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
#ifndef CLIENT_DLL
	m_pPlayer->FireBullets(30, m_pPlayer->GetGunPosition(), gpGlobals->v_forward, Vector(0.0675, 0.0675, 0), 1000, BULLET_PLAYER_BUCKSHOT, 0);
#endif

	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, ENT(m_pPlayer->pev), m_usFireM3, 0, (float *)&g_vecZero, (float *)&g_vecZero, 0, 0, 0, 0, FALSE, FALSE);

	if (m_iClip)
		m_flPumpTime = UTIL_WeaponTimeBase() + 1.5;

#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	if (m_iClip)
		m_flPumpTime = UTIL_WeaponTimeBase() + 1.5;

	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.5;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.5;

	if (m_iClip)
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2.5;
	else
		m_flTimeWeaponIdle = 0.875;

	m_fInSpecialReload = 0;
QuickReload_enable = FALSE;

	if (m_pPlayer->pev->flags & FL_ONGROUND)
		m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomLong(m_pPlayer->random_seed + 1, 2, 2);

	else
		m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomLong(m_pPlayer->random_seed + 1, 2, 2);

	m_pPlayer->m_flEjectBrass = gpGlobals->time + 0.45;
}


void CM3::DefaultReloadCall (void)
{
CLIENT_COMMAND(m_pPlayer->edict(), "QuickReload_client\n");
}


void CM3::Reload(void)
{
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0 || m_iClip == M3_MAX_CLIP)
		return;
if (m_iClip == M3_MAX_CLIP)
return;
	if (m_flNextPrimaryAttack > UTIL_WeaponTimeBase())
		return;

SetThink(&CM3::DefaultReloadCall);
pev->nextthink = gpGlobals->time + 0.01;

	if (!m_fInSpecialReload)
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		SendWeaponAnim(M3_START_RELOAD, UseDecrement() != FALSE);

		m_fInSpecialReload = 1;
		m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.5;
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.5;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5;
	}
	else if (m_fInSpecialReload == 1)
	{
		if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
			return;

		m_fInSpecialReload = 2;

if (QuickReload_enable)
{
		m_flNextReload = UTIL_WeaponTimeBase() + 0.35;
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.35;
		SendWeaponAnim(ANIM1, UseDecrement() != FALSE);

}
else
{
		m_flNextReload = UTIL_WeaponTimeBase() + 0.5;
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.5;
		SendWeaponAnim(M3_RELOAD, UseDecrement() != FALSE);
}

	}
	else
	{
		m_iClip++;
		#ifndef CLIENT_DLL
if (sv_unlimited_reserve_ammo.value == 1)
{

}
else
{
		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]--;
}
#endif
		m_fInSpecialReload = 1;
		m_pPlayer->ammo_buckshot--;
	}
}


void CM3::QuickReload()
{
	QuickReload_enable = TRUE;
}



void CM3::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_5DEGREES);

	if (m_flPumpTime && m_flPumpTime < UTIL_WeaponTimeBase())
		m_flPumpTime = 0;

	if (m_flTimeWeaponIdle < UTIL_WeaponTimeBase())
	{
		if (m_iClip == 0 && m_fInSpecialReload == 0 && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
		{
			Reload();
		}
		else if (m_fInSpecialReload != 0)
		{
			if (m_iClip != M3_MAX_CLIP && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
			{
				Reload();
			}
			else
			{
				SendWeaponAnim(M3_PUMP, UseDecrement() != FALSE);

				m_fInSpecialReload = 0;
				m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.5;
			}
		}
		else
			SendWeaponAnim(M3_IDLE, UseDecrement() != FALSE);
	}
}
