#include <vp.h>

// 0x807bb200 is the address for itemslot.bin loading

#define CHECK_BUTTON(universal, specific) \
    case universal: return (buttonPressed & specific) != 0;

RaceLoadHook *RaceLoadHook::sHooks = NULL;
RaceFrameHook *RaceFrameHook::sHooks = NULL;
s16 invincibilityTimer[12];

bool CheckButtonPressed(u8 playerHudId, UniversalButtons button){
    u32 controllerInfo = menudata->sub.controllerInfos[0].controllerSlotAndTypeActive;  
    RealControllerHolder *realControllerHolder = &inputdata->realControllerHolders[((controllerInfo & 0xFF00) >> 8)-1];
    u16 buttonPressed = realControllerHolder->inputStates[0].buttonRaw;
    ControllerType controllerType = ControllerType(controllerInfo & 0xFF);

    if (controllerType == WHEEL){
        switch (button){
            CHECK_BUTTON(BUTTON_DPAD_LEFT, WHEEL_DPAD_LEFT)
            CHECK_BUTTON(BUTTON_DPAD_RIGHT, WHEEL_DPAD_RIGHT)
            CHECK_BUTTON(BUTTON_DPAD_DOWN, WHEEL_DPAD_DOWN)
            CHECK_BUTTON(BUTTON_DPAD_UP, WHEEL_DPAD_UP)
            CHECK_BUTTON(BUTTON_A, WHEEL_A)
            CHECK_BUTTON(BUTTON_B, WHEEL_B)
            CHECK_BUTTON(BUTTON_MINUS, WHEEL_MINUS)
            CHECK_BUTTON(BUTTON_PLUS, WHEEL_PLUS)
            CHECK_BUTTON(BUTTON_HOME, WHEEL_HOME)
            CHECK_BUTTON(BUTTON_1, WHEEL_1)
            CHECK_BUTTON(BUTTON_2, WHEEL_2)
            default:
                return false;
        }
    }
    else if (controllerType == NUNCHUCK){
        switch (button){
            CHECK_BUTTON(BUTTON_DPAD_LEFT, NUNCHUCK_DPAD_LEFT)
            CHECK_BUTTON(BUTTON_DPAD_RIGHT, NUNCHUCK_DPAD_RIGHT)
            CHECK_BUTTON(BUTTON_DPAD_DOWN, NUNCHUCK_DPAD_DOWN)
            CHECK_BUTTON(BUTTON_DPAD_UP, NUNCHUCK_DPAD_UP)
            CHECK_BUTTON(BUTTON_A, NUNCHUCK_A)
            CHECK_BUTTON(BUTTON_B, NUNCHUCK_B)
            CHECK_BUTTON(BUTTON_MINUS, NUNCHUCK_MINUS)
            CHECK_BUTTON(BUTTON_PLUS, NUNCHUCK_PLUS)
            CHECK_BUTTON(BUTTON_HOME, NUNCHUCK_HOME)
            CHECK_BUTTON(BUTTON_1, NUNCHUCK_1)
            CHECK_BUTTON(BUTTON_2, NUNCHUCK_2)
            CHECK_BUTTON(BUTTON_C, NUNCHUCK_C)
            CHECK_BUTTON(BUTTON_Z, NUNCHUCK_Z)
            default:
                return false;
        }
        
    }
    else if (controllerType == CLASSIC){
        switch (button){
            CHECK_BUTTON(BUTTON_DPAD_LEFT, CLASSIC_DPAD_LEFT)
            CHECK_BUTTON(BUTTON_DPAD_RIGHT, CLASSIC_DPAD_RIGHT)
            CHECK_BUTTON(BUTTON_DPAD_DOWN, CLASSIC_DPAD_DOWN)
            CHECK_BUTTON(BUTTON_DPAD_UP, CLASSIC_DPAD_UP)
            CHECK_BUTTON(BUTTON_A, CLASSIC_A)
            CHECK_BUTTON(BUTTON_B, CLASSIC_B)
            CHECK_BUTTON(BUTTON_X, CLASSIC_X)
            CHECK_BUTTON(BUTTON_Y, CLASSIC_Y)
            CHECK_BUTTON(BUTTON_MINUS, CLASSIC_MINUS)
            CHECK_BUTTON(BUTTON_PLUS, CLASSIC_PLUS)
            CHECK_BUTTON(BUTTON_HOME, CLASSIC_HOME)
            CHECK_BUTTON(BUTTON_L, CLASSIC_L)
            CHECK_BUTTON(BUTTON_R, CLASSIC_R)
            CHECK_BUTTON(BUTTON_ZL, CLASSIC_ZL)
            CHECK_BUTTON(BUTTON_Z, CLASSIC_Z)
            default:
                return false;
        }
        
    }
    else {
        s8 horizontalCStick = realControllerHolder->gcnStruct->horizontalCStick;
        s8 verticalCStick = realControllerHolder->gcnStruct->verticalCStick;
        switch (button){
            CHECK_BUTTON(BUTTON_DPAD_LEFT, GCN_DPAD_LEFT)
            CHECK_BUTTON(BUTTON_DPAD_RIGHT, GCN_DPAD_RIGHT)
            CHECK_BUTTON(BUTTON_DPAD_DOWN, GCN_DPAD_DOWN)
            CHECK_BUTTON(BUTTON_DPAD_UP, GCN_DPAD_UP)
            CHECK_BUTTON(BUTTON_A, GCN_A)
            CHECK_BUTTON(BUTTON_B, GCN_B)
            CHECK_BUTTON(BUTTON_X, GCN_X)
            CHECK_BUTTON(BUTTON_Y, GCN_Y)
            CHECK_BUTTON(BUTTON_Z, GCN_Z)
            CHECK_BUTTON(BUTTON_PLUS, GCN_START)
            CHECK_BUTTON(BUTTON_L, GCN_L)
            CHECK_BUTTON(BUTTON_R, GCN_R)
            case C_STICK_LEFT:
                return horizontalCStick < -0x20;
            case C_STICK_RIGHT:
                return horizontalCStick > 0x20;
            case C_STICK_UP:
                return verticalCStick > 0x20;
            case C_STICK_DOWN:
                return verticalCStick < -0x20;
            default:
                return false;
        }
        
    }
}

