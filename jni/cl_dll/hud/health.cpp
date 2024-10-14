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
// Health.cpp
//
// implementation of CHudHealth class
//

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#include "hud.h"
#include "cl_util.h"
#include "parsemsg.h"
#include <string.h>
#include "eventscripts.h"

#include "draw_util.h"
//#include "const/const_client.h"
#include "triangleapi.h"

#include "string.h"
#include "assert.h"
#include <numeric>
#include <tuple>

#include "hud_sub.h"
#include "r_texture.h"

DECLARE_MESSAGE(m_Health, Health )
DECLARE_MESSAGE(m_Health, Damage )
DECLARE_MESSAGE(m_Health, ScoreAttrib )
DECLARE_MESSAGE(m_Health, ClCorpse )

DECLARE_MESSAGE(m_Health, HitMe);
DECLARE_COMMAND(m_Health, CommandActiveHitMe);


#define PAIN_NAME "sprites/%d_pain.spr"
#define DAMAGE_NAME "sprites/%d_dmg.spr"
#define EPSILON 0.4f

int giDmgHeight, giDmgWidth;

float g_LocationColor[3];

int giDmgFlags[NUM_DMG_TYPES] = 
{
	DMG_POISON,
	DMG_ACID,
	DMG_FREEZE|DMG_SLOWFREEZE,
	DMG_DROWN,
	DMG_BURN|DMG_SLOWBURN,
	DMG_NERVEGAS,
	DMG_RADIATION,
	DMG_SHOCK,
	DMG_CALTROP,
	DMG_TRANQ,
	DMG_CONCUSS,
	DMG_HALLUC
};

enum
{
	ATK_FRONT = 0,
	ATK_RIGHT,
	ATK_REAR,
	ATK_LEFT
};

void CHudHealth::UserCmd_CommandActiveHitMe(void)
{
HitMe_time = 200.0f;
}

int CHudHealth::MsgFunc_HitMe(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("HitMe");
	return 1;
}

int CHudHealth::Init(void)
{
	HOOK_MESSAGE(Health);
	HOOK_MESSAGE(Damage);
	HOOK_MESSAGE(ScoreAttrib);
	HOOK_MESSAGE(ClCorpse);

HOOK_MESSAGE(HitMe);
HOOK_COMMAND("HitMe", CommandActiveHitMe);

	m_iHealth = 100;
	m_fFade = 0;
	m_iFlags = 0;
	m_bitsDamage = 0;
	giDmgHeight = 0;
	giDmgWidth = 0;

	for( int i = 0; i < 4; i++ )
		m_fAttack[i] = 0;

	memset(m_dmg, 0, sizeof(DAMAGE_IMAGE) * NUM_DMG_TYPES);

	CVAR_CREATE("cl_corpsestay", "600", FCVAR_ARCHIVE);
	gHUD.AddHudElem(this);
	return 1;
}

void CHudHealth::Reset( void )
{
	// make sure the pain compass is cleared when the player respawns
	for( int i = 0; i < 4; i++ )
		m_fAttack[i] = 0;


	// force all the flashing damage icons to expire
	m_bitsDamage = 0;
	for ( int i = 0; i < NUM_DMG_TYPES; i++ )
	{
		m_dmg[i].fExpire = 0;
	}
}

