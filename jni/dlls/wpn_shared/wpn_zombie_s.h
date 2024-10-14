#ifndef WPN_XM1014_H
#define WPN_XM1014_H
#ifdef _WIN32
#pragma once
#endif

//xm1014
#define XM1014_MAX_SPEED	190
#define XM1014_CONE_VECTOR	Vector(0.0725, 0.0725, 0.0)	// special shotgun spreads

class Czombie_s : public CBasePlayerWeapon
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
	KnockbackData GetKnockBackData() override { return { 700.0f, 450.0f, 600.0f, 450.0f, 0.4f }; }

public:
	int m_iShell;
	//float m_flPumpTime;
void EXPORT Smack();
private:
TraceResult m_trHit;
	unsigned short m_usFirezombie_s;
};

#endif
