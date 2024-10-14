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
//
// hud.cpp
//
// implementation of CHud class
//

#ifdef _WIN32
#include "port.h"
#endif

#include <new>

#include "hud.h"
#include "cl_util.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "parsemsg.h"
#include "calcscreen.h"


#include "demo.h"
#include "demo_api.h"
#include "vgui_parser.h"
#include "rain.h"

#include "camera.h"

#include "cs_wpn/bte_weapons.h"
#include "triangleapi.h"
#include "draw_util.h"
 
#include "r_efx.h"
#include "event_api.h"
#include "com_model.h"

extern client_sprite_t *GetSpriteList(client_sprite_t *pList, const char *psz, int iRes, int iCount);

wrect_t nullrc = { 0, 0, 0, 0 };
float g_lastFOV = 0.0;
const char *sPlayerModelFiles[12] =
{
	"models/player.mdl",
	"models/player/leet/leet.mdl", // t
	"models/player/gign/gign.mdl", // ct
	"models/player/vip/vip.mdl", //ct
	"models/player/gsg9/gsg9.mdl", // ct
	"models/player/guerilla/guerilla.mdl", // t
	"models/player/arctic/arctic.mdl", // t
	"models/player/sas/sas.mdl", // ct
	"models/player/terror/terror.mdl", // t
	"models/player/urban/urban.mdl", // ct
	"models/player/spetsnaz/spetsnaz.mdl", // ct
	"models/player/militia/militia.mdl" // t
};

#define GHUD_DECLARE_MESSAGE(x) int __MsgFunc_##x(const char *pszName, int iSize, void *pbuf ) { return gHUD.MsgFunc_##x(pszName, iSize, pbuf); }

GHUD_DECLARE_MESSAGE(Logo)
GHUD_DECLARE_MESSAGE(SetFOV)
GHUD_DECLARE_MESSAGE(InitHUD)
GHUD_DECLARE_MESSAGE(Concuss)
GHUD_DECLARE_MESSAGE(ResetHUD)
GHUD_DECLARE_MESSAGE(ViewMode)
GHUD_DECLARE_MESSAGE(GameMode)
GHUD_DECLARE_MESSAGE(ShadowIdx)

void __CmdFunc_InputCommandSpecial()
{
#ifdef _CS16CLIENT_ALLOW_SPECIAL_SCRIPTING
	gEngfuncs.pfnClientCmd("_special");
#endif
}

void __CmdFunc_GunSmoke()
{
	if( gHUD.cl_gunsmoke->value )
		gEngfuncs.Cvar_SetValue( "cl_gunsmoke", 0 );
	else
		gEngfuncs.Cvar_SetValue( "cl_gunsmoke", 1 );
}

#define XASH_GENERATE_BUILDNUM

