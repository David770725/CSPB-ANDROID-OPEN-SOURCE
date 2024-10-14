//pb sfuff

#pragma once

class CHudKillEffect: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );
	virtual void Reset( void );
	void UpdateStars();

CHudMsgFunc(killframe);
CHudUserCmd(CommandActivekillframe);

CHudMsgFunc(killframeAnim);
CHudUserCmd(CommandActivekillframeAnim);

CHudMsgFunc(PiercingShot);
CHudUserCmd(CommandActivePiercingShot);

CHudMsgFunc(MissionComplete);
CHudUserCmd(CommandActiveMissionComplete);

CHudMsgFunc(MassKill);
CHudUserCmd(CommandActiveMassKill);

CHudMsgFunc(Pointkill);
CHudUserCmd(CommandActivePointkill);

CHudMsgFunc(Doublekill);
CHudUserCmd(CommandActiveDoublekill);

CHudMsgFunc(Triplekill);
CHudUserCmd(CommandActiveTriplekill);

CHudMsgFunc(Chainkiller);
CHudUserCmd(CommandActiveChainkiller);

CHudMsgFunc(HeadshotPoint);
CHudUserCmd(CommandActiveHeadshotPoint);

CHudMsgFunc(Headshot);
CHudUserCmd(CommandActiveHeadshot);

CHudMsgFunc(ChainHeadshot);
CHudUserCmd(CommandActiveChainHeadshot);

CHudMsgFunc(Helmet);
CHudUserCmd(CommandActiveHelmet);

CHudMsgFunc(Stopper);
CHudUserCmd(CommandActiveStopper);

CHudMsgFunc(Slugger);
CHudUserCmd(CommandActiveSlugger);

CHudMsgFunc(PointNumber);
CHudUserCmd(CommandActivePointNumber);

CHudMsgFunc(HitMarker);
CHudUserCmd(CommandActiveHitMarker);

CHudMsgFunc(HotKiller);
CHudUserCmd(CommandActiveHotKiller);

CHudMsgFunc(Nightmare);
CHudUserCmd(CommandActiveNightmare);

//specific
CHudMsgFunc(SpecialGunner);
CHudUserCmd(CommandActiveSpecialGunner);

CHudMsgFunc(BombShot);
CHudUserCmd(CommandActiveBombShot);

CHudMsgFunc(oneShot);
CHudUserCmd(CommandActiveoneShot);

CHudMsgFunc(OneshotEnable);
CHudUserCmd(CommandActiveOneshotEnable);

CHudMsgFunc(OneshotDisable);
CHudUserCmd(CommandActiveOneshotDisable);


CHudMsgFunc(FragAnimKill);
CHudUserCmd(CommandActiveFragAnimKill);

CHudMsgFunc(FragAnimHs);
CHudUserCmd(CommandActiveFragAnimHs);

CHudMsgFunc(FragAnimStopper);
CHudUserCmd(CommandActiveFragAnimStopper);

CHudMsgFunc(FragAnimBlue);
CHudUserCmd(CommandActiveFragAnimBlue);

CHudMsgFunc(FragAnimGold);
CHudUserCmd(CommandActiveFragAnimGold);

CHudMsgFunc(Pos1);
CHudUserCmd(CommandActivePos1);
CHudMsgFunc(Pos2);
CHudUserCmd(CommandActivePos2);

CHudMsgFunc(KillStar1);
CHudMsgFunc(KillStar2);
CHudMsgFunc(KillStar3);
CHudMsgFunc(KillStar4);
CHudMsgFunc(KillStar5);
CHudMsgFunc(KillStar6);
CHudMsgFunc(KillStar7);
CHudMsgFunc(KillStar8);
CHudMsgFunc(KillStar9);
CHudMsgFunc(KillStar10);

CHudMsgFunc(HeadshotStar1);
CHudMsgFunc(HeadshotStar2);
CHudMsgFunc(HeadshotStar3);
CHudMsgFunc(HeadshotStar4);
CHudMsgFunc(HeadshotStar5);
CHudMsgFunc(HeadshotStar6);
CHudMsgFunc(HeadshotStar7);
CHudMsgFunc(HeadshotStar8);
CHudMsgFunc(HeadshotStar9);
CHudMsgFunc(HeadshotStar10);

