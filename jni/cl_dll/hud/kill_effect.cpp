/*
kill_effect.cpp - Point Blank alerts implementation 
Copyright (C) 2020-2024 BillFlx
*/

#include "hud.h"
#include "triangleapi.h"
#include "r_efx.h"
#include "cl_util.h"

#include "draw_util.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#include "hud.h"
#include "cl_util.h"
#include "parsemsg.h"
#include <string.h>
#include "eventscripts.h"


#include "const.h"
#include "entity_state.h"
#include "cl_entity.h"
#include <string.h>
#include <stdio.h>
#include "event_api.h"
#include "com_weapons.h"
#include "kill_effect.h"


//#include "const/const_client.h"
#include "triangleapi.h"

//bill: peduli apa gw
#define XPOS( x ) ( (x) / 16.0f )
#define YPOS( y ) ( (y) / 10.0f  )

#define INT_XPOS(x) int(XPOS(x) * ScreenWidth)
#define INT_YPOS(y) int(YPOS(y) * ScreenHeight)

DECLARE_MESSAGE(m_KillEffect, Count_unit);
DECLARE_COMMAND(m_KillEffect, CommandActiveCount_unit);

//item
DECLARE_MESSAGE(m_KillEffect, buy_qc);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_qc);

DECLARE_MESSAGE(m_KillEffect, buy_megahp);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_megahp);

DECLARE_MESSAGE(m_KillEffect, buy_bpoint);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_bpoint);

DECLARE_MESSAGE(m_KillEffect, buy_qr);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_qr);

DECLARE_MESSAGE(m_KillEffect, buy_mask_1);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_mask_1);

DECLARE_MESSAGE(m_KillEffect, buy_mask_2);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_mask_2);

DECLARE_MESSAGE(m_KillEffect, buy_mask_3);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_mask_3);

DECLARE_MESSAGE(m_KillEffect, buy_mask_4);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_mask_4);

DECLARE_MESSAGE(m_KillEffect, buy_mask_5);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_mask_5);
DECLARE_MESSAGE(m_KillEffect, buy_mask_6);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_mask_6);
DECLARE_MESSAGE(m_KillEffect, buy_mask_7);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_mask_7);
DECLARE_MESSAGE(m_KillEffect, buy_mask_8);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_mask_8);
DECLARE_MESSAGE(m_KillEffect, buy_mask_9);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_mask_9);
DECLARE_MESSAGE(m_KillEffect, buy_mask_10);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_mask_10);
DECLARE_MESSAGE(m_KillEffect, buy_mask_11);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_mask_11);
DECLARE_MESSAGE(m_KillEffect, buy_mask_12);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_mask_12);
DECLARE_MESSAGE(m_KillEffect, buy_mask_13);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_mask_13);

DECLARE_MESSAGE(m_KillEffect, buy_qrespawn);
DECLARE_COMMAND(m_KillEffect, CommandActivebuy_qrespawn);

DECLARE_MESSAGE(m_KillEffect, Unequip_mask);
DECLARE_COMMAND(m_KillEffect, CommandActiveUnequip_mask);


DECLARE_MESSAGE(m_KillEffect, Add_point);
DECLARE_COMMAND(m_KillEffect, CommandActiveAdd_point);

DECLARE_MESSAGE(m_KillEffect, killframe);
DECLARE_COMMAND(m_KillEffect, CommandActivekillframe);

DECLARE_MESSAGE(m_KillEffect, killframeAnim);
DECLARE_COMMAND(m_KillEffect, CommandActivekillframeAnim);

DECLARE_MESSAGE(m_KillEffect, MissionComplete);
DECLARE_COMMAND(m_KillEffect, CommandActiveMissionComplete);

DECLARE_MESSAGE(m_KillEffect, Pointkill);
DECLARE_COMMAND(m_KillEffect, CommandActivePointkill);

DECLARE_MESSAGE(m_KillEffect, PiercingShot);
DECLARE_COMMAND(m_KillEffect, CommandActivePiercingShot);

DECLARE_MESSAGE(m_KillEffect, MassKill);
DECLARE_COMMAND(m_KillEffect, CommandActiveMassKill);

DECLARE_MESSAGE(m_KillEffect, Doublekill);
DECLARE_COMMAND(m_KillEffect, CommandActiveDoublekill);

DECLARE_MESSAGE(m_KillEffect, Triplekill);
DECLARE_COMMAND(m_KillEffect, CommandActiveTriplekill);

DECLARE_MESSAGE(m_KillEffect, Chainkiller);
DECLARE_COMMAND(m_KillEffect, CommandActiveChainkiller);

DECLARE_MESSAGE(m_KillEffect, HeadshotPoint);
DECLARE_COMMAND(m_KillEffect, CommandActiveHeadshotPoint);

DECLARE_MESSAGE(m_KillEffect, Headshot);
DECLARE_COMMAND(m_KillEffect, CommandActiveHeadshot);

DECLARE_MESSAGE(m_KillEffect, ChainHeadshot);
DECLARE_COMMAND(m_KillEffect, CommandActiveChainHeadshot);

DECLARE_MESSAGE(m_KillEffect, Helmet);
DECLARE_COMMAND(m_KillEffect, CommandActiveHelmet);

DECLARE_MESSAGE(m_KillEffect, Stopper);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopper);

DECLARE_MESSAGE(m_KillEffect, Slugger);
DECLARE_COMMAND(m_KillEffect, CommandActiveSlugger);

DECLARE_MESSAGE(m_KillEffect, PointNumber);
DECLARE_COMMAND(m_KillEffect, CommandActivePointNumber);

DECLARE_MESSAGE(m_KillEffect, HitMarker);
DECLARE_COMMAND(m_KillEffect, CommandActiveHitMarker);



DECLARE_MESSAGE(m_KillEffect, HotKiller);
DECLARE_COMMAND(m_KillEffect, CommandActiveHotKiller);

DECLARE_MESSAGE(m_KillEffect, Nightmare);
DECLARE_COMMAND(m_KillEffect, CommandActiveNightmare);



DECLARE_MESSAGE(m_KillEffect, FragAnimKill);
DECLARE_COMMAND(m_KillEffect, CommandActiveFragAnimKill);

DECLARE_MESSAGE(m_KillEffect, FragAnimHs);
DECLARE_COMMAND(m_KillEffect, CommandActiveFragAnimHs);

DECLARE_MESSAGE(m_KillEffect, FragAnimStopper);
DECLARE_COMMAND(m_KillEffect, CommandActiveFragAnimStopper);

DECLARE_MESSAGE(m_KillEffect, FragAnimBlue);
DECLARE_COMMAND(m_KillEffect, CommandActiveFragAnimBlue);

DECLARE_MESSAGE(m_KillEffect, FragAnimGold);
DECLARE_COMMAND(m_KillEffect, CommandActiveFragAnimGold);

DECLARE_MESSAGE(m_KillEffect, Pos1);
DECLARE_COMMAND(m_KillEffect, CommandActivePos1);

DECLARE_MESSAGE(m_KillEffect, Pos2);
DECLARE_COMMAND(m_KillEffect, CommandActivePos2);

//special
DECLARE_MESSAGE(m_KillEffect, SpecialGunner);
DECLARE_COMMAND(m_KillEffect, CommandActiveSpecialGunner);DECLARE_MESSAGE(m_KillEffect, BombShot);
DECLARE_COMMAND(m_KillEffect, CommandActiveBombShot);DECLARE_MESSAGE(m_KillEffect, oneShot);
DECLARE_COMMAND(m_KillEffect, CommandActiveoneShot);

DECLARE_MESSAGE(m_KillEffect, OneshotEnable);
DECLARE_COMMAND(m_KillEffect, CommandActiveOneshotEnable);

DECLARE_MESSAGE(m_KillEffect, OneshotDisable);
DECLARE_COMMAND(m_KillEffect, CommandActiveOneshotDisable);

DECLARE_MESSAGE(m_KillEffect, KillStar1);
DECLARE_MESSAGE(m_KillEffect, KillStar2);
DECLARE_MESSAGE(m_KillEffect, KillStar3);
DECLARE_MESSAGE(m_KillEffect, KillStar4);
DECLARE_MESSAGE(m_KillEffect, KillStar5);
DECLARE_MESSAGE(m_KillEffect, KillStar6);
DECLARE_MESSAGE(m_KillEffect, KillStar7);
DECLARE_MESSAGE(m_KillEffect, KillStar8);
DECLARE_MESSAGE(m_KillEffect, KillStar9);
DECLARE_MESSAGE(m_KillEffect, KillStar10);

DECLARE_MESSAGE(m_KillEffect, HeadshotStar1);
DECLARE_MESSAGE(m_KillEffect, HeadshotStar2);
DECLARE_MESSAGE(m_KillEffect, HeadshotStar3);
DECLARE_MESSAGE(m_KillEffect, HeadshotStar4);
DECLARE_MESSAGE(m_KillEffect, HeadshotStar5);
DECLARE_MESSAGE(m_KillEffect, HeadshotStar6);
DECLARE_MESSAGE(m_KillEffect, HeadshotStar7);
DECLARE_MESSAGE(m_KillEffect, HeadshotStar8);
DECLARE_MESSAGE(m_KillEffect, HeadshotStar9);
DECLARE_MESSAGE(m_KillEffect, HeadshotStar10);

DECLARE_MESSAGE(m_KillEffect, BlueStar5);
DECLARE_MESSAGE(m_KillEffect, GoldStar10);

DECLARE_MESSAGE(m_KillEffect, StopperStar1);
DECLARE_MESSAGE(m_KillEffect, StopperStar2);
DECLARE_MESSAGE(m_KillEffect, StopperStar3);
DECLARE_MESSAGE(m_KillEffect, StopperStar4);
DECLARE_MESSAGE(m_KillEffect, StopperStar5);
DECLARE_MESSAGE(m_KillEffect, StopperStar6);
DECLARE_MESSAGE(m_KillEffect, StopperStar7);
DECLARE_MESSAGE(m_KillEffect, StopperStar8);
DECLARE_MESSAGE(m_KillEffect, StopperStar9);
DECLARE_MESSAGE(m_KillEffect, StopperStar10);

DECLARE_MESSAGE(m_KillEffect, StopperHsStar1);
DECLARE_MESSAGE(m_KillEffect, StopperHsStar2);
DECLARE_MESSAGE(m_KillEffect, StopperHsStar3);
DECLARE_MESSAGE(m_KillEffect, StopperHsStar4);
DECLARE_MESSAGE(m_KillEffect, StopperHsStar5);
DECLARE_MESSAGE(m_KillEffect, StopperHsStar6);
DECLARE_MESSAGE(m_KillEffect, StopperHsStar7);
DECLARE_MESSAGE(m_KillEffect, StopperHsStar8);
DECLARE_MESSAGE(m_KillEffect, StopperHsStar9);
DECLARE_MESSAGE(m_KillEffect, StopperHsStar10);

DECLARE_MESSAGE(m_KillEffect, SluggerStar1);
DECLARE_MESSAGE(m_KillEffect, SluggerStar2);
DECLARE_MESSAGE(m_KillEffect, SluggerStar3);
DECLARE_MESSAGE(m_KillEffect, SluggerStar4);
DECLARE_MESSAGE(m_KillEffect, SluggerStar5);
DECLARE_MESSAGE(m_KillEffect, SluggerStar6);
DECLARE_MESSAGE(m_KillEffect, SluggerStar7);
DECLARE_MESSAGE(m_KillEffect, SluggerStar8);
DECLARE_MESSAGE(m_KillEffect, SluggerStar9);
DECLARE_MESSAGE(m_KillEffect, SluggerStar10);

DECLARE_MESSAGE(m_KillEffect, SluggerHsStar1);
DECLARE_MESSAGE(m_KillEffect, SluggerHsStar2);
DECLARE_MESSAGE(m_KillEffect, SluggerHsStar3);
DECLARE_MESSAGE(m_KillEffect, SluggerHsStar4);
DECLARE_MESSAGE(m_KillEffect, SluggerHsStar5);
DECLARE_MESSAGE(m_KillEffect, SluggerHsStar6);
DECLARE_MESSAGE(m_KillEffect, SluggerHsStar7);
DECLARE_MESSAGE(m_KillEffect, SluggerHsStar8);
DECLARE_MESSAGE(m_KillEffect, SluggerHsStar9);
DECLARE_MESSAGE(m_KillEffect, SluggerHsStar10);

DECLARE_COMMAND(m_KillEffect, CommandActiveKillStar1);
DECLARE_COMMAND(m_KillEffect, CommandActiveKillStar2);
DECLARE_COMMAND(m_KillEffect, CommandActiveKillStar3);
DECLARE_COMMAND(m_KillEffect, CommandActiveKillStar4);
DECLARE_COMMAND(m_KillEffect, CommandActiveKillStar5);
DECLARE_COMMAND(m_KillEffect, CommandActiveKillStar6);
DECLARE_COMMAND(m_KillEffect, CommandActiveKillStar7);
DECLARE_COMMAND(m_KillEffect, CommandActiveKillStar8);
DECLARE_COMMAND(m_KillEffect, CommandActiveKillStar9);
DECLARE_COMMAND(m_KillEffect, CommandActiveKillStar10);

DECLARE_COMMAND(m_KillEffect, CommandActiveHeadshotStar1);
DECLARE_COMMAND(m_KillEffect, CommandActiveHeadshotStar2);
DECLARE_COMMAND(m_KillEffect, CommandActiveHeadshotStar3);
DECLARE_COMMAND(m_KillEffect, CommandActiveHeadshotStar4);
DECLARE_COMMAND(m_KillEffect, CommandActiveHeadshotStar5);
DECLARE_COMMAND(m_KillEffect, CommandActiveHeadshotStar6);
DECLARE_COMMAND(m_KillEffect, CommandActiveHeadshotStar7);
DECLARE_COMMAND(m_KillEffect, CommandActiveHeadshotStar8);
DECLARE_COMMAND(m_KillEffect, CommandActiveHeadshotStar9);
DECLARE_COMMAND(m_KillEffect, CommandActiveHeadshotStar10);

DECLARE_COMMAND(m_KillEffect, CommandActiveBlueStar5);
DECLARE_COMMAND(m_KillEffect, CommandActiveGoldStar10);

DECLARE_COMMAND(m_KillEffect, CommandActiveStopperStar1);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperStar2);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperStar3);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperStar4);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperStar5);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperStar6);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperStar7);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperStar8);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperStar9);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperStar10);

DECLARE_COMMAND(m_KillEffect, CommandActiveStopperHsStar1);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperHsStar2);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperHsStar3);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperHsStar4);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperHsStar5);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperHsStar6);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperHsStar7);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperHsStar8);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperHsStar9);
DECLARE_COMMAND(m_KillEffect, CommandActiveStopperHsStar10);

DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerStar1);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerStar2);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerStar3);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerStar4);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerStar5);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerStar6);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerStar7);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerStar8);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerStar9);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerStar10);

DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerHsStar1);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerHsStar2);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerHsStar3);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerHsStar4);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerHsStar5);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerHsStar6);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerHsStar7);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerHsStar8);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerHsStar9);
DECLARE_COMMAND(m_KillEffect, CommandActiveSluggerHsStar10);


void CHudKillEffect::UserCmd_CommandActiveUnequip_mask(void)
{
ClientCmd("billflxcrypted_item_mask 0");
}

//unit count
void CHudKillEffect::UserCmd_CommandActiveCount_unit(void)
{
/*if (gHUD.item_QuickDeploy->value == 1)
{
gHUD.unit_item_QuickDeploy->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_quickdeploy", gHUD.unit_item_QuickDeploy->value);
}

if (gHUD.item_QuickReload->value == 1)
{
gHUD.unit_item_QuickReload->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_quickreload", gHUD.unit_item_QuickReload->value);
}

if (gHUD.item_MegaHp->value == 1)
{
gHUD.unit_item_MegaHp->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_megahp", gHUD.unit_item_MegaHp->value);
}


//unit count mask
if (gHUD.item_mask->value == 1)
{
gHUD.unit_item_mask_1->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_1", gHUD.unit_item_mask_1->value);
}
else if (gHUD.item_mask->value == 2)
{
gHUD.unit_item_mask_2->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_2", gHUD.unit_item_mask_2->value);
}
else if (gHUD.item_mask->value == 3)
{
gHUD.unit_item_mask_3->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_3", gHUD.unit_item_mask_3->value);
}
else if (gHUD.item_mask->value == 4)
{
gHUD.unit_item_mask_4->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_4", gHUD.unit_item_mask_4->value);
}
else if (gHUD.item_mask->value == 5)
{
gHUD.unit_item_mask_5->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_5", gHUD.unit_item_mask_5->value);
}
else if (gHUD.item_mask->value == 6)
{
gHUD.unit_item_mask_6->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_6", gHUD.unit_item_mask_6->value);
}
else if (gHUD.item_mask->value == 7)
{
gHUD.unit_item_mask_7->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_7", gHUD.unit_item_mask_7->value);
}
else if (gHUD.item_mask->value == 8)
{
gHUD.unit_item_mask_8->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_8", gHUD.unit_item_mask_8->value);
}
else if (gHUD.item_mask->value == 9)
{
gHUD.unit_item_mask_9->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_9", gHUD.unit_item_mask_9->value);
}
else if (gHUD.item_mask->value == 10)
{
gHUD.unit_item_mask_10->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_10", gHUD.unit_item_mask_10->value);
}
else if (gHUD.item_mask->value == 11)
{
gHUD.unit_item_mask_11->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_11", gHUD.unit_item_mask_11->value);
}
else if (gHUD.item_mask->value == 12)
{
gHUD.unit_item_mask_12->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_12", gHUD.unit_item_mask_12->value);
}
else if (gHUD.item_mask->value == 13)
{
gHUD.unit_item_mask_13->value -= 1;
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_13", gHUD.unit_item_mask_13->value);
}



//revert back value when unit is 0

if (gHUD.unit_item_QuickDeploy->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_quickdeploy_enable", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_quickdeploy", 100);
}

if (gHUD.unit_item_QuickReload->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_quickreload_enable", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_quickreload", 100);
}

if (gHUD.unit_item_MegaHp->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_megahp_enable", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_megahp", 100);
}

if (gHUD.unit_item_mask_1->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_item_mask", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_1", 100);
}

if (gHUD.unit_item_mask_2->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_item_mask", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_2", 100);
}

if (gHUD.unit_item_mask_3->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_item_mask", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_3", 100);
}

if (gHUD.unit_item_mask_4->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_item_mask", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_4", 100);
}

if (gHUD.unit_item_mask_5->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_item_mask", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_5", 100);
}

if (gHUD.unit_item_mask_6->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_item_mask", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_6", 100);
}

if (gHUD.unit_item_mask_7->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_item_mask", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_7", 100);
}
if (gHUD.unit_item_mask_8->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_item_mask", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_8", 100);
}
if (gHUD.unit_item_mask_9->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_item_mask", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_9", 100);
}
if (gHUD.unit_item_mask_10->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_item_mask", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_10", 100);
}
if (gHUD.unit_item_mask_11->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_item_mask", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_11", 100);
}
if (gHUD.unit_item_mask_12->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_item_mask", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_12", 100);
}
if (gHUD.unit_item_mask_13->value == 0)
{
gEngfuncs.Cvar_SetValue( "billflxcrypted_item_mask", 0);
gEngfuncs.Cvar_SetValue( "billflxcrypted_unit_mask_13", 100);
}*/
}

