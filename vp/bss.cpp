#include <vp.h>

bool BlueShellSwapping(bool hasItem){
    if (settings.mode == BSS){
        for(int i=0; i<4; i++){
            u8 playerId = (&raceData->main)->scenarios[0].settings.hudPlayerIds[i];
            if (playerId != 0xFF){
                ItemId currentItem = itemHolder->players[playerId].inventory.currentItemId;
                if (currentItem == BLUE_SHELL){
                    bool switchItem = false;
                    if(CheckButtonPressed(playerId, BUTTON_MINUS)){
                        switchItem = true;
                    }
                    else if ((menuData->sub.controllerInfos[0].controllerSlotAndTypeActive & 0xFF) == GCN){
                        if (CheckButtonPressed(playerId, C_STICK_LEFT_EIGHT) || 
                            CheckButtonPressed(playerId, C_STICK_RIGHT_EIGHT) ||
                            CheckButtonPressed(playerId, C_STICK_UP_EIGHT) ||
                            CheckButtonPressed(playerId, C_STICK_DOWN_EIGHT)){
                            switchItem = true;
                        }
                    }
                    if (switchItem){
                        itemHolder->players[playerId].inventory.currentItemId = TRIPLE_MUSHROOM;
                        u8 mushroomCount = 3;
                        u8 playerCount = itemHolder->playerCount;
                        u8 position = raceInfo->players[playerId]->position;
                        float third = (float)position/(float)playerCount;
                        if (third <= 1.0f/3.0f){
                            mushroomCount = 1;
                        }
                        else if (third <= 2.0f/3.0f){
                            mushroomCount = 2;
                        }

                        itemHolder->players[playerId].inventory.currentItemCount = mushroomCount;
                    }
                }
            }
        }
    }

    return hasItem;
}

kmBranch(0x807eeed0, &BlueShellSwapping);