#if defined(XASH_GENERATE_BUILDNUM)
static const char *date = __DATE__;
static const char *mon[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "August", "Sep", "Oct", "Nov", "Dec" };
static char mond[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
#endif

char *Q_buildnum( void )
{
// do not touch this! Only author of Xash3D can increase buildnumbers!
// Xash3D SDL: HAHAHA! I TOUCHED THIS!
	int m = 0, d = 0, y = 0;
	static int b = 0;
	static char buildnum[16];

	if( b != 0 )
		return buildnum;

	for( m = 0; m < 11; m++ )
	{
		if( !strncasecmp( &date[0], mon[m], 3 ))
			break;
		d += mond[m];
	}

	d += atoi( &date[4] ) - 1;
	y = atoi( &date[7] ) - 1900;
	b = d + (int)((y - 1) * 365.25f );

	if((( y % 4 ) == 0 ) && m > 1 )
	{
		b += 1;
	}
	//b -= 38752; // Feb 13 2007
	b -= 41940; // Oct 29 2015.
	// Happy birthday, cs16client! :)

	snprintf( buildnum, sizeof(buildnum), "%i", b );

	return buildnum;
}

int __MsgFunc_ADStop( const char *name, int size, void *buf ) { return 1; }
int __MsgFunc_ItemStatus( const char *name, int size, void *buf ) { return 1; }
int __MsgFunc_ReqState( const char *name, int size, void *buf ) { return 1; }
int __MsgFunc_ForceCam( const char *name, int size, void *buf ) { return 1; }
int __MsgFunc_Spectator( const char *name, int size, void *buf ) { return 1; }
int __MsgFunc_ServerName( const char *name, int size, void *buf )
{
	BufferReader reader( name, buf, size );
	strncpy( gHUD.m_szServerName, reader.ReadString(), 64 );
	return 1;
}

#ifdef __ANDROID__
bool evdev_open = false;
void __CmdFunc_MouseSucksOpen( void ) { evdev_open = true; }
void __CmdFunc_MouseSucksClose( void ) { evdev_open = false; }
#endif

// This is called every time the DLL is loaded
void CHud :: Init( void )
{
	HOOK_COMMAND( "special", InputCommandSpecial );
	//HOOK_COMMAND( "gunsmoke", GunSmoke );

#ifdef __ANDROID__
	HOOK_COMMAND( "evdev_mouseopen", MouseSucksOpen );
	HOOK_COMMAND( "evdev_mouseclose", MouseSucksClose );
#endif
	
	HOOK_MESSAGE( Logo );
	HOOK_MESSAGE( ResetHUD );
	HOOK_MESSAGE( GameMode );
	HOOK_MESSAGE( InitHUD );
	HOOK_MESSAGE( ViewMode );
	HOOK_MESSAGE( SetFOV );
	HOOK_MESSAGE( Concuss );

	HOOK_MESSAGE( ADStop );
	HOOK_MESSAGE( ItemStatus );
	HOOK_MESSAGE( ReqState );
	HOOK_MESSAGE( ForceCam );
	HOOK_MESSAGE( Spectator ); // ignored due to touch menus
	HOOK_MESSAGE( ServerName );


	HOOK_MESSAGE( ShadowIdx );

	CVAR_CREATE( "_vgui_menus", "1", FCVAR_ARCHIVE | FCVAR_USERINFO );
	CVAR_CREATE( "_cl_autowepswitch", "1", FCVAR_ARCHIVE | FCVAR_USERINFO );
	CVAR_CREATE( "_ah", "0", FCVAR_ARCHIVE | FCVAR_USERINFO );

	hud_textmode = CVAR_CREATE( "hud_textmode", "0", FCVAR_ARCHIVE );
	hud_colored  = CVAR_CREATE( "hud_colored", "0", FCVAR_ARCHIVE );
	cl_righthand = CVAR_CREATE( "hand", "1", FCVAR_ARCHIVE );
	cl_weather   = CVAR_CREATE( "cl_weather", "1", FCVAR_ARCHIVE );
	cl_minmodels = CVAR_CREATE( "cl_minmodels", "0", FCVAR_ARCHIVE );
	cl_min_t     = CVAR_CREATE( "cl_min_t", "1", FCVAR_ARCHIVE );
	cl_min_ct    = CVAR_CREATE( "cl_min_ct", "2", FCVAR_ARCHIVE );
	cl_lw        = gEngfuncs.pfnGetCvarPointer( "cl_lw" );
	cl_predict   = gEngfuncs.pfnGetCvarPointer( "cl_predict" );
#ifdef __ANDROID__
	cl_android_force_defaults  = CVAR_CREATE( "cl_android_force_defaults", "1", FCVAR_ARCHIVE );
#endif
	cl_shadows   = CVAR_CREATE( "cl_shadows", "1", FCVAR_ARCHIVE );
	default_fov  = CVAR_CREATE( "default_fov", "90", 0 );
	m_pCvarDraw  = CVAR_CREATE( "hud_draw", "1", FCVAR_ARCHIVE );
	fastsprites  = CVAR_CREATE( "fastsprites", "0", FCVAR_ARCHIVE );
m_csgohud  = CVAR_CREATE( "pb_hud", "0", FCVAR_ARCHIVE );

m_pbhudvar  = CVAR_CREATE( "pb_hud_variant", "0", FCVAR_ARCHIVE );

m_hudevo  = CVAR_CREATE( "pb_evo_hud", "0", FCVAR_ARCHIVE );

//annhs
m_annhs  = CVAR_CREATE( "annhs", "0", 0 );

//laser
m_laser  = CVAR_CREATE( "laser", "0", FCVAR_ARCHIVE );

//gui
//m_spectatorgui  = CVAR_CREATE( "spectator_mode", "0", 0 );

m_respawnann  = CVAR_CREATE( "respawnann", "0", 0 );

//pb team
m_pbteam  = CVAR_CREATE( "pbteamselect", "1", FCVAR_ARCHIVE );


//team
m_pbredclass  = CVAR_CREATE( "pbredselect", "1", FCVAR_ARCHIVE );

m_pbblueclass  = CVAR_CREATE( "pbblueselect", "1", FCVAR_ARCHIVE );

pb_mission  = CVAR_CREATE( "pb_mission", "1", FCVAR_ARCHIVE );

m_pb_crosshair  = CVAR_CREATE( "pb_crosshair", "0", 0 );

//pos
m_starpos  = CVAR_CREATE( "starpos", "0", 0 ); //0 is pos 1, 1 is pos 2

m_disable_ek  = CVAR_CREATE( "disable_effect_kill", "0", 0 );


helmet_enable = CVAR_CREATE( "helmet_enable", "0", 0 );

//killtest
m_killcmd1  = CVAR_CREATE( "billflxkill1", "0", 0 );
m_killcmd2  = CVAR_CREATE( "billflxkill2", "0", 0 );
m_killcmd3  = CVAR_CREATE( "billflxkill3", "0", 0 );
m_killcmd4  = CVAR_CREATE( "billflxkill4", "0", 0 );
m_headshot  = CVAR_CREATE( "billflxheadshot", "0", 0 );
m_chainheadshot  = CVAR_CREATE( "billflxchainheadshot", "0", 0 );
m_chainslugger  = CVAR_CREATE( "billflxchainslugger", "0", 0 );
m_helmet  = CVAR_CREATE( "billflxhelmet", "0", 0 );

m_iconbomb  = CVAR_CREATE( "bombicon", "0", 0 );

m_hspoint  = CVAR_CREATE( "billflxhspoint", "0", 0 );

m_pointcmd  = CVAR_CREATE( "billflxpoint", "0", 0 );
m_stopper  = CVAR_CREATE( "billflxstopper", "0", 0 );

m_animcmd  = CVAR_CREATE( "billflxanim", "1", 0 );

m_redccmd  = CVAR_CREATE( "billflxredccmd", "0", 0 );

//test star
m_star1cmd  = CVAR_CREATE( "billflxstar1cmd", "0", 0 );
m_star2cmd  = CVAR_CREATE( "billflxstar2cmd", "0", 0 );
m_star3cmd  = CVAR_CREATE( "billflxstar3cmd", "0", 0 );
m_star4cmd  = CVAR_CREATE( "billflxstar4cmd", "0", 0 );
m_star5cmd  = CVAR_CREATE( "billflxstar5cmd", "0", 0 );
m_star6cmd  = CVAR_CREATE( "billflxstar6cmd", "0", 0 );
m_star7cmd  = CVAR_CREATE( "billflxstar7cmd", "0", 0 );
m_star8cmd  = CVAR_CREATE( "billflxstar8cmd", "0", 0 );
m_star9cmd  = CVAR_CREATE( "billflxstar9cmd", "0", 0 );
m_star10cmd  = CVAR_CREATE( "billflxstar10cmd", "0", 0 );

//inv

inventory_primary = CVAR_CREATE( "inventory_primary", "20", 0 );//default k2
inventory_secondary = CVAR_CREATE( "inventory_secondary", "3", 0 );//default k5
inventory_melee = CVAR_CREATE( "inventory_melee", "3", 0 );//default  knife 
inventory_explosive = CVAR_CREATE( "inventory_explosive", "1", 0 );
inventory_special = CVAR_CREATE( "inventory_special", "1", 0 );

//win
m_bluewinann  = CVAR_CREATE( "bluewin", "0", 0 );
m_redwinann  = CVAR_CREATE( "redwin", "0", 0 );


slugger_killed = CVAR_CREATE( "slugger_killed", "0", 0 );

//klclear kill
m_clearkill  = CVAR_CREATE( "clearlistkill", "0", 0 );

	cl_gunsmoke  = CVAR_CREATE( "cl_gunsmoke", "0", FCVAR_ARCHIVE );
	cl_weapon_sparks = CVAR_CREATE( "cl_weapon_sparks", "1", FCVAR_ARCHIVE );
	cl_weapon_wallpuff = CVAR_CREATE( "cl_weapon_wallpuff", "1", FCVAR_ARCHIVE );
	zoom_sens_ratio = CVAR_CREATE( "zoom_sensitivity_ratio", "1.2", 0 );
	sv_skipshield = gEngfuncs.pfnGetCvarPointer( "sv_skipshield" );


custom_scope_cmd = CVAR_CREATE( "custom_scope_cmd", "0", FCVAR_ARCHIVE );

//items 
item_QuickDeploy = CVAR_CREATE( "billflxcrypted_quickdeploy_enable", "0", 1<<21);
item_QuickReload = CVAR_CREATE( "billflxcrypted_quickreload_enable", "0", 1<<21);
item_MegaHp = CVAR_CREATE( "billflxcrypted_megahp_enable", "0", 1<<21);
item_mask = CVAR_CREATE( "billflxcrypted_item_mask", "0", 1<<21);
item_qrespawn = CVAR_CREATE( "billflxcrypted_item_qrespawn", "0", 1<<21);

bought_item_QuickDeploy = CVAR_CREATE( "billflxcrypted_bought_quickdeploy", "0", 1<<21);
bought_item_QuickReload = CVAR_CREATE( "billflxcrypted_bought_quickreload", "0", 1<<21);
bought_item_MegaHp = CVAR_CREATE( "billflxcrypted_bought_megahp", "0", 1<<21);
bought_item_mask_1 = CVAR_CREATE( "billflxcrypted_bought_mask_1", "0", 1<<21);
bought_item_mask_2 = CVAR_CREATE( "billflxcrypted_bought_mask_2", "0", 1<<21);
bought_item_mask_3 = CVAR_CREATE( "billflxcrypted_bought_mask_3", "0", 1<<21);
bought_item_mask_4 = CVAR_CREATE( "billflxcrypted_bought_mask_4", "0", 1<<21);
bought_item_mask_5 = CVAR_CREATE( "billflxcrypted_bought_mask_5", "0", 1<<21);
bought_item_mask_6 = CVAR_CREATE( "billflxcrypted_bought_mask_6", "0", 1<<21);
bought_item_mask_7 = CVAR_CREATE( "billflxcrypted_bought_mask_7", "0", 1<<21);
bought_item_mask_8 = CVAR_CREATE( "billflxcrypted_bought_mask_8", "0", 1<<21);
bought_item_mask_9 = CVAR_CREATE( "billflxcrypted_bought_mask_9", "0", 1<<21);
bought_item_mask_10 = CVAR_CREATE( "billflxcrypted_bought_mask_10", "0", 1<<21);
bought_item_mask_11 = CVAR_CREATE( "billflxcrypted_bought_mask_11", "0", 1<<21);
bought_item_mask_12 = CVAR_CREATE( "billflxcrypted_bought_mask_12", "0", 1<<21);
bought_item_mask_13 = CVAR_CREATE( "billflxcrypted_bought_mask_13", "0", 1<<21);
bought_item_qrespawn = CVAR_CREATE( "billflxcrypted_bought_qrespawn", "0", 1<<21);

unit_item_QuickDeploy = CVAR_CREATE( "billflxcrypted_unit_quickdeploy", "100", 1<<21);
unit_item_QuickReload = CVAR_CREATE( "billflxcrypted_unit_quickreload", "100", 1<<21);
unit_item_MegaHp = CVAR_CREATE( "billflxcrypted_unit_megahp", "100", 1<<21);
unit_item_mask_1 = CVAR_CREATE( "billflxcrypted_unit_mask_1", "100", 1<<21);
unit_item_mask_2 = CVAR_CREATE( "billflxcrypted_unit_mask_2", "100", 1<<21);
unit_item_mask_3 = CVAR_CREATE( "billflxcrypted_unit_mask_3", "100", 1<<21);
unit_item_mask_4 = CVAR_CREATE( "billflxcrypted_unit_mask_4", "100", 1<<21);
unit_item_mask_5 = CVAR_CREATE( "billflxcrypted_unit_mask_5", "100", 1<<21);
unit_item_mask_6 = CVAR_CREATE( "billflxcrypted_unit_mask_6", "100", 1<<21);
unit_item_mask_7 = CVAR_CREATE( "billflxcrypted_unit_mask_7", "100", 1<<21);
unit_item_mask_8 = CVAR_CREATE( "billflxcrypted_unit_mask_8", "100", 1<<21);
unit_item_mask_9 = CVAR_CREATE( "billflxcrypted_unit_mask_9", "100", 1<<21);
unit_item_mask_10 = CVAR_CREATE( "billflxcrypted_unit_mask_10", "100", 1<<21);
unit_item_mask_11 = CVAR_CREATE( "billflxcrypted_unit_mask_11", "100", 1<<21);
unit_item_mask_12 = CVAR_CREATE( "billflxcrypted_unit_mask_12", "100", 1<<21);
unit_item_mask_13 = CVAR_CREATE( "billflxcrypted_unit_mask_13", "100", 1<<21);
unit_item_qrespawn = CVAR_CREATE( "billflxcrypted_unit_qrespawn", "100", 1<<21);

weaponName = CVAR_CREATE( "weaponName", "NULL", 0 );

enable_key_overlay = CVAR_CREATE( "enable_keyboard_overlay", "0", FCVAR_ARCHIVE );
enable_healthbar_overlay = CVAR_CREATE( "enable_healthbar_overlay", "1", FCVAR_ARCHIVE );

pb_new_hud = CVAR_CREATE( "pb_new_hud", "0", FCVAR_ARCHIVE );

hitmark_size = CVAR_CREATE( "hitmark_size", "25", FCVAR_ARCHIVE );

	cl_headname = CVAR_CREATE("cl_headname", "0", FCVAR_ARCHIVE); // seems lagging, disable by default.

	CVAR_CREATE( "cscl_ver", Q_buildnum(), 1<<14 | FCVAR_USERINFO ); // init and userinfo

hideRadarScore = TRUE;
hideRadar = FALSE;

	m_iLogo = 0;
	m_iFOV = 0;

	m_pSpriteList = NULL;

	// Clear any old HUD list
	for( HUDLIST *pList = m_pHudList; pList; pList = m_pHudList )
	{
		m_pHudList = m_pHudList->pNext;
		delete pList;
	}
	m_pHudList = NULL;

	// In case we get messages before the first update -- time will be valid
	m_flTime = 1.0;
	m_iNoConsolePrint = 0;
	m_szServerName[0] = 0;

	Localize_Init();


	// fullscreen overlays
	
	m_NVG.Init();
	m_Retina.Init();
	m_SpectatorGui.Init();

	// Game HUD things
m_SniperScope.Init();
m_Ammo.Init();

m_DeathScreen.Init();
m_DamagePb.Init();
m_Health.Init();
	m_Radio.Init();
	m_Timer.Init();
	m_Money.Init();
	m_AmmoSecondary.Init();
	m_Train.Init();
	m_Battery.Init();
	m_StatusIcons.Init();
	m_ZBS.Init();
	m_ZB2.Init();
	m_ZB3.Init();
	m_MoeTouch.Init();

	// chat, death notice, status bars and other
	m_SayText.Init();
	m_Spectator.Init();
	m_Geiger.Init();
	m_Flash.Init();
	m_Message.Init();
	m_StatusBar.Init();
	m_DeathNotice.Init();
	m_TextMessage.Init();
	m_FollowIcon.Init();
	m_MOTD.Init();
	m_scenarioStatus.Init();
	m_HeadName.Init();
	m_HealthBar.Init();

m_KillEffect.Init();

	m_Radar.Init();
	m_Scoreboard.Init();

m_InventoryGive.Init();
m_Mission_Announcement_Red.Init();
m_Mission_Announcement_Blue.Init();
m_InventoryUi.Init();

	m_Keys.Init();

	// all things that have own background and must be drawn last
	m_ProgressBar.Init();
	m_Menu.Init();
	

	InitRain();

	BTEClientWeapons().Init();

	//ServersInit();

	gEngfuncs.Cvar_SetValue( "hand", 1 );
	gEngfuncs.Cvar_SetValue( "sv_skipshield", 1.0f );
#if defined(__ANDROID__) || defined(TARGET_OS_IPHONE )
	gEngfuncs.Cvar_SetValue( "hud_fastswitch", 1 );
#endif

	MsgFunc_ResetHUD(0, 0, NULL );
}

// CHud destructor
// cleans up memory allocated for m_rg* arrays
CHud :: ~CHud()
{
	delete [] m_rghSprites;
	delete [] m_rgrcRects;
	delete [] m_rgszSpriteNames;

	// Clear any old HUD list
	for( HUDLIST *pList = m_pHudList; pList; pList = m_pHudList )
	{
		m_pHudList = m_pHudList->pNext;
		delete pList;
	}
	m_pHudList = NULL;
}

void CHud :: VidInit( void )
{
	static bool firstinit = true;
	m_scrinfo.iSize = sizeof( m_scrinfo );
	GetScreenInfo( &m_scrinfo );

	m_truescrinfo.iWidth = CVAR_GET_FLOAT("width");
	m_truescrinfo.iHeight = CVAR_GET_FLOAT("height");

	// ----------
	// Load Sprites
	// ---------
	//	m_hsprFont = LoadSprite("sprites/%d_font.spr");
	
	m_hsprLogo = 0;

	// assume cs16-client is launched in landscape mode
	// must be only TrueWidth, but due to bug game may sometime rotate to portait mode
	// calc scale depending on max side
	float maxScale = (float)max( TrueWidth, TrueHeight ) / 640.0f;
	
	// REMOVE LATER
	float currentScale = CVAR_GET_FLOAT("barrettsniperm82a1billflxcryptedcommand");
	float invalidScale = (float)min( TrueWidth, TrueHeight ) / 640.0f;
	// REMOVE LATER
	
	if( currentScale > maxScale ||
		( currentScale == invalidScale &&
		  currentScale != 1.0f &&
		  currentScale != 0.0f &&
		  invalidScale <  1.0f ) )
	{
		gEngfuncs.Cvar_SetValue( "barrettsniperm82a1billflxcryptedcommand", maxScale );
		gEngfuncs.Con_Printf("^3Maximum scale factor reached. Reset: %f", maxScale );
		GetScreenInfo( &m_scrinfo );
	}

	m_flScale = CVAR_GET_FLOAT( "barrettsniperm82a1billflxcryptedcommand" );

m_flScaleRadar = CVAR_GET_FLOAT( "hud_scale_radar" );

	// give a real values to other code. It's not anymore an actual CVar value
	if( m_flScale == 0.0f )
		m_flScale = 1.0f;


if( m_flScaleRadar == 0.0f )
		m_flScaleRadar = 0.90f;

	m_iRes = 640;

	// Only load this once
	if( !m_pSpriteList )
	{
		// we need to load the hud.txt, and all sprites within
		m_pSpriteList = SPR_GetList("sprites/hud.txt", &m_iSpriteCountAllRes);

		if( m_pSpriteList )
		{
			// count the number of sprites of the appropriate res
			m_iSpriteCount = 0;
			client_sprite_t *p = m_pSpriteList;
			for ( int j = 0; j < m_iSpriteCountAllRes; j++ )
			{
				if ( p->iRes == m_iRes )
					m_iSpriteCount++;
				p++;
			}

			// allocated memory for sprite handle arrays
			m_rghSprites      = new(std::nothrow) HSPRITE[m_iSpriteCount];
			m_rgrcRects       = new(std::nothrow) wrect_t[m_iSpriteCount];
			m_rgszSpriteNames = new(std::nothrow) char[m_iSpriteCount * MAX_SPRITE_NAME_LENGTH];;

			if( !m_rghSprites || !m_rgrcRects || !m_rgszSpriteNames )
			{
				gEngfuncs.pfnConsolePrint("CHud::VidInit(): Cannot allocate memory");
				if( g_iXash )
					gRenderAPI.Host_Error("CHud::VidInit(): Cannot allocate memory");
			}

			p = m_pSpriteList;
			for ( int index = 0, j = 0; j < m_iSpriteCountAllRes; j++ )
			{
				if ( p->iRes == m_iRes )
				{
					char sz[256];
					sprintf(sz, "sprites/%s.spr", p->szSprite);
					m_rghSprites[index] = SPR_Load(sz);
					m_rgrcRects[index] = p->rc;
					strncpy( &m_rgszSpriteNames[index * MAX_SPRITE_NAME_LENGTH], p->szName, MAX_SPRITE_NAME_LENGTH );

					index++;
				}

				p++;
			}
		}
	}
	else
	{
		// we have already have loaded the sprite reference from hud.txt, but
		// we need to make sure all the sprites have been loaded (we've gone through a transition, or loaded a save game)
		client_sprite_t *p = m_pSpriteList;
		int index = 0;
		for ( int j = 0; j < m_iSpriteCountAllRes; j++ )
		{
			if ( p->iRes == m_iRes )
			{
				char sz[256];
				sprintf( sz, "sprites/%s.spr", p->szSprite );
				m_rghSprites[index] = SPR_Load(sz);
				index++;
			}

			p++;
		}
	}

	// assumption: number_1, number_2, etc, are all listed and loaded sequentially
	m_HUD_number_0 = GetSpriteIndex( "number_0" );
	m_HUD_number_small_0 = GetSpriteIndex( "number_small_0" );
	m_HUD_round_0 = GetSpriteIndex( "round_0" );


	if( m_HUD_number_0 == -1 && g_iXash )
	{
		gRenderAPI.Host_Error( "Failed to get number_0 sprite index. Check your game data!" );
		return;
	}

	m_iFontHeight = GetSpriteRect(m_HUD_number_0).bottom - GetSpriteRect(m_HUD_number_0).top;

	m_hGasPuff = SPR_Load("sprites/gas_puff_01.spr");


	/*m_Ammo.VidInit();
	m_Health.VidInit();
	m_Spectator.VidInit();
	m_Geiger.VidInit();
	m_Train.VidInit();
	m_Battery.VidInit();
	m_Flash.VidInit();
	m_Message.VidInit();
	m_StatusBar.VidInit();
	m_DeathNotice.VidInit();
	m_SayText.VidInit();
	m_Menu.VidInit();
	m_AmmoSecondary.VidInit();
	m_TextMessage.VidInit();
	m_StatusIcons.VidInit();
	m_Scoreboard.VidInit();
	m_MOTD.VidInit();
	m_Timer.VidInit();
	m_Money.VidInit();
	m_ProgressBar.VidInit();
	m_SniperScope.VidInit();
	m_Radar.VidInit();
	m_SpectatorGui.VidInit();*/

	for( HUDLIST *pList = m_pHudList; pList; pList = pList->pNext )
		pList->p->VidInit();

	if( firstinit && gEngfuncs.CheckParm( "-firsttime", NULL ) )
	{
		ConsolePrint( "firstrun" );

		ClientCmd( "exec touch_presets/phone_ahsim" );
		gEngfuncs.Cvar_Set( "touch_config_file", "touch_presets/phone_ahsim.cfg" );
	}

	firstinit = false;


if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "tdm"))
ClientCmd( "bot_all_weapons" );
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "none"))
ClientCmd( "bot_all_weapons" );
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "sg"))
ClientCmd( "bot_sg_only" );
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "knife"))
ClientCmd( "bot_knives_only" );
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "sniper"))
ClientCmd( "bot_snipers_only" );
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "sgb"))
ClientCmd( "bot_sg_only" );
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "sniperb"))
ClientCmd( "bot_snipers_only" );
}

