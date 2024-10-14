
#include "hud.h"

#include "cl_util.h"
#include "parsemsg.h"
#include "com_model.h"
#include <triangleapi.h>
#include <cl_entity.h>
#include <ref_params.h>
#include "gamemode/mods_const.h"
#include "hud_radar_modern.h"
#include "draw_util.h"

#include <string>

#if 1
#define USE_HOSTAGEENTITY
#endif

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

CHudRadarModern::CHudRadarModern(void) : m_OverviewData()
{
	m_bCanRenderMapSprite = false;
	m_iLastWide = 0;

	m_bCanRenderMapSprite = false;
	m_iLastWide = 0;

	cl_newradar_size = CVAR_CREATE("cl_newradar_size", "0.145", FCVAR_ARCHIVE);
	cl_newradar_r = CVAR_CREATE("cl_newradar_r", "1", FCVAR_ARCHIVE);
	cl_newradar_g = CVAR_CREATE("cl_newradar_g", "1", FCVAR_ARCHIVE);
	cl_newradar_b = CVAR_CREATE("cl_newradar_b", "1", FCVAR_ARCHIVE);
	cl_newradar_a = CVAR_CREATE("cl_newradar_a", "0.75", FCVAR_ARCHIVE);

}

int CHudRadarModern::VidInit(void)
{
	m_hsprPlayer = SPR_Load("sprites/iplayer.spr");
	m_hsprPlayerBlue = SPR_Load("sprites/iplayerblue.spr");
	m_hsprPlayerRed = SPR_Load("sprites/iplayerred.spr");
	m_hsprPlayerDead = SPR_Load("sprites/iplayerdead.spr");
	m_hsprPlayerC4 = SPR_Load("sprites/iplayerc4.spr");
	m_hsprPlayerVIP = SPR_Load("sprites/iplayervip.spr");
	m_hsprBackPack = SPR_Load("sprites/ibackpack.spr");
	m_hsprCamera = SPR_Load("sprites/camera.spr");
	m_hsprRadio = SPR_Load("sprites/iradio.spr");
	m_hsprC4 = SPR_Load("sprites/ic4.spr");
	m_hsprHostage = SPR_Load("sprites/ihostage.spr");

	m_HUD_radar = gHUD.GetSpriteIndex("radar");
	m_HUD_radaropaque = gHUD.GetSpriteIndex("radaropaque");

	m_hRadarSupplybox.SetSpriteByName("radar_item");

	m_hrad = &gHUD.GetSpriteRect(m_HUD_radar);
	m_hradopaque = &gHUD.GetSpriteRect(m_HUD_radaropaque);

	m_hrad->left = 0;
	m_hrad->top = 0;
	m_hrad->right = 128;
	m_hrad->bottom = 128;

	m_hradopaque->left = 0;
	m_hradopaque->top = 0;
	m_hradopaque->right = 128;
	m_hradopaque->bottom = 128;

	m_hRadar = gHUD.GetSprite(m_HUD_radar);
	m_hRadaropaque = gHUD.GetSprite(m_HUD_radaropaque);

m_player = gRenderAPI.GL_LoadTexture("gfx/billflx/player.tga", NULL, 0, TF_NEAREST |TF_NOPICMIP|TF_NOMIPMAP|TF_CLAMP );


	return 1;
}

void CHudRadarModern::Reset(void)
{
	for (int i = 1; i <= MAX_HOSTAGES; i++)
		m_pHostages[i] = NULL;

	if (strcmp(m_OverviewData.map, gEngfuncs.pfnGetLevelName()))
	{
		// update level overview if level changed
		std::string map = gEngfuncs.pfnGetLevelName();
		map.erase(map.rfind('.'));
		map.erase(0, map.find_last_of("/\\") + 1);
		LoadOverviewInfo((std::string("overviews/") + std::move(map) + ".txt").c_str(), &m_OverviewData);
		LoadMapSprites();
	}

}

void CHudRadarModern::Think(void)
{

}

void CHudRadarModern::LoadMapSprites(void)
{
	// right now only support for one map layer
	if (m_OverviewData.image[0])
	{
		m_MapSprite = gEngfuncs.LoadMapSprite(m_OverviewData.image);
	}
	else
		m_MapSprite = NULL; // the standard "unknown map" sprite will be used instead
}

bool CHudRadarModern::LoadOverviewInfo(const char* fileName, overview_t* data)
{
	char* buffer = (char*)gEngfuncs.COM_LoadFile((char*)fileName, 5, nullptr);
	if (!buffer) {
		return false;
	}
	char* parsePos = buffer;
	char token[128];
	bool parseSuccess = false;
	while (true) {
		parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
		if (!parsePos) {
			break;
		}
		if (!stricmp(token, "global")) {
			parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
			if (!parsePos) {
				goto error;
			}
			if (strcmp(token, "{")) {
				goto error;
			}
			while (true) {
				parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
				if (!parsePos) {
					goto error;
				}
				if (!stricmp(token, "zoom")) {
					parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
					data->zoom = atof(token);
				}
				else if (!stricmp(token, "origin")) {
					parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
					data->originX = atof(token);
					parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
					data->originY = atof(token);
					parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
				}
				else if (!stricmp(token, "rotated")) {
					parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
					data->rotated = atoi(token) != 0;
				}
				else if (!stricmp(token, "}")) {
					break;
				}
				else {
					goto error;
				}
			}
		}
		else if (!stricmp(token, "layer")) {
			parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
			if (!parsePos) {
				goto error;
			}
			if (strcmp(token, "{")) {
				goto error;
			}
			while (true) {
				parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
				if (!stricmp(token, "image")) {
					parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
					strcpy(data->image, token);
				}
				else if (!stricmp(token, "height")) {
					parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
				}
				else if (!stricmp(token, "}")) {
					break;
				}
				else {
					goto error;
				}
			}
		}
		else {
			goto error;
		}
	}
	parseSuccess = true;
error:
	if (buffer) {
		gEngfuncs.COM_FreeFile(buffer);
	}

	strncpy(data->map, gEngfuncs.pfnGetLevelName(), sizeof(data->map));
	return parseSuccess;
}

