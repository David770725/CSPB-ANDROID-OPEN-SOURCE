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
#include "wpn_arabian_sword.h"

#ifndef CLIENT_DLL
#include "gamemode/mods.h"
#endif

#define KNIFE_BODYHIT_VOLUME 128
#define KNIFE_WALLHIT_VOLUME 512

LINK_ENTITY_TO_CLASS(weapon_arabian_sword, CArabian_sword)

enum amok_e
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
ANIM4
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

void CArabian_sword::Spawn(void)
{
	Precache();
	m_iId = WEAPON_KNIFE;
	SET_MODEL(ENT(pev), "models/w_knife.mdl");

	m_iClip = WEAPON_NOCLIP;
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

	FallInit();
}

void CArabian_sword::Precache(void)
{
PRECACHE_MODEL("models/billflx/v_arabian_sword.mdl");


#ifdef ENABLE_SHIELD
	PRECACHE_MODEL("models/shield/v_shield_knife.mdl");
#endif
	PRECACHE_MODEL("models/p_arabian_sword.mdl");

	PRECACHE_SOUND("weapons/arabian_sword_draw.wav");
	PRECACHE_SOUND("weapons/knife_hit1.wav");
	PRECACHE_SOUND("weapons/knife_hit2.wav");
	PRECACHE_SOUND("weapons/knife_hit3.wav");
	PRECACHE_SOUND("weapons/knife_hit4.wav");
	PRECACHE_SOUND("weapons/knife_slash1.wav");
	PRECACHE_SOUND("weapons/knife_slash2.wav");
	PRECACHE_SOUND("weapons/knife_stab.wav");
	PRECACHE_SOUND("weapons/knife_hitwall1.wav");

PRECACHE_SOUND("weapons/arabian_sword_hit.wav");


	m_usArabian_sword = PRECACHE_EVENT(1, "events/Arabian_sword.sc");
}

int CArabian_sword::GetItemInfo(ItemInfo *p)
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

BOOL CArabian_sword::Deploy(void)
{

	m_fMaxSpeed = 250;
	m_iSwing = 0;
	
		
return DefaultDeploy("models/billflx/v_arabian_sword.mdl", "models/p_arabian_sword.mdl", KNIFE_DRAW, "kukri", 0);
}

void CArabian_sword::QuickDeploy()
{
SendWeaponAnim(ANIM4, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

void CArabian_sword::Holster(int skiplocal)
{
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 4;
SetThink(nullptr);
}

void CArabian_sword::WeaponAnimation(int iAnimation)
{
	int flags;
#ifdef CLIENT_WEAPONS
	flags = FEV_NOTHOST;
#else
	flags = 0;
#endif

	PLAYBACK_EVENT_FULL(flags, ENT(m_pPlayer->pev), m_usArabian_sword, 0, (float *)&g_vecZero, (float *)&g_vecZero, 0, 0, iAnimation, 2, 3, 4);
}

void FindHullIntersectionArabian_sword(const Vector &vecSrc, TraceResult &tr, float *pflMins, float *pfkMaxs, edict_t *pEntity)
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

void CArabian_sword::PrimaryAttack(void)
{
	
#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif
	SendWeaponAnim(KNIFE_MIDATTACK1HIT, UseDecrement() != FALSE);

	//SetThink(&CArabian_sword::DelayedPrimaryAttack);
	//pev->nextthink = gpGlobals->time + 0.85;

SetThink(&CArabian_sword::DelayedPrimaryAttack);
	pev->nextthink = gpGlobals->time + 0.55;

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.4;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;
//m_tPreTime = gpGlobals->time + 0.4;
}


void CArabian_sword::afterprim()
{
	/*if (m_pPlayer->pev->button & IN_ATTACK)
	{
		if(m_tPreTime < gpGlobals->time)
		{

DelayedPrimaryAttack();

			SetThink(nullptr);
		}
		else
		{
			m_pPlayer->pev->button &= ~IN_ATTACK;
			pev->nextthink = gpGlobals->time + 0.01;
		}
	}
	else
	{
		SetThink(nullptr);
SendWeaponAnim(KNIFE_IDLE, 0);
		m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + gpGlobals->time - m_tPreTime;
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.02;
	}
*/
}

void CArabian_sword::DelayedPrimaryAttack()
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
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;

		

		}
	}
	else
	{
		fDidHit = TRUE;

#ifndef CLIENT_DLL
		
#endif
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.69;
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;

		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);


		float flDamage = 50.0;

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
				EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/arabian_sword_hit.wav", VOL_NORM, ATTN_NORM);
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
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;
}
#endif
		m_trHit = tr;
		m_pPlayer->m_iWeaponVolume = flVol * KNIFE_WALLHIT_VOLUME;

	}

	return;
}


void CArabian_sword::SetPlayerShieldAnim(void)
{
	;
}

void CArabian_sword::ResetPlayerShieldAnim(void)
{
	;
}

bool CArabian_sword::ShieldSecondaryFire(int up_anim, int down_anim)
{
	;
}

void CArabian_sword::SecondaryAttack(void)
{
	#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK2);
#endif
	SendWeaponAnim(KNIFE_STABHIT, UseDecrement() != FALSE);

	SetThink(&CArabian_sword::DelayedSecondaryAttack);
	pev->nextthink = gpGlobals->time + 0.65;

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.4;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;

//m_tPreTime = gpGlobals->time + 0.4;
}