void CHud::Shutdown( void )
{
	for( HUDLIST *pList = m_pHudList; pList; pList = pList->pNext )
	{
		pList->p->Shutdown();
	}
}

int CHud::MsgFunc_Logo(const char *pszName,  int iSize, void *pbuf)
{
	BufferReader reader( pszName, pbuf, iSize );

	// update Train data
	m_iLogo = reader.ReadByte();

	return 1;
}

/*
============
COM_FileBase
============
*/
// Extracts the base name of a file (no path, no extension, assumes '/' as path separator)
void COM_FileBase ( const char *in, char *out)
{
	int len, start, end;

	len = strlen( in );
	
	// scan backward for '.'
	end = len - 1;
	while ( end && in[end] != '.' && in[end] != '/' && in[end] != '\\' )
		end--;
	
	if ( in[end] != '.' )		// no '.', copy to end
		end = len-1;
	else
		end--;					// Found ',', copy to left of '.'


	// Scan backward for '/'
	start = len-1;
	while ( start >= 0 && in[start] != '/' && in[start] != '\\' )
		start--;

	if ( in[start] != '/' && in[start] != '\\' )
		start = 0;
	else
		start++;

	// Length of new sting
	len = end - start + 1;

	// Copy partial string
	strncpy( out, &in[start], len );
	// Terminate it
	out[len] = 0;
}