int CHudRadarModern::Draw(float time)
{

if (gHUD.hideRadar)
return 0;

	
	const int idx = gEngfuncs.GetLocalPlayer()->index;

#ifdef USE_HOSTAGEENTITY
	if (gHUD.m_flTime > m_flNextBuild)
	{
		BuildHostageList();
		m_flNextBuild = gHUD.m_flTime + 1.0;
	}
#endif

	int sx, sy, wide, tall;
	sx = sy = 2;
	
	tall =  cl_newradar_size->value * 2265 * gHUD.m_flScaleRadar;
	wide = cl_newradar_size->value * 2265 * gHUD.m_flScaleRadar;

	{
		float angles, xTemp, yTemp, viewzoom;
		float screenaspect, xs, ys, xStep, yStep, x, y, z;
		int ix, iy, i, xTiles, yTiles, frame, numframes;
		float xUpStep, yUpStep, xRightStep, yRightStep;
		float xIn, yIn, xOut, yOut;

		viewzoom = 10;

		i = m_MapSprite->numframes / (4 * 3);
		i = sqrt(float(i));

		xTiles = i * 4;
		yTiles = i * 3;

		screenaspect = 4.0f / 3.0f;
		angles = (gHUD.m_vecAngles[1] + 90.0) * (M_PI / 180.0);
		xs = gHUD.m_Spectator.m_OverviewData.origin[0];
		ys = gHUD.m_Spectator.m_OverviewData.origin[1];
		z = 0;

		frame = 0;
		numframes = m_MapSprite->numframes;

		if (m_OverviewData.rotated)
		{
			angles -= M_PI / 2.0;
			xTemp = 3 + gHUD.m_Spectator.m_OverviewData.zoom * (1.0 / 1024.0) * ys - (1.0 / 1024) * gHUD.m_Spectator.m_OverviewData.zoom * gHUD.m_vecOrigin[1];
			yTemp = -(-4 + gHUD.m_Spectator.m_OverviewData.zoom * (1.0 / 1024.0) * xs - (1.0 / 1024) * gHUD.m_Spectator.m_OverviewData.zoom * gHUD.m_vecOrigin[0]);
		}
		else
		{
			xTemp = 3 + gHUD.m_Spectator.m_OverviewData.zoom * (1.0 / 1024.0) * xs - (1.0 / 1024) * gHUD.m_Spectator.m_OverviewData.zoom * gHUD.m_vecOrigin[0];
			yTemp = 4 + gHUD.m_Spectator.m_OverviewData.zoom * (1.0 / 1024.0) * ys - (1.0 / 1024) * gHUD.m_Spectator.m_OverviewData.zoom * gHUD.m_vecOrigin[1];
		}

		xStep = (2 * 4096.0f / viewzoom) / xTiles;
		yStep = -(2 * 4096.0f / (viewzoom * screenaspect)) / yTiles;

		xUpStep = cos(angles + (M_PI / 2)) * yStep;
		yUpStep = sin(angles + (M_PI / 2)) * yStep;
		xRightStep = cos(angles) * xStep;
		yRightStep = sin(angles) * xStep;

xOut = wide * 0.5 - (xTemp * xRightStep) - (yTemp * xUpStep);
yOut = tall * 0.5 - (xTemp * yRightStep) - (yTemp * yUpStep);
//xOut = 0.71 * 2265 * 0.5 - (xTemp * xRightStep) - (yTemp * xUpStep);
//yOut = 0.74 * 1080 * 0.5 - (xTemp * yRightStep) - (yTemp * yUpStep);

		//glScissor(x, ScreenHeight - tall - y, wide, tall);
		//glEnable(GL_SCISSOR_TEST);

		if (g_iXash)
		gRenderAPI.GL_Scissor(1, sx, TrueHeight - tall - sy, wide, tall);

		gEngfuncs.pTriAPI->RenderMode(kRenderTransTexture);
		gEngfuncs.pTriAPI->CullFace(TRI_NONE);
		gEngfuncs.pTriAPI->Color4f(cl_newradar_r->value, cl_newradar_g->value, cl_newradar_b->value, cl_newradar_a->value);

		for (ix = 0; ix < yTiles; ix++)
		{
			xIn = xOut;
			yIn = yOut;

			for (iy = 0; iy < xTiles; iy++)
			{
				x = xIn;
				y = yIn;

				if (frame >= numframes)
					break;

				gEngfuncs.pTriAPI->SpriteTexture(m_MapSprite, frame);
				gEngfuncs.pTriAPI->Begin(TRI_QUADS);
				gEngfuncs.pTriAPI->TexCoord2f(0, 0);
				gEngfuncs.pTriAPI->Vertex3f(x, y, 0.0);
				gEngfuncs.pTriAPI->TexCoord2f(0, 1);
				gEngfuncs.pTriAPI->Vertex3f(x + xRightStep, y + yRightStep, 0.0);
				gEngfuncs.pTriAPI->TexCoord2f(1, 1);
				gEngfuncs.pTriAPI->Vertex3f(x + xRightStep + xUpStep, y + yRightStep + yUpStep, 0.0);
				gEngfuncs.pTriAPI->TexCoord2f(1, 0);
				gEngfuncs.pTriAPI->Vertex3f(x + xUpStep, y + yUpStep, 0.0);
				gEngfuncs.pTriAPI->End();

				frame++;

				xIn += xUpStep;
				yIn += yUpStep;
			}

			xOut += xRightStep;
			yOut += yRightStep;
		}
		//glDisable(GL_SCISSOR_TEST);
		if (g_iXash)
			gRenderAPI.GL_Scissor(0, 0, 0, 0, 0);
	}

	DrawUtils::DrawOutlinedRect(sx / gHUD.m_flScale, sy / gHUD.m_flScale, wide / gHUD.m_flScale, tall / gHUD.m_flScale, 0, 0, 0, 255);

	DrawUtils::DrawOutlinedRect2(sx / gHUD.m_flScale, sy / gHUD.m_flScale, wide / gHUD.m_flScale, tall / gHUD.m_flScale + 40, 0, 0, 0, 200);

gRenderAPI.GL_SelectTexture( 0 );
gRenderAPI.GL_Bind(0, m_player);
gEngfuncs.pTriAPI->RenderMode( kRenderTransAlpha );
DrawUtils::Draw2DQuad(sx / 2, sy, wide, tall - TrueHeight / -70 ); 



int syy = 282;
int iLength, iHeight;

//map name
if (strlen(g_szLocation))
{
		gEngfuncs.pfnDrawSetTextColor(255, 255, 255);
		gEngfuncs.pfnDrawConsoleStringLen(g_szLocation, &iLength, &iHeight);
		gEngfuncs.pfnDrawConsoleString(64 - iLength / 1.8, tall / 1.03+ iHeight, g_szLocation);
}

	// TODO : localization

	gEngfuncs.pTriAPI->RenderMode(kRenderTransAdd);
	gEngfuncs.pTriAPI->Color4f(1, 0.62745f, 0, 1.0f);

	struct model_s* model = (struct model_s*)gEngfuncs.GetSpritePointer(m_hsprCamera);
	gEngfuncs.pTriAPI->SpriteTexture(model, 0);
	
	float cameraScale = 2;
	int cameraWide = gEngfuncs.pfnSPR_Width(m_hsprCamera, 0) * cameraScale;
	int cameraHeight = gEngfuncs.pfnSPR_Height(m_hsprCamera, 0) * cameraScale;

	gEngfuncs.pTriAPI->Begin(TRI_TRIANGLES);
	gEngfuncs.pTriAPI->TexCoord2f(1, 1);
	gEngfuncs.pTriAPI->Vertex3f(wide / 2 + cameraWide * 0.7, tall / 2 - cameraHeight * 0.7, 0);
	gEngfuncs.pTriAPI->TexCoord2f(0, 0);
	gEngfuncs.pTriAPI->Vertex3f(wide / 2 - cameraWide * 0.7, tall / 2 - cameraHeight * 0.7, 0);
	gEngfuncs.pTriAPI->TexCoord2f(0, 1);
	gEngfuncs.pTriAPI->Vertex3f(wide / 2, tall / 2, 0);
	gEngfuncs.pTriAPI->End();

	gEngfuncs.pTriAPI->RenderMode(kRenderTransAlpha);

	float flTime = gHUD.m_flTime;

	char szTeamName[MAX_TEAM_NAME];
	strcpy(szTeamName, g_PlayerExtraInfo[idx].teamname);

	for (int i = 0; i < MAX_CLIENTS + 1; i++)
	{
		if (i != 32 && (!g_PlayerInfoList[i].name || !g_PlayerInfoList[i].name[0]))
			continue;

		if (strcmp(szTeamName, g_PlayerExtraInfo[i].teamname) || g_PlayerExtraInfo[i].dead)
			continue;

		int r, g, b;
		HSPRITE hspr = 0;
		HSPRITE hspr2 = 0;
		int scale = 8;
		float scale2 = 0.75;

		if (i == idx)
		{
		}
		else
		{
			if (g_PlayerExtraInfo[i].teamnumber == g_iTeamNumber)
			{
				if (g_iTeamNumber == TEAM_TERRORIST)
				{
					r = 255;
					g = 255;
					b = 255;
					hspr = m_hsprPlayerRed;

					if (g_PlayerExtraInfo[i].has_c4)
						hspr = m_hsprPlayerC4;
				}
				else if (g_iTeamNumber == TEAM_CT)
				{
					r = 255;
					g = 255;
					b = 255;
					hspr = m_hsprPlayerBlue;

					if (g_PlayerExtraInfo[i].vip)
						hspr = m_hsprPlayerVIP;
				}
			}
		}

		int rx, ry;
		float yaw = 0;

		if (i != 32)
		{
			if (hspr == 0)
				continue;

			cl_entity_t *ent = gEngfuncs.GetEntityByIndex(i);
			vec3_t *origin;
			bool valid;

			if (!IsValidEntity(ent))
			{
				valid = false;
				origin = &g_PlayerExtraInfo[i].origin;
			}
			else
			{
				valid = true;
				origin = &ent->origin;
			}

			if (!CalcPoint(*origin, rx, ry, scale))
			{
				if (valid)
					yaw = gHUD.m_vecAngles[1] - ent->angles[1];
			}

			DrawSprite(rx, ry, hspr, yaw, scale, r, g, b, 255);

			if (hspr2 != 0)
				DrawSprite(rx, ry, hspr2, yaw, scale * scale2, r, g, b, 255);
		}

		if (g_PlayerExtraInfo[i].radarflashtime != -1.0 && flTime > g_PlayerExtraInfo[i].radarflashtime && g_PlayerExtraInfo[i].radarflashes > 0)
		{
			g_PlayerExtraInfo[i].radarflashtime = flTime + g_PlayerExtraInfo[i].radarflashtimedelta;
			g_PlayerExtraInfo[i].radarflashes--;
			g_PlayerExtraInfo[i].nextflash = !g_PlayerExtraInfo[i].nextflash;
		}

		if (g_PlayerExtraInfo[i].nextflash == true && g_PlayerExtraInfo[i].radarflashes > 0)
		{
			if (i == 32)
			{
				if (g_iTeamNumber == TEAM_TERRORIST)
				{
					r = 255;
					g = 255;
					b = 255;
					hspr = m_hsprBackPack;
					scale = scale * 1.5;

					if (g_PlayerExtraInfo[i].playerclass == 1)
						hspr = m_hsprC4;

					CalcPoint(g_PlayerExtraInfo[i].origin, rx, ry, scale);
					DrawSprite(rx, ry, hspr, yaw, scale, r, g, b, 255);
				}
			}
			else
			{
				r = 255;
				g = 255;
				b = 255;
				hspr = m_hsprRadio;

				cl_entity_t *ent = gEngfuncs.GetEntityByIndex(i);
				vec3_t *origin;
				bool valid;

				if (!IsValidEntity(ent))
				{
					valid = false;
					origin = &g_PlayerExtraInfo[i].origin;
				}
				else
				{
					valid = true;
					origin = &ent->origin;
				}

				if (!CalcPoint(*origin, rx, ry, scale))
				{
					if (valid)
						yaw = gHUD.m_vecAngles[1] - ent->angles[1];
				}

				DrawSprite(rx, ry, hspr, yaw, scale, r, g, b, 255);
			}
		}
	}

	
	if (gHUD.m_iModRunning == MOD_ZB2 || gHUD.m_iModRunning == MOD_ZB3)
	{
		if (g_PlayerExtraInfo[gHUD.m_Scoreboard.m_iPlayerNum].teamnumber == TEAM_CT)
		{
			for (int i = 0; i < MAX_HOSTAGES; i++)
			{
				if (g_HostageInfo[i].dead)
					continue;

				HSPRITE hspr = m_hRadarSupplybox.spr;
				int scale = 8;
				int rx, ry;
				float yaw = 0;

				cl_entity_t* ent = m_pHostages[i];
				vec3_t* origin;
				bool valid;

				if (!IsValidEntity(ent))
				{
					valid = false;
					origin = &g_HostageInfo[i].origin;
				}
				else
				{
					valid = true;
					origin = &ent->origin;
				}

				if (!CalcPoint(*origin, rx, ry, scale))
				{
					if (valid)
						yaw = gHUD.m_vecAngles[1] - ent->angles[1];
				}
				//DrawSprite(rx, ry, hspr, yaw, scale, 200, 200, 200, 255);
				SPR_Set(hspr, 133, 247, 255);
				SPR_DrawAdditive(0, rx, ry, &m_hRadarSupplybox.rect);
			}
		}
	}
	else
	{
		for (int i = 0; i <= MAX_HOSTAGES; i++)
		{
			if ((g_HostageInfo[i].dead) || (g_HostageInfo[i].radarflashtime == -1))
				continue;

			int r, g, b;
			HSPRITE hspr = 0;
			int scale = 8;
			int rx, ry;
			float yaw = 0;

			if (g_HostageInfo[i].radarflashtime != -1.0 && flTime > g_HostageInfo[i].radarflashtime && g_HostageInfo[i].radarflashes > 0)
			{
				g_HostageInfo[i].radarflashtime = flTime + g_PlayerExtraInfo[i].radarflashtimedelta;
				g_HostageInfo[i].radarflashes--;
				g_HostageInfo[i].nextflash = !g_HostageInfo[i].nextflash;
			}

			if (g_HostageInfo[i].nextflash && g_HostageInfo[i].radarflashes > 0)
			{
				r = 255;
				g = 255;
				b = 255;
				hspr = m_hsprHostage;

				if (g_HostageInfo[i].dead)
				{
					r = 255;
					g = 255;
					b = 255;
				}

				cl_entity_t* ent = m_pHostages[i];
				vec3_t* origin;
				bool valid;

				if (!IsValidEntity(ent))
				{
					valid = false;
					origin = &g_HostageInfo[i].origin;
				}
				else
				{
					valid = true;
					origin = &ent->origin;
				}

				if (!CalcPoint(*origin, rx, ry, scale))
				{
					if (valid)
						yaw = gHUD.m_vecAngles[1] - ent->angles[1];
				}

				DrawSprite(rx, ry, hspr, yaw, scale, r, g, b, 255);
			}
		}
	}
	

	gEngfuncs.pTriAPI->RenderMode(kRenderNormal);
	return 1;
}