void CHudKillEffect::UserCmd_CommandActiveAdd_point(void)
{
pb_point->value += 300;
gEngfuncs.Cvar_SetValue( "billflxencrypted_pb_points", pb_point->value);
}


void CHudKillEffect::UserCmd_CommandActivebuy_qrespawn(void)
{
ClientCmd("billflxcrypted_item_qrespawn 1");

ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}

void CHudKillEffect::UserCmd_CommandActivebuy_mask_1(void)
{
ClientCmd("billflxcrypted_item_mask 1");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}

void CHudKillEffect::UserCmd_CommandActivebuy_mask_2(void)
{
ClientCmd("billflxcrypted_item_mask 2");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}




void CHudKillEffect::UserCmd_CommandActivebuy_mask_3(void)
{
ClientCmd("billflxcrypted_item_mask 3");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}





void CHudKillEffect::UserCmd_CommandActivebuy_mask_4(void)
{
ClientCmd("billflxcrypted_item_mask 4");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}

void CHudKillEffect::UserCmd_CommandActivebuy_mask_5(void)
{
ClientCmd("billflxcrypted_item_mask 5");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}

void CHudKillEffect::UserCmd_CommandActivebuy_mask_6(void)
{
ClientCmd("billflxcrypted_item_mask 6");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}

void CHudKillEffect::UserCmd_CommandActivebuy_mask_7(void)
{
ClientCmd("billflxcrypted_item_mask 7");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}

void CHudKillEffect::UserCmd_CommandActivebuy_mask_8(void)
{
ClientCmd("billflxcrypted_item_mask 8");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}

void CHudKillEffect::UserCmd_CommandActivebuy_mask_9(void)
{
ClientCmd("billflxcrypted_item_mask 9");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}

void CHudKillEffect::UserCmd_CommandActivebuy_mask_10(void)
{
ClientCmd("billflxcrypted_item_mask 10");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}

void CHudKillEffect::UserCmd_CommandActivebuy_mask_11(void)
{

ClientCmd("billflxcrypted_item_mask 11");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}

void CHudKillEffect::UserCmd_CommandActivebuy_mask_12(void)
{
ClientCmd("billflxcrypted_item_mask 12");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}

void CHudKillEffect::UserCmd_CommandActivebuy_mask_13(void)
{
ClientCmd("billflxcrypted_item_mask 13");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}

void CHudKillEffect::UserCmd_CommandActivebuy_qc(void)
{
ClientCmd("billflxcrypted_quickdeploy_enable 1; billflxcrypted_bought_quickdeploy 1");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}



void CHudKillEffect::UserCmd_CommandActivebuy_qr(void)
{

ClientCmd("billflxcrypted_quickreload_enable 1; billflxcrypted_bought_quickreload 1");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}

void CHudKillEffect::UserCmd_CommandActivebuy_megahp(void)
{
ClientCmd("billflxcrypted_megahp_enable 1; billflxcrypted_bought_megahp 1");
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#SUCCESS\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
}

void CHudKillEffect::UserCmd_CommandActivebuy_bpoint(void)
{
if (pb_point->value >= 0)
{

switch (Com_RandomLong(1, 20))
{
case 1:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#20.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 20000;
break;
case 2:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#5000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 5000;
break;
case 3:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#20.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 20000;
break;
case 4:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#10.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 10000;
break;
case 5:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#20.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 20000;
break;
case 6:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#40.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 40000;
break;
case 7:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#20.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 20000;
break;
case 8:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#15.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 15.000;
break;
case 9:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#50.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 50000;
break;
case 10:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#10.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 10000;
break;
case 11:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#20.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 20000;
break;
case 12:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#30.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 30000;
break;
case 13:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#20.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 20000;
break;
case 14:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#20.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 20000;
break;
case 15:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#100.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 100000;
break;
case 16:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#50.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 50000;
break;
case 17:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#20.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 20000;
break;
case 18:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#15.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 15000;
break;
case 19:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#10.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 10000;
break;
case 20:
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#10.000 point given\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Equip_on.wav");
pb_point->value += 10000;
break;
}



pb_point->value -= 20000;
gEngfuncs.Cvar_SetValue( "billflxencrypted_pb_points", pb_point->value);
}
else
{
ClientCmd("exec touch/notice; touch_addbutton \"notice_bg2\" \"#INSUFFICIENT POINT\" \"\" 0.360000 0.555870 0.660000 0.684148 255 255 255 214 4; play media/PB_15ver_Error.wav");
}
}

bool frag_headshot;
bool frag_kill;
bool frag_masskill2;
bool frag_masskill3;
bool frag_masskill4;
bool frag_masskill5;
bool frag_masskill6;
bool frag_masskill7;
bool frag_masskill8;
bool frag_melee;
bool frag_meleehs;
bool frag_stopper;
bool frag_stopperhs;
bool frag_stoppermelee;
bool frag_stoppermeleehs;

bool isPiercingShot;
bool isMassKill;
bool isDoublekill;
bool isTriplekill;
bool isChainkiller;
bool isHeadshot;
bool isChainHeadshot;
bool isHelmet;
bool isStopper;
bool isSlugger;
bool isHotKiller;
bool isNightmare;
bool isSpecialGunner;
bool isBombShot;

float dis_PiercingShot;
float dis_MassKill;
float dis_Doublekill;
float dis_Triplekill;
float dis_Chainkiller;
float dis_Headshot;
float dis_ChainHeadshot;
float dis_Helmet;
float dis_Stopper;
float dis_Slugger;
float dis_HotKiller;
float dis_Nightmare;
float dis_SpecialGunner;
float dis_BombShot;

float KillDisplay()
{
if (isPiercingShot)
dis_PiercingShot = 100.0f;
else
dis_PiercingShot = 0.0f;

if (isMassKill)
dis_MassKill = 100.0f;
else
dis_MassKill = 0.0f;

if (isDoublekill)
dis_Doublekill = 100.0f;
else
dis_Doublekill = 0.0f;

if (isTriplekill)
dis_Triplekill = 100.0f;
else
dis_Triplekill = 0.0f;

if (isChainkiller)
dis_Chainkiller = 100.0f;
else
dis_Chainkiller = 0.0f;

if (isHeadshot)
dis_Headshot = 100.0f;
else
dis_Headshot = 0.0f;

if (isChainHeadshot)
dis_ChainHeadshot = 100.0f;
else
dis_ChainHeadshot = 0.0f;

if (isHelmet)
dis_Helmet = 100.0f;
else
dis_Helmet = 0.0f;

if (isStopper)
dis_Stopper = 100.0f;
else
dis_Stopper = 0.0f;

if (isSlugger)
dis_Slugger = 100.0f;
else
dis_Slugger = 0.0f;

if (isHotKiller)
dis_HotKiller = 100.0f;//180.0f;
else
dis_HotKiller = 0.0f;

if (isNightmare)
dis_Nightmare = 100.0f;//180.0f;
else
dis_Nightmare = 0.0f;

if (isSpecialGunner)
dis_SpecialGunner = 100.0f;//220.0f;
else
dis_SpecialGunner = 0.0f;

if (isBombShot)
dis_BombShot = 100.0f;//220.0f;
else
dis_BombShot = 0.0f;

return dis_PiercingShot+dis_MassKill+dis_Doublekill+dis_Triplekill+dis_Chainkiller+dis_Headshot+dis_ChainHeadshot+dis_Helmet+dis_Stopper+dis_Slugger+dis_HotKiller+dis_Nightmare+dis_SpecialGunner+dis_BombShot;
}


void CHudKillEffect::Reset( void )
{
isPiercingShot=FALSE;
isMassKill=FALSE;
isDoublekill=FALSE;
isTriplekill=FALSE;
isChainkiller=FALSE;
isHeadshot=FALSE;
isChainHeadshot=FALSE;
isHelmet=FALSE;
isStopper=FALSE;
isSlugger=FALSE;
isHotKiller=FALSE;
isNightmare=FALSE;
isSpecialGunner=FALSE;
isBombShot=FALSE;	
}

void CHudKillEffect::UserCmd_CommandActiveMissionComplete(void)
{
MissionComplete_time = 250.0f;
}

void CHudKillEffect::UserCmd_CommandActivekillframe(void)
{
killframe_time = 40.0f;
}

void CHudKillEffect::UserCmd_CommandActivekillframeAnim(void)
{
killframeAnim_time = 35.0f;
}


void CHudKillEffect::UserCmd_CommandActiveOneshotEnable(void)
{
}

void CHudKillEffect::UserCmd_CommandActiveOneshotDisable(void)
{
}

void CHudKillEffect::UserCmd_CommandActivePointkill(void)
{

if (gHUD.piercing_shot == TRUE)
ClientCmd("spk vox/piercing.wav; PiercingShot");
else if (gHUD.mass_kill == TRUE)
ClientCmd("spk vox/mass.wav; MassKill");

if(gHUD.slugger_kill)
{

gHUD.slugger_count += 1;

 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = TRUE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
}
else
{

gHUD.slugger_count = 0;

 frag_headshot = FALSE;
 frag_kill = TRUE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
}

}

void CHudKillEffect::UserCmd_CommandActiveHeadshotPoint(void)
{
if (gHUD.piercing_shot == TRUE)
ClientCmd("spk vox/piercing.wav; PiercingShot");
else if (gHUD.mass_kill == TRUE)
ClientCmd("spk vox/mass.wav; MassKill");

if(gHUD.slugger_kill)
{
gHUD.slugger_count += 1;

 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = TRUE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
}
else
{
gHUD.slugger_count = 0;

 frag_headshot = TRUE;
 frag_kill = FALSE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
}
}

void CHudKillEffect::UserCmd_CommandActiveDoublekill(void)
{
if (gHUD.piercing_shot == TRUE)
{
ClientCmd("spk vox/piercing.wav; PiercingShot");

 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = TRUE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;

return;
}
else if (gHUD.mass_kill == TRUE)
{
ClientCmd("spk vox/mass.wav; MassKill");

 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = TRUE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
return;
}
else if (gHUD.slugger_kill)
{

if (gHUD.slugger_count >= 1)
ClientCmd("spk vox/ch_slugger.wav; Slugger");
else if (gHUD.slugger_count == 0)
{
isDoublekill=TRUE;
Doublekill_time = KillDisplay();//100.0f;
ClientCmd("spk vox/doublekill.wav");
}

gHUD.slugger_count += 1;


 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = TRUE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
return;
}
else
{
isDoublekill=TRUE;
Doublekill_time = KillDisplay();//100.0f;
ClientCmd("spk vox/doublekill.wav");

gHUD.slugger_count = 0;

 frag_headshot = FALSE;
 frag_kill = TRUE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
}


}

void CHudKillEffect::UserCmd_CommandActiveTriplekill(void)
{
if (gHUD.piercing_shot == TRUE)
{
ClientCmd("spk vox/piercing.wav; PiercingShot");

 
 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = FALSE;
 frag_masskill3 = TRUE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
return;
}
else if (gHUD.mass_kill == TRUE)
{
ClientCmd("spk vox/mass.wav; MassKill");


 
 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = FALSE;
 frag_masskill3 = TRUE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
return;
}
else if (gHUD.slugger_kill)
{

if (gHUD.slugger_count >= 1)
ClientCmd("spk vox/ch_slugger.wav; Slugger");
else if (gHUD.slugger_count == 0)
{
isTriplekill=TRUE;
Triplekill_time = KillDisplay();//100.0f;
ClientCmd("spk vox/triplekill.wav");
}

gHUD.slugger_count += 1;

 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = TRUE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
}
else
{
isTriplekill=TRUE;
Triplekill_time = KillDisplay();//100.0f;
ClientCmd("spk vox/triplekill.wav");

gHUD.slugger_count = 0;
 
 frag_headshot = FALSE;
 frag_kill = TRUE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
}

}

void CHudKillEffect::UserCmd_CommandActiveChainkiller(void)
{

if (gHUD.piercing_shot == TRUE)
{
ClientCmd("spk vox/piercing.wav; PiercingShot");

 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = TRUE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
return;
}
else if (gHUD.mass_kill == TRUE)
{
ClientCmd("spk vox/mass.wav; MassKill");

 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = TRUE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
return;
}
else if (gHUD.slugger_kill)
{

if (gHUD.slugger_count >= 1)
ClientCmd("spk vox/ch_slugger.wav; Slugger");
else if (gHUD.slugger_count == 0)
{
isChainkiller=TRUE;
Chainkiller_time = KillDisplay();//100.0f;
ClientCmd("spk vox/chainkiller.wav");
}

gHUD.slugger_count += 1;


 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = TRUE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
}
else
{
isChainkiller=TRUE;
Chainkiller_time = KillDisplay();//100.0f;
ClientCmd("spk vox/chainkiller.wav");

gHUD.slugger_count = 0;
 
 frag_headshot = FALSE;
 frag_kill = TRUE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
}

}

void CHudKillEffect::UserCmd_CommandActiveSlugger(void)
{
if (gHUD.slugger_count == 0)
return;

isSlugger=TRUE;
Slugger_time = KillDisplay();//100.0f;

gHUD.slugger_count += 1;
 
 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = TRUE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
}

void CHudKillEffect::UserCmd_CommandActiveHeadshot(void)
{
if (gHUD.piercing_shot == TRUE)
{
ClientCmd("spk vox/piercing.wav; PiercingShot");

 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = TRUE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
return;
}
else if (gHUD.mass_kill == TRUE)
{
ClientCmd("spk vox/mass.wav; MassKill");


 
 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = TRUE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
return;
}
else
{
isHeadshot=TRUE;
Headshot_time = KillDisplay();//100.0f;
ClientCmd("spk vox/headshot.wav");

 frag_headshot = TRUE;
 frag_kill = FALSE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
}

}

void CHudKillEffect::UserCmd_CommandActiveChainHeadshot(void)
{
if (gHUD.piercing_shot == TRUE)
{
ClientCmd("spk vox/piercing.wav; PiercingShot");

 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = TRUE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
return;
}
else if (gHUD.mass_kill == TRUE)
{
ClientCmd("spk vox/mass.wav; MassKill");
 
 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = TRUE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
return;
}
else
{

isHeadshot=TRUE;
ChainHeadshot_time = KillDisplay();//100.0f;
ClientCmd("spk vox/chainHeadshot.wav");


 frag_headshot = TRUE;
 frag_kill = FALSE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
}

}

void CHudKillEffect::UserCmd_CommandActivePiercingShot(void)
{
isPiercingShot=TRUE;
PiercingShot_time = KillDisplay();//100.0f;
}

void CHudKillEffect::UserCmd_CommandActiveMassKill(void)
{
isMassKill=TRUE;
MassKill_time = KillDisplay();//100.0f;
}

void CHudKillEffect::UserCmd_CommandActiveStopper(void)
{

if(gHUD.slugger_kill)
gHUD.slugger_count += 1;
else
gHUD.slugger_count = 0;

if (gHUD.piercing_shot == TRUE)
{
ClientCmd("spk vox/piercing.wav; PiercingShot");

 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = TRUE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
return;
}
else if (gHUD.mass_kill == TRUE)
{
ClientCmd("spk vox/mass.wav; MassKill");

 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = TRUE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = FALSE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
return;
}
else
{
isStopper=TRUE;
Stopper_time = KillDisplay();//100.0f; ClientCmd("spk vox/chainstopper.wav");
ClientCmd("spk vox/chainstopper.wav");

 frag_headshot = FALSE;
 frag_kill = FALSE;
 frag_masskill2 = FALSE;
 frag_masskill3 = FALSE;
 frag_masskill4 = FALSE;
 frag_masskill5 = FALSE;
 frag_masskill6 = FALSE;
 frag_masskill7 = FALSE;
 frag_masskill8 = FALSE;
 frag_melee = FALSE;
 frag_meleehs = FALSE;
 frag_stopper = TRUE;
 frag_stopperhs = FALSE;
 frag_stoppermelee = FALSE;
 frag_stoppermeleehs = FALSE;
}
}


void CHudKillEffect::UserCmd_CommandActiveHelmet(void)
{

if (gHUD.helmet_on == FALSE)
return;

isHelmet=TRUE;
Helmet_time = KillDisplay();//100.0f;
}

void CHudKillEffect::UserCmd_CommandActivePointNumber(void)
{

}

void CHudKillEffect::UserCmd_CommandActiveHitMarker(void)
{
hit_time = 50.0f;
}


//special 
void CHudKillEffect::UserCmd_CommandActiveSpecialGunner(void)
{
isSpecialGunner=TRUE;
SpecialGunner_time =  KillDisplay() + 50;//220.0f;
ClientCmd("spk vox/hot_killer.wav");
}
void CHudKillEffect::UserCmd_CommandActiveBombShot(void)
{
isBombShot=TRUE;
BombShot_time = KillDisplay() + 50;//KillDisplay();
ClientCmd("spk vox/hot_killer.wav");
}
void CHudKillEffect::UserCmd_CommandActiveoneShot(void)
{
}


void CHudKillEffect::UserCmd_CommandActiveHotKiller(void)
{
isHotKiller=TRUE;
HotKiller_time = KillDisplay() + 30;//KillDisplay();
}

void CHudKillEffect::UserCmd_CommandActiveNightmare(void)
{
isNightmare=TRUE;
Nightmare_time = KillDisplay() + 30;//KillDisplay();
}


void CHudKillEffect::UserCmd_CommandActiveFragAnimKill(void)
{
FragAnimKill_time = 110.0f; 
}
void CHudKillEffect::UserCmd_CommandActiveFragAnimHs(void)
{
FragAnimHs_time = 110.0f; 
}
void CHudKillEffect::UserCmd_CommandActiveFragAnimStopper(void)
{
FragAnimStopper_time = 110.0f; 
}
void CHudKillEffect::UserCmd_CommandActiveFragAnimBlue(void)
{
FragAnimBlue_time = 110.0f; 
}
void CHudKillEffect::UserCmd_CommandActiveFragAnimGold(void)
{
FragAnimGold_time = 110.0f; 
}


