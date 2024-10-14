#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "gamerules.h"
#include "weapons.h"
#include "weapons_precache.h"


// called by worldspawn

void W_Precache()
{
	Q_memset(CBasePlayerItem::ItemInfoArray, 0, ARRAYSIZE(CBasePlayerItem::ItemInfoArray));
	Q_memset(CBasePlayerItem::AmmoInfoArray, 0, ARRAYSIZE(CBasePlayerItem::AmmoInfoArray));
	giAmmoIndex = 0;

	// custom items...

	// common world objects
	UTIL_PrecacheOther("item_suit");
	UTIL_PrecacheOther("item_battery");
	UTIL_PrecacheOther("item_antidote");
	UTIL_PrecacheOther("item_security");
	UTIL_PrecacheOther("item_longjump");
	UTIL_PrecacheOther("item_kevlar");
	UTIL_PrecacheOther("item_assaultsuit");
	UTIL_PrecacheOther("item_thighpack");

	// awp magnum
	UTIL_PrecacheOtherWeapon("weapon_awp");
	UTIL_PrecacheOther("ammo_338magnum");

	
	UTIL_PrecacheOtherWeapon("weapon_ak47");
	UTIL_PrecacheOtherWeapon("weapon_scout");
	UTIL_PrecacheOther("ammo_762nato");

	// m249
	
	UTIL_PrecacheOther("ammo_556natobox");

	UTIL_PrecacheOtherWeapon("weapon_m4a1");

	UTIL_PrecacheOtherWeapon("weapon_aug");
	UTIL_PrecacheOtherWeapon("weapon_sg550");
	UTIL_PrecacheOther("ammo_556nato");

	// shotgun
	UTIL_PrecacheOtherWeapon("weapon_m3");
		UTIL_PrecacheOther("ammo_buckshot");

	UTIL_PrecacheOtherWeapon("weapon_usp");
	
	UTIL_PrecacheOther("ammo_45acp");

	UTIL_PrecacheOtherWeapon("weapon_p90");
	UTIL_PrecacheOther("ammo_57mm");

	// deagle
	UTIL_PrecacheOtherWeapon("weapon_deagle");
	UTIL_PrecacheOther("ammo_50ae");


	// knife
	UTIL_PrecacheOtherWeapon("weapon_flashbang");
	UTIL_PrecacheOtherWeapon("weapon_hegrenade");
	UTIL_PrecacheOtherWeapon("weapon_smokegrenade");
	UTIL_PrecacheOtherWeapon("weapon_c4");

UTIL_PrecacheOtherWeapon("weapon_colt_python");//⁰
UTIL_PrecacheOtherWeapon("weapon_deagle_dual");
UTIL_PrecacheOtherWeapon("weapon_dual_handgun");
UTIL_PrecacheOtherWeapon("weapon_taurus_raging_bull");
UTIL_PrecacheOtherWeapon("weapon_deagle");
UTIL_PrecacheOtherWeapon("weapon_usp");//5
UTIL_PrecacheOtherWeapon("weapon_glock18");
UTIL_PrecacheOtherWeapon("weapon_bow");
UTIL_PrecacheOtherWeapon("weapon_ak47");
UTIL_PrecacheOtherWeapon("weapon_aksopmod");
UTIL_PrecacheOtherWeapon("weapon_aug_hbar"); //²
UTIL_PrecacheOtherWeapon("weapon_aug"); //³
UTIL_PrecacheOtherWeapon("weapon_augblitz"); //4
UTIL_PrecacheOtherWeapon("weapon_p90");//5
UTIL_PrecacheOtherWeapon("weapon_aug_a3_silencer"); //6
UTIL_PrecacheOtherWeapon("weapon_f2000");
UTIL_PrecacheOtherWeapon("weapon_famas_g2");
UTIL_PrecacheOtherWeapon("weapon_g36c");
UTIL_PrecacheOtherWeapon("weapon_k1");
UTIL_PrecacheOtherWeapon("weapon_k2");//11
UTIL_PrecacheOtherWeapon("weapon_kriss_sv");
UTIL_PrecacheOtherWeapon("weapon_kriss_sv_dual");
UTIL_PrecacheOtherWeapon("weapon_kriss_sv_silence");
UTIL_PrecacheOtherWeapon("weapon_kriss_sv_dual_silence");
UTIL_PrecacheOtherWeapon("weapon_m4_cqb_lv1");
UTIL_PrecacheOtherWeapon("weapon_m4_cqb_lv2");
UTIL_PrecacheOtherWeapon("weapon_m4a1");//16
UTIL_PrecacheOtherWeapon("weapon_m4a1_s");
UTIL_PrecacheOtherWeapon("weapon_mp7");
UTIL_PrecacheOtherWeapon("weapon_oa93");
UTIL_PrecacheOtherWeapon("weapon_oa93_dual");
UTIL_PrecacheOtherWeapon("weapon_p90_mc" );//20
UTIL_PrecacheOtherWeapon("weapon_pindad_ss2_v5");
UTIL_PrecacheOtherWeapon("weapon_groza");
UTIL_PrecacheOtherWeapon("weapon_sc2010");
UTIL_PrecacheOtherWeapon("weapon_scar_carbine");//24
UTIL_PrecacheOtherWeapon("weapon_kriss_sv_crb");
UTIL_PrecacheOtherWeapon("weapon_m4a1_s");
UTIL_PrecacheOtherWeapon("weapon_mp5k");//27
UTIL_PrecacheOtherWeapon("weapon_m4_azure");
UTIL_PrecacheOtherWeapon("weapon_mp9");
UTIL_PrecacheOtherWeapon("weapon_sg550");
UTIL_PrecacheOtherWeapon("weapon_awp");///
UTIL_PrecacheOtherWeapon("weapon_cheytac_m200");//32//
UTIL_PrecacheOtherWeapon("weapon_dragunov");//
UTIL_PrecacheOtherWeapon("weapon_kar98k");//
UTIL_PrecacheOtherWeapon("weapon_rangemaster_338");//35///
UTIL_PrecacheOtherWeapon("weapon_m82a1");//
UTIL_PrecacheOtherWeapon("weapon_tactilite_t2");//
UTIL_PrecacheOtherWeapon("weapon_scout");//38//
UTIL_PrecacheOtherWeapon("weapon_m4_spr_lv1");//
UTIL_PrecacheOtherWeapon("weapon_m4_spr_lv2");
UTIL_PrecacheOtherWeapon("weapon_m1887");//41 page 26
UTIL_PrecacheOtherWeapon("weapon_spas_15");//page 47
UTIL_PrecacheOtherWeapon("weapon_zombie_s");//page 51
UTIL_PrecacheOtherWeapon("weapon_m3");
UTIL_PrecacheOtherWeapon("weapon_aksopmod_cg"); //46
UTIL_PrecacheOtherWeapon("weapon_aug_esport"); //47
UTIL_PrecacheOtherWeapon("weapon_t77"); //48
UTIL_PrecacheOtherWeapon("weapon_t77_dual"); //48
UTIL_PrecacheOtherWeapon("weapon_apc"); //49
UTIL_PrecacheOtherWeapon("weapon_fg42"); //50
UTIL_PrecacheOtherWeapon("weapon_msbs"); //51
UTIL_PrecacheOtherWeapon("weapon_as50"); //52
UTIL_PrecacheOtherWeapon("weapon_m1887_w"); //53
UTIL_PrecacheOtherWeapon("weapon_pgm"); //54
UTIL_PrecacheOtherWeapon("weapon_ump"); //55
UTIL_PrecacheOtherWeapon("weapon_sig"); //56
UTIL_PrecacheOtherWeapon("weapon_spectre"); //57
UTIL_PrecacheOtherWeapon("weapon_tar"); //58
UTIL_PrecacheOtherWeapon("weapon_xm8"); //59
UTIL_PrecacheOtherWeapon("weapon_water");
UTIL_PrecacheOtherWeapon("weapon_knife");//0
UTIL_PrecacheOtherWeapon("weapon_amok");
UTIL_PrecacheOtherWeapon("weapon_saber");
UTIL_PrecacheOtherWeapon("weapon_arabian_sword");//³
UTIL_PrecacheOtherWeapon("weapon_fangblade");
UTIL_PrecacheOtherWeapon("weapon_combat");//5
UTIL_PrecacheOtherWeapon("weapon_knifebone");
UTIL_PrecacheOtherWeapon("weapon_brass_knuckle");
UTIL_PrecacheOtherWeapon("weapon_candy_cane");
UTIL_PrecacheOtherWeapon("weapon_dual_knife");
UTIL_PrecacheOtherWeapon("weapon_keris");
UTIL_PrecacheOtherWeapon("weapon_mini_axe");//11
UTIL_PrecacheOtherWeapon("weapon_knife");
UTIL_PrecacheOtherWeapon("weapon_ice");
UTIL_PrecacheOtherWeapon("weapon_karambit");//14
UTIL_PrecacheOtherWeapon("weapon_butterfly");
UTIL_PrecacheOtherWeapon("weapon_hegrenade");//0
UTIL_PrecacheOtherWeapon("weapon_gasbomb");
UTIL_PrecacheOtherWeapon("weapon_smokegrenade");//0
UTIL_PrecacheOtherWeapon("weapon_medkit");




	if (g_pGameRules->IsDeathmatch())
	{
		// container for dropped deathmatch weapons
		UTIL_PrecacheOther("weaponbox");
	}

	g_sModelIndexFireball = PRECACHE_MODEL("sprites/zerogxplode.spr");	// fireball
	g_sModelIndexWExplosion = PRECACHE_MODEL("sprites/WXplo1.spr");		// underwater fireball
	g_sModelIndexSmoke = PRECACHE_MODEL("sprites/steam1.spr");		// smoke
	g_sModelIndexBubbles = PRECACHE_MODEL("sprites/bubble.spr");		// bubbles
	g_sModelIndexBloodSpray = PRECACHE_MODEL("sprites/bloodspray.spr");	// initial blood
	g_sModelIndexBloodDrop = PRECACHE_MODEL("sprites/blood.spr");		// splattered blood

	g_sModelIndexSmokePuff = PRECACHE_MODEL("sprites/smokepuff.spr");
	g_sModelIndexFireball2 = PRECACHE_MODEL("sprites/eexplo.spr");
	g_sModelIndexFireball3 = PRECACHE_MODEL("sprites/fexplo.spr");
	g_sModelIndexFireball4 = PRECACHE_MODEL("sprites/fexplo1.spr");
	g_sModelIndexRadio = PRECACHE_MODEL("sprites/radio.spr");

	g_sModelIndexCTGhost = PRECACHE_MODEL("sprites/b-tele1.spr");
	g_sModelIndexTGhost = PRECACHE_MODEL("sprites/c-tele1.spr");
	g_sModelIndexC4Glow = PRECACHE_MODEL("sprites/ledglow.spr");

	g_sModelIndexLaser = PRECACHE_MODEL((char*)g_pModelNameLaser);
	g_sModelIndexLaserDot = PRECACHE_MODEL("sprites/laserdot.spr");

	// used by explosions
	PRECACHE_MODEL("models/grenade.mdl");
	PRECACHE_MODEL("sprites/explode1.spr");

	PRECACHE_SOUND("weapons/debris1.wav");		// explosion aftermaths
	PRECACHE_SOUND("weapons/debris2.wav");		// explosion aftermaths
	PRECACHE_SOUND("weapons/debris3.wav");		// explosion aftermaths

	PRECACHE_SOUND("weapons/grenade_hit1.wav");	// grenade
	PRECACHE_SOUND("weapons/grenade_hit2.wav");	// grenade
	PRECACHE_SOUND("weapons/grenade_hit3.wav");	// grenade

	PRECACHE_SOUND("weapons/bullet_hit1.wav");	// hit by bullet
	PRECACHE_SOUND("weapons/bullet_hit2.wav");	// hit by bullet

	PRECACHE_SOUND("items/weapondrop1.wav");	// weapon falls to the ground
	PRECACHE_SOUND("weapons/generic_reload.wav");
}
