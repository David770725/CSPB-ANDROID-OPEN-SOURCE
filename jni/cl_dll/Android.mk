#
# Android.mk - CSMoE Client Android Port
# Copyright (c) 2018 Moemod Hyakuya
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

#hlsdk-2.3 client port for android
#Copyright (c) mittorn

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := client

include $(XASH3D_CONFIG)

ifeq ($(TARGET_ARCH_ABI),linux-x86_64)
LOCAL_MODULE_FILENAME = libclient_hardfp
endif

LOCAL_CFLAGS += -fsigned-char -DCLIENT_DLL=1 -DCLIENT_WEAPONS=1 -D_LINUX
LOCAL_CFLAGS += -Dstricmp=strcasecmp -D_strnicmp=strncasecmp -Dstrnicmp=strncasecmp 
LOCAL_CONLYFLAGS += -std=c99
LOCAL_CPPFLAGS += -std=c++11

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
	$(LOCAL_PATH) \
	$(LOCAL_PATH)/hud \
	$(LOCAL_PATH)/studio \
	$(LOCAL_PATH)/../common \
	$(LOCAL_PATH)/../engine \
	$(LOCAL_PATH)/../game_shared \
	$(LOCAL_PATH)/../dlls \
	$(LOCAL_PATH)/../pm_shared \
	$(LOCAL_PATH)/../public \
	$(LOCAL_PATH)/../public/tier1 \

LOCAL_SRC_FILES := \
	./cdll_int.cpp \
	./demo.cpp \
	./entity.cpp \
	./in_camera.cpp \
	./input.cpp \
	./rain.cpp \
	./tri.cpp \
	./util.cpp \
	./view.cpp \
	./input_xash3d.cpp \
	./vgui_parser.cpp \
	../public/unicode_strtools.cpp \
	./draw_util.cpp \
	../pm_shared/pm_debug.c \
	../pm_shared/pm_math.c \
	../pm_shared/pm_shared.c \
	./studio/GameStudioModelRenderer.cpp \
	./studio/StudioModelRenderer.cpp \
	./studio/studio_util.cpp \
	./hud/ammo_secondary.cpp \
	./hud/ammohistory.cpp \
	./hud/battery.cpp \
	./hud/geiger.cpp \
	./hud/health.cpp \
./hud/ammo.cpp \
	./hud/hud.cpp \
./hud/kill_effect.cpp \
	./hud/hud_msg.cpp \
	./hud/hud_redraw.cpp \
	./hud/hud_spectator.cpp \
	./hud/hud_update.cpp \
	./hud/sniperscope.cpp \
	./hud/nvg.cpp \
	./hud/hud_menu.cpp \