void CHudKillEffect::UserCmd_CommandActivePos1(void)  { Pos1_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActivePos2(void)  { Pos2_time = 40.0f; }


void CHudKillEffect::UserCmd_CommandActiveKillStar1(void)  { KillStar1_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveKillStar2(void)  { KillStar2_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveKillStar3(void)  { KillStar3_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveKillStar4(void)  { KillStar4_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveKillStar5(void)  { KillStar5_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveKillStar6(void)  { KillStar6_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveKillStar7(void)  { KillStar7_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveKillStar8(void)  { KillStar8_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveKillStar9(void)  { KillStar9_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveKillStar10(void)  { KillStar10_time = 40.0f; }


void CHudKillEffect::UserCmd_CommandActiveHeadshotStar1(void)  { HeadshotStar1_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveHeadshotStar2(void)  { HeadshotStar2_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveHeadshotStar3(void)  { HeadshotStar3_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveHeadshotStar4(void)  { HeadshotStar4_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveHeadshotStar5(void)  { HeadshotStar5_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveHeadshotStar6(void)  { HeadshotStar6_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveHeadshotStar7(void)  { HeadshotStar7_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveHeadshotStar8(void)  { HeadshotStar8_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveHeadshotStar9(void)  { HeadshotStar9_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveHeadshotStar10(void)  { HeadshotStar10_time = 40.0f; }

void CHudKillEffect::UserCmd_CommandActiveBlueStar5(void)  { BlueStar5_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveGoldStar10(void)  { GoldStar10_time = 40.0f; }

void CHudKillEffect::UserCmd_CommandActiveStopperStar1(void)  { StopperStar1_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperStar2(void)  { StopperStar2_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperStar3(void)  { StopperStar3_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperStar4(void)  { StopperStar4_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperStar5(void)  { StopperStar5_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperStar6(void)  { StopperStar6_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperStar7(void)  { StopperStar7_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperStar8(void)  { StopperStar8_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperStar9(void)  { StopperStar9_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperStar10(void)  { StopperStar10_time = 40.0f; }


void CHudKillEffect::UserCmd_CommandActiveStopperHsStar1(void)  { StopperHsStar1_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperHsStar2(void)  { StopperHsStar2_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperHsStar3(void)  { StopperHsStar3_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperHsStar4(void)  { StopperHsStar4_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperHsStar5(void)  { StopperHsStar5_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperHsStar6(void)  { StopperHsStar6_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperHsStar7(void)  { StopperHsStar7_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperHsStar8(void)  { StopperHsStar8_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperHsStar9(void)  { StopperHsStar9_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveStopperHsStar10(void)  { StopperHsStar10_time = 40.0f; }

void CHudKillEffect::UserCmd_CommandActiveSluggerStar1(void)  { SluggerStar1_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerStar2(void)  { SluggerStar2_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerStar3(void)  { SluggerStar3_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerStar4(void)  { SluggerStar4_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerStar5(void)  { SluggerStar5_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerStar6(void)  { SluggerStar6_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerStar7(void)  { SluggerStar7_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerStar8(void)  { SluggerStar8_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerStar9(void)  { SluggerStar9_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerStar10(void)  { SluggerStar10_time = 40.0f; }

void CHudKillEffect::UserCmd_CommandActiveSluggerHsStar1(void)  { SluggerHsStar1_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerHsStar2(void)  { SluggerHsStar2_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerHsStar3(void)  { SluggerHsStar3_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerHsStar4(void)  { SluggerHsStar4_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerHsStar5(void)  { SluggerHsStar5_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerHsStar6(void)  { SluggerHsStar6_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerHsStar7(void)  { SluggerHsStar7_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerHsStar8(void)  { SluggerHsStar8_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerHsStar9(void)  { SluggerHsStar9_time = 40.0f; }
void CHudKillEffect::UserCmd_CommandActiveSluggerHsStar10(void)  { SluggerHsStar10_time = 40.0f; }


int CHudKillEffect::MsgFunc_buy_qc(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_qc");
	return 1;
}

int CHudKillEffect::MsgFunc_buy_qrespawn(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_qrespawn");
	return 1;
}

int CHudKillEffect::MsgFunc_buy_megahp(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_megahp");
	return 1;
}
int CHudKillEffect::MsgFunc_buy_bpoint(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_bpoint");
	return 1;
}
int CHudKillEffect::MsgFunc_buy_qr(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_qr");
	return 1;
}
int CHudKillEffect::MsgFunc_buy_mask_1(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_mask_1");
	return 1;
}
int CHudKillEffect::MsgFunc_buy_mask_2(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_mask_2");
	return 1;
}
int CHudKillEffect::MsgFunc_buy_mask_3(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_mask_3");
	return 1;
}

int CHudKillEffect::MsgFunc_buy_mask_4(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_mask_4");
	return 1;
}

int CHudKillEffect::MsgFunc_buy_mask_5(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_mask_5");
	return 1;
}

int CHudKillEffect::MsgFunc_buy_mask_6(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_mask_6");
	return 1;
}

int CHudKillEffect::MsgFunc_buy_mask_7(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_mask_7");
	return 1;
}

int CHudKillEffect::MsgFunc_buy_mask_8(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_mask_8");
	return 1;
}

int CHudKillEffect::MsgFunc_buy_mask_9(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_mask_9");
	return 1;
}

int CHudKillEffect::MsgFunc_buy_mask_10(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_mask_10");
	return 1;
}

int CHudKillEffect::MsgFunc_buy_mask_11(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_mask_11");
	return 1;
}

int CHudKillEffect::MsgFunc_buy_mask_12(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_mask_12");
	return 1;
}

int CHudKillEffect::MsgFunc_buy_mask_13(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("buy_mask_13");
	return 1;
}

int CHudKillEffect::MsgFunc_Unequip_mask(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Unequip_mask");
	return 1;
}

int CHudKillEffect::MsgFunc_Count_unit(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Count_unit");
	return 1;
}


int CHudKillEffect::MsgFunc_killframe(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("killframe");
	return 1;
}

int CHudKillEffect::MsgFunc_killframeAnim(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("killframeAnim");
	return 1;
}


int CHudKillEffect::MsgFunc_PiercingShot(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );

gHUD.one_shot = FALSE;

	ClientCmd("PiercingShot");
	return 1;
}

int CHudKillEffect::MsgFunc_MassKill(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );

	ClientCmd("MassKill");
	return 1;
}

int CHudKillEffect::MsgFunc_OneshotEnable(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );

	ClientCmd("OneshotEnable");
	return 1;
}

int CHudKillEffect::MsgFunc_OneshotDisable(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );

	ClientCmd("OneshotDisable");
	return 1;
}


int CHudKillEffect::MsgFunc_Add_point(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Add_point");
	return 1;
}

int CHudKillEffect::MsgFunc_Pointkill(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );

if (gHUD.special_gunner)
{
ClientCmd("Pointkill; SpecialGunner");
}
else if (gHUD.bomb_shot)
{
ClientCmd("Pointkill; BombShot");
}
else
{

ClientCmd("Pointkill");

}

ClientCmd("killframe; killframeAnim");

	return 1;
}

int CHudKillEffect::MsgFunc_HeadshotPoint(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );

if (gHUD.special_gunner)
{
ClientCmd("HeadshotPoint; SpecialGunner");
}
else
{
ClientCmd("HeadshotPoint");
}

ClientCmd("killframe; killframeAnim");

	return 1;
}

//special
int CHudKillEffect::MsgFunc_SpecialGunner(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );

	ClientCmd("SpecialGunner");

	return 1;
}
int CHudKillEffect::MsgFunc_BombShot(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );

	ClientCmd("BombShot");

	return 1;
}
int CHudKillEffect::MsgFunc_oneShot(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );


	return 1;
}


int CHudKillEffect::MsgFunc_MissionComplete(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );

	ClientCmd("MissionComplete");

	return 1;
}



int CHudKillEffect::MsgFunc_Doublekill(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );

////ClientCmd("spk vox/piercing.wav");

if (gHUD.piercing_shot == TRUE || gHUD.mass_kill == TRUE) //disable for mass_kill
return 1;

//ClientCmd("spk vox/doublekill.wav")
gHUD.one_shot = FALSE;

ClientCmd("Doublekill");


	return 1;
}
int CHudKillEffect::MsgFunc_Triplekill(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
////ClientCmd("spk vox/piercing.wav");
if (gHUD.piercing_shot == TRUE || gHUD.mass_kill == TRUE) //disable for mass_kill
return 1;

//ClientCmd("spk vox/triplekill.wav");
gHUD.one_shot = FALSE;
ClientCmd("Triplekill");


	return 1;
}
int CHudKillEffect::MsgFunc_Chainkiller(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
//ClientCmd("spk vox/piercing.wav");
if (gHUD.piercing_shot == TRUE || gHUD.mass_kill == TRUE) //disable for mass_kill
return 1;


//ClientCmd("spk vox/chainkiller.wav");
gHUD.one_shot = FALSE;
ClientCmd("Chainkiller");

	return 1;
}



int CHudKillEffect::MsgFunc_Headshot(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
//ClientCmd("spk vox/piercing.wav");
if (gHUD.piercing_shot == TRUE || gHUD.mass_kill == TRUE) //disable for mass_kill
return 1;

//ClientCmd("spk vox/headshot.wav");

ClientCmd("Headshot");

	return 1;
}
int CHudKillEffect::MsgFunc_ChainHeadshot(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
//ClientCmd("spk vox/piercing.wav");
if (gHUD.piercing_shot == TRUE || gHUD.mass_kill == TRUE) //disable for mass_kill
return 1;

gHUD.one_shot = FALSE;
//ClientCmd("spk vox/chainHeadshot.wav");

ClientCmd("ChainHeadshot");

	return 1;
}
int CHudKillEffect::MsgFunc_Helmet(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Helmet");
if (gHUD.helmet_on == FALSE)
return 1;

ClientCmd("spk vox/helmet.wav");

	return 1;
}
int CHudKillEffect::MsgFunc_Stopper(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
////ClientCmd("spk vox/piercing.wav");
if (gHUD.piercing_shot == TRUE || gHUD.mass_kill == TRUE) //disable for mass_kill
return 1;

gHUD.one_shot = FALSE;
//ClientCmd("spk vox/chainstopper.wav");

ClientCmd("Stopper");


	return 1;
}
int CHudKillEffect::MsgFunc_Slugger(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Slugger");

gHUD.one_shot = FALSE;
//ClientCmd("spk vox/chainslugger.wav");

	return 1;
}

int CHudKillEffect::MsgFunc_HotKiller(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("HotKiller");

ClientCmd("spk vox/hot_killer.wav");

	return 1;
}

int CHudKillEffect::MsgFunc_Nightmare(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Nightmare");

ClientCmd("spk vox/hot_killer.wav");

	return 1;
}


int CHudKillEffect::MsgFunc_PointNumber(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	return 1;
}

int CHudKillEffect::MsgFunc_HitMarker(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("HitMarker");
	ClientCmd("spk vox/hithuman.wav");
	return 1;
}





int CHudKillEffect::MsgFunc_FragAnimKill(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("FragAnimKill");
	return 1;
}
int CHudKillEffect::MsgFunc_FragAnimHs(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("FragAnimHs");
	return 1;
}
int CHudKillEffect::MsgFunc_FragAnimStopper(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("FragAnimStopper");
	return 1;
}
int CHudKillEffect::MsgFunc_FragAnimBlue(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("FragAnimBlue");
	return 1;
}
int CHudKillEffect::MsgFunc_FragAnimGold(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("FragAnimGold");
	return 1;
}



int CHudKillEffect::MsgFunc_Pos1(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("Pos1"); 	return 1; }
int CHudKillEffect::MsgFunc_Pos2(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("Pos2"); 	return 1; }



int CHudKillEffect::MsgFunc_KillStar1(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("KillStar1"); 	return 1; }
int CHudKillEffect::MsgFunc_KillStar2(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("KillStar2"); 	return 1; }
int CHudKillEffect::MsgFunc_KillStar3(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("KillStar3"); 	return 1; }
int CHudKillEffect::MsgFunc_KillStar4(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("KillStar4"); 	return 1; }
int CHudKillEffect::MsgFunc_KillStar5(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("KillStar5"); 	return 1; }
int CHudKillEffect::MsgFunc_KillStar6(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("KillStar6"); 	return 1; }
int CHudKillEffect::MsgFunc_KillStar7(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("KillStar7"); 	return 1; }
int CHudKillEffect::MsgFunc_KillStar8(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("KillStar8"); 	return 1; }
int CHudKillEffect::MsgFunc_KillStar9(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("KillStar9"); 	return 1; }
int CHudKillEffect::MsgFunc_KillStar10(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("KillStar10"); 	return 1; }

int CHudKillEffect::MsgFunc_HeadshotStar1(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("HeadshotStar1"); 	return 1; }
int CHudKillEffect::MsgFunc_HeadshotStar2(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("HeadshotStar2"); 	return 1; }
int CHudKillEffect::MsgFunc_HeadshotStar3(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("HeadshotStar3"); 	return 1; }
int CHudKillEffect::MsgFunc_HeadshotStar4(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("HeadshotStar4"); 	return 1; }
int CHudKillEffect::MsgFunc_HeadshotStar5(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("HeadshotStar5"); 	return 1; }
int CHudKillEffect::MsgFunc_HeadshotStar6(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("HeadshotStar6"); 	return 1; }
int CHudKillEffect::MsgFunc_HeadshotStar7(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("HeadshotStar7"); 	return 1; }
int CHudKillEffect::MsgFunc_HeadshotStar8(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("HeadshotStar8"); 	return 1; }
int CHudKillEffect::MsgFunc_HeadshotStar9(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("HeadshotStar9"); 	return 1; }
int CHudKillEffect::MsgFunc_HeadshotStar10(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("HeadshotStar10"); 	return 1; }

int CHudKillEffect::MsgFunc_BlueStar5(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("BlueStar5"); 	return 1; }
int CHudKillEffect::MsgFunc_GoldStar10(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("GoldStar10"); 	return 1; }

int CHudKillEffect::MsgFunc_StopperStar1(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperStar1"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperStar2(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperStar2"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperStar3(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperStar3"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperStar4(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperStar4"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperStar5(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperStar5"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperStar6(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperStar6"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperStar7(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperStar7"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperStar8(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperStar8"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperStar9(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperStar9"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperStar10(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperStar10"); 	return 1; }

int CHudKillEffect::MsgFunc_StopperHsStar1(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperHsStar1"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperHsStar2(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperHsStar2"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperHsStar3(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperHsStar3"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperHsStar4(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperHsStar4"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperHsStar5(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperHsStar5"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperHsStar6(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperHsStar6"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperHsStar7(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperHsStar7"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperHsStar8(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperHsStar8"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperHsStar9(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperHsStar9"); 	return 1; }
int CHudKillEffect::MsgFunc_StopperHsStar10(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("StopperHsStar10"); 	return 1; }

int CHudKillEffect::MsgFunc_SluggerStar1(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerStar1"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerStar2(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerStar2"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerStar3(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerStar3"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerStar4(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerStar4"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerStar5(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerStar5"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerStar6(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerStar6"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerStar7(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerStar7"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerStar8(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerStar8"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerStar9(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerStar9"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerStar10(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerStar10"); 	return 1; }

int CHudKillEffect::MsgFunc_SluggerHsStar1(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerHsStar1"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerHsStar2(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerHsStar2"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerHsStar3(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerHsStar3"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerHsStar4(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerHsStar4"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerHsStar5(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerHsStar5"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerHsStar6(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerHsStar6"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerHsStar7(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerHsStar7"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerHsStar8(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerHsStar8"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerHsStar9(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerHsStar9"); 	return 1; }
int CHudKillEffect::MsgFunc_SluggerHsStar10(const char *pszName, int iSize, void *pbuf ) { 	BufferReader reader( pszName, pbuf, iSize ); 	ClientCmd("SluggerHsStar10"); 	return 1; }


cvar_t *mission_kill;
cvar_t *mission_doublekill;
cvar_t *mission_triplekill;
cvar_t *mission_chainkiller;
cvar_t *mission_headshot;
cvar_t *mission_chainheadshot;
cvar_t *mission_slugger;
cvar_t *mission_masskill;
cvar_t *mission_piercingshot;
cvar_t *pb_point;

#define CVAR_INVISIBLE (1<<21)

int CHudKillEffect::Init()
{
gHUD.AddHudElem(this);

HOOK_MESSAGE(Add_point);
HOOK_COMMAND("Add_point", CommandActiveAdd_point);

HOOK_MESSAGE(Count_unit);
HOOK_COMMAND("Count_unit", CommandActiveCount_unit);

HOOK_MESSAGE(Unequip_mask);
HOOK_COMMAND("Unequip_mask", CommandActiveUnequip_mask);

HOOK_MESSAGE(buy_qc);
HOOK_COMMAND("buy_qc", CommandActivebuy_qc);

HOOK_MESSAGE(buy_megahp);
HOOK_COMMAND("buy_megahp", CommandActivebuy_megahp);

HOOK_MESSAGE(buy_bpoint);
HOOK_COMMAND("buy_bpoint", CommandActivebuy_bpoint);

HOOK_MESSAGE(buy_qr);
HOOK_COMMAND("buy_qr", CommandActivebuy_qr);

HOOK_MESSAGE(buy_mask_1);
HOOK_COMMAND("buy_mask_1", CommandActivebuy_mask_1);

HOOK_MESSAGE(buy_mask_2);
HOOK_COMMAND("buy_mask_2", CommandActivebuy_mask_2);

HOOK_MESSAGE(buy_mask_3);
HOOK_COMMAND("buy_mask_3", CommandActivebuy_mask_3);

HOOK_MESSAGE(buy_mask_4);
HOOK_COMMAND("buy_mask_4", CommandActivebuy_mask_4);

HOOK_MESSAGE(buy_mask_5);
HOOK_COMMAND("buy_mask_5", CommandActivebuy_mask_5);

HOOK_MESSAGE(buy_mask_6);
HOOK_COMMAND("buy_mask_6", CommandActivebuy_mask_6);
HOOK_MESSAGE(buy_mask_7);
HOOK_COMMAND("buy_mask_7", CommandActivebuy_mask_7);
HOOK_MESSAGE(buy_mask_8);
HOOK_COMMAND("buy_mask_8", CommandActivebuy_mask_8);
HOOK_MESSAGE(buy_mask_9);
HOOK_COMMAND("buy_mask_9", CommandActivebuy_mask_9);
HOOK_MESSAGE(buy_mask_10);
HOOK_COMMAND("buy_mask_10", CommandActivebuy_mask_10);
HOOK_MESSAGE(buy_mask_11);
HOOK_COMMAND("buy_mask_11", CommandActivebuy_mask_11);
HOOK_MESSAGE(buy_mask_12);
HOOK_COMMAND("buy_mask_12", CommandActivebuy_mask_12);
HOOK_MESSAGE(buy_mask_13);
HOOK_COMMAND("buy_mask_13", CommandActivebuy_mask_13);

HOOK_MESSAGE(buy_qrespawn);
HOOK_COMMAND("buy_qrespawn", CommandActivebuy_qrespawn);



HOOK_MESSAGE(killframe);
HOOK_COMMAND("killframe", CommandActivekillframe);

HOOK_MESSAGE(killframeAnim);
HOOK_COMMAND("killframeAnim", CommandActivekillframeAnim);

HOOK_MESSAGE(MissionComplete);
HOOK_COMMAND("MissionComplete", CommandActiveMissionComplete);

HOOK_MESSAGE(SpecialGunner);
HOOK_COMMAND("SpecialGunner", CommandActiveSpecialGunner);
HOOK_MESSAGE(BombShot);
HOOK_COMMAND("BombShot", CommandActiveBombShot);
HOOK_MESSAGE(oneShot);
HOOK_COMMAND("oneShot", CommandActiveoneShot);

HOOK_MESSAGE(OneshotEnable);
HOOK_COMMAND("OneshotEnable", CommandActiveOneshotEnable);
HOOK_MESSAGE(OneshotDisable);
HOOK_COMMAND("OneshotDisable", CommandActiveOneshotDisable);

HOOK_MESSAGE(Pointkill);
HOOK_COMMAND("Pointkill", CommandActivePointkill);

HOOK_MESSAGE(PiercingShot);
HOOK_COMMAND("PiercingShot", CommandActivePiercingShot);

HOOK_MESSAGE(MassKill);
HOOK_COMMAND("MassKill", CommandActiveMassKill);

HOOK_MESSAGE(Doublekill);
HOOK_COMMAND("Doublekill", CommandActiveDoublekill);

HOOK_MESSAGE(Triplekill);
HOOK_COMMAND("Triplekill", CommandActiveTriplekill);

HOOK_MESSAGE(Chainkiller);
HOOK_COMMAND("Chainkiller", CommandActiveChainkiller);

HOOK_MESSAGE(HeadshotPoint);
HOOK_COMMAND("HeadshotPoint", CommandActiveHeadshotPoint);

HOOK_MESSAGE(Headshot);
HOOK_COMMAND("Headshot", CommandActiveHeadshot);

HOOK_MESSAGE(ChainHeadshot);
HOOK_COMMAND("ChainHeadshot", CommandActiveChainHeadshot);

HOOK_MESSAGE(Helmet);
HOOK_COMMAND("Helmet", CommandActiveHelmet);

HOOK_MESSAGE(Stopper);
HOOK_COMMAND("Stopper", CommandActiveStopper);

HOOK_MESSAGE(Slugger);
HOOK_COMMAND("Slugger", CommandActiveSlugger);

HOOK_MESSAGE(PointNumber);
HOOK_COMMAND("PointNumber", CommandActivePointNumber);

HOOK_MESSAGE(HitMarker);
HOOK_COMMAND("HitMarker", CommandActiveHitMarker);

HOOK_MESSAGE(HotKiller);
HOOK_COMMAND("HotKiller", CommandActiveHotKiller);

HOOK_MESSAGE(Nightmare);
HOOK_COMMAND("Nightmare", CommandActiveNightmare);


HOOK_MESSAGE(FragAnimKill);
HOOK_COMMAND("FragAnimKill", CommandActiveFragAnimKill);

HOOK_MESSAGE(FragAnimHs);
HOOK_COMMAND("FragAnimHs", CommandActiveFragAnimHs);

HOOK_MESSAGE(FragAnimStopper);
HOOK_COMMAND("FragAnimStopper", CommandActiveFragAnimStopper);

HOOK_MESSAGE(FragAnimBlue);
HOOK_COMMAND("FragAnimBlue", CommandActiveFragAnimBlue);

HOOK_MESSAGE(FragAnimGold);
HOOK_COMMAND("FragAnimGold", CommandActiveFragAnimGold);

HOOK_MESSAGE(Pos1);
HOOK_COMMAND("Pos1", CommandActivePos1);

HOOK_MESSAGE(Pos2);
HOOK_COMMAND("Pos2", CommandActivePos2);

HOOK_MESSAGE(KillStar1);
HOOK_MESSAGE(KillStar2);
HOOK_MESSAGE(KillStar3);
HOOK_MESSAGE(KillStar4);
HOOK_MESSAGE(KillStar5);
HOOK_MESSAGE(KillStar6);
HOOK_MESSAGE(KillStar7);
HOOK_MESSAGE(KillStar8);
HOOK_MESSAGE(KillStar9);
HOOK_MESSAGE(KillStar10);

HOOK_MESSAGE(HeadshotStar1);
HOOK_MESSAGE(HeadshotStar2);
HOOK_MESSAGE(HeadshotStar3);
HOOK_MESSAGE(HeadshotStar4);
HOOK_MESSAGE(HeadshotStar5);
HOOK_MESSAGE(HeadshotStar6);
HOOK_MESSAGE(HeadshotStar7);
HOOK_MESSAGE(HeadshotStar8);
HOOK_MESSAGE(HeadshotStar9);
HOOK_MESSAGE(HeadshotStar10);

HOOK_MESSAGE(BlueStar5);
HOOK_MESSAGE(GoldStar10);

HOOK_MESSAGE(StopperStar1);
HOOK_MESSAGE(StopperStar2);
HOOK_MESSAGE(StopperStar3);
HOOK_MESSAGE(StopperStar4);
HOOK_MESSAGE(StopperStar5);
HOOK_MESSAGE(StopperStar6);
HOOK_MESSAGE(StopperStar7);
HOOK_MESSAGE(StopperStar8);
HOOK_MESSAGE(StopperStar9);
HOOK_MESSAGE(StopperStar10);

HOOK_MESSAGE(StopperHsStar1);
HOOK_MESSAGE(StopperHsStar2);
HOOK_MESSAGE(StopperHsStar3);
HOOK_MESSAGE(StopperHsStar4);
HOOK_MESSAGE(StopperHsStar5);
HOOK_MESSAGE(StopperHsStar6);
HOOK_MESSAGE(StopperHsStar7);
HOOK_MESSAGE(StopperHsStar8);
HOOK_MESSAGE(StopperHsStar9);
HOOK_MESSAGE(StopperHsStar10);

HOOK_MESSAGE(SluggerStar1);
HOOK_MESSAGE(SluggerStar2);
HOOK_MESSAGE(SluggerStar3);
HOOK_MESSAGE(SluggerStar4);
HOOK_MESSAGE(SluggerStar5);
HOOK_MESSAGE(SluggerStar6);
HOOK_MESSAGE(SluggerStar7);
HOOK_MESSAGE(SluggerStar8);
HOOK_MESSAGE(SluggerStar9);
HOOK_MESSAGE(SluggerStar10);

HOOK_MESSAGE(SluggerHsStar1);
HOOK_MESSAGE(SluggerHsStar2);
HOOK_MESSAGE(SluggerHsStar3);
HOOK_MESSAGE(SluggerHsStar4);
HOOK_MESSAGE(SluggerHsStar5);
HOOK_MESSAGE(SluggerHsStar6);
HOOK_MESSAGE(SluggerHsStar7);
HOOK_MESSAGE(SluggerHsStar8);
HOOK_MESSAGE(SluggerHsStar9);
HOOK_MESSAGE(SluggerHsStar10);


HOOK_COMMAND("KillStar1", CommandActiveKillStar1);
HOOK_COMMAND("KillStar2", CommandActiveKillStar2);
HOOK_COMMAND("KillStar3", CommandActiveKillStar3);
HOOK_COMMAND("KillStar4", CommandActiveKillStar4);
HOOK_COMMAND("KillStar5", CommandActiveKillStar5);
HOOK_COMMAND("KillStar6", CommandActiveKillStar6);
HOOK_COMMAND("KillStar7", CommandActiveKillStar7);
HOOK_COMMAND("KillStar8", CommandActiveKillStar8);
HOOK_COMMAND("KillStar9", CommandActiveKillStar9);
HOOK_COMMAND("KillStar10", CommandActiveKillStar10);

HOOK_COMMAND("HeadshotStar1", CommandActiveHeadshotStar1);
HOOK_COMMAND("HeadshotStar2", CommandActiveHeadshotStar2);
HOOK_COMMAND("HeadshotStar3", CommandActiveHeadshotStar3);
HOOK_COMMAND("HeadshotStar4", CommandActiveHeadshotStar4);
HOOK_COMMAND("HeadshotStar5", CommandActiveHeadshotStar5);
HOOK_COMMAND("HeadshotStar6", CommandActiveHeadshotStar6);
HOOK_COMMAND("HeadshotStar7", CommandActiveHeadshotStar7);
HOOK_COMMAND("HeadshotStar8", CommandActiveHeadshotStar8);
HOOK_COMMAND("HeadshotStar9", CommandActiveHeadshotStar9);
HOOK_COMMAND("HeadshotStar10", CommandActiveHeadshotStar10);

HOOK_COMMAND("BlueStar5", CommandActiveBlueStar5);
HOOK_COMMAND("GoldStar10", CommandActiveGoldStar10);

HOOK_COMMAND("StopperStar1", CommandActiveStopperStar1);
HOOK_COMMAND("StopperStar2", CommandActiveStopperStar2);
HOOK_COMMAND("StopperStar3", CommandActiveStopperStar3);
HOOK_COMMAND("StopperStar4", CommandActiveStopperStar4);
HOOK_COMMAND("StopperStar5", CommandActiveStopperStar5);
HOOK_COMMAND("StopperStar6", CommandActiveStopperStar6);
HOOK_COMMAND("StopperStar7", CommandActiveStopperStar7);
HOOK_COMMAND("StopperStar8", CommandActiveStopperStar8);
HOOK_COMMAND("StopperStar9", CommandActiveStopperStar9);
HOOK_COMMAND("StopperStar10", CommandActiveStopperStar10);

HOOK_COMMAND("StopperHsStar1", CommandActiveStopperHsStar1);
HOOK_COMMAND("StopperHsStar2", CommandActiveStopperHsStar2);
HOOK_COMMAND("StopperHsStar3", CommandActiveStopperHsStar3);
HOOK_COMMAND("StopperHsStar4", CommandActiveStopperHsStar4);
HOOK_COMMAND("StopperHsStar5", CommandActiveStopperHsStar5);
HOOK_COMMAND("StopperHsStar6", CommandActiveStopperHsStar6);
HOOK_COMMAND("StopperHsStar7", CommandActiveStopperHsStar7);
HOOK_COMMAND("StopperHsStar8", CommandActiveStopperHsStar8);
HOOK_COMMAND("StopperHsStar9", CommandActiveStopperHsStar9);
HOOK_COMMAND("StopperHsStar10", CommandActiveStopperHsStar10);

HOOK_COMMAND("SluggerStar1", CommandActiveSluggerStar1);
HOOK_COMMAND("SluggerStar2", CommandActiveSluggerStar2);
HOOK_COMMAND("SluggerStar3", CommandActiveSluggerStar3);
HOOK_COMMAND("SluggerStar4", CommandActiveSluggerStar4);
HOOK_COMMAND("SluggerStar5", CommandActiveSluggerStar5);
HOOK_COMMAND("SluggerStar6", CommandActiveSluggerStar6);
HOOK_COMMAND("SluggerStar7", CommandActiveSluggerStar7);
HOOK_COMMAND("SluggerStar8", CommandActiveSluggerStar8);
HOOK_COMMAND("SluggerStar9", CommandActiveSluggerStar9);
HOOK_COMMAND("SluggerStar10", CommandActiveSluggerStar10);

HOOK_COMMAND("SluggerHsStar1", CommandActiveSluggerHsStar1);
HOOK_COMMAND("SluggerHsStar2", CommandActiveSluggerHsStar2);
HOOK_COMMAND("SluggerHsStar3", CommandActiveSluggerHsStar3);
HOOK_COMMAND("SluggerHsStar4", CommandActiveSluggerHsStar4);
HOOK_COMMAND("SluggerHsStar5", CommandActiveSluggerHsStar5);
HOOK_COMMAND("SluggerHsStar6", CommandActiveSluggerHsStar6);
HOOK_COMMAND("SluggerHsStar7", CommandActiveSluggerHsStar7);
HOOK_COMMAND("SluggerHsStar8", CommandActiveSluggerHsStar8);
HOOK_COMMAND("SluggerHsStar9", CommandActiveSluggerHsStar9);
HOOK_COMMAND("SluggerHsStar10", CommandActiveSluggerHsStar10);

	m_iFlags = HUD_DRAW;

	return 1;
}


int CHudKillEffect::VidInit()
{

//killframe
R_InitTexture(m_killframe, "gfx/billflx/frame/frame.tga");


//anim
R_InitTexture(m_fraganim[0], "gfx/billflx/fraganim/Frag_Kill.tga");
R_InitTexture(m_fraganim[1], "gfx/billflx/fraganim/Frag_Headshot.tga");
R_InitTexture(m_fraganim[2], "gfx/billflx/fraganim/Frag_Stopper.tga");
R_InitTexture(m_fraganim[3], "gfx/billflx/fraganim/Frag_Blue_1.tga");
R_InitTexture(m_fraganim[4], "gfx/billflx/fraganim/Frag_StopperHs.tga");
R_InitTexture(m_fraganim[5], "gfx/billflx/fraganim/Frag_melee.tga");
R_InitTexture(m_fraganim[6], "gfx/billflx/fraganim/Frag_masskill2.tga");
R_InitTexture(m_fraganim[7], "gfx/billflx/fraganim/Frag_masskill3.tga");
R_InitTexture(m_fraganim[8], "gfx/billflx/fraganim/Frag_masskill4.tga");
R_InitTexture(m_fraganim[9], "gfx/billflx/fraganim/Frag_masskill5.tga");
R_InitTexture(m_fraganim[10], "gfx/billflx/fraganim/Frag_masskill6.tga");
R_InitTexture(m_fraganim[11], "gfx/billflx/fraganim/Frag_masskill7.tga");
R_InitTexture(m_fraganim[12], "gfx/billflx/fraganim/Frag_masskill8.tga");
R_InitTexture(m_fraganim[13], "gfx/billflx/fraganim/Frag_meleeHs.tga");
R_InitTexture(m_fraganim[14], "gfx/billflx/fraganim/Frag_silver_1.tga");
R_InitTexture(m_fraganim[15], "gfx/billflx/fraganim/Frag_stoppermelee.tga");
R_InitTexture(m_fraganim[16], "gfx/billflx/fraganim/Frag_stoppermeleeHs.tga");
R_InitTexture(m_fraganim[17], "gfx/billflx/fraganim/Frag_gold_1.tga");
R_InitTexture(m_fraganim[18], "gfx/billflx/fraganim/Frag_melee.tga");

//slugger 

R_InitTexture(m_MissionComplete, "gfx/billflx/announcement/MissionComplete.tga");

R_InitTexture(m_chslugger[0], "gfx/billflx/announcement/chslug.tga");

//piercing 
R_InitTexture(m_piercing[0], "gfx/billflx/announcement/piercing.tga");


//mass 
R_InitTexture(m_mass[0], "gfx/billflx/announcement/masskill.tga");

//kill2
R_InitTexture(m_kill2[0], "gfx/billflx/announcement/double.tga");


//kill3
R_InitTexture(m_kill3[0], "gfx/billflx/announcement/triple.tga");



//kill4
R_InitTexture(m_kill4[0], "gfx/billflx/announcement/chkill.tga");


//hs
R_InitTexture(m_headshot[0], "gfx/billflx/announcement/hs.tga");


//chhs
R_InitTexture(m_chheadshot[0], "gfx/billflx/announcement/chhs.tga");


//helmet
R_InitTexture(m_helmet[0], "gfx/billflx/announcement/helmet.tga");


//chsip

R_InitTexture(m_stopper[0], "gfx/billflx/announcement/chstop.tga");



//hotkiller
R_InitTexture(m_hotkiller[0], "gfx/billflx/announcement/hotkill.tga");


//nightmare 
R_InitTexture(m_nightmare[0], "gfx/billflx/announcement/night.tga");

//special
R_InitTexture(m_special[0], "gfx/billflx/announcement/sg.tga");
R_InitTexture(m_special[1], "gfx/billflx/announcement/bs.tga");
R_InitTexture(m_special[2], "gfx/billflx/announcement/oneShot.tga");

//underneath stars
R_InitTexture(m_starPos1Kill1[0], "gfx/billflx/null");
R_InitTexture(m_starPos1Kill1[1], "gfx/billflx/star/pos1/1/0001");
R_InitTexture(m_starPos1Kill1[2], "gfx/billflx/star/pos1/1/0002");
R_InitTexture(m_starPos1Kill1[3], "gfx/billflx/star/pos1/1/0003");
R_InitTexture(m_starPos1Kill1[4], "gfx/billflx/star/pos1/1/0004");
R_InitTexture(m_starPos1Kill1[5], "gfx/billflx/star/pos1/1/0005");
R_InitTexture(m_starPos1Kill1[5], "gfx/billflx/star/pos1/1/0006");
R_InitTexture(m_starPos1Kill1[6], "gfx/billflx/star/pos1/1/0007");
R_InitTexture(m_starPos1Kill1[7], "gfx/billflx/star/pos1/1/0008");
R_InitTexture(m_starPos1Kill1[8], "gfx/billflx/star/pos1/1/0009");
R_InitTexture(m_starPos1Kill1[9], "gfx/billflx/star/pos1/1/0010");

R_InitTexture(m_starPos1Kill2[0], "gfx/billflx/null");
R_InitTexture(m_starPos1Kill2[1], "gfx/billflx/star/pos1/2/0001");
R_InitTexture(m_starPos1Kill2[2], "gfx/billflx/star/pos1/2/0002");
R_InitTexture(m_starPos1Kill2[3], "gfx/billflx/star/pos1/2/0003");
R_InitTexture(m_starPos1Kill2[4], "gfx/billflx/star/pos1/2/0004");
R_InitTexture(m_starPos1Kill2[5], "gfx/billflx/star/pos1/2/0005");
R_InitTexture(m_starPos1Kill2[6], "gfx/billflx/star/pos1/2/0006");
R_InitTexture(m_starPos1Kill2[7], "gfx/billflx/star/pos1/2/0007");
R_InitTexture(m_starPos1Kill2[8], "gfx/billflx/star/pos1/2/0008");
R_InitTexture(m_starPos1Kill2[9], "gfx/billflx/star/pos1/2/0009");
R_InitTexture(m_starPos1Kill2[10], "gfx/billflx/star/pos1/2/0010");

R_InitTexture(m_starPos1Kill3[0], "gfx/billflx/null");
R_InitTexture(m_starPos1Kill3[1], "gfx/billflx/star/pos1/3/0001");
R_InitTexture(m_starPos1Kill3[2], "gfx/billflx/star/pos1/3/0002");
R_InitTexture(m_starPos1Kill3[3], "gfx/billflx/star/pos1/3/0003");
R_InitTexture(m_starPos1Kill3[4], "gfx/billflx/star/pos1/3/0004");
R_InitTexture(m_starPos1Kill3[5], "gfx/billflx/star/pos1/3/0005");
R_InitTexture(m_starPos1Kill3[6], "gfx/billflx/star/pos1/3/0006");
R_InitTexture(m_starPos1Kill3[7], "gfx/billflx/star/pos1/3/0007");
R_InitTexture(m_starPos1Kill3[8], "gfx/billflx/star/pos1/3/0008");
R_InitTexture(m_starPos1Kill3[9], "gfx/billflx/star/pos1/3/0009");
R_InitTexture(m_starPos1Kill3[10], "gfx/billflx/star/pos1/3/0010");

R_InitTexture(m_starPos1Kill4[0], "gfx/billflx/null");
R_InitTexture(m_starPos1Kill4[1], "gfx/billflx/star/pos1/4/0001");
R_InitTexture(m_starPos1Kill4[2], "gfx/billflx/star/pos1/4/0002");
R_InitTexture(m_starPos1Kill4[3], "gfx/billflx/star/pos1/4/0003");
R_InitTexture(m_starPos1Kill4[4], "gfx/billflx/star/pos1/4/0004");
R_InitTexture(m_starPos1Kill4[5], "gfx/billflx/star/pos1/4/0005");
R_InitTexture(m_starPos1Kill4[6], "gfx/billflx/star/pos1/4/0006");
R_InitTexture(m_starPos1Kill4[7], "gfx/billflx/star/pos1/4/0007");
R_InitTexture(m_starPos1Kill4[8], "gfx/billflx/star/pos1/4/0008");
R_InitTexture(m_starPos1Kill4[9], "gfx/billflx/star/pos1/4/0009");
R_InitTexture(m_starPos1Kill4[10], "gfx/billflx/star/pos1/4/0010");

R_InitTexture(m_starPos1Kill5[0], "gfx/billflx/null");
R_InitTexture(m_starPos1Kill5[1], "gfx/billflx/star/pos1/5/0001");
R_InitTexture(m_starPos1Kill5[2], "gfx/billflx/star/pos1/5/0002");
R_InitTexture(m_starPos1Kill5[3], "gfx/billflx/star/pos1/5/0003");
R_InitTexture(m_starPos1Kill5[4], "gfx/billflx/star/pos1/5/0004");
R_InitTexture(m_starPos1Kill5[5], "gfx/billflx/star/pos1/5/0005");
R_InitTexture(m_starPos1Kill5[6], "gfx/billflx/star/pos1/5/0006");
R_InitTexture(m_starPos1Kill5[7], "gfx/billflx/star/pos1/5/0007");
R_InitTexture(m_starPos1Kill5[8], "gfx/billflx/star/pos1/5/0008");
R_InitTexture(m_starPos1Kill5[9], "gfx/billflx/star/pos1/5/0009");
R_InitTexture(m_starPos1Kill5[10], "gfx/billflx/star/pos1/5/0010");

R_InitTexture(m_starPos1Kill6[0], "gfx/billflx/null");
R_InitTexture(m_starPos1Kill6[1], "gfx/billflx/star/pos1/6/0001");
R_InitTexture(m_starPos1Kill6[2], "gfx/billflx/star/pos1/6/0002");
R_InitTexture(m_starPos1Kill6[3], "gfx/billflx/star/pos1/6/0003");
R_InitTexture(m_starPos1Kill6[4], "gfx/billflx/star/pos1/6/0004");
R_InitTexture(m_starPos1Kill6[5], "gfx/billflx/star/pos1/6/0005");
R_InitTexture(m_starPos1Kill6[6], "gfx/billflx/star/pos1/6/0006");
R_InitTexture(m_starPos1Kill6[7], "gfx/billflx/star/pos1/6/0007");
R_InitTexture(m_starPos1Kill6[8], "gfx/billflx/star/pos1/6/0008");
R_InitTexture(m_starPos1Kill6[9], "gfx/billflx/star/pos1/6/0009");
R_InitTexture(m_starPos1Kill6[10], "gfx/billflx/star/pos1/6/0010");

R_InitTexture(m_starPos1Kill7[0], "gfx/billflx/null");
R_InitTexture(m_starPos1Kill7[1], "gfx/billflx/star/pos1/7/0001");
R_InitTexture(m_starPos1Kill7[2], "gfx/billflx/star/pos1/7/0002");
R_InitTexture(m_starPos1Kill7[3], "gfx/billflx/star/pos1/7/0003");
R_InitTexture(m_starPos1Kill7[4], "gfx/billflx/star/pos1/7/0004");
R_InitTexture(m_starPos1Kill7[5], "gfx/billflx/star/pos1/7/0005");
R_InitTexture(m_starPos1Kill7[6], "gfx/billflx/star/pos1/7/0006");
R_InitTexture(m_starPos1Kill7[7], "gfx/billflx/star/pos1/7/0007");
R_InitTexture(m_starPos1Kill7[8], "gfx/billflx/star/pos1/7/0008");
R_InitTexture(m_starPos1Kill7[9], "gfx/billflx/star/pos1/7/0009");
R_InitTexture(m_starPos1Kill7[10], "gfx/billflx/star/pos1/7/0010");

R_InitTexture(m_starPos1Kill8[0], "gfx/billflx/null");
R_InitTexture(m_starPos1Kill8[1], "gfx/billflx/star/pos1/8/0001");
R_InitTexture(m_starPos1Kill8[2], "gfx/billflx/star/pos1/8/0002");
R_InitTexture(m_starPos1Kill8[3], "gfx/billflx/star/pos1/8/0003");
R_InitTexture(m_starPos1Kill8[4], "gfx/billflx/star/pos1/8/0004");
R_InitTexture(m_starPos1Kill8[5], "gfx/billflx/star/pos1/8/0005");
R_InitTexture(m_starPos1Kill8[6], "gfx/billflx/star/pos1/8/0006");
R_InitTexture(m_starPos1Kill8[7], "gfx/billflx/star/pos1/8/0007");
R_InitTexture(m_starPos1Kill8[8], "gfx/billflx/star/pos1/8/0008");
R_InitTexture(m_starPos1Kill8[9], "gfx/billflx/star/pos1/8/0009");
R_InitTexture(m_starPos1Kill8[10], "gfx/billflx/star/pos1/8/0010");

R_InitTexture(m_starPos1Kill9[0], "gfx/billflx/null");
R_InitTexture(m_starPos1Kill9[1], "gfx/billflx/star/pos1/9/0001");
R_InitTexture(m_starPos1Kill9[2], "gfx/billflx/star/pos1/9/0002");
R_InitTexture(m_starPos1Kill9[3], "gfx/billflx/star/pos1/9/0003");
R_InitTexture(m_starPos1Kill9[4], "gfx/billflx/star/pos1/9/0004");
R_InitTexture(m_starPos1Kill9[5], "gfx/billflx/star/pos1/9/0005");
R_InitTexture(m_starPos1Kill9[6], "gfx/billflx/star/pos1/9/0006");
R_InitTexture(m_starPos1Kill9[7], "gfx/billflx/star/pos1/9/0007");
R_InitTexture(m_starPos1Kill9[8], "gfx/billflx/star/pos1/9/0008");
R_InitTexture(m_starPos1Kill9[9], "gfx/billflx/star/pos1/9/0009");
R_InitTexture(m_starPos1Kill9[10], "gfx/billflx/star/pos1/9/0010");


R_InitTexture(m_starPos2Kill1[0], "gfx/billflx/null");
R_InitTexture(m_starPos2Kill1[1], "gfx/billflx/star/pos2/1/0001");
R_InitTexture(m_starPos2Kill1[2], "gfx/billflx/star/pos2/1/0002");
R_InitTexture(m_starPos2Kill1[3], "gfx/billflx/star/pos2/1/0003");
R_InitTexture(m_starPos2Kill1[4], "gfx/billflx/star/pos2/1/0004");
R_InitTexture(m_starPos2Kill1[5], "gfx/billflx/star/pos2/1/0005");
R_InitTexture(m_starPos2Kill1[6], "gfx/billflx/star/pos2/1/0006");
R_InitTexture(m_starPos2Kill1[7], "gfx/billflx/star/pos2/1/0007");
R_InitTexture(m_starPos2Kill1[8], "gfx/billflx/star/pos2/1/0008");
R_InitTexture(m_starPos2Kill1[9], "gfx/billflx/star/pos2/1/0009");
R_InitTexture(m_starPos2Kill1[10], "gfx/billflx/star/pos2/1/0010");

R_InitTexture(m_starPos2Kill2[0], "gfx/billflx/null");
R_InitTexture(m_starPos2Kill2[1], "gfx/billflx/star/pos2/2/0001");
R_InitTexture(m_starPos2Kill2[2], "gfx/billflx/star/pos2/2/0002");
R_InitTexture(m_starPos2Kill2[3], "gfx/billflx/star/pos2/2/0003");
R_InitTexture(m_starPos2Kill2[4], "gfx/billflx/star/pos2/2/0004");
R_InitTexture(m_starPos2Kill2[5], "gfx/billflx/star/pos2/2/0005");
R_InitTexture(m_starPos2Kill2[6], "gfx/billflx/star/pos2/2/0006");
R_InitTexture(m_starPos2Kill2[7], "gfx/billflx/star/pos2/2/0007");
R_InitTexture(m_starPos2Kill2[8], "gfx/billflx/star/pos2/2/0008");
R_InitTexture(m_starPos2Kill2[9], "gfx/billflx/star/pos2/2/0009");
R_InitTexture(m_starPos2Kill2[10], "gfx/billflx/star/pos2/2/0010");

R_InitTexture(m_starPos2Kill3[0], "gfx/billflx/null");
R_InitTexture(m_starPos2Kill3[1], "gfx/billflx/star/pos2/3/0001");
R_InitTexture(m_starPos2Kill3[2], "gfx/billflx/star/pos2/3/0002");
R_InitTexture(m_starPos2Kill3[3], "gfx/billflx/star/pos2/3/0003");
R_InitTexture(m_starPos2Kill3[4], "gfx/billflx/star/pos2/3/0004");
R_InitTexture(m_starPos2Kill3[5], "gfx/billflx/star/pos2/3/0005");
R_InitTexture(m_starPos2Kill3[6], "gfx/billflx/star/pos2/3/0006");
R_InitTexture(m_starPos2Kill3[7], "gfx/billflx/star/pos2/3/0007");
R_InitTexture(m_starPos2Kill3[8], "gfx/billflx/star/pos2/3/0008");
R_InitTexture(m_starPos2Kill3[9], "gfx/billflx/star/pos2/3/0009");
R_InitTexture(m_starPos2Kill3[10], "gfx/billflx/star/pos2/3/0010");

R_InitTexture(m_starPos2Kill4[0], "gfx/billflx/null");
R_InitTexture(m_starPos2Kill4[1], "gfx/billflx/star/pos2/4/0001");
R_InitTexture(m_starPos2Kill4[2], "gfx/billflx/star/pos2/4/0002");
R_InitTexture(m_starPos2Kill4[3], "gfx/billflx/star/pos2/4/0003");
R_InitTexture(m_starPos2Kill4[4], "gfx/billflx/star/pos2/4/0004");
R_InitTexture(m_starPos2Kill4[5], "gfx/billflx/star/pos2/4/0005");
R_InitTexture(m_starPos2Kill4[6], "gfx/billflx/star/pos2/4/0006");
R_InitTexture(m_starPos2Kill4[7], "gfx/billflx/star/pos2/4/0007");
R_InitTexture(m_starPos2Kill4[8], "gfx/billflx/star/pos2/4/0008");
R_InitTexture(m_starPos2Kill4[9], "gfx/billflx/star/pos2/4/0009");
R_InitTexture(m_starPos2Kill4[10], "gfx/billflx/star/pos2/4/0010");

R_InitTexture(m_starPos2Kill5[0], "gfx/billflx/null");
R_InitTexture(m_starPos2Kill5[1], "gfx/billflx/star/pos2/5/0001");
R_InitTexture(m_starPos2Kill5[2], "gfx/billflx/star/pos2/5/0002");
R_InitTexture(m_starPos2Kill5[3], "gfx/billflx/star/pos2/5/0003");
R_InitTexture(m_starPos2Kill5[4], "gfx/billflx/star/pos2/5/0004");
R_InitTexture(m_starPos2Kill5[5], "gfx/billflx/star/pos2/5/0005");
R_InitTexture(m_starPos2Kill5[6], "gfx/billflx/star/pos2/5/0006");
R_InitTexture(m_starPos2Kill5[7], "gfx/billflx/star/pos2/5/0007");
R_InitTexture(m_starPos2Kill5[8], "gfx/billflx/star/pos2/5/0008");
R_InitTexture(m_starPos2Kill5[9], "gfx/billflx/star/pos2/5/0009");
R_InitTexture(m_starPos2Kill5[10], "gfx/billflx/star/pos2/5/0010");

R_InitTexture(m_starPos2Kill6[0], "gfx/billflx/null");
R_InitTexture(m_starPos2Kill6[1], "gfx/billflx/star/pos2/6/0001");
R_InitTexture(m_starPos2Kill6[2], "gfx/billflx/star/pos2/6/0002");
R_InitTexture(m_starPos2Kill6[3], "gfx/billflx/star/pos2/6/0003");
R_InitTexture(m_starPos2Kill6[4], "gfx/billflx/star/pos2/6/0004");
R_InitTexture(m_starPos2Kill6[5], "gfx/billflx/star/pos2/6/0005");
R_InitTexture(m_starPos2Kill6[6], "gfx/billflx/star/pos2/6/0006");
R_InitTexture(m_starPos2Kill6[7], "gfx/billflx/star/pos2/6/0007");
R_InitTexture(m_starPos2Kill6[8], "gfx/billflx/star/pos2/6/0008");
R_InitTexture(m_starPos2Kill6[9], "gfx/billflx/star/pos2/6/0009");
R_InitTexture(m_starPos2Kill6[10], "gfx/billflx/star/pos2/6/0010");

R_InitTexture(m_starPos2Kill7[0], "gfx/billflx/null");
R_InitTexture(m_starPos2Kill7[1], "gfx/billflx/star/pos2/7/0001");
R_InitTexture(m_starPos2Kill7[2], "gfx/billflx/star/pos2/7/0002");
R_InitTexture(m_starPos2Kill7[3], "gfx/billflx/star/pos2/7/0003");
R_InitTexture(m_starPos2Kill7[4], "gfx/billflx/star/pos2/7/0004");
R_InitTexture(m_starPos2Kill7[5], "gfx/billflx/star/pos2/7/0005");
R_InitTexture(m_starPos2Kill7[6], "gfx/billflx/star/pos2/7/0006");
R_InitTexture(m_starPos2Kill7[7], "gfx/billflx/star/pos2/7/0007");
R_InitTexture(m_starPos2Kill7[8], "gfx/billflx/star/pos2/7/0008");
R_InitTexture(m_starPos2Kill7[9], "gfx/billflx/star/pos2/7/0009");
R_InitTexture(m_starPos2Kill7[10], "gfx/billflx/star/pos2/7/0010");

R_InitTexture(m_starPos2Kill8[0], "gfx/billflx/null");
R_InitTexture(m_starPos2Kill8[1], "gfx/billflx/star/pos2/8/0001");
R_InitTexture(m_starPos2Kill8[2], "gfx/billflx/star/pos2/8/0002");
R_InitTexture(m_starPos2Kill8[3], "gfx/billflx/star/pos2/8/0003");
R_InitTexture(m_starPos2Kill8[4], "gfx/billflx/star/pos2/8/0004");
R_InitTexture(m_starPos2Kill8[5], "gfx/billflx/star/pos2/8/0005");
R_InitTexture(m_starPos2Kill8[6], "gfx/billflx/star/pos2/8/0006");
R_InitTexture(m_starPos2Kill8[7], "gfx/billflx/star/pos2/8/0007");
R_InitTexture(m_starPos2Kill8[8], "gfx/billflx/star/pos2/8/0008");
R_InitTexture(m_starPos2Kill8[9], "gfx/billflx/star/pos2/8/0009");
R_InitTexture(m_starPos2Kill8[10], "gfx/billflx/star/pos2/8/0010");

R_InitTexture(m_starPos2Kill9[0], "gfx/billflx/null");
R_InitTexture(m_starPos2Kill9[1], "gfx/billflx/star/pos2/9/0001");
R_InitTexture(m_starPos2Kill9[2], "gfx/billflx/star/pos2/9/0002");
R_InitTexture(m_starPos2Kill9[3], "gfx/billflx/star/pos2/9/0003");
R_InitTexture(m_starPos2Kill9[4], "gfx/billflx/star/pos2/9/0004");
R_InitTexture(m_starPos2Kill9[5], "gfx/billflx/star/pos2/9/0005");
R_InitTexture(m_starPos2Kill9[6], "gfx/billflx/star/pos2/9/0006");
R_InitTexture(m_starPos2Kill9[7], "gfx/billflx/star/pos2/9/0007");
R_InitTexture(m_starPos2Kill9[8], "gfx/billflx/star/pos2/9/0008");
R_InitTexture(m_starPos2Kill9[9], "gfx/billflx/star/pos2/9/0009");
R_InitTexture(m_starPos2Kill9[10], "gfx/billflx/star/pos2/9/0010");

R_InitTexture(m_starPos2Kill10[0], "gfx/billflx/null");
R_InitTexture(m_starPos2Kill10[1], "gfx/billflx/star/pos2/10/0001");
R_InitTexture(m_starPos2Kill10[2], "gfx/billflx/star/pos2/10/0002");
R_InitTexture(m_starPos2Kill10[3], "gfx/billflx/star/pos2/10/0003");
R_InitTexture(m_starPos2Kill10[4], "gfx/billflx/star/pos2/10/0004");
R_InitTexture(m_starPos2Kill10[5], "gfx/billflx/star/pos2/10/0005");
R_InitTexture(m_starPos2Kill10[6], "gfx/billflx/star/pos2/10/0006");
R_InitTexture(m_starPos2Kill10[7], "gfx/billflx/star/pos2/10/0007");
R_InitTexture(m_starPos2Kill10[8], "gfx/billflx/star/pos2/10/0008");
R_InitTexture(m_starPos2Kill10[9], "gfx/billflx/star/pos2/10/0009");
R_InitTexture(m_starPos2Kill10[10], "gfx/billflx/star/pos2/10/0010");

//bruhh
m_HUD_cross = gHUD.GetSpriteIndex( "cross" );

R_InitTexture(m_hit, "gfx/billflx/hit");

//mission 
mission_kill = CVAR_CREATE("billflxcrypted_mission_kill","0", CVAR_INVISIBLE);
mission_doublekill = CVAR_CREATE("billflxcrypted_mission_doublekill","0",CVAR_INVISIBLE);
mission_triplekill = CVAR_CREATE("billflxcrypted_mission_triplekill","0", CVAR_INVISIBLE);
mission_chainkiller = CVAR_CREATE("billflxcrypted_mission_chainkiller","0", CVAR_INVISIBLE);
mission_headshot = CVAR_CREATE("billflxcrypted_mission_headshot","0",CVAR_INVISIBLE);
mission_chainheadshot = CVAR_CREATE("billflxcrypted_mission_chainheadshot","0", CVAR_INVISIBLE);
mission_slugger = CVAR_CREATE("billflxcrypted_mission_slugger","0",CVAR_INVISIBLE);
mission_masskill = CVAR_CREATE("billflxcrypted_mission_masskill","0", CVAR_INVISIBLE);
mission_piercingshot = CVAR_CREATE("billflxcrypted_mission_piercingshot","0",CVAR_INVISIBLE);
pb_point = CVAR_CREATE("billflxencrypted_pb_points","999999999",CVAR_INVISIBLE);

	return 1;
}

int CHudKillEffect::Draw( float flTime )
{
/////////////////////////////////////////underneath stars///////////////////////////////////////
/////////////////////////////////////////underneath stars///////////////////////////////////////
/////////////////////////////////////////underneath stars///////////////////////////////////////

int xr2 = ScreenWidth / 2;
int yr2 = 5;

int CrossWidthN2 = gHUD.GetSpriteRect(m_HUD_cross).right - gHUD.GetSpriteRect(m_HUD_cross).left;
int ye2, xe2;
ye2 = TrueHeight- gHUD.m_iFontHeight - gHUD.m_iFontHeight / 1;
xe2 = TrueWidth - (9.3* CrossWidthN2);

gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);

//kill1

if (gHUD.m_star1cmd->value == 0)
{//no kill 
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
m_starPos1Kill1[0]->Bind();
DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star1cmd->value == 1)
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill1[1]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill1[1]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star1cmd->value == 2) //hs
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill1[2]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill1[2]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star1cmd->value == 3)//stopper
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill1[3]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill1[3]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star1cmd->value == 4)//blue
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill1[4]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill1[4]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star1cmd->value == 5)//gold
{

if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill1[5]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill1[5]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}

else if (gHUD.m_star1cmd->value == 6)//Slugger
{

if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill1[7]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill1[7]->Bind();
}
DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}

else if (gHUD.m_star1cmd->value == 7)//ps
{

if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill1[8]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill1[8]->Bind();
}
DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}


//Kill2 =============================\\\Kill2
//Kill2 =============================\\\Kill2
//Kill2 =============================\\\Kill2
//Kill2 =============================\\\Kill2
//Kill2 =============================\\\Kill2

if (gHUD.m_star2cmd->value == 0)
{//no kill 
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
m_starPos1Kill2[0]->Bind();
DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star2cmd->value == 1)
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill2[1]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill2[1]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}

else if (gHUD.m_star2cmd->value == 2) //hs
{
if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill2[2]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill2[2]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}

else if (gHUD.m_star2cmd->value == 3)//stopper
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill2[3]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill2[3]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star2cmd->value == 4)//blue
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill2[4]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill2[4]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star2cmd->value == 5)//gold
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill2[5]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill2[5]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star2cmd->value == 6)//slug
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill2[7]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill2[7]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star2cmd->value == 7)//ps
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill2[8]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill2[8]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}


//Kill3 =============================\\\Kill3
//Kill3 =============================\\\Kill3
//Kill3 =============================\\\Kill3
//Kill3 =============================\\\Kill3
//Kill3 =============================\\\Kill3

if (gHUD.m_star3cmd->value == 0)
{//no kill 
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
m_starPos1Kill3[0]->Bind();
DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star3cmd->value == 1)
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill3[1]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill3[1]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star3cmd->value == 2) //hs
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill3[2]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill3[2]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star3cmd->value == 3)//stopper
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill3[3]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill3[3]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star3cmd->value == 4)//blue
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill3[4]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill3[4]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star3cmd->value == 5)//gold
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill3[5]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill3[5]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}

else if (gHUD.m_star3cmd->value == 6)//slug
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill3[7]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill3[7]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star3cmd->value == 7)//ps
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill3[8]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill3[8]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}




//Kill4 =============================\\\Kill4
//Kill4 =============================\\\Kill4
//Kill4 =============================\\\Kill4
//Kill4 =============================\\\Kill4
//Kill4 =============================\\\Kill4

if (gHUD.m_star4cmd->value == 0)
{//no kill 
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
m_starPos1Kill4[0]->Bind();
DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star4cmd->value == 1)
{

if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill4[1]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill4[1]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star4cmd->value == 2) //hs
{

if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill4[2]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill4[2]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star4cmd->value == 3)//stopper
{
if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill4[3]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill4[3]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star4cmd->value == 4)//blue
{
if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill4[4]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill4[4]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star4cmd->value == 5)//gold
{
if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill4[5]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill4[5]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star4cmd->value == 6)//slug
{
if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill4[7]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill4[7]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star4cmd->value == 7)//ps
{
if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill4[8]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill4[8]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}


//Kill5 =============================\\\Kill5
//Kill5 =============================\\\Kill5
//Kill5 =============================\\\Kill5
//Kill5 =============================\\\Kill5
//Kill5 =============================\\\Kill5

if (gHUD.m_star5cmd->value == 0)
{//no kill 
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
m_starPos1Kill5[0]->Bind();
DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star5cmd->value == 1)
{

if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill5[1]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill5[1]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star5cmd->value == 2) //hs
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill5[2]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill5[2]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star5cmd->value == 3)//stopper
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill5[3]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill5[3]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star5cmd->value == 4)//blue
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill5[4]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill5[4]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star5cmd->value == 5)//gold
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill5[5]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill5[5]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star5cmd->value == 6)//slug
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill5[7]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill5[7]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star5cmd->value == 7)//ps
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill5[8]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill5[8]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}



//Kill6 =============================\\\Kill6
//Kill6 =============================\\\Kill6
//Kill6 =============================\\\Kill6
//Kill6 =============================\\\Kill6
//Kill6 =============================\\\Kill6

if (gHUD.m_star6cmd->value == 0)
{//no kill 
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
m_starPos1Kill6[0]->Bind();
DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star6cmd->value == 1)
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill6[1]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill6[1]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star6cmd->value == 2) //hs
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill6[2]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill6[2]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star6cmd->value == 3)//stopper
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill6[3]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill6[3]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star6cmd->value == 4)//blue
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill6[4]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill6[4]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star6cmd->value == 5)//gold
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill6[5]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill6[5]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}

else if (gHUD.m_star6cmd->value == 6)//slug
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill6[7]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill6[7]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star6cmd->value == 7)//gold
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill6[8]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill6[8]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}


//Kill7 =============================\\\Kill7
//Kill7 =============================\\\Kill7
//Kill7 =============================\\\Kill7
//Kill7 =============================\\\Kill7
//Kill7 =============================\\\Kill7

if (gHUD.m_star7cmd->value == 0)
{//no kill 
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
m_starPos1Kill7[0]->Bind();
DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star7cmd->value == 1)
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill7[1]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill7[1]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star7cmd->value == 2) //hs
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill7[2]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill7[2]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star7cmd->value == 3)//stopper
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill7[3]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill7[3]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star7cmd->value == 4)//blue
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill7[4]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill7[4]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star7cmd->value == 5)//gold
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill7[5]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill7[5]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star7cmd->value == 6)//slug
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill7[7]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill7[7]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star7cmd->value == 7)//ps
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill7[8]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill7[8]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}


//Kill8 =============================\\\Kill8
//Kill8 =============================\\\Kill8
//Kill8 =============================\\\Kill8
//Kill8 =============================\\\Kill8
//Kill8 =============================\\\Kill8

if (gHUD.m_star8cmd->value == 0)
{//no kill 
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
m_starPos1Kill8[0]->Bind();
DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star8cmd->value == 1)
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill8[1]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill8[1]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star8cmd->value == 2) //hs
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill8[2]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill8[2]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star8cmd->value == 3)//stopper
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill8[3]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill8[3]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star8cmd->value == 4)//blue
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill8[4]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill8[4]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star8cmd->value == 5)//gold
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill8[5]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill8[5]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star8cmd->value == 6)//slug
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill8[7]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill8[7]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star8cmd->value == 7)//ps
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill8[8]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill8[8]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}


//Kill9 =============================\\\Kill9
//Kill9 =============================\\\Kill9
//Kill9 =============================\\\Kill9
//Kill9 =============================\\\Kill9
//Kill9 =============================\\\Kill9

if (gHUD.m_star9cmd->value == 0)
{//no kill 
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
m_starPos1Kill9[0]->Bind();
DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star9cmd->value == 1)
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill9[1]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill9[1]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star9cmd->value == 2) //hs
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill9[2]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill9[2]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star9cmd->value == 3)//stopper
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill9[3]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill9[3]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star9cmd->value == 4)//blue
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill9[4]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill9[4]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star9cmd->value == 5)//gold
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill9[5]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill9[5]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star9cmd->value == 6)//slug
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill9[7]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill9[7]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star9cmd->value == 7)//gold
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos1Kill9[8]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill9[8]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}

//Kill10 =============================\\\Kill10
//Kill10 =============================\\\Kill10
//Kill10 =============================\\\Kill10
//Kill10 =============================\\\Kill10
//Kill10 =============================\\\Kill10

if (gHUD.m_star10cmd->value == 0)
{//no kill 
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
m_starPos2Kill10[0]->Bind();
DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star10cmd->value == 1)
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos2Kill10[1]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill10[1]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star10cmd->value == 2) //hs
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos2Kill10[2]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill10[2]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star10cmd->value == 3)//stopper
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos2Kill10[3]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill10[3]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star10cmd->value == 4)//blue
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos2Kill10[4]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill10[4]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star10cmd->value == 5)//gold
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos2Kill10[5]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill10[5]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star10cmd->value == 6)//slug
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos2Kill10[7]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill10[7]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}
else if (gHUD.m_star10cmd->value == 7)//ps
{


if (gHUD.m_starpos->value == 0)//pos 1
{
m_starPos2Kill10[7]->Bind();
}
else if (gHUD.m_starpos->value == 1)//pos 2
{
m_starPos2Kill10[7]->Bind();
}

DrawUtils::Draw2DQuadScaled(xr2 - 850 / 2, ye2 - gHUD.m_iFontHeight / 2, xr2 + 850 / 2, ScreenHeight / 1);
}

//screen kill effect 
Pointkill_time -= 1;//done
Doublekill_time -= 1;//done
Triplekill_time -= 1;//done
Chainkiller_time -= 1;//done
HeadshotPoint_time -= 1;//done
Headshot_time -= 1; //done 
ChainHeadshot_time -= 1;//done
Helmet_time -= 1;//done
Stopper_time -= 1;//done
Slugger_time -= 1;
HotKiller_time -= 1;//done
Nightmare_time -= 1;//done
MissionComplete_time -= 1;//done

SpecialGunner_time -= 1;//done
BombShot_time -= 1;//done
oneShot_time -= 1;//done
killframe_time -= 1;//done
killframeAnim_time -= 1;//done
hit_time -= 1;//done

PiercingShot_time -= 1;//done
MassKill_time -= 1;//done

FragAnimKill_time -= 1;//done
FragAnimHs_time -= 1;//done
FragAnimStopper_time -= 1;//done
FragAnimBlue_time -= 1;//done
FragAnimGold_time -= 1;//done

int x = ScreenWidth / 2;
int y = 2;
int x2 = ScreenWidth / 2; 
int y2 = ScreenHeight / 2;

Pos1_time -= 1;
Pos2_time -= 1;


//hit
if (hit_time == 50) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }

