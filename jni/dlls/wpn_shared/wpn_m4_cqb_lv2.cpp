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
#include "wpn_m4_cqb_lv2.h"

enum m4a1_e
{
	AUG_IDLE1,
	AUG_RELOAD,
	AUG_DRAW,
	AUG_SHOOT1,
	AUG_SHOOT2,
	AUG_SHOOT3, 
OFF,
ANIM2,
ANIM3,
ANIM4,
ANIM5,
ANIM6
};

LINK_ENTITY_TO_CLASS(weapon_m4_cqb_lv2, CM4_cqb_lv2)

void CM4_cqb_lv2::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_m4_cqb_lv2");

	Precache();
	m_iId = WEAPON_GALIL;
	SET_MODEL(ENT(pev), "models/w_aug_a3.mdl");

	m_iDefaultAmmo = M4A1_DEFAULT_GIVE;
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;

	FallInit();
}

void CM4_cqb_lv2::Precache(void)
{
	
PRECACHE_MODEL("models/sight/v_m4cgb_sight.mdl");

PRECACHE_MODEL("models/billflx/v_m4_cqb-r_lv2.mdl");
	PRECACHE_MODEL("models/p_m4_cqb-r_lv2.mdl");

	PRECACHE_SOUND("weapons/m4_cqb-r_lv1-1.wav");
	PRECACHE_SOUND("weapons/aug_clipout.wav");
	PRECACHE_SOUND("weapons/aug_clipin.wav");
	PRECACHE_SOUND("weapons/aug_boltpull.wav");
	PRECACHE_SOUND("weapons/aug_boltslap.wav");
	PRECACHE_SOUND("weapons/aug_forearm.wav");
PRECACHE_SOUND("weapons/zoom_generic_in.wav");
PRECACHE_SOUND("weapons/zoom_generic_out.wav");

	m_iShell = PRECACHE_MODEL("models/pshell.mdl");
	m_usFireM4_cqb_lv2 = PRECACHE_EVENT(1, "events/ak47.sc");
}

int CM4_cqb_lv2::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "556Nato";
	p->iMaxAmmo1 = MAX_AMMO_556NATO;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = M4A1_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 17;
	p->iId = WEAPON_GALIL;
	p->iFlags = 0;
	p->iWeight = 25;

	return 1;
}

BOOL CM4_cqb_lv2::Deploy(void)
{

m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	iShellOn = 1;

return DefaultDeploy("models/billflx/v_m4_cqb-r_lv2.mdl", "models/p_m4_cqb-r_lv2.mdl", AUG_DRAW, "rifle", 0);

}

void CM4_cqb_lv2::QuickDeploy()
{
SendWeaponAnim(ANIM5, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CM4_cqb_lv2::SecondaryAttack(void)
{
	/*switch (m_pPlayer->m_iFOV)
	{
		case 90: m_pPlayer->pev->viewmodel = MAKE_STRING("models/sight/v_m4cgb_sight.mdl");
SendWeaponAnim(OFF, 0);

		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;

		m_pPlayer->pev->fov = m_pPlayer->m_iFOV = 55; break;

		
		default: m_pPlayer->pev->viewmodel = MAKE_STRING(m_pPlayer->m_iTeam == CT ? "models/billflx/cityforce/v_m4_cqb-r_lv2.mdl" : "models/billflx/rebel/v_m4_cqb-r_lv2.mdl");
SendWeaponAnim(OFF, 0);

		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
		m_pPlayer->pev->fov = m_pPlayer->m_iFOV = 90; break;
	}

	m_pPlayer->ResetMaxSpeed();
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom.wav", 0.2, 2.4);
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}*/
switch (m_pPlayer->m_iFOV)
	{
		case 90:

SetThink(&CM4_cqb_lv2::Fov2);
	pev->nextthink = gpGlobals->time + 0.02;
break;

		default:
SetThink(&CM4_cqb_lv2::offFov2);
	pev->nextthink = gpGlobals->time + 0.02;
SendWeaponAnim(OFF, 0);


 break;
	}

	m_pPlayer->ResetMaxSpeed();
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom.wav", 0.2, 2.4);
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}


void CM4_cqb_lv2::Fov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 

SetThink(&CM4_cqb_lv2::Fov3);
	pev->nextthink = gpGlobals->time + 0.02;
CLIENT_COMMAND(m_pPlayer->edict(), "disable_scope\n");
}

void CM4_cqb_lv2::Fov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 80; 

SetThink(&CM4_cqb_lv2::Fov4);
	pev->nextthink = gpGlobals->time + 0.02;
}

