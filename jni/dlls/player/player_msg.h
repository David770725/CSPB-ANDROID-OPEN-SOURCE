/*
player_msg.h - CSMoE Server : CBasePlayer messages
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

#ifndef PLAYER_MSG_H
#define PLAYER_MSG_H
#ifdef _WIN32
#pragma once
#endif

extern int giPrecacheGrunt;
extern int gmsgWeapPickup;
extern int gmsgHudText;
extern int gmsgHudTextArgs;
extern int gmsgShake;
extern int gmsgFade;
extern int gmsgFlashlight;
extern int gmsgFlashBattery;
extern int gmsgResetHUD;
extern int gmsgInitHUD;
extern int gmsgViewMode;
extern int gmsgShowGameTitle;
extern int gmsgCurWeapon;
extern int gmsgHealth;
extern int gmsgDamage;
extern int gmsgBattery;
extern int gmsgTrain;
extern int gmsgLogo;
extern int gmsgWeaponList;
extern int gmsgAmmoX;
extern int gmsgDeathMsg;
extern int gmsgScoreAttrib;
extern int gmsgScoreInfo;
extern int gmsgTeamInfo;
extern int gmsgTeamScore;
extern int gmsgGameMode;
extern int gmsgMOTD;
extern int gmsgServerName;
extern int gmsgAmmoPickup;
extern int gmsgItemPickup;
extern int gmsgHideWeapon;
extern int gmsgSayText;
extern int gmsgTextMsg;
extern int gmsgSetFOV;
extern int gmsgShowMenu;
extern int gmsgSendAudio;
extern int gmsgRoundTime;
extern int gmsgMoney;
extern int gmsgBlinkAcct;
extern int gmsgArmorType;
extern int gmsgStatusValue;
extern int gmsgStatusText;
extern int gmsgStatusIcon;
extern int gmsgBarTime;
extern int gmsgReloadSound;
extern int gmsgCrosshair;
extern int gmsgNVGToggle;
extern int gmsgRadar;
extern int gmsgSpectator;
extern int gmsgVGUIMenu;
extern int gmsgCZCareer;
extern int gmsgCZCareerHUD;
extern int gmsgTaskTime;
extern int gmsgTutorText;
extern int gmsgTutorLine;
extern int gmsgShadowIdx;
extern int gmsgTutorState;
extern int gmsgTutorClose;
extern int gmsgAllowSpec;
extern int gmsgBombDrop;
extern int gmsgBombPickup;
extern int gmsgHostagePos;
extern int gmsgHostageK;
extern int gmsgGeigerRange;
extern int gmsgSendCorpse;
extern int gmsgHLTV;
extern int gmsgSpecHealth;
extern int gmsgForceCam;
extern int gmsgADStop;
extern int gmsgReceiveW;
extern int gmsgScenarioIcon;
extern int gmsgBotVoice;
extern int gmsgBuyClose;
extern int gmsgItemStatus;
extern int gmsgLocation;
extern int gmsgSpecHealth2;
extern int gmsgBarTime2;
extern int gmsgBotProgress;
extern int gmsgBrass;
extern int gmsgFog;
extern int gmsgShowTimer;

extern int gmsgZBSTip;
extern int gmsgZBSLevel;
extern int gmsgBTEWeapon;
extern int gmsgZB2Msg;
extern int gmsgZB3Msg;
extern int gmsgGunDeath;
extern int gmsgHitMarker;
extern int gmsgDamagePb;
extern int gmsgDeathScreen;
extern int gmsgHotKiller;
extern int gmsgNightmare;
extern int gmsgHealthBar;
extern int gmsgInventoryGive;
extern int gmsgInventoryGiveEx;

extern int gmsgPointkill;
extern int gmsgDoublekill;
extern int gmsgTriplekill;
extern int gmsgChainkiller;
extern int gmsgHeadshotPoint;
extern int gmsgHeadshot;
extern int gmsgChainHeadshot;
extern int gmsgHelmet;
extern int gmsgStopper;
extern int gmsgSlugger;
extern int gmsgPointNumber;
extern int gmsgFadeViewModel;

extern int gmsgFragAnimKill;
extern int gmsgFragAnimHs;
extern int gmsgFragAnimStopper;
extern int gmsgFragAnimStopperHs;
extern int gmsgFragAnimBlue;
extern int gmsgFragAnimGold;

extern int		gmsgRoundFrags;
extern int		gmsgRoundFrags_headshot;
extern int		gmsgRoundFrags_grenade;
extern int		gmsgRoundFrags_knife;
extern int		gmsgRoundFrags_shotgun;
extern int		gmsgRoundFrags_sniper;

extern int gmsgReddot; 
extern int gmsgEotech;
extern int gmsgAcog;
extern int gmsgDot_l;
extern int gmsgTelescopic;
extern int gmsgEotechCrb;
extern int gmsgEotechPandora;
extern int gmsgSksScope;
extern int gmsgSniperScope;
extern int gmsgAzureScope;
extern int gmsgEotechDot;

extern int gmsgKillStar1;
extern int gmsgKillStar2;
extern int gmsgKillStar3;
extern int gmsgKillStar4;
extern int gmsgKillStar5;
extern int gmsgKillStar6;
extern int gmsgKillStar7;
extern int gmsgKillStar8;
extern int gmsgKillStar9;
extern int gmsgKillStar10;

extern int gmsgHeadshotStar1;
extern int gmsgHeadshotStar2;
extern int gmsgHeadshotStar3;
extern int gmsgHeadshotStar4;
extern int gmsgHeadshotStar5;
extern int gmsgHeadshotStar6;
extern int gmsgHeadshotStar7;
extern int gmsgHeadshotStar8;
extern int gmsgHeadshotStar9;
extern int gmsgHeadshotStar10;

extern int gmsgBlueStar5;
extern int gmsgGoldStar10;

extern int gmsgStopperStar1;
extern int gmsgStopperStar2;
extern int gmsgStopperStar3;
extern int gmsgStopperStar4;
extern int gmsgStopperStar5;
extern int gmsgStopperStar6;
extern int gmsgStopperStar7;
extern int gmsgStopperStar8;
extern int gmsgStopperStar9;
extern int gmsgStopperStar10;

extern int gmsgStopperHsStar1;
extern int gmsgStopperHsStar2;
extern int gmsgStopperHsStar3;
extern int gmsgStopperHsStar4;
extern int gmsgStopperHsStar5;
extern int gmsgStopperHsStar6;
extern int gmsgStopperHsStar7;
extern int gmsgStopperHsStar8;
extern int gmsgStopperHsStar9;
extern int gmsgStopperHsStar10;

extern int gmsgSluggerHsStar1;
extern int gmsgStopperHsStar2;
extern int gmsgStopperHsStar3;
extern int gmsgStopperHsStar4;
extern int gmsgStopperHsStar5;
extern int gmsgStopperHsStar6;
extern int gmsgStopperHsStar7;
extern int gmsgStopperHsStar8;
extern int gmsgStopperHsStar9;
extern int gmsgStopperHsStar10;

extern int gmsgSluggerStar1;
extern int gmsgSluggerStar2;
extern int gmsgSluggerStar3;
extern int gmsgSluggerStar4;
extern int gmsgSluggerStar5;
extern int gmsgSluggerStar6;
extern int gmsgSluggerStar7;
extern int gmsgSluggerStar8;
extern int gmsgSluggerStar9;
extern int gmsgSluggerStar10;

extern int gmsgSluggerHsStar1;
extern int gmsgSluggerHsStar2;
extern int gmsgSluggerHsStar3;
extern int gmsgSluggerHsStar4;
extern int gmsgSluggerHsStar5;
extern int gmsgSluggerHsStar6;
extern int gmsgSluggerHsStar7;
extern int gmsgSluggerHsStar8;
extern int gmsgSluggerHsStar9;
extern int gmsgSluggerHsStar10;

extern int gmsgPos1;
extern int gmsgPos2;

extern int gmsgHeadName;

extern int gmsgC4_hud;

extern int gmsgupdateitem;
extern int gmsgQuickDeploy_client;
extern int gmsgQuickReload_client;

extern int gmsgPlayerUpdate;

void LinkUserMessages();
void WriteSigonMessages();
void SendItemStatus(CBasePlayer *pPlayer);

void SetScoreAttrib(CBasePlayer *dest, CBasePlayer *src);

struct ItemInfo;
void WriteWeaponInfo(CBasePlayer *pPlayer, const ItemInfo &II);
#endif
