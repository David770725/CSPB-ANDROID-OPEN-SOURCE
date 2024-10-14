/*
weapons_moe_buy.cpp - CSMoE Gameplay server : Weapon buy command handler
Copyright (C) 2019 Moemod Hymei

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "weapons.h"
#include "gamerules.h"
#include "client.h"
#include "weapons_moe_buy.h"

#include <algorithm>

bool HasPlayerItem(CBasePlayer *pPlayer, const char *pszCheckItem)
{
	for (CBasePlayerItem *pItem : pPlayer->m_rgpPlayerItems)
	{
		while (pItem != nullptr)
		{
			if (FClassnameIs(pItem->pev, pszCheckItem))
				return true;

			pItem = pItem->m_pNext;
		}
	}
	return false;
}

struct Throwable_s
{
	const char *pszClassName;
	const char *pszDisplayName;
	int iCost;
	InventorySlotType iSlot;
	TeamName team;
};

static Throwable_s g_Throwable[] = {
{ "weapon_medkit", "medkit", 0, GRENADE_SLOT, UNASSIGNED },
{ "weapon_hegrenade", "hegrenade", 0, GRENADE_SLOT, UNASSIGNED },
{ "weapon_smokegrenade", "smoke", 0, GRENADE_SLOT, UNASSIGNED },
{ "weapon_gasbomb", "gas", 0, GRENADE_SLOT, UNASSIGNED },

};


bool MoE_Throwable(CBasePlayer *pPlayer, const char *pszCommand)
{
	if (!pPlayer->CanPlayerBuy(true))
		return false;

	if (HasPlayerItem(pPlayer, pszCommand))
	{
		return false;
	}
		
	auto iter = std::find_if(std::begin(g_Throwable), std::end(g_Throwable), 
		[pszCommand](const Throwable_s &info) {
			return !strcmp(info.pszClassName, pszCommand);
		}
	);

	if (iter != std::end(g_Throwable))
	{
		if (pPlayer->m_iAccount < iter->iCost)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(pPlayer, 2);

			return false;
		}

		switch (iter->iSlot)
		{
		case PRIMARY_WEAPON_SLOT:
			DropPrimary(pPlayer);
			break;
		case PISTOL_SLOT :
			DropSecondary(pPlayer);
			break;
		case KNIFE_SLOT:
			if (pPlayer->m_rgpPlayerItems[KNIFE_SLOT])
			{
				pPlayer->RemovePlayerItem(pPlayer->m_rgpPlayerItems[KNIFE_SLOT]);
			}
			break;
		default:
			break;
		}

		pPlayer->GiveNamedItem(iter->pszClassName);
		pPlayer->AddAccount(-iter->iCost);
		
		return true;
	}

	return false;
}



struct MoEWeaponBuyInfo_s
{
	const char *pszClassName;
	const char *pszDisplayName;
	int iCost;
	InventorySlotType iSlot;
	TeamName team;
};

static MoEWeaponBuyInfo_s g_MoEWeaponBuyInfo[] = {

{ "weapon_colt_python", "colt python", 4, PISTOL_SLOT, UNASSIGNED },
{ "weapon_deagle_dual", "deagle dual", 4, PISTOL_SLOT, UNASSIGNED },
{ "weapon_dual_handgun", "dual handgun", 4, PISTOL_SLOT, UNASSIGNED },
{ "weapon_taurus_raging_bull", "taurus raging bull", 5, PISTOL_SLOT, UNASSIGNED },
{ "weapon_deagle", "deagle", 5, PISTOL_SLOT, UNASSIGNED },
{ "weapon_usp", "usp", 5, PISTOL_SLOT, UNASSIGNED },
{ "weapon_glock18", "glock", 5, PISTOL_SLOT, UNASSIGNED },
{ "weapon_bow", "bow", 5, PISTOL_SLOT, UNASSIGNED },


{ "weapon_ak47", "ak47", 6, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_m1887", "M1887", 6, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_aksopmod", "ak sopmod", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_aug", "aug", 6, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_awp", "awp", 6, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_aug_hbar", "aug hbar", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_augblitz", "AUG BLITZ", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_cheytac_m200", "cheytac m200", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_dragunov", "dragunov", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_p90", "p90", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_aug_a3_silencer", "aug a3 silencer", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_m82a1", "barrett m82a1", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_f2000", "f2000", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_famas_g2", "famas g2", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_g36c", "g36c", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_groza", "groza", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_k1", "k1", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_k2", "k2", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_kar98k", "kar98k", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_kriss_sv", "kriss sv", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_kriss_sv_silence", "kriss sv silencer", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_m4_cqb_lv1", "m4 cqb lv1", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_m4_cqb_lv2", "m4 cqb lv2", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_m4_spr_lv1", "m4 spr lv1", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_m4_spr_lv2", "m4 spr lv2", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_m4a1", "m4a1", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_m4a1_s", "m4a1 s", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_mp7", "mp7", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_oa93", "oa93", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_p90_mc", "p90 mc", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_pindad_ss2_v5", "pindad ss2 v5", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_rangemaster_338", "rangemaster 338", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_sc2010", "sc 2010", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_scar_carbine", "scar carbine", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_spas_15", "spas 15", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_tactilite_t2", "tactilite t2", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
//
{ "weapon_kriss_sv_batik", "kriss sv batik", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_kriss_sv_crb", "kriss sv crb", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_m4a1_s", "m4a1 s", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_zombie_s", "zombie slayer", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_mp5k", "mp5k", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_m4_azure", "m4 azure", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_mp9", "mp9", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_m3", "m3", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_scout", "scout", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_sg550", "sg550", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
//new
{ "weapon_aksopmod_cg", "aksopmod cg", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_aug_esport", "aug e sport", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_t77", "t77", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_apc", "apc9", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_fg42", "fg42", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_msbs", "msbs", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_as50", "as50", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_m1887_w", "m1887 w", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_pgm", "pgm", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_ump", "ump", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_sig", "sig", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_spectre", "spectre", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_tar", "tar21", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_xm8", "xm8", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },
{ "weapon_water", "watergun", 5, PRIMARY_WEAPON_SLOT, UNASSIGNED },




{ "weapon_knife", "Seal Knife", 0, KNIFE_SLOT, UNASSIGNED },
{ "weapon_amok", "amok kukri", 0, KNIFE_SLOT, UNASSIGNED },
{ "weapon_saber", " saber", 5, KNIFE_SLOT, UNASSIGNED },
{ "weapon_arabian_sword", "arabian sword", 0, KNIFE_SLOT, UNASSIGNED },
{ "weapon_fangblade", "fangblade Knife", 0, KNIFE_SLOT, UNASSIGNED },
{ "weapon_combat", "combat machete", 0, KNIFE_SLOT, UNASSIGNED },
{ "weapon_knifebone", "bone Knife", 0, KNIFE_SLOT, UNASSIGNED },
{ "weapon_brass_knuckle", "brass knuckle", 0, KNIFE_SLOT, UNASSIGNED },
{ "weapon_candy_cane", "candy cane", 0, KNIFE_SLOT, UNASSIGNED },
{ "weapon_dual_knife", "dual knife", 0, KNIFE_SLOT, UNASSIGNED },
{ "weapon_keris", "keris", 0, KNIFE_SLOT, UNASSIGNED },
{ "weapon_mini_axe", "mini axe", 0, KNIFE_SLOT, UNASSIGNED },
{ "weapon_knife", "knife", 0, KNIFE_SLOT, UNASSIGNED },
{ "weapon_ice", "ice fork", 0, KNIFE_SLOT, UNASSIGNED },
{ "weapon_karambit", "karambit", 0, KNIFE_SLOT, UNASSIGNED },
{ "weapon_butterfly", "butterfly", 0, KNIFE_SLOT, UNASSIGNED },


//grenade
{ "weapon_medkit", "medkit", 5, GRENADE_SLOT, UNASSIGNED },
{ "weapon_hegrenade", "hegrenade", 5, GRENADE_SLOT, UNASSIGNED },
{ "weapon_smokegrenade", "smoke", 5, GRENADE_SLOT, UNASSIGNED },
{ "weapon_gasbomb", "gas", 5, GRENADE_SLOT, UNASSIGNED },

};

bool MoE_HandleBuyCommands(CBasePlayer *pPlayer, const char *pszCommand)
{
	if (!pPlayer->CanPlayerBuy(true))
		return false;

	if (HasPlayerItem(pPlayer, pszCommand))
	{
		return false;
	}
		
	auto iter = std::find_if(std::begin(g_MoEWeaponBuyInfo), std::end(g_MoEWeaponBuyInfo), 
		[pszCommand](const MoEWeaponBuyInfo_s &info) {
			return !strcmp(info.pszClassName, pszCommand);
		}
	);

	if (iter != std::end(g_MoEWeaponBuyInfo))
	{
		if (pPlayer->m_iAccount < iter->iCost)
		{
			ClientPrint(pPlayer->pev, HUD_PRINTCENTER, "#Not_Enough_Money");
			BlinkAccount(pPlayer, 2);

			return false;
		}

		switch (iter->iSlot)
		{
		case PRIMARY_WEAPON_SLOT:
			DropPrimary(pPlayer);
			break;
		case PISTOL_SLOT :
			DropSecondary(pPlayer);
			break;
		case KNIFE_SLOT:
			if (pPlayer->m_rgpPlayerItems[KNIFE_SLOT])
			{
				pPlayer->RemovePlayerItem(pPlayer->m_rgpPlayerItems[KNIFE_SLOT]);
			}
			break;
		default:
			break;
		}

		pPlayer->GiveNamedItem(iter->pszClassName);
		pPlayer->AddAccount(-iter->iCost);
		
		return true;
	}

	return false;
}
