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
#include "wpn_medkit.h"

enum medkit_e
{
	medkit_IDLE,
	medkit_PULLPIN,
	medkit_THROW,
	medkit_DRAW
};

//medkit
#ifndef CLIENT_DLL
class CMed_Effect : public CBaseEntity
	{
	public:
		void Spawn() override
		{
			Precache();
			pev->classname = MAKE_STRING("medkit");

			SET_MODEL(this->edict(), "sprites/nautilus/heal.spr");

			EMIT_SOUND_DYN(this->edict(), CHAN_WEAPON, "nautilus/medkit_effect.wav", VOL_NORM, 1.3, 0, PITCH_NORM);

			pev->rendermode = kRenderTransAdd; // 5;
			pev->renderfx = kRenderFxNone;
			pev->renderamt = 100.0;
			pev->scale = 0.5;
			m_flMaxFrames = 17.0;
			m_iAttackStep = 45;
			flife = gpGlobals->time;
			SetThink(&CMed_Effect::OnThink);
			pev->nextthink = gpGlobals->time + 0.1;
			pev->framerate = 17;

			pev->solid = SOLID_BBOX; // 2
		}

		void Precache() override
		{
			PRECACHE_MODEL("sprites/nautilus/heal.spr");

		}

		void FireThink()
		{
			
		}
		void OnThink()
		{
			this->pev->frame = (float)(this->pev->framerate * gpGlobals->frametime / 1) + this->pev->frame;
			if (pev->frame > m_flMaxFrames)
			{
				pev->frame = fmod(pev->frame, m_flMaxFrames);
			}
			Vector origin = pev->origin;
			origin[2] = origin[2] - 20.0;
			if (g_engfuncs.pfnPointContents(origin) != CONTENTS_SOLID)
			{
				pev->origin[2] -= RANDOM_FLOAT(2.0, 3.0);
			}
			pev->nextthink = gpGlobals->time + 0.0099999998;
			m_iAttackStep += 1;
			if (m_iAttackStep == 60)
			{
				RadiusDamage(origin, FireDamage());
				m_iAttackStep = 0;
			}
			if (flife + 2.0 < gpGlobals->time)
				Remove();
		}

		float flife;
		int m_iAttackStep;
		float m_flMaxFrames;


	protected:
		void Remove()
		{
			SetThink(nullptr);
			pev->effects |= EF_NODRAW; // 0x80u
			return UTIL_Remove(this);
		}


		float FireDamage()
		{
			return 10.0f;
		}

		void RadiusDamage(Vector vecAiming, float flDamage)
		{
			float flRadius = 30.0f;
	
			const Vector vecSrc = vecAiming;
			entvars_t* const pevAttacker = VARS(pev->owner);
			entvars_t* const pevInflictor = this->pev;
			int bitsDamageType = DMG_FALL;

			TraceResult tr;
			const float falloff = flRadius ? flDamage / flRadius : 1;
			const int bInWater = (UTIL_PointContents(vecSrc) == CONTENTS_WATER);

			CBaseEntity* pEntity = NULL;
			while ((pEntity = UTIL_FindEntityInSphere(pEntity, vecSrc, flRadius)) != NULL)
			{
				if (pEntity->pev->takedamage != DAMAGE_NO)
				{
					if (bInWater && !pEntity->pev->waterlevel)
						continue;

					if (!bInWater && pEntity->pev->waterlevel == 3)
						continue;

					if (pEntity->IsBSPModel())
						continue;

					Vector vecSpot = pEntity->BodyTarget(vecSrc);
					UTIL_TraceLine(vecSrc, vecSpot, missile, ENT(pevInflictor), &tr);

					if (tr.flFraction == 1.0f || tr.pHit == pEntity->edict())
					{
						if (tr.fStartSolid)
						{
							tr.vecEndPos = vecSrc;
							tr.flFraction = 0;
						}
						float flAdjustedDamage = flDamage - (vecSrc - pEntity->pev->origin).Length() * falloff;
						flAdjustedDamage = Q_max(0, flAdjustedDamage);

						if (tr.flFraction == 1.0f)
						{
	//						pEntity->TakeDamage(pevInflictor, pevAttacker, flAdjustedDamage, bitsDamageType);
pEntity->TakeHealth(50, DMG_GENERIC);

						}
						else
						{
							//tr.iHitgroup = HITGROUP_CHEST;
							//ClearMultiDamage();
					//pEntity->TraceAttack(pevInflictor, flAdjustedDamage, (tr.vecEndPos - vecSrc).Normalize(), &tr, bitsDamageType);
							//ApplyMultiDamage(pevInflictor, pevAttacker);


pEntity->TakeHealth(50, DMG_GENERIC);
						}
					}
				}
			}

		}
	};

	LINK_ENTITY_TO_CLASS(medkit_effect, CMed_Effect);
#endif


//medkit
LINK_ENTITY_TO_CLASS(weapon_medkit, CMedkit)

void CMedkit::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_medkit");

	Precache();
	m_iId = WEAPON_SMOKEGRENADE;
	SET_MODEL(ENT(pev), "models/w_medkit.mdl");

	pev->dmg = 4;
	m_iDefaultAmmo = SMOKEGRENADE_DEFAULT_GIVE;
	m_flStartThrow = 0;
	m_flReleaseThrow = -1;
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

	FallInit();
}

