#pragma once
#include <nw4r.h>
#include <kamek.h>

struct BasicSound{
    u8 unknown_0x0[0x34];
    float ambientPitch;
    u8 unknown_0x38[0x50-0x38];
    float actorPitch;
    u8 unknown_0x54[0xbc-0x54];
    float volumeRatio;
    u8 unknown_0xc0[0xe8-0xc0];
    nw4r::ut::LinkListNode initialNode;
}; // Total size ???

struct BrstmData{
    u8 unknown_0x0[0x34];
    nw4r::ut::LinkList *linkList;
}; // Total size ???

class SoundData{
    // vtable 0x808d9918
    virtual void unknown_vtable();
    u8 unknown_0x4[0x5bc-0x4];
    BrstmData *brstmData;
    u8 unknown_0x5c0[0x5d0-0x5c0];
    UnkType *audioSystem;
    u8 unknown_0x5c4[0x8c0-0x5d4];
}; // Total size 0x8c0