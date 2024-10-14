#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "game.h"
#include "client.h"

#include "bmodels.h"
#include "player/player_mod_strategy.h"

#include "mod_sg_bomb.h"

#include <algorithm>

void CMod_Sgb::CheckMapConditions()
{
	IBaseMod::CheckMapConditions();
	m_mapBombZones.clear();
	if (m_bMapHasBombZone)
	{
		CBaseEntity *pEntity = nullptr;

		while ((pEntity = UTIL_FindEntityByClassname(pEntity, "func_bomb_target")))
		{
			m_mapBombZones.emplace_back(pEntity, VecBModelOrigin(pEntity->pev));
		}
		// pEntity = nullptr;
		while ((pEntity = UTIL_FindEntityByClassname(pEntity, "info_bomb_target")))
		{
			m_mapBombZones.emplace_back(pEntity, pEntity->pev->origin);
		}

		using EVpair_t = decltype(m_mapBombZones)::value_type;
		std::sort(m_mapBombZones.begin(), m_mapBombZones.end(), [](const EVpair_t &a, const EVpair_t &b) {return a.first->eoffset() < b.first->eoffset(); });
	}
}

void CMod_Sgb::UpdateGameMode(CBasePlayer *pPlayer)
{
	MESSAGE_BEGIN(MSG_ONE, gmsgGameMode, NULL, pPlayer->edict());
	WRITE_BYTE(MOD_NONE);
	WRITE_BYTE(0); // Reserved. (weapon restriction? )
	WRITE_BYTE(maxrounds.value); // MaxRound (mp_roundlimit)
	WRITE_BYTE(0); // Reserved. (MaxTime?)

	WRITE_BYTE(m_mapBombZones.size());
	for (const auto& EV : m_mapBombZones)
	{
		const Vector &pos(EV.second);
		WRITE_COORD(pos[0]);
		WRITE_COORD(pos[1]);
		WRITE_COORD(pos[2]);
	}

	MESSAGE_END();

CLIENT_COMMAND(pPlayer->edict(), "Count_unit; Mode_ui\n");
}

void CMod_Sgb::InstallPlayerModStrategy(CBasePlayer *player)
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

void CMod_Sgb::PlayerSpawn(CBasePlayer *pPlayer)
{

	IBaseMod::PlayerSpawn(pPlayer);
	pPlayer->AddAccount(16000);
	// Give Armor
	pPlayer->m_iKevlar = ARMOR_TYPE_HELMET;
	pPlayer->pev->armorvalue = 100;
	pPlayer->SpawnProtection_Start(5.0f);
RemoveGuns();
}

