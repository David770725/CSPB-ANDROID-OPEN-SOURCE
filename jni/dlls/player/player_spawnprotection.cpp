#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "gamerules.h"
#include "client.h"
#include "game.h"
#include "globals.h"
#include "trains.h"
#include "bmodels.h"
#include "gamerules.h"


void CBasePlayer::SpawnProtection_Check()
{
	if (!m_bSpawnProtection)
		return;
	if (gpGlobals->time > m_flTimeSpawnProctionExpires)
	{
		SpawnProtection_End();

	}
}

void CBasePlayer::SpawnProtection_Start(float flTime)
{
	m_bSpawnProtection = true;
	m_flTimeSpawnProctionExpires = gpGlobals->time + flTime;

	
//pev->rendermode = kRenderTransAlpha;
pev->renderfx = kRenderFxGlowShell;
pev->rendercolor = { 255,255,255 };

	pev->renderamt = 1;
	pev->takedamage = DAMAGE_NO;

}

void CBasePlayer::SpawnProtection_End()
{
	m_bSpawnProtection = false;
	pev->renderfx = kRenderFxNone;
	pev->takedamage = DAMAGE_AIM;
}




//inventory 
void CBasePlayer::inventory_Check()
{
	;
}

void CBasePlayer::inventory_Start(float flTime)
{

;
}

void CBasePlayer::inventory_End()
{
	;

}
