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
// Geiger.cpp
//
// implementation of CHudAmmo class
//

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#include "hud.h"
#include "cl_util.h"
#include "cl_entity.h"
#include "triangleapi.h"
#include "draw_util.h"
#include "com_model.h"
#include "calcscreen.h"
#include "ammo.h"
#include "eventscripts.h"
#include "health.h"
#include <string.h>
#include "parsemsg.h"
#include "scoreboard.h"
#include "ammohistory.h"

//New
#include "followicon.h"
#include "ammohistory.h"
#include "moe/moe_touch.h"

#include <vector>
#include <algorithm>

#define XPOS( x ) ( (x) / 16.0f )
#define YPOS( y ) ( (y) / 10.0f  )

#define INT_XPOS(x) int(XPOS(x) * ScreenWidth)
#define INT_YPOS(y) int(YPOS(y) * ScreenHeight)

DECLARE_MESSAGE( m_Background, ImgFade )
DECLARE_COMMAND(m_Background, Cmd1)

int CHudBackground::Init(void)
{
	HOOK_MESSAGE(ImgFade);
	
	HOOK_COMMAND("notice1", Cmd1); //Ct
	
	gHUD.AddHudElem(this);
	m_iFlags |= HUD_DRAW;

	return 1;
}

void CHudBackground::UserCmd_Cmd1(void)
{
	ffade = 255;
	m_fFade = 8.0f; 

}


int CHudBackground:: MsgFunc_ImgFade(const char *pszName, int iSize, void *pbuf )
{
	BufferReader reader( pszName, pbuf, iSize );
	
	ClientCmd("notice1");
	
	return 1;
}

int CHudBackground::VidInit(void)
{
	R_InitTexture(m_dmg, "materials/pb/hud/damage");
	
	return 1;
}

int CHudBackground::Draw(float flTime)
{
	int a, x, y, r, g, b;
	int alphaBalance;
	int alphaBalance2;
	int alphaBalance3;
	int alphaBalance4;
	int alphaBalance5;
	int alphaBalance6;
	int alphaBalance7;
	int alphaBalance8;
	int alphaBalance9;
	int alphaBalance10;
	
	int alphaStatic;
	int alphaStatic2;
	int alphaStatic3;
	int alphaStatic4;
	int alphaStatic5;
	//
	
	m_fFade -= gHUD.m_flTimeDelta;
	if( m_fFade < 0)
	{
		m_fFade = 0.0f;
	}
	
	float interpolate2 = ( 5 - m_fFade ) / 5;
	alphaBalance = 255 - interpolate2 * 255;
	//
	
	float interpolate = ( 5 - m_fFade2 ) / 5;
	alphaBalance2 = 255 - interpolate * 255;
		
	a = max( MIN_ALPHA, (int)m_fFade );
	
	y = ScreenHeight - gHUD.m_iFontHeight - gHUD.m_iFontHeight/2;
	
	DrawUtils::UnpackRGB(r, g, b, RGB_YELLOWISH);
	DrawUtils::ScaleColors(r, g, b, a);
	
    x = ScreenWidth/6.2;
    y = 92;
    
    if(alphaBalance < 255)
    alphaStatic = alphaBalance;
    else
    alphaStatic = 255;
	
	gEngfuncs.pTriAPI->RenderMode(kRenderTransTexture);
	m_dmg->Bind();
	gEngfuncs.pTriAPI->Color4ub(255, 255, 255, alphaStatic);
	DrawUtils::Draw2DQuad( (INT_XPOS(0) + 0) * gHUD.m_flScale, (INT_YPOS(0) * 0) * gHUD.m_flScale,(INT_XPOS(15.8) + 0 + gHUD.GetCharHeight() ) * gHUD.m_flScale,(INT_YPOS(22) * 0.5 + gHUD.GetCharHeight() ) * gHUD.m_flScale );
		
	return 1;
}
