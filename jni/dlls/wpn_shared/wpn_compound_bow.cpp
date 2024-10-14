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
#include "wpn_compound_bow.h"
#ifndef CLIENT_DLL
#include "effects.h"
#include "customentity.h"
#include "monsters.h"
#endif

#include <vector>
#include <array>

#ifndef CLIENT_DLL
	Vector Get_Velocity_Angle(CBaseEntity *pEntity, Vector Output)
	{
		pEntity->pev->velocity;
		Output = UTIL_VecToAngles(pEntity->pev->velocity);
		if (Output[0] > 90.0)
			Output[0] = -(360.0 - Output[0]);
		return Output;
	}

	Vector Stock_Get_Velocity_Angle(Vector In, Vector Output)
	{
		Output = UTIL_VecToAngles(In);
		if (Output[0] > 90.0)
			Output[0] = -(360.0 - Output[0]);
		return Output;
	}
#endif



#ifndef CLIENT_DLL
	class CBowArrow : public CBaseEntity
	{
	public:
		void Spawn() override
		{
			Precache();

			SET_MODEL(this->edict(), "models/arrow.mdl");
			SetThink(&CBowArrow::OnThink);
			SetTouch(&CBowArrow::OnTouch);
			pev->mins = { -0.1, -0.1, -0.1 };
			pev->maxs = { 0.1, 0.1, 0.1 };
			pev->rendermode = kRenderTransAdd; // 5;
			pev->renderfx = kRenderFxNone;
			pev->renderamt = 230.0;		
			pev->nextthink = gpGlobals->time + 0.15;
			pev->framerate = 1;
			pev->solid = SOLID_BBOX; // 2
			pev->movetype = MOVETYPE_FLY; // 9

			pev->classname = MAKE_STRING("d_arrow");
		}

		void EXPORT OnTouch(CBaseEntity *pOther)
		{
			if (pev->owner == pOther->edict())
				return;
			pev->solid = SOLID_NOT;

			int DECAL_SHOT[5];
			DECAL_SHOT[0] = DECAL_INDEX("{shot1");
			DECAL_SHOT[1] = DECAL_INDEX("{shot2");
			DECAL_SHOT[2] = DECAL_INDEX("{shot3");
			DECAL_SHOT[3] = DECAL_INDEX("{shot4");
			DECAL_SHOT[4] = DECAL_INDEX("{shot5");


			Vector vecStart,vecAngle,vecForw,vecEnd;
			vecStart = pev->origin;
			vecAngle = Get_Velocity_Angle(this, vecAngle);

			UTIL_MakeVectors(vecAngle);		
			vecForw = gpGlobals->v_forward * 20.0;
			vecEnd = vecStart + vecForw;
			vecForw = gpGlobals->v_forward * -0.5;
			vecStart = vecForw;

			CBaseEntity *pAttacker = CBaseEntity::Instance(pev->owner);
			CBasePlayer *pAttackePlayer = nullptr;

			if (pAttacker && pAttacker->IsPlayer())
				pAttackePlayer = static_cast<CBasePlayer *>(pAttacker);
		
			TraceResult tr;
			UTIL_TraceLine(vecStart, vecEnd, dont_ignore_monsters, ENT(pAttackePlayer->pev), &tr);
			
			if (pAttackePlayer &&
				pOther->pev->takedamage != DAMAGE_NO &&
				pOther->IsAlive()
				)
			{
				Vector vecDirection = (pev->velocity).Normalize();

				ClearMultiDamage();
				pOther->TraceAttack(pAttackePlayer->pev, m_ArrowDamage, vecDirection, &tr, DMG_BULLET | DMG_NEVERGIB);
				ApplyMultiDamage(pAttackePlayer->pev, pAttackePlayer->pev);

				pev->renderamt = 0.0;
				EMIT_SOUND_DYN(this->edict(), CHAN_AUTO, "weapons/xbow_hitbod1.wav", VOL_NORM, ATTN_NORM, 0, PITCH_NORM);

			}

			SetThink(&CBaseEntity::SUB_StartFadeOut);
			pev->nextthink = gpGlobals->time + 6.0;
			pev->rendermode = kRenderNormal;
			pev->renderamt = 255.0;

			if (pOther->IsBSPModel())
			{
				MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY, pev->origin);
				WRITE_BYTE(TE_GUNSHOTDECAL);
				WRITE_COORD(pev->origin.x);
				WRITE_COORD(pev->origin.y);
				WRITE_COORD(pev->origin.z);
				WRITE_SHORT(0);
				WRITE_BYTE(DECAL_SHOT[RANDOM_LONG(0, 4)]);
				MESSAGE_END();

				EMIT_SOUND_DYN(this->edict(), CHAN_AUTO, "weapons/xbow_hit1.wav", VOL_NORM, ATTN_NORM, 0, PITCH_NORM);


				pev->animtime = gpGlobals->time;
				pev->framerate = 1.0;
				pev->sequence = 0;
				SetThink(&CBaseEntity::SUB_StartFadeOut);
				pev->nextthink = gpGlobals->time + 3.5;
				pev->renderamt = 255.0;
				pev->movetype = MOVETYPE_NONE;
				return;
			}
			else
				pev->flags |= FL_KILLME;

&CGrenade::ExplodeTouch;
			pev->movetype = MOVETYPE_NONE;
		}

		void Precache() override
		{
			m_iModelLight1 = PRECACHE_MODEL("sprites/smoke.spr");
			PRECACHE_MODEL("models/arrow.mdl");
		}

		void OnThink()
		{
			if (pev->flags & FL_KILLME)
				return;
			MESSAGE_BEGIN(MSG_BROADCAST, SVC_TEMPENTITY);
			WRITE_BYTE(TE_BEAMFOLLOW);
			WRITE_SHORT(this->entindex());  // short (entity:attachment to follow)
			WRITE_SHORT(m_iModelLight1);// short (sprite index)
			WRITE_BYTE(5);
			WRITE_BYTE(1);
			WRITE_BYTE(244);
			WRITE_BYTE(244);
			WRITE_BYTE(244);
			WRITE_BYTE(100);
			MESSAGE_END();
			pev->nextthink = gpGlobals->time + 10.0;
		}

		void Init(Vector vecVelocity, float flDamage, TeamName iTeam, int iMode, float flGravity)
		{
			pev->gravity = flGravity;
			m_iMode = iMode;
			m_ArrowDamage = flDamage;
			pev->velocity = std::move(vecVelocity);
			m_iTeam = iTeam;
		}

		int m_iModelLight1;
		int m_iMode;
		float m_ArrowDamage;
		TeamName m_iTeam;

	protected:
		void Remove()
		{
			SetTouch(nullptr);
			SetThink(nullptr);
			pev->effects |= EF_NODRAW; // 0x80u
			return UTIL_Remove(this);
		}

	};

	LINK_ENTITY_TO_CLASS(bow_arrow, CBowArrow);
