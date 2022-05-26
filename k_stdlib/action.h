#pragma once
#include <kamek.h>
#include <common.h>

/*
typedef enum ScreenInput{ //each value represent an action, itself represented by an actionHandler in PushButton's screenElementActionHolder and a bool in the same struct 
    FORWARD_PRESS,
    BACK_PRESS,
    START_PRESS,
    UP_PRESS,
    DOWN_PRESS,
    LEFT_PRESS,
    RIGHT_PRESS,
    UNK_PRESS,
    SWITCH_PRESS //minus and Z 
};

class ScreenElementActionHolder{
public:
    ScreenElementActionHolder *nextHolder; 
    ScreenElementActionHolder *prevHolder;
    virtual void unk_vtable();
    UnkType *Pane;
    float unk;
    u8 unknown_0x14[0x24-0x14];
    ptmfHolder *onSelectHandler;
    ptmfHolder *onDeselectHandler;
    u8 unknown_0x2c[0x3c-0x2c];
    void *pointer_0x3c;
    ptmfHolder *actionHandlers[8]; //each corresponds to a ScreenInput
    u32 unknown_0x60;
    bool actionsSet[8]; //same
    u8 unknown_0x6c[0x84-0x6c];
}; //total size 0x84

class ScreenActionHolderList{
public:
    virtual void func_vtable();
    ScreenElementActionHolder *actionHolder;
    u32 unknown_0x8;
}; //total size 0xc

class ButtonInfo {
public:
    virtual void func_vtable();
    u32 forwardPressTime; //2 or A
    u32 backPressTime; //1 or B
    u32 startPressTime; //+ or start
    u32 upPressTime;
    u32 downPressTime;    
    u32 leftPressTime;
    u32 rightPressTime;
    u32 unknown_0x20;
    u32 spectateSwitchPressTime; //- + x + z
    u8 unknown_0x28[0x34-0x28];
}; //total size 0x34

class ScreenActionHandler{
public:
    ScreenElementActionHolder *curActionHolder;
    u8 unknown_0x4[4];
    ButtonInfo buttonInfo;
    u32 enabledHandlers;
    u32 resetTime;
    u8 unknown_0x44[0x5C-0x44];
}; //total size 0x5C

class ScreenActionController{
public:
    virtual void func_vtable(); //0x&808b99e8
    u32 playerCount;
    u8 unknown_0x8[0x10-0x8];
    ScreenActionHolderList screenActionHolderList;
    ptmfHolder *handlers[9];
    u8 unknown_0x40[0x54-0x40];
    ScreenActionHandler actionHandlers[5];
    void calcDistance();
    void SetHandler(ScreenInput id, ptmfHolder *handler, bool enable, bool r7);
};//total size 0x224


class PushButton : public LayoutUIControl{
public:
    virtual void unk_vtable();

    ScreenElementActionHolder actionHolder;
    ptmfHolder onSelectHandlerObj;
    ptmfHolder onDeselectHandlerObj;
    ptmfHolder onclickHandlerObj;
    ptmfHolder *onClickHandler;
    ptmfHolder *onSelectHandler;
    ptmfHolder *onDeselectHandler;
    u32 buttonId;
    u32 playerCount;
    u8 unknown_0x248[0x250-0x248];
    void HandleClick(u32 r4, u32 r5);
};//Total Size 0x254

*/