void CHudRadarModern::InitHUDData()
{
	Reset();
}

void CHudRadarModern::BuildHostageList(void)
{
	int index = 1;

	for (int i = 1; ; i++)
	{
		cl_entity_t *entity = gEngfuncs.GetEntityByIndex(i);

		if (!entity)
			break;

		model_t *model = entity->model;

		if (model)
		{
			if (model->name[0] == '*')
				continue;

			if (!strcmp(model->name, "models/hostage.mdl"))
			{
				m_pHostages[index] = entity;
				index++;
			}
		}
	}

	for (int i = index; i <= MAX_HOSTAGES; i++)
		m_pHostages[i] = NULL;
}

bool CHudRadarModern::IsValidEntity(cl_entity_s *pEntity)
{
	if (pEntity && pEntity->model && pEntity->model->name[0] && !(pEntity->curstate.messagenum < gEngfuncs.GetLocalPlayer()->curstate.messagenum))
		return true;

	return false;
}

#ifdef _MSC_VER
#pragma optimize("", off)
#endif

bool CHudRadarModern::CalcPoint(float *origin, int &screenX, int &screenY, int &scale)
{
	int wide, tall;
	
	tall =  cl_newradar_size->value * 2265 * gHUD.m_flScaleRadar;
	wide = cl_newradar_size->value * 2265 * gHUD.m_flScaleRadar;

	float dx = origin[0] - gHUD.m_vecOrigin[0];
	float dy = origin[1] - gHUD.m_vecOrigin[1];

	float yaw = gHUD.m_vecAngles[1] * (M_PI / 180.0);

	float yawSin = sin(yaw);
	float yawCos = cos(yaw);

	float x = dx * yawSin - dy * yawCos;
	float y = dx * (-yawCos) - dy * yawSin;

	float zoom = 10;
	bool scaled = false;

	screenX = (wide / 2) + (x / zoom) * m_OverviewData.zoom;
	screenY = (tall / 2) + (y / zoom) * m_OverviewData.zoom;

	bool result = false;
	float scalleRate = (1 / 1.2);

	if (screenX < 0 + scale)
	{
		screenX = 0;
		result = true;
		scale *= scalleRate;
		scaled = true;
		screenX += scale + 1;
	}
	else if (screenX >= wide - scale)
	{
		screenX = wide;
		result = true;
		scale *= scalleRate;
		scaled = true;
		screenX -= scale + 1;
	}

	if (screenY < 0 + scale)
	{
		screenY = 0;
		result = true;

		if (!scaled)
			scale *= scalleRate;

		screenY += scale + 1;
	}
	else if (screenY >= tall - scale)
	{
		screenY = wide;
		result = true;

		if (!scaled)
			scale *= scalleRate;

		screenY -= scale + 1;
	}

	return result;
}

