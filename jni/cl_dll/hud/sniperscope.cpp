/*
hud_overlays.cpp - HUD Overlays
Copyright (C) 2015-2016 a1batross

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

In addition, as a special exception, the author gives permission to
link the code of this program with the Half-Life Game Engine ("HL
Engine") and Modified Game Libraries ("MODs") developed by Valve,
L.L.C ("Valve").  You must obey the GNU General Public License in all
respects for all of the code used other than the HL Engine and MODs
from Valve.  If you modify this file, you may extend this exception
to your version of the file, but you are not obligated to do so.  If
you do not wish to do so, delete this exception statement from your
version.

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


//#include "const/const_client.h"
#include "triangleapi.h"

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
	WEAPON_SHIELDGUN = 99
};

DECLARE_MESSAGE(m_SniperScope, Reddot_Scope);
DECLARE_COMMAND(m_SniperScope, CommandActiveReddot);

DECLARE_MESSAGE(m_SniperScope, Eotech_Scope);
DECLARE_COMMAND(m_SniperScope, CommandActiveEotech);

DECLARE_MESSAGE(m_SniperScope, Acog_Scope);
DECLARE_COMMAND(m_SniperScope, CommandActiveAcog);

DECLARE_MESSAGE(m_SniperScope, Dot_l_Scope);
DECLARE_COMMAND(m_SniperScope, CommandActiveDot_l);

DECLARE_MESSAGE(m_SniperScope, Telescopic_Scope);
DECLARE_COMMAND(m_SniperScope, CommandActiveTelescopic);

DECLARE_MESSAGE(m_SniperScope, EotechCrb_Scope);
DECLARE_COMMAND(m_SniperScope, CommandActiveEotechCrb);

DECLARE_MESSAGE(m_SniperScope, EotechPandora_Scope);
DECLARE_COMMAND(m_SniperScope, CommandActiveEotechPandora);

DECLARE_MESSAGE(m_SniperScope, Sks_Scope);
DECLARE_COMMAND(m_SniperScope, CommandActiveSksScope);

DECLARE_MESSAGE(m_SniperScope, Sniper_Scope);
DECLARE_COMMAND(m_SniperScope, CommandActiveSniperScope);

DECLARE_MESSAGE(m_SniperScope, Azure_Scope);
DECLARE_COMMAND(m_SniperScope, CommandActiveAzureScope);

DECLARE_MESSAGE(m_SniperScope, EotechDot_Scope);
DECLARE_COMMAND(m_SniperScope, CommandActiveEotechDot);

DECLARE_MESSAGE(m_SniperScope, Disable_Scope);
DECLARE_COMMAND(m_SniperScope, CommandActiveDisableScope);

DECLARE_MESSAGE(m_SniperScope, Custom_Scope);
DECLARE_COMMAND(m_SniperScope, CommandActiveCustomScope);


void CHudSniperScope::UserCmd_CommandActiveCustomScope(void)
{
active_Reddot = FALSE; 
active_Eotech = FALSE;
active_Acog = FALSE;
active_Dot_l = FALSE;
active_Telescopic = FALSE;
active_EotechCrb = FALSE;
active_EotechPandora = FALSE;
active_SksScope = FALSE;
active_SniperScope = FALSE;
active_AzureScope = FALSE;
active_EotechDot = FALSE;
active_CustomSight = TRUE; 
}


void CHudSniperScope::UserCmd_CommandActiveDisableScope(void)
{
gHUD.disable_scope = TRUE;

active_Reddot = FALSE; 
active_Eotech = FALSE;
active_Acog = FALSE;
active_Dot_l = FALSE;
active_Telescopic = FALSE;
active_EotechCrb = FALSE;
active_EotechPandora = FALSE;
active_SksScope = FALSE;
active_SniperScope = FALSE;
active_AzureScope = FALSE;
active_EotechDot = FALSE;
active_CustomSight = FALSE; 
}

void CHudSniperScope::UserCmd_CommandActiveReddot(void)
{
gHUD.reddot_scope = TRUE;
active_Reddot = true;
active_Eotech= false;
active_Acog= false;
active_Dot_l= false;
active_Telescopic= false;
active_EotechCrb= false;
active_EotechPandora= false;
active_SksScope= false;
active_SniperScope= false;
active_AzureScope= false;
active_EotechDot= false;
active_CustomSight = false; 
}

void CHudSniperScope::UserCmd_CommandActiveEotech(void)
{
active_Eotech = true;
active_Reddot= false; 
active_Acog= false;
active_Dot_l= false;
active_Telescopic= false;
active_EotechCrb= false;
active_EotechPandora= false;
active_SksScope= false;
active_SniperScope= false;
active_AzureScope= false;
active_EotechDot= false;
active_CustomSight = false; 
}

void CHudSniperScope::UserCmd_CommandActiveAcog(void)
{
active_Acog = true;
active_Reddot= false; 
active_Eotech= false;
active_Dot_l= false;
active_Telescopic= false;
active_EotechCrb= false;
active_EotechPandora= false;
active_SksScope= false;
active_SniperScope= false;
active_AzureScope= false;
active_EotechDot= false;
active_CustomSight = false; 
}

void CHudSniperScope::UserCmd_CommandActiveDot_l(void)
{
gHUD.reddot_scope = TRUE;
active_Dot_l = true;
active_Reddot= false; 
active_Eotech= false;
active_Acog= false;
active_Telescopic= false;
active_EotechCrb= false;
active_EotechPandora= false;
active_SksScope= false;
active_SniperScope= false;
active_AzureScope= false;
active_EotechDot= false;
active_CustomSight = false; 
}

void CHudSniperScope::UserCmd_CommandActiveTelescopic(void)
{
active_Telescopic = true;
active_Reddot= false; 
active_Eotech= false;
active_Acog= false;
active_Dot_l= false;
active_EotechCrb= false;
active_EotechPandora= false;
active_SksScope= false;
active_SniperScope= false;
active_AzureScope= false;
active_EotechDot= false;
active_CustomSight = false; 
}

void CHudSniperScope::UserCmd_CommandActiveEotechCrb(void)
{
active_EotechCrb = true;
active_Reddot= false; 
active_Eotech= false;
active_Acog= false;
active_Dot_l= false;
active_Telescopic= false;
active_EotechPandora= false;
active_SksScope= false;
active_SniperScope= false;
active_AzureScope= false;
active_EotechDot= false;
active_CustomSight = false; 
}

void CHudSniperScope::UserCmd_CommandActiveEotechPandora(void)
{
active_EotechPandora = true;
active_Reddot= false; 
active_Eotech= false;
active_Acog= false;
active_Dot_l= false;
active_Telescopic= false;
active_EotechCrb= false;
active_SksScope= false;
active_SniperScope= false;
active_AzureScope= false;
active_EotechDot= false;
active_CustomSight = false; 
}

void CHudSniperScope::UserCmd_CommandActiveSksScope(void)
{
active_SksScope = true;
active_Reddot= false; 
active_Eotech= false;
active_Acog= false;
active_Dot_l= false;
active_Telescopic= false;
active_EotechCrb= false;
active_EotechPandora= false;
active_SniperScope= false;
active_AzureScope= false;
active_EotechDot= false;
active_CustomSight = false; 
}

void CHudSniperScope::UserCmd_CommandActiveSniperScope(void)
{
active_SniperScope = true;
active_Reddot= false; 
active_Eotech= false;
active_Acog= false;
active_Dot_l= false;
active_Telescopic= false;
active_EotechCrb= false;
active_EotechPandora= false;
active_SksScope= false;
active_AzureScope= false;
active_EotechDot= false;
active_CustomSight = false; 
}

void CHudSniperScope::UserCmd_CommandActiveAzureScope(void)
{
active_AzureScope = true;
active_Reddot= false; 
active_Eotech= false;
active_Acog= false;
active_Dot_l= false;
active_Telescopic= false;
active_EotechCrb= false;
active_EotechPandora= false;
active_SksScope= false;
active_SniperScope= false;
active_EotechDot= false;
active_CustomSight = false; 
}

void CHudSniperScope::UserCmd_CommandActiveEotechDot(void)
{
gHUD.reddot_scope = TRUE;
active_EotechDot = true;
active_Reddot= false; 
active_Eotech= false;
active_Acog= false;
active_Dot_l= false;
active_Telescopic= false;
active_EotechCrb= false;
active_EotechPandora= false;
active_SksScope= false;
active_SniperScope= false;
active_AzureScope= false;
active_CustomSight = false; 
}


int CHudSniperScope::MsgFunc_Disable_Scope(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	return 1;
}

int CHudSniperScope::MsgFunc_Reddot_Scope(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	return 1;
}
int CHudSniperScope::MsgFunc_Eotech_Scope(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	return 1;
}
int CHudSniperScope::MsgFunc_Acog_Scope(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	return 1;
}
int CHudSniperScope::MsgFunc_Dot_l_Scope(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	return 1;
}
int CHudSniperScope::MsgFunc_Telescopic_Scope(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	return 1;
}
int CHudSniperScope::MsgFunc_EotechCrb_Scope(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	return 1;
}
int CHudSniperScope::MsgFunc_EotechPandora_Scope(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	return 1;
}
int CHudSniperScope::MsgFunc_Sks_Scope(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	return 1;
}
int CHudSniperScope::MsgFunc_Sniper_Scope(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	return 1;
}
int CHudSniperScope::MsgFunc_Azure_Scope(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	return 1;
}
int CHudSniperScope::MsgFunc_EotechDot_Scope(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	return 1;
}
int CHudSniperScope::MsgFunc_Custom_Scope(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	return 1;
}


int CHudSniperScope::Init()
{
	gHUD.AddHudElem(this);
	m_iFlags = HUD_DRAW;

HOOK_MESSAGE(Reddot_Scope);
HOOK_COMMAND("Reddot_Scope", CommandActiveReddot);

HOOK_MESSAGE(Eotech_Scope);
HOOK_COMMAND("Eotech_Scope", CommandActiveEotech);

HOOK_MESSAGE(Acog_Scope);
HOOK_COMMAND("Acog_Scope", CommandActiveAcog);

HOOK_MESSAGE(Dot_l_Scope);
HOOK_COMMAND("Dot_l_Scope", CommandActiveDot_l);

HOOK_MESSAGE(Telescopic_Scope);
HOOK_COMMAND("Telescopic_Scope", CommandActiveTelescopic);

HOOK_MESSAGE(EotechCrb_Scope);
HOOK_COMMAND("EotechCrb_Scope", CommandActiveEotechCrb);

HOOK_MESSAGE(EotechPandora_Scope);
HOOK_COMMAND("EotechPandora_Scope", CommandActiveEotechPandora);

HOOK_MESSAGE(Sks_Scope);
HOOK_COMMAND("Sks_Scope", CommandActiveSksScope);

HOOK_MESSAGE(Sniper_Scope);
HOOK_COMMAND("Sniper_Scope", CommandActiveSniperScope);

HOOK_MESSAGE(Azure_Scope);
HOOK_COMMAND("Azure_Scope", CommandActiveAzureScope);

HOOK_MESSAGE(EotechDot_Scope);
HOOK_COMMAND("EotechDot_Scope", CommandActiveEotechDot);

HOOK_MESSAGE(Disable_Scope);
HOOK_COMMAND("Disable_Scope", CommandActiveDisableScope);

HOOK_MESSAGE(Custom_Scope);
HOOK_COMMAND("Custom_Scope", CommandActiveCustomScope);
	return 1;
}

int CHudSniperScope::VidInit()
{
R_InitTexture(m_sight[0], "gfx/sight/reddot.tga");
R_InitTexture(m_sight[1], "gfx/sight/eotech.tga");
R_InitTexture(m_sight[2], "gfx/sight/eotech_dot.tga");
R_InitTexture(m_sight[3], "gfx/sight/acog.tga");
R_InitTexture(m_sight[4], "gfx/sight/dot_l.tga");
R_InitTexture(m_sight[5], "gfx/sight/telescopic.tga");
R_InitTexture(m_sight[6], "gfx/sight/eotechcrb.tga");
R_InitTexture(m_sight[7], "gfx/sight/eotechpandora.tga");
R_InitTexture(m_sight[8], "gfx/sight/sksscope.tga");
R_InitTexture(m_sight[9], "gfx/sight/sniper.tga");
R_InitTexture(m_sight[10], "gfx/sight/dot_l2.tga");
R_InitTexture(m_sight[11], "gfx/sight/azure.tga");

R_InitTexture(m_sight[12], "materials/pb/hud/bombicon/bombicon.tga");

R_InitTexture(m_CustomSight[0], "gfx/sight/custom/custom1.tga");
R_InitTexture(m_CustomSight[1], "gfx/sight/custom/custom1.tga");
R_InitTexture(m_CustomSight[2], "gfx/sight/custom/custom2.tga");
R_InitTexture(m_CustomSight[3], "gfx/sight/custom/custom3.tga");
R_InitTexture(m_CustomSight[4], "gfx/sight/custom/custom4.tga");
R_InitTexture(m_CustomSight[5], "gfx/sight/custom/custom5.tga");
R_InitTexture(m_CustomSight[6], "gfx/sight/custom/custom6.tga");
R_InitTexture(m_CustomSight[7], "gfx/sight/custom/custom7.tga");
R_InitTexture(m_CustomSight[8], "gfx/sight/custom/custom8.tga");
R_InitTexture(m_CustomSight[9], "gfx/sight/custom/custom9.tga");
R_InitTexture(m_CustomSight[10], "gfx/sight/custom/custom10.tga");
R_InitTexture(m_CustomSight[11], "gfx/sight/custom/custom11.tga");
R_InitTexture(m_CustomSight[12], "gfx/sight/custom/custom12.tga");
R_InitTexture(m_CustomSight[13], "gfx/sight/custom/custom13.tga");
R_InitTexture(m_CustomSight[14], "gfx/sight/custom/custom14.tga");
R_InitTexture(m_CustomSight[15], "gfx/sight/custom/custom15.tga");
R_InitTexture(m_CustomSight[16], "gfx/sight/custom/custom16.tga");
R_InitTexture(m_CustomSight[17], "gfx/sight/custom/custom17.tga");
R_InitTexture(m_CustomSight[18], "gfx/sight/custom/custom18.tga");
R_InitTexture(m_CustomSight[19], "gfx/sight/custom/custom19.tga");
R_InitTexture(m_CustomSight[20], "gfx/sight/custom/custom20.tga");
R_InitTexture(m_CustomSight[21], "gfx/sight/custom/custom21.tga");
R_InitTexture(m_CustomSight[22], "gfx/sight/custom/custom22.tga");
R_InitTexture(m_CustomSight[23], "gfx/sight/custom/custom23.tga");
R_InitTexture(m_CustomSight[24], "gfx/sight/custom/custom24.tga");
R_InitTexture(m_CustomSight[25], "gfx/sight/custom/custom25.tga");//170 sidebar
R_InitTexture(m_CustomSight[26], "gfx/sight/custom/custom26.tga");
R_InitTexture(m_CustomSight[27], "gfx/sight/custom/custom27.tga");
R_InitTexture(m_CustomSight[28], "gfx/sight/custom/custom28.tga");
R_InitTexture(m_CustomSight[29], "gfx/sight/custom/custom29.tga");
R_InitTexture(m_CustomSight[30], "gfx/sight/custom/custom30.tga");
R_InitTexture(m_CustomSight[31], "gfx/sight/custom/custom31.tga");
R_InitTexture(m_CustomSight[32], "gfx/sight/custom/custom32.tga");
R_InitTexture(m_CustomSight[33], "gfx/sight/custom/custom33.tga");
R_InitTexture(m_CustomSight[34], "gfx/sight/custom/custom34.tga");
R_InitTexture(m_CustomSight[35], "gfx/sight/custom/custom35.tga");
R_InitTexture(m_CustomSight[36], "gfx/sight/custom/custom36.tga");
R_InitTexture(m_CustomSight[37], "gfx/sight/custom/custom37.tga");
R_InitTexture(m_CustomSight[38], "gfx/sight/custom/custom38.tga");
R_InitTexture(m_CustomSight[39], "gfx/sight/custom/custom39.tga");
R_InitTexture(m_CustomSight[40], "gfx/sight/custom/custom40.tga");//255 sidebar
R_InitTexture(m_CustomSight[41], "gfx/sight/custom/custom41.tga");
R_InitTexture(m_CustomSight[42], "gfx/sight/custom/custom42.tga");
R_InitTexture(m_CustomSight[43], "gfx/sight/custom/custom43.tga");
R_InitTexture(m_CustomSight[44], "gfx/sight/custom/custom44.tga");
R_InitTexture(m_CustomSight[45], "gfx/sight/custom/custom45.tga");
R_InitTexture(m_CustomSight[46], "gfx/sight/custom/custom46.tga");
R_InitTexture(m_CustomSight[47], "gfx/sight/custom/custom47.tga");
R_InitTexture(m_CustomSight[48], "gfx/sight/custom/custom48.tga");
R_InitTexture(m_CustomSight[49], "gfx/sight/custom/custom49.tga");

left = (ScreenWidth - ScreenHeight)/2;
right = left + ScreenHeight;
centerx = ScreenWidth/2;
centery = ScreenHeight/2;
	return 1;
}

int CHudSniperScope::Draw(float flTime)
{
if(gHUD.m_iFOV == 90)
{
gHUD.reddot_scope = FALSE;
gHUD.disable_scope = FALSE;
return 0;
}

const int idx = gEngfuncs.GetLocalPlayer()->index;
if (g_PlayerExtraInfo[idx].dead == true)
return 0;

if (gHUD.disable_scope)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(0, 0, 0, 0);
return 0;
}

gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);

//custom 
if (active_CustomSight)
{
//if (gHUD.custom_scope_cmd->value == 0) m_CustomSight[0]->Bind();
if (gHUD.custom_scope_cmd->value == 1) m_CustomSight[1]->Bind();
else if (gHUD.custom_scope_cmd->value == 2) m_CustomSight[2]->Bind();
else if (gHUD.custom_scope_cmd->value == 3) m_CustomSight[3]->Bind();
else if (gHUD.custom_scope_cmd->value == 4) m_CustomSight[4]->Bind();
else if (gHUD.custom_scope_cmd->value == 5) m_CustomSight[5]->Bind();
else if (gHUD.custom_scope_cmd->value == 6) m_CustomSight[6]->Bind();
else if (gHUD.custom_scope_cmd->value == 7) m_CustomSight[7]->Bind();
else if (gHUD.custom_scope_cmd->value == 8) m_CustomSight[8]->Bind();
else if (gHUD.custom_scope_cmd->value == 9) m_CustomSight[9]->Bind();
else if (gHUD.custom_scope_cmd->value == 10) m_CustomSight[10]->Bind();
else if (gHUD.custom_scope_cmd->value == 11) m_CustomSight[11]->Bind();
else if (gHUD.custom_scope_cmd->value == 12) m_CustomSight[12]->Bind();
else if (gHUD.custom_scope_cmd->value == 13) m_CustomSight[13]->Bind();
else if (gHUD.custom_scope_cmd->value == 14) m_CustomSight[14]->Bind();
else if (gHUD.custom_scope_cmd->value == 15) m_CustomSight[15]->Bind();
else if (gHUD.custom_scope_cmd->value == 16) m_CustomSight[16]->Bind();
else if (gHUD.custom_scope_cmd->value == 17) m_CustomSight[17]->Bind();
else if (gHUD.custom_scope_cmd->value == 18) m_CustomSight[18]->Bind();
else if (gHUD.custom_scope_cmd->value == 19) m_CustomSight[19]->Bind();
else if (gHUD.custom_scope_cmd->value == 20) m_CustomSight[20]->Bind();
else if (gHUD.custom_scope_cmd->value == 21) m_CustomSight[21]->Bind();
else if (gHUD.custom_scope_cmd->value == 22) m_CustomSight[22]->Bind();
else if (gHUD.custom_scope_cmd->value == 23) m_CustomSight[23]->Bind();
else if (gHUD.custom_scope_cmd->value == 24) m_CustomSight[24]->Bind();
else if (gHUD.custom_scope_cmd->value == 25) m_CustomSight[25]->Bind();
else if (gHUD.custom_scope_cmd->value == 26) m_CustomSight[26]->Bind();
else if (gHUD.custom_scope_cmd->value == 27) m_CustomSight[27]->Bind();
else if (gHUD.custom_scope_cmd->value == 28) m_CustomSight[28]->Bind();
else if (gHUD.custom_scope_cmd->value == 29) m_CustomSight[29]->Bind();
else if (gHUD.custom_scope_cmd->value == 30) m_CustomSight[30]->Bind();
else if (gHUD.custom_scope_cmd->value == 31) m_CustomSight[31]->Bind();
else if (gHUD.custom_scope_cmd->value == 32) m_CustomSight[32]->Bind();
else if (gHUD.custom_scope_cmd->value == 33) m_CustomSight[33]->Bind();
else if (gHUD.custom_scope_cmd->value == 34) m_CustomSight[34]->Bind();
else if (gHUD.custom_scope_cmd->value == 35) m_CustomSight[35]->Bind();
else if (gHUD.custom_scope_cmd->value == 36) m_CustomSight[36]->Bind();
else if (gHUD.custom_scope_cmd->value == 37) m_CustomSight[37]->Bind();
else if (gHUD.custom_scope_cmd->value == 38) m_CustomSight[38]->Bind();
else if (gHUD.custom_scope_cmd->value == 39) m_CustomSight[39]->Bind();
else if (gHUD.custom_scope_cmd->value == 40) m_CustomSight[40]->Bind();
else if (gHUD.custom_scope_cmd->value == 41) m_CustomSight[41]->Bind();
else if (gHUD.custom_scope_cmd->value == 42) m_CustomSight[42]->Bind();
else if (gHUD.custom_scope_cmd->value == 43) m_CustomSight[43]->Bind();
else if (gHUD.custom_scope_cmd->value == 44) m_CustomSight[44]->Bind();
else if (gHUD.custom_scope_cmd->value == 45) m_CustomSight[45]->Bind();
else if (gHUD.custom_scope_cmd->value == 46) m_CustomSight[46]->Bind();
else if (gHUD.custom_scope_cmd->value == 47) m_CustomSight[47]->Bind();
else if (gHUD.custom_scope_cmd->value == 48) m_CustomSight[48]->Bind();
else if (gHUD.custom_scope_cmd->value == 49) m_CustomSight[49]->Bind();

DrawUtils::Draw2DQuad((ScreenWidth - ScreenHeight)/2, 0, (ScreenWidth - ScreenHeight)/2 + ScreenHeight, ScreenHeight);


if (gHUD.custom_scope_cmd->value >= 40)
{
FillRGBABlend( 0, 0, (ScreenWidth - ScreenHeight) / 2 + 2, ScreenHeight, 0, 0, 0, 255 );
FillRGBABlend( (ScreenWidth - ScreenHeight) / 2 - 2 + ScreenHeight, 0, (ScreenWidth - ScreenHeight) / 2 + 2, ScreenHeight, 0, 0, 0, 255 );
}
else if (gHUD.custom_scope_cmd->value >= 25)
{
FillRGBABlend( 0, 0, (ScreenWidth - ScreenHeight) / 2.005 + 2, ScreenHeight, 0, 0, 0, 170 );
FillRGBABlend( (ScreenWidth - ScreenHeight) / 1.994 - 2 + ScreenHeight, 0, (ScreenWidth - ScreenHeight) / 2 + 2, ScreenHeight, 0, 0, 0, 170 );
}

}



//azure
if (active_AzureScope)
{
m_sight[11]->Bind();
DrawUtils::Draw2DQuad((ScreenWidth - ScreenHeight)/2, 0, (ScreenWidth - ScreenHeight)/2 + ScreenHeight, ScreenHeight);
}

if (active_Dot_l)
{
m_sight[4]->Bind();
DrawUtils::Draw2DQuad((ScreenWidth - ScreenHeight)/2, 0, (ScreenWidth - ScreenHeight)/2 + ScreenHeight, ScreenHeight);
}
//reddot
if (active_Reddot)
{
m_sight[0]->Bind();
DrawUtils::Draw2DQuad((ScreenWidth - ScreenHeight)/2, 0, (ScreenWidth - ScreenHeight)/2 + ScreenHeight, ScreenHeight);

FillRGBABlend( 0, 0, (ScreenWidth - ScreenHeight) / 2.005 + 2, ScreenHeight, 0, 0, 0, 170 );
FillRGBABlend( (ScreenWidth - ScreenHeight) / 1.994 - 2 + ScreenHeight, 0, (ScreenWidth - ScreenHeight) / 2 + 2, ScreenHeight, 0, 0, 0, 170 );
}

//eotech
if (active_Eotech)
{
m_sight[1]->Bind();
DrawUtils::Draw2DQuad((ScreenWidth - ScreenHeight)/2, 0, (ScreenWidth - ScreenHeight)/2 + ScreenHeight, ScreenHeight);
}

//eotech_dot
if (active_EotechDot)
{
m_sight[2]->Bind();
DrawUtils::Draw2DQuad((ScreenWidth - ScreenHeight)/2, 0, (ScreenWidth - ScreenHeight)/2 + ScreenHeight, ScreenHeight);

}

//acog
if (active_Acog)
{
m_sight[3]->Bind();
DrawUtils::Draw2DQuad((ScreenWidth - ScreenHeight)/2, 0, (ScreenWidth - ScreenHeight)/2 + ScreenHeight, ScreenHeight);

FillRGBABlend( 0, 0, (ScreenWidth - ScreenHeight) / 2.005 + 2, ScreenHeight, 0, 0, 0, 170 );
FillRGBABlend( (ScreenWidth - ScreenHeight) / 1.994 - 2 + ScreenHeight, 0, (ScreenWidth - ScreenHeight) / 2 + 2, ScreenHeight, 0, 0, 0, 170 );
}

//telescopic
if (active_Telescopic)
{
m_sight[5]->Bind();
DrawUtils::Draw2DQuad((ScreenWidth - ScreenHeight)/2, 0, (ScreenWidth - ScreenHeight)/2 + ScreenHeight, ScreenHeight);

FillRGBABlend( 0, 0, (ScreenWidth - ScreenHeight) / 2.005 + 2, ScreenHeight, 0, 0, 0, 170 );
FillRGBABlend( (ScreenWidth - ScreenHeight) / 1.994 - 2 + ScreenHeight, 0, (ScreenWidth - ScreenHeight) / 2 + 2, ScreenHeight, 0, 0, 0, 170 );
}

//crb eotech
if (active_EotechCrb)
{
m_sight[6]->Bind();
DrawUtils::Draw2DQuad((ScreenWidth - ScreenHeight)/2, 0, (ScreenWidth - ScreenHeight)/2 + ScreenHeight, ScreenHeight);
}

//eotechpandora
if (active_EotechPandora)
{
m_sight[7]->Bind();
DrawUtils::Draw2DQuad((ScreenWidth - ScreenHeight)/2, 0, (ScreenWidth - ScreenHeight)/2 + ScreenHeight, ScreenHeight);
}

//sks
if (active_SksScope)
{
m_sight[8]->Bind();
DrawUtils::Draw2DQuad((ScreenWidth - ScreenHeight)/2, 0, (ScreenWidth - ScreenHeight)/2 + ScreenHeight, ScreenHeight);

FillRGBABlend( 0, 0, (ScreenWidth - ScreenHeight) / 2 + 2, ScreenHeight, 0, 0, 0, 255 );
FillRGBABlend( (ScreenWidth - ScreenHeight) / 2 - 2 + ScreenHeight, 0, (ScreenWidth - ScreenHeight) / 2 + 2, ScreenHeight, 0, 0, 0, 255 );
}

//sniper
if (active_SniperScope)
{
m_sight[9]->Bind();
DrawUtils::Draw2DQuad((ScreenWidth - ScreenHeight)/2, 0, (ScreenWidth - ScreenHeight)/2 + ScreenHeight, ScreenHeight);

FillRGBABlend( 0, 0, (ScreenWidth - ScreenHeight) / 2 + 2, ScreenHeight, 0, 0, 0, 255 );
FillRGBABlend( (ScreenWidth - ScreenHeight) / 2 - 2 + ScreenHeight, 0, (ScreenWidth - ScreenHeight) / 2 + 2, ScreenHeight, 0, 0, 0, 255 );
}

	return 0;

}