CHudMsgFunc(BlueStar5);
CHudMsgFunc(GoldStar10);

CHudMsgFunc(StopperStar1);
CHudMsgFunc(StopperStar2);
CHudMsgFunc(StopperStar3);
CHudMsgFunc(StopperStar4);
CHudMsgFunc(StopperStar5);
CHudMsgFunc(StopperStar6);
CHudMsgFunc(StopperStar7);
CHudMsgFunc(StopperStar8);
CHudMsgFunc(StopperStar9);
CHudMsgFunc(StopperStar10);

CHudMsgFunc(StopperHsStar1);
CHudMsgFunc(StopperHsStar2);
CHudMsgFunc(StopperHsStar3);
CHudMsgFunc(StopperHsStar4);
CHudMsgFunc(StopperHsStar5);
CHudMsgFunc(StopperHsStar6);
CHudMsgFunc(StopperHsStar7);
CHudMsgFunc(StopperHsStar8);
CHudMsgFunc(StopperHsStar9);
CHudMsgFunc(StopperHsStar10);

CHudMsgFunc(SluggerStar1);
CHudMsgFunc(SluggerStar2);
CHudMsgFunc(SluggerStar3);
CHudMsgFunc(SluggerStar4);
CHudMsgFunc(SluggerStar5);
CHudMsgFunc(SluggerStar6);
CHudMsgFunc(SluggerStar7);
CHudMsgFunc(SluggerStar8);
CHudMsgFunc(SluggerStar9);
CHudMsgFunc(SluggerStar10);

CHudMsgFunc(SluggerHsStar1);
CHudMsgFunc(SluggerHsStar2);
CHudMsgFunc(SluggerHsStar3);
CHudMsgFunc(SluggerHsStar4);
CHudMsgFunc(SluggerHsStar5);
CHudMsgFunc(SluggerHsStar6);
CHudMsgFunc(SluggerHsStar7);
CHudMsgFunc(SluggerHsStar8);
CHudMsgFunc(SluggerHsStar9);
CHudMsgFunc(SluggerHsStar10);


CHudUserCmd(CommandActiveKillStar1);
CHudUserCmd(CommandActiveKillStar2);
CHudUserCmd(CommandActiveKillStar3);
CHudUserCmd(CommandActiveKillStar4);
CHudUserCmd(CommandActiveKillStar5);
CHudUserCmd(CommandActiveKillStar6);
CHudUserCmd(CommandActiveKillStar7);
CHudUserCmd(CommandActiveKillStar8);
CHudUserCmd(CommandActiveKillStar9);
CHudUserCmd(CommandActiveKillStar10);

CHudUserCmd(CommandActiveHeadshotStar1);
CHudUserCmd(CommandActiveHeadshotStar2);
CHudUserCmd(CommandActiveHeadshotStar3);
CHudUserCmd(CommandActiveHeadshotStar4);
CHudUserCmd(CommandActiveHeadshotStar5);
CHudUserCmd(CommandActiveHeadshotStar6);
CHudUserCmd(CommandActiveHeadshotStar7);
CHudUserCmd(CommandActiveHeadshotStar8);
CHudUserCmd(CommandActiveHeadshotStar9);
CHudUserCmd(CommandActiveHeadshotStar10);

CHudUserCmd(CommandActiveBlueStar5);
CHudUserCmd(CommandActiveGoldStar10);

CHudUserCmd(CommandActiveStopperStar1);
CHudUserCmd(CommandActiveStopperStar2);
CHudUserCmd(CommandActiveStopperStar3);
CHudUserCmd(CommandActiveStopperStar4);
CHudUserCmd(CommandActiveStopperStar5);
CHudUserCmd(CommandActiveStopperStar6);
CHudUserCmd(CommandActiveStopperStar7);
CHudUserCmd(CommandActiveStopperStar8);
CHudUserCmd(CommandActiveStopperStar9);
CHudUserCmd(CommandActiveStopperStar10);

