#ifndef WPN_AWP_H
#define WPN_AWP_H
#ifdef _WIN32
#pragma once
#endif

#define BOW_MAX_SPEED            220

class CBow : public CBasePlayerWeapon
{
public:
	void Spawn() override;
	void Precache() override;
	int GetItemInfo(ItemInfo *p) override;
	BOOL Deploy() override;
	
	float GetMaxSpeed() override { return HANDGUN_SPEED; }
	void PrimaryAttack() override;

void ammoGrenade();
void ammoArrow();

void crosshairOn();
void crosshairOff();

	void SecondaryAttack() override;
	void Reload() override;
	void WeaponIdle() override;
	BOOL UseDecrement() override
	{
#ifdef CLIENT_WEAPONS
		return TRUE;
#else
		return FALSE;
#endif
	}
	int m_iMode;
	KnockbackData GetKnockBackData() override 
	{ 
		if (m_iMode)
			//return { 2500, 500, 700, 600, 0.4f };
		//else
			return { 1500, 900, 1000, 900, 0.25f };
	}
	
	int m_iShell;
	float fFinishTime;
bool m_finish = false;
float m_count = 1;
	int iShellOn;
bool m_crosshair = false;
bool shootGrenade;
public:
void Taurus_raging_bullFire(float flSpread, float flCycleTime, BOOL fUseSemi);

private:
	unsigned short m_usFireBow;
};

#endif
