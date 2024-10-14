/*
nvg.cpp - Night Vision Googles
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
#include "cl_util.h"
#include "parsemsg.h"
#include "r_efx.h"
#include "dlight.h"
#include "eventscripts.h"

DECLARE_MESSAGE(m_NVG, NVGToggle)
DECLARE_COMMAND(m_NVG, NVGAdjustDown)
DECLARE_COMMAND(m_NVG, NVGAdjustUp)

int CHudNVG::Init()
{
	HOOK_MESSAGE(NVGToggle)
	HOOK_COMMAND("+nvgadjust", NVGAdjustUp);
	HOOK_COMMAND("-nvgadjust", NVGAdjustDown);

	cl_fancy_nvg = CVAR_CREATE( "cl_fancy_nvg", "0", FCVAR_ARCHIVE );

	gHUD.AddHudElem(this);
	m_iFlags = 0;
	m_iAlpha = 110; // 220 is max, 30 is min

	m_LightStypeBackup = -1.0f;

   return 0;
}

int CHudNVG::VidInit(void)
{
	m_LightStypeBackup = -1.0f;
	return 0;
}

int CHudNVG::Draw(float flTime)
{
	if( gEngfuncs.IsSpectateOnly() )
	{
		return 1;
	}

	int r = 50, g = 225, b = 50, a = m_iAlpha;
	bool bNewLight = false;
	int idx = gEngfuncs.GetLocalPlayer()->index;
	if (IS_FIRSTPERSON_SPEC)
		idx = g_iUser2;

	if (g_PlayerExtraInfo[idx].zombie)
	{
		r = 225, g = 50, b = 50, a = 110;
		bNewLight = true;
	}

	gEngfuncs.pfnFillRGBABlend(0, 0, ScreenWidth, ScreenHeight, r, g, b, a);
	gEngfuncs.pfnFillRGBA(0, 0, ScreenWidth, ScreenHeight, 0, 90, 0, rand() % 10 + 50);

	if (bNewLight)
	{
		
	}
	// draw a dynamic light on player's origin
	else if (cl_fancy_nvg->value)
	{
		// recreate new dlight every frame

		dlight_t *dl = gEngfuncs.pEfxAPI->CL_AllocDlight(0);
		dl->origin = gHUD.m_vecOrigin;
		dl->radius = Com_RandomLong(750, 800);
		dl->die = flTime + 0.1f;
		dl->color.r = r;
		dl->color.g = g;
		dl->color.b = b;
	}
	else
	{
		// recreate if died
		if (!m_pLight || m_pLight->die < flTime)
		{
			m_pLight = gEngfuncs.pEfxAPI->CL_AllocDlight(0);

			// I hope no one is crazy so much to keep NVG for 9999 seconds
			m_pLight->die = flTime + 9999.0f;
			m_pLight->color.r = r;
			m_pLight->color.g = g;
			m_pLight->color.b = b;
		}

		// just update origin
		if (m_pLight)
		{
			m_pLight->origin = gHUD.m_vecOrigin;
			m_pLight->radius = Com_RandomLong(750, 800);
		}
	}
	

	
	return 1;
}

int CHudNVG::MsgFunc_NVGToggle(const char *pszName, int iSize, void *pbuf)
{
	BufferReader reader( pszName, pbuf, iSize );

	bool bDraw = reader.ReadByte();

	m_iFlags = bDraw ? HUD_DRAW : 0;

	if( m_pLight )
	{
		m_pLight->die = 0; // engine will remove this immediately

		m_pLight = NULL; // it's safe to set it 0 now
	}

	if (g_iXash)
	{
		if (m_LightStypeBackup < 0)
			m_LightStypeBackup = gRenderAPI.GetLightStyle(0)->map[0];

		if (bDraw)
		{
			gRenderAPI.GetLightStyle(0)->map[0] = 64;
		}
		else
		{
			gRenderAPI.GetLightStyle(0)->map[0] = m_LightStypeBackup;
		}
	}

	return 1;
}

void CHudNVG::UserCmd_NVGAdjustDown()
{
	m_iAlpha = max( 220, m_iAlpha + 20 );
}

void CHudNVG::UserCmd_NVGAdjustUp()
{
	m_iAlpha = min( 30, m_iAlpha - 20 );
}
