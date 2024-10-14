/*
billflx 2023
*/

#ifndef SERVER_TO_CLIENT_H
#define SERVER_TO_CLIENT_H

#include <player.h>

#ifdef _WIN32
#pragma once
#endif

class CServerClient : public CBaseMonster
{
public:

CBasePlayer *player = GetClassPtr<CBasePlayer>(pev);


};

#endif