int CHudHealth::VidInit(void)
{
	m_hSprite = LoadSprite(PAIN_NAME);

	m_vAttackPos[ATK_FRONT].x = ScreenWidth  / 2 - SPR_Width ( m_hSprite, 0 ) / 2;
	m_vAttackPos[ATK_FRONT].y = ScreenHeight / 2 - SPR_Height( m_hSprite, 0 ) * 3;

	m_vAttackPos[ATK_RIGHT].x = ScreenWidth  / 2 + SPR_Width ( m_hSprite, 1 ) * 2;
	m_vAttackPos[ATK_RIGHT].y = ScreenHeight / 2 - SPR_Height( m_hSprite, 1 ) / 2;

	m_vAttackPos[ATK_REAR ].x = ScreenWidth  / 2 - SPR_Width ( m_hSprite, 2 ) / 2;
	m_vAttackPos[ATK_REAR ].y = ScreenHeight / 2 + SPR_Height( m_hSprite, 2 ) * 2;

	m_vAttackPos[ATK_LEFT ].x = ScreenWidth  / 2 - SPR_Width ( m_hSprite, 3 ) * 3;
	m_vAttackPos[ATK_LEFT ].y = ScreenHeight / 2 - SPR_Height( m_hSprite, 3 ) / 2;


	m_HUD_dmg_bio = gHUD.GetSpriteIndex( "dmg_bio" ) + 1;
	m_HUD_cross = gHUD.GetSpriteIndex( "cross" );

	giDmgHeight = gHUD.GetSpriteRect(m_HUD_dmg_bio).right - gHUD.GetSpriteRect(m_HUD_dmg_bio).left;
	giDmgWidth = gHUD.GetSpriteRect(m_HUD_dmg_bio).bottom - gHUD.GetSpriteRect(m_HUD_dmg_bio).top;

m_iNum_L = gHUD.GetSpriteIndex("upboard_num");
m_iNum_S = gHUD.GetSpriteIndex("SBNum_S");

BuildHudNumberRect(m_iNum_L, m_rcNumber_Large, 30, 55, 1, 1);
BuildHudNumberRect(m_iNum_S, m_rcNumber_Small, 10, 10, 1, 1);

R_InitTexture(m_equipment[0], "gfx/billflx/equip/stand.tga");
R_InitTexture(m_equipment[1], "gfx/billflx/equip/duck.tga");R_InitTexture(m_equipment[2], "gfx/billflx/equip/helmet.tga");R_InitTexture(m_equipment[3], "gfx/billflx/equip/helmetless.tga");

	return 1;
}

int CHudHealth:: MsgFunc_Health(const char *pszName,  int iSize, void *pbuf )
{
	// TODO: update local health data
	BufferReader reader( pszName, pbuf, iSize );
	//int x = reader.ReadByte();
	int x = m_iHealth;
	if (iSize == 2)
	{
		x = reader.ReadShort();
	}
	else
	{
		x = reader.ReadByte();
	}

	m_iFlags |= HUD_DRAW;

	// Only update the fade if we've changed health
	if (x != m_iHealth)
	{
		m_fFade = FADE_TIME;
		m_iHealth = x;
	}

	return 1;
}


int CHudHealth:: MsgFunc_Damage(const char *pszName,  int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );

	int armor = reader.ReadByte();	// armor
	int damageTaken = reader.ReadByte();	// health
	long bitsDamage = reader.ReadLong(); // damage bits

	vec3_t vecFrom;

	for ( int i = 0 ; i < 3 ; i++)
		vecFrom[i] = reader.ReadCoord();

	UpdateTiles(gHUD.m_flTime, bitsDamage);

	// Actually took damage?
	if ( damageTaken > 0 || armor > 0 )
	{
		CalcDamageDirection(vecFrom);
		if( g_iXash )
		{
			float time = damageTaken * 4.0f + armor * 2.0f;

			if( time > 200.0f ) time = 200.0f;
			if(gMobileAPI.pfnVibrate)
				gMobileAPI.pfnVibrate( time, 1 );
		}
	}
	return 1;
}

