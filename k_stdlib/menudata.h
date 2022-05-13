/*
MenuData is the class that holds the information about the current displayed Menu.
*/

#pragma once
#include <common.h>
#include <kamek.h>
#include <inputdata.h>

typedef enum ControllerType{
    WHEEL=0x11,
    NUNCHUCK=0x12,
    CLASSIC=0x13,
    GCN=0x24
};

typedef enum GhostType {
    BEST_TIME=0x1,
    CONTINENTAL_RECORD=0x2,
    WORLD_RECORD=0x2,
    FLAG_GHOST=0x4,
    GHOST_RACE=0x6,
    EASY_STAFF_GHOST=0x25,
    EXPERT_STAFF_GHOST=0x26
};

typedef enum MenuCategory {
    CATEGORY_ACTION=0x0,
    CATEGORY_MENU=0x1,
    CATEGORY_GAMEPLAY=0x2,
    CATEGORY_TEST=0x3,
    CATEGORY_ONLINE_MENU=0x4,
    CATEGORY_UNK5=0x5,
    CATEGORY_UNK6=0x6,
    CATEGORY_UNK7=0x7,
    CATEGORY_UNK8=0x8,
    CATEGORY_UNK9=0x9,
    CATEGORY_UNK10=0xa,
    CATEGORY_UNK11=0xb
};

typedef enum MenuState {
    NO_TRANSITION=0x0,
    SET_TRANSITION=0x1,
    SCREEN_DISABLED=0x2,
    MENU_ENDTRANSITION=0x3,
    SCREEN_ENDTRANSITION=0x4
};