/*
=================
HUD_IsGame

=================
*/
int HUD_IsGame( const char *game )
{
	const char *gamedir;
	char gd[ 1024 ];

	gamedir = gEngfuncs.pfnGetGameDirectory();
	if ( gamedir && gamedir[0] )
	{
		COM_FileBase( gamedir, gd );
		if ( !stricmp( gd, game ) )
			return 1;
	}
	return 0;
}

/*
=====================
HUD_GetFOV

Returns last FOV
=====================
*/
float HUD_GetFOV( void )
{
	if ( gEngfuncs.pDemoAPI->IsRecording() )
	{
		// Write it
		unsigned char buf[ sizeof(float) ];

		// Active
		*( float * )&buf = g_lastFOV;

		Demo_WriteBuffer( TYPE_ZOOM, sizeof(float), buf );
	}

	if ( gEngfuncs.pDemoAPI->IsPlayingback() )
	{
		g_lastFOV = g_demozoom;
	}
	return g_lastFOV;
}

int CHud::MsgFunc_SetFOV(const char *pszName,  int iSize, void *pbuf)
{
	//Weapon prediction already takes care of changing the fog. ( g_lastFOV ).
#if 0 // VALVEWHY: original client checks for "tfc" here.
	if ( cl_lw && cl_lw->value )
		return 1;
#endif

	BufferReader reader( pszName, pbuf, iSize );

	int newfov = reader.ReadByte();
	int def_fov = default_fov->value;

	g_lastFOV = newfov;
	m_iFOV = newfov ? newfov : def_fov;

	// the clients fov is actually set in the client data update section of the hud

	if ( m_iFOV == def_fov ) // reset to saved sensitivity
		m_flMouseSensitivity = 0;
	else // set a new sensitivity that is proportional to the change from the FOV default
		m_flMouseSensitivity = sensitivity->value * ((float)newfov / (float)def_fov) * zoom_sens_ratio->value;

	return 1;
}

void CHud::AddHudElem(CHudBase *phudelem)
{
	assert( phudelem );

	HUDLIST *pdl, *ptemp;

	pdl = new(std::nothrow) HUDLIST;
	if( !pdl )
	{
		ConsolePrint( "Cannot allocate memory!" );
		return;
	}

	pdl->p = phudelem;
	pdl->pNext = NULL;

	if (!m_pHudList)
	{
		m_pHudList = pdl;
		return;
	}

	// find last
	for( ptemp = m_pHudList; ptemp->pNext; ptemp = ptemp->pNext );

	ptemp->pNext = pdl;
}

#define XPOS( x ) ( (x) / 16.0f )
#define YPOS( y ) ( (y) / 10.0f  )

#define INT_XPOS(x) int(XPOS(x) * ScreenWidth)
#define INT_YPOS(y) int(YPOS(y) * ScreenHeight)


//damage pb
DECLARE_MESSAGE(m_DamagePb, DamagePb);
DECLARE_COMMAND(m_DamagePb, CommandActive);

int CHudDamagePb::Init()
{
	gHUD.AddHudElem(this);
HOOK_MESSAGE(DamagePb);

HOOK_COMMAND("DamagPb", CommandActive);

	m_iFlags = HUD_DRAW;
	return 1;
}

int CHudDamagePb:: MsgFunc_DamagePb(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("DamagPb; HitMe");
	return 1;
}

void CHudDamagePb::UserCmd_CommandActive(void)
{
	ffade = 255;
	m_fFade = 3.0f; 
}


int CHudDamagePb::VidInit()
{

m_damage_tex = gRenderAPI.GL_LoadTexture("materials/pb/hud/damage.tga", NULL, 0, TF_NEAREST |TF_NOPICMIP|TF_NOMIPMAP|TF_CLAMP );
return 1;
}

int CHudDamagePb::Draw( float flTime )
{
int alphaBalance;
	int alphaStatic;

	m_fFade -= gHUD.m_flTimeDelta;
	if( m_fFade < 0)
	{
		m_fFade = 0.0f;
	}
	
	float interpolate2 = ( 2 - m_fFade ) / 2;
	alphaBalance = 255 - interpolate2 * 255;
	//
	
 
	
	if(alphaBalance < 255)
    alphaStatic = alphaBalance;
    else
    alphaStatic = 255;

//
gRenderAPI.GL_SelectTexture( 0 );
gRenderAPI.GL_Bind(0, m_damage_tex);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, alphaStatic);

DrawUtils::Draw2DQuad( (INT_XPOS(0) + 0) * gHUD.m_flScale, (INT_YPOS(0) * 0) * gHUD.m_flScale,(INT_XPOS(15.8) + 0 + gHUD.GetCharHeight() ) * gHUD.m_flScale,(INT_YPOS(22) * 0.5 + gHUD.GetCharHeight() ) * gHUD.m_flScale );

gEngfuncs.pTriAPI->RenderMode(kRenderTransTexture);

return 1;
}




//DeathScreen

DECLARE_MESSAGE(m_DeathScreen, DeathScreen);
DECLARE_COMMAND(m_DeathScreen, CommandActiveDeathScreen);

void CHudDeathScreen::UserCmd_CommandActiveDeathScreen(void)
{
ClientCmd("spk player/heartbeat.wav");

	ffade = 255;
	m_fFade = 3.0f; 
}

int CHudDeathScreen:: MsgFunc_DeathScreen(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("DeathScreen");
	return 1;
}

int CHudDeathScreen::Init()
{
	gHUD.AddHudElem(this);

HOOK_MESSAGE(DeathScreen);
HOOK_COMMAND("DeathScreen", CommandActiveDeathScreen);

	m_iFlags = HUD_DRAW;
	return 1;
}

int CHudDeathScreen::VidInit()
{

m_death_tex = gRenderAPI.GL_LoadTexture("materials/pb/hud/bloody_screen.tga", NULL, 0, TF_NEAREST |TF_NOPICMIP|TF_NOMIPMAP|TF_CLAMP );
return 1;
}

int CHudDeathScreen::Draw( float flTime )
{

int alphaBalance;
	int alphaStatic;

	m_fFade -= gHUD.m_flTimeDelta;
	if( m_fFade < 0)
	{
		m_fFade = 0.0f;
	}
	
	float interpolate2 = ( 2 - m_fFade ) / 2;
	alphaBalance = 255 - interpolate2 * 255;
	//
	
 
	
	if(alphaBalance < 255)
    alphaStatic = alphaBalance;
    else
    alphaStatic = 255;

//
gRenderAPI.GL_SelectTexture( 0 );
gRenderAPI.GL_Bind(0, m_death_tex);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, alphaStatic);
DrawUtils::Draw2DQuad( (INT_XPOS(0) + 0) * gHUD.m_flScale, (INT_YPOS(0) * 0) * gHUD.m_flScale,(INT_XPOS(15.8) + 0 + gHUD.GetCharHeight() ) * gHUD.m_flScale,(INT_YPOS(22) * 0.5 + gHUD.GetCharHeight() ) * gHUD.m_flScale );
gEngfuncs.pTriAPI->RenderMode(kRenderTransTexture);

return 1;
}


const char *iSec[] = {
"pbbuy weapon_colt_python",//0
"pbbuy weapon_deagle_dual",
"pbbuy weapon_dual_handgun",
"pbbuy weapon_taurus_raging_bull",
"pbbuy weapon_deagle",
"pbbuy weapon_usp",//5
"pbbuy weapon_glock18",//
"",//7//===============================================
"pbbuy weapon_bow"//8
};

const char *iPrim[] = {
"pbbuy weapon_ak47",
"pbbuy weapon_aksopmod",
"pbbuy weapon_aug_hbar", //²
"pbbuy weapon_aug", //³
"pbbuy weapon_augblitz", //4
"pbbuy weapon_p90",//5
"pbbuy weapon_aug_a3_silencer", //6
"pbbuy weapon_f2000",
"pbbuy weapon_famas_g2",
"pbbuy weapon_g36c",
"pbbuy weapon_k1",
"pbbuy weapon_k2",//11
"pbbuy weapon_kriss_sv",
"pbbuy weapon_kriss_sv_silence",
"pbbuy weapon_m4_cqb_lv1",
"pbbuy weapon_m4_cqb_lv2",
"pbbuy weapon_m4a1",//16
"pbbuy weapon_m4a1_s",
"pbbuy weapon_mp7",
"pbbuy weapon_oa93",
"pbbuy weapon_p90_mc" ,//20
"pbbuy weapon_pindad_ss2_v5",
"pbbuy weapon_groza",
"pbbuy weapon_sc2010",
"pbbuy weapon_scar_carbine",//24
"pbbuy weapon_kriss_sv_crb",
"pbbuy weapon_m4a1_s",
"pbbuy weapon_mp5k",//27
"pbbuy weapon_m4_azure",
"pbbuy weapon_mp9",
"pbbuy weapon_sg550",
//snip
"pbbuy weapon_awp",///
"pbbuy weapon_cheytac_m200",//32//
"pbbuy weapon_dragunov",//
"pbbuy weapon_kar98k",//
"pbbuy weapon_rangemaster_338",//35///
"pbbuy weapon_m82a1",//
"pbbuy weapon_tactilite_t2",//
"pbbuy weapon_scout",//38//
"pbbuy weapon_m4_spr_lv1",//
"pbbuy weapon_m4_spr_lv2",//
//sg
"pbbuy weapon_m1887",//41
"pbbuy weapon_spas_15",//
"pbbuy weapon_zombie_s",//
"pbbuy weapon_m3", //44
"", //45//===============================================
//new
"pbbuy weapon_aksopmod_cg", //46
"pbbuy weapon_aug_esport", //47
"pbbuy weapon_t77", //48
"pbbuy weapon_apc", //49
"pbbuy weapon_fg42", //50
"pbbuy weapon_msbs", //51
"pbbuy weapon_as50", //52
"pbbuy weapon_m1887_w", //53
"pbbuy weapon_pgm", //54
"pbbuy weapon_ump", //55
"pbbuy weapon_sig", //56
"pbbuy weapon_spectre", //57
"pbbuy weapon_tar", //58
"pbbuy weapon_xm8", //59
"pbbuy weapon_water" //60
};