else if (hit_time == 49) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 48) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 47) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 46) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 45) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 44) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 43) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 42) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 41) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 40) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 39) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 38) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 37) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 36) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 35) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 34) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 33) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 32) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 31) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 30) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 29) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 28) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 27) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 26) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 25) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 24) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 23) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 22) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 21) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 20) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 19) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 18) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 17) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 16) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 15) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 14) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 13) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 190); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 12) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 180); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 11) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 150); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 10) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 9) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 90); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 8) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 7) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 70); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 6) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 5) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 50); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 4) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 40); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 3) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 30); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 2) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 1) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }
else if (hit_time == 0) { m_hit->Bind(); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha ); DrawUtils::Draw2DQuadScaled(x2 - gHUD.hitmark_size->value, y2 - gHUD.hitmark_size->value,x2 + gHUD.hitmark_size->value,y2 + gHUD.hitmark_size->value ); }

////kill1===============kill1 =======================///
////kill1===============kill1 =======================///
////kill1===============kill1 =======================///
////kill1===============kill1 =======================///
//1st y + down last y - up
if (killframe_time == 40) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 180); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); 
}
else if (killframe_time == 39) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 190); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 38) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 37) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 36) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 35) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 34) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 33) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 32) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 190); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 31) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 180); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 30) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 170); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 29) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 160); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 28) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 150); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 27) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 140); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 26) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 25) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 120); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 24) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 23) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 22) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 21) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 20) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 19) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 18) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 17) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 16) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 15) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 14) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 13) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 12) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 11) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 10) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 9) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 8) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 7) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 90); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 6) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 5) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 75); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 4) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 70); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 3) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 2) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 50); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 1) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 30); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); }
else if (killframe_time == 0) { m_killframe->Bind();gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 140 / 2, y+ 260, x + 140 / 2, y + 360); 
}


