/*
player_msg.cpp - CSMoE Server : CBasePlayer messages
Copyright (C) 2019 Moemod Hyakuya

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
#include "gamerules.h"

#include "player.h"

// global vars
int giPrecacheGrunt = 0;
int gmsgWeapPickup = 0;
int gmsgHudText = 0;
int gmsgHudTextArgs = 0;
int gmsgShake = 0;
int gmsgFade = 0;
int gmsgFlashlight = 0;
int gmsgFlashBattery = 0;
int gmsgResetHUD = 0;
int gmsgInitHUD = 0;
int gmsgViewMode = 0;
int gmsgShowGameTitle = 0;
int gmsgCurWeapon = 0;
int gmsgHealth = 0;
int gmsgDamage = 0;
int gmsgBattery = 0;
int gmsgTrain = 0;
int gmsgLogo = 0;
int gmsgWeaponList = 0;
int gmsgAmmoX = 0;
int gmsgDeathMsg = 0;
int gmsgScoreAttrib = 0;
int gmsgScoreInfo = 0;
int gmsgTeamInfo = 0;
int gmsgTeamScore = 0;
int gmsgGameMode = 0;
int gmsgMOTD = 0;
int gmsgServerName = 0;
int gmsgAmmoPickup = 0;
int gmsgItemPickup = 0;
int gmsgHideWeapon = 0;
int gmsgSayText = 0;
int gmsgTextMsg = 0;
int gmsgSetFOV = 0;
int gmsgShowMenu = 0;
int gmsgSendAudio = 0;
int gmsgRoundTime = 0;
int gmsgMoney = 0;
int gmsgBlinkAcct = 0;
int gmsgArmorType = 0;
int gmsgStatusValue = 0;
int gmsgStatusText = 0;
int gmsgStatusIcon = 0;
int gmsgBarTime = 0;
int gmsgReloadSound = 0;
int gmsgCrosshair = 0;
int gmsgNVGToggle = 0;
int gmsgRadar = 0;
int gmsgSpectator = 0;
int gmsgVGUIMenu = 0;
int gmsgCZCareer = 0;
int gmsgCZCareerHUD = 0;
int gmsgTaskTime = 0;
int gmsgTutorText = 0;
int gmsgTutorLine = 0;
int gmsgShadowIdx = 0;
int gmsgTutorState = 0;
int gmsgTutorClose = 0;
int gmsgAllowSpec = 0;
int gmsgBombDrop = 0;
int gmsgBombPickup = 0;
int gmsgHostagePos = 0;
int gmsgHostageK = 0;
int gmsgGeigerRange = 0;
int gmsgSendCorpse = 0;
int gmsgHLTV = 0;
int gmsgSpecHealth = 0;
int gmsgForceCam = 0;
int gmsgADStop = 0;
int gmsgReceiveW = 0;
int gmsgScenarioIcon = 0;
int gmsgBotVoice = 0;
int gmsgBuyClose = 0;
int gmsgItemStatus = 0;
int gmsgLocation = 0;
int gmsgSpecHealth2 = 0;
int gmsgBarTime2 = 0;
int gmsgBotProgress = 0;
int gmsgBrass = 0;
int gmsgFog = 0;
int gmsgShowTimer = 0;

int gmsgZBSTip = 0;
int gmsgZBSLevel = 0;
int gmsgBTEWeapon = 0;
int gmsgZB2Msg = 0;
int gmsgZB3Msg = 0;
int gmsgGunDeath = 0;
int gmsgHitMarker = 0;
int gmsgDamagePb = 0;
int gmsgDeathScreen = 0;
int gmsgHotKiller = 0;
int gmsgNightmare = 0;
int gmsgHealthBar = 0;
int gmsgInventoryGive = 0;
int gmsgInventoryGiveEx = 0;

int gmsgPointkill = 0;
int gmsgDoublekill = 0;
int gmsgTriplekill = 0;
int gmsgChainkiller = 0;
int gmsgHeadshotPoint = 0;
int gmsgHeadshot = 0;
int gmsgChainHeadshot = 0;
int gmsgHelmet = 0;
int gmsgStopper = 0;
int gmsgSlugger = 0;
int gmsgPointNumber = 0;
int gmsgFadeViewModel = 0;

int gmsgFragAnimKill = 0;
int gmsgFragAnimHs = 0;
int gmsgFragAnimStopper = 0;
int gmsgFragAnimStopperHs = 0;
int gmsgFragAnimBlue = 0;
int gmsgFragAnimGold = 0;

int	gmsgRoundFrags = 0;
int	gmsgRoundFrags_headshot = 0;
int	gmsgRoundFrags_grenade = 0;
int	gmsgRoundFrags_knife = 0;
int	gmsgRoundFrags_shotgun = 0;
int	gmsgRoundFrags_sniper = 0;

int gmsgReddot = 0;
int gmsgEotech = 0;
int gmsgAcog = 0;
int gmsgDot_l = 0;
int gmsgTelescopic = 0;
int gmsgEotechCrb = 0;
int gmsgEotechPandora = 0;
int gmsgSksScope = 0;
int gmsgSniperScope = 0;
int gmsgAzureScope = 0;
int gmsgEotechDot = 0;


int gmsgKillStar1 = 0;
int gmsgKillStar2 = 0;
int gmsgKillStar3 = 0;
int gmsgKillStar4 = 0;
int gmsgKillStar5 = 0;
int gmsgKillStar6 = 0;
int gmsgKillStar7 = 0;
int gmsgKillStar8 = 0;
int gmsgKillStar9 = 0;
int gmsgKillStar10 = 0;

int gmsgHeadshotStar1 = 0;
int gmsgHeadshotStar2 = 0;
int gmsgHeadshotStar3 = 0;
int gmsgHeadshotStar4 = 0;
int gmsgHeadshotStar5 = 0;
int gmsgHeadshotStar6 = 0;
int gmsgHeadshotStar7 = 0;
int gmsgHeadshotStar8 = 0;
int gmsgHeadshotStar9 = 0;
int gmsgHeadshotStar10 = 0;

int gmsgBlueStar5 = 0;
int gmsgGoldStar10 = 0;

int gmsgStopperStar1 = 0;
int gmsgStopperStar2 = 0;
int gmsgStopperStar3 = 0;
int gmsgStopperStar4 = 0;
int gmsgStopperStar5 = 0;
int gmsgStopperStar6 = 0;
int gmsgStopperStar7 = 0;
int gmsgStopperStar8 = 0;
int gmsgStopperStar9 = 0;
int gmsgStopperStar10 = 0;

int gmsgStopperHsStar1 = 0;
int gmsgStopperHsStar2 = 0;
int gmsgStopperHsStar3 = 0;
int gmsgStopperHsStar4 = 0;
int gmsgStopperHsStar5 = 0;
int gmsgStopperHsStar6 = 0;
int gmsgStopperHsStar7 = 0;
int gmsgStopperHsStar8 = 0;
int gmsgStopperHsStar9 = 0;
int gmsgStopperHsStar10 = 0;

int gmsgSluggerStar1 = 0;
int gmsgSluggerStar2 = 0;
int gmsgSluggerStar3 = 0;
int gmsgSluggerStar4 = 0;
int gmsgSluggerStar5 = 0;
int gmsgSluggerStar6 = 0;
int gmsgSluggerStar7 = 0;
int gmsgSluggerStar8 = 0;
int gmsgSluggerStar9 = 0;
int gmsgSluggerStar10 = 0;

int gmsgSluggerHsStar1 = 0;
int gmsgSluggerHsStar2 = 0;
int gmsgSluggerHsStar3 = 0;
int gmsgSluggerHsStar4 = 0;
int gmsgSluggerHsStar5 = 0;
int gmsgSluggerHsStar6 = 0;
int gmsgSluggerHsStar7 = 0;
int gmsgSluggerHsStar8 = 0;
int gmsgSluggerHsStar9 = 0;
int gmsgSluggerHsStar10 = 0;

int gmsgC4_hud = 0;

int gmsgPos1 = 0;
int gmsgPos2 = 0;

int gmsgHeadName = 0;

int gmsgupdateitem = 0;
int gmsgQuickDeploy_client = 0;
int gmsgQuickReload_client = 0;
int gmsgPlayerUpdate = 0;


// utils
inline int FNullEnt(CBaseEntity *ent) { return (!ent) || FNullEnt(ent->edict()); }

// main code

void LinkUserMessages()
{
	if (gmsgCurWeapon)
		return;

	gmsgCurWeapon = REG_USER_MSG("CurWeapon", -1); // 3
	gmsgGeigerRange = REG_USER_MSG("Geiger", 1);
	gmsgFlashlight = REG_USER_MSG("Flashlight", 2);
	gmsgFlashBattery = REG_USER_MSG("FlashBat", 1);
	gmsgHealth = REG_USER_MSG("Health", 2); // 1
	gmsgDamage = REG_USER_MSG("Damage", 12);
	gmsgBattery = REG_USER_MSG("Battery", 2);
	gmsgTrain = REG_USER_MSG("Train", 1);
	gmsgHudText = REG_USER_MSG("HudTextPro", -1);
	REG_USER_MSG("HudText", -1);
	gmsgSayText = REG_USER_MSG("SayText", -1);
	gmsgTextMsg = REG_USER_MSG("TextMsg", -1);
	gmsgWeaponList = REG_USER_MSG("WeaponList", -1);
	gmsgResetHUD = REG_USER_MSG("ResetHUD", 0);
	gmsgInitHUD = REG_USER_MSG("InitHUD", 0);
	gmsgViewMode = REG_USER_MSG("ViewMode", 0);
	gmsgShowGameTitle = REG_USER_MSG("GameTitle", 1);
	gmsgDeathMsg = REG_USER_MSG("DeathMsg", -1);
	gmsgScoreAttrib = REG_USER_MSG("ScoreAttrib", 2);
	gmsgScoreInfo = REG_USER_MSG("ScoreInfo", 9);
	gmsgTeamInfo = REG_USER_MSG("TeamInfo", -1);
	gmsgTeamScore = REG_USER_MSG("TeamScore", -1);
	gmsgGameMode = REG_USER_MSG("GameMode", -1); // modified
	gmsgMOTD = REG_USER_MSG("MOTD", -1);
	gmsgServerName = REG_USER_MSG("ServerName", -1);
	gmsgAmmoPickup = REG_USER_MSG("AmmoPickup", 2);
	gmsgWeapPickup = REG_USER_MSG("WeapPickup", 1);
	gmsgItemPickup = REG_USER_MSG("ItemPickup", -1);
	gmsgHideWeapon = REG_USER_MSG("HideWeapon", 1);
	gmsgSetFOV = REG_USER_MSG("SetFOV", 1);
	gmsgShowMenu = REG_USER_MSG("ShowMenu", -1);
	gmsgShake = REG_USER_MSG("ScreenShake", 6);
	gmsgFade = REG_USER_MSG("ScreenFade", 10);
	gmsgAmmoX = REG_USER_MSG("AmmoX", -1); // 2
	gmsgSendAudio = REG_USER_MSG("SendAudio", -1);
	gmsgRoundTime = REG_USER_MSG("RoundTime", 2);
	gmsgMoney = REG_USER_MSG("Money", 5);
	gmsgArmorType = REG_USER_MSG("ArmorType", 1);
	gmsgBlinkAcct = REG_USER_MSG("BlinkAcct", 1);
	gmsgStatusValue = REG_USER_MSG("StatusValue", -1);
	gmsgStatusText = REG_USER_MSG("StatusText", -1);
	gmsgStatusIcon = REG_USER_MSG("StatusIcon", -1);
	gmsgBarTime = REG_USER_MSG("BarTime", 2);
	gmsgReloadSound = REG_USER_MSG("ReloadSound", 2);
	gmsgCrosshair = REG_USER_MSG("Crosshair", 1);
	gmsgNVGToggle = REG_USER_MSG("NVGToggle", 1);
	gmsgRadar = REG_USER_MSG("Radar", 7);
	gmsgSpectator = REG_USER_MSG("Spectator", 2);
	gmsgVGUIMenu = REG_USER_MSG("VGUIMenu", -1);
	gmsgTutorText = REG_USER_MSG("TutorText", -1);
	gmsgTutorLine = REG_USER_MSG("TutorLine", -1);
	gmsgTutorState = REG_USER_MSG("TutorState", -1);
	gmsgTutorClose = REG_USER_MSG("TutorClose", -1);
	gmsgAllowSpec = REG_USER_MSG("AllowSpec", 1);
	gmsgBombDrop = REG_USER_MSG("BombDrop", 7);
	gmsgBombPickup = REG_USER_MSG("BombPickup", 0);
	gmsgSendCorpse = REG_USER_MSG("ClCorpse", -1);
	gmsgHostagePos = REG_USER_MSG("HostagePos", 8);
	gmsgHostageK = REG_USER_MSG("HostageK", 1);
	gmsgHLTV = REG_USER_MSG("HLTV", 2);
	gmsgSpecHealth = REG_USER_MSG("SpecHealth", 1);
	gmsgForceCam = REG_USER_MSG("ForceCam", 3);
	gmsgADStop = REG_USER_MSG("ADStop", 0);
	gmsgReceiveW = REG_USER_MSG("ReceiveW", 1);
	gmsgCZCareer = REG_USER_MSG("CZCareer", -1);
	gmsgCZCareerHUD = REG_USER_MSG("CZCareerHUD", -1);
	gmsgShadowIdx = REG_USER_MSG("ShadowIdx", 4);
	gmsgTaskTime = REG_USER_MSG("TaskTime", 4);
	gmsgScenarioIcon = REG_USER_MSG("Scenario", -1);
	gmsgBotVoice = REG_USER_MSG("BotVoice", 2);
	gmsgBuyClose = REG_USER_MSG("BuyClose", 0);
	gmsgSpecHealth2 = REG_USER_MSG("SpecHealth2", 2);
	gmsgBarTime2 = REG_USER_MSG("BarTime2", 4);
	gmsgItemStatus = REG_USER_MSG("ItemStatus", 1);
	gmsgLocation = REG_USER_MSG("Location", -1);
	gmsgBotProgress = REG_USER_MSG("BotProgress", -1);
	gmsgBrass = REG_USER_MSG("Brass", -1);
	gmsgFog = REG_USER_MSG("Fog", 7);
	gmsgShowTimer = REG_USER_MSG("ShowTimer", 0);
	gmsgHudTextArgs = REG_USER_MSG("HudTextArgs", -1);

	gmsgZBSTip = REG_USER_MSG("ZBSTip", -1);
	gmsgZBSLevel = REG_USER_MSG("ZBSLevel", -1);
	gmsgBTEWeapon = REG_USER_MSG("BTEWeapon", -1);
	gmsgZB2Msg = REG_USER_MSG("ZB2Msg", -1);
	gmsgZB3Msg = REG_USER_MSG("ZB3Msg", -1);
	gmsgGunDeath = REG_USER_MSG("GunDeath", -1);

gmsgHitMarker = REG_USER_MSG("HitMarker", -1);
gmsgDamagePb = REG_USER_MSG("DamagePb", -1);
gmsgDeathScreen = REG_USER_MSG("DeathScreen", -1);
gmsgHotKiller = REG_USER_MSG("HotKiller", -1);
gmsgNightmare = REG_USER_MSG("Nightmare", -1);
gmsgHealthBar = REG_USER_MSG("HealthBar", -1);
gmsgInventoryGive = REG_USER_MSG("InventoryGive", -1);
gmsgInventoryGiveEx = REG_USER_MSG("InventoryGiveEx", -1);

gmsgRoundFrags = REG_USER_MSG("RoundFrags", -1);
	gmsgRoundFrags_headshot = REG_USER_MSG("RoundFrags_headshot", -1);
	gmsgRoundFrags_grenade = REG_USER_MSG("RoundFrags_grenade", -1);
	gmsgRoundFrags_knife = REG_USER_MSG("RoundFrags_knifes", -1);
	gmsgRoundFrags_shotgun = REG_USER_MSG("RoundFrags_shotgun", -1);
	gmsgRoundFrags_sniper = REG_USER_MSG("RoundFrags_sniper", -1);

//kill effect announcement 
gmsgPointkill = REG_USER_MSG("Pointkill", -1);
gmsgDoublekill = REG_USER_MSG("Doublekill", -1);
gmsgTriplekill = REG_USER_MSG("Triplekill", -1);
gmsgChainkiller = REG_USER_MSG("Chainkiller", -1);
gmsgHeadshotPoint = REG_USER_MSG("HeadshotPoint", -1);
gmsgHeadshot = REG_USER_MSG("Headshot", -1);
gmsgChainHeadshot = REG_USER_MSG("ChainHeadshot", -1);
gmsgHelmet = REG_USER_MSG("Helmet", -1);
gmsgStopper = REG_USER_MSG("Stopper", -1);
gmsgSlugger = REG_USER_MSG("Slugger", -1);
gmsgPointNumber = REG_USER_MSG("PointNumber", -1);
gmsgFadeViewModel = REG_USER_MSG("FadeViewModel", -1);

//underneath anim stars 
gmsgFragAnimKill = REG_USER_MSG("FragAnimKill", -1);
gmsgFragAnimHs = REG_USER_MSG("FragAnimHs", -1);
gmsgFragAnimStopper = REG_USER_MSG("FragAnimStopper", -1);
gmsgFragAnimStopperHs = REG_USER_MSG("FragAnimStopperHs", -1);
gmsgFragAnimBlue = REG_USER_MSG("FragAnimBlue", -1);
gmsgFragAnimGold = REG_USER_MSG("FragAnimGold", -1);

gmsgReddot = REG_USER_MSG("Reddot_Scope", -1);
gmsgEotech = REG_USER_MSG("Eotech_Scope", -1);
gmsgAcog = REG_USER_MSG("Acog_Scope", -1);
gmsgDot_l = REG_USER_MSG("Dot_l_Scope", -1);
gmsgTelescopic = REG_USER_MSG("Telescopic_Scope", -1);
gmsgEotechCrb = REG_USER_MSG("EotechCrb_Scope", -1);
gmsgEotechPandora = REG_USER_MSG("EotechPandora_Scope", -1);
gmsgSksScope = REG_USER_MSG("Sks_Scope", -1);
gmsgSniperScope = REG_USER_MSG("Sniper_Scope", -1);
gmsgAzureScope = REG_USER_MSG("Azure_Scope", -1);
gmsgEotechDot = REG_USER_MSG("EotechDot_Scope", -1);

//specific stars for kill

gmsgKillStar1 = REG_USER_MSG("KillStar1", -1);
gmsgKillStar2 = REG_USER_MSG("KillStar2", -1);
gmsgKillStar3 = REG_USER_MSG("KillStar3", -1);
gmsgKillStar4 = REG_USER_MSG("KillStar4", -1);
gmsgKillStar5 = REG_USER_MSG("KillStar5", -1);
gmsgKillStar6 = REG_USER_MSG("KillStar6", -1);
gmsgKillStar7 = REG_USER_MSG("KillStar7", -1);
gmsgKillStar8 = REG_USER_MSG("KillStar8", -1);
gmsgKillStar9 = REG_USER_MSG("KillStar9", -1);
gmsgKillStar10 = REG_USER_MSG("KillStar10", -1);

gmsgHeadshotStar1 = REG_USER_MSG("HeadshotStar1", -1);
gmsgHeadshotStar2 = REG_USER_MSG("HeadshotStar2", -1);
gmsgHeadshotStar3 = REG_USER_MSG("HeadshotStar3", -1);
gmsgHeadshotStar4 = REG_USER_MSG("HeadshotStar4", -1);
gmsgHeadshotStar5 = REG_USER_MSG("HeadshotStar5", -1);
gmsgHeadshotStar6 = REG_USER_MSG("HeadshotStar6", -1);
gmsgHeadshotStar7 = REG_USER_MSG("HeadshotStar7", -1);
gmsgHeadshotStar8 = REG_USER_MSG("HeadshotStar8", -1);
gmsgHeadshotStar9 = REG_USER_MSG("HeadshotStar9", -1);
gmsgHeadshotStar10 = REG_USER_MSG("HeadshotStar10", -1);

gmsgStopperStar1 = REG_USER_MSG("StopperStar1", -1);
gmsgStopperStar2 = REG_USER_MSG("StopperStar2", -1);
gmsgStopperStar3 = REG_USER_MSG("StopperStar3", -1);
gmsgStopperStar4 = REG_USER_MSG("StopperStar4", -1);
gmsgStopperStar5 = REG_USER_MSG("StopperStar5", -1);
gmsgStopperStar6 = REG_USER_MSG("StopperStar6", -1);
gmsgStopperStar7 = REG_USER_MSG("StopperStar7", -1);
gmsgStopperStar8 = REG_USER_MSG("StopperStar8", -1);
gmsgStopperStar9 = REG_USER_MSG("StopperStar9", -1);
gmsgStopperStar10 = REG_USER_MSG("StopperStar10", -1);

gmsgBlueStar5 = REG_USER_MSG("BlueStar5", -1);
gmsgGoldStar10 = REG_USER_MSG("GoldStar10", -1);
/*
gmsgStopperHsStar1 = REG_USER_MSG("StopperHsStar1", -1);
gmsgStopperHsStar2 = REG_USER_MSG("StopperHsStar2", -1);
gmsgStopperHsStar3 = REG_USER_MSG("StopperHsStar3", -1);
gmsgStopperHsStar4 = REG_USER_MSG("StopperHsStar4", -1);
gmsgStopperHsStar5 = REG_USER_MSG("StopperHsStar5", -1);
gmsgStopperHsStar6 = REG_USER_MSG("StopperHsStar6", -1);
gmsgStopperHsStar7 = REG_USER_MSG("StopperHsStar6", -1);
gmsgStopperHsStar8 = REG_USER_MSG("StopperHsStar8", -1);
gmsgStopperHsStar9 = REG_USER_MSG("StopperHsStar9", -1);
gmsgStopperHsStar10 = REG_USER_MSG("StopperHsStar10", -1);

gmsgSluggerStar1 = REG_USER_MSG("SluggerStar1", -1);
gmsgSluggerStar2 = REG_USER_MSG("SluggerStar2", -1);
gmsgSluggerStar3 = REG_USER_MSG("SluggerStar3", -1);
gmsgSluggerStar4 = REG_USER_MSG("SluggerStar4", -1);
gmsgSluggerStar5 = REG_USER_MSG("SluggerStar5", -1);
gmsgSluggerStar6 = REG_USER_MSG("SluggerStar6", -1);
gmsgSluggerStar7 = REG_USER_MSG("SluggerStar7", -1);
gmsgSluggerStar8 = REG_USER_MSG("SluggerStar8", -1);
gmsgSluggerStar9 = REG_USER_MSG("SluggerStar9", -1);
gmsgSluggerStar10 = REG_USER_MSG("SluggerStar10", -1);

gmsgSluggerHsStar1 = REG_USER_MSG("SluggerHsStar1", -1);
gmsgSluggerHsStar2 = REG_USER_MSG("SluggerHsStar2", -1);
gmsgSluggerHsStar3 = REG_USER_MSG("SluggerHsStar3", -1);
gmsgSluggerHsStar4 = REG_USER_MSG("SluggerHsStar4", -1);
gmsgSluggerHsStar5 = REG_USER_MSG("SluggerHsStar5", -1);
gmsgSluggerHsStar6 = REG_USER_MSG("SluggerHsStar6", -1);
gmsgSluggerHsStar7 = REG_USER_MSG("SluggerHsStar7", -1);
gmsgSluggerHsStar8 = REG_USER_MSG("SluggerHsStar8", -1);
gmsgSluggerHsStar9 = REG_USER_MSG("SluggerHsStar9", -1);
gmsgSluggerHsStar10 = REG_USER_MSG("SluggerHsStar10", -1);

*/
gmsgPos1 = REG_USER_MSG("Pos1", -1);
gmsgPos2 = REG_USER_MSG("Pos2", -1);

