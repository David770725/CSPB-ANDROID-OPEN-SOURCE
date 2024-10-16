#include "hud.h"
#include "cl_util.h"
#include "cl_entity.h"
#include "triangleapi.h"
#include "draw_util.h"
#include "com_model.h"
#include "calcscreen.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#include "triangleapi.h"
#include "eventscripts.h"
#include "health.h"
#include <string.h>
#include "parsemsg.h"
#include "scoreboard.h"
#include "ammohistory.h"

DECLARE_MESSAGE(m_HeadName, HeadName);
DECLARE_COMMAND(m_HeadName, CommandActiveHeadName);

void CHudHeadName::UserCmd_CommandActiveHeadName(void)
{
}

int CHudHeadName::MsgFunc_HeadName(const char *pszName, int iSize, void *pbuf )
{
	/*BufferReader reader( pszName, pbuf, iSize );

//enable = reader.ReadByte();
float x = reader.ReadCoord();
float y = reader.ReadCoord();
float z = reader.ReadCoord();
    
m_TargetOrigin.x = x;
m_TargetOrigin.y = y;
m_TargetOrigin.z = z;

	ClientCmd("HeadName");*/
	return 1;
}

int CHudHeadName::Init(void)
{
	gHUD.AddHudElem(this);

	m_iFlags |= HUD_DRAW;

	return 1;
}

int CHudHeadName::VidInit(void)
{


	return 1;
}

bool CHudHeadName::CheckForPlayer(cl_entity_s *pEnt)
{
	if (pEnt && pEnt->model && pEnt->model->name[0] && pEnt->player)
		return true;

	return false;
}

int CHudHeadName::Draw(float flTime)
{
	if ((gHUD.m_iHideHUDDisplay & HIDEHUD_ALL) || g_iUser1 || !gHUD.cl_headname->value)
		return 1;

for (int i = 1; i < 33; i++)
	{
		if (g_PlayerExtraInfo[i].dead)
			continue;

		if (g_PlayerExtraInfo[i].teamnumber != g_PlayerExtraInfo[gHUD.m_Scoreboard.m_iPlayerNum].teamnumber)
			continue;

		if (i != gHUD.m_Scoreboard.m_iPlayerNum)
		{
			cl_entity_t *ent = gEngfuncs.GetEntityByIndex(i);

			if (!CheckForPlayer(ent))
				continue;

			model_t *model = ent->model;
			vec3_t origin = ent->origin;

			if (model)
				origin.z += max(model->maxs.z, 35.0);

			float screen[2]{ -1,-1 };
			if (!CalcScreen(origin, screen))
				continue;

			int textlen = DrawUtils::HudStringLen(g_PlayerInfoList[i].name);

			//DrawUtils::DrawHudString(screen[0] - textlen * 0.5f, screen[1], gHUD.m_scrinfo.iWidth, g_PlayerInfoList[i].name, 255, 255, 255);

gEngfuncs.pfnDrawSetTextColor(255, 255, 255);
gEngfuncs.pfnDrawConsoleString(screen[0] - textlen * 0.5f, screen[1], g_PlayerInfoList[i].name);

		}
	}

	return 1;
}