int CHudHealth:: MsgFunc_ScoreAttrib(const char *pszName,  int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );

	int index = reader.ReadByte();
	unsigned char flags = reader.ReadByte();
	g_PlayerExtraInfo[index].dead   = !!(flags & PLAYER_DEAD);
	g_PlayerExtraInfo[index].has_c4 = !!(flags & PLAYER_HAS_C4);
	g_PlayerExtraInfo[index].vip    = !!(flags & PLAYER_VIP);
	g_PlayerExtraInfo[index].zombie = !!(flags & PLAYER_ZOMBIE);
	return 1;
}
// Returns back a color from the
// Green <-> Yellow <-> Red ramp
void CHudHealth::GetPainColor( int &r, int &g, int &b, int &a )
{
#if 0
	int iHealth = m_iHealth;

	if (iHealth > 25)
		iHealth -= 25;
	else if ( iHealth < 0 )
		iHealth = 0;
	g = iHealth * 255 / 100;
	r = 255 - g;
	b = 0;
#else
	if( m_iHealth <= 15 )
	{
		a = 255; // If health is getting low, make it bright red
	}
	else
	{
		// Has health changed? Flash the health #
		if (m_fFade)
		{
			m_fFade -= (gHUD.m_flTimeDelta * 20);

			if (m_fFade <= 0)
			{
				m_fFade = 0;
				a = MIN_ALPHA;
			}
			else
			{
				// Fade the health number back to dim
				a = MIN_ALPHA +  (m_fFade/FADE_TIME) * 128;
			}
		}
		else
		{
			a = MIN_ALPHA;
		}
	}

	if (m_iHealth > 25)
	{
		DrawUtils::UnpackRGB(r,g,b, RGB_YELLOWISH);
	}
	else
	{
		r = 250;
		g = 0;
		b = 0;
	}
#endif 
}


void CHudHealth::BuildHudNumberRect(int moe, wrect_t *prc, int w, int h, int xOffset, int yOffset)
{
	wrect_t rc = gHUD.GetSpriteRect(moe);
	int x = rc.left;
	int y = rc.top;

	for (int i = 0; i < 10; i++)
	{
		prc[i].left = x;
		prc[i].top = 0;
		prc[i].right = prc[i].left + w + xOffset;
		prc[i].bottom = h + yOffset;

		x += w;
		y += h;
	}
}

int CHudHealth::DrawHudNumber(int moe, wrect_t *prc, int x, int y, int iFlags, int iNumber, int r, int g, int b)
{
	int iWidth = prc[0].right - prc[0].left;
	int k;
	wrect_t rc;

	if (iNumber >= 10000)
	{
		k = iNumber / 10000;
		SPR_Set(gHUD.GetSprite(moe), r, g, b);
		SPR_DrawAdditive(0, x, y, &prc[k]);
		x += iWidth;
	}
	else if (iFlags & (DHN_5DIGITS))
	{
		if (iFlags & DHN_DRAWZERO)
		{
			SPR_Set(gHUD.GetSprite(moe), r, g, b);
			SPR_DrawAdditive(0, x, y, &prc[0]);
		}

		x += iWidth;
	}

	if (iNumber >= 1000)
	{
		k = (iNumber % 10000) / 1000;
		SPR_Set(gHUD.GetSprite(moe), r, g, b);
		SPR_DrawAdditive(0, x, y, &prc[k]);
		x += iWidth;
	}
	else if (iFlags & (DHN_5DIGITS | DHN_4DIGITS))
	{
		if (iFlags & DHN_DRAWZERO)
		{
			SPR_Set(gHUD.GetSprite(moe), r, g, b);
			SPR_DrawAdditive(0, x, y, &prc[0]);
		}

		x += iWidth;
	}

	if (iNumber >= 100)
	{
		k = (iNumber % 1000) / 100;
		SPR_Set(gHUD.GetSprite(moe), r, g, b);
		SPR_DrawAdditive(0, x, y, &prc[k]);
		x += iWidth;
	}
	else if (iFlags & (DHN_5DIGITS | DHN_4DIGITS | DHN_3DIGITS))
	{
		if (iFlags & DHN_DRAWZERO)
		{
			SPR_Set(gHUD.GetSprite(moe), r, g, b);
			SPR_DrawAdditive(0, x, y, &prc[0]);
		}

		x += iWidth;
	}

	if (iNumber >= 10)
	{
		k = (iNumber % 100) / 10;
		rc = prc[k];
		SPR_Set(gHUD.GetSprite(moe), r, g, b);
		SPR_DrawAdditive(0, x, y, &rc);
		x += iWidth;
	}
	else if (iFlags & (DHN_5DIGITS | DHN_4DIGITS | DHN_3DIGITS | DHN_2DIGITS))
	{
		if (iFlags & DHN_DRAWZERO)
		{
			SPR_Set(gHUD.GetSprite(moe), r, g, b);
			SPR_DrawAdditive(0, x, y, &prc[0]);
		}

		x += iWidth;
	}

	k = iNumber % 10;
	SPR_Set(gHUD.GetSprite(moe), r, g, b);
	SPR_DrawAdditive(0, x, y, &prc[k]);
	x += iWidth;

	return x;
}


