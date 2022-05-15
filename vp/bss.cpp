#include <vp.h>

bool BlueShellSwapping(bool hasItem){
    if (settings.mode == BSS){
        for(int i=0; i<4; i++){
            u8 playerId = (&racedata->main)->scenarios[0].settings.hudPlayerIds[i];
            if (playerId != 0xFF){
                ItemId currentItem = itemholder->players[playerId].inventory.currentItemId;
                if (currentItem == BLUE_SHELL){
                    bool switchItem = false;
                    if(CheckButtonPressed(playerId, BUTTON_MINUS)){
                        switchItem = true;
                    }
                    else if ((menudata->sub.controllerInfos[0].controllerSlotAndTypeActive & 0xFF) == GCN){
                        if (CheckButtonPressed(playerId, C_STICK_LEFT) || 
                            CheckButtonPressed(playerId, C_STICK_RIGHT) ||
                            CheckButtonPressed(playerId, C_STICK_UP) ||
                            CheckButtonPressed(playerId, C_STICK_DOWN)){
                            switchItem = true;
                        }
                    }
                    if (switchItem){
                        itemholder->players[playerId].inventory.currentItemId = TRIPLE_MUSHROOM;
                        u8 mushroomCount = 3;
                        u8 playerCount = itemholder->playerCount;
                        u8 position = raceinfo->players[playerId]->position;
                        float third = (float)(position/playerCount);
                        if (third <= 1/3){
                            mushroomCount = 1;
                        }
                        else if (third <= 2/3){
                            mushroomCount = 2;
                        }

                        itemholder->players[playerId].inventory.currentItemCount = mushroomCount;
                    }
                }
            }
        }
    }

    return hasItem;
}

kmBranch(0x807eeed0, &BlueShellSwapping);