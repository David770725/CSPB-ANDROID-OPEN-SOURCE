
#ifndef WEAPONS_CONST_H
#define WEAPONS_CONST_H
#ifdef _WIN32
#pragma once
#endif


enum WeaponIdType
{
	WEAPON_NONE,
	WEAPON_P228,
	WEAPON_GLOCK,
	WEAPON_SCOUT,
	WEAPON_HEGRENADE,
	WEAPON_XM1014,
	WEAPON_C4,
	WEAPON_MAC10,
	WEAPON_AUG,
	WEAPON_SMOKEGRENADE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_UMP45,
	WEAPON_SG550,
	WEAPON_GALIL,
	WEAPON_FAMAS,
	WEAPON_USP,
	WEAPON_GLOCK18,
	WEAPON_AWP,
	WEAPON_MP5N,
	WEAPON_M249,
	WEAPON_M3,
	WEAPON_M4A1,
	WEAPON_TMP,
	WEAPON_G3SG1,
	WEAPON_FLASHBANG,
	WEAPON_DEAGLE,
	WEAPON_SG552,
	WEAPON_AK47,
	WEAPON_KNIFE,
	WEAPON_P90,
WEAPON_CUSTOM1, 	
WEAPON_CUSTOM2, 	
WEAPON_CUSTOM3, 	
WEAPON_CUSTOM4, 	
WEAPON_CUSTOM5, 	
WEAPON_CUSTOM6, 	
WEAPON_CUSTOM7, 	
WEAPON_CUSTOM8, 	
WEAPON_CUSTOM9, 	
WEAPON_CUSTOM10, 	
WEAPON_CUSTOM11, 	
WEAPON_CUSTOM12, 	
WEAPON_CUSTOM13, 	
WEAPON_CUSTOM14, 	
WEAPON_CUSTOM15, 	
WEAPON_CUSTOM16, 	
WEAPON_CUSTOM17, 	
WEAPON_CUSTOM18, 	
WEAPON_CUSTOM19, 	
WEAPON_CUSTOM20, 	
WEAPON_CUSTOM21, 	
WEAPON_CUSTOM22, 	
WEAPON_CUSTOM23, 	
WEAPON_CUSTOM24, 	
WEAPON_CUSTOM25, 	
WEAPON_CUSTOM26, 	
WEAPON_CUSTOM27, 	
WEAPON_CUSTOM28, 	
WEAPON_CUSTOM29, 	
WEAPON_CUSTOM30, 	
WEAPON_CUSTOM31, 	
WEAPON_CUSTOM32, 	
WEAPON_CUSTOM33, 	
WEAPON_CUSTOM34, 	
WEAPON_CUSTOM35, 	
WEAPON_CUSTOM36, 	
WEAPON_CUSTOM37, 	
WEAPON_CUSTOM38, 	
WEAPON_CUSTOM39, 	
WEAPON_CUSTOM40, 	
WEAPON_CUSTOM41, 	
WEAPON_CUSTOM42, 	
WEAPON_CUSTOM43, 	
WEAPON_CUSTOM44, 	
WEAPON_CUSTOM45, 	
WEAPON_CUSTOM46, 	
WEAPON_CUSTOM47, 	
WEAPON_CUSTOM48, 	
WEAPON_CUSTOM49, 	
WEAPON_CUSTOM50, 	
WEAPON_CUSTOM51, 	
WEAPON_CUSTOM52, 	
WEAPON_CUSTOM53, 	
WEAPON_CUSTOM54, 	
WEAPON_CUSTOM55, 	
WEAPON_CUSTOM56, 	
WEAPON_CUSTOM57, 	
WEAPON_CUSTOM58, 	
WEAPON_CUSTOM59, 	
WEAPON_CUSTOM60, 	
WEAPON_CUSTOM61, 	
WEAPON_CUSTOM62, 	
WEAPON_CUSTOM63, 	
WEAPON_CUSTOM64, 	
WEAPON_CUSTOM65, 	
WEAPON_CUSTOM66, 	
WEAPON_CUSTOM67, 	
WEAPON_CUSTOM68, 	
WEAPON_CUSTOM69, 	
WEAPON_CUSTOM70, 	
WEAPON_CUSTOM71, 	
WEAPON_CUSTOM72, 	
WEAPON_CUSTOM73, 	
WEAPON_CUSTOM74, 	
WEAPON_CUSTOM75, 	
WEAPON_CUSTOM76, 	
WEAPON_CUSTOM77, 	
WEAPON_CUSTOM78, 	
WEAPON_CUSTOM79, 	
WEAPON_CUSTOM80, 	
WEAPON_CUSTOM81, 	
WEAPON_CUSTOM82, 	
WEAPON_CUSTOM83, 	
WEAPON_CUSTOM84, 	
WEAPON_CUSTOM85, 	
WEAPON_CUSTOM86, 	
WEAPON_CUSTOM87, 	
WEAPON_CUSTOM88, 	
WEAPON_CUSTOM89, 	
WEAPON_CUSTOM90, 	
WEAPON_CUSTOM91, 	
WEAPON_CUSTOM92, 	
WEAPON_CUSTOM93, 	
WEAPON_CUSTOM94, 	
WEAPON_CUSTOM95, 	
WEAPON_CUSTOM96, 	
WEAPON_CUSTOM97, 	
WEAPON_CUSTOM98, 	
WEAPON_CUSTOM99, 	
WEAPON_CUSTOM100, 	
	WEAPON_SHIELDGUN = 99
};

