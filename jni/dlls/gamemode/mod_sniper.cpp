#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "game.h"
#include "globals.h"
#include "trains.h"
#include "bmodels.h"
#include "client.h"
#include "shake.h"

#include "mod_sniper.h"

class CMultiplayGameMgrHelper : public IVoiceGameMgrHelper
{
public:
	virtual bool		CanPlayerHearPlayer(CBasePlayer *pListener, CBasePlayer *pTalker)
	{
		if (g_pGameRules->IsTeamplay())
		{
			if (g_pGameRules->PlayerRelationship(pListener, pTalker) != GR_TEAMMATE)
			{
				return false;
			}
		}

		return true;
	}
};
static CMultiplayGameMgrHelper g_GameMgrHelper;

void CMod_TeamDeathMatchSniper::InstallPlayerModStrategy(CBasePlayer *player)
{
	class MyPlayerModStrategy : public CPlayerModStrategy_Default
	{
	public:
		MyPlayerModStrategy(CBasePlayer *player) : CPlayerModStrategy_Default(player) {}
		bool CanPlayerBuy(bool display) override { return true; }
	};

	std::unique_ptr<MyPlayerModStrategy> up(new MyPlayerModStrategy(player));
	player->m_pModStrategy = std::move(up);
}

CMod_TeamDeathMatchSniper::CMod_TeamDeathMatchSniper()
{
	m_VoiceGameMgr.Init(&g_GameMgrHelper, gpGlobals->maxClients);

	m_flIntermissionEndTime = 0;
	m_flIntermissionStartTime = 0;

	m_iMaxRoundsWon = (int)maxkills.value;
}


void CMod_TeamDeathMatchSniper::Think(void)
{
	m_VoiceGameMgr.Update(gpGlobals->frametime);\

	///// Check game rules /////

	if (CheckGameOver())   // someone else quit the game already
		return;
	
	if (CheckTimeLimit())
		return;

	m_iTotalRoundsPlayed = m_iNumCTWins + m_iNumTerroristWins; // hack
	/*if (CheckMaxRounds())
		return;
	*/
	if (CheckWinLimit())
		return;
	
	
	if (IsFreezePeriod())
	{
		CheckFreezePeriodExpired();
	}

	CheckLevelInitialized();

	if (gpGlobals->time > m_tmNextPeriodicThink)
	{
		CheckRestartRound();
		m_tmNextPeriodicThink = gpGlobals->time + 1.0f;

		

		if (g_psv_friction->value != 4.0f)
		{
			CVAR_SET_FLOAT("sv_friction", 4.0);
		}

		if (g_psv_stopspeed->value != 75.0f)
		{
			CVAR_SET_FLOAT("sv_stopspeed", 75.0);
		}

		
		m_iMaxRoundsWon = (int)maxkills.value;

		if (m_iMaxRoundsWon < 0)
		{
			m_iMaxRoundsWon = 0;
			CVAR_SET_FLOAT("mp_maxkills", 0);
		}
	}

	for (int iIndex = 1; iIndex <= gpGlobals->maxClients; ++iIndex)
	{
		CBaseEntity *entity = UTIL_PlayerByIndex(iIndex);

		if (!entity)
			continue;

		CBasePlayer *player = static_cast<CBasePlayer *>(entity);

		if (player->pev->deadflag != DEAD_DEAD && player->pev->deadflag != DEAD_RESPAWNABLE)
			continue;

		if (player->m_iTeam == TEAM_UNASSIGNED  || player->m_iTeam == TEAM_SPECTATOR)
			continue;

		if(gpGlobals->time < player->m_fDeadTime + 5.0f)
			continue;

		player->RoundRespawn();
	}
}