gmsgHeadName = REG_USER_MSG("HeadName", -1);

gmsgC4_hud = REG_USER_MSG("C4_hud", -1);

gmsgupdateitem = REG_USER_MSG("updateitem", -1);
gmsgQuickDeploy_client = REG_USER_MSG("QuickDeploy_client", -1);
gmsgQuickReload_client = REG_USER_MSG("QuickReload_client", -1);
gmsgPlayerUpdate = REG_USER_MSG("PlayerUpdate", -1);

}




void WriteWeaponInfo(CBasePlayer *pPlayer, const ItemInfo &II)
{
	const char *pszName;
	if (!II.pszName)
		pszName = "Empty";
	else
		pszName = II.pszName;

	MESSAGE_BEGIN(MSG_ONE, gmsgWeaponList, NULL, pPlayer->pev);
	WRITE_STRING(pszName);
	WRITE_BYTE(CBasePlayer::GetAmmoIndex(II.pszAmmo1));
	WRITE_BYTE(II.iMaxAmmo1);
	WRITE_BYTE(CBasePlayer::GetAmmoIndex(II.pszAmmo2));
	WRITE_BYTE(II.iMaxAmmo2);
	WRITE_BYTE(II.iSlot);
	WRITE_BYTE(II.iPosition);
	WRITE_BYTE(II.iId);
	WRITE_BYTE(II.iFlags);
	MESSAGE_END();
}

