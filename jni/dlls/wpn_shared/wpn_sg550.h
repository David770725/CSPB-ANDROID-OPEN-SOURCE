#ifndef WPN_SG550_H
#define WPN_SG550_H
#ifdef _WIN32
#pragma once
#endif

//sg550
#define SG550_MAX_SPEED			190
#define SG550_MAX_SPEED_ZOOM		150
#define SG550_DAMAGE			70
#define SG550_RANGE_MODIFER		0.98
#define SG550_RELOAD_TIME		3.35

class CSG550 : public CBasePlayerWeapon
{
public:
	void Spawn() override;
	void Precache() override;
	int GetItemInfo(ItemInfo *p) override;
	BOOL Deploy() override;
	float GetMaxSpeed() override { return ASSAULT_SPEED; }
	int iItemSlot() override { return PRIMARY_WEAPON_SLOT; }
	void PrimaryAttack() override;
void QuickDeploy() override;

void QuickReload() override;
void Fov2();
void Fov3();
void Fov4();
void Fov5();
void Fov6();


void offFov2();
void offFov3();
void offFov4();
void offFov5();
void offFov6();

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
	KnockbackData GetKnockBackData() override { return { 450.0f, 400.0f, 400.0f, 200.0f, 0.5f }; }

public:
	void SG550Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

public:
	int m_iShell;

private:
	unsigned short m_usFireSG550;
};

#endif