#endif

enum bow_e
{
	BOW_DRAW_EMPTY,
	BOW_IDLE_ARROW,
	BOW_IDLE_GRENADE,
	BOW_DRAW_ARROW,
	BOW_DRAW_GRENADE,
	BOW_SHOOT_ARROW,
	BOW_SHOOT_GRENADE,
	BOW_SHOOT_ARROW_LAST,
	BOW_SHOOT_GRENADE_LAST,
};

LINK_ENTITY_TO_CLASS(weapon_bow, CBow)

void CBow::Spawn(void)
{
	pev->classname = MAKE_STRING("weapon_bow");

	Precache();
	m_iId = WEAPON_USP;
	SET_MODEL(ENT(pev), "models/w_bow.mdl");
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;
m_crosshair = false;
shootGrenade = FALSE;
	//m_iClip = -1;
	m_iDefaultAmmo = -1;

	FallInit();
}

void CBow::Precache(void)
{
	
PRECACHE_MODEL("models/billflx/v_bow.mdl");


	PRECACHE_MODEL("models/p_bow.mdl");



	PRECACHE_SOUND("weapons/bow-1.wav");
	PRECACHE_SOUND("weapons/deagle-2.wav");
	PRECACHE_SOUND("weapons/xbow_hitbod1.wav");
	PRECACHE_SOUND("weapons/xbow_hit1.wav");
	PRECACHE_SOUND("weapons/de_deploy.wav");

	m_iShell = PRECACHE_MODEL("models/pshell.mdl");
	m_usFireBow = PRECACHE_EVENT(1, "events/deagle.sc");
}
const float AMMO_BOW = 1;

