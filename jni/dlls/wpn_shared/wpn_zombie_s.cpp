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
#include "wpn_zombie_s.h"

#define KNIFE_BODYHIT_VOLUME		128
#define KNIFE_WALLHIT_VOLUME		512
#define KNIFE_MAX_SPEED			250
#define KNIFE_MAX_SPEED_SHIELD		180

enum xm1014_e
{
	XM1014_IDLE,
	XM1014_FIRE1,
	XM1014_FIRE2,
	XM1014_RELOAD,
XM1014_RELOAD2,
XM1014_RELOAD3,
XM1014_DRAW, 
	XM1014_START_RELOAD, 
SLASH,
ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5
};

LINK_ENTITY_TO_CLASS(weapon_zombie_s, Czombie_s)

const int ZOMBIES_MAXCLIP = 18;

void Czombie_s::Spawn(void)
{
	Precache();
	m_iId = WEAPON_XM1014;
	SET_MODEL(ENT(pev), "models/w_xm1014.mdl");

	m_iDefaultAmmo = ZOMBIES_MAXCLIP;

	FallInit();
}

void Czombie_s::Precache(void)
{
	//ct

PRECACHE_MODEL("models/billflx/v_zombie_s.mdl");

	PRECACHE_MODEL("models/p_zombie_s.mdl");

	m_iShellId = m_iShell = PRECACHE_MODEL("models/shotgunshell.mdl");

	PRECACHE_SOUND("weapons/zombie_slayer-1.wav");
	PRECACHE_SOUND("weapons/reload1.wav");
	PRECACHE_SOUND("weapons/reload3.wav");

	m_usFirezombie_s = PRECACHE_EVENT(1, "events/m3.sc");
}

int Czombie_s::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "buckshot";
	p->iMaxAmmo1 = MAX_AMMO_BUCKSHOT;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = ZOMBIES_MAXCLIP;
	p->iSlot = 0;
	p->iPosition = 12;
	p->iId = WEAPON_XM1014;
	p->iFlags = 0;
	p->iWeight = XM1014_WEIGHT;

	return 1;
}

void Czombie_s::Holster(int skiplocal)
{

m_fInReload = FALSE;
SetThink(nullptr);
}


BOOL Czombie_s::Deploy(void)
{
if (DefaultDeploy("models/billflx/v_zombie_s.mdl", "models/p_zombie_s.mdl", XM1014_DRAW, "shotgun", 0)) 

{
	m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.6;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.6;
	
	return TRUE;
	}
	return FALSE;

}

void Czombie_s::QuickDeploy()
{
SendWeaponAnim(ANIM1, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void Czombie_s::SecondaryAttack(void)
{
	
	SendWeaponAnim(SLASH, UseDecrement() != FALSE);

	SetThink(&Czombie_s::DelayedSecondaryAttack);
	pev->nextthink = gpGlobals->time + 0.61;

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.62;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.5;
}

void Czombie_s::DelayedSecondaryAttack()
{
	BOOL fDidHit = FALSE;
	UTIL_MakeVectors(m_pPlayer->pev->v_angle);
	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecEnd = vecSrc + gpGlobals->v_forward * 45;

	TraceResult tr;
	UTIL_TraceLine(vecSrc, vecEnd, dont_ignore_monsters, ENT(m_pPlayer->pev), &tr);

	if (tr.flFraction >= 1)
	{
		UTIL_TraceHull(vecSrc, vecEnd, dont_ignore_monsters, head_hull, ENT(m_pPlayer->pev), &tr);

		if (tr.flFraction < 1)
		{
			CBaseEntity *pHit = CBaseEntity::Instance(tr.pHit);

			if (!pHit || pHit->IsBSPModel())
				FindHullIntersection(vecSrc, tr, VEC_DUCK_HULL_MIN, VEC_DUCK_HULL_MAX, ENT(m_pPlayer->pev));

			vecEnd = tr.vecEndPos;
		}
	}

	if (tr.flFraction >= 1)
	{
		
		{
			
			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.62;
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.5;

			

#ifndef CLIENT_DLL
			m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif
		}
	}
	else
	{
		fDidHit = TRUE;

#ifndef CLIENT_DLL
		
#endif
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.1;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.5;

		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);

#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif
		float flDamage = 100.0;

		if (pEntity && pEntity->IsPlayer())
		{
			Vector2D vec2LOS;
			Vector vecForward = gpGlobals->v_forward;

			UTIL_MakeVectors(m_pPlayer->pev->angles);

			vec2LOS = vecForward.Make2D();
			vec2LOS = vec2LOS.Normalize();

			if (DotProduct(vec2LOS, gpGlobals->v_forward.Make2D()) > 0.8)
				flDamage *= 3.0;
		}

		UTIL_MakeVectors(m_pPlayer->pev->v_angle);
		ClearMultiDamage();
		if (pEntity)
			pEntity->TraceAttack(m_pPlayer->pev, flDamage, gpGlobals->v_forward, &tr, DMG_NEVERGIB | DMG_BULLET);
		ApplyMultiDamage(m_pPlayer->pev, m_pPlayer->pev);

		float flVol = 1;
#ifndef CLIENT_DLL
		int fHitWorld = TRUE;
#endif
		if (pEntity)
		{
			if (pEntity->Classify() != CLASS_NONE && pEntity->Classify() != CLASS_MACHINE)
			{
				EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/fangblade_hit_slash_1.wav", VOL_NORM, ATTN_NORM);
				m_pPlayer->m_iWeaponVolume = KNIFE_BODYHIT_VOLUME;

				if (!pEntity->IsAlive())
					return;

				flVol = 0.1;
#ifndef CLIENT_DLL
				fHitWorld = FALSE;
#endif
			}
		}

#ifndef CLIENT_DLL
		if (fHitWorld)
		{
			TEXTURETYPE_PlaySound(&tr, vecSrc, vecSrc + (vecEnd - vecSrc) * 2, BULLET_PLAYER_CROWBAR);
			
		}
#endif
CBaseEntity *pHit = CBaseEntity::Instance(tr.pHit);
const Vector vecOrigin = tr.vecEndPos + Vector(0, 0, 3);
#ifndef CLIENT_DLL
if (fHitWorld)
{
MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY, pev->origin);
WRITE_BYTE(TE_SPARKS);
WRITE_COORD(vecOrigin[0]);
WRITE_COORD(vecOrigin[1]);
WRITE_COORD(vecOrigin[2]);
MESSAGE_END();
}
#endif
		m_trHit = tr;
		m_pPlayer->m_iWeaponVolume = flVol * KNIFE_WALLHIT_VOLUME;

		SetThink(&Czombie_s::Smack);
		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;
	}

	return;
}

