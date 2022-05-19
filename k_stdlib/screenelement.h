#pragma once
#include <nw4r.h>
#include <screen.h>



class CtrlRaceBase : public LayoutUIControl { //one element is one CtrlRaceBase
public:
    //CtrlRaceBase(); //literally cannot find it
    ~CtrlRaceBase(); //vtable 808d3a98
    virtual void InitSelf(); //called setup pause position on sanbo
    virtual int get809cXXXX(); //returns 809c4010
    virtual char* getClassName();
    virtual void UpdatePausePosition(); //called updatePausePosition
    virtual void func_0x40(); 
    virtual UnkType* func_0x44();
    virtual bool isPaused(); //returns MenuData -> curScene -> isPaused
    virtual bool hasRaceStarted(); //checks raceinfo->timer 
    void HudSlotColorEnabled(char *pane, bool enable); //pane name from the brlyt
    int getControlCount();
    u8 getPlayerId();
    u8 unknown_0x174[0x190-0x174]; //couldn't find the ctor so based on 807f7c18 (ctor for timer element)
    u8 hudSlotId;
    u8 unknown_0x191[0x198-0x191];
};//Total Size 0x198


class ScreenController{
public:
    LayoutUIControl *layoutUIControl;
    ScreenController(LayoutUIControl *r4);
    void LoadCtr(char *folderName, char *ctrName, char *locName, const char **animNames);
    ~ScreenController();
    u8 unknown_0x4[0x28-0x4];

};//Total Size 0x28


class CtrlRaceSpeedo : public CtrlRaceBase {
public:
    virtual void Init();
    virtual void OnUpdate();
    void Load(char* variant, u8 id);
};

extern "C"{
    void DisplayEffect(void* Effect, u32 id, float value);
}




