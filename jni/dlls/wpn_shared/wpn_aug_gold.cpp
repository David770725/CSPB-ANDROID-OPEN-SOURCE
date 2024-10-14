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
#include "wpn_aug_gold.h"

enum augg_e
{
	TAR21_IDLE1,
	TAR21_RELOAD,
	TAR21_DRAW,
	TAR21_SHOOT1,
	TAR21_SHOOT2,
	TAR21_SHOOT3, 
OFF
};

LINK_ENTITY_TO_CLASS(weapon_auggold, CAUGG)

const int AUGG_MAX_CLIP = 30;

void CAUGG::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_auggold");

	Precache();
	m_iId = WEAPON_AUG;
	SET_MODEL(ENT(pev), "models/w_aug_gold.mdl");

	m_iDefaultAmmo = AUGG_MAX_CLIP;
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;

	FallInit();
}

void CAUGG::Precache(void)
{
	PRECACHE_MODEL("models/billflx/classred1/v_aug_gold.mdl");
PRECACHE_MODEL("models/billflx/classred2/v_aug_gold.mdl");
PRECACHE_MODEL("models/billflx/classred3/v_aug_gold.mdl");
PRECACHE_MODEL("models/billflx/classred4/v_aug_gold.mdl");
PRECACHE_MODEL("models/billflx/classred5/v_aug_gold.mdl");
PRECACHE_MODEL("models/billflx/classblue1/v_aug_gold.mdl");
PRECACHE_MODEL("models/billflx/classblue2/v_aug_gold.mdl");
PRECACHE_MODEL("models/billflx/classblue3/v_aug_gold.mdl");
PRECACHE_MODEL("models/billflx/classblue4/v_aug_gold.mdl");
PRECACHE_MODEL("models/billflx/classblue5/v_aug_gold.mdl");


	PRECACHE_MODEL("models/p_aug_gold.mdl");
	
	PRECACHE_SOUND("weapons/tar21-1.wav");
	PRECACHE_SOUND("weapons/tar21_clipout.wav");
	PRECACHE_SOUND("weapons/tar21_clipin.wav");
	PRECACHE_SOUND("weapons/tar21_boltpull.wav");
PRECACHE_SOUND("weapons/zoom_generic_in.wav");
PRECACHE_SOUND("weapons/zoom_generic_out.wav");

	m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireAugg = PRECACHE_EVENT(1, "events/auggold.sc");
}

int CAUGG::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "556Nato";
	p->iMaxAmmo1 = MAX_AMMO_556NATO;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = AUGG_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 14;
	p->iId = m_iId = WEAPON_AUG;
	p->iFlags = 0;
	p->iWeight = AUG_WEIGHT;

	return 1;
}

void CAUGG::WeaponName(void)
{
CLIENT_COMMAND(m_pPlayer->edict(), "laser 1\n");
SendWeaponAnim(TAR21_DRAW, 0);
CLIENT_COMMAND(m_pPlayer->edict(), "weaponname 8\n");
}

BOOL CAUGG::Deploy(void)
{
SetThink(&CAUGG::WeaponName);
	pev->nextthink = gpGlobals->time + 0.01;

	m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	iShellOn = 1;

//return DefaultDeploy(m_pPlayer->m_iTeam == CT ? "models/billflx/cityforce/v_aug_gold.mdl" : "models/billflx/rebel/v_aug_gold.mdl", "models/p_aug_gold.mdl", NULL, "carbine", UseDecrement() != FALSE);


switch (m_pPlayer->m_iModelName)
		{
		case MODEL_URBAN://acid
return DefaultDeploy("models/billflx/classblue1/v_aug_gold.mdl", "models/p_aug_gold.mdl", NULL, "carbine", UseDecrement() != FALSE);
			break;

		case MODEL_GSG9://keen
return DefaultDeploy("models/billflx/classblue2/v_aug_gold.mdl", "models/p_aug_gold.mdl", NULL, "carbine", UseDecrement() != FALSE);
			break;

		case MODEL_SAS://leopard
return DefaultDeploy("models/billflx/classblue3/v_aug_gold.mdl", "models/p_aug_gold.mdl", NULL, "carbine", UseDecrement() != FALSE);
			break;

		case MODEL_GIGN://hide
return DefaultDeploy("models/billflx/classblue4/v_aug_gold.mdl", "models/p_aug_gold.mdl", NULL, "carbine", UseDecrement() != FALSE);
			break;

                             case MODEL_SPETSNAZ://chou
return DefaultDeploy("models/billflx/classblue5/v_aug_gold.mdl", "models/p_aug_gold.mdl", NULL, "carbine", UseDecrement() != FALSE);
			break;

//
                           case MODEL_TERROR://redbull
return DefaultDeploy("models/billflx/classred1/v_aug_gold.mdl", "models/p_aug_gold.mdl", NULL, "carbine", UseDecrement() != FALSE);
			break;

		case MODEL_LEET://tarantula
return DefaultDeploy("models/billflx/classred2/v_aug_gold.mdl", "models/p_aug_gold.mdl", NULL, "carbine", UseDecrement() != FALSE);
			break;

		case MODEL_ARCTIC://dfox
return DefaultDeploy("models/billflx/classred3/v_aug_gold.mdl", "models/p_aug_gold.mdl", NULL, "carbine", UseDecrement() != FALSE);
			break;

		case MODEL_GUERILLA://viper
return DefaultDeploy("models/billflx/classred4/v_aug_gold.mdl", "models/p_aug_gold.mdl", NULL, "carbine", UseDecrement() != FALSE);
			break;

		case MODEL_MILITIA://rica
return DefaultDeploy("models/billflx/classred5/v_aug_gold.mdl", "models/p_aug_gold.mdl", NULL, "carbine", UseDecrement() != FALSE);
			break;
}
}