void CMod_TeamDeathMatchSniper::PlayerKilled(CBasePlayer *pVictim, entvars_t *pKiller, entvars_t *pInflictor)
{
	IBaseMod::PlayerKilled(pVictim, pKiller, pInflictor);

	CBasePlayer *peKiller = NULL;
	CBaseEntity *ktmp = CBaseEntity::Instance(pKiller);

	if (ktmp && ktmp->Classify() == CLASS_PLAYER)
	{
		peKiller = static_cast<CBasePlayer *>(ktmp);
	}
	else if (ktmp && ktmp->Classify() == CLASS_VEHICLE)
	{
		CBasePlayer *pDriver = static_cast<CBasePlayer *>(((CFuncVehicle *)ktmp)->m_pDriver);

		if (pDriver != NULL)
		{
			pKiller = pDriver->pev;
			peKiller = static_cast<CBasePlayer *>(pDriver);
		}
	}
	if (peKiller && peKiller->IsPlayer())
	{
		if (pVictim->m_iTeam != peKiller->m_iTeam)
		{
			switch (peKiller->m_iTeam)
			{
			case TEAM_CT:
				++m_iNumCTWins;
				break;
			case TEAM_TERRORIST:
				++m_iNumTerroristWins;
				break;
			default:
				// ?
				break;
			}
			UpdateTeamScores();
		}
	}

	// TODO: RespawnBar.
}

BOOL CMod_TeamDeathMatchSniper::FPlayerCanTakeDamage(CBasePlayer *pPlayer, CBaseEntity *pAttacker)
{
	if (pAttacker && PlayerRelationship(pPlayer, pAttacker) == GR_TEAMMATE)
	{
		// my teammate hit me.
		if ((friendlyfire.value == 0) && (pAttacker != pPlayer))
		{
			// friendly fire is off, and this hit came from someone other than myself,  then don't get hurt
			return FALSE;
		}
	}



	return CHalfLifeMultiplay::FPlayerCanTakeDamage(pPlayer, pAttacker);
}

int CountTeamPlayersSnip(int iTeam)
{
	CBaseEntity *pPlayer = NULL;
	int i = 0;

	while ((pPlayer = UTIL_FindEntityByClassname(pPlayer, "player")) != NULL)
	{
		if (FNullEnt(pPlayer->edict()))
			break;

		if (pPlayer->pev->flags & FL_DORMANT)
			continue;

		if (GetClassPtr<CBasePlayer>(pPlayer->pev)->m_iTeam == iTeam)
			++i;
	}

	return i;
}

BOOL CMod_TeamDeathMatchSniper::FPlayerCanRespawn(CBasePlayer *pPlayer)
{
CHalfLifeMultiplay *mp = g_pGameRules;

if (gpGlobals->time < pPlayer->m_fDeadTime + 1)

#ifndef CLIENT_DLL
pPlayer->SetProgressBarTime(4);
#endif

CLIENT_COMMAND(pPlayer->edict(), "Respawning\n");

mp->m_iNumCT = CountTeamPlayersSnip(CT);
mp->m_iNumTerrorist = CountTeamPlayersSnip(TERRORIST);

{
return FALSE;
}

	if (pPlayer->m_iMenu == Menu_ChooseAppearance)
	{
		return FALSE;
	}

	return TRUE;
}

void CMod_TeamDeathMatchSniper::UpdateGameMode(CBasePlayer *pPlayer)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgGameMode, NULL, pPlayer->edict());
	WRITE_BYTE(MOD_TDM);
	WRITE_BYTE(0); // Reserved. (weapon restriction? )
	WRITE_BYTE(maxkills.value); // MaxRound (mp_roundlimit)
	WRITE_BYTE(0); // Reserved. (MaxTime?)
	MESSAGE_END();

CLIENT_COMMAND(pPlayer->edict(), "Count_unit; Mode_ui\n");
}


void CMod_TeamDeathMatchSniper::PlayerSpawn(CBasePlayer *pPlayer)
{

	IBaseMod::PlayerSpawn(pPlayer);
	pPlayer->AddAccount(16000);
	// Give Armor
	pPlayer->m_iKevlar = ARMOR_TYPE_HELMET;
	pPlayer->pev->armorvalue = 100;
	pPlayer->SpawnProtection_Start(5.0f);

RemoveGuns();
}
