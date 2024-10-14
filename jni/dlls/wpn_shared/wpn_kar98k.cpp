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
#include "wpn_kar98k.h"
#include "game.h"

enum sg552_e
{
	SG552_IDLE1,
SG552_SHOOT1,
	SG552_SHOOT2,
	SG552_SHOOT3, 
SG552_START,
	SG552_DRAW, 
SG552_INSERT,
SG552_END,
SG552_IDLE2,
SG552_IDLE3,
SG552_IDLE4,
ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5
};

LINK_ENTITY_TO_CLASS(weapon_kar98k, CKar98k)

const int KAR98K_MAXCLIP = 8;

void CKar98k::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_kar98k");

	Precache();
	m_iId = WEAPON_AWP;
	SET_MODEL(ENT(pev), "models/w_sg552.mdl");

	m_iDefaultAmmo = KAR98K_MAXCLIP;
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;

	FallInit();
}

void CKar98k::Precache(void)
{
	
PRECACHE_MODEL("models/billflx/v_kar98k.mdl");

	PRECACHE_MODEL("models/p_kar98k.mdl");

	PRECACHE_SOUND("weapons/kar98k-1.wav");
	PRECACHE_SOUND("weapons/sg552-2.wav");
	PRECACHE_SOUND("weapons/sg552_clipout.wav");
	PRECACHE_SOUND("weapons/sg552_clipin.wav");
	PRECACHE_SOUND("weapons/sg552_boltpull.wav");
PRECACHE_SOUND("weapons/zoom_sniper_in.wav");
PRECACHE_SOUND("weapons/zoom_sniper_out.wav");


	m_iShell = PRECACHE_MODEL("models/rshell.mdl");
	m_usFireAWP = PRECACHE_EVENT(1, "events/awp.sc");
}

int CKar98k::GetItemInfo(ItemInfo *p)
{

p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "338Magnum";
	p->iMaxAmmo1 = MAX_AMMO_338MAGNUM;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = KAR98K_MAXCLIP;
	p->iSlot = 0;
	p->iPosition = 2;
	p->iId = WEAPON_AWP;
	p->iFlags = 0;
	p->iWeight = AWP_WEIGHT;

	return 1;
}

BOOL CKar98k::Deploy(void)
{

m_fInSpecialReload = 0;

m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	iShellOn = 1;

if (DefaultDeploy("models/billflx/v_kar98k.mdl", "models/p_kar98k.mdl", SG552_DRAW, "rifle", 0)) 
{
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 1;
	m_flNextSecondaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.6;
	return TRUE;
	}
	return FALSE;

}


void CKar98k::QuickDeploy()
{
SendWeaponAnim(ANIM1, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CKar98k::SecondaryAttack(void)
{
	switch (m_pPlayer->m_iFOV)
	{
		case 90: 

SetThink(&CKar98k::Fov2);
	pev->nextthink = gpGlobals->time + 0.000001;
break;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;

		default: 
SetThink(&CKar98k::offFov2);
	pev->nextthink = gpGlobals->time + 0.0000009;
break;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
	}

	m_pPlayer->ResetMaxSpeed();
	
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;

}

void CKar98k::Fov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 80; 

SetThink(&CKar98k::Fov3);
	pev->nextthink = gpGlobals->time + 0.000001;


#ifndef CLIENT_DLL
if (weapon_sight_kar98k.value == 0)
CLIENT_COMMAND(m_pPlayer->edict(), "sks_scope\n");
else if (weapon_sight_kar98k.value == 1) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 1; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 2) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 2; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 3) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 3; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 4) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 4; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 5) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 5; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 6) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 6; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 7) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 7; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 8) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 8; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 9) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 9; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 10) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 10; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 11) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 11; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 12) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 12; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 13) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 13; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 14) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 14; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 15) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 15; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 16) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 16; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 17) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 17; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 18) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 18; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 19) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 19; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 20) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 20; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 21) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 21; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 22) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 22; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 23) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 23; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 24) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 24; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 25) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 25; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 26) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 26; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 27) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 27; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 28) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 28; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 29) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 29; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 30) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 30; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 31) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 31; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 32) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 32; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 33) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 33; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 34) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 34; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 35) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 35; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 36) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 36; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 37) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 37; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 38) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 38; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 39) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 39; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 40) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 40; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 41) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 41; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 42) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 42; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 43) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 43; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 44) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 44; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 45) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 45; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 46) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 46; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 47) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 47; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 48) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 48; Custom_Scope\n");
else if (weapon_sight_kar98k.value == 49) CLIENT_COMMAND(m_pPlayer->edict(), "custom_scope_cmd 49; Custom_Scope\n");
#endif
}

void CKar98k::Fov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CKar98k::Fov4);
	pev->nextthink = gpGlobals->time + 0.0000009;

}

void CKar98k::Fov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 50; 

SetThink(&CKar98k::Fov5);
	pev->nextthink = gpGlobals->time + 0.0000009;


}

void CKar98k::Fov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 40; 

