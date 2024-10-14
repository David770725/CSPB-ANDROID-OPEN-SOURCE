
#pragma once

#include "hud_sub.h"

class CHudScoreBoardLegacy : public IBaseHudSub
{
public:
	CHudScoreBoardLegacy();
	~CHudScoreBoardLegacy() override;
	int VidInit(void) override;
	int Draw(float time) override;
	void Reset(void) override;		// called every time a server is connected to

protected:
	void BuildHudNumberRect(int moe, wrect_t *prc, int w, int h, int xOffset, int yOffset);
	int DrawHudNumberBill2(int moe, wrect_t *prc, int x, int y, int iFlags, int iNumber, int r, int g, int b);
	int GetHudNumberWidth(int moe, wrect_t *prc, int iFlags, int iNumber);

private:
	int m_iBGIndex;
	int m_iTextIndex;
	int m_iTTextIndex, m_iCTTextIndex;

	wrect_t m_rcNumber_Large[10];
	wrect_t m_rcNumber_Small[10];

wrect_t m_rcNumber_Large_ammo[10];
wrect_t m_rcNumber_Small_ammo[10];
int m_iNum_L_ammo;
int m_iNum_S_ammo;

UniqueTexture board[2];

	int m_iOriginalBG;
	int m_iTeamDeathBG;
	int m_iUnitehBG;
	int m_iNum_L;
	int m_iNum_S;
	int m_iText_CT;
	int m_iText_T;
	int m_iText_TR;
	int m_iText_HM;
	int m_iText_ZB;
	int m_iText_1st;
	int m_iText_Kill;
	int m_iText_Round;
};