int CBow::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "556Nato";
	p->iMaxAmmo1 = MAX_AMMO_556NATO;
	p->pszAmmo2 = "buckshot"; // whatever it is, it can't be bought
	p->iMaxAmmo2 = 10;
	p->iMaxClip = 30;
	p->iSlot = 1;
	p->iPosition = 6;
	p->iId = WEAPON_USP;
	p->iFlags = 0;
	p->iWeight = USP_WEIGHT;

	return 1;
}


void CBow::crosshairOn(void)
{
CLIENT_COMMAND(m_pPlayer->edict(), "pb_crosshair 2\n");
}

void CBow::crosshairOff(void)
{
CLIENT_COMMAND(m_pPlayer->edict(), "pb_crosshair 1\n");
}

BOOL CBow::Deploy(void)
{
	m_flAccuracy = 0.2;
	m_iShotsFired = 0;
	iShellOn = 1;
	pev->iuser1 = 0;
	fFinishTime = 0;

if (m_iWeaponState & WPNSTATE_M4A1_SILENCED)
{

SetThink(&CBow::crosshairOn);
pev->nextthink = gpGlobals->time + 0.01;

if (m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType] == 81)
{
return DefaultDeploy("models/billflx/v_bow.mdl", "models/p_bow.mdl", BOW_DRAW_EMPTY, "rifle", UseDecrement() != FALSE);
}
else
{

if (shootGrenade)
return DefaultDeploy("models/billflx/v_bow.mdl", "models/p_bow.mdl", BOW_DRAW_EMPTY, "rifle", UseDecrement() != FALSE);
else
return DefaultDeploy("models/billflx/v_bow.mdl", "models/p_bow.mdl", BOW_DRAW_GRENADE, "rifle", UseDecrement() != FALSE);
}


}
	else
{

SetThink(&CBow::crosshairOff);
	pev->nextthink = gpGlobals->time + 0.01;


if (m_iClip == 4)
{
return DefaultDeploy("models/billflx/v_bow.mdl", "models/p_bow.mdl", BOW_DRAW_EMPTY, "rifle", UseDecrement() != FALSE);
}
else
{
return DefaultDeploy("models/billflx/v_bow.mdl", "models/p_bow.mdl", BOW_DRAW_ARROW, "rifle", UseDecrement() != FALSE);
}

}

}

void CBow::PrimaryAttack(void)
{
if (m_iWeaponState & WPNSTATE_M4A1_SILENCED)
	{


if (m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType] == 82)
{
SendWeaponAnim(BOW_SHOOT_GRENADE_LAST, UseDecrement() != FALSE);
EMIT_SOUND_DYN(this->edict(), CHAN_AUTO, "weapons/bow-1.wav", VOL_NORM, ATTN_NORM, 0, PITCH_NORM);
SecondaryAttack();
}
else if (m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType] <= 81)
{
SendWeaponAnim(BOW_DRAW_EMPTY, UseDecrement() != FALSE);
}
else
{
SendWeaponAnim(BOW_SHOOT_GRENADE, UseDecrement() != FALSE);
EMIT_SOUND_DYN(this->edict(), CHAN_AUTO, "weapons/bow-1.wav", VOL_NORM, ATTN_NORM, 0, PITCH_NORM);
}
ammoGrenade();

	}
	else
	{

if (m_iClip == 3)
{
SendWeaponAnim(BOW_SHOOT_ARROW_LAST, UseDecrement() != FALSE);
EMIT_SOUND_DYN(this->edict(), CHAN_AUTO, "weapons/bow-1.wav", VOL_NORM, ATTN_NORM, 0, PITCH_NORM);
SecondaryAttack();
}
else if (m_iClip == 4)
{
SendWeaponAnim(BOW_DRAW_EMPTY, UseDecrement() != FALSE);

}
else
{
SendWeaponAnim(BOW_SHOOT_ARROW, UseDecrement() != FALSE);
EMIT_SOUND_DYN(this->edict(), CHAN_AUTO, "weapons/bow-1.wav", VOL_NORM, ATTN_NORM, 0, PITCH_NORM);
}

ammoArrow();

	}



}

