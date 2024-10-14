#include "hud.h"
#include "cl_util.h"
#include "draw_util.h"
#include "triangleapi.h"

#include "hud_scoreboard_legacy.h"

#include "gamemode/mods_const.h"


CHudScoreBoardLegacy::CHudScoreBoardLegacy()
{
	
}

CHudScoreBoardLegacy::~CHudScoreBoardLegacy()
{
	
}

int CHudScoreBoardLegacy::VidInit(void)
{
	m_iOriginalBG = gHUD.GetSpriteIndex("SBOriginalBG");
	m_iTeamDeathBG = gHUD.GetSpriteIndex("SBTeamDeathBG");
	m_iUnitehBG = gHUD.GetSpriteIndex("SBUnitehBG");
	m_iNum_S = gHUD.GetSpriteIndex("SBNum_S");
	m_iText_CT = gHUD.GetSpriteIndex("SBText_CT");
	m_iText_T = gHUD.GetSpriteIndex("SBText_T");
	m_iText_TR = gHUD.GetSpriteIndex("SBText_TR");
	m_iText_HM = gHUD.GetSpriteIndex("SBText_HM");
	m_iText_ZB = gHUD.GetSpriteIndex("SBText_ZB");
	m_iText_1st = gHUD.GetSpriteIndex("SBText_1st");
	m_iText_Kill = gHUD.GetSpriteIndex("SBText_Kill");
	m_iText_Round = gHUD.GetSpriteIndex("SBText_Round");

	
	BuildHudNumberRect(m_iNum_S, m_rcNumber_Small, 10, 10, 1, 1);

R_InitTexture(board[0], "gfx/billflx/board/red");
R_InitTexture(board[1], "gfx/billflx/board/blue");

m_iNum_L_ammo = gHUD.GetSpriteIndex("upboard_num");
m_iNum_S_ammo = gHUD.GetSpriteIndex("SBNum_S");

BuildHudNumberRect(m_iNum_L_ammo, m_rcNumber_Large_ammo, 30, 55, 1, 1);
BuildHudNumberRect(m_iNum_S_ammo, m_rcNumber_Small_ammo, 10, 10, 1, 1);

m_iNum_L = gHUD.GetSpriteIndex("SBNum_L");
BuildHudNumberRect(m_iNum_L, m_rcNumber_Large, 13, 13, 1, 1);


	return 1;
}

int CHudScoreBoardLegacy::Draw(float flTime)
{

	HSPRITE bgSprite = gHUD.GetSprite(m_iBGIndex);
	wrect_t bgRect = gHUD.GetSpriteRect(m_iBGIndex);
	int bgHeight = (bgRect.bottom - bgRect.top);
	int bgWidth = (bgRect.right - bgRect.left);
	int bgY = 2;
	int bgX = (ScreenWidth - bgWidth) / 2;

	int aliveCT = gHUD.m_Scoreboard.m_iTeamAlive_CT;
	int aliveT = gHUD.m_Scoreboard.m_iTeamAlive_T;
	int textWidth_CTAlive = GetHudNumberWidth(m_iNum_S, m_rcNumber_Small, DHN_2DIGITS | DHN_DRAWZERO, aliveCT);
	int textWidth_TAlive = GetHudNumberWidth(m_iNum_S, m_rcNumber_Small, DHN_2DIGITS | DHN_DRAWZERO, aliveT);
	int scoreCT = gHUD.m_Scoreboard.m_iTeamScore_CT;
	int scoreT = gHUD.m_Scoreboard.m_iTeamScore_T;
	int scoreMax = gHUD.m_Scoreboard.m_iTeamScore_Max;
	int roundNumber = scoreMax ? scoreMax : scoreT + scoreCT + 1;
	int iFlags = DHN_DRAWZERO; // draw 0 values

int textWidth_T = GetHudNumberWidth(m_iNum_S, m_rcNumber_Small, DHN_2DIGITS | DHN_DRAWZERO, scoreT);
int textWidth_CT = GetHudNumberWidth(m_iNum_S, m_rcNumber_Small, DHN_4DIGITS | DHN_3DIGITS | DHN_2DIGITS | DHN_DRAWZERO, scoreCT);

int currentRound= GetHudNumberWidth(m_iNum_S, m_rcNumber_Small, DHN_4DIGITS | DHN_3DIGITS | DHN_2DIGITS | DHN_DRAWZERO, scoreCT+scoreT);

int x = ScreenWidth / 2;
int y = 1;
int iLength, iHeight;

if( g_PlayerExtraInfo[gHUD.m_Scoreboard.m_iPlayerNum].teamnumber == TEAM_TERRORIST )
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
board[0]->Bind();
DrawUtils::Draw2DQuadScaled(x - 380 / 2,y, x + 380 / 2, y + 56);
}
else
{
gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);
gEngfuncs.pTriAPI->Color4ub(255, 255, 255, 255);
board[1]->Bind();
DrawUtils::Draw2DQuadScaled(x - 380 / 2,y, x + 380 / 2, y + 56);
}