void GetCustomItemWindow(UnkType *r3, char *folderName, char *ctrName, char *locName, char **animNames){
    if (settings.mode == BSS){
        ctrName = "item_window_new_bss";
    }
    else if (settings.mode == BBB){
        ctrName = "item_window_new_bbb";
    }
    ScreenCtr_loadCtr(r3, folderName, ctrName, locName, animNames);
}

kmCall(0x807ef50c, &GetCustomItemWindow);

u32 GetCustomItemSlot(UnkType *archive, u8 src, char *fileName, UnkType *r6){
    if (settings.mode == NOMODE){
        fileName = "ItemSlot0.bin";
    }
    else if (settings.mode == BSS){
        fileName = "ItemSlot1.bin";
    }
    else if (settings.mode == BBB){
        fileName = "ItemSlot2.bin";
    }

    return LoadFromU8(archive, src, fileName, r6);
}

kmCall(0x807bb128, &GetCustomItemSlot);
kmCall(0x807bb030, &GetCustomItemSlot);
kmCall(0x807bb200, &GetCustomItemSlot);
kmCall(0x807bbb58, &GetCustomItemSlot);


void ChangeItemBehaviour(){
    ItemBehaviour *table = itemBehaviourTable;
    table[TRIPLE_BANANA].useType = ITEMUSE_CIRCLE;
    table[BLUE_SHELL].useType = ITEMUSE_FIRE;

    if (settings.mode == BBB){
        table[TRIPLE_GREEN_SHELL].objectId = OBJ_BOBOMB;
        table[TRIPLE_GREEN_SHELL].useType = ITEMUSE_CIRCLE;
        table[MUSHROOM].objectId = OBJ_BOBOMB;
        table[MUSHROOM].useType = ITEMUSE_FIRE;
        table[BULLET_BILL].objectId = OBJ_BOBOMB;
        table[BULLET_BILL].useType = ITEMUSE_CIRCLE;
        table[BULLET_BILL].numberOfItems = 0x3;
    }

    if (settings.mode == BSS){
        table[BULLET_BILL].objectId = OBJ_BLUE_SHELL;
        table[BULLET_BILL].useType = ITEMUSE_CIRCLE;
        table[BULLET_BILL].numberOfItems = 0x3;
    }
}

kmBranch(0x807bd1cc, &ChangeItemBehaviour);

