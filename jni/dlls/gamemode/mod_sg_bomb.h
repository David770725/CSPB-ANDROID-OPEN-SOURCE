
#ifndef MOD_SGB_H
#define MOD_SGB_H
#ifdef _WIN32
#pragma once
#endif

#include "mod_base.h"

#include <vector>
#include <utility>

class CMod_Sgb : public IBaseMod
{
public:
	CMod_Sgb() {}

public: // CHalfLifeMultiplay
	BOOL IsTeamplay(void) override { return TRUE; }
	void CheckMapConditions() override;
	void UpdateGameMode(CBasePlayer *pPlayer) override;
void PlayerSpawn(CBasePlayer *pPlayer) override;

protected:
	std::vector<std::pair<CBaseEntity *, Vector>> m_mapBombZones;

public:
	void InstallPlayerModStrategy(CBasePlayer *player) override;
};

#endif