enum AmmoType
{
	AMMO_BUCKSHOT,
	AMMO_9MM,
	AMMO_556NATO,
	AMMO_556NATOBOX,
	AMMO_762NATO,
	AMMO_45ACP,
	AMMO_50AE,
	AMMO_338MAGNUM,
	AMMO_57MM,
	AMMO_357SIG,
	AMMO_MAX_TYPES,
};

enum WeaponState
{
	WPNSTATE_USP_SILENCED = (1 << 0),
	WPNSTATE_GLOCK18_BURST_MODE = (1 << 1),
	WPNSTATE_M4A1_SILENCED = (1 << 2),
	WPNSTATE_ELITE_LEFT = (1 << 3),
	WPNSTATE_FAMAS_BURST_MODE = (1 << 4),
	WPNSTATE_SHIELD_DRAWN = (1 << 5),
	WPNSTATE_KRISS_SILENCED = (1 << 6),
};

// custom enum
// the default amount of ammo that comes with each gun when it spawns
enum ClipGiveDefault
{
	P228_DEFAULT_GIVE = 6,
	GLOCK18_DEFAULT_GIVE = 20,
	SCOUT_DEFAULT_GIVE = 5,
	HEGRENADE_DEFAULT_GIVE = 1,
	XM1014_DEFAULT_GIVE = 7,
	C4_DEFAULT_GIVE = 1,
	MAC10_DEFAULT_GIVE = 30,
	AUG_DEFAULT_GIVE = 30,
	SMOKEGRENADE_DEFAULT_GIVE = 1,
	ELITE_DEFAULT_GIVE = 14,
	FIVESEVEN_DEFAULT_GIVE = 6,
	UMP45_DEFAULT_GIVE = 30,
	SG550_DEFAULT_GIVE = 30,
	GALIL_DEFAULT_GIVE = 35,
	FAMAS_DEFAULT_GIVE = 30,
	USP_DEFAULT_GIVE = 12,
	AWP_DEFAULT_GIVE = 5,
	MP5NAVY_DEFAULT_GIVE = 30,
	M249_DEFAULT_GIVE = 100,
	M3_DEFAULT_GIVE = 8,
	M4A1_DEFAULT_GIVE = 30,
	TMP_DEFAULT_GIVE = 30,
	G3SG1_DEFAULT_GIVE = 20,
	FLASHBANG_DEFAULT_GIVE = 1,
	DEAGLE_DEFAULT_GIVE = 7,
	SG552_DEFAULT_GIVE = 6,
	AK47_DEFAULT_GIVE = 30,
	/*KNIFE_DEFAULT_GIVE		= 1,*/
	P90_DEFAULT_GIVE = 50,
};


