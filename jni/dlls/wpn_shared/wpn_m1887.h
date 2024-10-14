#ifndef WPN_M3_H
#define WPN_M3_H
#ifdef _WIN32
#pragma once
#endif

//m3
#define M3_MAX_SPEED		190
#define M3_CONE_VECTOR		Vector(0.0675, 0.0675, 0.0)	// special shotgun spreads
#define KNIFE_BODYHIT_VOLUME		128
#define KNIFE_WALLHIT_VOLUME		512
#define KNIFE_MAX_SPEED			250
#define KNIFE_MAX_SPEED_SHIELD		180

class CM1887 : public CBasePlayerWeapon
{
public:
	void Spawn() override;
	void Precache() override;
	int GetItemInfo(ItemInfo *p) override;
	BOOL Deploy() override;
	float GetMaxSpeed() override { return SG_SPEED; }
	int iItemSlot() override { return PRIMARY_WEAPON_SLOT; }
	void PrimaryAttack() override;
void QuickDeploy() override;

void QuickReload() override;
void SecondaryAttack() override;
void Holster(int skiplocal);
void DefaultReloadCall();

void DelayedSecondaryAttack();
	float GetPrimaryAttackDamage() const
	{
		float flDamage = 100;

		return flDamage;
	}
	float GetSecondaryAttackDamage() const
	{
		float flDamage = 100;

		return flDamage;
	}


	void Reload() override;
	void WeaponIdle() override;
	BOOL UseDecrement() override {
#ifdef CLIENT_WEAPONS
		return TRUE;
#else
		return FALSE;
#endif
	}
	KnockbackData GetKnockBackData() override { return { 1800.0f, 480.0f, 900.0f, 600.0f, 0.3f }; }

public:
	int m_iShell;
	float m_flPumpTime;

float m_idletime;
void EXPORT Smack();
private:
TraceResult m_trHit;
	unsigned short m_usFireM1887;
};


//wood
class CM1887_W : public CBasePlayerWeapon
{
public:
	void Spawn() override;
	void Precache() override;
	int GetItemInfo(ItemInfo *p) override;
	BOOL Deploy() override;
	float GetMaxSpeed() override { return M3_MAX_SPEED; }
	int iItemSlot() override { return PRIMARY_WEAPON_SLOT; }
	void PrimaryAttack() override;
void SecondaryAttack() override;
void QuickDeploy() override;
void QuickReload() override;
void DefaultReloadCall();

void Holster(int skiplocal);
void DelayedSecondaryAttack();
	float GetPrimaryAttackDamage() const
	{
		float flDamage = 100;

		return flDamage;
	}
	float GetSecondaryAttackDamage() const
	{
		float flDamage = 100;

		return flDamage;
	}


	void Reload() override;
	void WeaponIdle() override;
	BOOL UseDecrement() override {
#ifdef CLIENT_WEAPONS
		return TRUE;
#else
		return FALSE;
#endif
	}
	KnockbackData GetKnockBackData() override { return { 1800.0f, 480.0f, 900.0f, 600.0f, 0.3f }; }

public:
	int m_iShell;
	float m_flPumpTime;

float m_idletime;
void EXPORT Smack();
private:
TraceResult m_trHit;
	unsigned short m_usFireM1887;
};
#endif
