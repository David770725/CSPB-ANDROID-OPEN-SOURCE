
#ifndef MOD_NONE_H
#define MOD_NONE_H
#ifdef _WIN32
#pragma once
#endif

#include "mod_base.h"

#include <vector>
#include <utility>

class CMod_None : public IBaseMod
{
public:
	CMod_None() {}

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


//sniper bomb
#ifndef MOD_SNIPERB_H
#define MOD_SNIPERB_H
#ifdef _WIN32
#pragma once
#endif

#include <vector>
#include <utility>

class CMod_SniperB : public IBaseMod
{
public:
	CMod_SniperB() {}

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


//sniper bomb
#ifndef MOD_knifeB_H
#define MOD_knifeB_H
#ifdef _WIN32
#pragma once
#endif

#include <vector>
#include <utility>

class CMod_knifeB : public IBaseMod
{
public:
	CMod_knifeB() {}

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
