/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#include "events.h"

int g_iRShell, g_iPShell, g_iBlackSmoke, g_iShotgunShell;


//extern "C"

	DECLARE_EVENT(FireAK47);
	DECLARE_EVENT(FireAUG);
	DECLARE_EVENT(FireAWP);
	DECLARE_EVENT(CreateExplo);
	DECLARE_EVENT(CreateSmoke);
	DECLARE_EVENT(FireDEAGLE);
	DECLARE_EVENT(DecalReset);
	DECLARE_EVENT(FireEliteLeft);
	DECLARE_EVENT(FireEliteRight);
	DECLARE_EVENT(FireFAMAS);
	DECLARE_EVENT(Fire57);
	DECLARE_EVENT(FireG3SG1);
	DECLARE_EVENT(FireGALIL);
	DECLARE_EVENT(Fireglock18);
	DECLARE_EVENT(Knife);
	DECLARE_EVENT(FireM249);
	DECLARE_EVENT(FireM3);
	DECLARE_EVENT(FireM4A1);
	DECLARE_EVENT(FireMAC10);
	DECLARE_EVENT(FireMP5);
	DECLARE_EVENT(FireMP7);
	DECLARE_EVENT(FireP228);
	DECLARE_EVENT(FireP90);
	DECLARE_EVENT(FireScout);
	DECLARE_EVENT(FireSG550);
	DECLARE_EVENT(FireSG552);
	DECLARE_EVENT(FireTMP);
	DECLARE_EVENT(FireUMP45);
	DECLARE_EVENT(FireUSP);
	DECLARE_EVENT(Vehicle);
	DECLARE_EVENT(FireXM1014);
	DECLARE_EVENT(TrainPitchAdjust);
/*
======================
Game_HookEvents

Associate script file name with callback functions.  Callback's must be extern "C" so
 the engine doesn't get confused about name mangling stuff.  Note that the format is
 always the same.  Of course, a clever mod team could actually embed parameters, behavior
 into the actual .sc files and create a .sc file parser and hook their functionality through
 that.. i.e., a scripting system.

That was what we were going to do, but we ran out of time...oh well.
======================
*/
void Game_HookEvents( void )
{
	HOOK_EVENT( ak47, FireAK47 );
	HOOK_EVENT( aug, FireAUG );
	HOOK_EVENT( awp, FireAWP );
	HOOK_EVENT( createexplo, CreateExplo );
	HOOK_EVENT( createsmoke, CreateSmoke );
	HOOK_EVENT( deagle, FireDEAGLE );
	HOOK_EVENT( decal_reset, DecalReset );
	HOOK_EVENT( elite_left, FireEliteLeft );
	HOOK_EVENT( elite_right, FireEliteRight );
	HOOK_EVENT( famas, FireFAMAS );
	HOOK_EVENT( fiveseven, Fire57 );
	HOOK_EVENT( g3sg1, FireG3SG1 );
	HOOK_EVENT( galil, FireGALIL );
	HOOK_EVENT( glock18, Fireglock18 );
	HOOK_EVENT( knife, Knife );
	HOOK_EVENT( m249, FireM249 );
	HOOK_EVENT( m3, FireM3 );
	HOOK_EVENT( m4a1, FireM4A1 );
	HOOK_EVENT( mac10, FireMAC10 );
	HOOK_EVENT( mp5n, FireMP5 );
	HOOK_EVENT( mp7, FireMP7 );
	HOOK_EVENT( p228, FireP228 );
	HOOK_EVENT( p90, FireP90 );
	HOOK_EVENT( scout, FireScout );
	HOOK_EVENT( sg550, FireSG550 );
	HOOK_EVENT( sg552, FireSG552 );
	HOOK_EVENT( tmp, FireTMP );
	HOOK_EVENT( ump45, FireUMP45 );
	HOOK_EVENT( usp, FireUSP );
	HOOK_EVENT( vehicle, Vehicle );
	HOOK_EVENT( xm1014, FireXM1014 );
}
