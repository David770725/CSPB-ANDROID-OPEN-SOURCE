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
#include "wpn_saber.h"

#ifndef CLIENT_DLL
#include "gamemode/mods.h"
#endif

#define KNIFE_BODYHIT_VOLUME 128
#define KNIFE_WALLHIT_VOLUME 512

LINK_ENTITY_TO_CLASS(weapon_saber,CSaber)

enum combat_e
{

KNIFE_IDLE,
	KNIFE_DRAW,
	KNIFE_SLASH,
	KNIFE_STAB,
	KNIFE_START,
	KNIFE_WALK,
	KNIFE_END,
ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5
};


void CSaber::Spawn(void)
{
	Precache();
	m_iId = WEAPON_KNIFE;
	SET_MODEL(ENT(pev), "models/w_knife.mdl");

	m_iClip = WEAPON_NOCLIP;
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

	FallInit();
}

void CSaber::Precache(void)
{
	
PRECACHE_MODEL("models/billflx/v_saber.mdl");

#ifdef ENABLE_SHIELD
	PRECACHE_MODEL("models/shield/v_shield_knife.mdl");
#endif
	PRECACHE_MODEL("models/p_saber.mdl");

	PRECACHE_SOUND("weapons/combat_machete_draw.wav");
	PRECACHE_SOUND("weapons/knife_hit1.wav");
	PRECACHE_SOUND("weapons/knife_hit2.wav");
	PRECACHE_SOUND("weapons/knife_hit3.wav");
	PRECACHE_SOUND("weapons/knife_hit4.wav");
	PRECACHE_SOUND("weapons/knife_slash1.wav");
	PRECACHE_SOUND("weapons/knife_slash2.wav");
	PRECACHE_SOUND("weapons/knife_stab.wav");
	PRECACHE_SOUND("weapons/knife_hitwall1.wav");

PRECACHE_SOUND("weapons/combat_machete_hit_stab_2.wav");
PRECACHE_SOUND("weapons/combat_machete_hit_stab_1.wav");
	m_usCombat = PRECACHE_EVENT(1, "events/combat.sc");
}

int CSaber::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = " 762nato";
	p->iMaxAmmo1 = -1;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = AK47_MAX_CLIP;
	p->iSlot = 2;
	p->iPosition = 1;
	p->iId = WEAPON_KNIFE;
	p->iFlags = 0;
	p->iWeight = KNIFE_WEIGHT;

	return 1;
}


BOOL CSaber::Deploy(void)
{

ResetRunIdle();
m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1;

m_fMaxSpeed = 250;

if ( DefaultDeploy("models/billflx/v_saber.mdl", "models/p_saber.mdl", KNIFE_DRAW, "kukri", 0));

{
	m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.8;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.8;
	
	return TRUE;
	}
	return FALSE;
		
}


void CSaber::QuickDeploy()
{
SendWeaponAnim(ANIM1, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}
	


void CSaber::Holster(int skiplocal)
{
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 4;
SetThink(nullptr);
}

void CSaber::WeaponAnimation(int iAnimation)
{
	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, ENT(m_pPlayer->pev), m_usCombat, 0, (float *)&g_vecZero, (float *)&g_vecZero, 0, 0, iAnimation, 2, 3, 4);
}

void FindHullIntersectionSaber(const Vector &vecSrc, TraceResult &tr, float *pflMins, float *pfkMaxs, edict_t *pEntity)
{
	TraceResult trTemp;
	float flDistance = 1000000;
	float *pflMinMaxs[2] = { pflMins, pfkMaxs };
	Vector vecHullEnd = tr.vecEndPos;

	vecHullEnd = vecSrc + ((vecHullEnd - vecSrc) * 2);
	TRACE_LINE(vecSrc, vecHullEnd, dont_ignore_monsters, pEntity, &trTemp);

	if (trTemp.flFraction < 1)
	{
		tr = trTemp;
		return;
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				Vector vecEnd;
				vecEnd.x = vecHullEnd.x + pflMinMaxs[i][0];
				vecEnd.y = vecHullEnd.y + pflMinMaxs[j][1];
				vecEnd.z = vecHullEnd.z + pflMinMaxs[k][2];

				TRACE_LINE(vecSrc, vecEnd, dont_ignore_monsters, pEntity, &trTemp);

				if (trTemp.flFraction < 1)
				{
					float flThisDistance = (trTemp.vecEndPos - vecSrc).Length();

					if (flThisDistance < flDistance)
					{
						tr = trTemp;
						flDistance = flThisDistance;
					}
				}
			}
		}
	}
}

