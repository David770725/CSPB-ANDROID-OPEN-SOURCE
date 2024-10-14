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
#include "wpn_glock18.h"

#ifdef CLIENT_DLL
extern bool g_bGlockBurstMode;
#endif

enum glock18_e
{
	GLOCK18_IDLE,
	GLOCK18_SHOOT,
	GLOCK18_SHOOT2,
	GLOCK18_SHOOT3,
GLOCK18_RELOAD,
GLOCK18_DRAW,
	GLOCK18_IDLE2,
GLOCK18_IDLE3,
GLOCK18_IDLE4,
	GLOCK18_RELOAD2,
	RUN, 
DAMAGE, 
JUMP,
};

enum glock18_shield_e
{
	GLOCK18_SHIELD_IDLE1,
	GLOCK18_SHIELD_SHOOT,
	GLOCK18_SHIELD_SHOOT2,
	GLOCK18_SHIELD_SHOOT_EMPTY,
	GLOCK18_SHIELD_RELOAD,
	GLOCK18_SHIELD_DRAW,
	GLOCK18_SHIELD_IDLE,
	GLOCK18_SHIELD_UP,
	GLOCK18_SHIELD_DOWN
};

LINK_ENTITY_TO_CLASS(weapon_glock18, CGLOCK18)

void CGLOCK18::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_glock18");

	Precache();
	m_iId = WEAPON_GLOCK18;
	SET_MODEL(ENT(pev), "models/w_glock18.mdl");

	m_bBurstFire = 0;
	m_iGlock18ShotsFired = 0;
	m_flGlock18Shoot = 0;
	m_iDefaultAmmo = GLOCK18_DEFAULT_GIVE;
	m_flAccuracy = 0.9;
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

	FallInit();
}

void CGLOCK18::Precache(void)
{
	
PRECACHE_MODEL("models/billflx/v_glock_18.mdl");

	PRECACHE_MODEL("models/p_glock_18.mdl");
	

	PRECACHE_SOUND("weapons/glock18-1.wav");
	PRECACHE_SOUND("weapons/glock18-2.wav");
	PRECACHE_SOUND("weapons/clipout1.wav");
	PRECACHE_SOUND("weapons/clipin1.wav");
	PRECACHE_SOUND("weapons/sliderelease1.wav");
	PRECACHE_SOUND("weapons/slideback1.wav");
	PRECACHE_SOUND("weapons/357_cock1.wav");
	PRECACHE_SOUND("weapons/de_clipin.wav");
	PRECACHE_SOUND("weapons/de_clipout.wav");

	m_iShellId = m_iShell = PRECACHE_MODEL("models/pshell.mdl");
	m_usFireGlock18 = PRECACHE_EVENT(1, "events/glock18.sc");
}


int CGLOCK18::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "9mm";
	p->iMaxAmmo1 = MAX_AMMO_9MM;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = GLOCK18_MAX_CLIP;
	p->iSlot = 1;
	p->iPosition = 2;
	p->iId = WEAPON_GLOCK18;
	p->iFlags = 0;
	p->iWeight = GLOCK18_WEIGHT;

	return 1;
}


BOOL CGLOCK18::Deploy(void)
{

m_bBurstFire = 0;
	m_iGlock18ShotsFired = 0;
	m_flGlock18Shoot = 0;
	m_flAccuracy = 0.9;
	m_fMaxSpeed = 250;
	
		return DefaultDeploy("models/billflx/v_glock_18.mdl", "models/p_glock_18.mdl", GLOCK18_DRAW, "onehanded", 0);

}


void CGLOCK18::QuickDeploy()
{
SendWeaponAnim(RUN, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CGLOCK18::SecondaryAttack(void)
{
	
}

void CGLOCK18::PrimaryAttack(void)
{

		GLOCK18Fire((0.0), 0.0955, FALSE);

}

void CGLOCK18::GLOCK18Fire(float flSpread, float flCycleTime, BOOL fUseBurstMode)
{
	
m_bDelayFire = true;
	m_iShotsFired++;
	m_flAccuracy = ((float)(m_iShotsFired * m_iShotsFired * m_iShotsFired) / 200.0) + 0.35;

	if (m_flAccuracy > 1.25)
		m_flAccuracy = 1.25;

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
	Vector vecDir = m_pPlayer->FireBullets3(vecSrc, gpGlobals->v_forward, flSpread, 8192, 2, BULLET_PLAYER_9MM, 20, 0.98, m_pPlayer->pev, FALSE, m_pPlayer->random_seed);

//Vector vecSrc = m_pPlayer->GetGunPosition();
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/glock18-1.wav", VOL_NORM, ATTN_NORM);

if (m_iClip > 0)
{
SendWeaponAnim(GLOCK18_SHOOT, 0);
}
else if (m_iClip == 0)
{
SendWeaponAnim(GLOCK18_IDLE, 0);
}



	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usFireGlock18, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), FALSE, FALSE);

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

void CGLOCK18::Reload(void)
{
	if (m_pPlayer->ammo_9mm <= 0)
		return;
if (m_iClip == GLOCK18_MAX_CLIP)
return;

	if (DefaultReload(GLOCK18_MAX_CLIP, NULL, 2.2))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		m_flAccuracy = 0.9;

	}
SendWeaponAnim(GLOCK18_RELOAD, 0);

}

void CGLOCK18::QuickReload()
{
	if (m_pPlayer->ammo_9mm <= 0)
		return;
if (m_iClip == GLOCK18_MAX_CLIP)
return;

	if (DefaultReloadQuick(GLOCK18_MAX_CLIP, NULL, 1.2))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		m_flAccuracy = 0.9;

	}
SendWeaponAnim(DAMAGE, 0);

}

void CGLOCK18::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;
	{
		if (m_pPlayer->pev->button & IN_JUMP)
		{
			//if ()
			{
				SendWeaponAnim(JUMP, UseDecrement() != FALSE); 
			
				//m_flTimeWeaponIdle = gpGlobals->time;
				m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.75;
				return;
			}
			//else if (m_flNextRunIdle <= gpGlobals->time)
			{
				//SendWeaponAnim(ANIM_RUN_IDLE, UseDecrement() != FALSE);
				//m_flTimeWeaponIdle = gpGlobals->time + 0.57;
			}
			//m_flTimeWeaponIdle = gpGlobals->time;
		}
		//else
		{
			//if ()
			{
				//SendWeaponAnim(ANIM_RUN_END, UseDecrement() != FALSE);
			
				//m_flTimeWeaponIdle = gpGlobals->time;
				//m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.60;
				//return;
			}
			//else if( m_flNextRunEnd<= gpGlobals->time)
			{
				SendWeaponAnim(GLOCK18_IDLE, UseDecrement() != FALSE);
				//m_flTimeWeaponIdle = gpGlobals->time + 0.60;
			}
			//m_flNextRunIdle = gpGlobals->time;
		}
	}
}

	void CGLOCK18::ResetRunIdle()
{
	//pev->iuser2 = 1;
	m_flTimeWeaponIdle = gpGlobals->time;
}