typedef enum MenuType {
    POWER_OFF_WII=0x0,
    RETURN_TO_WII_MENU_1=0x4,
    RETURN_TO_WII_MENU_2=0x5,
    TEST_6=0x6,
    TEST_7=0x7,
    TEST_8=0x8,
    TEST_9=0x9,
    TEST_A=0xa,
    TEST_B=0xb,
    TEST_C=0xc,
    TEST_D=0xd,
    TEST_E=0xe,
    TEST_F=0xf,
    CREATE_NEW_SAVE=0x10,
    CORRUPTED_SAVE=0x11,
    COUNTRY_CHANGED=0x12,
    GAME_CANNOT_BE_SAVED=0x13,
    CANNOT_ACCESS_SYSTEM_MEMORY=0x14,
    CANNOT_ACCESS_MII_DATA=0x15,
    ESRB_NOTICE=0x16,
    RECOMMEND_60HZ_1=0x17,
    RECOMMEND_60HZ_2=0x18,
    GRAND_PRIX_PANORAMA=0x19,
    VS_RACE_PANORAMA=0x1a,
    BALLOON_BATTLE_PANORAMA=0x1b,
    MISSION_BOSS_PANORAMA=0x1c,
    COMPETITON_BOSS_PANORAMA=0x1d,
    GRAND_PRIX_GAMEPLAY=0x1e,
    TIME_TRIAL_GAMEPLAY=0x1f,
    P1_VS_RACE_GAMEPLAY=0x20,
    P2_VS_RACE_GAMEPLAY=0x21,
    P3_VS_RACE_GAMEPLAY=0x22,
    P4_VS_RACE_GAMEPLAY=0x23,
    P1_TEAM_VS_RACE_GAMEPLAY=0x24,
    P2_TEAM_VS_RACE_GAMEPLAY=0x25,
    P3_TEAM_VS_RACE_GAMEPLAY=0x26,
    P4_TEAM_VS_RACE_GAMEPLAY=0x27,
    P1_BATTLE_GAMEPLAY=0x28,
    P2_BATTLE_GAMEPLAY=0x29,
    P3_BATTLE_GAMEPLAY=0x2a,
    P4_BATTLE_GAMEPLAY=0x2b,
    MISSION_MODE_GAMEPLAY=0x2c,
    TOURNAMENT_GAMEPLAY=0x2d,
    GRAND_PRIX_REPLAY=0x2e,
    TIME_TRIAL_REPLAY=0x2f,
    GHOST_RACE_GAMEPLAY_1=0x30,
    GHOST_RACE_GAMEPLAY_2=0x31,
    WATCH_GHOST_FROM_CHANNEL=0x32,
    WATCH_GHOST_FROM_DOWNLOADS=0x33,
    WATCH_GHOST_FROM_MENU=0x34,
    GRAND_PRIX_AWARD=0x35,
    VS_RACE_AWARD=0x36,
    AWARD_37=0x37,
    AWARD_38=0x38,
    ENDING_NORMAL_A=0x39,
    ENDING_TRUE_A=0x3a,
    ENDING_NORMAL_B=0x3b,
    ENDING_TRUE_B=0x3c,
    CONGRATULATIONS=0x3d,
    CONGRATULATIONS_COMPLETE=0x3e,
    MAIN_MENU_FROM_BOOT=0x3f,
    MAIN_MENU_FROM_RESET=0x40,
    MAIN_MENU_FROM_MENU=0x41,
    MAIN_MENU_FROM_NEW_LICENSE=0x42,
    MAIN_MENU_FROM_LICENSE_43=0x43,
    DEMO=0x44,
    MII_SELECT_1=0x45,
    MII_SELECT_2=0x46,
    LICENSE_SETTINGS=0x47,
    SINGLE_PLAYER_FROM_MENU=0x48,
    SINGLE_PLAYER_TT_CHANGE_CHARA=0x49,
    SINGLE_PLAYER_TT_CHANGE_COURSE=0x4a,
    SINGLE_PLAYER_VS_NEXT_RACE=0x4b,
    SINGLE_PLAYER_BT_NEXT_BATTLE=0x4c,
    SINGLE_PLAYER_MR_CHOOSE_MISSION=0x4d,
    SINGLE_PLAYER_CHAN_RACE_GHOST=0x4e,
    SINGLE_PLAYER_LB_RACE_GHOST=0x4f,
    SINGLE_PLAYER_LIST_RACE_GHOST=0x50,
    SEND_GHOST_TO_FRIEND=0x51,
    RACE_GHOST_FROM_CHAN_BOOT=0x52,
    WATCH_REPLAY_FROM_CHAN_BOOT=0x53,
    LOCAL_MULTIPLAYER=0x54,
    P1_WIFI=0x55,
    P1_WIFI_GLOBE_DISCONNECT=0x56,
    P1_WIFI_FROM_FIND_FRIEND=0x57,
    P1_WIFI_VS_VOTING=0x58,
    P1_WIFI_BATTLE_VOTING=0x59,
    P2_WIFI_SELECT_MII=0x5a,
    P2_WIFI=0x5b,
    P2_WIFI_GLOBE_DISCONNECT=0x5c,
    UNKNOWN_5D=0x5d,
    P2_WIFI_VS_VOTING=0x5e,
    P2_WIFI_BATTLE_VOTING=0x5f,
    P1_WIFI_FRIEND_ROOM_VS_VOTING=0x60,
    P1_WIFI_FRIEND_ROOM_TEAM_VS_VOTING=0x61,
    P1_WIFI_FRIEND_ROOM_BALLOON_VOTING=0x62,
    P1_WIFI_FRIEND_ROOM_COIN_VOTING=0x63,
    P2_WIFI_FRIEND_ROOM_VS_VOTING=0x64,
    P2_WIFI_FRIEND_ROOM_TEAM_VS_VOTING=0x65,
    P2_WIFI_FRIEND_ROOM_BALLOON_VOTING=0x66,
    P2_WIFI_FRIEND_ROOM_COIN_VOTING=0x67,
    P1_WIFI_VS_GAMEPLAY=0x68,
    P2_WIFI_VS_GAMEPLAY=0x69,
    P1_WIFI_VS_LIVE_VIEW=0x6a,
    P2_WIFI_VS_LIVE_VIEW=0x6b,
    P1_WIFI_BT_GAMEPLAY=0x6c,
    P2_WIFI_BT_GAMEPLAY=0x6d,
    P1_WIFI_BT_LIVE_VIEW=0x6e,
    P2_WIFI_BT_LIVE_VIEW=0x6f,
    P1_WIFI_FRIEND_VS_GAMEPLAY=0x70,
    P1_WIFI_FRIEND_TEAM_VS_GAMEPLAY=0x71,
    P1_WIFI_FRIEND_BALLOON_BT_GAMEPLAY=0x72,
    P1_WIFI_FRIEND_COIN_BT_GAMEPLAY=0x73,
    P2_WIFI_FRIEND_VS_GAMEPLAY=0x74,
    P2_WIFI_FRIEND_TEAM_VS_GAMEPLAY=0x75,
    P2_WIFI_FRIEND_BALLOON_BT_GAMEPLAY=0x76,
    P2_WIFI_FRIEND_COIN_BT_GAMEPLAY=0x77,
    WIFI_DISCONNECT_ERROR=0x78,
    WIFI_DISCONNECT_GENERAL=0x79,
    CHANNEL_FROM_MENU=0x7a,
    CHANNEL_FROM_CHECK_RANKINGS=0x7b,
    CHANNEL_FROM_DOWNLOADS=0x7c,
    TIME_TRIAL_LEADERBOARDS=0x7d,
    TOURNAMENT_LEADERBOARDS=0x7e,
    GHOST_RACE_WITH_DATA=0x7f,
    GHOST_RACE_WITHOUT_DATA=0x80,
    GHOST_RACE_NEXT_RACE=0x81,
    DOWNLOADED_GHOST_DATA=0x82,
    FRIENDS_LIST_1=0x83,
    FRIENDS_LIST_2=0x84,
    TOURNAMENT=0x85,
    TOURNAMENT_CHANGE_CHARA=0x86,
    TOURNAMENT_SUBMIT_RECORD=0x87,
    TOURNAMENT_WII_WHEEL_ONLY=0x88,
    TOURNAMENT_WII_WHEEL_ONLY_BOSSES=0x89,
    INVITE_FRIENDS_FROM_MSG_BOARD=0x8a,
    DOWNLOAD_LATEST_DATA=0x8b,
    OPTIONS=0x8c,
    INSTALL_CHANNEL=0x8d,
    CHOOSE_REGION=0x8e,
    JOIN_MESSAGE_SERVICE=0x8f,
    MSG_UNLOCK_ORANGE1=0x90,
    MSG_UNLOCK_ORANGE2=0x91,
    MSG_UNLOCK_BLUE=0x92,
    MSG_UNLOCK_YELLOW=0x93,
    BROKEN_MISSION_MODE_MENU=0x94,
    MENU_NONE=0xFFFFFFFF
};