void Czombie_s::Smack(void)
{
	;
}

void Czombie_s::PrimaryAttack(void)
{
	
if (m_pPlayer->pev->waterlevel == 3)
	{
		PlayEmptySound();
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1;
		return;
	}

	if (m_iClip <= 0)
	{
		Reload();

		if (m_iClip == 0)
			PlayEmptySound();

		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1;
		return;
	}

	m_pPlayer->m_iWeaponVolume = LOUD_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;

	m_iClip--;
	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
#ifndef CLIENT_DLL
	m_pPlayer->FireBullets(40, m_pPlayer->GetGunPosition(), gpGlobals->v_forward, Vector(0.0675, 0.0675, 0), 2000, BULLET_PLAYER_BUCKSHOT, 0);
#endif
	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

SendWeaponAnim(XM1014_FIRE1, 0);
EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/zombie_slayer-1.wav", VOL_NORM, ATTN_NORM);

	PLAYBACK_EVENT_FULL(flags, ENT(m_pPlayer->pev),m_usFirezombie_s, 0, (float *)&g_vecZero, (float *)&g_vecZero, m_vVecAiming.x, m_vVecAiming.y, 7, m_vVecAiming.x * 100, m_iClip != 0, FALSE);

	if (m_iClip)
		//m_flPumpTime = UTIL_WeaponTimeBase() + 0.125;

#ifndef CLIENT_DLL
	if (!m_iClip && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0)
		m_pPlayer->SetSuitUpdate("!HEV_AMO0", FALSE, 0);
#endif
	if (m_iClip)
		//m_flPumpTime = UTIL_WeaponTimeBase() + 0.125;

	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;

	if (m_iClip)
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.5;
	else
		m_flTimeWeaponIdle = 0.5;

	m_fInSpecialReload = 0;

	if (m_pPlayer->pev->flags & FL_ONGROUND)
		m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomLong(m_pPlayer->random_seed + 1, 2, 2);
	else
		m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomLong(m_pPlayer->random_seed + 1, 2, 2);
}

void Czombie_s::Reload(void)
{

if (m_pPlayer->ammo_buckshot <= 0)
		return;
if (m_iClip == ZOMBIES_MAXCLIP)
return;
	if (DefaultReload(ZOMBIES_MAXCLIP, NULL, 3.1))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif

		m_flAccuracy = 0;
		m_iShotsFired = 0;
		m_bDelayFire = false;

SendWeaponAnim(XM1014_START_RELOAD, 0);
	}
}

void Czombie_s::QuickReload()
{

if (m_pPlayer->ammo_buckshot <= 0)
		return;
if (m_iClip == ZOMBIES_MAXCLIP)
return;
	if (DefaultReloadQuick(ZOMBIES_MAXCLIP, ANIM2, 1.5))
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif

		m_flAccuracy = 0;
		m_iShotsFired = 0;
		m_bDelayFire = false;

	}
}

void Czombie_s::WeaponIdle(void)
{

ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
	SendWeaponAnim(XM1014_IDLE, UseDecrement() != FALSE);
}
