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
#include "wpn_scout.h"

enum scout_e
{
	SCOUT_IDLE,
	SCOUT_SHOOT1,
	SCOUT_SHOOT2,
	SCOUT_SHOOT3,
	SCOUT_RELOAD,
	SCOUT_DRAW,
ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5,
ANIM6
};


LINK_ENTITY_TO_CLASS(weapon_scout, CSCOUT)

void CSCOUT::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_scout");

	Precache();
	m_iId = WEAPON_SCOUT;
	SET_MODEL(ENT(pev), "models/w_scout.mdl");

	m_iDefaultAmmo = SCOUT_DEFAULT_GIVE;
	FallInit();
}

void CSCOUT::Precache(void)
{
	
PRECACHE_MODEL("models/billflx/v_ssg69.mdl");

	PRECACHE_MODEL("models/p_ssg69.mdl");

//test
m_iSprBeam = PRECACHE_MODEL("sprites/trace.spr");


	PRECACHE_SOUND("weapons/scout_fire-1.wav");
	PRECACHE_SOUND("weapons/scout_bolt.wav");
	PRECACHE_SOUND("weapons/scout_clipin.wav");
	PRECACHE_SOUND("weapons/scout_clipout.wav");
	PRECACHE_SOUND("weapons/zoom_sniper_in.wav");
PRECACHE_SOUND("weapons/zoom_sniper_out.wav");


	m_iShellId = PRECACHE_MODEL("models/rshell_big.mdl");
	m_usFireScout = PRECACHE_EVENT(1, "events/awp.sc");
}

int CSCOUT::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "338Magnum";
	p->iMaxAmmo1 = MAX_AMMO_338MAGNUM;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = SCOUT_MAX_CLIP;
	p->iSlot = 0;
	p->iPosition = 9;
	p->iId = WEAPON_SCOUT;
	p->iFlags = 0;
	p->iWeight = SCOUT_WEIGHT;

	return 1;
}



BOOL CSCOUT::Deploy(void)
{

if (DefaultDeploy("models/billflx/v_ssg69.mdl", "models/p_ssg69.mdl", SCOUT_DRAW, "rifle", 0)) 

{
	m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 1;
	m_flNextSecondaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.6;
	
	return TRUE;
	}
	return FALSE;

}

void CSCOUT::QuickDeploy()
{
SendWeaponAnim(ANIM5, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CSCOUT::SecondaryAttack(void)
{
	switch (m_pPlayer->m_iFOV)
	{
		case 90: 

SetThink(&CSCOUT::Fov2);
	pev->nextthink = gpGlobals->time + 0.000001;
break;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;

		default: 
SetThink(&CSCOUT::offFov2);
	pev->nextthink = gpGlobals->time + 0.0000009;
break;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
	}

	m_pPlayer->ResetMaxSpeed();
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;

}

void CSCOUT::Fov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 80; 

SetThink(&CSCOUT::Fov3);
	pev->nextthink = gpGlobals->time + 0.000001;

#ifndef CLIENT_DLL
if (weapon_sight_ssg69.value == 0)
CLIENT_COMMAND(m_pPlayer->edict(), "sniper_scope\n");
else if (weapon_sight_ssg69.value == 1) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 1; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 2) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 2; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 3) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 3; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 4) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 4; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 5) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 5; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 6) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 6; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 7) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 7; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 8) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 8; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 9) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 9; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 10) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 10; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 11) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 11; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 12) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 12; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 13) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 13; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 14) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 14; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 15) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 15; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 16) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 16; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 17) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 17; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 18) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 18; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 19) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 19; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 20) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 20; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 21) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 21; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 22) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 22; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 23) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 23; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 24) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 24; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 25) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 25; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 26) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 26; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 27) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 27; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 28) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 28; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 29) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 29; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 30) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 30; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 31) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 31; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 32) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 32; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 33) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 33; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 34) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 34; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 35) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 35; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 36) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 36; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 37) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 37; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 38) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 38; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 39) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 39; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 40) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 40; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 41) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 41; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 42) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 42; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 43) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 43; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 44) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 44; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 45) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 45; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 46) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 46; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 47) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 47; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 48) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 48; Custom_Scope\n");
else if (weapon_sight_ssg69.value == 49) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 49; Custom_Scope\n");
#endif
}

void CSCOUT::Fov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CSCOUT::Fov4);
	pev->nextthink = gpGlobals->time + 0.0000009;

}

void CSCOUT::Fov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 50; 

SetThink(&CSCOUT::Fov5);
	pev->nextthink = gpGlobals->time + 0.0000009;

}

void CSCOUT::Fov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 40; 

SetThink(&CSCOUT::Fov6);
	pev->nextthink = gpGlobals->time + 0.0000009;

}

void CSCOUT::Fov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 30; 

SetThink(&CSCOUT::Fov7);
	pev->nextthink = gpGlobals->time + 0.0000009;

}

