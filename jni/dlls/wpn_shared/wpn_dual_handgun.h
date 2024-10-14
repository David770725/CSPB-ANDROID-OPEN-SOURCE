#ifndef WPN_ELITE_H
#define WPN_ELITE_H
#ifdef _WIN32
#pragma once
#endif

//Elites
#define ELITE_MAX_SPEED		195
#define ELITE_RELOAD_TIME	4.5
#define ELITE_DAMAGE		36
#define ELITE_RANGE_MODIFER	0.75

class CDual_handgun : public CBasePlayerWeapon
{
public:
	void Spawn() override;
	void Precache() override;
	int GetItemInfo(ItemInfo *p) override;
	BOOL Deploy() override;
	float GetMaxSpeed() override { return HANDGUN_SPEED; }
	int iItemSlot() override { return PISTOL_SLOT; }
	void PrimaryAttack() override;
	void Reload() override;
void QuickDeploy() override;
void QuickReload() override;
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
	void DhandgunFire(float flSpread, float flCycleTime, BOOL fUseSemi);

public:
	int m_iShell;
	unsigned short m_usFireDHANDGUN_LEFT;
	unsigned short m_usFireDHANDGUN_RIGHT;
};

#endif
