#ifndef WPN_GALIL_H
#define WPN_GALIL_H
#ifdef _WIN32
#pragma once
#endif

//oa
class COA93 : public CBasePlayerWeapon
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
	void SecondaryAttack();
	void Reload() override;
	void WeaponIdle() override;
	BOOL UseDecrement() override {
#ifdef CLIENT_WEAPONS
		return TRUE;
#else
		return FALSE;
#endif
	}

	KnockbackData GetKnockBackData() override { return { 350.0f, 250.0f, 300.0f, 100.0f, 0.6f }; }
	float GetArmorRatioModifier() override { return 1.4; }
	const char *GetCSModelName() override { return "models/w_scar.mdl"; }

#ifndef CLIENT_DLL
	virtual void AttachToPlayer(CBasePlayer *pPlayer) override;
	virtual void ItemPostFrame() override;
	~COA93();
#endif

public:
	void OA93Fire(float flSpread, float flCycleTime, BOOL fUseAutoAim);
	float GetDamage();

public:
	int m_iShell;
	int iShellOn;
private:
	unsigned short m_usFireOa93;
};
#endif