#ifdef _MSC_VER
#pragma optimize("", on)
#endif

void CHudRadarModern::DrawSprite(int x, int y, HSPRITE hspr, float yaw, int scale, int r, int g, int b, int a)
{
	if (hspr == 0)
	{
		gEngfuncs.pfnFillRGBA(x - 10, y - 10, 20, 20, r, g, b, a);
		return;
	}

	int wide, tall;
	tall =  cl_newradar_size->value * 2265 * gHUD.m_flScaleRadar;
	wide = cl_newradar_size->value * 2265 * gHUD.m_flScaleRadar;
	if (x < 0 || x > wide || y < 0 || y > tall)
		return;

	gEngfuncs.pTriAPI->CullFace(TRI_NONE);
	gEngfuncs.pTriAPI->Color4ub(r, g, b, a);

	struct model_s *model = (struct model_s *)gEngfuncs.GetSpritePointer(hspr);
	gEngfuncs.pTriAPI->SpriteTexture(model, 0);

	vec3_t forward, right, sub;
	sub[0] = sub[2] = 0;
	sub[1] = yaw - 90.0;

	gEngfuncs.pfnAngleVectors(sub, forward, right, NULL);

	gEngfuncs.pTriAPI->Begin(TRI_QUADS);
	gEngfuncs.pTriAPI->TexCoord2f(1, 0);
	gEngfuncs.pTriAPI->Vertex3f(x + right.x * scale + forward.x * scale, y + right.y * scale + forward.y * scale, 0);
	gEngfuncs.pTriAPI->TexCoord2f(0, 0);
	gEngfuncs.pTriAPI->Vertex3f(x + right.x * scale + forward.x * -scale, y + right.y * scale + forward.y * -scale, 0);
	gEngfuncs.pTriAPI->TexCoord2f(0, 1);
	gEngfuncs.pTriAPI->Vertex3f(x + right.x * -scale + forward.x * -scale, y + right.y * -scale + forward.y * -scale, 0);
	gEngfuncs.pTriAPI->TexCoord2f(1, 1);
	gEngfuncs.pTriAPI->Vertex3f(x + right.x * -scale + forward.x * scale, y + right.y * -scale + forward.y * scale, 0);
	gEngfuncs.pTriAPI->End();
}