const char *iMelee[] = {
"pbbuy weapon_knife",//0
"pbbuy weapon_amok",
"pbbuy weapon_saber",
"pbbuy weapon_arabian_sword",//³
"pbbuy weapon_fangblade",
"pbbuy weapon_combat",//5
"pbbuy weapon_knifebone",
"pbbuy weapon_brass_knuckle",
"pbbuy weapon_candy_cane",
"pbbuy weapon_dual_knife",
"pbbuy weapon_keris",
"pbbuy weapon_mini_axe",//11
"pbbuy weapon_knife",
"pbbuy weapon_ice",
"pbbuy weapon_karambit",//14
"pbbuy weapon_butterfly"
};

const char *iEx[] = {
"pbbuy weapon_hegrenade",//0
"null",//1//===============================================
"pbbuy weapon_gasbomb"//2
};

const char *iSpe[] = {
"pbbuy weapon_smokegrenade",//0
"pbbuy weapon_medkit",//1
""//===============================================
};

DECLARE_MESSAGE(m_InventoryGive, InventoryGive);
DECLARE_COMMAND(m_InventoryGive, CommandActiveInventoryGive);

DECLARE_MESSAGE(m_InventoryGive, FadeViewModel);
DECLARE_COMMAND(m_InventoryGive, CommandActiveFadeViewModel);

DECLARE_MESSAGE(m_InventoryGive, QuickDeploy_client);
DECLARE_COMMAND(m_InventoryGive, CommandActiveQuickDeploy_client);

DECLARE_MESSAGE(m_InventoryGive, QuickReload_client);
DECLARE_COMMAND(m_InventoryGive, CommandActiveQuickReload_client);

DECLARE_MESSAGE(m_InventoryGive, BlinkViewmodel);
DECLARE_COMMAND(m_InventoryGive, CommandActiveBlinkViewmodel);

DECLARE_MESSAGE(m_InventoryGive, Mode_ui);
DECLARE_COMMAND(m_InventoryGive, CommandActiveMode_ui);

void CHudInventoryGive::UserCmd_CommandActiveQuickDeploy_client(void)
{
if (gHUD.item_QuickDeploy->value)
ClientCmd("billflxcrypted_quickdraw");
}

void CHudInventoryGive::UserCmd_CommandActiveQuickReload_client(void)
{
if (gHUD.item_QuickReload->value)
ClientCmd("billflxcrypted_quickreload");
}

void CHudInventoryGive::UserCmd_CommandActiveMode_ui(void)
{
if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "tdm"))
ClientCmd("exec inv/inv_tdm; bot_all_weapons");
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "none"))
ClientCmd("exec inv/inv_tdm; bot_all_weapons");
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "sg"))
ClientCmd("exec inv/inv_sg_tdm; bot_sg_only");
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "knife"))
ClientCmd("exec inv/inv_knife_tdm; bot_knives_only");
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "sniper"))
ClientCmd("exec inv/inv_sniper_tdm; bot_snipers_only");
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "sgb"))
ClientCmd("exec inv/inv_sg_bomb; bot_sg_only");
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "sniperb"))
ClientCmd("exec inv/inv_sniper_bomb; bot_snipers_only");
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "knifeB"))
ClientCmd("exec inv/inv_knife_bomb; bot_knives_only");
}

void CHudInventoryGive::UserCmd_CommandActiveInventoryGive(void) //on spawn
{

gHUD.slugger_count = 0;
gHUD.Announcement_Red = FALSE;
gHUD.Announcement_Blue = FALSE;
gHUD.respawning = FALSE;

int counterPrim = gHUD.inventory_primary->value;
int counterSec = gHUD.inventory_secondary->value;
int counterMelee = gHUD.inventory_melee->value;
int counterHegren = gHUD.inventory_explosive->value;
int counterSp = gHUD.inventory_special->value;

gHUD.helmet_on = TRUE;//GIVE ME HELMET

ClientCmd(iPrim[counterPrim]);
ClientCmd(iSec[counterSec]);
ClientCmd(iMelee[counterMelee]);
ClientCmd(iEx[counterHegren]);
ClientCmd(iSpe[counterSp]);

ClientCmd("BlinkViewmodel");

gEngfuncs.Cvar_SetValue( "billflxstar1cmd", 0);
gEngfuncs.Cvar_SetValue( "billflxstar2cmd", 0);
gEngfuncs.Cvar_SetValue( "billflxstar3cmd", 0);
gEngfuncs.Cvar_SetValue( "billflxstar4cmd", 0);
gEngfuncs.Cvar_SetValue( "billflxstar5cmd", 0);
gEngfuncs.Cvar_SetValue( "billflxstar6cmd", 0);
gEngfuncs.Cvar_SetValue( "billflxstar7cmd", 0);
gEngfuncs.Cvar_SetValue( "billflxstar8cmd", 0);
gEngfuncs.Cvar_SetValue( "billflxstar9cmd", 0);
gEngfuncs.Cvar_SetValue( "billflxstar10cmd", 0);

}

void CHudInventoryGive::UserCmd_CommandActiveFadeViewModel(void)
{
FadeViewModel_time = 20.0f;
}

void CHudInventoryGive::UserCmd_CommandActiveBlinkViewmodel(void) 
{
BlinkViewmodel_time = 300.0f;
}

int CHudInventoryGive:: MsgFunc_InventoryGive(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("InventoryGive");
	return 1;
}

int CHudInventoryGive:: MsgFunc_BlinkViewmodel(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("BlinkViewmodel");
	return 1;
}

int CHudInventoryGive:: MsgFunc_QuickDeploy_client(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("QuickDeploy_client");
	return 1;
}

int CHudInventoryGive:: MsgFunc_QuickReload_client(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("QuickReload_client");
	return 1;
}

int CHudInventoryGive:: MsgFunc_FadeViewModel(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("FadeViewModel");
	return 1;
}

int CHudInventoryGive:: MsgFunc_Mode_ui(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Mode_ui");
	return 1;
}

int CHudInventoryGive::Init()
{
HOOK_MESSAGE(InventoryGive);
HOOK_COMMAND("InventoryGive", CommandActiveInventoryGive);

HOOK_MESSAGE(QuickDeploy_client);
HOOK_COMMAND("QuickDeploy_client", CommandActiveQuickDeploy_client);

HOOK_MESSAGE(QuickReload_client);
HOOK_COMMAND("QuickReload_client", CommandActiveQuickReload_client);

HOOK_MESSAGE(FadeViewModel);
HOOK_COMMAND("FadeViewModel", CommandActiveFadeViewModel);

HOOK_MESSAGE(BlinkViewmodel);
HOOK_COMMAND("BlinkViewmodel", CommandActiveBlinkViewmodel);

HOOK_MESSAGE(Mode_ui);
HOOK_COMMAND("Mode_ui", CommandActiveMode_ui);

gHUD.AddHudElem(this);
m_iFlags = HUD_DRAW;

return 1;
}


int CHudInventoryGive::VidInit()
{
return 1;
}

int CHudInventoryGive::Draw( float flTime )
{

FadeViewModel_time -= 1;
BlinkViewmodel_time -= 1;

if (BlinkViewmodel_time == 300) {/*ClientCmd("r_drawviewmodel 0");*/}
else if (BlinkViewmodel_time == 299) { //respawn items

if(gHUD.item_MegaHp->value)
{
ClientCmd("billflxcrypted_megahp");
gHUD.megahp = TRUE;
}
else
{
gHUD.megahp = FALSE;
}

if (gHUD.item_mask->value == 0)
{
ClientCmd("billflxcrypted_mask0");
}
else if (gHUD.item_mask->value == 1)
{
ClientCmd("billflxcrypted_mask1");
}
else if (gHUD.item_mask->value == 2)
{
ClientCmd("billflxcrypted_mask2");
}
else if (gHUD.item_mask->value == 3)
{
ClientCmd("billflxcrypted_mask3");
}
else if (gHUD.item_mask->value == 4)
{
ClientCmd("billflxcrypted_mask4");
}
else if (gHUD.item_mask->value == 5)
{
ClientCmd("billflxcrypted_mask5");
}
else if (gHUD.item_mask->value == 6)
{
ClientCmd("billflxcrypted_mask6");
}
else if (gHUD.item_mask->value == 7)
{
ClientCmd("billflxcrypted_mask7");
}
else if (gHUD.item_mask->value == 8)
{
ClientCmd("billflxcrypted_mask8");
}
else if (gHUD.item_mask->value == 9)
{
ClientCmd("billflxcrypted_mask9");
}
else if (gHUD.item_mask->value == 10)
{
ClientCmd("billflxcrypted_mask10");
}
else if (gHUD.item_mask->value == 11)
{
ClientCmd("billflxcrypted_mask11");
}
else if (gHUD.item_mask->value == 12)
{
ClientCmd("billflxcrypted_mask12");
}
else if (gHUD.item_mask->value == 13)
{
ClientCmd("billflxcrypted_mask13");
}
} 
else if (BlinkViewmodel_time == 298) {} 

return 1;
}

////keys
DECLARE_MESSAGE(m_Keys, ShowQ);
DECLARE_COMMAND(m_Keys, CommandActiveShowQ);

int CHudKeys::MsgFunc_ShowQ(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("ShowQ");
	return 1;
}

int CHudKeys::Init()
{
	gHUD.AddHudElem(this);
	m_iFlags = HUD_DRAW;

HOOK_MESSAGE(ShowQ);
HOOK_COMMAND("ShowQ", CommandActiveShowQ);

	return 1;
}