void CMedkit::Precache(void)
{
	PRECACHE_MODEL("models/billflx/v_medkit.mdl");
PRECACHE_MODEL("models/w_medkit.mdl");
	PRECACHE_MODEL("models/p_molotov.mdl");
	PRECACHE_SOUND("weapons/molotov-1.wav");
	PRECACHE_SOUND("weapons/molotov-2.wav");
	PRECACHE_SOUND("weapons/molotov_hit1.wav");
	PRECACHE_SOUND("weapons/molotov_hit2.wav");
	PRECACHE_SOUND("weapons/molotov_hit3.wav");
#ifdef ENABLE_SHIELD
	PRECACHE_MODEL("models/shield/v_shield_smokegrenade.mdl");
#endif
m_usCreateMedkit = PRECACHE_EVENT(1, "events/createMedkit.sc");

}

int CMedkit::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "SmokeGrenade";
	p->iMaxAmmo1 = MAX_AMMO_SMOKEGRENADE;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = WEAPON_NOCLIP;
	p->iSlot = 3;
	p->iPosition = 3;
	p->iId = WEAPON_SMOKEGRENADE;
	p->iWeight = SMOKEGRENADE_WEIGHT;
	p->iFlags = ITEM_FLAG_LIMITINWORLD | ITEM_FLAG_EXHAUSTIBLE;

	return 1;
}

BOOL CMedkit::Deploy(void)
{

	m_flReleaseThrow = -1;
	m_fMaxSpeed = 250;

if (DefaultDeploy("models/billflx/v_medkit.mdl", "models/p_medkit.mdl", MOLLY_DRAW, "grenade", 0))

{
	m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.8;

m_flNextSecondaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
	
	return TRUE;
	}
	return FALSE;
}

void CMedkit::Holster(int skiplocal)
{
	if (!m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
	{
		m_pPlayer->pev->weapons &= ~(1 << WEAPON_SMOKEGRENADE);
		DestroyItem();
	}

	m_flStartThrow = 0;
	m_flReleaseThrow = -1;
}

void CMedkit::PrimaryAttack(void)
{
	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
		return;

	if (!m_flStartThrow && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] > 0)
	{
		m_flStartThrow = gpGlobals->time;
		m_flReleaseThrow = 0;
		SendWeaponAnim(MOLLY_PINPULL, UseDecrement() != FALSE);
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.5;
	}
}

void CMedkit::SetPlayerShieldAnim(void)
{
	if (m_pPlayer->HasShield() == true)
	{
		if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
			strcpy(m_pPlayer->m_szAnimExtention, "shield");
		else
			strcpy(m_pPlayer->m_szAnimExtention, "shieldgren");
	}
}

void CMedkit::ResetPlayerShieldAnim(void)
{
	if (m_pPlayer->HasShield() == true)
	{
		if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
			strcpy(m_pPlayer->m_szAnimExtention, "shieldgren");
	}
}

bool CMedkit::ShieldSecondaryFire(int up_anim, int down_anim)
{
	;
}

void CMedkit::SecondaryAttack(void)
{
		;
}

void CMedkit::WeaponIdle(void)
{
	if (!m_flReleaseThrow && m_flStartThrow)
		m_flReleaseThrow = gpGlobals->time;

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;


if (m_flStartThrow)
	{

		Vector angThrow = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;

		if (angThrow.x < 0)
			angThrow.x = -10 + angThrow.x * ((90 - 10) / 90.0);
		else
			angThrow.x = -10 + angThrow.x * ((90 + 10) / 90.0);

		float flVel = (90 - angThrow.x) * 2;

		if (flVel > 750)
			flVel = 750;

		UTIL_MakeVectors(angThrow);
		Vector vecSrc = m_pPlayer->pev->origin + m_pPlayer->pev->view_ofs + gpGlobals->v_forward;
		Vector vecThrow = gpGlobals->v_forward * flVel + m_pPlayer->pev->velocity;
		float time = 2;

CGrenade::ShootMedkit(m_pPlayer->pev, vecSrc, vecThrow, time, m_usCreateMedkit);

		SetPlayerShieldAnim();

#ifndef CLIENT_DLL
		m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif
		m_flStartThrow = 0;
		m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.5;
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.75;
		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]--;

		if (!m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
			m_flTimeWeaponIdle = m_flNextSecondaryAttack = m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.5;

		ResetPlayerShieldAnim();
		return;
	}
	else if (m_flReleaseThrow > 0)
	{
		m_flStartThrow = 0;


		if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
		{
			SendWeaponAnim(MOLLY_DRAW, UseDecrement() != FALSE);
			m_flReleaseThrow = 0;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 10;
		}
		else
			RetireWeapon();

		return;
	}

	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
	{
		if (m_pPlayer->HasShield() != false)
		{
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20.0;

			if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
				SendWeaponAnim(SHIELDREN_IDLE, UseDecrement() != FALSE);

			return;
		}

		int iAnim;
		float flRand = RANDOM_FLOAT(0, 1);

		if (flRand <= 0.75)
		{
			iAnim = MOLLY_IDLE;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 10;
		}
		else
		{
			iAnim = MOLLY_IDLE;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 75.0 / 30.0;
		}

		SendWeaponAnim(iAnim, UseDecrement() != FALSE);
	}

}

BOOL CMedkit::CanDeploy(void)
{
	return m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] != 0;
}