//board

CHudRadarModernBoard::CHudRadarModernBoard(void) : m_OverviewData()
{
	m_bCanRenderMapSprite = false;
	m_iLastWide = 0;

	m_bCanRenderMapSprite = false;
	m_iLastWide = 0;

	cl_newradar_board_size = CVAR_CREATE("cl_newradar_board_size", "0.175", FCVAR_ARCHIVE);
	cl_newradar_r = CVAR_CREATE("cl_newradar_r", "1", FCVAR_ARCHIVE);
	cl_newradar_g = CVAR_CREATE("cl_newradar_g", "1", FCVAR_ARCHIVE);
	cl_newradar_b = CVAR_CREATE("cl_newradar_b", "1", FCVAR_ARCHIVE);
	cl_newradar_a = CVAR_CREATE("cl_newradar_a", "0.75", FCVAR_ARCHIVE);

}

int CHudRadarModernBoard::VidInit(void)
{
	m_hsprPlayer = SPR_Load("sprites/iplayer.spr");
	m_hsprPlayerBlue = SPR_Load("sprites/iplayerblue.spr");
	m_hsprPlayerRed = SPR_Load("sprites/iplayerred.spr");
	m_hsprPlayerDead = SPR_Load("sprites/iplayerdead.spr");
	m_hsprPlayerC4 = SPR_Load("sprites/iplayerc4.spr");
	m_hsprPlayerVIP = SPR_Load("sprites/iplayervip.spr");
	m_hsprBackPack = SPR_Load("sprites/ibackpack.spr");
	m_hsprCamera = SPR_Load("sprites/camera.spr");
	m_hsprRadio = SPR_Load("sprites/iradio.spr");
	m_hsprC4 = SPR_Load("sprites/ic4.spr");
	m_hsprHostage = SPR_Load("sprites/ihostage.spr");

	m_HUD_radar = gHUD.GetSpriteIndex("radar");
	m_HUD_radaropaque = gHUD.GetSpriteIndex("radaropaque");

	m_hRadarSupplybox.SetSpriteByName("radar_item");

	m_hrad = &gHUD.GetSpriteRect(m_HUD_radar);
	m_hradopaque = &gHUD.GetSpriteRect(m_HUD_radaropaque);

	m_hrad->left = 0;
	m_hrad->top = 0;
	m_hrad->right = 128;
	m_hrad->bottom = 128;

	m_hradopaque->left = 0;
	m_hradopaque->top = 0;
	m_hradopaque->right = 128;
	m_hradopaque->bottom = 128;

	m_hRadar = gHUD.GetSprite(m_HUD_radar);
	m_hRadaropaque = gHUD.GetSprite(m_HUD_radaropaque);
	return 1;
}