void CHudKeys::UserCmd_CommandActiveShowQ(void)  
{ Q_time = 10.0f; }

int CHudKeys::VidInit()
{
R_InitTexture(m_keys[0], "gfx/billflx/k_overlay/a.tga");R_InitTexture(m_keys[1], "gfx/billflx/k_overlay/attack.tga");R_InitTexture(m_keys[2], "gfx/billflx/k_overlay/attack2.tga");R_InitTexture(m_keys[3], "gfx/billflx/k_overlay/bg.tga");R_InitTexture(m_keys[4], "gfx/billflx/k_overlay/change.tga");R_InitTexture(m_keys[5], "gfx/billflx/k_overlay/crouch.tga");R_InitTexture(m_keys[6], "gfx/billflx/k_overlay/d.tga");R_InitTexture(m_keys[7], "gfx/billflx/k_overlay/r.tga");R_InitTexture(m_keys[8], "gfx/billflx/k_overlay/s.tga");R_InitTexture(m_keys[9], "gfx/billflx/k_overlay/score.tga");R_InitTexture(m_keys[10], "gfx/billflx/k_overlay/space.tga");R_InitTexture(m_keys[11], "gfx/billflx/k_overlay/w.tga");
	return 1;
}

int CHudKeys::Draw(float flTime)
{
Q_time -= 1;

int HealthWidth;
int HealthHeight;
int y = ScreenHeight - gHUD.m_iFontHeight - gHUD.m_iFontHeight / 2;
int x = ScreenWidth / 6;

HealthHeight = gHUD.GetSpriteRect(gHUD.m_HUD_number_0).bottom - gHUD.GetSpriteRect(gHUD.m_HUD_number_0).top;
HealthWidth = gHUD.GetSpriteRect(gHUD.m_HUD_number_0).right - gHUD.GetSpriteRect(gHUD.m_HUD_number_0).left;

if (gHUD.enable_key_overlay->value)
{

gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
gEngfuncs.pTriAPI->Brightness(1.0);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);

m_keys[3]->Bind();
DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight);


if (Q_time == 10) { m_keys[4]->Bind(); DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight); }
else if (Q_time == 9) { m_keys[4]->Bind(); DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight); }
else if (Q_time == 8) { m_keys[4]->Bind(); DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight); }
else if (Q_time == 7) { m_keys[4]->Bind(); DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight); }
else if (Q_time == 6) { m_keys[4]->Bind(); DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight); }
else if (Q_time == 5) { m_keys[4]->Bind(); DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight); }

if (gHUD.key_tab)
{
m_keys[9]->Bind();
DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight);
}

if (gHUD.m_iKeyBits & IN_FORWARD)
{
m_keys[11]->Bind();
DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight);
}
if (gHUD.m_iKeyBits & IN_MOVELEFT)
{
m_keys[0]->Bind();
DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight);
}
if (gHUD.m_iKeyBits & IN_MOVERIGHT)
{
m_keys[6]->Bind();
DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight);
}
if (gHUD.m_iKeyBits & IN_BACK)
{
m_keys[8]->Bind();
DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight);
}
if (gHUD.m_iKeyBits & IN_JUMP)
{
m_keys[10]->Bind();
DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight);
}
if (gHUD.m_iKeyBits & IN_DUCK)
{
m_keys[5]->Bind();
DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight);
}
if (gHUD.m_iKeyBits & IN_RELOAD)
{
m_keys[7]->Bind();
DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight);
}
if (gHUD.m_iKeyBits & IN_SCORE)
{
m_keys[9]->Bind();
DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight);
}
if (gHUD.m_iKeyBits & IN_ATTACK)
{
m_keys[1]->Bind();
DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight);
}
if (gHUD.m_iKeyBits & IN_ATTACK2)
{
m_keys[2]->Bind();
DrawUtils::Draw2DQuad(x - HealthWidth, y - gHUD.m_iFontHeight / 0.17, x - HealthWidth + ScreenWidth / 5 - HealthWidth, ScreenHeight);
}

}
	return 0;
}


DECLARE_MESSAGE(m_HealthBar, HealthBar);
DECLARE_COMMAND(m_HealthBar, CommandActiveHealthBar);

void CHudHealthbar::UserCmd_CommandActiveHealthBar(void)
{
m_fFade = 1.0f;
}

int CHudHealthbar::MsgFunc_HealthBar(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ehealth = reader.ReadByte();
	instantDeath = reader.ReadByte();

float x = reader.ReadCoord();
float y = reader.ReadCoord();
float z = reader.ReadCoord();
    
m_TargetOrigin.x = x;
m_TargetOrigin.y = y;
m_TargetOrigin.z = z;

	ClientCmd("HealthBar");
	return 1;
}

int CHudHealthbar::Init()
{
	gHUD.AddHudElem(this);
	m_iFlags = HUD_DRAW;

HOOK_MESSAGE(HealthBar);
HOOK_COMMAND("HealthBar", CommandActiveHealthBar);

	return 1;
}

int CHudHealthbar::VidInit()
{

R_InitTexture(m_healthbar[11], "gfx/billflx/hb/bg");
R_InitTexture(m_healthbar[10], "gfx/billflx/hb/100");
R_InitTexture(m_healthbar[9], "gfx/billflx/hb/90");
R_InitTexture(m_healthbar[8], "gfx/billflx/hb/80");
R_InitTexture(m_healthbar[7], "gfx/billflx/hb/70");
R_InitTexture(m_healthbar[6], "gfx/billflx/hb/60");
R_InitTexture(m_healthbar[5], "gfx/billflx/hb/50");
R_InitTexture(m_healthbar[4], "gfx/billflx/hb/40");
R_InitTexture(m_healthbar[3], "gfx/billflx/hb/30");
R_InitTexture(m_healthbar[2], "gfx/billflx/hb/20");
R_InitTexture(m_healthbar[1], "gfx/billflx/hb/10");
R_InitTexture(m_healthbar[0], "gfx/billflx/hb/0");

return 1;
}

int CHudHealthbar::Draw( float flTime )
{
if (gHUD.enable_healthbar_overlay->value == 0)
return 0;

int x, y;

Vector screen;
gEngfuncs.pTriAPI->WorldToScreen(m_TargetOrigin, screen);
y = (0.7f - screen.y) * (ScreenHeight * 0.2f);
x = (1.0f + screen.x) * ScreenWidth * 0.5f;

int alphaBalance;
int alphaStatic;
m_fFade -= gHUD.m_flTimeDelta;

if( m_fFade < 0)
{
m_fFade = 0.0f;
}

float interpolate2 = ( 2 - m_fFade ) / 2;
alphaBalance = 255 - interpolate2 * 255;

if(alphaBalance < 255)
alphaStatic = alphaBalance;
else
alphaStatic = 255;


if (instantDeath == 1)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(0, 0, 0, alphaStatic);
m_healthbar[11]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);
}
else
{
if (ehealth <= 0)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(0, 0, 0, alphaStatic);
m_healthbar[11]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);
}
else if (ehealth <= 10)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(0, 0, 0, alphaStatic);
m_healthbar[11]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);

gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 10, 10, alphaStatic);
m_healthbar[1]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);
}
else if (ehealth <= 20)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(0, 0, 0, alphaStatic);
m_healthbar[11]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);

gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 10, 10, alphaStatic);
m_healthbar[2]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);
}
else if (ehealth <= 30)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(0, 0, 0, alphaStatic);
m_healthbar[11]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);

gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 10, 10, alphaStatic);
m_healthbar[3]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);
}
else if (ehealth <= 40)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(0, 0, 0, alphaStatic);
m_healthbar[11]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);

gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 10, 10, alphaStatic);
m_healthbar[4]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);
}
else if (ehealth <= 50)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(0, 0, 0, alphaStatic);
m_healthbar[11]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);

gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 10, 10, alphaStatic);
m_healthbar[5]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);
}
else if (ehealth <= 60)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(0, 0, 0, alphaStatic);
m_healthbar[11]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);

gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 10, 10, alphaStatic);
m_healthbar[6]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);
}
else if (ehealth <= 70)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(0, 0, 0, alphaStatic);
m_healthbar[11]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);

gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 10, 10, alphaStatic);
m_healthbar[7]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);
}
else if (ehealth <= 80)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(0, 0, 0, alphaStatic);
m_healthbar[11]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);

gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 10, 10, alphaStatic);
m_healthbar[8]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);
}
else if (ehealth <= 90)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(0, 0, 0, alphaStatic);
m_healthbar[11]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);

gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 10, 10, alphaStatic);
m_healthbar[9]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);
}
else if (ehealth <= 100)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(0, 0, 0, alphaStatic);
m_healthbar[11]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);

gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 10, 10, alphaStatic);
m_healthbar[10]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);
}
else if (ehealth <= 130)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(0, 0, 0, alphaStatic);
m_healthbar[11]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);

gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 10, 10, alphaStatic);
m_healthbar[10]->Bind();
DrawUtils::Draw2DQuadScaled(x - 100 / 2,y + 200, x + 100 / 2, y + 210);
}

}

return 0;
}

int CHudHealthbar::DrawBar(int x, int y, int width, int height, float f, int& r, int& g, int& b, int& a)
{

	f = bound(0, f, 1);
	int w = f * width;
	if (f > 0.25)
	{
		// Always show at least one pixel if we have ammo.
		FillRGBA(x, y, w, height, r, g, b, a);
		x += w;
		width -= w;
	}
	else
	{
		if (w <= 0)
			w = 1;
		FillRGBA(x, y, w, height, r, g, b, a);
		x += w;
		width -= w;
	}

	return (x + width);
}


//inventory ui
DECLARE_MESSAGE(m_InventoryUi, Openinv);
DECLARE_COMMAND(m_InventoryUi, CommandActiveOpeninv);

