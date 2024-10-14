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
#include "wpn_lpg.h"

enum hegrenade_e
{
	HEGRENADE_IDLE,
	HEGRENADE_PULLPIN,
	HEGRENADE_THROW,
	HEGRENADE_DRAW,
ANIM1,
ANIM2,
ANIM3,
ANIM4,
ANIM5
};

LINK_ENTITY_TO_CLASS(weapon_gasbomb, CLPG)

void CLPG::Spawn(void)
{
	Precache();
	m_iId = WEAPON_HEGRENADE;
	SET_MODEL(ENT(pev), "models/w_hegrenade.mdl");

	pev->dmg = 4;
	m_iDefaultAmmo = HEGRENADE_DEFAULT_GIVE;
	m_flStartThrow = 0;
	m_flReleaseThrow = -1;
	m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;

	FallInit();
}

void CLPG::Precache(void)
{
	//ct
PRECACHE_MODEL("models/billflx/v_gasbomb_melon.mdl");
PRECACHE_MODEL("models/w_gasbomb_melon.mdl");


#ifdef ENABLE_SHIELD
	PRECACHE_MODEL("models/shield/v_shield_hegrenade.mdl");
#endif

	PRECACHE_SOUND("weapons/hegrenade-1.wav");
	PRECACHE_SOUND("weapons/hegrenade-2.wav");
	PRECACHE_SOUND("weapons/he_bounce-1.wav");
	PRECACHE_SOUND("weapons/pinpull.wav");

	m_usCreateExplosion = PRECACHE_EVENT(1, "events/createexplo.sc");
}

int CLPG::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "HEGrenade";
	p->iMaxAmmo1 = MAX_AMMO_HEGRENADE;
	p->pszAmmo2 = NULL;
	p->iMaxAmmo2 = -1;
	p->iMaxClip = WEAPON_NOCLIP;
	p->iSlot = 3;
	p->iPosition = 1;
	p->iId = WEAPON_HEGRENADE;
	p->iWeight = HEGRENADE_WEIGHT;
	p->iFlags = ITEM_FLAG_LIMITINWORLD | ITEM_FLAG_EXHAUSTIBLE;

	return 1;
}


BOOL CLPG::Deploy(void)
{

m_flReleaseThrow = -1;
	m_fMaxSpeed = 250;
	
if ( DefaultDeploy("models/billflx/v_gasbomb_melon.mdl", "models/p_gasbomb_melon.mdl", HEGRENADE_DRAW, "grenade", 0));

{
	m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
	
	return TRUE;
	}
	return FALSE;
		

}

void CLPG::QuickDeploy()
{
SendWeaponAnim(ANIM1, 0);
m_flNextPrimaryAttack = m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.3;
m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.3;
}

BOOL CLPG::CanHolster(void)
{
	return m_flStartThrow == 0;
}

void CLPG::Holster(int skiplocal)
{
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;

	if (!m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
	{
		m_pPlayer->pev->weapons &= ~(1 << WEAPON_HEGRENADE);
		DestroyItem();
	}

	m_flStartThrow = 0;
	m_flReleaseThrow = -1;
}


void CLPG::PrimaryAttack(void)
{
	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
		return;

	if (!m_flStartThrow && m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] > 0)
	{
		m_flStartThrow = gpGlobals->time;
		m_flReleaseThrow = 0;
		SendWeaponAnim(HEGRENADE_PULLPIN, 0);
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.5;


	}
}

void CLPG::SetPlayerShieldAnim(void)
{
	if (m_pPlayer->HasShield() == true)
	{
		if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
			strcpy(m_pPlayer->m_szAnimExtention, "shield");
		else
			strcpy(m_pPlayer->m_szAnimExtention, "shieldgren");
	}
}

void CLPG::ResetPlayerShieldAnim(void)
{
	if (m_pPlayer->HasShield() == true)
	{
		if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
			strcpy(m_pPlayer->m_szAnimExtention, "shieldgren");
	}
}

bool CLPG::ShieldSecondaryFire(int up_anim, int down_anim)
{
	if (m_pPlayer->HasShield() == false)
		return false;

	if (m_flStartThrow > 0)
		return false;

	if (m_iWeaponState & WPNSTATE_SHIELD_DRAWN)
	{
		m_iWeaponState &= ~WPNSTATE_SHIELD_DRAWN;
		SendWeaponAnim(down_anim, 0);
		strcpy(m_pPlayer->m_szAnimExtention, "shieldgren");
		m_fMaxSpeed = 300;
		m_pPlayer->m_bShieldDrawn = false;
	}
	else
	{
		m_iWeaponState |= WPNSTATE_SHIELD_DRAWN;
		SendWeaponAnim(up_anim, 0);
		strcpy(m_pPlayer->m_szAnimExtention, "shielded");
		m_fMaxSpeed = 180;
		m_pPlayer->m_bShieldDrawn = true;
	}

#ifndef CLIENT_DLL
	m_pPlayer->UpdateShieldCrosshair((m_iWeaponState & WPNSTATE_SHIELD_DRAWN) == 0);
	m_pPlayer->ResetMaxSpeed();
#endif
	m_flNextSecondaryAttack = UTIL_WeaponTimeBase() + 0.4;
	m_flNextPrimaryAttack = UTIL_WeaponTimeBase() + 0.4;
	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.6;
	return true;
}

