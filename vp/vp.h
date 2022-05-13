#pragma once
#include <kamek.h>
#include <racedata.h>
#include <raceinfo.h>
#include <menudata.h>
#include <settings.h>
#include <player.h>
#include <rknetcontroller.h>
#include <musichandler.h>
#include <common.h>
#include <inputdata.h>
#include <base/c_stdlib.h>
#include <item.h>
#include <playermodel.h>
#include <itembehaviour.h>
#include <itemobjproperties.h>

bool CheckButtonPressed(u8 playerHudId, UniversalButtons button);
extern "C"{
    void SetMatIcon(UnkType *r3, char *materialName, char *iconPaneName);
    int PlayBRSARSound(int r3, u32 soundId, u32 r5);
    void ChangeMusic(MusicHandler *musichandler, RaceState raceState);
    u32 LoadFromU8(UnkType *archive, u8 src, char *fileName, UnkType *r6);
    void ScreenCtr_loadCtr(UnkType *r3, char *folderName, char *ctrName, char *locName, char **animNames);
    void CopyItemOBJPropertiesFromRelToTable(int *itemTable, ItemOBJProperties *itemObjProperties);
}