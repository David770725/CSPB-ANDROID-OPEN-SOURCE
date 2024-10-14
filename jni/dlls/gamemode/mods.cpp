/*
mods.cpp - CSMoE Server Gameplay : gamemode object factory
Copyright (C) 2018 Moemod Hyakuya

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/

#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "player.h"
#include "mods.h"

#include <tuple>
#include <type_traits>

#include "mod_none.h"
#include "mod_tdm.h"

#include "mod_m3.h"
#include "mod_sg.h"
#include "mod_knife.h"
#include "mod_sniper.h"
#include "mod_sg_bomb.h"


IBaseMod *g_pModRunning = nullptr;

template<class T>
IBaseMod *DefaultFactory()
{
	return new T;
}

std::pair<const char *, IBaseMod *(*)()> g_FindList[] = {
	{ "", DefaultFactory<CMod_None> }, // default
	{ "", DefaultFactory<CMod_None> }, // BTE_MOD_CS16
	{ "none", DefaultFactory<CMod_None> }, // BTE_MOD_NONE
	{ "tdm", DefaultFactory<CMod_TeamDeathMatch> },
{ "m3", DefaultFactory<CMod_M3> },
	{ "sg", DefaultFactory<CMod_TeamDeathMatchSG> },
	{ "knife", DefaultFactory<CMod_TeamDeathMatchKnife> },
	{ "sniper", DefaultFactory<CMod_TeamDeathMatchSniper> },
{ "sgb", DefaultFactory<CMod_Sgb> },
	{ "sniperb", DefaultFactory<CMod_SniperB> },
	{ "knifeb", DefaultFactory<CMod_knifeB> },
};

void InstallBteMod(const char *name)
{
	for (auto p : g_FindList)
	{
		if (!strcasecmp(name, p.first))
		{
			g_pModRunning = p.second();
			return;
		}
	}
	g_pModRunning = g_FindList[0].second(); // default
	return;
}