int CHudHealth::GetHudNumberWidth(int moe, wrect_t *prc, int iFlags, int iNumber)
{
	int iWidth = prc[0].right - prc[0].left;
	int k;
	wrect_t rc;
	int x = 0;

	if (iNumber >= 10000)
	{
		k = iNumber / 10000;
		x += iWidth;
	}
	else if (iFlags & (DHN_5DIGITS))
		x += iWidth;

	if (iNumber >= 1000)
	{
		k = (iNumber % 10000) / 1000;
		x += iWidth;
	}
	else if (iFlags & (DHN_5DIGITS | DHN_4DIGITS))
		x += iWidth;

	if (iNumber >= 100)
	{
		k = (iNumber % 1000) / 100;
		x += iWidth;
	}
	else if (iFlags & (DHN_5DIGITS | DHN_4DIGITS | DHN_3DIGITS))
		x += iWidth;

	if (iNumber >= 10)
	{
		k = (iNumber % 100) / 10;
		rc = prc[k];
		x += iWidth;
	}
	else if (iFlags & (DHN_5DIGITS | DHN_4DIGITS | DHN_3DIGITS | DHN_2DIGITS))
		x += iWidth;

	k = iNumber % 10;
	x += iWidth;

	return x;
}


int CHudHealth::Draw(float flTime)
{

HitMe_time -= 0.5;

	if( !(gHUD.m_iHideHUDDisplay & HIDEHUD_HEALTH ) && !gEngfuncs.IsSpectateOnly() )
	{
		DrawHealthBar( flTime );
		DrawDamage( flTime );
		DrawPain( flTime );
	}

return 1;
}

