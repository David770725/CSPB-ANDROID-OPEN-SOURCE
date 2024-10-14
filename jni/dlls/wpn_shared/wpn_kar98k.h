#ifndef WPN_SG552_H
#define WPN_SG552_H
#ifdef _WIN32
#pragma once
#endif

//sg552
#define SG552_MAX_SPEED			160
#define SG552_MAX_SPEED_ZOOM		200
#define SG552_DAMAGE			33
#define SG552_RANGE_MODIFER		0.955
#define SG552_RELOAD_TIME		3

class CKar98k : public CBasePlayerWeapon
{
public:
	virtual void Spawn();
	virtual void Precache();
	virtual int GetItemInfo(ItemInfo *p);
	virtual BOOL Deploy();
	float GetMaxSpeed() override { return HEAVY_SNIPER_SPEED; }
	virtual int iItemSlot() { return PRIMARY_WEAPON_SLOT; }
	virtual void PrimaryAttack();
void Fov2();
void QuickDeploy() override;
void QuickReload() override;
void Fov3();
void Fov4();
void Fov5();
void Fov6();
void Fov7();
void DefaultReloadCall();

void offFov2();
void offFov3();
void offFov4();
void offFov5();
void offFov6();
void offFov7();
void Holster(int skiplocal) override;
void breath();


	virtual void SecondaryAttack();
	virtual void Reload();
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
	void Kar98kFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);

	int m_iShell;
	int iShellOn;

private:
	unsigned short m_usFireAWP;
};

#endif