void CHudRadarModernBoard::Reset(void)
{
	for (int i = 1; i <= MAX_HOSTAGES; i++)
		m_pHostages[i] = NULL;

	if (strcmp(m_OverviewData.map, gEngfuncs.pfnGetLevelName()))
	{
		// update level overview if level changed
		std::string map = gEngfuncs.pfnGetLevelName();
		map.erase(map.rfind('.'));
		map.erase(0, map.find_last_of("/\\") + 1);
		LoadOverviewInfo((std::string("overviews/") + std::move(map) + ".txt").c_str(), &m_OverviewData);
		LoadMapSprites();
	}

}

void CHudRadarModernBoard::Think(void)
{

}

void CHudRadarModernBoard::LoadMapSprites(void)
{
	// right now only support for one map layer
	if (m_OverviewData.image[0])
	{
		m_MapSprite = gEngfuncs.LoadMapSprite(m_OverviewData.image);
	}
	else
		m_MapSprite = NULL; // the standard "unknown map" sprite will be used instead
}

bool CHudRadarModernBoard::LoadOverviewInfo(const char* fileName, overview_t* data)
{
	char* buffer = (char*)gEngfuncs.COM_LoadFile((char*)fileName, 5, nullptr);
	if (!buffer) {
		return false;
	}
	char* parsePos = buffer;
	char token[128];
	bool parseSuccess = false;
	while (true) {
		parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
		if (!parsePos) {
			break;
		}
		if (!stricmp(token, "global")) {
			parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
			if (!parsePos) {
				goto error;
			}
			if (strcmp(token, "{")) {
				goto error;
			}
			while (true) {
				parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
				if (!parsePos) {
					goto error;
				}
				if (!stricmp(token, "zoom")) {
					parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
					data->zoom = atof(token);
				}
				else if (!stricmp(token, "origin")) {
					parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
					data->originX = atof(token);
					parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
					data->originY = atof(token);
					parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
				}
				else if (!stricmp(token, "rotated")) {
					parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
					data->rotated = atoi(token) != 0;
				}
				else if (!stricmp(token, "}")) {
					break;
				}
				else {
					goto error;
				}
			}
		}
		else if (!stricmp(token, "layer")) {
			parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
			if (!parsePos) {
				goto error;
			}
			if (strcmp(token, "{")) {
				goto error;
			}
			while (true) {
				parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
				if (!stricmp(token, "image")) {
					parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
					strcpy(data->image, token);
				}
				else if (!stricmp(token, "height")) {
					parsePos = gEngfuncs.COM_ParseFile(parsePos, token);
				}
				else if (!stricmp(token, "}")) {
					break;
				}
				else {
					goto error;
				}
			}
		}
		else {
			goto error;
		}
	}
	parseSuccess = true;
error:
	if (buffer) {
		gEngfuncs.COM_FreeFile(buffer);
	}

	strncpy(data->map, gEngfuncs.pfnGetLevelName(), sizeof(data->map));
	return parseSuccess;
}