void CSaber::PrimaryAttack(void)
{

#ifndef CLIENT_DLL
			m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif

SendWeaponAnim(KNIFE_SLASH, 0);
SetThink(&CSaber::slash);
	pev->nextthink = gpGlobals->time + 0.000000009;
}



void CSaber::DelayedPrimaryAttack()
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
			
			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.56;
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;

		}
	}
	else
	{
		fDidHit = TRUE;

#ifndef CLIENT_DLL
		
#endif
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.1;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.1;

		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);

		float flDamage = 20.0;

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
				EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/combat_machete_hit_stab_2.wav", VOL_NORM, ATTN_NORM);
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
			case 0: EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/knife_hitwall1.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3)); break;
			case 1: EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/knife_hitwall1.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3)); break;
			case 2: EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/knife_hitwall1.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3)); break;
			}
		}
#endif

		m_trHit = tr;
		m_pPlayer->m_iWeaponVolume = flVol * KNIFE_WALLHIT_VOLUME;

		SetThink(&CSaber::Smack);
		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;
	}

	return;
}


void CSaber::SetPlayerShieldAnim(void)
{
	;
}

void CSaber::ResetPlayerShieldAnim(void)
{
	;
}

bool CSaber::ShieldSecondaryFire(int up_anim, int down_anim)
{
	;
}

void CSaber::slash(void)
{

#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif

SendWeaponAnim(KNIFE_SLASH, 0);


SetThink(&CSaber::DelayedPrimaryAttack);
	pev->nextthink = gpGlobals->time + 0.20;

ResetRunIdle();
	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 1;
}

void CSaber::stab(void)
{

#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif
	SetThink(&CSaber::DelayedSecondaryAttack2);
pev->nextthink = gpGlobals->time + 0.25;

SendWeaponAnim(KNIFE_STAB, 0);

}

void CSaber::SecondaryAttack(void)
{

	SetThink(&CSaber::stab);
pev->nextthink = gpGlobals->time + 0.00000009;
m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;
SendWeaponAnim(KNIFE_STAB, 0);
}



void CSaber::DelayedSecondaryAttack()
{

SetThink(&CSaber::ResetRunIdle);
pev->nextthink = gpGlobals->time + 0.00000009;

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
			
	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.92;
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;

		}
	}
	else
	{
		fDidHit = TRUE;

		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.1;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.1;

		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);

		float flDamage = 60.0;

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
				EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/combat_machete_hit_stab_2.wav", VOL_NORM, ATTN_NORM);
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
			case 0: EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/knife_hitwall1.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3)); break;
			case 1: EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/knife_hitwall1.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3)); break;
			case 2: EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/knife_hitwall1.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3)); break;
			}
		}
#endif

		m_trHit = tr;
		m_pPlayer->m_iWeaponVolume = flVol * KNIFE_WALLHIT_VOLUME;

		SetThink(&CSaber::Smack);
		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;
	}

	return;
}

void CSaber::DelayedSecondaryAttack2()
{

SetThink(&CSaber::DelayedSecondaryAttack);
pev->nextthink = gpGlobals->time + 0.5;

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
			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.92;
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;


		}
	}
	else
	{
		fDidHit = TRUE;


#ifndef CLIENT_DLL
		
#endif

		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.1;
		//m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.1;

		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);



		float flDamage = 30.0;

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
				EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/combat_machete_hit_stab_2.wav", VOL_NORM, ATTN_NORM);
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
			case 0: EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/knife_hitwall1.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3)); break;
			case 1: EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/knife_hitwall1.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3)); break;
			case 2: EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/knife_hitwall1.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3)); break;
			}
		}
#endif

		m_trHit = tr;
		m_pPlayer->m_iWeaponVolume = flVol * KNIFE_WALLHIT_VOLUME;

		/*SetThink(&CSaber::Smack);
		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;*/

	}

	return;
}

void CSaber::Smack(void)
{
	;
}

void CSaber::SwingAgain(void)
{
	Swing(FALSE);
}

void CSaber::start(void)
{
	SendWeaponAnim(KNIFE_START, 0);
}

void CSaber::walk(void)
{
	SendWeaponAnim(KNIFE_WALK, 0);
}

