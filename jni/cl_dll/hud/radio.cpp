/*
radio.cpp -- Radio HUD implementation
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

extern "C"
{
#include "pm_math.h"
}

#include "parsemsg.h"
#include "cl_util.h"

#include "r_efx.h"
#include "event_api.h"
#include "com_model.h"
#include <string.h>

DECLARE_MESSAGE( m_Radio, SendAudio )
DECLARE_MESSAGE( m_Radio, ReloadSound )
DECLARE_MESSAGE( m_Radio, BotVoice )


int CHudRadio::Init( )
{
	HOOK_MESSAGE( SendAudio );
	HOOK_MESSAGE( ReloadSound );
	HOOK_MESSAGE( BotVoice );
	gHUD.AddHudElem( this );
	m_iFlags = 0;
	return 1;
}

void Broadcast( const char *msg, int pitch )
{
	if ( msg[0] == '%' && msg[1] == '!' )
		gEngfuncs.pfnPlaySoundVoiceByName( &const_cast<char *>(msg)[1], 1.0f, pitch );
	else
		gEngfuncs.pfnPlaySoundVoiceByName(const_cast<char *>(msg), 1.0f, pitch );
}

int CHudRadio::MsgFunc_SendAudio( const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );

	int SenderID = reader.ReadByte( );
	char *sentence = reader.ReadString( );
	int pitch = reader.ReadShort( );

	Broadcast( sentence, pitch );

	if( SenderID <= MAX_PLAYERS )
	{
		g_PlayerExtraInfo[SenderID].radarflashes = 22;
		g_PlayerExtraInfo[SenderID].radarflashtime = gHUD.m_flTime;
		g_PlayerExtraInfo[SenderID].radarflashtimedelta = 0.5f;
	}
	return 1;
}

int CHudRadio::MsgFunc_ReloadSound( const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );

	int vol = reader.ReadByte( );
	if ( reader.ReadByte( ) )
	{
		gEngfuncs.pfnPlaySoundByName( "weapon/generic_reload.wav", vol / 255.0f );
	}
	else
	{
		gEngfuncs.pfnPlaySoundByName( "weapon/generic_shot_reload.wav", vol / 255.0f );
	}
	return 1;
}


static void VoiceIconCallback(struct tempent_s *ent, float frametime, float currenttime)
{
	int entIndex = ent->clientIndex;
	if( !g_PlayerExtraInfo[entIndex].talking )
	{
		g_PlayerExtraInfo[entIndex].talking = false;
		ent->die = 0.0f;
	}
}

void CHudRadio::Voice(int entindex, bool bTalking)
{
	/*extra_player_info_t *pplayer;
struct cl_entity_s *ent;
	TEMPENTITY *temp;
	int spr;
int i;

	if( entindex < 0 || entindex > MAX_PLAYERS - 1) // bomb can't talk!
		return;

	pplayer = g_PlayerExtraInfo + entindex ;

	if( bTalking == pplayer->talking )
		return; // user is talking already

	if( !bTalking && pplayer->talking )
	{
		pplayer->talking = true;
	//return; // stop talking
	}

	spr = gEngfuncs.pEventAPI->EV_FindModelIndex( "sprites/voiceicon.spr" );
	if( !spr ) return;

	temp = gEngfuncs.pEfxAPI->R_DefaultSprite( vec3_origin, spr, 0 );
	if( !temp ) return;
if( gHUD.m_Health.m_iHealth == 0 )
{
	pplayer->talking = false; // sprite is created
}
else
{
pplayer->talking = true; 
}
	temp->flags = FTENT_SPRANIMATELOOP | FTENT_CLIENTCUSTOM | FTENT_PLYRATTACHMENT;
	temp->tentOffset.z = 40;
	temp->clientIndex = entindex;
	temp->callback = VoiceIconCallback;
	temp->entity.curstate.scale = 0.60f;
	temp->entity.curstate.rendermode = kRenderTransAdd;
	temp->die = gHUD.m_flTime + 60.0f; // 60 seconds must be enough?
*/
}

int CHudRadio::MsgFunc_BotVoice( const char *pszName, int iSize, void *buf )
{
	BufferReader reader( pszName, buf, iSize );

	int enable   = reader.ReadByte();
	int entIndex = reader.ReadByte();

	Voice( entIndex, enable );

	return 1;
}



/*
#include "triangleapi.h"
#include "draw_util.h"
#include "calcscreen.h"
#include "com_weapons.h"

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

/////=================item head=========

DECLARE_MESSAGE( m_HealthBar, HealthBar )
DECLARE_COMMAND(m_HealthBar, CommandActiveHealthBar);

void CHudHealthbar::UserCmd_CommandActiveHealthBar(void)
{

ffade = 255;
	m_fFade = 2.0f; 
}

int CHudHealthbar::MsgFunc_HealthBar(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	
	ClientCmd("healthbar");
	
	return 1;
}

int CHudHealthbar::Init( )
{
	HOOK_MESSAGE(HealthBar);
HOOK_COMMAND("healthbar", CommandActiveHealthBar); //Unlabeled
	gHUD.AddHudElem( this );
	m_iFlags = HUD_DRAW;
	return 1;
}

int CHudHealthbar::VidInit()
{

R_InitTexture(m_sniper, "materials/pb/hud/icon/sniper.tga");
R_InitTexture(m_rifle, "materials/pb/hud/icon/assault.tga");
R_InitTexture(m_shotgun, "materials/pb/hud/icon/shotgun.tga");
R_InitTexture(m_pistol, "materials/pb/hud/icon/pistol.tga");
//R_InitTexture(m_healthbar, "materials/pb/hud/icon/.tga");

return 1;
}

int CHudHealthbar::Draw(float flTime)
{
int weaponid; 
WEAPON *m_pWeapon;
weaponid = m_pWeapon->iId;

//
if ((gHUD.m_iHideHUDDisplay & HIDEHUD_ALL) || g_iUser1)
		return 1;

	for (int i = 1; i < 33; i++)
	{
		if (g_PlayerExtraInfo[i].dead)
			continue;

		if (g_PlayerExtraInfo[i].teamnumber != g_PlayerExtraInfo[gHUD.m_Scoreboard.m_iPlayerNum].teamnumber)
			continue;

		
			cl_entity_t *ent = gEngfuncs.GetEntityByIndex(i);


			model_t *model = ent->model;
			vec3_t origin = ent->origin;

			if (model)
				origin.z += max(model->maxs.z, 45.0);

			float screen[2]{ -1,-5 };
			if (!CalcScreen(origin, screen))
				continue;

			int textlen = DrawUtils::HudStringLen(g_PlayerInfoList[i].name);

gEngfuncs.pTriAPI->RenderMode(kRenderTransTexture);
m_pistol->Bind();
 gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);     DrawUtils::Draw2DQuadScaled(screen[0] - textlen * 0.5f - 35, screen[1] - 45, screen[0] - textlen * 0.5f + 35, screen[1] + 35);
		
	}

	return 1;
}
*/