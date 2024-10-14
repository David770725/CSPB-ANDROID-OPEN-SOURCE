#ifndef WPN_SMOKEGRENADE_H
#define WPN_SMOKEGRENADE_H
#ifdef _WIN32
#pragma once
#endif

//smokegrenade
#define SMOKEGRENADE_MAX_SPEED		200
#define SMOKEGRENADE_MAX_SPEED_SHIELD	180

class CSmokeGrenade : public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL CanDeploy();
	virtual BOOL CanDrop() { return FALSE; }
	virtual BOOL Deploy();
	virtual void Holster(int skiplocal);
	float GetMaxSpeed() override { return KNIFE_SPEED; }
	virtual int iItemSlot() { return GRENADE_SLOT; }
	virtual void PrimaryAttack();
	virtual void SecondaryAttack();

	virtual void WeaponIdle();
	virtual BOOL UseDecrement()
	{
#ifdef CLIENT_WEAPONS
		return TRUE;
#else
		return FALSE;
#endif
	}

public:
	bool ShieldSecondaryFire(int iUpAnim, int iDownAnim);
	void SetPlayerShieldAnim();
	void ResetPlayerShieldAnim();

public:
	unsigned short m_usCreateSmoke;
};

#endif