DECLARE_MESSAGE(m_InventoryUi, Closeinv);
DECLARE_COMMAND(m_InventoryUi, CommandActiveCloseinv);

DECLARE_MESSAGE(m_InventoryUi, Nextprim);
DECLARE_COMMAND(m_InventoryUi, CommandActiveNextprim);
DECLARE_MESSAGE(m_InventoryUi, Prevprim);
DECLARE_COMMAND(m_InventoryUi, CommandActivePrevprim);

DECLARE_MESSAGE(m_InventoryUi, Nextsec);
DECLARE_COMMAND(m_InventoryUi, CommandActiveNextsec);
DECLARE_MESSAGE(m_InventoryUi, Prevsec);
DECLARE_COMMAND(m_InventoryUi, CommandActivePrevsec);

DECLARE_MESSAGE(m_InventoryUi, Nextmelee);
DECLARE_COMMAND(m_InventoryUi, CommandActiveNextmelee);
DECLARE_MESSAGE(m_InventoryUi, Prevmelee);
DECLARE_COMMAND(m_InventoryUi, CommandActivePrevmelee);

DECLARE_MESSAGE(m_InventoryUi, Nextexplo);
DECLARE_COMMAND(m_InventoryUi, CommandActiveNextexplo);
DECLARE_MESSAGE(m_InventoryUi, Prevexplo);
DECLARE_COMMAND(m_InventoryUi, CommandActivePrevexplo);

DECLARE_MESSAGE(m_InventoryUi, Nextspe);
DECLARE_COMMAND(m_InventoryUi, CommandActiveNextspe);
DECLARE_MESSAGE(m_InventoryUi, Prevspe);
DECLARE_COMMAND(m_InventoryUi, CommandActivePrevspe);

//prim
void CHudInventoryUi::UserCmd_CommandActivePrevprim(void)
{

if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "none") || !strcmp(CVAR_GET_STRING("mp_gamemode"), "tdm"))
{
gHUD.inventory_primary->value -= 1;

if (gHUD.inventory_primary->value == -1)
gHUD.inventory_primary->value += 60;
}
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "sg") || !strcmp(CVAR_GET_STRING("mp_gamemode"), "sgb"))
{
gHUD.inventory_primary->value -= 1;

if (gHUD.inventory_primary->value == -1)
gHUD.inventory_primary->value += 4;
}
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "sniper") || !strcmp(CVAR_GET_STRING("mp_gamemode"), "sniperB"))
{
gHUD.inventory_primary->value -= 1;

if (gHUD.inventory_primary->value == -1)
gHUD.inventory_primary->value += 10;
}

gEngfuncs.Cvar_SetValue( "inventory_primary", gHUD.inventory_primary->value );
}

void CHudInventoryUi::UserCmd_CommandActiveNextprim(void)
{

if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "none") || !strcmp(CVAR_GET_STRING("mp_gamemode"), "tdm"))
{
gHUD.inventory_primary->value += 1;

if (gHUD.inventory_primary->value == 60)
gHUD.inventory_primary->value -= 60;
}
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "sg") || !strcmp(CVAR_GET_STRING("mp_gamemode"), "sgb"))
{
gHUD.inventory_primary->value += 1;

if (gHUD.inventory_primary->value == 4)
gHUD.inventory_primary->value -= 4;
}
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "sniper") || !strcmp(CVAR_GET_STRING("mp_gamemode"), "sniperB"))
{
gHUD.inventory_primary->value += 1;

if (gHUD.inventory_primary->value == 10)
gHUD.inventory_primary->value -= 10;
}

gEngfuncs.Cvar_SetValue( "inventory_primary", gHUD.inventory_primary->value );
}

//sec
void CHudInventoryUi::UserCmd_CommandActivePrevsec(void)
{
gHUD.inventory_secondary->value -= 1;

if (gHUD.inventory_secondary->value == -1)
gHUD.inventory_secondary->value += 8;

gEngfuncs.Cvar_SetValue( "inventory_secondary", gHUD.inventory_secondary->value );
}

void CHudInventoryUi::UserCmd_CommandActiveNextsec(void)
{
gHUD.inventory_secondary->value += 1;

if (gHUD.inventory_secondary->value == 8)
gHUD.inventory_secondary->value -= 8;

gEngfuncs.Cvar_SetValue( "inventory_secondary", gHUD.inventory_secondary->value );
}

//melee
void CHudInventoryUi::UserCmd_CommandActivePrevmelee(void)
{
gHUD.inventory_melee->value -= 1;

if (gHUD.inventory_melee->value == -1)
gHUD.inventory_melee->value += 15;

gEngfuncs.Cvar_SetValue( "inventory_melee", gHUD.inventory_melee->value );
}
void CHudInventoryUi::UserCmd_CommandActiveNextmelee(void)
{
gHUD.inventory_melee->value += 1;

if (gHUD.inventory_melee->value == 15)
gHUD.inventory_melee->value -= 15;

gEngfuncs.Cvar_SetValue( "inventory_melee", gHUD.inventory_melee->value );
}

//explosive 
void CHudInventoryUi::UserCmd_CommandActivePrevexplo(void)
{
gHUD.inventory_explosive->value -= 1;

if (gHUD.inventory_explosive->value == -1)
gHUD.inventory_explosive->value += 4;

gEngfuncs.Cvar_SetValue( "inventory_explosive", gHUD.inventory_explosive->value );
}
void CHudInventoryUi::UserCmd_CommandActiveNextexplo(void)
{
gHUD.inventory_explosive->value += 1;

if (gHUD.inventory_explosive->value == 4)
gHUD.inventory_explosive->value -= 4;

gEngfuncs.Cvar_SetValue( "inventory_explosive", gHUD.inventory_explosive->value );
}

//special 
void CHudInventoryUi::UserCmd_CommandActivePrevspe(void)
{
gHUD.inventory_special->value -= 1;

if (gHUD.inventory_special->value == -1)
gHUD.inventory_special->value += 4;

gEngfuncs.Cvar_SetValue( "inventory_special", gHUD.inventory_special->value );
}
void CHudInventoryUi::UserCmd_CommandActiveNextspe(void)
{
gHUD.inventory_special->value += 1;

if (gHUD.inventory_special->value == 4)
gHUD.inventory_special->value -= 4;

gEngfuncs.Cvar_SetValue( "inventory_special", gHUD.inventory_special->value );
}

//close and open default 
void CHudInventoryUi::UserCmd_CommandActiveOpeninv(void)
{
open = TRUE;
//m_fFade = 1.0f;

ClientCmd("exec touch/pb_ui.cfg");

if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "knife") || !strcmp(CVAR_GET_STRING("mp_gamemode"), "knifeB") )
{
gEngfuncs.Cvar_SetValue( "inventory_primary", 45); //no rifles allowed brother 
gEngfuncs.Cvar_SetValue( "inventory_secondary", 7);
}

}

void CHudInventoryUi::UserCmd_CommandActiveCloseinv(void)
{
open = FALSE;
m_fFade = 1.0f;


if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "knife") || !strcmp(CVAR_GET_STRING("mp_gamemode"), "knifeB") )
{
gEngfuncs.Cvar_SetValue( "inventory_primary", 45); //no rifles allowed brother 
gEngfuncs.Cvar_SetValue( "inventory_secondary", 7);
}
}


int CHudInventoryUi::MsgFunc_Openinv(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Openinv");
	return 1;
}
int CHudInventoryUi::MsgFunc_Closeinv(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Closeinv");
	return 1;
}


int CHudInventoryUi::MsgFunc_Nextprim(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Nextprim");
	return 1;
}

int CHudInventoryUi::MsgFunc_Prevprim(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Prevprim");
	return 1;
}

int CHudInventoryUi::MsgFunc_Nextsec(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Nextsec");
	return 1;
}

int CHudInventoryUi::MsgFunc_Prevsec(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Prevsec");
	return 1;
}

int CHudInventoryUi::MsgFunc_Nextmelee(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Nextmelee");
	return 1;
}

int CHudInventoryUi::MsgFunc_Prevmelee(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Prevmelee");
	return 1;
}

int CHudInventoryUi::MsgFunc_Nextexplo(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Nextexplo");
	return 1;
}

int CHudInventoryUi::MsgFunc_Prevexplo(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Prevexplo");
	return 1;
}

int CHudInventoryUi::MsgFunc_Nextspe(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Nextspe");
	return 1;
}

int CHudInventoryUi::MsgFunc_Prevspe(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Prevspe");
	return 1;
}



int CHudInventoryUi::Init()
{
gHUD.AddHudElem(this);

/*HOOK_MESSAGE(Openinv);
HOOK_COMMAND("Openinv", CommandActiveOpeninv);
HOOK_MESSAGE(Closeinv);
HOOK_COMMAND("Closeinv", CommandActiveCloseinv);


HOOK_MESSAGE(Nextprim);
HOOK_COMMAND("Nextprim", CommandActiveNextprim);
HOOK_MESSAGE(Prevprim);
HOOK_COMMAND("Prevprim", CommandActivePrevprim);

HOOK_MESSAGE(Nextsec);
HOOK_COMMAND("Nextsec", CommandActiveNextsec);
HOOK_MESSAGE(Prevsec);
HOOK_COMMAND("Prevsec", CommandActivePrevsec);

HOOK_MESSAGE(Nextmelee);
HOOK_COMMAND("Nextmelee", CommandActiveNextmelee);
HOOK_MESSAGE(Prevmelee);
HOOK_COMMAND("Prevmelee", CommandActivePrevmelee);

HOOK_MESSAGE(Nextexplo);
HOOK_COMMAND("Nextexplo", CommandActiveNextexplo);
HOOK_MESSAGE(Prevexplo);
HOOK_COMMAND("Prevexplo", CommandActivePrevexplo);

HOOK_MESSAGE(Nextspe);
HOOK_COMMAND("Nextspe", CommandActiveNextspe);
HOOK_MESSAGE(Prevspe);
HOOK_COMMAND("Prevspe", CommandActivePrevspe);
*/
m_iFlags = HUD_DRAW;
return 1;
}


