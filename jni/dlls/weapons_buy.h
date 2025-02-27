/*
*
*   This program is free software; you can redistribute it and/or modify it
*   under the terms of the GNU General Public License as published by the
*   Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*   General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   In addition, as a special exception, the author gives permission to
*   link the code of this program with the Half-Life Game Engine ("HL
*   Engine") and Modified Game Libraries ("MODs") developed by Valve,
*   L.L.C ("Valve").  You must obey the GNU General Public License in all
*   respects for all of the code used other than the HL Engine and MODs
*   from Valve.  If you modify this file, you may extend this exception
*   to your version of the file, but you are not obligated to do so.  If
*   you do not wish to do so, delete this exception statement from your
*   version.
*
*/

#ifndef WEAPONS_BUY_H
#define WEAPONS_BUY_H
#ifdef _WIN32
#pragma once
#endif



enum AutoBuyClassType
{
	AUTOBUYCLASS_NONE		= 0,
	AUTOBUYCLASS_PRIMARY		= (1 << 0),
	AUTOBUYCLASS_SECONDARY		= (1 << 1),
	AUTOBUYCLASS_AMMO		= (1 << 2),
	AUTOBUYCLASS_ARMOR		= (1 << 3),
	AUTOBUYCLASS_DEFUSER		= (1 << 4),
	AUTOBUYCLASS_PISTOL		= (1 << 5),
	AUTOBUYCLASS_SMG		= (1 << 6),
	AUTOBUYCLASS_RIFLE		= (1 << 7),
	AUTOBUYCLASS_SNIPERRIFLE	= (1 << 8),
	AUTOBUYCLASS_SHOTGUN		= (1 << 9),
	AUTOBUYCLASS_MACHINEGUN		= (1 << 10),
	AUTOBUYCLASS_GRENADE		= (1 << 11),
	AUTOBUYCLASS_NIGHTVISION	= (1 << 12),
	AUTOBUYCLASS_SHIELD		= (1 << 13),
};

enum AmmoCostType
{
	AMMO_338MAG_PRICE	= 125,
	AMMO_357SIG_PRICE	= 50,
	AMMO_45ACP_PRICE	= 25,
	AMMO_50AE_PRICE		= 40,
	AMMO_556MM_PRICE	= 60,
	AMMO_57MM_PRICE		= 50,
	AMMO_762MM_PRICE	= 80,
	AMMO_9MM_PRICE		= 20,
	AMMO_BUCKSHOT_PRICE	= 65,
	AMMO_46MM_PRICE		= 20,
	AMMO_50BMG_PRICE = 100,
};

enum WeaponCostType
{
	AK47_PRICE	= 5,
	AWP_PRICE	= 5,
	DEAGLE_PRICE	= 5,
	G3SG1_PRICE	= 5,
	SG550_PRICE	= 5,
	GLOCK18_PRICE	= 5,
	M249_PRICE	= 5,
	M3_PRICE	= 5,
	M4A1_PRICE	= 5,
	AUG_PRICE	= 5,
	MP5NAVY_PRICE	= 5,
	P228_PRICE	= 5,
	P90_PRICE	= 5,
	UMP45_PRICE	= 5,
	MAC10_PRICE	= 5,
	SCOUT_PRICE	= 5,
	SG552_PRICE	= 5,
	TMP_PRICE	= 5,
	USP_PRICE	= 5,
	ELITE_PRICE	= 5,
	FIVESEVEN_PRICE	= 5,
	XM1014_PRICE	= 5,
	GALIL_PRICE	= 5,
	FAMAS_PRICE	= 5,
	SHIELDGUN_PRICE	= 5,
};

enum WeaponClassType
{
	WEAPONCLASS_NONE,
	WEAPONCLASS_KNIFE,
	WEAPONCLASS_PISTOL,
	WEAPONCLASS_GRENADE,
	WEAPONCLASS_SUBMACHINEGUN,
	WEAPONCLASS_SHOTGUN,
	WEAPONCLASS_MACHINEGUN,
	WEAPONCLASS_RIFLE,
	WEAPONCLASS_SNIPERRIFLE,
	WEAPONCLASS_MAX,
};

enum AmmoBuyAmount
{
	AMMO_338MAG_BUY		= 10,
	AMMO_357SIG_BUY		= 13,
	AMMO_45ACP_BUY		= 12,
	AMMO_50AE_BUY		= 7,
	AMMO_556NATO_BUY	= 30,
	AMMO_556NATOBOX_BUY	= 30,
	AMMO_57MM_BUY		= 50,
	AMMO_762NATO_BUY	= 30,
	AMMO_9MM_BUY		= 30,
	AMMO_BUCKSHOT_BUY	= 8,
	AMMO_46MM_BUY = 30,
	AMMO_50BMG_BUY = 5,
};

enum ItemCostType
{
	ASSAULTSUIT_PRICE	= 1000,
	FLASHBANG_PRICE		= 200,
	HEGRENADE_PRICE		= 0,
	SMOKEGRENADE_PRICE	= 0,
	KEVLAR_PRICE		= 650,
	HELMET_PRICE		= 350,
	NVG_PRICE		= 1250,
	DEFUSEKIT_PRICE		= 200,
};

struct AutoBuyInfoStruct
{
	int m_class;
	const char *m_command;
	const char *m_classname;
};

struct WeaponAliasInfo
{
	const char *alias;
	WeaponIdType id;
};

struct WeaponBuyAliasInfo
{
	const char *alias;
	WeaponIdType id;
	const char *failName;
};

struct WeaponClassAliasInfo
{
	const char *alias;
	WeaponClassType id;
};

struct WeaponInfoStruct
{
	int id;
	int cost;
	int clipCost;
	int buyClipSize;
	int gunClipSize;
	int maxRounds;
	int ammoType;
	const char *entityName;
};

struct WeaponBuyAmmoConfig
{
	const char *classname;
	int cost;
};

//pb stuff 

extern AutoBuyInfoStruct g_autoBuyInfo[];

// WeaponType
WeaponIdType AliasToWeaponID(const char *alias);
const char *BuyAliasToWeaponID(const char *alias, WeaponIdType &id);
const char *WeaponIDToAlias(int id);
WeaponClassType AliasToWeaponClass(const char *alias);
WeaponClassType WeaponIDToWeaponClass(int id);
bool IsPrimaryWeapon(int id);
bool IsSecondaryWeapon(int id);
WeaponInfoStruct *GetWeaponInfo(int weaponID);
bool CanBuyWeaponByMaptype(int playerTeam, WeaponIdType weaponID, bool useAssasinationRestrictions);

#endif // WEAPONTYPE_H