void CHudHealth::DrawHealthBar( float flTime )
{
	int r, g, b;
	int a = 0, x, y;
	int HealthWidth;
	int HealthHeight;
	int iFlags = DHN_DRAWZERO; // draw 0 values

	GetPainColor( r, g, b, a );
	DrawUtils::ScaleColors(r, g, b, a );

	// Only draw health if we have the suit.
	if (gHUD.m_iWeaponBits & (1<<(WEAPON_SUIT)))
	{


		HealthHeight = gHUD.GetSpriteRect(gHUD.m_HUD_number_0).bottom - gHUD.GetSpriteRect(gHUD.m_HUD_number_0).top;
		HealthWidth = gHUD.GetSpriteRect(gHUD.m_HUD_number_0).right - gHUD.GetSpriteRect(gHUD.m_HUD_number_0).left;


		int CrossWidth = gHUD.GetSpriteRect(m_HUD_cross).right - gHUD.GetSpriteRect(m_HUD_cross).left;

		y = ScreenHeight - gHUD.m_iFontHeight - gHUD.m_iFontHeight / 2;
		x = CrossWidth /2;


int y1 = ScreenHeight - gHUD.m_iFontHeight / 0.5;
int x1 = 1+CrossWidth /0.3;

		//SPR_Set(gHUD.GetSprite(m_HUD_cross), r, g, b);
		//SPR_DrawAdditive(0, x, y, &gHUD.GetSpriteRect(m_HUD_cross));

		x = CrossWidth + HealthWidth / 2;

		//x = DrawUtils::DrawHudNumber2(x1, y1, true,3, m_iHealth, r, g, b);

int textHealth = GetHudNumberWidth(m_iNum_S, m_rcNumber_Small, DHN_2DIGITS | DHN_DRAWZERO, m_iHealth);
int rh,gh,bh;

const int idx = gEngfuncs.GetLocalPlayer()->index;
if (g_PlayerExtraInfo[idx].dead == true)
{

x = DrawHudNumber(m_iNum_L, m_rcNumber_Large, x1, y1 - 30, iFlags|DHN_3DIGITS, 00, 255, 0, 0);

}
else
{

if (textHealth < 0)
x = DrawHudNumber(m_iNum_L, m_rcNumber_Large, x1, y1 - 30, iFlags|DHN_3DIGITS, 00, 255, 0, 0);
else if (textHealth > 0)
{

if (m_iHealth <= 25)
{
rh = 255;
gh = 0;
bh = 0;
}
else if (m_iHealth <= 50)
{
rh = 255;
gh = 255;
bh = 0;
}
else if (m_iHealth <= 85)
{
rh = 255;
gh = 165;
bh = 0;
}
else if (m_iHealth >= 100)
{
rh = 255;
gh = 255;
bh = 255;
}


x = DrawHudNumber(m_iNum_L, m_rcNumber_Large, x1, y1 - 30, iFlags|DHN_3DIGITS, m_iHealth, rh, gh, bh);
}

}

		
int abang = 255, ijo = 255, biru = 255;

int ys = ScreenHeight - gHUD.m_iFontHeight / 1.2;
float f;

if (gHUD.megahp)
f = (float)m_iHealth / (float)130;
else
f = (float)m_iHealth / (float)100;

FillRGBABlend(5, ys + 0.5, HealthWidth * 16, HealthHeight * 0.6, 255, 255, 255, 90);

x = DrawBar(5, ys + 0.5, HealthWidth * 16, HealthHeight * 0.6, f, abang, ijo, biru, a); //  height 20 number 25

DrawUtils::DrawOutlinedRect(5, ys + 0.5, HealthWidth * 16, HealthHeight * 0.6, 0, 0, 0, 255);




int HealthWidth;
int HealthHeight;

HealthHeight = gHUD.GetSpriteRect(gHUD.m_HUD_number_0).bottom - gHUD.GetSpriteRect(gHUD.m_HUD_number_0).top;
HealthWidth = gHUD.GetSpriteRect(gHUD.m_HUD_number_0).right - gHUD.GetSpriteRect(gHUD.m_HUD_number_0).left;

int yss = ScreenHeight - gHUD.m_iFontHeight - gHUD.m_iFontHeight / 2;

//gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);

if (HitMe_time == 200) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 199) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 198) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 197) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 196) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 195) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 194) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 193) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 192) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 191) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 190) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 189) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 188) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 187) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 186) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 185) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 184) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 183) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 182) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 181) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 180) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 179) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 178) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 177) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 176) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 175) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 174) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 173) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 172) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 171) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 170) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 169) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 168) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 167) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 166) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 165) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 164) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 163) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 162) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 161) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 160) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 159) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 158) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 157) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 156) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 155) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 154) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 153) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 152) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 151) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 150) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 149) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 148) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 147) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 146) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 145) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 144) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 143) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 142) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 141) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 140) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 139) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 138) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 137) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 136) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 135) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 134) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 133) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 132) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 131) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 130) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 129) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 128) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 127) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 126) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 125) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 124) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 123) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 122) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 121) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 120) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 119) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 118) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 117) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 116) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 115) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 114) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 113) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 112) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 111) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 110) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 109) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 108) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 107) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 106) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 105) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 104) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 103) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 102) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 101) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 100) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 99) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 98) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 97) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 96) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 95) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 94) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 93) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 92) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 91) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 90) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 89) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 88) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 87) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 86) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 85) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 84) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 83) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 82) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 81) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 80) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 79) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 78) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 77) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 76) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 75) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 74) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 73) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 72) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 71) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 70) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 69) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 68) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 67) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 66) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 65) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 64) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 63) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 62) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 61) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 60) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 59) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 58) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 57) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 56) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 55) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 54) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 53) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 52) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 51) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 50) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 49) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 48) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 47) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 46) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 45) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 44) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 43) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 42) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 41) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 40) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 39) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 38) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 37) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 36) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 35) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 34) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 33) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 32) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 31) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 30) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 29) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 28) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 27) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 26) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 25) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 24) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 23) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 22) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 21) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 20) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 19) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 18) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 17) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 16) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 15) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 14) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 13) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 12) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 11) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 10) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 0);
else if (HitMe_time == 9) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 8) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 7) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 6) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 5) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 4) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 3) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 2) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 1) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
else if (HitMe_time == 0) gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);