int CHudRadarModernBoard::Draw(float time)
{
if (gHUD.hideRadarScore== true)
return 0;

const int idx = gEngfuncs.GetLocalPlayer()->index;

#ifdef USE_HOSTAGEENTITY
	if (gHUD.m_flTime > m_flNextBuild)
	{
		BuildHostageList();
		m_flNextBuild = gHUD.m_flTime + 1.0;
	}
#endif

	int sx, sy, wide, tall;
sx = 15;
sy = 15;
tall =  cl_newradar_board_size->value * ScreenWidth * gHUD.m_flScaleRadar;
wide = cl_newradar_board_size->value * ScreenWidth * gHUD.m_flScaleRadar;

	{
		float angles, xTemp, yTemp, viewzoom;
		float screenaspect, xs, ys, xStep, yStep, x, y, z;
		int ix, iy, i, xTiles, yTiles, frame, numframes;
		float xUpStep, yUpStep, xRightStep, yRightStep;
		float xIn, yIn, xOut, yOut;

		viewzoom = 5;

		i = m_MapSprite->numframes / (4 * 3);
		i = sqrt(float(i));

		xTiles = i * 4;
		yTiles = i * 3;

		screenaspect = 2.0f / 2.0f;
		angles = (gHUD.m_vecAngles[1] + 90.0) * (M_PI / 180.0);
		xs = gHUD.m_Spectator.m_OverviewData.origin[0];
		ys = gHUD.m_Spectator.m_OverviewData.origin[1];
		z = 0;

		frame = 0;
		numframes = m_MapSprite->numframes;

		if (m_OverviewData.rotated)
		{
			angles -= M_PI / 2.0;
			xTemp = 3 + gHUD.m_Spectator.m_OverviewData.zoom * (1.0 / 1024.0) * ys - (1.0 / 1024) * gHUD.m_Spectator.m_OverviewData.zoom * gHUD.m_vecOrigin[1];
			yTemp = -(-4 + gHUD.m_Spectator.m_OverviewData.zoom * (1.0 / 1024.0) * xs - (1.0 / 1024) * gHUD.m_Spectator.m_OverviewData.zoom * gHUD.m_vecOrigin[0]);
		}
		else
		{
			xTemp = 3 + gHUD.m_Spectator.m_OverviewData.zoom * (1.0 / 1024.0) * xs - (1.0 / 1024) * gHUD.m_Spectator.m_OverviewData.zoom * gHUD.m_vecOrigin[0];
			yTemp = 4 + gHUD.m_Spectator.m_OverviewData.zoom * (1.0 / 1024.0) * ys - (1.0 / 1024) * gHUD.m_Spectator.m_OverviewData.zoom * gHUD.m_vecOrigin[1];
		}

		xStep = (2 * 4096.0f / viewzoom) / xTiles;
		yStep = -(2 * 4096.0f / (viewzoom * screenaspect)) / yTiles;

		xUpStep = cos(angles + (M_PI / 2)) * yStep;
		yUpStep = sin(angles + (M_PI / 2)) * yStep;
		xRightStep = cos(angles) * xStep;
		yRightStep = sin(angles) * xStep;

int size;
int xy = ScreenWidth / 2;

int xstart = xy - 400;
int xend = xy + 950;

int ystart = 100;
int yend = ScreenHeight - ystart;

//origin 
xOut = 1.23 * ScreenWidth * 0.5 - (xTemp * xRightStep) - (yTemp * xUpStep);
yOut = 1 * ScreenHeight * 0.5 - (xTemp * yRightStep) - (yTemp * yUpStep);

DrawUtils::DrawRectangle(xstart + 300, ystart, xend - xstart - 600, yend - ystart, 0, 0, 0, 150, false);
gRenderAPI.GL_Scissor(1, xstart + 300, ystart, xend - xstart - 600, yend - ystart);

//enable, wide, height,wide, tall

		gEngfuncs.pTriAPI->RenderMode(kRenderTransTexture);
		gEngfuncs.pTriAPI->CullFace(TRI_NONE);
		gEngfuncs.pTriAPI->Color4f(cl_newradar_r->value, cl_newradar_g->value, cl_newradar_b->value, cl_newradar_a->value);

		for (ix = 0; ix < yTiles; ix++)
		{
			xIn = xOut;
			yIn = yOut;

			for (iy = 0; iy < xTiles; iy++)
			{
				x = xIn;
				y = yIn;

				if (frame >= numframes)
					break;

				gEngfuncs.pTriAPI->SpriteTexture(m_MapSprite, frame);
				gEngfuncs.pTriAPI->Begin(TRI_QUADS);
				gEngfuncs.pTriAPI->TexCoord2f(0, 0);
				gEngfuncs.pTriAPI->Vertex3f(x, y, 0.0);
				gEngfuncs.pTriAPI->TexCoord2f(0, 1);
				gEngfuncs.pTriAPI->Vertex3f(x + xRightStep, y + yRightStep, 0.0);
				gEngfuncs.pTriAPI->TexCoord2f(1, 1);
				gEngfuncs.pTriAPI->Vertex3f(x + xRightStep + xUpStep, y + yRightStep + yUpStep, 0.0);
				gEngfuncs.pTriAPI->TexCoord2f(1, 0);
				gEngfuncs.pTriAPI->Vertex3f(x + xUpStep, y + yUpStep, 0.0);
				gEngfuncs.pTriAPI->End();

				frame++;

				xIn += xUpStep;
				yIn += yUpStep;
			}

			xOut += xRightStep;
			yOut += yRightStep;
		}
		//glDisable(GL_SCISSOR_TEST);
		if (g_iXash)
			gRenderAPI.GL_Scissor(0, 0, 0, 0, 0);
	}


int r = 255, g = 255, b = 255;

	int startpos = 4;
	{
		startpos = XRES(gHUD.m_Spectator.m_OverviewData.insetWindowWidth) + XRES(gHUD.m_Spectator.m_OverviewData.insetWindowX);
		startpos *= ScreenWidth / TrueWidth; // hud_scale adjust
	}
	
	return 1;
}