void CBow::Taurus_raging_bullFire(float flSpread, float flCycleTime, BOOL fUseAutoAim)
{
	;
}


void CBow::SecondaryAttack(void)
{

if (m_iClip == 4 && m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType] <= 81)
{
RetireWeapon();
DestroyItem();
}

if (m_iWeaponState & WPNSTATE_M4A1_SILENCED)
	{

		m_iWeaponState &= ~WPNSTATE_M4A1_SILENCED;
SetThink(&CBow::crosshairOff);
	pev->nextthink = gpGlobals->time + 0.01;
if (m_iClip == 4)
SendWeaponAnim(BOW_DRAW_EMPTY, 0);
else
		SendWeaponAnim(BOW_DRAW_ARROW, 0);
		strcpy(m_pPlayer->m_szAnimExtention, "rifle");

	}
	else
	{
		m_iWeaponState |= WPNSTATE_M4A1_SILENCED;
SetThink(&CBow::crosshairOn);
	pev->nextthink = gpGlobals->time + 0.01;
if (m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType] == 81)
{
SendWeaponAnim(BOW_DRAW_EMPTY, 0);
}
else
{

if (shootGrenade)
		SendWeaponAnim(BOW_DRAW_EMPTY, 0);
else
		SendWeaponAnim(BOW_DRAW_GRENADE, 0);
}
		strcpy(m_pPlayer->m_szAnimExtention, "rifle");

	}


	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 1;
	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 1;
}

void CBow::ammoGrenade(void)
{
if (m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType] == 81)
return;

if (shootGrenade)
return;

	if (m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType] <= 0)
	{
		if (m_fFireOnEmpty)
		{
			PlayEmptySound();
			m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.2;
		}

		return;
	}
	--m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType];


#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.9;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.925;

	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);
Vector angThrow = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;
		UTIL_MakeVectors(angThrow);
		Vector vecSrc = m_pPlayer->pev->origin + m_pPlayer->pev->view_ofs;
		Vector vecThrow = gpGlobals->v_forward * 2000;
float time = 0;
	CGrenade::ShootExplode(m_pPlayer->pev, vecSrc, vecThrow, time, m_pPlayer->m_iTeam, NULL);

shootGrenade = TRUE;
}

void CBow::ammoArrow(void)
{
if (m_iClip == 4)
return;
	m_iShotsFired++;
	m_pPlayer->pev->punchangle.x -= 2.0;
m_iClip += 1;
	
#ifndef CLIENT_DLL
	m_pPlayer->SetAnimation(PLAYER_ATTACK1);
#endif

	m_flNextPrimaryAttack = m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.9;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.925;


#ifndef CLIENT_DLL
	Vector vecArrowAngle;
	UTIL_MakeVectors(m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle);

	CBowArrow *pEnt = static_cast<CBowArrow *>(CBaseEntity::Create("bow_arrow", m_pPlayer->GetGunPosition(), Stock_Get_Velocity_Angle(gpGlobals->v_forward * 2000, vecArrowAngle), ENT(m_pPlayer->pev)));
	if (pEnt)
	{
		pEnt->Init(gpGlobals->v_forward * 2000, 210, m_pPlayer->m_iTeam, 1, 0.15);


	}
#endif
}


void CBow::Reload(void)
{
		return;
}

void CBow::WeaponIdle(void)
{
	ResetEmptySound();
	m_pPlayer->GetAutoaimVector(AUTOAIM_10DEGREES);

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

if (m_iWeaponState & WPNSTATE_M4A1_SILENCED)
{
		SetThink(&CBow::crosshairOn);
	pev->nextthink = gpGlobals->time + 0.01;
}
	else
{
		SetThink(&CBow::crosshairOff);
	pev->nextthink = gpGlobals->time + 0.01;
}


if (m_iClip == 4 && m_pPlayer->m_rgAmmo[m_iSecondaryAmmoType] <= 81)
{
RetireWeapon();
DestroyItem();
}

/*
if (m_crosshair = true)
{
CLIENT_COMMAND(m_pPlayer->edict(), "laser 4\n");
}
else
{
CLIENT_COMMAND(m_pPlayer->edict(), "laser 0\n");
}*/

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 20;
	
}