//frame anim

{
if (frag_kill)
m_fraganim[0]->Bind();
else if (frag_headshot)
m_fraganim[1]->Bind();
else if (frag_melee)
m_fraganim[5]->Bind();
else if (frag_meleehs)
m_fraganim[13]->Bind();
else if (frag_stopper)
m_fraganim[2]->Bind();

if (killframeAnim_time == 33){
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 150 / 2, y+ 245, x + 150 / 2, y + 385);}
else if (killframeAnim_time == 32){
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 110); DrawUtils::Draw2DQuadScaled(x - 150 / 2, y+ 245, x + 150 / 2, y + 385);}
else if (killframeAnim_time == 31) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 120); DrawUtils::Draw2DQuadScaled(x - 100 / 2, y+ 265, x + 100 / 2, y + 365);}
else if (killframeAnim_time == 30) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 100 / 2, y+ 265, x + 100 / 2, y + 365);}
else if (killframeAnim_time == 29) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 150); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 28) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 27) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 26) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 25) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 24) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 23) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 22) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 21) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 20) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 19) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 18) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 17) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 16) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 15) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 14) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 13) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 12) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 11) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 10) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 9) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 8) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 7) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 190); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 285, x + 70 / 2, y + 345); }
else if (killframeAnim_time == 6) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 160); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 335, x + 70 / 2, y + 395); }
else if (killframeAnim_time == 5) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 140); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 385, x + 70 / 2, y + 445); }
else if (killframeAnim_time == 4) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 90); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 435, x + 70 / 2, y + 495); }
else if (killframeAnim_time == 3) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 70); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 485, x + 70 / 2, y + 545); }
else if (killframeAnim_time == 2) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 50); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 535, x + 70 / 2, y + 595); }
else if (killframeAnim_time == 1) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 585, x + 70 / 2, y + 645); }
else if (killframeAnim_time == 0) { gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 70 / 2, y+ 635, x + 70 / 2, y + 695); }
}