//round 
int textWidth = GetHudNumberWidth(m_iNum_S_ammo, m_rcNumber_Small_ammo, DHN_2DIGITS | DHN_DRAWZERO, roundNumber);

if (gHUD.m_iModRunning != MOD_NONE) //tdm
{
if (textWidth > 0)
{
x = DrawUtils::DrawHudNumber2((ScreenWidth - textWidth) / 2 - 17, bgY + 10, true,3, roundNumber, 255, 255, 0);
}
}
else //bomb mission 
{
gEngfuncs.pfnDrawSetTextColor(255, 255, 255);
gEngfuncs.pfnDrawConsoleString(x - 30 / 2,y+5, "Round");

int num = GetHudNumberWidth(m_iNum_L, m_rcNumber_Large, DHN_2DIGITS | DHN_DRAWZERO, roundNumber);

if (num > 0)
{
DrawHudNumberBill2(m_iNum_L, m_rcNumber_Large, x - 0.5/ 2, y + 30, DHN_2DIGITS | DHN_DRAWZERO, roundNumber, 160, 160, 160);

gEngfuncs.pfnDrawConsoleString(x - 1 / 2,y+30, "/");

DrawUtils::DrawHudNumber2(x - 85 / 2, y + 20,false,1, scoreCT + scoreT + 1, 255, 215, 0);
DrawUtils::DrawHudRound(x - 40 / 2, y + 22,false,1, 0, 255, 215, 0);
}
}



//y↑↓ x←→

if (textWidth_T > 0)
DrawUtils::DrawHudNumber2((ScreenWidth) / 2 - 135, bgY + 16,true,3, scoreT, 255, 255, 255);


if (textWidth_CT > 0)
DrawUtils::DrawHudNumber2(((ScreenWidth) / 2) + 95 - (textWidth_CT / 2), bgY + 16,true,3, scoreCT, 255, 255, 255);

	return 1;
}

void CHudScoreBoardLegacy::Reset(void)
{
	m_iBGIndex = m_iOriginalBG;
	m_iTextIndex = m_iText_Round;
	m_iTTextIndex = m_iText_TR;
	m_iCTTextIndex = m_iText_CT;

	switch (gHUD.m_iModRunning)
	{
	case MOD_NONE:
	{
		// nothing to change
		break;
	}
	case MOD_TDM:
	{
		m_iBGIndex = m_iTeamDeathBG;
		m_iTextIndex = m_iText_Kill;
		break;
	}
	case MOD_DM:
	{
		m_iBGIndex = m_iTeamDeathBG;
		m_iTextIndex = m_iText_Kill;
		m_iTTextIndex = m_iText_1st;
		m_iCTTextIndex = m_iText_Kill;
		break;
	}
	case MOD_ZB3:
	case MOD_ZB2:
	case MOD_ZB1:
	{
		m_iTTextIndex = m_iText_ZB;
		m_iCTTextIndex = m_iText_HM;
		break;
	}
	case MOD_ZBS:
	{
		// already drawn in zbs/zbs_scoreboard.cpp
		m_iBGIndex = -1;
		break;
	}
	default:
	{
		// shut clang warnings
		break;
	}
	}
}


void CHudScoreBoardLegacy::BuildHudNumberRect(int moe, wrect_t *prc, int w, int h, int xOffset, int yOffset)
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

int CHudScoreBoardLegacy::DrawHudNumberBill2(int moe, wrect_t *prc, int x, int y, int iFlags, int iNumber, int r, int g, int b)
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

int CHudScoreBoardLegacy::GetHudNumberWidth(int moe, wrect_t *prc, int iFlags, int iNumber)
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