if (gHUD.m_iKeyBits & IN_DUCK)
{
m_equipment[1]->Bind();
DrawUtils::Draw2DQuadScaled(20, yss - gHUD.m_iFontHeight / 0.5, 1080 /12 - HealthWidth, ScreenHeight - 25);
}
else
{
m_equipment[0]->Bind();
DrawUtils::Draw2DQuadScaled(20, yss - gHUD.m_iFontHeight / 0.5, 1080 /12 - HealthWidth, ScreenHeight - 25);
}


//helmet
if (gHUD.helmet_on)
{
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
m_equipment[2]->Bind();
DrawUtils::Draw2DQuadScaled(285, yss - gHUD.m_iFontHeight / 1, HealthWidth * 16, ScreenHeight - 25);
}
else
{
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
m_equipment[3]->Bind();
DrawUtils::Draw2DQuadScaled(285, yss - gHUD.m_iFontHeight / 1, HealthWidth * 16, ScreenHeight - 25);
}
	}
}


int CHudHealth::DrawBar(int x, int y, int width, int height, float f, int& r, int& g, int& b, int& a)
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


void CHudHealth::CalcDamageDirection( Vector vecFrom )
{
	Vector	forward, right, up;
	float	side, front, flDistToTarget;

	if( vecFrom.IsNull() )
	{
		for( int i = 0; i < 4; i++ )
			m_fAttack[i] = 0;
		return;
	}

	vecFrom = vecFrom - gHUD.m_vecOrigin;
	flDistToTarget = vecFrom.Length();
	vecFrom = vecFrom.Normalize();
	AngleVectors (gHUD.m_vecAngles, forward, right, up);

	front = DotProduct (vecFrom, right);
	side = DotProduct (vecFrom, forward);

	if (flDistToTarget <= 50)
	{
		for( int i = 0; i < 4; i++ )
			m_fAttack[i] = 1;
	}
	else
	{
		if (side > EPSILON)
			m_fAttack[0] = max(m_fAttack[0], side);
		if (side < -EPSILON)
			m_fAttack[1] = max(m_fAttack[1], 0 - side );
		if (front > EPSILON)
			m_fAttack[2] = max(m_fAttack[2], front);
		if (front < -EPSILON)
			m_fAttack[3] = max(m_fAttack[3], 0 - front );
	}
}

void CHudHealth::DrawPain(float flTime)
{
	if (m_fAttack[0] == 0 &&
		m_fAttack[1] == 0 &&
		m_fAttack[2] == 0 &&
		m_fAttack[3] == 0)
		return;

	float a, fFade = gHUD.m_flTimeDelta * 2;

	for( int i = 0; i < 4; i++ )
	{
		if( m_fAttack[i] > EPSILON )
		{
			/*GetPainColor(r, g, b);
			shade = a * max( m_fAttack[i], 0.5 );
			DrawUtils::ScaleColors(r, g, b, shade);*/

			a = max( m_fAttack[i], 0.5f );

			SPR_Set( m_hSprite, 255 * a, 255 * a, 255 * a);
			SPR_DrawAdditive( i, m_vAttackPos[i].x, m_vAttackPos[i].y, NULL );
			m_fAttack[i] = max( 0.0f, m_fAttack[i] - fFade );
		}
		else
			m_fAttack[i] = 0;
	}
}