./hud/hudBackground.cpp \
	./hud/message.cpp \
	./hud/status_icons.cpp \
	./hud/statusbar.cpp \
	./hud/text_message.cpp \
	./hud/train.cpp \
	./hud/scoreboard.cpp \
	./hud/MOTD.cpp \
	./hud/radio.cpp \
	./hud/radar.cpp \
	./hud/timer.cpp \
	./hud/money.cpp \
	./hud/flashlight.cpp \
	./hud/death.cpp \
	./hud/saytext.cpp \
	./hud/spectator_gui.cpp \
	./hud/followicon.cpp \
	./hud/headname.cpp \
	./hud/zbs/zbs.cpp \
	./hud/zbs/zbs_level.cpp \
	./hud/zbs/zbs_scoreboard.cpp \
	./hud/zbs/zbs_kill.cpp \
	./hud/zbs/zbs_roundclear.cpp \
	./hud/retina.cpp \
	./hud/scenariostatus.cpp \
	./hud/zb2/zb2.cpp \
	./hud/zb2/zb2_skill.cpp \
	./hud/legacy/hud_radar_legacy.cpp \
	./hud/legacy/hud_scoreboard_legacy.cpp \
	./hud/modern/hud_radar_modern.cpp \
	./hud/zb3/zb3.cpp \
	./hud/zb3/zb3_rage.cpp \
	./hud/zb3/zb3_morale.cpp \
	./hud/moe/moe_touch.cpp \
	./com_weapons.cpp \
	./cs_wpn/cs_baseentity.cpp \
	./cs_wpn/cs_weapons.cpp \
	./cs_wpn/bte_weapons.cpp \
	../dlls/wpn_shared/wpn_ak47.cpp \
	../dlls/wpn_shared/wpn_aug.cpp \
	../dlls/wpn_shared/wpn_awp.cpp \
	../dlls/wpn_shared/wpn_c4.cpp \
	../dlls/wpn_shared/wpn_deagle.cpp \
	../dlls/wpn_shared/wpn_flashbang.cpp \
	../dlls/wpn_shared/wpn_glock18.cpp \
	../dlls/wpn_shared/wpn_hegrenade.cpp \
	../dlls/wpn_shared/wpn_m3.cpp \
	../dlls/wpn_shared/wpn_m4a1.cpp \
	../dlls/wpn_shared/wpn_p90.cpp \
	../dlls/wpn_shared/wpn_scout.cpp \
	../dlls/wpn_shared/wpn_sg550.cpp \
	../dlls/wpn_shared/wpn_smokegrenade.cpp \
	../dlls/wpn_shared/wpn_usp.cpp \
