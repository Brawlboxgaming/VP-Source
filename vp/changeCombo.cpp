#include <kamek.h>
#include <menudata.h>
#include <screenelement.h>
#include <screen.h>
#include <specificscreens.h>

ptmfHolder votingSTARThandler;
bool hasStartbeenPressed = false;

void OnStartPress(PushButton *pushButton){
    hasStartbeenPressed = true;
    pushButton->HandleClick(0, -1);
}

void AddChangeComboScreens(Scene *scene, MenuType menuId){
    scene->BuildScreens(menuId);
    if (menuId == P1_WIFI_VS_VOTING || menuId == P1_WIFI_BATTLE_VOTING || menuId == P1_WIFI_FRIEND_ROOM_VS_VOTING || menuId == P1_WIFI_FRIEND_ROOM_TEAM_VS_VOTING 
    || menuId == P1_WIFI_FRIEND_ROOM_BALLOON_VOTING || menuId == P1_WIFI_FRIEND_ROOM_COIN_VOTING) {
          scene->CreateScreen(CHARACTER_SELECT);
    switch(menuId){
        case(P1_WIFI_VS_VOTING):
        case(P1_WIFI_FRIEND_ROOM_VS_VOTING):
        case(P1_WIFI_FRIEND_ROOM_TEAM_VS_VOTING):
            scene->CreateScreen(VEHICLE_SELECT);
        case(P1_WIFI_BATTLE_VOTING):
        case(P1_WIFI_FRIEND_ROOM_COIN_VOTING):
        case(P1_WIFI_FRIEND_ROOM_BALLOON_VOTING):
            scene->CreateScreen(SELECT_VEHICLE_BATTLE);
    }
        scene->CreateScreen(DRIFT_SELECT);

        TimerScreen *timerScreen = (TimerScreen*) scene->screens[TIMER];
        UITimer *timer = &timerScreen->timer;
    
        CharacterSelectScreen *charScreen = (CharacterSelectScreen*) scene->screens[CHARACTER_SELECT];
        charScreen->timer = timer;
        VehicleSelectScreen *vehicleScreen = (VehicleSelectScreen*) scene->screens[VEHICLE_SELECT];
        if (vehicleScreen != NULL){
            vehicleScreen->timer = timer;
        }
        
        VehicleSelectBattleScreen *vehicleBattleScreen = (VehicleSelectBattleScreen*) scene->screens[SELECT_VEHICLE_BATTLE];
        if (vehicleBattleScreen != NULL){
            vehicleBattleScreen->timer = timer;
        }

        DriftSelectScreen *driftScreen = (DriftSelectScreen*) scene->screens[DRIFT_SELECT];
        driftScreen->timer = timer;

        VotingScreen *votingScreen = (VotingScreen*) scene->screens[PLAYER_LIST_VR_SCREEN];
        votingSTARThandler.vtable = (u32) &ptmfVtable;
        votingSTARThandler.subject = &votingScreen->pushButton;
        votingSTARThandler.ptmf.this_delta = 0x0;
        votingSTARThandler.ptmf.vtableOffset = -1;
        votingSTARThandler.ptmf.functionPointer = &OnStartPress;

        votingScreen->screenActionController.SetHandler(START_PRESS, &votingSTARThandler, true, 0);
    }
}

void AddCharSelectLayer(TimerScreen *screen, ScreenType id){
    if (hasStartbeenPressed){
        id = CHARACTER_SELECT;
        CharacterSelectScreen *charScreen = (CharacterSelectScreen*) menuData->curScene->screens[CHARACTER_SELECT];
        charScreen->backButton.isVisible2 = 0x01000000;
        hasStartbeenPressed = false;
              
    } 
    return screen->AddScreenLayer(id);
}

void PatchScreenAfterDrift(InteractableScreen *screen, ScreenType id, u32 animId){
    GameMode gamemode = raceData->main.scenarios[1].settings.gamemode;
    if (gamemode == MODE_PUBLIC_BATTLE || gamemode == MODE_PRIVATE_BATTLE) id = SELECT_BATTLE_CUP;
    return screen->LoadNextScreen(id, animId);
}

kmCall(0x80622088, &AddChangeComboScreens);
kmCall(0x806509d0, &AddCharSelectLayer);
kmCall(0x8084e698, &PatchScreenAfterDrift);

kmWrite32(0x8065086c, 0x38800058);