void CArabian_sword::aftersecond()
{
	/*if (m_pPlayer->pev->button & IN_ATTACK2)
	{
		if(m_tPreTime < gpGlobals->time)
		{

DelayedSecondaryAttack();

			SetThink(nullptr);
		}

else
{
			m_pPlayer->pev->button &= ~IN_ATTACK2;
			pev->nextthink = gpGlobals->time + 0.01;
}
	}


	else
	{
		SetThink(nullptr);
SendWeaponAnim(KNIFE_IDLE, 0);
		m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + gpGlobals->time - m_tPreTime;
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.02;
	}
*/
}

void CArabian_sword::DelayedSecondaryAttack()
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
		m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.1;

		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);

		float flDamage = 80.0;

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
				EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/arabian_sword_hit.wav", VOL_NORM, ATTN_NORM);
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
}
#endif

		m_trHit = tr;
		m_pPlayer->m_iWeaponVolume = flVol * KNIFE_WALLHIT_VOLUME;

		SetThink(&CArabian_sword::Smack);
		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;
	}

	return;
}


void CArabian_sword::Smack(void)
{
	;
}

void CArabian_sword::SwingAgain(void)
{
	Swing(FALSE);
}

void CArabian_sword::WeaponIdle(void)
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

int CArabian_sword::Swing(int fFirst)
{
	BOOL fDidHit = FALSE;
	UTIL_MakeVectors(m_pPlayer->pev->v_angle);
	Vector vecSrc = m_pPlayer->GetGunPosition();
	Vector vecEnd = vecSrc + gpGlobals->v_forward * 48;

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
		if (fFirst)
		{
			if (m_pPlayer->HasShield() == false)
			{
				switch ((m_iSwing++) % 2)
				{
					case 0: SendWeaponAnim(KNIFE_MIDATTACK1HIT, UseDecrement() != FALSE); break;
					case 1: SendWeaponAnim(KNIFE_MIDATTACK2HIT, UseDecrement() != FALSE); break;
				}

				m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.35;
				m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5;
			}
			else
			{
				SendWeaponAnim(KNIFE_SHIELD_ATTACKHIT, UseDecrement() != FALSE);

				m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.0;
				m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.2;
			}

			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;

			if (RANDOM_LONG(0, 1))
				EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/knife_slash1.wav", VOL_NORM, ATTN_NORM, 0, 94);
			else
				EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/knife_slash2.wav", VOL_NORM, ATTN_NORM, 0, 94);

		}
	}
	else
	{
		fDidHit = TRUE;

		if (m_pPlayer->HasShield() == false)
		{
			switch ((m_iSwing++) % 2)
			{
				case 0: SendWeaponAnim(KNIFE_MIDATTACK1HIT, UseDecrement() != FALSE); break;
				case 1: SendWeaponAnim(KNIFE_MIDATTACK2HIT, UseDecrement() != FALSE); break;
			}

			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.4;
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.5;
		}
		else
		{
			SendWeaponAnim(KNIFE_SHIELD_ATTACKHIT, UseDecrement() != FALSE);

			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1.0;
			m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1.2;
		}

		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 2;

		CBaseEntity *pEntity = CBaseEntity::Instance(tr.pHit);
		SetPlayerShieldAnim();

#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif
		ClearMultiDamage();
		if (pEntity)
		{
			float flDamage = 15;
			if (m_flNextPrimaryAttack + 0.4 < UTIL_WeaponTimeBase())
				flDamage = 20;

#ifndef CLIENT_DLL
			if (g_pModRunning->DamageTrack() == DT_ZB)
				flDamage *= 9.5f;
			else if (g_pModRunning->DamageTrack() == DT_ZBS)
				flDamage *= 5.5f;
#endif

			pEntity->TraceAttack(m_pPlayer->pev, flDamage, gpGlobals->v_forward, &tr, DMG_NEVERGIB | DMG_BULLET);
		}
		ApplyMultiDamage(m_pPlayer->pev, m_pPlayer->pev);

		float flVol = 1;
#ifndef CLIENT_DLL
		int fHitWorld = TRUE;
#endif
		if (pEntity)
		{
			if (pEntity->Classify() != CLASS_NONE && pEntity->Classify() != CLASS_MACHINE)
			{
				switch (RANDOM_LONG(0, 3))
				{
					case 0: EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/knife_hit1.wav", VOL_NORM, ATTN_NORM); break;
					case 1: EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/knife_hit2.wav", VOL_NORM, ATTN_NORM); break;
					case 2: EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/knife_hit3.wav", VOL_NORM, ATTN_NORM); break;
					case 3: EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "weapons/knife_hit4.wav", VOL_NORM, ATTN_NORM); break;
				}

				m_pPlayer->m_iWeaponVolume = KNIFE_BODYHIT_VOLUME;

				if (!pEntity->IsAlive())
					return TRUE;

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
			EMIT_SOUND_DYN(ENT(m_pPlayer->pev), CHAN_ITEM, "weapons/knife_hitwall1.wav", VOL_NORM, ATTN_NORM, 0, 98 + RANDOM_LONG(0, 3));
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

		SetThink(&CArabian_sword::Smack);
		pev->nextthink = UTIL_WeaponTimeBase() + 0.2;
		SetPlayerShieldAnim();
	}

	return fDidHit;
}

int CArabian_sword::Stab(int fFirst)
{
	;
}
