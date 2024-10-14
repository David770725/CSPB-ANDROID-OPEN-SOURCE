#ifndef WPN_p90_H
#define WPN_p90_H
#ifdef _WIN32
#pragma once
#endif

//p90
#define p90_MAX_SPEED			190
#define p90_DAMAGE			32
#define p90_RANGE_MODIFER		0.96
#define p90_RELOAD_TIME			3.3

class CP90 : public CBasePlayerWeapon
{
public:
	void Spawn() override;
	void Precache() override;
	int GetItemInfo(ItemInfo *p) override;
	BOOL Deploy() override;
	float GetMaxSpeed() override { return SMG_SPEED; }
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
	KnockbackData GetKnockBackData() override { return { 350.0f,250.0f,300.0f,100.0f,0.6f }; }

public:
	void p90Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;
int m_iSprBeam;
private:
	unsigned short m_usFirep90;
};

#endif