void ChangeItemOBJProperties(int *billTable, ItemOBJProperties *billProperties){
    CopyItemOBJPropertiesFromRelToTable(billTable, billProperties);

    ItemOBJProperties *table = itemObjProperties;

    table[OBJ_BULLET_BILL].limit = 0x2;

    if(settings.mode == BSS){
        table[OBJ_BLUE_SHELL].limit = 0x14;
    }
    if(settings.mode == BBB){
        table[OBJ_BOBOMB].limit = 0x14;
    }
}

kmCall(0x80790c04, &ChangeItemOBJProperties);

// Don't Hide Position After Race
kmWrite32(0x807F4DB8, 0x38000001);

// Show Everyone's Times After Race
kmWrite32(0x8085C914, 0x38000000);
kmWrite32(0x8085D460, 0x4BF984FD);

// Don't Lose VR When Disconnecting
kmWrite32(0x80856560, 0x60000000);

// Coloured Minimap
kmWrite32(0x807DFC24, 0x60000000);

// Unlock Code
kmWrite32(0x80549974, 0x38600001);

// Motion Sensor Bombs
kmWrite16(0x807A5BF6, 0x0FFF);
kmWrite16(0x807A4ACA, 0x0FFF);

void UpdateTimers(){
    for (int i=0; i<12; i++){
        if (invincibilityTimer[i] > 0){
            invincibilityTimer[i]--;
        }
    }
}

static RaceFrameHook updateTimerHook(UpdateTimers);

void ResetTimers(){
    for (int i=0; i<12; i++){
            invincibilityTimer[i] = 0;
        }
}

static RaceLoadHook resetTimerHook(ResetTimers);

void InvincibilityFrames(PlayerSub14 *playersub14, DamageType newDamage, UnkType r5, int r6, u32 r7){ // For Chaotic add random item damage
    if (racedata->main.scenarios[0].settings.gamemode != MODE_BATTLE){
        u8 playerId = playersub14->playerPointers->params->playerIdx;
        if (invincibilityTimer[playerId] > 0){
            return;
        }
        invincibilityTimer[playerId] = 150;
    }
    playersub14->Update(newDamage, r5, r6, r7);
}

kmCall(0x805721a4, &InvincibilityFrames);
kmCall(0x805727b4, &InvincibilityFrames);
kmCall(0x80590d84, &InvincibilityFrames);

kmBranch(0x805320d0, RaceLoadHook::exec);
kmBranch(0x8053369c, RaceFrameHook::exec);

UnkType AllVehiclesInBattle(){
    return 0;
}

kmBranch(0x80860A8C, &AllVehiclesInBattle);
kmWrite32(0x8084FEE8, 0x38000000);
kmWrite32(0x80553FAC, 0x38A00000);

// No Team Invincibility
//kmWrite32(0x80530568, 0x38E00000);

// // VP 200cc

// Minimum Drift Speed Modifier
kmWrite32(0x808B5B1C, 0x3EBBBBBC);

// Engine Class Modifier
kmWrite32(0x808B5CD4, 0x3F666666); //50->100cc
kmWrite32(0x808B5CD8, 0x3F800000); //100->150cc
kmWrite32(0x808B5CDC, 0x3F99999A); //150->200cc

// Max Speed Modifier
kmWrite32(0x808B59F4, 0x43100000);

// Bullet Bill Speed Modifier
kmWrite32(0x808B59F8, 0x432E0000);

// Green Shell Speed Modifier
static PostLECodeHook greenShellSpeedModifier(&GreenShellSpeed, 0x3e6042fc, PostLECodeHook::WRITE32);

// Red Shell Speed Modifier
static PostLECodeHook redShellSpeedModifier(&RedShellSpeed, 0x3e6042b4, PostLECodeHook::WRITE32);

// Blue Shell Speed Modifier
static PostLECodeHook blueShellSpeedModifier(&BlueShellSpeed, 0x3e60431c, PostLECodeHook::WRITE32);

UnkType MegaTC(Player *player, int r4, int r5, int r6){
    UseMegaFunction(player);
    return 0;
}

kmCall(0x80580630, &MegaTC);

u32 AccurateItemRoulette(int r3, int itemBoxSetting, int position, s32 r6, int r7){
    u8 playerId = raceinfo->playerIdInEachPosition[position];
    ItemHolderPlayer itemholder = itemHolder->players[playerId];
    return DecideItem(itemSlotData, itemBoxSetting, position, itemholder.isHuman, 0x1, &itemholder);
}

kmBranch(0x807BB8D0, &AccurateItemRoulette);