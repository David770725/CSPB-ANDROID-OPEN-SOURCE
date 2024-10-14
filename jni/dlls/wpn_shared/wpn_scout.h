#ifndef WPN_SCOUT_H
#define WPN_SCOUT_H
#ifdef _WIN32
#pragma once
#endif

//scout
#define SCOUT_MAX_SPEED			210
#define SCOUT_MAX_SPEED_ZOOM		220
#define SCOUT_DAMAGE			75
#define SCOUT_RANGE_MODIFER		0.98
#define SCOUT_RELOAD_TIME		2

class CSCOUT : public CBasePlayerWeapon
{
public:
	void Spawn() override;
	void Precache() override;
	int GetItemInfo(ItemInfo *p) override;
	BOOL Deploy() override;
	float GetMaxSpeed() override;
	int iItemSlot() override { return PRIMARY_WEAPON_SLOT; }
	void PrimaryAttack() override;
void QuickDeploy() override;

void QuickReload() override;
void Fov2();
void Fov3();
void Fov4();
void Fov5();
void Fov6();
void Fov7();

void offFov2();
void offFov3();
void offFov4();
void offFov5();
void offFov6();
void offFov7();
void Holster(int skiplocal) override;
void breath();


	void SecondaryAttack() override;
	void Reload() override;
	void WeaponIdle() override;
	BOOL UseDecrement() override {
#ifdef CLIENT_WEAPONS
		return TRUE;
#else
		return FALSE;
#endif
	}
	KnockbackData GetKnockBackData() override { return { 3000.0f, 500.0f, 1200.0f, 800.0f, 0.3f }; }

public:
	void SCOUTFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);
	int m_iShell;
int m_iSprBeam;

private:
	unsigned short m_usFireScout;
};

#endif