struct ControllerInfo{
    u32 controllerSlotAndType;
    u32 controllerSlotAndTypeActive;
    u32 wantsController;
    ControllerHolder * controllerHolder; // see inputdata.h
}; // datasize 0x10

struct Scene {
public:
    MenuType menuId;
    u32 openingAnimIdx;
    void *screens[0xD2]; //https://wiki.tockdom.com/wiki/List_of_Identifiers#Screen_Identifiers
    void *activeScreens[11];
    u32 layerCount;
    void *controllerDisconnectedScreen;
    void *cursor;
    bool hideCursor; /* ? */
    bool pauseGame;
    bool controllerDcPause;
    bool isPaused;
	u8 unknown_0x38C[0x390 - 0x38C];

	u8 drawInfo[0x54];
    u32 * layoutHeap;
    u32 * *arcResourceAccessor;
    void * *iconLayout;
    float pointerTranslationBoxSize[2];
    float pointerScale[2];
    u32 videoPlayer;
    u32 friendList;
};//Total Size 0x408

struct MenuData98{
public:
	u8 unknown_0x0[0x60];
	u32 vsRaceLimit;
	u32 raceCount;
	u8 unknown_0x68[0x124 - 0x68];
	u32 humanPlayerCount;
	u8 unknown_0x128[0x14c - 0x128];
	u32 lastSelectedCourse;
	u32 lastSelectedStage;
	u8 unknown_0x154[0x220 - 0x154];
	s32 selCharacter;
	s32 selVehicle;
	s8 starRank;
	u8 unknown_0x229[0x2D0 - 0x229];
	u32 currentRaceNumber;
	u8 unknown_0x2D4[0x3C4 - 0x2D4];
	GhostType ghostType;
	CourseId courseId;
	u8 unknown_0x3CC[0x4E8 - 0x3CC];
	u8 licenseNum;
	u8 unknown_0x4e9[0x510 - 0x4E9];
}; //Total Size 0x510


class MenuDataSub{
public:
    virtual int vtableTemp();
	//vtable 0x808BB44
	ControllerInfo controllerInfos[4];
	u8 unknown_0x80[0x88 - 0x80];
	u32 isTransitionDone;
}; //Total size 0x5C



class MenuData {
public:
    Scene* curScene; /* http://wiki.tockdom.com/wiki/List_of_Identifiers#Menu_Identifiers */
    MenuType menuType[2];
    u32 nextMenuId;
    u32 prevMenuId;
    u32 openingTransitionAnimIdx;
    u32 transitionAnimIdx;
    u32 transitionDelay;
    bool firstLoad;
	u8 unknown_0x21[3];

    u32 homeMenuAction;
    u32 transitionParam;
    u32 transitionFrame;
    MenuState transitionState;
    MenuDataSub sub; /* length is uncertain */
    u32 field17_0x90; /* 0x128 struct */
    u32 *field18_0x94; /* 0x14 struct */
    MenuData98 *menudata98;
}; //Total Size 0x9C

extern MenuData *menudata;