SetThink(&CKar98k::Fov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CKar98k::Fov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 30; 

SetThink(&CKar98k::Fov7);
	pev->nextthink = gpGlobals->time + 0.0000009;

}

void CKar98k::Fov7(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 20;
	
	m_pPlayer->ResetMaxSpeed();
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_sniper_in.wav", 0.2, 2.4);	


SetThink(&CKar98k::breath);
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


void CKar98k::breath()
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

void CKar98k::Holster(int skiplocal)
{
m_fInReload = FALSE;
SetThink(nullptr);
}

//offfov

void CKar98k::offFov2(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 30; 

SetThink(&CKar98k::offFov3);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CKar98k::offFov3(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 40; 

SetThink(&CKar98k::offFov4);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CKar98k::offFov4(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 50; 

SetThink(&CKar98k::offFov5);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CKar98k::offFov5(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 60; 

SetThink(&CKar98k::offFov6);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CKar98k::offFov6(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 70; 

SetThink(&CKar98k::offFov7);
	pev->nextthink = gpGlobals->time + 0.0000009;
}

void CKar98k::offFov7(void)
{
	
m_pPlayer->m_iFOV = m_pPlayer->pev->fov = 90;
	m_pPlayer->ResetMaxSpeed();
	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/zoom_sniper_out.wav", 0.2, 2.4);
m_pPlayer->pev->viewmodel = MAKE_STRING("models/billflx/v_kar98k.mdl");

}



void CKar98k::PrimaryAttack(void)
{


	if (!FBitSet(m_pPlayer->pev->flags, FL_ONGROUND))
		Kar98kFire(0.0, 2, FALSE);
	else if (m_pPlayer->pev->velocity.Length2D() > 170)
		Kar98kFire(0.0, 2, FALSE);
	else if (FBitSet(m_pPlayer->pev->flags, FL_DUCKING))
		Kar98kFire(0.0, 2, FALSE);
	else
		Kar98kFire(0.0, 2, FALSE);





}

void CKar98k::Kar98kFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
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

	Vector vecDir = FireBullets3(m_pPlayer->GetGunPosition(), gpGlobals->v_forward, flSpread, 8192, 3, BULLET_PLAYER_556MM, 150, 0.98, m_pPlayer->pev, TRUE, m_pPlayer->random_seed);

EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/kar98k-1.wav", VOL_NORM, ATTN_NORM);

SendWeaponAnim(SG552_SHOOT1, 0);


	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

m_fInSpecialReload = 0;
QuickReload_enable = FALSE;


	PLAYBACK_EVENT_FULL(flags, ENT(m_pPlayer->pev), m_usFireAWP, 0, (float *)&g_vecZero, (float *)&g_vecZero, vecDir.x * 1000, vecDir.y * 1000, (int)(m_pPlayer->pev->punchangle.x * 100), (int)(m_pPlayer->pev->punchangle.x * 100), FALSE, FALSE);
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + flCycleTime;
#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.8;
	m_pPlayer->pev->punchangle.x -= 2;
}

void CKar98k::DefaultReloadCall (void)
{
CLIENT_COMMAND(m_pPlayer->edict(), "QuickReload_client\n");
}


void CKar98k::Reload(void)
{
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0 || m_iClip == KAR98K_MAXCLIP)
		return;
if (m_iClip == KAR98K_MAXCLIP)
return;
	if (m_flNextPrimaryAttack > UTIL_WeaponTimeBase())
		return;

SetThink(&CKar98k::DefaultReloadCall);
pev->nextthink = gpGlobals->time + 0.01;

	if (!m_fInSpecialReload)
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif
		SendWeaponAnim(SG552_START, UseDecrement() != FALSE);

		m_fInSpecialReload = 1;
		m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.75;
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.75;
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.75;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.75;
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
		SendWeaponAnim(ANIM2, UseDecrement() != FALSE);

}
else
{
		m_flNextReload = UTIL_WeaponTimeBase() + 0.55;
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.55;
		SendWeaponAnim(SG552_INSERT, UseDecrement() != FALSE);
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
		m_pPlayer->ammo_556nato--;
	if (m_pPlayer->pev->fov != 90)
		{
			m_pPlayer->pev->fov = m_pPlayer->m_iFOV = 10;
			SecondaryAttack();
		}
	}
}

void CKar98k::QuickReload()
{
	QuickReload_enable = TRUE;
}

void CKar98k::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_5DEGREES);

	//if (m_flPumpTime && m_flPumpTime < UTIL_WeaponTimeBase())
		//m_flPumpTime = 0;

	if (m_flTimeWeaponIdle < UTIL_WeaponTimeBase())
	{
		if (m_iClip == 0 && m_fInSpecialReload == 0 && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
		{
			Reload();
		}
		else if (m_fInSpecialReload != 0)
		{
			if (m_iClip != KAR98K_MAXCLIP && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
			{
				Reload();
			}
			else
			{
				SendWeaponAnim(SG552_END, UseDecrement() != FALSE);

				m_fInSpecialReload = 0;
				m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.5;
			}
		}
		else
			SendWeaponAnim(SG552_IDLE1, UseDecrement() != FALSE);
	}

}