int m_HUD_cross;
int ye;
int xe;
int CrossWidthN = gHUD.GetSpriteRect(m_HUD_cross).right - gHUD.GetSpriteRect(m_HUD_cross).left;

m_HUD_cross = gHUD.GetSpriteIndex( "cross" );
ye = TrueHeight- gHUD.m_iFontHeight - gHUD.m_iFontHeight / 1.5;
xe = TrueWidth - (9.3* CrossWidthN);



////=============°°°°°FragAnimKill=============°°°°°////////////=============°°°°°FragAnimKill=============°°°°°////////////=============°°°°°FragAnimKill=============°°°°°////////////=============°°°°°FragAnimKill=============°°°°°////////////=============°°°°°FragAnimKill=============°°°°°////////////=============°°°°°FragAnimKill=============°°°°°////////////=============°°°°°FragAnimKill=============°°°°°////////
if (FragAnimKill_time == 80)
{
m_fraganim[0]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimKill_time == 79)
{
m_fraganim[0]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimKill_time == 78)
{
m_fraganim[0]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}



else if (FragAnimKill_time == 77)
{
m_fraganim[0]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimKill_time == 76)
{
m_fraganim[0]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimKill_time == 75)
{
m_fraganim[0]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}


else if (FragAnimKill_time == 74)
{
m_fraganim[0]->Bind(); //last
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 15 / 2, ye - gHUD.m_iFontHeight / 0.5, x + 135 / 2, ScreenHeight / 1);
}
else if (FragAnimKill_time == 73)
{
m_fraganim[0]->Bind(); //last
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 15 / 2, ye - gHUD.m_iFontHeight / 0.5, x + 135 / 2, ScreenHeight / 1);
}
else if (FragAnimKill_time == 72)
{
m_fraganim[0]->Bind(); //last
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 15 / 2, ye - gHUD.m_iFontHeight / 0.5, x + 135 / 2, ScreenHeight / 1);
}



else if (FragAnimKill_time == 71)
{
m_fraganim[0]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimKill_time == 70)
{
m_fraganim[0]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimKill_time == 69)
{
m_fraganim[0]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}


else if (FragAnimKill_time == 68)
{
m_fraganim[0]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimKill_time == 67)
{
m_fraganim[0]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimKill_time == 66)
{
m_fraganim[0]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}

////=============°°°°°FragAnimHs=============°°°°°////////////=============°°°°°FragAnimHs=============°°°°°////////////=============°°°°°FragAnimHs=============°°°°°////////////=============°°°°°FragAnimHs=============°°°°°////////////=============°°°°°FragAnimHs=============°°°°°////////////=============°°°°°FragAnimHs=============°°°°°////////////=============°°°°°FragAnimHs=============°°°°°////////
if (FragAnimHs_time == 80)
{
m_fraganim[1]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimHs_time == 79)
{
m_fraganim[1]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimHs_time == 78)
{
m_fraganim[1]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}


else if (FragAnimHs_time == 77)
{
m_fraganim[1]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimHs_time == 76)
{
m_fraganim[1]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimHs_time == 75)
{
m_fraganim[1]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}



else if (FragAnimHs_time == 74)
{
m_fraganim[1]->Bind(); //last
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 15 / 2, ye - gHUD.m_iFontHeight / 0.5, x + 135 / 2, ScreenHeight / 1);
}
else if (FragAnimHs_time == 73)
{
m_fraganim[1]->Bind(); //last
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 15 / 2, ye - gHUD.m_iFontHeight / 0.5, x + 135 / 2, ScreenHeight / 1);
}
else if (FragAnimHs_time == 72)
{
m_fraganim[1]->Bind(); //last
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 15 / 2, ye - gHUD.m_iFontHeight / 0.5, x + 135 / 2, ScreenHeight / 1);
}



else if (FragAnimHs_time == 71)
{
m_fraganim[1]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimHs_time == 70)
{
m_fraganim[1]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimHs_time == 69)
{
m_fraganim[1]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}


else if (FragAnimHs_time == 68)
{
m_fraganim[1]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimHs_time == 67)
{
m_fraganim[1]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimHs_time == 66)
{
m_fraganim[1]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}

////=============°°°°°FragAnimStopper=============°°°°°////////////=============°°°°°FragAnimStopper=============°°°°°////////////=============°°°°°FragAnimStopper=============°°°°°////////////=============°°°°°FragAnimStopper=============°°°°°////////////=============°°°°°FragAnimStopper=============°°°°°////////////=============°°°°°FragAnimStopper=============°°°°°////////////=============°°°°°FragAnimStopper=============°°°°°////////
if (FragAnimStopper_time == 80)
{
m_fraganim[2]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimStopper_time == 79)
{
m_fraganim[2]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimStopper_time == 78)
{
m_fraganim[2]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}



