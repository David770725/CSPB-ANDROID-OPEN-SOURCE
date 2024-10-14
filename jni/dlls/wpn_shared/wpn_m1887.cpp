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
#include "wpn_m1887.h"

enum m3_e
{
	M3_IDLE,
	M3_FIRE1,
	M3_FIRE2,
M3_RELOAD,
M3_PUMP,
M3_START_RELOAD,
M3_DRAW, 
SMASH,
ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5
};

LINK_ENTITY_TO_CLASS(weapon_m1887,CM1887)

void CM1887::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_m1887");

	Precache();
	m_iId = WEAPON_M3;
	SET_MODEL(ENT(pev), "models/w_870mcs.mdl");
	m_iDefaultAmmo = M3_DEFAULT_GIVE;

	FallInit();
}

void CM1887::Precache(void)
{
		//ct

PRECACHE_MODEL("models/billflx/v_m1887.mdl");

	PRECACHE_MODEL("models/p_m1887.mdl");

	m_iShellId = m_iShell = PRECACHE_MODEL("models/shotgunshell.mdl");

PRECACHE_SOUND("weapons/m1887_hit_player.wav");

	PRECACHE_SOUND("weapons/m1887-1.wav");
	PRECACHE_SOUND("weapons/m3_insertshell.wav");
	PRECACHE_SOUND("weapons/m3_pump.wav");
	PRECACHE_SOUND("weapons/reload1.wav");
	PRECACHE_SOUND("weapons/reload3.wav");

	m_usFireM1887 = PRECACHE_EVENT(1, "events/m3.sc");
}

int CM1887::GetItemInfo(ItemInfo *p)
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


BOOL CM1887::Deploy(void)
{

m_fInSpecialReload = 0;

if (DefaultDeploy("models/billflx/v_m1887.mdl", "models/p_m1887.mdl", M3_DRAW, "shotgun", 0)) 

{
	m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.6;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.6;

	return TRUE;
}
	return FALSE;

}



void CM1887::QuickDeploy()
{
SendWeaponAnim(ANIM1, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CM1887::Holster(int skiplocal)
{
SetThink(nullptr);
}


void CM1887::SecondaryAttack(void)
{
	 #ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif
m_fInSpecialReload = 0;
SendWeaponAnim(SMASH, 0);
		
	SetThink(&CM1887::DelayedSecondaryAttack);
	pev->nextthink = gpGlobals->time + 0.61;

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.62;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.5;
}

void CM1887::DelayedSecondaryAttack()
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
		float flDamage = 200.0;

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
				EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/m1887_hit_player.wav", VOL_NORM, ATTN_NORM);
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
			switch (RANDOM_LONG(0, 2))
			{
			case 0: EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/m1887_hit_player.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3)); break;
			case 1: EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/m1887_hit_player.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3)); break;
			case 2: EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/m1887_hit_player.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3)); break;
			}
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

		SetThink(&CM1887::Smack);
		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;
	}

	return;
}

void CM1887::Smack(void)
{
	;
}

void CM1887::PrimaryAttack(void)
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

	m_pPlayer->m_iWeaponVolume = LOUD_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;

	m_iClip--;
	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif


SendWeaponAnim(M3_FIRE1, 0);
			

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

EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/m1887-1.wav", VOL_NORM, ATTN_NORM);




	PLAYBACK_EVENT_FULL(flags, ENT(m_pPlayer->pev),m_usFireM1887, 0, (float *)&g_vecZero, (float *)&g_vecZero, 0, 0, 0, 0, FALSE, FALSE);
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.5;
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
		m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomLong(m_pPlayer->random_seed + 1, 2, 2); //6
	else
		m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomLong(m_pPlayer->random_seed + 1, 2, 2); //11 8

	m_pPlayer->m_flEjectBrass = gpGlobals->time + 0.45;
}


void CM1887::DefaultReloadCall (void)
{
CLIENT_COMMAND(m_pPlayer->edict(), "QuickReload_client\n");
}

void CM1887::Reload(void)
{
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0 || m_iClip == M3_MAX_CLIP)
		return;
if (m_iClip == M3_MAX_CLIP)
return;
	if (m_flNextPrimaryAttack > UTIL_WeaponTimeBase())
		return;

SetThink(&CM1887::DefaultReloadCall);
pev->nextthink = gpGlobals->time + 0.01;

	if (!m_fInSpecialReload)
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif

SendWeaponAnim(M3_START_RELOAD, 0);

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
		m_flNextReload = UTIL_WeaponTimeBase() + 0.3;
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.3;
SendWeaponAnim(ANIM2, 0);
}
else
{
		m_flNextReload = UTIL_WeaponTimeBase() + 0.45;
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.45;
SendWeaponAnim(M3_RELOAD, 0);
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

void CM1887::QuickReload()
{
QuickReload_enable = TRUE;
}

void CM1887::WeaponIdle(void)
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


SendWeaponAnim(M3_PUMP, 0);
		
				m_fInSpecialReload = 0;
				m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.5;
			}
		}
		else
{

if (m_flTimeWeaponIdle < UTIL_WeaponTimeBase())
{

SendWeaponAnim(M3_IDLE, 0);
		
m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
}


}
	}
}