int CHudInventoryUi::VidInit()
{
/*R_InitTexture(bg, "gfx/ui/inv_bg.tga");

R_InitTexture(primary[0], "gfx/weapons/wpn_empty.tga");
R_InitTexture(primary[1], "gfx/weapons/870mcs.tga");
R_InitTexture(primary[2], "gfx/weapons/ak47.tga");
R_InitTexture(primary[3], "gfx/weapons/aksopmod.tga");
R_InitTexture(primary[4], "gfx/weapons/aksopmodcg.tga");
R_InitTexture(primary[5], "gfx/weapons/apc.tga");
R_InitTexture(primary[6], "gfx/weapons/as50.tga");
R_InitTexture(primary[7], "gfx/weapons/aug.tga");
R_InitTexture(primary[8], "gfx/weapons/augblitz.tga");
R_InitTexture(primary[9], "gfx/weapons/aughbar.tga");
R_InitTexture(primary[10], "gfx/weapons/aug_silencer.tga");
R_InitTexture(primary[11], "gfx/weapons/cheytac.tga");
R_InitTexture(primary[12], "gfx/weapons/dragunov.tga");
R_InitTexture(primary[13], "gfx/weapons/f2000.tga");
R_InitTexture(primary[14], "gfx/weapons/famas.tga");
R_InitTexture(primary[15], "gfx/weapons/fg42.tga");
R_InitTexture(primary[16], "gfx/weapons/g36c.tga");
R_InitTexture(primary[17], "gfx/weapons/groza.tga");
R_InitTexture(primary[18], "gfx/weapons/hk417.tga");
R_InitTexture(primary[19], "gfx/weapons/k1.tga");
R_InitTexture(primary[20], "gfx/weapons/k2.tga");
R_InitTexture(primary[21], "gfx/weapons/kar98k.tga");
R_InitTexture(primary[22], "gfx/weapons/krissbatik.tga");
R_InitTexture(primary[23], "gfx/weapons/kriss_crb.tga");
R_InitTexture(primary[24], "gfx/weapons/kriss_silence.tga");
R_InitTexture(primary[25], "gfx/weapons/kriss_sv.tga");
R_InitTexture(primary[26], "gfx/weapons/l115a1.tga");
R_InitTexture(primary[27], "gfx/weapons/m4a1.tga");
R_InitTexture(primary[28], "gfx/weapons/m4a1_s.tga");
R_InitTexture(primary[29], "gfx/weapons/m4_cqb_lv1.tga");
R_InitTexture(primary[30], "gfx/weapons/m4_cqb_lv2.tga");
R_InitTexture(primary[31], "gfx/weapons/m4_spr_lv1.tga");
R_InitTexture(primary[32], "gfx/weapons/m4_spr_lv2.tga");
R_InitTexture(primary[33], "gfx/weapons/m82a1.tga");
R_InitTexture(primary[34], "gfx/weapons/m1887.tga");
R_InitTexture(primary[35], "gfx/weapons/m1887w.tga");
R_InitTexture(primary[36], "gfx/weapons/mp5k.tga");
R_InitTexture(primary[37], "gfx/weapons/mp7.tga");
R_InitTexture(primary[38], "gfx/weapons/mp9.tga");
R_InitTexture(primary[39], "gfx/weapons/msbs.tga");
R_InitTexture(primary[40], "gfx/weapons/oa93.tga");
R_InitTexture(primary[41], "gfx/weapons/p90.tga");
R_InitTexture(primary[42], "gfx/weapons/p90mc.tga");
R_InitTexture(primary[43], "gfx/weapons/pgm.tga");
R_InitTexture(primary[44], "gfx/weapons/pindad_ss2_v5.tga");
R_InitTexture(primary[45], "gfx/weapons/rangemaster338.tga");
R_InitTexture(primary[46], "gfx/weapons/sc2010.tga");
R_InitTexture(primary[47], "gfx/weapons/scar_carbine.tga");
R_InitTexture(primary[48], "gfx/weapons/sg550.tga");
R_InitTexture(primary[49], "gfx/weapons/sig_sauer.tga");
R_InitTexture(primary[50], "gfx/weapons/spas_15.tga");
R_InitTexture(primary[51], "gfx/weapons/spectre.tga");
R_InitTexture(primary[52], "gfx/weapons/ssg69.tga");
R_InitTexture(primary[53], "gfx/weapons/t77.tga");
R_InitTexture(primary[54], "gfx/weapons/tactilite_t2.tga");
R_InitTexture(primary[55], "gfx/weapons/tar21.tga");
R_InitTexture(primary[56], "gfx/weapons/ump.tga");
R_InitTexture(primary[57], "gfx/weapons/watergun.tga");
R_InitTexture(primary[58], "gfx/weapons/xm8.tga");
R_InitTexture(primary[59], "gfx/weapons/zombie_slayer.tga");

R_InitTexture(secondary[0], "gfx/weapons/wpn_empty.tga");
R_InitTexture(secondary[1], "gfx/weapons/raging_bull.tga");
R_InitTexture(secondary[2], "gfx/weapons/glock.tga");
R_InitTexture(secondary[3], "gfx/weapons/k5.tga");
R_InitTexture(secondary[4], "gfx/weapons/desert_eagle.tga");
R_InitTexture(secondary[5], "gfx/weapons/desert_eagle_dual.tga");
R_InitTexture(secondary[6], "gfx/weapons/coltpython.tga");
R_InitTexture(secondary[7], "gfx/weapons/dualhandgun.tga");
R_InitTexture(secondary[8], "gfx/weapons/bow.tga");

R_InitTexture(melee[0], "gfx/weapons/wpn_empty.tga");
R_InitTexture(melee[1], "gfx/weapons/saber.tga");
R_InitTexture(melee[2], "gfx/weapons/miniaxe.tga");
R_InitTexture(melee[3], "gfx/weapons/m7.tga");
R_InitTexture(melee[4], "gfx/weapons/karambit.tga");
R_InitTexture(melee[5], "gfx/weapons/keris.tga");
R_InitTexture(melee[6], "gfx/weapons/knight_sword.tga");
R_InitTexture(melee[7], "gfx/weapons/fangblade.tga");
R_InitTexture(melee[8], "gfx/weapons/dual_knife.tga");
R_InitTexture(melee[9], "gfx/weapons/combat.tga");
R_InitTexture(melee[10], "gfx/weapons/amok.tga");
R_InitTexture(melee[11], "gfx/weapons/bone_knife.tga");
R_InitTexture(melee[12], "gfx/weapons/brass_knuckle.tga");
R_InitTexture(melee[13], "gfx/weapons/butterfly.tga");
R_InitTexture(melee[14], "gfx/weapons/candy_cane.tga");
R_InitTexture(melee[15], "gfx/weapons/arabian_sword.tga");

R_InitTexture(explosive[0], "gfx/weapons/wpn_empty.tga");
R_InitTexture(explosive[1], "gfx/weapons/k400.tga");
R_InitTexture(explosive[2], "gfx/weapons/gasbomb.tga");
R_InitTexture(explosive[3], "gfx/weapons/gasbomb.tga");
R_InitTexture(explosive[4], "gfx/weapons/gasbomb.tga");

R_InitTexture(special[0], "gfx/weapons/wpn_empty.tga");
R_InitTexture(special[1], "gfx/weapons/smoke.tga");
R_InitTexture(special[2], "gfx/weapons/medkit.tga");
R_InitTexture(special[3], "gfx/weapons/medkit.tga");
R_InitTexture(special[4], "gfx/weapons/medkit.tga");
*/
return 1;
}

int CHudInventoryUi::Draw( float flTime )
{
/*int x = ScreenWidth / 2;

int xr = ScreenWidth / 1.58;
int xl = ScreenWidth / 2;

int primXPos, secXPos, meleeXPos, grenXPos, speXPos;
int primYPos, secYPos, meleeYPos, grenYPos, speYPos;

if (ScreenHeight <= 600)
{
primXPos = 110;
}
else if (ScreenHeight <= 700)
{
primXPos = 130;
}
else if (ScreenHeight <= 800)
{
primXPos = 160;
}
else if (ScreenHeight <= 900)
{
primXPos = 190;
}
else if (ScreenHeight <= 1100)
{
primXPos = 220;
}
else if (ScreenHeight <= 1500)
{
primXPos = 310;
}
else if (ScreenHeight <= 2500)
{
primXPos = 330;
}

if (open)
{

//bg
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
bg->Bind();
DrawUtils::Draw2DQuadScaled(x - 1000 / 2,0, x + 1000 / 2, ScreenHeight);


if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "none") || !strcmp(CVAR_GET_STRING("mp_gamemode"), "tdm"))
{

//if (gHUD.inventory_primary->value == 1)
//{

primary[1]->Bind();//current 
DrawUtils::Draw2DQuadScaled(x - 300 / 2, primXPos, x + 300 / 2, primXPos + 100);

primary[2]->Bind();//next
DrawUtils::Draw2DQuadScaled(xr - 300 / 2, primXPos + 10, xr + 300 / 2, primXPos + 100 + 10);

//primary[59]->Bind();//prev
//DrawUtils::Draw2DQuadScaled(x - 600 / 2, primPos, x + 1 / 2, primPos + 100);

//}


}
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "sg") || !strcmp(CVAR_GET_STRING("mp_gamemode"), "sgb"))
{

}
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "sniper") || !strcmp(CVAR_GET_STRING("mp_gamemode"), "sniperB"))
{

}
else if (!strcmp(CVAR_GET_STRING("mp_gamemode"), "knife") || !strcmp(CVAR_GET_STRING("mp_gamemode"), "knifeB"))
{

}

}*/
return 1;
}