CHudUserCmd(CommandActiveStopperHsStar1);
CHudUserCmd(CommandActiveStopperHsStar2);
CHudUserCmd(CommandActiveStopperHsStar3);
CHudUserCmd(CommandActiveStopperHsStar4);
CHudUserCmd(CommandActiveStopperHsStar5);
CHudUserCmd(CommandActiveStopperHsStar6);
CHudUserCmd(CommandActiveStopperHsStar7);
CHudUserCmd(CommandActiveStopperHsStar8);
CHudUserCmd(CommandActiveStopperHsStar9);
CHudUserCmd(CommandActiveStopperHsStar10);

CHudUserCmd(CommandActiveSluggerStar1);
CHudUserCmd(CommandActiveSluggerStar2);
CHudUserCmd(CommandActiveSluggerStar3);
CHudUserCmd(CommandActiveSluggerStar4);
CHudUserCmd(CommandActiveSluggerStar5);
CHudUserCmd(CommandActiveSluggerStar6);
CHudUserCmd(CommandActiveSluggerStar7);
CHudUserCmd(CommandActiveSluggerStar8);
CHudUserCmd(CommandActiveSluggerStar9);
CHudUserCmd(CommandActiveSluggerStar10);

CHudUserCmd(CommandActiveSluggerHsStar1);
CHudUserCmd(CommandActiveSluggerHsStar2);
CHudUserCmd(CommandActiveSluggerHsStar3);
CHudUserCmd(CommandActiveSluggerHsStar4);
CHudUserCmd(CommandActiveSluggerHsStar5);
CHudUserCmd(CommandActiveSluggerHsStar6);
CHudUserCmd(CommandActiveSluggerHsStar7);
CHudUserCmd(CommandActiveSluggerHsStar8);
CHudUserCmd(CommandActiveSluggerHsStar9);
CHudUserCmd(CommandActiveSluggerHsStar10);

//item
CHudMsgFunc(buy_qc);
CHudUserCmd(CommandActivebuy_qc);

CHudMsgFunc(buy_megahp);
CHudUserCmd(CommandActivebuy_megahp);

CHudMsgFunc(buy_bpoint);
CHudUserCmd(CommandActivebuy_bpoint);

CHudMsgFunc(buy_qr);
CHudUserCmd(CommandActivebuy_qr);

CHudMsgFunc(buy_mask_1);
CHudUserCmd(CommandActivebuy_mask_1);

CHudMsgFunc(buy_mask_2);
CHudUserCmd(CommandActivebuy_mask_2);

CHudMsgFunc(buy_mask_3);
CHudUserCmd(CommandActivebuy_mask_3);

CHudMsgFunc(buy_mask_4);
CHudUserCmd(CommandActivebuy_mask_4);

CHudMsgFunc(buy_mask_5);
CHudUserCmd(CommandActivebuy_mask_5);
CHudMsgFunc(buy_mask_6);
CHudUserCmd(CommandActivebuy_mask_6);
CHudMsgFunc(buy_mask_7);
CHudUserCmd(CommandActivebuy_mask_7);
CHudMsgFunc(buy_mask_8);
CHudUserCmd(CommandActivebuy_mask_8);
CHudMsgFunc(buy_mask_9);
CHudUserCmd(CommandActivebuy_mask_9);
CHudMsgFunc(buy_mask_10);
CHudUserCmd(CommandActivebuy_mask_10);
CHudMsgFunc(buy_mask_11);
CHudUserCmd(CommandActivebuy_mask_11);
CHudMsgFunc(buy_mask_12);
CHudUserCmd(CommandActivebuy_mask_12);
CHudMsgFunc(buy_mask_13);
CHudUserCmd(CommandActivebuy_mask_13);

CHudMsgFunc(buy_qrespawn);
CHudUserCmd(CommandActivebuy_qrespawn);

CHudMsgFunc(Unequip_mask);
CHudUserCmd(CommandActiveUnequip_mask);

CHudMsgFunc(Count_unit);
CHudUserCmd(CommandActiveCount_unit);

CHudMsgFunc(Add_point);
CHudUserCmd(CommandActiveAdd_point);

public:
int m_HUD_cross;

long killframe_time;
long killframeAnim_time;

long Pointkill_time;
long Doublekill_time;
long Triplekill_time;
long Chainkiller_time;
long HeadshotPoint_time;
long Headshot_time;
long ChainHeadshot_time;
long Helmet_time;
long Stopper_time;
long Slugger_time;
long PointNumber_time;
long HitMarker_time;
long PiercingShot_time;
long MassKill_time;