void CLPG::SecondaryAttack(void)
{
	ShieldSecondaryFire(SHIELDGUN_DRAW, SHIELDGUN_DRAWN_IDLE);
}

void CLPG::WeaponIdle(void)
{
	if (!m_flReleaseThrow && m_flStartThrow)
		m_flReleaseThrow = gpGlobals->time;

	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	if (m_flStartThrow)
	{



#ifndef CLIENT_DLL
		switch (m_pPlayer->m_iModelName)
		{
		case MODEL_URBAN:
	
m_pPlayer->Radio("%!MRAD_FIREINHOLEMALE", "#Fire_in_the_hole");
			break;
		case MODEL_GSG9:
			m_pPlayer->Radio("%!MRAD_FIREINHOLEFEMALE", "#Fire_in_the_hole");
			break;
		case MODEL_GIGN:
m_pPlayer->Radio("%!MRAD_FIREINHOLEFEMALE", "#Fire_in_the_hole");
			break;
		case MODEL_SAS:
m_pPlayer->Radio("%!MRAD_FIREINHOLEMALE", "#Fire_in_the_hole");
			break;
case MODEL_SPETSNAZ:
m_pPlayer->Radio("%!MRAD_FIREINHOLEFEMALE", "#Fire_in_the_hole");
break;

                           case MODEL_TERROR:
m_pPlayer->Radio("%!MRAD_FIREINHOLEMALE", "#Fire_in_the_hole");
			break;
		case MODEL_LEET:
m_pPlayer->Radio("%!MRAD_FIREINHOLEFEMALE", "#Fire_in_the_hole");
			break;
		case MODEL_ARCTIC:
m_pPlayer->Radio("%!MRAD_FIREINHOLEMALE", "#Fire_in_the_hole");
			break;
		case MODEL_GUERILLA:
m_pPlayer->Radio("%!MRAD_FIREINHOLEFEMALE", "#Fire_in_the_hole");
			break;

case MODEL_MILITIA:
m_pPlayer->Radio("%!MRAD_FIREINHOLEFEMALE", "#Fire_in_the_hole");
			break;

case MODEL_BLUEFEMALE1:
m_pPlayer->Radio("%!MRAD_FIREINHOLEFEMALE", "#Fire_in_the_hole");
			break;

case MODEL_BLUEMALE1:
m_pPlayer->Radio("%!MRAD_FIREINHOLEMALE", "#Fire_in_the_hole");
			break;

case MODEL_REDFEMALE1:
m_pPlayer->Radio("%!MRAD_FIREINHOLEFEMALE", "#Fire_in_the_hole");
			break;

case MODEL_REDMALE1:
m_pPlayer->Radio("%!MRAD_FIREINHOLEMALE", "#Fire_in_the_hole");
			break;

}
#endif
		Vector angThrow = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;

		if (angThrow.x < 0)
			angThrow.x = -10 + angThrow.x * ((90 - 10) / 90.0);
		else
			angThrow.x = -10 + angThrow.x * ((90 + 10) / 90.0);

		float flVel = (90 - angThrow.x) * 6;

		if (flVel > 750)
			flVel = 750;

		UTIL_MakeVectors(angThrow);
		Vector vecSrc = m_pPlayer->pev->origin + m_pPlayer->pev->view_ofs + gpGlobals->v_forward * 16;
		Vector vecThrow = gpGlobals->v_forward * flVel + m_pPlayer->pev->velocity;
		float time = 1.5;
		CGrenade::ShootLpg(m_pPlayer->pev, vecSrc, vecThrow, time, m_pPlayer->m_iTeam, m_usCreateExplosion);

		SendWeaponAnim(HEGRENADE_THROW, 0);
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
			SendWeaponAnim(HEGRENADE_DRAW, 0);
			m_flReleaseThrow = -1;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + RANDOM_FLOAT(10, 15);
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
				SendWeaponAnim(SHIELDREN_IDLE, 0);

			return;
		}

		SendWeaponAnim(HEGRENADE_IDLE, 0);
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + RANDOM_FLOAT(10, 15);
	}
}

BOOL CLPG::CanDeploy(void)
{
	return m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] != 0;
}