void CSCOUT::Fov7(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 20;
	
	m_pPlayer->ResetMaxSpeed();
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_sniper_in.wav", 0.2, 2.4);


SetThink(&CSCOUT::breath);
switch (RANDOM_LONG(1, 3))
{
case 1:
	pev->nextthink = gpGlobals->time + 4;
break;
case 2:
	pev->nextthink = gpGlobals->time + 5;
break;
case 3:
	pev->nextthink = gpGlobals->time + 7;
break;
}

}


void CSCOUT::breath()
{
switch (m_pPlayer->m_iModelName)
		{
case MODEL_URBAN:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breath\"\n");
			break;
case MODEL_GSG9:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breathf\"\n");
			break;
case MODEL_SAS:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breath\"\n");
			break;
case MODEL_GIGN:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breathf\"\n");
			break;
case MODEL_SPETSNAZ:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breathf\"\n");
			break;
case MODEL_TERROR:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breath\"\n");
			break;
case MODEL_LEET:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breathf\"\n");
			break;
case MODEL_ARCTIC:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breath\"\n");
			break;
case MODEL_GUERILLA:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breathf\"\n");
			break;
case MODEL_MILITIA:
CLIENT_COMMAND(m_pPlayer->edict(), "speak \"breathf\"\n");
			break;
}

}

void CSCOUT::Holster(int skiplocal)
{
m_fInReload = FALSE;
SetThink(nullptr);
}

//offfov

void CSCOUT::offFov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 30; 

SetThink(&CSCOUT::offFov3);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CSCOUT::offFov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 40; 

SetThink(&CSCOUT::offFov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CSCOUT::offFov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 50; 

SetThink(&CSCOUT::offFov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CSCOUT::offFov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 60; 

SetThink(&CSCOUT::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CSCOUT::offFov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CSCOUT::offFov7);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CSCOUT::offFov7(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90;
	m_pPlayer->ResetMaxSpeed();
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_sniper_out.wav", 0.2, 2.4);
m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/v_ssg69.mdl");


}



void CSCOUT::PrimaryAttack(void)
{



	if (!FBitSet(m_pPlayer->pev->flags, FL_ONGROUND))
		SCOUTFire(0.0, 1.7, FALSE);
	else if (m_pPlayer->pev->velocity.Length2D() > 170)
		SCOUTFire(0.0, 1.7, FALSE);
	else if (FBitSet(m_pPlayer->pev->flags, FL_DUCKING))
		SCOUTFire(0.0, 1.7, FALSE);
	else
		SCOUTFire(0.006, 1.7, FALSE);




}

void CSCOUT::SCOUTFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	if (m_pPlayer->pev->fov != 90)
	{
		m_pPlayer->m_iLastZoom = m_pPlayer->m_iFOV;
		m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90;


	}
	else
		flSpread += 0.1;

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

	m_pPlayer->m_flEjectBrass = gpGlobals->time + 0.56;
	m_pPlayer->m_iWeaponVolume = BIG_EXPLOSION_VOLUME;
	m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;

	Vector vecDir = FireBullets3(m_pPlayer->GetGunPosition(), gpGlobals->v_forward, flSpread, 8192, 3, BULLET_PLAYER_762MM, 75, 0.98, m_pPlayer->pev, TRUE, m_pPlayer->random_seed);

Vector vecSrc = m_pPlayer->GetGunPosition();

SendWeaponAnim(SCOUT_SHOOT1, 0);
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/scout_fire-1.wav", VOL_NORM, ATTN_NORM);

	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, ENT(m_pPlayer->pev),m_usFireScout, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x * 1000, vecDir.y * 1000, (int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.x * 100), FALSE, FALSE);
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;
#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.8;
	m_pPlayer->pev->punchangle.x -= 2;
}

void CSCOUT::Reload(void)
{
	if (m_pPlayer->ammo_762nato <= 0)
		return;
if (m_iClip == SCOUT_MAX_CLIP)
return;
	if (DefaultReload(SCOUT_MAX_CLIP, NULL, 3))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif

		
			//m_pPlayer->pev->fov = m_pPlayer->m_iFOV = 15;
			SetThink(&CSCOUT::offFov7);
	pev->nextthink = gpGlobals->time + 0.0000009;

	}
SendWeaponAnim(SCOUT_RELOAD,  0);
}

void CSCOUT::QuickReload()
{
	if (m_pPlayer->ammo_762nato <= 0)
		return;
if (m_iClip == SCOUT_MAX_CLIP)
return;
	if (DefaultReloadQuick(SCOUT_MAX_CLIP, NULL, 2))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		
			//m_pPlayer->pev->fov = m_pPlayer->m_iFOV = 15;
			SetThink(&CSCOUT::offFov7);
	pev->nextthink = gpGlobals->time + 0.0000009;
	}
SendWeaponAnim(ANIM6,  0);
}

void CSCOUT::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;



		;
	

	if (m_iClip)
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 60;
		SendWeaponAnim(SCOUT_IDLE, UseDecrement() != FALSE);
	}
}

float CSCOUT::GetMaxSpeed(void)
{
	if (m_pPlayer->m_iFOV == 90)
		return 200;

	return 150;
}