void CSaber::end(void)
{
	SendWeaponAnim(KNIFE_END, 0);
}

void CSaber::idle(void)
{
	SendWeaponAnim(KNIFE_IDLE, 0);
}

void CSaber::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;
	if (m_flTimeWeaponIdle < UTIL_WeaponTimeBase())
	{
		if (m_pPlayer->pev->button & IN_FORWARD)
		{
			if (pev->iuser2)
			{
				//SendWeaponAnim(KNIFE_START, 0);
SetThink(&CSaber::start);
pev->nextthink = gpGlobals->time + 0.00001;
				pev->iuser2 = 0;
				m_flNextRunIdle = gpGlobals->time;
				m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.33;
				return;
			}
			else if (m_flNextRunIdle <= gpGlobals->time)
			{
				//SendWeaponAnim(KNIFE_WALK, 0);
SetThink(&CSaber::walk);
pev->nextthink = gpGlobals->time + 0.00001;

				m_flNextRunIdle = gpGlobals->time + 0.57;
		}
			m_flNextRunEnd = gpGlobals->time;
	}
		//

else if (m_pPlayer->pev->button & IN_BACK)
		{
			if (pev->iuser2)
			{
				//SendWeaponAnim(KNIFE_START, 0);
SetThink(&CSaber::start);
pev->nextthink = gpGlobals->time + 0.00001;
				pev->iuser2 = 0;
				m_flNextRunIdle = gpGlobals->time;
				m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.33;
				return;
			}
			else if (m_flNextRunIdle <= gpGlobals->time)
			{
				//SendWeaponAnim(KNIFE_WALK, 0);
SetThink(&CSaber::walk);
pev->nextthink = gpGlobals->time + 0.00001;

				m_flNextRunIdle = gpGlobals->time + 0.57;
		}
			m_flNextRunEnd = gpGlobals->time;
	}

else if (m_pPlayer->pev->button & IN_MOVELEFT)
		{
			if (pev->iuser2)
			{
				//SendWeaponAnim(KNIFE_START, 0);
SetThink(&CSaber::start);
pev->nextthink = gpGlobals->time + 0.00001;
				pev->iuser2 = 0;
				m_flNextRunIdle = gpGlobals->time;
				m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.33;
				return;
			}
			else if (m_flNextRunIdle <= gpGlobals->time)
			{
				//SendWeaponAnim(KNIFE_WALK, 0);
SetThink(&CSaber::walk);
pev->nextthink = gpGlobals->time + 0.00001;

				m_flNextRunIdle = gpGlobals->time + 0.57;
		}
			m_flNextRunEnd = gpGlobals->time;
	}


else if (m_pPlayer->pev->button & IN_MOVERIGHT)
		{
			if (pev->iuser2)
			{
				//SendWeaponAnim(KNIFE_START, 0);
SetThink(&CSaber::start);
pev->nextthink = gpGlobals->time + 0.00001;
				pev->iuser2 = 0;
				m_flNextRunIdle = gpGlobals->time;
				m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.33;
				return;
			}
			else if (m_flNextRunIdle <= gpGlobals->time)
			{
				//SendWeaponAnim(KNIFE_WALK, 0);
SetThink(&CSaber::walk);
pev->nextthink = gpGlobals->time + 0.00001;

				m_flNextRunIdle = gpGlobals->time + 0.57;
		}
			m_flNextRunEnd = gpGlobals->time;
	}

               else
	{
			if (!pev->iuser2)
			{
				//SendWeaponAnim(KNIFE_END, 0);
SetThink(&CSaber::end);
pev->nextthink = gpGlobals->time + 0.00001;
				pev->iuser2 = 1;
				m_flNextRunEnd = gpGlobals->time;
				m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.3;
				return;
			}
			else if( m_flNextRunEnd<= gpGlobals->time)
			{
				SetThink(&CSaber::idle);
pev->nextthink = gpGlobals->time + 0.00001;
				m_flNextRunEnd = gpGlobals->time + 3.0;
			}
			m_flNextRunIdle = gpGlobals->time;
		}

//


//

	}


}

void CSaber::ResetRunIdle()
{
	pev->iuser2 = 1;
	m_flNextRunIdle = m_flNextRunEnd = gpGlobals->time;
}

int CSaber::Swing(int fFirst)
{
	;
}

int CSaber::Stab(int fFirst)
{
	;
}