else if (FragAnimStopper_time == 77)
{
m_fraganim[2]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimStopper_time == 76)
{
m_fraganim[2]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimStopper_time == 75)
{
m_fraganim[2]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}



else if (FragAnimStopper_time == 73)
{
m_fraganim[2]->Bind(); //last
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 15 / 2, ye - gHUD.m_iFontHeight / 0.5, x + 135 / 2, ScreenHeight / 1);
}
else if (FragAnimStopper_time == 74)
{
m_fraganim[2]->Bind(); //last
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 15 / 2, ye - gHUD.m_iFontHeight / 0.5, x + 135 / 2, ScreenHeight / 1);
}
else if (FragAnimStopper_time == 73)
{
m_fraganim[2]->Bind(); //last
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 15 / 2, ye - gHUD.m_iFontHeight / 0.5, x + 135 / 2, ScreenHeight / 1);
}



else if (FragAnimStopper_time == 72)
{
m_fraganim[2]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimStopper_time == 71)
{
m_fraganim[2]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimStopper_time == 70)
{
m_fraganim[2]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}



else if (FragAnimStopper_time == 69)
{
m_fraganim[2]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimStopper_time == 68)
{
m_fraganim[2]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimStopper_time == 67)
{
m_fraganim[2]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}

////=============°°°°°FragAnimBlue=============°°°°°////////////=============°°°°°FragAnimBlue=============°°°°°////////////=============°°°°°FragAnimBlue=============°°°°°////////////=============°°°°°FragAnimBlue=============°°°°°////////////=============°°°°°FragAnimBlue=============°°°°°////////////=============°°°°°FragAnimBlue=============°°°°°////////////=============°°°°°FragAnimBlue=============°°°°°////////
if (FragAnimBlue_time == 80)
{
m_fraganim[3]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimBlue_time == 79)
{
m_fraganim[3]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimBlue_time == 78)
{
m_fraganim[3]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}



else if (FragAnimBlue_time == 77)
{
m_fraganim[3]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimBlue_time == 76)
{
m_fraganim[3]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimBlue_time == 75)
{
m_fraganim[3]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}




else if (FragAnimBlue_time == 74)
{
m_fraganim[3]->Bind(); //last
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 15 / 2, ye - gHUD.m_iFontHeight / 0.5, x + 135 / 2, ScreenHeight / 1);
}
else if (FragAnimBlue_time == 73)
{
m_fraganim[3]->Bind(); //last
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 15 / 2, ye - gHUD.m_iFontHeight / 0.5, x + 135 / 2, ScreenHeight / 1);
}
else if (FragAnimBlue_time == 72)
{
m_fraganim[3]->Bind(); //last
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 15 / 2, ye - gHUD.m_iFontHeight / 0.5, x + 135 / 2, ScreenHeight / 1);
}




else if (FragAnimBlue_time == 71)
{
m_fraganim[3]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimBlue_time == 70)
{
m_fraganim[3]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimBlue_time == 69)
{
m_fraganim[3]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}



else if (FragAnimBlue_time == 68)
{
m_fraganim[3]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimBlue_time == 67)
{
m_fraganim[3]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimBlue_time == 66)
{
m_fraganim[3]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}

////=============°°°°°FragAnimGold=============°°°°°////////////=============°°°°°FragAnimGold=============°°°°°////////////=============°°°°°FragAnimGold=============°°°°°////////////=============°°°°°FragAnimGold=============°°°°°////////////=============°°°°°FragAnimGold=============°°°°°////////////=============°°°°°FragAnimGold=============°°°°°////////////=============°°°°°FragAnimGold=============°°°°°////////
if (FragAnimGold_time == 80)
{
m_fraganim[4]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimGold_time == 79)
{
m_fraganim[4]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimGold_time == 78)
{
m_fraganim[4]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}


else if (FragAnimGold_time == 77)
{
m_fraganim[4]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimGold_time == 76)
{
m_fraganim[4]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimGold_time == 75)
{
m_fraganim[4]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}




else if (FragAnimGold_time == 74)
{
m_fraganim[4]->Bind(); //last
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 15 / 2, ye - gHUD.m_iFontHeight / 0.5, x + 135 / 2, ScreenHeight / 1);
}
else if (FragAnimGold_time == 73)
{
m_fraganim[4]->Bind(); //last
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 15 / 2, ye - gHUD.m_iFontHeight / 0.5, x + 135 / 2, ScreenHeight / 1);
}
else if (FragAnimGold_time == 72)
{
m_fraganim[4]->Bind(); //last
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 15 / 2, ye - gHUD.m_iFontHeight / 0.5, x + 135 / 2, ScreenHeight / 1);
}




else if (FragAnimGold_time == 71)
{
m_fraganim[4]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimGold_time == 70)
{
m_fraganim[4]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}
else if (FragAnimGold_time == 69)
{
m_fraganim[4]->Bind(); //middle
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 25 / 2, ye - gHUD.m_iFontHeight / 0.7, x + 105 / 2, ScreenHeight / 1);
}



else if (FragAnimGold_time == 68)
{
m_fraganim[4]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimGold_time == 67)
{
m_fraganim[4]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}
else if (FragAnimGold_time == 66)
{
m_fraganim[4]->Bind(); //first 
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
DrawUtils::Draw2DQuadScaled(x - 45 / 2, ye - gHUD.m_iFontHeight / 1.2, x + 45 / 2, ScreenHeight / 1);
}


///helmet=========================°°°°///helmet=========================°°°°
///helmet=========================°°°°
///helmet=========================°°°°
///helmet=========================°°°°
///helmet=========================°°°°
///helmet=========================°°°°

if (Helmet_time == 100) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390); }
else if (Helmet_time == 99) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350); }
else if (Helmet_time == 98) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (Helmet_time == 97) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (Helmet_time == 96) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (Helmet_time == 95) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (Helmet_time == 94) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (Helmet_time == 93) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (Helmet_time == 92) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (Helmet_time == 91) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (Helmet_time == 90) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (Helmet_time == 89) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 88) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 87) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 86) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 85) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 84) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 83) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 82) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 81) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 80) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 79) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 78) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 77) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 76) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 75) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 74) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 73) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 72) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 71) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 70) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 69) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 68) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 67) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 66) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 65) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 64) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 63) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 62) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 61) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 60) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 59) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 58) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 57) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 56) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 55) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 54) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 53) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 52) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 51) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 50) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 49) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 48) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 47) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 46) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 45) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 44) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 43) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 42) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 41) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 40) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 39) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 38) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 37) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 36) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 35) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 34) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 33) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 32) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 31) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 30) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 29) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 28) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 27) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 26) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 25) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 24) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 23) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 22) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 21) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 20) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 19) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 18) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 17) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 16) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 15) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 14) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 13) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 12) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 11) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 10) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 9) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 8) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 7) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 6) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 5) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 4) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 3) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 2) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 1) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Helmet_time == 0) { m_helmet[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); 
isHelmet=FALSE;
}

//hotkiller====================hotkiller====================
//hotkiller====================hotkiller====================
//hotkiller====================hotkiller====================
//hotkiller====================hotkiller====================

if (HotKiller_time == 100) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390); }
else if (HotKiller_time == 99) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350); }
else if (HotKiller_time == 98) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (HotKiller_time == 97) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (HotKiller_time == 96) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (HotKiller_time == 95) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (HotKiller_time == 94) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (HotKiller_time == 93) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (HotKiller_time == 92) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (HotKiller_time == 91) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (HotKiller_time == 90) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (HotKiller_time == 89) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 88) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 87) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 86) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 85) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 84) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 83) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 82) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 81) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 80) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 79) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 78) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 77) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 76) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 75) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 74) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 73) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 72) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 71) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 70) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 69) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 68) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 67) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 66) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 65) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 64) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 63) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 62) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 61) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 60) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 59) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 58) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 57) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 56) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 55) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 54) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 53) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 52) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 51) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 50) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 49) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 48) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 47) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 46) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 45) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 44) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 43) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 42) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 41) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 40) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 39) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 38) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 37) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 36) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 35) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 34) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 33) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 32) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 31) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 30) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 29) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 28) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 27) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 26) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 25) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 24) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 23) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 22) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 21) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 20) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 19) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 18) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 17) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 16) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 15) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 14) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 13) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 12) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 11) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 10) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 9) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 8) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 7) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 6) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 5) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 4) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 3) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 2) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 1) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (HotKiller_time == 0) { m_hotkiller[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); 
isHotKiller=FALSE;
}

//SpecialGunner====================SpecialGunner====================
//SpecialGunner====================SpecialGunner====================
//SpecialGunner====================SpecialGunner====================
//SpecialGunner====================SpecialGunner====================

if (SpecialGunner_time == 100) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390); }
else if (SpecialGunner_time == 99) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350); }
else if (SpecialGunner_time == 98) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (SpecialGunner_time == 97) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (SpecialGunner_time == 96) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (SpecialGunner_time == 95) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (SpecialGunner_time == 94) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (SpecialGunner_time == 93) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (SpecialGunner_time == 92) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (SpecialGunner_time == 91) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (SpecialGunner_time == 90) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (SpecialGunner_time == 89) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 88) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 87) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 86) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 85) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 84) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 83) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 82) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 81) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 80) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 79) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 78) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 77) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 76) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 75) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 74) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 73) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 72) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 71) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 70) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 69) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 68) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 67) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 66) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 65) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 64) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 63) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 62) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 61) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 60) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 59) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 58) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 57) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 56) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 55) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 54) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 53) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 52) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 51) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 50) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 49) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 48) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 47) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 46) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 45) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 44) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 43) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 42) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 41) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 40) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 39) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 38) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 37) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 36) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 35) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 34) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 33) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 32) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 31) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 30) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 29) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 28) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 27) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 26) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 25) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 24) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 23) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 22) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 21) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 20) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 19) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 18) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 17) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 16) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 15) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 14) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 13) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 12) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 11) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 10) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 9) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 8) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 7) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 6) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 5) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 4) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 3) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 2) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 1) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (SpecialGunner_time == 0) { m_special[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); 
isSpecialGunner=FALSE;
}

//BombShot====================BombShot====================
//BombShot====================BombShot====================
//BombShot====================BombShot====================
//BombShot====================BombShot====================

if (BombShot_time == 100) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390); }
else if (BombShot_time == 99) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350); }
else if (BombShot_time == 98) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (BombShot_time == 97) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (BombShot_time == 96) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (BombShot_time == 95) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (BombShot_time == 94) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (BombShot_time == 93) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (BombShot_time == 92) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (BombShot_time == 91) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (BombShot_time == 90) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (BombShot_time == 89) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 88) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 87) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 86) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 85) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 84) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 83) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 82) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 81) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 80) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 79) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 78) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 77) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 76) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 75) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 74) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 73) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 72) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 71) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 70) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 69) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 68) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 67) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 66) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 65) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 64) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 63) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 62) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 61) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 60) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 59) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 58) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 57) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 56) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 55) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 54) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 53) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 52) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 51) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 50) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 49) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 48) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 47) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 46) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 45) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 44) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 43) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 42) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 41) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 40) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 39) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 38) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 37) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 36) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 35) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 34) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 33) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 32) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 31) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 30) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 29) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 28) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 27) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 26) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 25) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 24) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 23) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 22) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 21) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 20) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 19) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 18) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 17) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 16) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 15) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 14) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 13) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 12) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 11) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 10) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 9) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 8) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 7) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 6) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 5) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 4) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 3) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 2) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 1) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (BombShot_time == 0) { m_special[1]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); 
isBombShot=FALSE;
}

//oneShot====================oneShot====================
//oneShot====================oneShot====================
//oneShot====================oneShot====================
//oneShot====================oneShot====================

if (oneShot_time == 100) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390); }
else if (oneShot_time == 99) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350); }
else if (oneShot_time == 98) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (oneShot_time == 97) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (oneShot_time == 96) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (oneShot_time == 95) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (oneShot_time == 94) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (oneShot_time == 93) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (oneShot_time == 92) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (oneShot_time == 91) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (oneShot_time == 90) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (oneShot_time == 89) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 88) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 87) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 86) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 85) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 84) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 83) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 82) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 81) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 80) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 79) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 78) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 77) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 76) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 75) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 74) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 73) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 72) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 71) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 70) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 69) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 68) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 67) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 66) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 65) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 64) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 63) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 62) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 61) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 60) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 59) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 58) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 57) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 56) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 55) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 54) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 53) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 52) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 51) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 50) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 49) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 48) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 47) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 46) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 45) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 44) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 43) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 42) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 41) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 40) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 39) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 38) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 37) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 36) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 35) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 34) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 33) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 32) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 31) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 30) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 29) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 28) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 27) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 26) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 25) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 24) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 23) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 22) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 21) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 20) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 19) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 18) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 17) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 16) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 15) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 14) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 13) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 12) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 11) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 10) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 9) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 8) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 7) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 6) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 5) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 4) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 3) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 2) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 1) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (oneShot_time == 0) { m_special[2]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }

//Nightmare====================Nightmare====================
//Nightmare====================Nightmare====================
//Nightmare====================Nightmare====================
//Nightmare====================Nightmare====================

if (Nightmare_time == 100) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390); }
else if (Nightmare_time == 99) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350); }
else if (Nightmare_time == 98) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (Nightmare_time == 97) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (Nightmare_time == 96) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (Nightmare_time == 95) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (Nightmare_time == 94) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (Nightmare_time == 93) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (Nightmare_time == 92) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (Nightmare_time == 91) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (Nightmare_time == 90) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (Nightmare_time == 89) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 88) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 87) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 86) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 85) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 84) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 83) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 82) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 81) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 80) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 79) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 78) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 77) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 76) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 75) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 74) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 73) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 72) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 71) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 70) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 69) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 68) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 67) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 66) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 65) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 64) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 63) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 62) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 61) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 60) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 59) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 58) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 57) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 56) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 55) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 54) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 53) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 52) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 51) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 50) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 49) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 48) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 47) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 46) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 45) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 44) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 43) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 42) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 41) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 40) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 39) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 38) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 37) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 36) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 35) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 34) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 33) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 32) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 31) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 30) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 29) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 28) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 27) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 26) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 25) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 24) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 23) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 22) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 21) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 20) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 19) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 18) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 17) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 16) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 15) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 14) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 13) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 12) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 11) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 10) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 9) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 8) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 7) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 6) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 5) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 4) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 3) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 2) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 1) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Nightmare_time == 0) { m_nightmare[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); 
isNightmare=FALSE;
}

//piercing====================piercing====================
//piercing====================piercing====================
//piercing====================piercing====================
//piercing====================piercing====================

if (PiercingShot_time == 100) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390); }
else if (PiercingShot_time == 99) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350); }
else if (PiercingShot_time == 98) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (PiercingShot_time == 97) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (PiercingShot_time == 96) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (PiercingShot_time == 95) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (PiercingShot_time == 94) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (PiercingShot_time == 93) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (PiercingShot_time == 92) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (PiercingShot_time == 91) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (PiercingShot_time == 90) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (PiercingShot_time == 89) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 88) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 87) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 86) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 85) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 84) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 83) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 82) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 81) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 80) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 79) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 78) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 77) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 76) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 75) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 74) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 73) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 72) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 71) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 70) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 69) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 68) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 67) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 66) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 65) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 64) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 63) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 62) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 61) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 60) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 59) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 58) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 57) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 56) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 55) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 54) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 53) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 52) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 51) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 50) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 49) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 48) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 47) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 46) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 45) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 44) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 43) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 42) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 41) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 40) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 39) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 38) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 37) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 36) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 35) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 34) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 33) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 32) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 31) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 30) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 29) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 28) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 27) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 26) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 25) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 24) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 23) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 22) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 21) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 20) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 19) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 18) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 17) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 16) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 15) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 14) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 13) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 12) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 11) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 10) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 9) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 8) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 7) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 6) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 5) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 4) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 3) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 2) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 1) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (PiercingShot_time == 0) { m_piercing[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); 
isPiercingShot=FALSE;
}

//mass====================mass====================
//mass====================mass====================
//mass====================mass====================
//mass====================mass====================

if (MassKill_time == 100) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390); }
else if (MassKill_time == 99) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350); }
else if (MassKill_time == 98) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (MassKill_time == 97) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (MassKill_time == 96) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (MassKill_time == 95) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (MassKill_time == 94) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (MassKill_time == 93) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (MassKill_time == 92) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (MassKill_time == 91) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (MassKill_time == 90) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (MassKill_time == 89) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 88) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 87) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 86) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 85) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 84) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 83) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 82) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 81) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 80) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 79) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 78) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 77) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 76) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 75) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 74) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 73) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 72) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 71) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 70) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 69) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 68) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 67) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 66) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 65) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 64) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 63) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 62) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 61) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 60) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 59) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 58) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 57) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 56) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 55) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 54) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 53) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 52) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 51) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 50) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 49) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 48) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 47) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 46) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 45) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 44) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 43) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 42) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 41) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 40) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 39) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 38) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 37) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 36) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 35) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 34) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 33) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 32) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 31) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 30) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 29) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 28) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 27) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 26) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 25) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 24) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 23) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 22) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 21) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 20) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 19) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 18) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 17) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 16) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 15) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 14) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 13) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 12) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 11) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 10) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 9) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 8) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 7) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 6) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 5) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 4) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 3) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 2) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 1) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MassKill_time == 0) { m_mass[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); 
isMassKill=FALSE;
}

//chslugger====================chslugger====================
//chslugger====================chslugger====================
//chslugger====================chslugger====================
//chslugger====================chslugger====================

if (Slugger_time == 100) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390);}
else if (Slugger_time == 99) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350);
 }
else if (Slugger_time == 98) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (Slugger_time == 97) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (Slugger_time == 96) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (Slugger_time == 95) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (Slugger_time == 94) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (Slugger_time == 93) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (Slugger_time == 92) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (Slugger_time == 91) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (Slugger_time == 90) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (Slugger_time == 89) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 88) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 87) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 86) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 85) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 84) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 83) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 82) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 81) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 80) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 79) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 78) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 77) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 76) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 75) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 74) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 73) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 72) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 71) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 70) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 69) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 68) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 67) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 66) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 65) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 64) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 63) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 62) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 61) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 60) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 59) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 58) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 57) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 56) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 55) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 54) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 53) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 52) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 51) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 50) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 49) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 48) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 47) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 46) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 45) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 44) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 43) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 42) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 41) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 40) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 39) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 38) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 37) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 36) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 35) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 34) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 33) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 32) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 31) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 30) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 29) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 28) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 27) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 26) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 25) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 24) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 23) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 22) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 21) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 20) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 19) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 18) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 17) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 16) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 15) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 14) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 13) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 12) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 11) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 10) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 9) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 8) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 7) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 6) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 5) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 4) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 3) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 2) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 1) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Slugger_time == 0) { m_chslugger[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); 
isSlugger=FALSE;
}

UpdateStars();

if (gHUD.piercing_shot == TRUE) //disable for mass_kill
return 0;

