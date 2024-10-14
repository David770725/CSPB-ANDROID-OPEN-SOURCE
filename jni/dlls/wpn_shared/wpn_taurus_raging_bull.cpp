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
#include "wpn_taurus_raging_bull.h"

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
ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5
	
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

LINK_ENTITY_TO_CLASS(weapon_taurus_raging_bull, CTaurus_raging_bull)

void CTaurus_raging_bull::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_taurus_raging_bull");

	Precache();
	m_iId = WEAPON_DEAGLE;
	SET_MODEL(ENT(pev), "models/w_p228.mdl");

	m_iDefaultAmmo = P228_DEFAULT_GIVE;
	m_flAccuracy = 0.9;
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

	FallInit();
}

void CTaurus_raging_bull::Precache(void)
{
	
PRECACHE_MODEL("models/billflx/v_taurus_raging_bull.mdl");

	PRECACHE_MODEL("models/p_taurus_raging_bull.mdl");
#ifdef ENABLE_SHIELD
	PRECACHE_MODEL("models/shield/v_shield_p228.mdl");
#endif

	PRECACHE_SOUND("weapons/taurus_raging_bull-1.wav");
	PRECACHE_SOUND("weapons/p228_clipout.wav");
	PRECACHE_SOUND("weapons/p228_clipin.wav");
	PRECACHE_SOUND("weapons/p228_sliderelease.wav");
	PRECACHE_SOUND("weapons/p228_slidepull.wav");
PRECACHE_SOUND("weapons/zoom_sniper_in.wav");
PRECACHE_SOUND("weapons/zoom_sniper_out.wav");


	m_iShell = PRECACHE_MODEL("models/pshell.mdl");
	m_usFireTaurus_raging_bull = PRECACHE_EVENT(1, "events/taurus_raging_bull.sc");
}

int CTaurus_raging_bull::GetItemInfo(ItemInfo *p)
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


BOOL CTaurus_raging_bull::Deploy(void)
{

	m_flAccuracy = 0.9;
	m_fMaxSpeed = 250;
	
//return DefaultDeploy("models/billflx/v_taurus_raging_bull.mdl", "models/p_taurus_raging_bull.mdl", P228_DRAW, "onehanded", 0);

if (DefaultDeploy("models/billflx/v_taurus_raging_bull.mdl", "models/p_taurus_raging_bull.mdl", P228_DRAW, "onehanded", 0))

{
	m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.8;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.8;
	
	return TRUE;
	}
	return FALSE;

}

void CTaurus_raging_bull::QuickDeploy()
{
SendWeaponAnim(ANIM1, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CTaurus_raging_bull::PrimaryAttack(void)
{
	if (!FBitSet(m_pPlayer->pev->flags, FL_ONGROUND))
		Taurus_raging_bullFire((1.0) * (1 - m_flAccuracy), 1, FALSE);
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
		Taurus_raging_bullFire((0.0) * (1 - m_flAccuracy), 1, FALSE);
	else if (FBitSet(m_pPlayer->pev->flags, FL_DUCKING))
		Taurus_raging_bullFire((0.0) * (1 - m_flAccuracy), 1, FALSE);
	else
		Taurus_raging_bullFire((0.0) * (1 - m_flAccuracy), 1, FALSE);





}

void CTaurus_raging_bull::SecondaryAttack(void)
{
	/*switch (m_pPlayer->m_iFOV)
	{
		case 90: m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 30; break;
		//case 40: m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 10; break;
		default: m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90; break;
	}

	m_pPlayer->ResetMaxSpeed();
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom.wav", 0.2, 2.4);
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}*/
switch (m_pPlayer->m_iFOV)
	{
		case 90: 

SetThink(&CTaurus_raging_bull::Fov2);
	pev->nextthink = gpGlobals->time + 0.0000009;
break;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.1;

		default: 
SetThink(&CTaurus_raging_bull::offFov2);
	pev->nextthink = gpGlobals->time + 0.0000009;
break;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.1;
	}

	m_pPlayer->ResetMaxSpeed();
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.1;

}

void CTaurus_raging_bull::Fov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 80; 

SetThink(&CTaurus_raging_bull::Fov3);
	pev->nextthink = gpGlobals->time + 0.0000009;
CLIENT_COMMAND(m_pPlayer->edict(), "sniper_scope\n");
m_pPlayer->pev->viewmodel = MAKE_STRING("models/sight/v_muzzle_bottom.mdl");

}

void CTaurus_raging_bull::Fov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CTaurus_raging_bull::Fov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
m_pPlayer->pev->viewmodel = MAKE_STRING("models/sight/v_muzzle_bottom.mdl");
}

