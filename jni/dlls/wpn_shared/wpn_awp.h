#ifndef WPN_AWP_H
#define WPN_AWP_H
#ifdef _WIN32
#pragma once
#endif

//AWP
#define AWP_MAX_SPEED		180
#define AWP_MAX_SPEED_ZOOM	150
#define AWP_DAMAGE		115
#define AWP_RANGE_MODIFER	0.99
#define AWP_RELOAD_TIME		2.5
#define BOW_MAX_SPEED            240


class CAWP : public CBasePlayerWeapon
{
public:
	void Spawn() override;
	void Precache() override;
	int GetItemInfo(ItemInfo *p) override;
	BOOL Deploy() override;
	float GetMaxSpeed() override { return SNIPER_SPEED; }
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


void Trace(Vector vecSrc, Vector vecDir, float flDamage, float flRadius, int bitsDamageType,
		entvars_t* pevInflictor, entvars_t* pevAttacker);
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
	KnockbackData GetKnockBackData() override { return { 5000.0f, 500.0f, 1200.0f, 800.0f, 0.3f }; }

public:
	void AWPFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
int m_iSprBeam;

private:
	unsigned short m_usFireAWP;
};
#endif