void CHudHealth::DrawDamage(float flTime)
{
	int r, g, b, a;

	if (!m_bitsDamage)
		return;

	DrawUtils::UnpackRGB(r,g,b, RGB_YELLOWISH);
	
	a = (int)( fabs(sin(flTime*2)) * 256.0);

	DrawUtils::ScaleColors(r, g, b, a);
	int i;
	// Draw all the items
	for (i = 0; i < NUM_DMG_TYPES; i++)
	{
		if (m_bitsDamage & giDmgFlags[i])
		{
			DAMAGE_IMAGE *pdmg = &m_dmg[i];
			SPR_Set(gHUD.GetSprite(m_HUD_dmg_bio + i), r, g, b );
			SPR_DrawAdditive(0, pdmg->x, pdmg->y, &gHUD.GetSpriteRect(m_HUD_dmg_bio + i));
		}
	}


	// check for bits that should be expired
	for ( i = 0; i < NUM_DMG_TYPES; i++ )
	{
		DAMAGE_IMAGE *pdmg = &m_dmg[i];

		if ( m_bitsDamage & giDmgFlags[i] )
		{
			pdmg->fExpire = min( flTime + DMG_IMAGE_LIFE, pdmg->fExpire );

			if ( pdmg->fExpire <= flTime		// when the time has expired
				 && a < 40 )						// and the flash is at the low point of the cycle
			{
				pdmg->fExpire = 0;

				int y = pdmg->y;
				pdmg->x = pdmg->y = 0;

				// move everyone above down
				for (int j = 0; j < NUM_DMG_TYPES; j++)
				{
					pdmg = &m_dmg[j];
					if ((pdmg->y) && (pdmg->y < y))
						pdmg->y += giDmgHeight;

				}

				m_bitsDamage &= ~giDmgFlags[i];  // clear the bits
			}
		}
	}
}


void CHudHealth::UpdateTiles(float flTime, long bitsDamage)
{	
	DAMAGE_IMAGE *pdmg;

	// Which types are new?
	long bitsOn = ~m_bitsDamage & bitsDamage;
	
	for (int i = 0; i < NUM_DMG_TYPES; i++)
	{
		pdmg = &m_dmg[i];

		// Is this one already on?
		if (m_bitsDamage & giDmgFlags[i])
		{
			pdmg->fExpire = flTime + DMG_IMAGE_LIFE; // extend the duration
			if (!pdmg->fBaseline)
				pdmg->fBaseline = flTime;
		}

		// Are we just turning it on?
		if (bitsOn & giDmgFlags[i])
		{
			// put this one at the bottom
			pdmg->x = giDmgWidth/8;
			pdmg->y = ScreenHeight - giDmgHeight * 2;
			pdmg->fExpire=flTime + DMG_IMAGE_LIFE;
			
			// move everyone else up
			for (int j = 0; j < NUM_DMG_TYPES; j++)
			{
				if (j == i)
					continue;

				pdmg = &m_dmg[j];
				if (pdmg->y)
					pdmg->y -= giDmgHeight;

			}
			pdmg = &m_dmg[i];
		}
	}

	// damage bits are only turned on here;  they are turned off when the draw time has expired (in DrawDamage())
	m_bitsDamage |= bitsDamage;
}


int CHudHealth :: MsgFunc_ClCorpse(const char *pszName, int iSize, void *pbuf)
{
#if 0
	BufferReader reader(pbuf, iSize);

	char szModel[64];

	char *pModel = reader.ReadString();
	Vector origin;
	origin.x = reader.ReadLong() / 128.0f;
	origin.y = reader.ReadLong() / 128.0f;
	origin.z = reader.ReadLong() / 128.0f;
	Vector angles;
	angles.x = reader.ReadCoord();
	angles.y = reader.ReadCoord();
	angles.z = reader.ReadCoord();
	float delay = reader.ReadLong() / 100.0f;
	int sequence = reader.ReadByte();
	int classID = reader.ReadByte();
	int teamID = reader.ReadByte();
	int playerID = reader.ReadByte();

	if( !cl_minmodels->value )
	{
		if( !strstr(pModel, "models/") )
		{
			snprintf(szModel, sizeof(szModel), "models/player/%s/%s.mdl", pModel, pModel );
		}
	}
	else if( teamID == 1 ) // terrorists
	{
		int modelidx = cl_min_t->value;
		if( BIsValidTModelIndex(modelidx) )
			strncpy(szModel, sPlayerModelFiles[modelidx], sizeof(szModel));
		else strncpy(szModel, sPlayerModelFiles[1], sizeof(szModel) ); // set leet.mdl
	}
	else if( teamID == 2 ) // ct
	{
		int modelidx = cl_min_ct->value;

		if( g_PlayerExtraInfo[playerID].vip )
			strncpy( szModel, sPlayerModelFiles[3], sizeof(szModel) ); // vip.mdl
		else if( BIsValidCTModelIndex( modelidx ) )
			strncpy( szModel, sPlayerModelFiles[ modelidx ], sizeof(szModel));
		else strncpy( szModel, sPlayerModelFiles[2], sizeof(szModel) ); // gign.mdl
	}
	else strncpy( szModel, sPlayerModelFiles[0], sizeof(szModel) ); // player.mdl

	CreateCorpse( &origin, &angles, szModel, delay, sequence, classID );
#endif
   return 0;
}