void WriteSigonMessages()
{
	// No need for this
	// WeaponList will be sent when player pick up weapon.

	/*for (int i = 0; i < MAX_WEAPONS; ++i)
	{
		ItemInfo &II = CBasePlayerItem::ItemInfoArray[i];

		if (!II.iId)
			continue;

		WriteWeaponInfo(II);
	}*/
}

void SendItemStatus(CBasePlayer *pPlayer)
{
	int itemStatus = 0;
	if (pPlayer->m_bHasNightVision)
		itemStatus |= ITEM_STATUS_NIGHTVISION;

	if (pPlayer->m_bHasDefuser)
		itemStatus |= ITEM_STATUS_DEFUSER;

	MESSAGE_BEGIN(MSG_ONE, gmsgItemStatus, NULL, pPlayer->pev);
	WRITE_BYTE(itemStatus);
	MESSAGE_END();
}

void SetScoreAttrib(CBasePlayer *dest, CBasePlayer *src)
{
	int state = 0;
	if (src->pev->deadflag != DEAD_NO)
		state |= PLAYER_DEAD;

	if (src->m_bHasC4)
		state |= PLAYER_HAS_C4;

	if (src->m_bIsVIP)
		state |= PLAYER_VIP;

	if (src->m_bIsZombie)
		state |= PLAYER_ZOMBIE;

	if (gmsgScoreAttrib)
	{
		MESSAGE_BEGIN(MSG_ONE, gmsgScoreAttrib, NULL, dest->pev);
		WRITE_BYTE(src->entindex());
		WRITE_BYTE(state);
		MESSAGE_END();
	}
}