long HotKiller_time;
long Nightmare_time;

//special
long SpecialGunner_time;
long BombShot_time;
long oneShot_time;

long FragAnimKill_time;
long FragAnimHs_time;
long FragAnimStopper_time;
long FragAnimBlue_time;
long FragAnimGold_time;


long KillStar1_time;
long KillStar2_time;
long KillStar3_time;
long KillStar4_time;
long KillStar5_time;
long KillStar6_time;
long KillStar7_time;
long KillStar8_time;
long KillStar9_time;
long KillStar10_time;

long HeadshotStar1_time;
long HeadshotStar2_time;
long HeadshotStar3_time;
long HeadshotStar4_time;
long HeadshotStar5_time;
long HeadshotStar6_time;
long HeadshotStar7_time;
long HeadshotStar8_time;
long HeadshotStar9_time;
long HeadshotStar10_time;

long BlueStar5_time;
long GoldStar10_time;

long StopperStar1_time;
long StopperStar2_time;
long StopperStar3_time;
long StopperStar4_time;
long StopperStar5_time;
long StopperStar6_time;
long StopperStar7_time;
long StopperStar8_time;
long StopperStar9_time;
long StopperStar10_time;

long StopperHsStar1_time;
long StopperHsStar2_time;
long StopperHsStar3_time;
long StopperHsStar4_time;
long StopperHsStar5_time;
long StopperHsStar6_time;
long StopperHsStar7_time;
long StopperHsStar8_time;
long StopperHsStar9_time;
long StopperHsStar10_time;

long SluggerStar1_time;
long SluggerStar2_time;
long SluggerStar3_time;
long SluggerStar4_time;
long SluggerStar5_time;
long SluggerStar6_time;
long SluggerStar7_time;
long SluggerStar8_time;
long SluggerStar9_time;
long SluggerStar10_time;

long SluggerHsStar1_time;
long SluggerHsStar2_time;
long SluggerHsStar3_time;
long SluggerHsStar4_time;
long SluggerHsStar5_time;
long SluggerHsStar6_time;
long SluggerHsStar7_time;
long SluggerHsStar8_time;
long SluggerHsStar9_time;
long SluggerHsStar10_time;

long MissionComplete_time;

long Pos1_time;

long Pos2_time;

long hit_time;


private:

UniqueTexture m_killframe;

UniqueTexture m_MissionComplete;

UniqueTexture m_kill1[20];
UniqueTexture m_hspoint[20];
UniqueTexture m_kill2[20];
UniqueTexture m_kill3[20];
UniqueTexture m_kill4[20];
UniqueTexture m_stopper[20];
UniqueTexture m_helmet[20];
UniqueTexture m_headshot[20];
UniqueTexture m_chheadshot[20];
UniqueTexture m_chslugger[20];
UniqueTexture m_piercing[20];
UniqueTexture m_mass[20];
UniqueTexture m_point[4];
UniqueTexture m_hitmarker;
UniqueTexture m_hotkiller[20];
UniqueTexture m_nightmare[20];
UniqueTexture m_fraganim[20];
//special 
UniqueTexture m_special[20];

//underneath stars
UniqueTexture m_starPos1Kill1[11];
UniqueTexture m_starPos1Kill2[11];
UniqueTexture m_starPos1Kill3[11];
UniqueTexture m_starPos1Kill4[11];
UniqueTexture m_starPos1Kill5[11];
UniqueTexture m_starPos1Kill6[11];
UniqueTexture m_starPos1Kill7[11];
UniqueTexture m_starPos1Kill8[11];
UniqueTexture m_starPos1Kill9[11];

UniqueTexture m_starPos2Kill1[11];
UniqueTexture m_starPos2Kill2[11];
UniqueTexture m_starPos2Kill3[11];
UniqueTexture m_starPos2Kill4[11];
UniqueTexture m_starPos2Kill5[11];
UniqueTexture m_starPos2Kill6[11];
UniqueTexture m_starPos2Kill7[11];
UniqueTexture m_starPos2Kill8[11];
UniqueTexture m_starPos2Kill9[11];
UniqueTexture m_starPos2Kill10[11];

UniqueTexture m_hit;
};