/*
============
CL_IsDead

Returns 1 if health is <= 0
============
*/
bool CL_IsDead()
{
	if( gHUD.m_Health.m_iHealth <= 0 )
		return true;
	return false;
}


////////

DECLARE_MESSAGE(m_Mission_Announcement_Red, Mission_Announcement_Red);
DECLARE_COMMAND(m_Mission_Announcement_Red, CommandActiveMission_Announcement_Red);

void CHudMission_Announcement_Red::UserCmd_CommandActiveMission_Announcement_Red(void) //on spawn
{

gHUD.Announcement_Red = TRUE;

if( g_PlayerExtraInfo[gHUD.m_Scoreboard.m_iPlayerNum].teamnumber == TEAM_TERRORIST )
{
ClientCmd("redwin 1; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; spk vox/mission_success.wav");
}
else 
{
ClientCmd("redwin 1; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; spk vox/mission_fail.wav");
}

}

int CHudMission_Announcement_Red:: MsgFunc_Mission_Announcement_Red(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Mission_Announcement_Red");
	return 1;
}

int CHudMission_Announcement_Red::Init()
{
	gHUD.AddHudElem(this);

HOOK_MESSAGE(Mission_Announcement_Red);
HOOK_COMMAND("Mission_Announcement_Red", CommandActiveMission_Announcement_Red);

m_iFlags = HUD_DRAW;
	return 1;
}


int CHudMission_Announcement_Red::VidInit()
{

R_InitTexture(m_win, "materials/pb/hud/redwin.tga");

return 1;
}

int CHudMission_Announcement_Red::Draw( float flTime )
{

if(gHUD.Announcement_Red)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
m_win->Bind();
DrawUtils::Draw2DQuadScaled(ScreenWidth / 2 - 750 / 2, 5 + 300, ScreenWidth / 2 + 750 / 2, 5 + 450);
}


return 1;
}


//
DECLARE_MESSAGE(m_Mission_Announcement_Blue, Mission_Announcement_Blue);
DECLARE_COMMAND(m_Mission_Announcement_Blue, CommandActiveMission_Announcement_Blue);

void CHudMission_Announcement_Blue::UserCmd_CommandActiveMission_Announcement_Blue(void) //on spawn
{

gHUD.Announcement_Blue = TRUE;

if( g_PlayerExtraInfo[gHUD.m_Scoreboard.m_iPlayerNum].teamnumber == TEAM_TERRORIST )
{
ClientCmd("bluewin 1; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; spk vox/mission_fail.wav");
}
else
{
ClientCmd("bluewin 1; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; wait; spk vox/mission_success.wav");
}

}

int CHudMission_Announcement_Blue:: MsgFunc_Mission_Announcement_Blue(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	ClientCmd("Mission_Announcement_Blue");
	return 1;
}

int CHudMission_Announcement_Blue::Init()
{
	gHUD.AddHudElem(this);

HOOK_MESSAGE(Mission_Announcement_Blue);
HOOK_COMMAND("Mission_Announcement_Blue", CommandActiveMission_Announcement_Blue);

m_iFlags = HUD_DRAW;
	return 1;
}


int CHudMission_Announcement_Blue::VidInit()
{
R_InitTexture(m_win, "materials/pb/hud/bluewin.tga");
return 1;
}

int CHudMission_Announcement_Blue::Draw( float flTime )
{

if(gHUD.Announcement_Blue)
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
m_win->Bind();
DrawUtils::Draw2DQuadScaled(ScreenWidth / 2 - 750 / 2, 5 + 300, ScreenWidth / 2 + 750 / 2, 5 + 450);
}

return 1;
}