void CHudRadarModernBoard::InitHUDData()
{
	Reset();
}

void CHudRadarModernBoard::BuildHostageList(void)
{
	int index = 1;

	for (int i = 1; ; i++)
	{
		cl_entity_t *entity = gEngfuncs.GetEntityByIndex(i);

		if (!entity)
			break;

		model_t *model = entity->model;

		if (model)
		{
			if (model->name[0] == '*')
				continue;

			if (!strcmp(model->name, "models/hostage.mdl"))
			{
				m_pHostages[index] = entity;
				index++;
			}
		}
	}

	for (int i = index; i <= MAX_HOSTAGES; i++)
		m_pHostages[i] = NULL;
}

bool CHudRadarModernBoard::IsValidEntity(cl_entity_s *pEntity)
{
	if (pEntity && pEntity->model && pEntity->model->name[0] && !(pEntity->curstate.messagenum < gEngfuncs.GetLocalPlayer()->curstate.messagenum))
		return true;

	return false;
}

#ifdef _MSC_VER
#pragma optimize("", off)
#endif

bool CHudRadarModernBoard::CalcPoint(float *origin, int &screenX, int &screenY, int &scale)
{
	int wide, tall;
	tall = wide = 0.160 * ScreenWidth * gHUD.m_flScale;

	float dx = origin[0] - gHUD.m_vecOrigin[0];
	float dy = origin[1] - gHUD.m_vecOrigin[1];

	float yaw = gHUD.m_vecAngles[1] * (M_PI / 180.0);

	float yawSin = sin(yaw);
	float yawCos = cos(yaw);

	float x = dx * yawSin - dy * yawCos;
	float y = dx * (-yawCos) - dy * yawSin;

	float zoom = 10;
	bool scaled = false;

	screenX = (wide / 2) + (x / zoom) * m_OverviewData.zoom;
	screenY = (tall / 2) + (y / zoom) * m_OverviewData.zoom;

	bool result = false;
	float scalleRate = (1 / 1.2);

	if (screenX < 0 + scale)
	{
		screenX = 0;
		result = true;
		scale *= scalleRate;
		scaled = true;
		screenX += scale + 1;
	}
	else if (screenX >= wide - scale)
	{
		screenX = wide;
		result = true;
		scale *= scalleRate;
		scaled = true;
		screenX -= scale + 1;
	}

	if (screenY < 0 + scale)
	{
		screenY = 0;
		result = true;

		if (!scaled)
			scale *= scalleRate;

		screenY += scale + 1;
	}
	else if (screenY >= tall - scale)
	{
		screenY = wide;
		result = true;

		if (!scaled)
			scale *= scalleRate;

		screenY -= scale + 1;
	}

	return result;
}

#ifdef _MSC_VER
#pragma optimize("", on)
#endif

void CHudRadarModernBoard::DrawSprite(int x, int y, HSPRITE hspr, float yaw, int scale, int r, int g, int b, int a)
{
	if (hspr == 0)
	{
		gEngfuncs.pfnFillRGBA(x - 10, y - 10, 20, 20, r, g, b, a);
		return;
	}

	int wide, tall;
	tall = wide = 0.160 * ScreenWidth * gHUD.m_flScale;
	if (x < 0 || x > wide || y < 0 || y > tall)
		return;

	gEngfuncs.pTriAPI->CullFace(TRI_NONE);
	gEngfuncs.pTriAPI->Color4ub(r, g, b, a);

	struct model_s *model = (struct model_s *)gEngfuncs.GetSpritePointer(hspr);
	gEngfuncs.pTriAPI->SpriteTexture(model, 0);

	vec3_t forward, right, sub;
	sub[0] = sub[2] = 0;
	sub[1] = yaw - 90.0;

	gEngfuncs.pfnAngleVectors(sub, forward, right, NULL);

	gEngfuncs.pTriAPI->Begin(TRI_QUADS);
	gEngfuncs.pTriAPI->TexCoord2f(1, 0);
	gEngfuncs.pTriAPI->Vertex3f(x + right.x * scale + forward.x * scale, y + right.y * scale + forward.y * scale, 0);
	gEngfuncs.pTriAPI->TexCoord2f(0, 0);
	gEngfuncs.pTriAPI->Vertex3f(x + right.x * scale + forward.x * -scale, y + right.y * scale + forward.y * -scale, 0);
	gEngfuncs.pTriAPI->TexCoord2f(0, 1);
	gEngfuncs.pTriAPI->Vertex3f(x + right.x * -scale + forward.x * -scale, y + right.y * -scale + forward.y * -scale, 0);
	gEngfuncs.pTriAPI->TexCoord2f(1, 1);
	gEngfuncs.pTriAPI->Vertex3f(x + right.x * -scale + forward.x * scale, y + right.y * -scale + forward.y * scale, 0);
	gEngfuncs.pTriAPI->End();
}