void CM4_cqb_lv2::Fov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CM4_cqb_lv2::Fov5);
	pev->nextthink = gpGlobals->time + 0.02;
}

void CM4_cqb_lv2::Fov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 65; 

SetThink(&CM4_cqb_lv2::Fov6);
	pev->nextthink = gpGlobals->time + 0.02;
}

void CM4_cqb_lv2::Fov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 55; 

m_pPlayer->pev->viewmodel = MAKE_STRING("models/sight/v_m4cgb_sight.mdl");
SendWeaponAnim(OFF, 0);

}

//offfov

void CM4_cqb_lv2::offFov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 60; 

SetThink(&CM4_cqb_lv2::offFov3);
	pev->nextthink = gpGlobals->time + 0.02;
}

void CM4_cqb_lv2::offFov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CM4_cqb_lv2::offFov4);
	pev->nextthink = gpGlobals->time + 0.02;
}

void CM4_cqb_lv2::offFov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CM4_cqb_lv2::offFov5);
	pev->nextthink = gpGlobals->time + 0.02;
}
void CM4_cqb_lv2::offFov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 

SetThink(&CM4_cqb_lv2::offFov6);
	pev->nextthink = gpGlobals->time + 0.02;
}

void CM4_cqb_lv2::offFov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90; 

m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/v_m4_cqb-r_lv2.mdl");


}


void CM4_cqb_lv2::PrimaryAttack(void)
{
	
		M4_cqb_lv2Fire((0.03) * m_flAccuracy, 0.07, FALSE);

}

void CM4_cqb_lv2::M4_cqb_lv2Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
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
	Vector vecDir = m_pPlayer->FireBullets3(vecSrc, gpGlobals->v_forward, flSpread, 8192, 1, BULLET_PLAYER_45ACP, 20, 0.82, m_pPlayer->pev, FALSE, m_pPlayer->random_seed);

	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/m4_cqb-r_lv1-1.wav", VOL_NORM, ATTN_NORM);
if (m_iClip > 0)
{
SendWeaponAnim(AUG_SHOOT1, 0);
}
else if (m_iClip == 0)
{
SendWeaponAnim(AUG_IDLE1, 0);
}
	PLAYBACK_EVENT_FULL(flags, m_pPlayer->edict(),m_usFireM4_cqb_lv2, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), FALSE, FALSE);
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;
#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;

	if (!FBitSet(m_pPlayer->pev->flags, FL_ONGROUND))
		KickBack(0.5, 0.55, 0.4, 0.05, 0.75, 0.75, 0.5);
	else if (m_pPlayer->pev->velocity.Length2D() > 0)
		KickBack(0.5, 0.45, 0.25, 0.035, 0.5, 0.5, 0.5);
	else if (FBitSet(m_pPlayer->pev->flags, FL_DUCKING))
		KickBack(0.75, 0.4, 0.175, 0.03, 0.75, 0.5, 0.5);
	else
		KickBack(0.6, 0.425, 0.2, 0.03, 0.5, 0.5, 0.5);

}

void CM4_cqb_lv2::Reload(void)
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;
if (m_iClip == M4A1_MAX_CLIP)
return;
	if (DefaultReload(M4A1_MAX_CLIP, NULL, 3.3))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		
			SetThink(&CM4_cqb_lv2::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;


		m_flAccuracy = 0;
		m_iShotsFired = 0;
		m_bDelayFire = false;
	}
SendWeaponAnim(AUG_RELOAD, 0);
}

void CM4_cqb_lv2::QuickReload()
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;
if (m_iClip == M4A1_MAX_CLIP)
return;
	if (DefaultReloadQuick(M4A1_MAX_CLIP, NULL, 1.3))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		
			SetThink(&CM4_cqb_lv2::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;


		m_flAccuracy = 0;
		m_iShotsFired = 0;
		m_bDelayFire = false;
	}
SendWeaponAnim(ANIM6, 0);
}

void CM4_cqb_lv2::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;



	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
	SendWeaponAnim(AUG_IDLE1, UseDecrement() != FALSE);
}