//mission
if (MissionComplete_time == 100) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390); 
}
else if (MissionComplete_time == 99) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350); }
else if (MissionComplete_time == 98) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (MissionComplete_time == 97) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (MissionComplete_time == 96) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (MissionComplete_time == 95) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (MissionComplete_time == 94) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (MissionComplete_time == 93) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (MissionComplete_time == 92) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (MissionComplete_time == 91) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (MissionComplete_time == 90) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (MissionComplete_time == 89) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 88) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 87) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 86) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 85) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 84) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 83) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 82) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 81) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 80) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 79) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 78) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 77) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 76) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 75) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 74) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 73) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 72) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 71) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 70) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 69) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 68) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 67) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 66) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 65) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 64) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 63) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 62) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 61) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 60) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 59) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 58) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 57) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 56) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 55) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 54) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 53) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 52) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 51) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 50) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 49) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 48) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 47) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 46) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 45) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 44) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 43) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 42) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 41) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 40) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 39) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 38) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 37) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 36) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 35) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 34) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 33) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 32) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 31) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 30) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 29) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 28) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 27) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 26) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 25) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 24) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 23) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 22) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 21) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 20) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 19) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 18) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 17) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 16) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 15) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 14) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 13) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 12) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 11) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 10) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 9) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 8) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 7) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 6) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 5) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 4) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 3) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 2) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 1) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (MissionComplete_time == 0) { m_MissionComplete->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }


////kill2===============kill2 =======================///
////kill2===============kill2 =======================///
////kill2===============kill2 =======================///
////kill#===============kill2 =======================///
//1st y + down last y - up
if (Doublekill_time == 100) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390); 
}
else if (Doublekill_time == 99) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350); }
else if (Doublekill_time == 98) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (Doublekill_time == 97) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (Doublekill_time == 96) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (Doublekill_time == 95) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (Doublekill_time == 94) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (Doublekill_time == 93) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (Doublekill_time == 92) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (Doublekill_time == 91) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (Doublekill_time == 90) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (Doublekill_time == 89) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 88) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 87) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 86) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 85) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 84) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 83) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 82) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 81) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 80) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 79) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 78) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 77) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 76) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 75) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 74) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 73) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 72) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 71) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 70) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 69) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 68) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 67) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 66) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 65) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 64) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 63) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 62) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 61) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 60) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 59) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 58) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 57) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 56) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 55) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 54) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 53) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 52) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 51) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 50) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 49) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 48) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 47) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 46) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 45) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 44) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 43) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 42) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 41) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 40) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 39) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 38) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 37) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 36) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 35) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 34) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 33) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 32) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 31) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 30) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 29) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 28) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 27) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 26) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 25) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 24) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 23) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 22) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 21) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 20) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 19) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 18) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 17) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 16) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 15) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 14) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 13) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 12) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 11) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 10) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 9) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 8) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 7) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 6) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 5) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 4) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 3) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 2) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 1) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Doublekill_time == 0) { m_kill2[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); 
isDoublekill=FALSE;
}



////kill3===============kill3 =======================///
////kill3===============kill3 =======================///
////kill3===============kill3 =======================///
////kill#===============kill3 =======================///

if (Triplekill_time == 100) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390); }
else if (Triplekill_time == 99) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350); }
else if (Triplekill_time == 98) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (Triplekill_time == 97) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (Triplekill_time == 96) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (Triplekill_time == 95) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (Triplekill_time == 94) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (Triplekill_time == 93) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (Triplekill_time == 92) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (Triplekill_time == 91) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (Triplekill_time == 90) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (Triplekill_time == 89) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 88) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 87) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 86) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 85) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 84) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 83) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 82) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 81) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 80) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 79) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 78) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 77) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 76) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 75) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 74) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 73) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 72) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 71) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 70) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 69) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 68) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 67) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 66) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 65) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 64) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 63) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 62) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 61) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 60) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 59) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 58) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 57) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 56) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 55) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 54) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 53) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 52) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 51) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 50) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 49) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 48) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 47) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 46) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 45) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 44) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 43) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 42) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 41) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 40) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 39) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 38) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 37) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 36) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 35) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 34) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 33) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 32) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 31) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 30) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 29) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 28) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 27) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 26) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 25) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 24) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 23) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 22) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 21) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 20) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 19) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 18) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 17) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 16) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 15) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 14) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 13) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 12) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 11) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 10) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 9) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 8) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 7) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 6) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 5) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 4) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 3) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 2) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 1) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Triplekill_time == 0) { m_kill3[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300);
isTriplekill=FALSE;
}


////kill4===============kill4 =======================///
////kill4===============kill4 =======================///
////kill4===============kill4 =======================///
////kill4===============kill4 =======================///

if (Chainkiller_time == 100) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390); }
else if (Chainkiller_time == 99) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350); }
else if (Chainkiller_time == 98) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (Chainkiller_time == 97) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (Chainkiller_time == 96) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (Chainkiller_time == 95) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (Chainkiller_time == 94) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (Chainkiller_time == 93) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (Chainkiller_time == 92) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (Chainkiller_time == 91) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (Chainkiller_time == 90) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (Chainkiller_time == 89) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 88) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 87) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 86) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 85) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 84) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 83) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 82) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 81) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 80) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 79) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 78) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 77) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 76) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 75) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 74) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 73) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 72) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 71) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 70) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 69) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 68) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 67) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 66) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 65) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 64) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 63) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 62) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 61) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 60) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 59) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 58) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 57) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 56) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 55) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 54) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 53) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 52) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 51) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 50) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 49) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 48) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 47) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 46) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 45) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 44) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 43) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 42) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 41) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 40) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 39) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 38) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 37) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 36) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 35) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 34) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 33) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 32) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 31) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 30) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 29) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 28) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 27) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 26) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 25) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 24) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 23) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 22) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 21) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 20) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 19) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 18) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 17) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 16) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 15) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 14) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 13) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 12) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 11) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 10) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 9) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 8) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 7) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 6) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 5) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 4) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 3) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 2) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 1) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Chainkiller_time == 0) { m_kill4[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); 
isChainkiller=FALSE;
}


////headshot==============headshot =======================///
////headshot=============headshot =======================///
////headshot=============headshot =======================///
////headshot=============headshot =======================///

if (Headshot_time == 100) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390); }
else if (Headshot_time == 99) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350); }
else if (Headshot_time == 98) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (Headshot_time == 97) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (Headshot_time == 96) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (Headshot_time == 95) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (Headshot_time == 94) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (Headshot_time == 93) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (Headshot_time == 92) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (Headshot_time == 91) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (Headshot_time == 90) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (Headshot_time == 89) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 88) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 87) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 86) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 85) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 84) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 83) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 82) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 81) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 80) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 79) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 78) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 77) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 76) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 75) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 74) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 73) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 72) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 71) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 70) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 69) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 68) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 67) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 66) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 65) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 64) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 63) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 62) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 61) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 60) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 59) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 58) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 57) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 56) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 55) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 54) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 53) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 52) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 51) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 50) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 49) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 48) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 47) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 46) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 45) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 44) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 43) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 42) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 41) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 40) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 39) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 38) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 37) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 36) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 35) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 34) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 33) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 32) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 31) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 30) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 29) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 28) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 27) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 26) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 25) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 24) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 23) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 22) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 21) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 20) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 19) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 18) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 17) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 16) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 15) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 14) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 13) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 12) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 11) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 10) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 9) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 8) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 7) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 6) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 5) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 4) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 3) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 2) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 1) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Headshot_time == 0) { m_headshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); 
isHeadshot=FALSE;
}

////ChainHeadshot======ChainHeadshot =================///
////ChainHeadshot======ChainHeadshot ================///
////ChainHeadshot======ChainHeadshot ===============///
////ChainHeadshot======ChainHeadshot ======m===========///

if (ChainHeadshot_time == 100) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390); }
else if (ChainHeadshot_time == 99) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350); }
else if (ChainHeadshot_time == 98) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (ChainHeadshot_time == 97) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (ChainHeadshot_time == 96) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (ChainHeadshot_time == 95) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (ChainHeadshot_time == 94) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (ChainHeadshot_time == 93) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (ChainHeadshot_time == 92) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (ChainHeadshot_time == 91) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (ChainHeadshot_time == 90) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (ChainHeadshot_time == 89) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 88) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 87) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 86) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 85) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 84) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 83) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 82) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 81) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 80) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 79) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 78) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 77) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 76) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 75) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 74) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 73) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 72) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 71) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 70) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 69) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 68) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 67) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 66) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 65) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 64) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 63) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 62) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 61) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 60) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 59) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 58) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 57) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 56) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 55) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 54) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 53) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 52) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 51) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 50) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 49) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 48) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 47) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 46) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 45) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 44) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 43) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 42) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 41) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 40) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 39) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 38) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 37) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 36) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 35) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 34) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 33) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 32) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 31) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 30) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 29) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 28) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 27) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 26) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 25) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 24) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 23) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 22) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 21) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 20) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 19) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 18) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 17) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 16) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 15) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 14) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 13) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 12) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 11) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 10) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 9) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 8) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 7) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 6) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 5) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 4) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 3) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 2) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 1) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (ChainHeadshot_time == 0) { m_chheadshot[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); 
isChainHeadshot=FALSE;
}


///Stopper=========================°°°°///Stopper=========================°°°°
///Stopper=========================°°°°
///Stopper=========================°°°°
///Stopper=========================°°°°
///Stopper=========================°°°°
///Stopper=========================°°°°

if (Stopper_time == 100) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 2000 / 2, y+ 130, x + 2000 / 2, y + 390); }
else if (Stopper_time == 99) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1850 / 2, y+ 135, x + 1850 / 2, y + 350); }
else if (Stopper_time == 98) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 1750 / 2, y+ 140, x + 1750 / 2, y + 345); }
else if (Stopper_time == 97) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1650 / 2, y+ 145, x + 1650 / 2, y + 335); }
else if (Stopper_time == 96) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1500 / 2, y+ 150, x + 1500 / 2, y + 330); }
else if (Stopper_time == 95) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1300 / 2, y+ 155, x + 1300 / 2, y + 325); }
else if (Stopper_time == 94) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 1000 / 2, y+ 160, x + 1000 / 2, y + 320); }
else if (Stopper_time == 93) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 800 / 2, y+ 170, x + 800 / 2, y + 315); }
else if (Stopper_time == 92) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 750 / 2, y+ 185, x + 750 / 2, y + 310); }
else if (Stopper_time == 91) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 700 / 2, y+ 180, x + 700 / 2, y + 307); }
else if (Stopper_time == 90) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 650 / 2, y+ 195, x + 650 / 2, y + 305); }
else if (Stopper_time == 89) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 88) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 87) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 86) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 85) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 84) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 83) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 82) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 81) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 80) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 79) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 78) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 77) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 76) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 75) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 74) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 73) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 72) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 71) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 70) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 69) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 68) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 67) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 66) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 65) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 64) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 63) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 62) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 61) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 60) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 59) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 58) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 57) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 56) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 55) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 54) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 53) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 52) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 51) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 50) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 49) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 48) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 47) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 46) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 45) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 44) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 43) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 42) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 41) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 40) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 39) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 38) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 37) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 36) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 35) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 34) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 33) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 32) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 31) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 30) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 29) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 28) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 27) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 26) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 25) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 24) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 23) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 22) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 21) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 20) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 19) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 18) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 17) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 16) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 15) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 14) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 13) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 12) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 11) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 10) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 9) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 200); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 8) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 130); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 7) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 6) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 100); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 5) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 80); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 4) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 60); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 3) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 45); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 2) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 20); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 1) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 10); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); }
else if (Stopper_time == 0) { m_stopper[0]->Bind(); gEngfuncs.pTriAPI->RenderMode(kRenderTransColor); gEngfuncs.pTriAPI->Brightness(1.0); gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0); DrawUtils::Draw2DQuadScaled(x - 500 / 2, y+ 200, x + 500 / 2, y + 300); 
isStopper=FALSE;
}

	return 0;

}


void CHudKillEffect::UpdateStars()
{
KillStar1_time -= 1;
KillStar2_time -= 1;
KillStar3_time -= 1;
KillStar4_time -= 1;
KillStar5_time -= 1;
KillStar6_time -= 1;
KillStar7_time -= 1;
KillStar8_time -= 1;
KillStar9_time -= 1;
KillStar10_time -= 1;

HeadshotStar1_time -= 1;
HeadshotStar2_time -= 1;
HeadshotStar3_time -= 1;
HeadshotStar4_time -= 1;
HeadshotStar5_time -= 1;
HeadshotStar6_time -= 1;
HeadshotStar7_time -= 1;
HeadshotStar8_time -= 1;
HeadshotStar9_time -= 1;
HeadshotStar10_time -= 1;

BlueStar5_time -= 1;
GoldStar10_time -= 1;

StopperStar1_time -= 1;
StopperStar2_time -= 1;
StopperStar3_time -= 1;
StopperStar4_time -= 1;
StopperStar5_time -= 1;
StopperStar6_time -= 1;
StopperStar7_time -= 1;
StopperStar8_time -= 1;
StopperStar9_time -= 1;
StopperStar10_time -= 1;

StopperHsStar1_time -= 1;
StopperHsStar2_time -= 1;
StopperHsStar3_time -= 1;
StopperHsStar4_time -= 1;
StopperHsStar5_time -= 1;
StopperHsStar6_time -= 1;
StopperHsStar7_time -= 1;
StopperHsStar8_time -= 1;
StopperHsStar9_time -= 1;
StopperHsStar10_time -= 1;

SluggerStar1_time -= 1;
SluggerStar2_time -= 1;
SluggerStar3_time -= 1;
SluggerStar4_time -= 1;
SluggerStar5_time -= 1;
SluggerStar6_time -= 1;
SluggerStar7_time -= 1;
SluggerStar8_time -= 1;
SluggerStar9_time -= 1;
SluggerStar10_time -= 1;

SluggerHsStar1_time -= 1;
SluggerHsStar2_time -= 1;
SluggerHsStar3_time -= 1;
SluggerHsStar4_time -= 1;
SluggerHsStar5_time -= 1;
SluggerHsStar6_time -= 1;
SluggerHsStar7_time -= 1;
SluggerHsStar8_time -= 1;
SluggerHsStar9_time -= 1;
SluggerHsStar10_time -= 1;

if (Helmet_time == 99)
gHUD.helmet_on = FALSE;

//1
if (KillStar1_time == 0) ClientCmd("billflxstar1cmd 1");//kill1
if (HeadshotStar1_time == 0) ClientCmd("billflxstar1cmd 2");//hs
if (StopperStar1_time == 0) ClientCmd("billflxstar1cmd 3");//stopper
if (SluggerStar1_time == 0) ClientCmd("billflxstar1cmd 6");//slugger 

//2
if (KillStar2_time == 0) ClientCmd("billflxstar2cmd 1");
if (HeadshotStar2_time == 0) ClientCmd("billflxstar2cmd 2");
if (StopperStar2_time == 0) ClientCmd("billflxstar2cmd 3");//stopper
if (SluggerStar2_time == 0) ClientCmd("billflxstar2cmd 6");//slugger 

//3
if (KillStar3_time == 0) ClientCmd("billflxstar3cmd 1");
if (HeadshotStar3_time == 0) ClientCmd("billflxstar3cmd 2");
if (StopperStar3_time == 0) ClientCmd("billflxstar3cmd 3");//stopper
if (SluggerStar3_time == 0) ClientCmd("billflxstar3cmd 6");//slugger 

//4
if (KillStar4_time == 0) ClientCmd("billflxstar4cmd 1");
if (HeadshotStar4_time == 0) ClientCmd("billflxstar4cmd 2");
if (StopperStar4_time == 0) ClientCmd("billflxstar4cmd 3");//stopper
if (SluggerStar4_time == 0) ClientCmd("billflxstar4cmd 6");//slugger 

//5
if (KillStar5_time == 0) ClientCmd("billflxstar5cmd 1");
if (HeadshotStar5_time == 0) ClientCmd("billflxstar5cmd 2");
if (StopperStar5_time == 0) ClientCmd("billflxstar5cmd 3");//stopper
if (SluggerStar5_time == 0) ClientCmd("billflxstar5cmd 6");//slugger 

//6
if (KillStar6_time == 0) ClientCmd("billflxstar6cmd 1");
if (HeadshotStar6_time == 0) ClientCmd("billflxstar6cmd 2");
if (StopperStar6_time == 0) ClientCmd("billflxstar6cmd 3");//stopper
if (SluggerStar6_time == 0) ClientCmd("billflxstar6cmd 6");//slugger 

//7
if (KillStar7_time == 0) ClientCmd("billflxstar7cmd 1");
if (HeadshotStar7_time == 0) ClientCmd("billflxstar7cmd 2");
if (StopperStar7_time == 0) ClientCmd("billflxstar7cmd 3");//stopper
if (SluggerStar7_time == 0) ClientCmd("billflxstar7cmd 6");//slugger 

//8
if (KillStar8_time == 0) ClientCmd("billflxstar8cmd 1");
if (HeadshotStar8_time == 0) ClientCmd("billflxstar8cmd 2");
if (StopperStar8_time == 0) ClientCmd("billflxstar8cmd 3");//stopper
if (SluggerStar8_time == 0) ClientCmd("billflxstar8cmd 6");//slugger 

//9
if (KillStar9_time == 0) ClientCmd("billflxstar9cmd 1");
if (HeadshotStar9_time == 0) ClientCmd("billflxstar9cmd 2");
if (StopperStar9_time == 0) ClientCmd("billflxstar9cmd 3");//stopper
if (SluggerStar9_time == 0) ClientCmd("billflxstar9cmd 6");//slugger 

//10
if (KillStar10_time == 0) ClientCmd("billflxstar10cmd 1");
if (HeadshotStar10_time == 0) ClientCmd("billflxstar10cmd 2");
if (StopperStar10_time == 0) ClientCmd("billflxstar10cmd 3");//stopper
if (SluggerStar10_time == 0) ClientCmd("billflxstar10cmd 6");//slugger 

if (BlueStar5_time == 0) ClientCmd("billflxstar5cmd 4");//interval 5 blue
//if (BlueStar5_time30 == 0) ClientCmd("billflxstar10cmd 4");//interval 10 blue

if (GoldStar10_time == 0) ClientCmd("billflxstar5cmd 5");//interval 15 gold
//if (KillStar1_time29 == 0) ClientCmd("billflxstar10cmd 5");//interval 20 gold

if (Pos1_time == 0) ClientCmd("starpos 0"); //pos1
if (Pos2_time == 0) ClientCmd("starpos 1"); //pos2

/*
if (KillStar1_time23 == 0) ClientCmd("billflxstar3cmd 4");
if (KillStar1_time24 == 0) ClientCmd("billflxstar4cmd 4");

if (KillStar1_time26 == 0) ClientCmd("billflxstar6cmd 4");
if (KillStar1_time27 == 0) ClientCmd("billflxstar7cmd 4");
if (KillStar1_time29 == 0) ClientCmd("billflxstar9cmd 4");


if (KillStar1_time31 == 0) ClientCmd("billflxstar9cmd 1");


*/
}