void CAUGG::SecondaryAttack(void)
{
	
switch (m_pPlayer->m_iFOV)
	{
		case 90:

SetThink(&CAUGG::Fov2);
	pev->nextthink = gpGlobals->time + 0.0000009;
break;

		default:
SetThink(&CAUGG::offFov2);
	pev->nextthink = gpGlobals->time + 0.0000009;
SendWeaponAnim(OFF, 0);


 break;
	}

	m_pPlayer->ResetMaxSpeed();
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}


void CAUGG::Fov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 

SetThink(&CAUGG::Fov3);
	pev->nextthink = gpGlobals->time + 0.0000009;
CLIENT_COMMAND(m_pPlayer->edict(), "eotechdot 1\n");

}

void CAUGG::Fov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 80; 

SetThink(&CAUGG::Fov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
CLIENT_COMMAND(m_pPlayer->edict(), "eotechdot 1\n");
}

void CAUGG::Fov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CAUGG::Fov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
CLIENT_COMMAND(m_pPlayer->edict(), "eotechdot 1\n");
}

void CAUGG::Fov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 65; 

SetThink(&CAUGG::Fov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
CLIENT_COMMAND(m_pPlayer->edict(), "eotechdot 1\n");
}

void CAUGG::Fov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 55; 
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_generic_in.wav", 0.2, 2.4);
m_pPlayer->pev->viewmodel = MAKE_STRING("models/sight/v_muzzle_bottom.mdl");

CLIENT_COMMAND(m_pPlayer->edict(), "eotechdot 1\n");
}

//offfov

void CAUGG::offFov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 60; 

SetThink(&CAUGG::offFov3);
	pev->nextthink = gpGlobals->time + 0.0000009;

}

void CAUGG::offFov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CAUGG::offFov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CAUGG::offFov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CAUGG::offFov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}
void CAUGG::offFov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 

SetThink(&CAUGG::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CAUGG::offFov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90; 
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_generic_out.wav", 0.2, 2.4);
//m_pPlayer->pev->viewmodel = MAKE_STRING(m_pPlayer->m_iTeam == CT ? "models/billflx/cityforce/v_aug_gold.mdl" : "models/billflx/rebel/v_aug_gold.mdl");

switch (m_pPlayer->m_iModelName)
		{
		case MODEL_URBAN://acid
m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/classblue1/v_aug_gold.mdl");
			break;
		case MODEL_GSG9://keen
m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/classblue2/v_aug_gold.mdl");
			break;
		case MODEL_SAS://leopard
m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/classblue3/v_aug_gold.mdl");
			break;
		case MODEL_GIGN://hide
m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/classblue4/v_aug_gold.mdl");
			break;
                             case MODEL_SPETSNAZ://chou
m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/classblue5/v_aug_gold.mdl");
			break;
//
                           case MODEL_TERROR://redbull
m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/classred1/v_aug_gold.mdl");
			break;
		case MODEL_LEET://tarantula
m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/classred2/v_aug_gold.mdl");
			break;
		case MODEL_ARCTIC://dfox
m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/classred3/v_aug_gold.mdl");
			break;
		case MODEL_GUERILLA://viper
m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/classred4/v_aug_gold.mdl");
			break;
		case MODEL_MILITIA://rica
m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/classred5/v_aug_gold.mdl");
			break;
}

}


void CAUGG::PrimaryAttack(void)
{
	float FireRate = (m_pPlayer->pev->fov == 90) ? 0.095 : 0.13;
	if (!FBitSet(m_pPlayer->pev->flags, FL_ONGROUND))
		AUGGFire(0.0 * m_flAccuracy + (0.04), FireRate, FALSE);
	else if (m_pPlayer->pev->velocity.Length2D() > 130)
		AUGGFire(0.0 * m_flAccuracy + (0.02), FireRate, FALSE);
	else if (FBitSet(m_pPlayer->pev->flags, FL_DUCKING))
		AUGGFire(0.0 * m_flAccuracy, FireRate, FALSE);
	else if (m_pPlayer->pev->fov == 90)
		AUGGFire((0.0) * m_flAccuracy, FireRate, FALSE);
	else
		AUGGFire((0.0) * m_flAccuracy, FireRate, FALSE);
}

void CAUGG::AUGGFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	m_bDelayFire = true;
	m_iShotsFired++;
	m_flAccuracy = ((float)(m_iShotsFired * m_iShotsFired * m_iShotsFired) / 220.0) + 0.29;

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
UTIL_MakeVectors(m_pPlayer->pev->v_angle);
	Vector vecEnd = vecSrc + gpGlobals->v_forward * 2000;
#ifndef CLIENT_DLL
	m_pPlayer->Trace(vecEnd, gpGlobals->v_forward, flSpread, 0, 0, m_pPlayer->pev, m_pPlayer->pev);
#endif


	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(), m_usFireAugg, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), FALSE, FALSE);
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
	else if (m_pPlayer->pev->fov != 90)
		KickBack(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	else if (FBitSet(m_pPlayer->pev->flags, FL_DUCKING))
		KickBack(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
	else
		KickBack(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5);
}

void CAUGG::Reload(void)
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;

	if (DefaultReload(AUGG_MAX_CLIP, TAR21_RELOAD, 2.3))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		if (m_pPlayer->m_iFOV != 90)
{
			SetThink(&CAUGG::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;

m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 3;

SendWeaponAnim(TAR21_RELOAD, 0);
		}
	}
}

void CAUGG::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
	SendWeaponAnim(TAR21_IDLE1, UseDecrement() != FALSE);
}
