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
#include "wpn_m4_azure.h"

enum sg550_e
{
	SG550_IDLE,
SG550_RELOAD,
	SG550_DRAW, 
	SG550_SHOOT,
	SG550_SHOOT2,
	SG550_SHOOT3,
OFF,
ANIM2,
ANIM3,
ANIM4,
ANIM5
};

const int AZURE_MAXCLIP = 45;

LINK_ENTITY_TO_CLASS(weapon_m4_azure, CM4_Azure)


void CM4_Azure::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_m4_azure");

	Precache();
	m_iId = WEAPON_AUG;
	SET_MODEL(ENT(pev), "models/w_sg550.mdl");
	m_iDefaultAmmo = AZURE_MAXCLIP;

	FallInit();
}

void CM4_Azure::Precache(void)
{
	
PRECACHE_MODEL("models/billflx/v_bb_azure_dragon.mdl");

	PRECACHE_MODEL("models/p_hk.mdl");

	PRECACHE_SOUND("weapons/hk417-1.wav");
	PRECACHE_SOUND("weapons/sg550_boltpull.wav");
	PRECACHE_SOUND("weapons/sg550_clipin.wav");
	PRECACHE_SOUND("weapons/sg550_clipout.wav");
	PRECACHE_SOUND("weapons/zoom_generic_in.wav");
PRECACHE_SOUND("weapons/zoom_generic_out.wav");

	m_iShellId = m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireScar_carbine = PRECACHE_EVENT(1, "events/ak47.sc");
}

int CM4_Azure::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "556Nato";
	p->iMaxAmmo1 = MAX_AMMO_556NATO;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = AZURE_MAXCLIP;
	p->iSlot = 0;
	p->iPosition = 14;
	p->iId = m_iId = WEAPON_AUG;
	p->iFlags = 0;
	p->iWeight = AUG_WEIGHT;

	return 1;
}


BOOL CM4_Azure::Deploy(void)
{

m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	//iShellOn = 1;

return DefaultDeploy("models/billflx/v_bb_azure_dragon.mdl", "models/p_hk.mdl", SG550_DRAW, "rifle", 0);

}

void CM4_Azure::QuickDeploy()
{
SendWeaponAnim(OFF, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CM4_Azure::SecondaryAttack(void)
{
	
switch (m_pPlayer->m_iFOV)
	{
		case 90:

SetThink(&CM4_Azure::Fov2);
	pev->nextthink = gpGlobals->time + 0.0000009;
break;

		default:
SetThink(&CM4_Azure::offFov2);
	pev->nextthink = gpGlobals->time + 0.0000009;


 break;
	}

		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}


void CM4_Azure::Fov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 

SetThink(&CM4_Azure::Fov3);
	pev->nextthink = gpGlobals->time + 0.0000009;



#ifndef CLIENT_DLL
if (weapon_sight_m4_azure.value == 0)
CLIENT_COMMAND(m_pPlayer->edict(), "eotech_scope\n");
else if (weapon_sight_m4_azure.value == 1) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 1; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 2) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 2; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 3) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 3; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 4) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 4; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 5) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 5; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 6) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 6; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 7) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 7; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 8) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 8; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 9) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 9; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 10) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 10; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 11) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 11; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 12) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 12; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 13) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 13; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 14) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 14; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 15) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 15; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 16) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 16; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 17) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 17; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 18) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 18; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 19) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 19; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 20) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 20; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 21) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 21; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 22) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 22; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 23) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 23; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 24) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 24; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 25) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 25; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 26) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 26; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 27) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 27; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 28) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 28; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 29) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 29; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 30) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 30; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 31) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 31; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 32) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 32; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 33) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 33; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 34) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 34; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 35) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 35; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 36) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 36; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 37) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 37; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 38) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 38; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 39) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 39; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 40) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 40; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 41) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 41; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 42) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 42; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 43) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 43; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 44) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 44; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 45) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 45; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 46) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 46; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 47) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 47; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 48) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 48; Custom_Scope\n");
else if (weapon_sight_m4_azure.value == 49) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 49; Custom_Scope\n");
#endif
}