//============wood
LINK_ENTITY_TO_CLASS(weapon_m1887_w,CM1887_W)

void CM1887_W::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_m1887_w");

	Precache();
	m_iId = WEAPON_M3;
	SET_MODEL(ENT(pev), "models/w_870mcs.mdl");
	m_iDefaultAmmo = M3_DEFAULT_GIVE;

	FallInit();
}

void CM1887_W::Precache(void)
{
		//ct

PRECACHE_MODEL("models/billflx/v_m1887_w.mdl");

	PRECACHE_MODEL("models/p_m1887_w.mdl");

	m_iShellId = m_iShell = PRECACHE_MODEL("models/shotgunshell.mdl");

PRECACHE_SOUND("weapons/m1887_hit_player.wav");

	PRECACHE_SOUND("weapons/m1887-1.wav");
	PRECACHE_SOUND("weapons/m3_insertshell.wav");
	PRECACHE_SOUND("weapons/m3_pump.wav");
	PRECACHE_SOUND("weapons/reload1.wav");
	PRECACHE_SOUND("weapons/reload3.wav");

	m_usFireM1887 = PRECACHE_EVENT(1, "events/m3.sc");
}

int CM1887_W::GetItemInfo(ItemInfo *p)
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


BOOL CM1887_W::Deploy(void)
{

m_fInSpecialReload = 0;

if (DefaultDeploy("models/billflx/v_m1887_w.mdl", "models/p_m1887_w.mdl", M3_DRAW, "shotgun", 0)) 

{
	m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.6;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.6;

	return TRUE;
}
	return FALSE;
	
}



void CM1887_W::QuickDeploy()
{
SendWeaponAnim(ANIM1, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CM1887_W::Holster(int skiplocal)
{
SetThink(nullptr);
}


void CM1887_W::SecondaryAttack(void)
{
	 #ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif
m_fInSpecialReload = 0;
SendWeaponAnim(SMASH, 0);
		
	SetThink(&CM1887_W::DelayedSecondaryAttack);
	pev->nextthink = gpGlobals->time + 0.61;

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.62;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.5;
}

void CM1887_W::DelayedSecondaryAttack()
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
		float flDamage = 200.0;

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
				EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/m1887_hit_player.wav", VOL_NORM, ATTN_NORM);
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
			switch (RANDOM_LONG(0, 2))
			{
			case 0: EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/m1887_hit_player.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3)); break;
			case 1: EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/m1887_hit_player.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3)); break;
			case 2: EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/m1887_hit_player.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3)); break;
			}
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

		SetThink(&CM1887_W::Smack);
		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;
	}

	return;
}

void CM1887_W::Smack(void)
{
	;
}

void CM1887_W::PrimaryAttack(void)
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

	m_pPlayer->m_iWeaponVolume = LOUD_GUN_VOLUME;
	m_pPlayer->m_iWeaponFlash = BRIGHT_GUN_FLASH;

	m_iClip--;
	m_pPlayer->pev->effects |= EF_MUZZLEFLASH;
#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif


SendWeaponAnim(M3_FIRE1, 0);
			

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

EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/m1887-1.wav", VOL_NORM, ATTN_NORM);




	PLAYBACK_EVENT_FULL(flags, ENT(m_pPlayer->pev),m_usFireM1887, 0, (float *)&g_vecZero, (float *)&g_vecZero, 0, 0, 0, 0, FALSE, FALSE);
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.5;
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
		m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomLong(m_pPlayer->random_seed + 1, 2, 2); //6
	else
		m_pPlayer->pev->punchangle.x -= UTIL_SharedRandomLong(m_pPlayer->random_seed + 1, 2, 2); //11 8

	m_pPlayer->m_flEjectBrass = gpGlobals->time + 0.45;
}


void CM1887_W::DefaultReloadCall (void)
{
CLIENT_COMMAND(m_pPlayer->edict(), "QuickReload_client\n");
}

void CM1887_W::Reload(void)
{
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] <= 0 || m_iClip == M3_MAX_CLIP)
		return;
if (m_iClip == M3_MAX_CLIP)
return;
	if (m_flNextPrimaryAttack > UTIL_WeaponTimeBase())
		return;

SetThink(&CM1887_W::DefaultReloadCall);
pev->nextthink = gpGlobals->time + 0.01;

	if (!m_fInSpecialReload)
	{
#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_RELOAD);
#endif

SendWeaponAnim(M3_START_RELOAD, 0);

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
		m_flNextReload = UTIL_WeaponTimeBase() + 0.3;
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.3;
SendWeaponAnim(ANIM2, 0);
}
else
{
		m_flNextReload = UTIL_WeaponTimeBase() + 0.45;
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.45;
SendWeaponAnim(M3_RELOAD, 0);
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

void CM1887_W::QuickReload()
{
QuickReload_enable = TRUE;
}

void CM1887_W::WeaponIdle(void)
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


SendWeaponAnim(M3_PUMP, 0);
		
				m_fInSpecialReload = 0;
				m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1.5;
			}
		}
		else
{

if (m_flTimeWeaponIdle < UTIL_WeaponTimeBase())
{

SendWeaponAnim(M3_IDLE, 0);
		
m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
}


}
	}
}
