#ifndef WPN_P228_H
#define WPN_P228_H
#ifdef _WIN32
#pragma once
#endif

//p228
#define P228_MAX_SPEED		196
#define P228_DAMAGE		32
#define P228_RANGE_MODIFER	0.8
#define P228_RELOAD_TIME	2.7

class CTaurus_raging_bull : public CBasePlayerWeapon
{
public:
	void Spawn() override;
	void Precache() override;
	int GetItemInfo(ItemInfo *p) override;
	BOOL Deploy() override;
	float GetMaxSpeed() override { return HANDGUN_SPEED; }
	int iItemSlot() override { return PISTOL_SLOT; }
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
	BOOL IsPistol() override { return TRUE; }
	KnockbackData GetKnockBackData() override { return { 85.0f, 100.0f, 100.0f, 80.0f, 0.8f }; }

public:
	void Taurus_raging_bullFire(float flSpread, float flCycleTime, BOOL fUseSemi);
	NOXREF void MakeBeam();
	NOXREF void BeamUpdate();

public:
	int m_iShell;

private:
	unsigned short m_usFireTaurus_raging_bull;
};

#endif
