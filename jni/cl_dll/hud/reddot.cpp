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

int CHudRedDot::Init()
{
	gHUD.AddHudElem(this);
	m_iFlags = HUD_DRAW;
	return 1;
}

int CHudRedDot::VidInit()
{
	R_InitTexture(m_iReddotArc[0], "gfx/sight/reddot/scope_arc_nw.tga");
	R_InitTexture(m_iReddotArc[1], "gfx/sight/reddot/scope_arc_nw.tga");
	R_InitTexture(m_iReddotArc[2], "gfx/sight/reddot/scope_arc_nw.tga");
	R_InitTexture(m_iReddotArc[3], "gfx/sight/reddot/scope_arc_nw.tga");

	left = (TrueWidth - TrueHeight)/2;
	right = left + TrueHeight;
	centerx = TrueWidth/2;
	centery = TrueHeight/2;
	return 1;
}

int CHudRedDot::Draw(float flTime)
{
	if(gHUD.m_iFOV > 55)
{
		return 1;
	gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
	gEngfuncs.pTriAPI->Brightness(1.0);
	gEngfuncs.pTriAPI->Color4ub(0, 0, 0, 255);
}
else if(gHUD.m_iFOV > 40)
{
		return 1;
	gEngfuncs.pTriAPI->RenderMode(kRenderTransColor);
	gEngfuncs.pTriAPI->Brightness(1.0);
	gEngfuncs.pTriAPI->Color4ub(0, 0, 0, 0);
}
	gEngfuncs.pTriAPI->CullFace(TRI_NONE);

	m_iReddotArc[0]->Bind();
	DrawUtils::Draw2DQuad(left, 0, centerx, centery);

	m_iReddotArc[1]->Bind();
	DrawUtils::Draw2DQuad(centerx, 0, right, centery);

	m_iReddotArc[2]->Bind();
	DrawUtils::Draw2DQuad(centerx, centery, right, TrueHeight);

	m_iReddotArc[3]->Bind();
	DrawUtils::Draw2DQuad(left, centery, centerx, TrueHeight);

	FillRGBABlend( 0, 0, (ScreenWidth - ScreenHeight) / 2 + 2, ScreenHeight, 0, 0, 0, 255 );
	FillRGBABlend( (ScreenWidth - ScreenHeight) / 2 - 2 + ScreenHeight, 0, (ScreenWidth - ScreenHeight) / 2 + 2, ScreenHeight, 0, 0, 0, 255 );

	FillRGBABlend(0,                  ScreenHeight/2, ScreenWidth/2 - 20, 1,  0, 0, 0, 255);
	FillRGBABlend(ScreenWidth/2 + 20, ScreenHeight/2, ScreenWidth       , 1,  0, 0, 0, 255);

	FillRGBABlend(ScreenWidth/2, 0                  , 1, ScreenHeight/2 - 20, 0, 0, 0, 255);
	FillRGBABlend(ScreenWidth/2, ScreenHeight/2 + 20, 1, ScreenHeight       , 0, 0, 0, 255);

	return 0;
}

void CHudRedDot::Shutdown()
{
	std::fill(std::begin(m_iReddotArc), std::end(m_iReddotArc), nullptr);
}