../dlls/wpn_shared/wpn_knife.cpp \
../dlls/wpn_shared/wpn_butterfly.cpp \
../dlls/wpn_shared/wpn_m1887.cpp \
../dlls/wpn_shared/wpn_aug_gold.cpp \
../dlls/wpn_shared/wpn_knife_bone.cpp \
../dlls/wpn_shared/wpn_amok.cpp \
../dlls/wpn_shared/wpn_combat.cpp \
../dlls/wpn_shared/wpn_compound_bow.cpp \
../dlls/wpn_shared/wpn_fangblade.cpp \
../dlls/wpn_shared/wpn_aug_blitz.cpp \
../dlls/wpn_shared/wpn_aksopmod.cpp \
../dlls/wpn_shared/wpn_aug_hbar.cpp \
../dlls/wpn_shared/wpn_cheytac_m200.cpp \
../dlls/wpn_shared/wpn_colt_python.cpp \
../dlls/wpn_shared/wpn_deagle_dual.cpp \
../dlls/wpn_shared/wpn_dragunov.cpp \
../dlls/wpn_shared/wpn_dual_handgun.cpp \
../dlls/wpn_shared/wpn_arabian_sword.cpp \
../dlls/wpn_shared/wpn_aug_a3_silencer.cpp \
../dlls/wpn_shared/wpn_m82a1.cpp \
../dlls/wpn_shared/wpn_brass_knuckle.cpp \
../dlls/wpn_shared/wpn_candy_cane.cpp \
../dlls/wpn_shared/wpn_dual_knife.cpp \
../dlls/wpn_shared/wpn_f2000.cpp \
../dlls/wpn_shared/wpn_famas_g2.cpp \
../dlls/wpn_shared/wpn_g36c.cpp \
../dlls/wpn_shared/wpn_groza.cpp \
../dlls/wpn_shared/wpn_k1.cpp \
../dlls/wpn_shared/wpn_pgm.cpp \
../dlls/wpn_shared/wpn_msbs.cpp \
../dlls/wpn_shared/wpn_k2.cpp \
../dlls/wpn_shared/wpn_kar98k.cpp \
../dlls/wpn_shared/wpn_keris.cpp \
../dlls/wpn_shared/wpn_kriss_sv.cpp \
../dlls/wpn_shared/wpn_kriss_sv_dual.cpp \
../dlls/wpn_shared/wpn_kriss_sv_silence.cpp \
../dlls/wpn_shared/wpn_kriss_sv_dual_silence.cpp \
../dlls/wpn_shared/wpn_l86_lsw.cpp \
../dlls/wpn_shared/wpn_m4_cqb_lv1.cpp \
../dlls/wpn_shared/wpn_m4_cqb_lv2.cpp \
../dlls/wpn_shared/wpn_m4_spr_lv1.cpp \
../dlls/wpn_shared/wpn_m4_spr_lv2.cpp \
../dlls/wpn_shared/wpn_mini_axe.cpp \
../dlls/wpn_shared/wpn_mp7.cpp \
../dlls/wpn_shared/wpn_sig.cpp \
../dlls/wpn_shared/wpn_ump.cpp \
../dlls/wpn_shared/wpn_xm8.cpp \
../dlls/wpn_shared/wpn_oa93.cpp \
../dlls/wpn_shared/wpn_tar21.cpp \
../dlls/wpn_shared/wpn_lpg.cpp \
../dlls/wpn_shared/wpn_t77.cpp \
../dlls/wpn_shared/wpn_t77_dual.cpp \
../dlls/wpn_shared/wpn_fg42.cpp \
../dlls/wpn_shared/wpn_spectre.cpp \
../dlls/wpn_shared/wpn_water.cpp \
../dlls/wpn_shared/wpn_oa93_dual.cpp \
../dlls/wpn_shared/wpn_p90_mc.cpp \
../dlls/wpn_shared/wpn_pindad_ss2_v5.cpp \
../dlls/wpn_shared/wpn_rangemaster_338.cpp \
../dlls/wpn_shared/wpn_sc2010.cpp \
../dlls/wpn_shared/wpn_scar_carbine.cpp \
../dlls/wpn_shared/wpn_spas_15.cpp \
../dlls/wpn_shared/wpn_tactilite_t2.cpp \
../dlls/wpn_shared/wpn_taurus_raging_bull.cpp \
../dlls/wpn_shared/wpn_m4a1_s.cpp \
../dlls/wpn_shared/wpn_zombie_s.cpp \
../dlls/wpn_shared/wpn_ice_fork.cpp \
../dlls/wpn_shared/wpn_mp5k.cpp \
../dlls/wpn_shared/wpn_kriss_sv_crb.cpp \
../dlls/wpn_shared/wpn_kriss_sv_dual_crb.cpp \
../dlls/wpn_shared/wpn_medkit.cpp \
../dlls/wpn_shared/wpn_raptor.cpp \
../dlls/wpn_shared/wpn_karambit.cpp \
../dlls/wpn_shared/wpn_as50.cpp \
../dlls/wpn_shared/wpn_apc.cpp \
	./events/ev_cs16.cpp \
	./events/event_ak47.cpp \
	./events/event_aug.cpp \
	./events/event_awp.cpp \
	./events/event_createexplo.cpp \
	./events/event_createsmoke.cpp \
	./events/event_deagle.cpp \
	./events/event_decal_reset.cpp \
	./events/event_elite_left.cpp \
	./events/event_elite_right.cpp \
	./events/event_famas.cpp \
	./events/event_fiveseven.cpp \
	./events/event_g3sg1.cpp \
	./events/event_galil.cpp \
	./events/event_glock18.cpp \
	./events/event_knife.cpp \
	./events/event_m249.cpp \
	./events/event_m3.cpp \
	./events/event_m4a1.cpp \
	./events/event_mac10.cpp \
	./events/event_mp5n.cpp \
	./events/event_p228.cpp \
	./events/event_p90.cpp \
	./events/event_scout.cpp \
	./events/event_sg550.cpp \
	./events/event_sg552.cpp \
	./events/event_tmp.cpp \
	./events/event_ump45.cpp \
	./events/event_usp.cpp \
	./events/event_vehicle.cpp \
	./events/event_xm1014.cpp \
	./events/hl_events.cpp \
	./ev_common.cpp \
	./calcscreen.cpp \
	./input_touch.cpp \
	

include $(BUILD_SHARED_LIBRARY)
