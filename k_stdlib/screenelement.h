#pragma once
#include <nw4r.h>
#include <screen.h>

struct PositionAndScale{
    Vec3 position;
    Vec2 scale;
    u8 opacity;
    u8 unknown_0x15[0x18-0x15];
}; //Total Size 0x18


class AnimationThing{
public:
    AnimationThing(); //0x8063c3ec
    UnkType *array; 
    u32 animationCount; //Unsure
    u32 unknown_0x0[2]; //2nd and 3rd stored at 0x8063c464 check Ghidra
    void *EffectById(u32 id);
}; //Total Size 0x10

class BMGThing{
public:
    BMGThing(); //0x805f8b34
    u32 *pointer_0x0;
    u32 *pointer_0x4;
    u32 *pointer_0x8; //points to UTF-16 strings of all bmg messages
    u32 unknown_0xC;
    u32 *pointer_0x10;
}; //Total Size 0x14

class ParentScreenLayout{
public:
    virtual ~ParentScreenLayout(); //vtable 808b950c
    nw4r::lyt::Layout layout; //from 0x0 to 0x0
    UnkType *pointer1_0x24;    //0x24
}; //Total size 0x28

class ScreenLayout : ParentScreenLayout {
public:
    ScreenLayout(); //vtable 808b94c4
    virtual ~ScreenLayout(); 
    char string[0x44]; //from 0x28 to 0x6
    u8 unknown_0x6C[0x9C-0x6C];
}; //Total Size 0x9C

class UIControl { 
public:
    UIControl(); 
    virtual ~UIControl();  //vtable 808bf008
    virtual void Init();
    virtual void Update();
    virtual void Draw(); //inferred from the name of the child overriden function
    virtual void InitSelf(); //just a blr
    virtual void OnUpdate(); //just a blr
    virtual void setPosition(); 
    virtual void func_805BD2DC(); //just a blr
    virtual int get809cXXXX(); //returns 809c1e80
    virtual char* getClassName(); //how the class name was found
    virtual void func_0x30();
    virtual void func_805bd2d8(); //just a blr
    PositionAndScale positionAndscale[4]; //same structs repeats itself 4 times, but only the last one seems to do anything?
    UnkType *pointer; //0x64 points to the parent class holding all screens 
    ControlGroup controlGroup; 
    bool isVisible;
    u32 isVisible2; //setting this to anything but 0 removes the element
    bool unknown_0x84;
    u8 unknown_0x85[0x8C-0x85];
    float unknown_0x8C;
    u32 unknown_0x90[2];
}; //Total Size 0x98

class LayoutUIControl : public UIControl {
public:
    LayoutUIControl(); //0x8063d798
    virtual ~LayoutUIControl(); //vtable 808befb4
    virtual void Init();
    virtual void Update();
    virtual void Draw();
    virtual int get809cXXXX(); //returns 809c1e84
    virtual char* getClassName(); //how the class name was found
    virtual void func_0x30(); //called screen_buttonHolder
    virtual void func_0x38(); //called screen_buttonHolder too

    AnimationThing AnimationThing;
    ScreenLayout screenLayout;
    BMGThing bmgThing1;
    BMGThing bmgThing2;
    UnkType *pointer_0x16C;
    u32 unknown_0x170;
};//Total Size 0x174

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




