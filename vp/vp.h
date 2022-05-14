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
    void ResFile_LoadFromU8(int *r3, UnkType U8Source, char *fileName);
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