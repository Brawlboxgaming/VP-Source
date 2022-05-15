#include <vp.h>
#include <ScreenElement.h>

// 0x807bb200 is the address for itemslot.bin loading

#define CHECK_BUTTON(universal, specific) \
    case universal: return (buttonPressed & specific) != 0;

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

void GetCustomItemWindow(ScreenController *screenctr , char *folderName, char *ctrName, char *locName, char **animNames){
    if (settings.mode == BSS){
        ctrName = "item_window_new_bss";
    }
    else if (settings.mode == BBB){
        ctrName = "item_window_new_bbb";
    }
    screenctr->LoadCtr(folderName, ctrName, locName, animNames);
    return;
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

    return;
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

    OSReport("%x", sizeof(ItemOBJProperties));

    return;
}

kmCall(0x80790c04, &ChangeItemOBJProperties);