#pragma once
#include <kamek.h>
#include <racedata.h>
#include <raceinfo.h>
#include <menudata.h>
#include <settings.h>
#include <playerholder.h>
#include <rknetcontroller.h>
#include <musichandler.h>
#include <common.h>
#include <inputdata.h>
#include <base/c_stdlib.h>
#include <itemholder.h>
#include <playermodel.h>
#include <itembehaviour.h>
#include <itemobjproperties.h>
#include <screen.h>
#include <screenelement.h>
#include <lecode.h>
#include <itemslotdata.h>

bool CheckButtonPressed(u8 playerHudId, UniversalButtons button);
extern int *GreenShellSpeed;
extern int *RedShellSpeed;
extern int *BlueShellSpeed;
extern "C"{
    void SetMatIcon(UnkType *r3, char *materialName, char *iconPaneName);
    int PlayBRSARSound(int r3, u32 soundId, u32 r5);
    void ChangeMusic(MusicHandler *musichandler, RaceState raceState);
    u32 LoadFromU8(UnkType *archive, u8 src, char *fileName, UnkType *r6);
    void ScreenCtr_loadCtr(UnkType *r3, char *folderName, char *ctrName, char *locName, char **animNames);
    void CopyItemOBJPropertiesFromRelToTable(int *itemTable, ItemOBJProperties *itemObjProperties);
    UnkType *ResFile_LoadFromU8(int *r3, UnkType U8Source, char *fileName);
    void UseMegaFunction(Player *player);
    int DecideItem(ItemSlotData *itemSlotData, s32 itemboxSetting, int position, int isHuman, UnkType r7, ItemHolderPlayer *itemHolderPlayer);
}

class RaceLoadHook {
private:
    typedef void (Func)();
    Func *mFunc;
    RaceLoadHook * mNext;

    static RaceLoadHook * sHooks;

public:
    RaceLoadHook(Func * f) {
        mNext = sHooks;
        sHooks = this;
        mFunc = f;
    }

    static void exec() {
        for (RaceLoadHook * p = sHooks; p; p = p->mNext)
            p->mFunc();
    }
};

class RaceFrameHook {
private:
    typedef void (Func)();
    Func *mFunc;
    RaceFrameHook * mNext;

    static RaceFrameHook * sHooks;

public:
    RaceFrameHook(Func * f) {
        mNext = sHooks;
        sHooks = this;
        mFunc = f;
    }

    static void exec() {
        for (RaceFrameHook * p = sHooks; p; p = p->mNext)
            p->mFunc();
    }
};