void CM4_Azure::Fov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 80; 

SetThink(&CM4_Azure::Fov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CM4_Azure::Fov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CM4_Azure::Fov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CM4_Azure::Fov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 65; 

SetThink(&CM4_Azure::Fov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CM4_Azure::Fov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 55; 

EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_generic_in.wav", 0.2, 2.4);

m_pPlayer->pev->viewmodel = MAKE_STRING("models/sight/v_muzzle_bottom.mdl");
SendWeaponAnim(SG550_IDLE, UseDecrement() != FALSE);
}

//offfov

void CM4_Azure::offFov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 60; 

SetThink(&CM4_Azure::offFov3);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CM4_Azure::offFov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CM4_Azure::offFov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CM4_Azure::offFov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 75; 

SetThink(&CM4_Azure::offFov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}
void CM4_Azure::offFov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 85; 
SendWeaponAnim(SG550_IDLE, 0);
SetThink(&CM4_Azure::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CM4_Azure::offFov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90; 
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_generic_out.wav", 0.2, 2.4);

m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/v_bb_azure_dragon.mdl");



}

void CM4_Azure::PrimaryAttack(void)
{
	
		Scar_carbineFire((0.0), 0.0955, FALSE);

}

void CM4_Azure::Scar_carbineFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	if (m_pPlayer->pev->fov == 90)
		flSpread += 0.025;

	if (m_flLastFire)
	{
		m_flAccuracy = (gpGlobals->time - m_flLastFire) * 0.35 + 0.65;

		if (m_flAccuracy > 0.98)
			m_flAccuracy = 0.98;
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
#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	m_pPlayer->m_iWeaponVolume = BIG_EXPLOSION_VOLUME;
	m_pPlayer->m_iWeaponFlash = NORMAL_GUN_FLASH;

	Vector vecDir = FireBullets3(m_pPlayer->GetGunPosition(), gpGlobals->v_forward, flSpread, 8192, 2, BULLET_PLAYER_556MM, 20, 0.98, m_pPlayer->pev, TRUE, m_pPlayer->random_seed);

Vector vecSrc = m_pPlayer->GetGunPosition();
if (m_iClip > 0)
{
SendWeaponAnim(SG550_SHOOT, 0);
}
else if (m_iClip == 0)
{
SendWeaponAnim(SG550_IDLE, 0);
}
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/hk417-1.wav", VOL_NORM, ATTN_NORM);


	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, ENT(m_pPlayer->pev),m_usFireScar_carbine, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x, vecDir.y, (int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.y * 100), 5, FALSE);
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;
#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.8;

	m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomFloat(m_pPlayer->random_seed + 1, 0.5, 0.2) + m_pPlayer->pev->punchangle.x * 0.25;
	m_pPlayer->pev->punchangle.y += UTIL_SharedRandomFloat(m_pPlayer->random_seed + 0.2, 0.1, 0.2);
}

void CM4_Azure::Reload(void)
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;
if (m_iClip == AZURE_MAXCLIP)
return;
	if (DefaultReload(AZURE_MAXCLIP, NULL, 2.5))
	{
		m_flAccuracy = 0.2;
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif

		
			SetThink(&CM4_Azure::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;

m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 2.3;
		
	}
SendWeaponAnim(SG550_RELOAD, 0);
}

void CM4_Azure::QuickReload()
{
	if (m_pPlayer->ammo_556nato <= 0)
		return;
if (m_iClip == AZURE_MAXCLIP)
return;
	if (DefaultReloadQuick(AZURE_MAXCLIP, NULL, 1.5))
	{
		m_flAccuracy = 0.2;
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif

		
			SetThink(&CM4_Azure::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;

m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.3;
		
	}
SendWeaponAnim(ANIM2, 0);
}

void CM4_Azure::WeaponIdle(void)
{
	ResetEmptySound();

	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	if (m_iClip)
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 60;
		SendWeaponAnim(SG550_IDLE, UseDecrement() != FALSE);
	}
}

