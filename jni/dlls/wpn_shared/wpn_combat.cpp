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
#include "wpn_combat.h"

#ifndef CLIENT_DLL
#include "gamemode/mods.h"
#endif

#define KNIFE_BODYHIT_VOLUME 128
#define KNIFE_WALLHIT_VOLUME 512

LINK_ENTITY_TO_CLASS(weapon_combat,CCombat)

enum combat_e
{
	KNIFE_IDLE,
	KNIFE_ATTACK1HIT,
	KNIFE_ATTACK2HIT,
	KNIFE_DRAW,
	KNIFE_STABHIT,
	KNIFE_STABMISS,
	KNIFE_MIDATTACK1HIT,
	KNIFE_MIDATTACK2HIT,
ANIM1,
ANIM2,
ANIM3,
ANIM4,
};

enum knife_shield_e
{
	KNIFE_SHIELD_IDLE,
	KNIFE_SHIELD_SLASH,
	KNIFE_SHIELD_ATTACKHIT,
	KNIFE_SHIELD_DRAW,
	KNIFE_SHIELD_UPIDLE,
	KNIFE_SHIELD_UP,
	KNIFE_SHIELD_DOWN
};

void CCombat::Spawn(void)
{
	Precache();
	m_iId = WEAPON_KNIFE;
	SET_MODEL(ENT(pev), "models/w_knife.mdl");

	m_iClip = WEAPON_NOCLIP;
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

	FallInit();
}

void CCombat::Precache(void)
{
	
PRECACHE_MODEL("models/billflx/v_combat_machete.mdl");

#ifdef ENABLE_SHIELD
	PRECACHE_MODEL("models/shield/v_shield_knife.mdl");
#endif
	PRECACHE_MODEL("models/p_combat_machete.mdl");

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

int CCombat::GetItemInfo(ItemInfo *p)
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

BOOL CCombat::Deploy(void)
{
	m_fMaxSpeed = 250;
	m_iSwing = 0;
	
		
return DefaultDeploy("models/billflx/v_combat_machete.mdl", "models/p_combat_machete.mdl", KNIFE_DRAW, "knife", 0);


}

void CCombat::QuickDeploy()
{
SendWeaponAnim(ANIM4, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CCombat::Holster(int skiplocal)
{
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 4;
SetThink(nullptr);
}

void CCombat::WeaponAnimation(int iAnimation)
{
	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, ENT(m_pPlayer->pev), m_usCombat, 0, (float *)&g_vecZero, (float *)&g_vecZero, 0, 0, iAnimation, 2, 3, 4);
}

void FindHullIntersectionCombat(const Vector &vecSrc, TraceResult &tr, float *pflMins, float *pfkMaxs, edict_t *pEntity)
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

void CCombat::PrimaryAttack(void)
{
	
#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif
	SendWeaponAnim(KNIFE_MIDATTACK1HIT, UseDecrement() != FALSE);

	SetThink(&CCombat::DelayedPrimaryAttack);
	pev->nextthink = gpGlobals->time + 0.56;

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.4;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;
}



void CCombat::DelayedPrimaryAttack()
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
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.56;
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;

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

m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.56;
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;
}
#endif
		m_trHit = tr;
		m_pPlayer->m_iWeaponVolume = flVol * KNIFE_WALLHIT_VOLUME;

		SetThink(&CCombat::Smack);
		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;
	}

	return;
}


void CCombat::SetPlayerShieldAnim(void)
{
	;
}

void CCombat::ResetPlayerShieldAnim(void)
{
	;
}

bool CCombat::ShieldSecondaryFire(int up_anim, int down_anim)
{
	;
}

void CCombat::SecondaryAttack(void)
{
	#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif

	SendWeaponAnim(KNIFE_STABHIT, UseDecrement() != FALSE);

if (m_iId == WEAPON_KNIFE)
{
	SetThink(&CCombat::DelayedSecondaryAttack2);
pev->nextthink = gpGlobals->time + 0.52;
}
else 
{
SetThink(&CCombat::Smack);
pev->nextthink = gpGlobals->time + 0.00001;
}

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.4;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;

}


void CCombat::DelayedSecondaryAttack()
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
			
	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.69;
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.7;



		}
	}
	else
	{
		fDidHit = TRUE;

		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.69;
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.7;

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

m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.69;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.7;
}
#endif
		m_trHit = tr;
		m_pPlayer->m_iWeaponVolume = flVol * KNIFE_WALLHIT_VOLUME;

	}

	return;
}

void CCombat::DelayedSecondaryAttack2()
{

SetThink(&CCombat::DelayedSecondaryAttack);
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
			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.79;
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;


		}
	}
	else
	{
		fDidHit = TRUE;


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

m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.79;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;

}
#endif
		m_trHit = tr;
		m_pPlayer->m_iWeaponVolume = flVol * KNIFE_WALLHIT_VOLUME;

	}

	return;
}

void CCombat::Smack(void)
{
	;
}

void CCombat::SwingAgain(void)
{
	Swing(FALSE);
}

void CCombat::WeaponIdle(void)
{
	ResetEmptySound();
 	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	if (m_pPlayer->m_bShieldDrawn != true)
	{
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
		SendWeaponAnim(KNIFE_IDLE, UseDecrement() != FALSE);
	}
}

int CCombat::Swing(int fFirst)
{
	;
}

int CCombat::Stab(int fFirst)
{
	;
}