enum ClipSizeType
{
	P228_MAX_CLIP = 6,
	GLOCK18_MAX_CLIP = 20,
	SCOUT_MAX_CLIP = 5,
	XM1014_MAX_CLIP = 7,
	MAC10_MAX_CLIP = 30,
	AUG_MAX_CLIP = 30,
	ELITE_MAX_CLIP = 14,
	FIVESEVEN_MAX_CLIP = 6,
	UMP45_MAX_CLIP = 30,
	SG550_MAX_CLIP = 30,
	GALIL_MAX_CLIP = 35,
	FAMAS_MAX_CLIP = 30,
	USP_MAX_CLIP = 12,
	AWP_MAX_CLIP = 5,
	MP5N_MAX_CLIP = 30,
	M249_MAX_CLIP = 100,
	M3_MAX_CLIP = 8,
	M4A1_MAX_CLIP = 30,
	TMP_MAX_CLIP = 30,
	G3SG1_MAX_CLIP = 20,
	DEAGLE_MAX_CLIP = 7,
	SG552_MAX_CLIP = 6,
	AK47_MAX_CLIP = 30,
	P90_MAX_CLIP = 50,
};

enum MaxAmmoType
{
	MAX_AMMO_BUCKSHOT = 0,
	MAX_AMMO_9MM = 0,
	MAX_AMMO_556NATO = 0,
	MAX_AMMO_556NATOBOX = 0,
	MAX_AMMO_762NATO = 0,
	MAX_AMMO_45ACP = 0,
	MAX_AMMO_50AE = 0,
	MAX_AMMO_338MAGNUM = 0,
	MAX_AMMO_57MM = 0,
	MAX_AMMO_357SIG = 0,

	// custom
	MAX_AMMO_SMOKEGRENADE = 1,
	MAX_AMMO_HEGRENADE = 1,
	MAX_AMMO_FLASHBANG = 2,
	MAX_AMMO_C4 = 1,

	MAX_AMMO_46MM = 80,
	MAX_AMMO_50BMG = 50,
};

enum WeightWeapon
{
	P228_WEIGHT = 5,
	GLOCK18_WEIGHT = 5,
	SCOUT_WEIGHT = 30,
	HEGRENADE_WEIGHT = 2,
	XM1014_WEIGHT = 20,
	C4_WEIGHT = 3,
	MAC10_WEIGHT = 25,
	AUG_WEIGHT = 25,
	SMOKEGRENADE_WEIGHT = 1,
	ELITE_WEIGHT = 5,
	FIVESEVEN_WEIGHT = 5,
	UMP45_WEIGHT = 25,
	SG550_WEIGHT = 20,
	GALIL_WEIGHT = 25,
	FAMAS_WEIGHT = 75,
	USP_WEIGHT = 5,
	AWP_WEIGHT = 30,
	MP5NAVY_WEIGHT = 25,
	M249_WEIGHT = 25,
	M3_WEIGHT = 20,
	M4A1_WEIGHT = 25,
	TMP_WEIGHT = 25,
	G3SG1_WEIGHT = 20,
	FLASHBANG_WEIGHT = 1,
	DEAGLE_WEIGHT = 7,
	SG552_WEIGHT = 25,
	AK47_WEIGHT = 25,
	P90_WEIGHT = 26,
	KNIFE_WEIGHT = 0,
};

enum shieldgun_e
{
	SHIELDGUN_IDLE,
	SHIELDGUN_SHOOT1,
	SHIELDGUN_SHOOT2,
	SHIELDGUN_SHOOT_EMPTY,
	SHIELDGUN_RELOAD,
	SHIELDGUN_DRAW,
	SHIELDGUN_DRAWN_IDLE,
	SHIELDGUN_UP,
	SHIELDGUN_DOWN,
};

// custom
enum shieldgren_e
{
	SHIELDREN_IDLE = 4,
	SHIELDREN_UP,
	SHIELDREN_DOWN
};

enum InventorySlotType
{
	PRIMARY_WEAPON_SLOT = 1,
	PISTOL_SLOT,
	KNIFE_SLOT,
	GRENADE_SLOT,
	C4_SLOT,
};

enum Bullet
{
	BULLET_NONE,
	BULLET_PLAYER_9MM,
	BULLET_PLAYER_MP5,
	BULLET_PLAYER_357,
	BULLET_PLAYER_BUCKSHOT,
	BULLET_PLAYER_CROWBAR,
	BULLET_MONSTER_9MM,
	BULLET_MONSTER_MP5,
	BULLET_MONSTER_12MM,
	BULLET_PLAYER_45ACP,
	BULLET_PLAYER_338MAG,
	BULLET_PLAYER_762MM,
	BULLET_PLAYER_556MM,
	BULLET_PLAYER_50AE,
	BULLET_PLAYER_57MM,
	BULLET_PLAYER_357SIG,
};

#endif