void CTaurus_raging_bull::Fov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 50; 

SetThink(&CTaurus_raging_bull::Fov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
m_pPlayer->pev->viewmodel = MAKE_STRING("models/sight/v_muzzle_bottom.mdl");
}

void CTaurus_raging_bull::Fov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 40;
	
	m_pPlayer->ResetMaxSpeed();
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_sniper_in.wav", 0.2, 2.4);
m_pPlayer->pev->viewmodel = MAKE_STRING("models/sight/v_muzzle_bottom.mdl");
}

void CTaurus_raging_bull::Fov6(void)
{
	
;
}

void CTaurus_raging_bull::Fov7(void)
{
	
;
}

//offfov

void CTaurus_raging_bull::offFov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 40; 

SetThink(&CTaurus_raging_bull::offFov3);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CTaurus_raging_bull::offFov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 50; 

SetThink(&CTaurus_raging_bull::offFov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CTaurus_raging_bull::offFov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 60; 

SetThink(&CTaurus_raging_bull::offFov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CTaurus_raging_bull::offFov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CTaurus_raging_bull::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CTaurus_raging_bull::offFov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90;
	
	m_pPlayer->ResetMaxSpeed();
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_sniper_out.wav", 0.2, 2.4);

m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/v_taurus_raging_bull.mdl");

}

void CTaurus_raging_bull::offFov7(void)
{
	
;
}


void CTaurus_raging_bull::Taurus_raging_bullFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
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
	Vector vecDir = m_pPlayer->FireBullets3(vecSrc, gpGlobals->v_forward, flSpread, 4096, 1, BULLET_PLAYER_357SIG, 80, 0.8, m_pPlayer->pev, TRUE, m_pPlayer->random_seed);

//Vector vecSrc = m_pPlayer->GetGunPosition();
UTIL_MakeVectors(m_pPlayer->pev->v_angle);
	

SendWeaponAnim(P228_SHOOT1, 0);
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/taurus_raging_bull-1.wav", VOL_NORM, ATTN_NORM);
	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(),m_usFireTaurus_raging_bull, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), m_iClip != 0, FALSE);
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;
#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;
	ResetPlayerShieldAnim();
	m_pPlayer->pev->punchangle.x -= 2;
}

void CTaurus_raging_bull::Reload(void)
{
	if (m_pPlayer->ammo_357sig <= 0)
		return;
if (m_iClip == P228_MAX_CLIP)
return;
	int iAnim;

	if (m_pPlayer->HasShield() != false)
		iAnim = P228_SHIELD_RELOAD;
	else
		iAnim = P228_RELOAD;

	if (DefaultReload(P228_MAX_CLIP, NULL, 2.7))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif


			//m_pPlayer->pev->fov = m_pPlayer->m_iFOV = 10;
			SetThink(&CTaurus_raging_bull::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
		m_flAccuracy = 0.9;


}
SendWeaponAnim(P228_RELOAD,  0);
	
}


void CTaurus_raging_bull::QuickReload()
{
	if (m_pPlayer->ammo_357sig <= 0)
		return;
if (m_iClip == P228_MAX_CLIP)
return;
	int iAnim;

	if (m_pPlayer->HasShield() != false)
		iAnim = P228_SHIELD_RELOAD;
	else
		iAnim = P228_RELOAD;

	if (DefaultReloadQuick(P228_MAX_CLIP, NULL, 1.7))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif

			//m_pPlayer->pev->fov = m_pPlayer->m_iFOV = 10;
			SetThink(&CTaurus_raging_bull::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
		m_flAccuracy = 0.9;


}
SendWeaponAnim(ANIM2,  0);
	
}

void CTaurus_raging_bull::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	if (m_pPlayer->HasShield())
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;

		if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
			SendWeaponAnim(P228_SHIELD_IDLE_UP, UseDecrement() != FALSE);

		return;
	}

	if (m_iClip)
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 3.0625;
		SendWeaponAnim(P228_IDLE, 0);
	}
}
