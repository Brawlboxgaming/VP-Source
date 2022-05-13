#pragma once
#include <kamek.h>
#include <egg.h>
#include <nw4r.h>
#include <common.h>
#include <player.h>

class ItemHolderPlayer;

class PlayerModel;

class Item_KouraTogezo { //yoinked that from sanbo, idk where it's used but I'm keeping it
public:
    virtual int unknown_vtable_0x0();
    u8 unknown_0x4[0x290-0x4];
    float distance[3];
    u8 unknown_0x29c[0x2c4-0x29c];
    u8 currentState;
    u8 unknown_0x2c8[0x2d0-0x2c8];
    u16 * stateIds;
    UnkType stateTable;
    UnkType *self_pointer;
    u8 unknown_0x2dc[0x2ec-0x2dc];
    u8 targetPlayer;
    u8 unknown_0x2ed[0x338-0x2ed];
}; // Total size 0x338


class ItemObject { //Called ItemControllerSub by Ssanbo seems to be the parent class of item type specific ones
public:
    virtual int unknown_vtable();
    u8 unknown_0x4[0x174-0x4]; //has a bunch of Vec3s, probably for speed/scale
};//Total Size 0x174


class PlayerRoulette{
public:
    ItemHolderPlayer *itemHolderPlayer;
    u32 unknown_0x4[3];
    float unknown_0x10[2];
    u32 currentItem;
    u32 nextItem;
    ItemId nextItemId;
    u32 unknown_0x24;
    u16 setting;
    u8 position;
    u8 unknown_0x2B[0x30-0x2b];
    u32 itemNum; //how many items have you pulled so far, useful for mushroom bug
}; //Total Size 0x34


class PlayerInventory{
public:
    ItemHolderPlayer *itemHolderPlayer;
    ItemId currentItemId;
    u32 currentItemCount;
    u8 unknown_0xC[0x2C-0xC];
}; //Total Size 0x2C


class ItemHolderPlayerSub {
public:
    PlayerPointers *playerPointers;
    ItemHolderPlayer *itemHolderPlayer;
    u8 unknown_0x8[4];
    ItemHolderPlayer *itemHolderPlayer2;
    u8 id;
    u8 unknown0x11[0x14-0x11];
    ItemObjectId itemObjId; //seems to only change for items you can hold "behind" (including triple shells)
    ItemId itemId; //same
    u32 useType; //0x1 if trailing behind 0x2 if trailing behind triples, 0x3 if spinning, 0x4 if no item
    u8 unknown_0x20[0x50-0x20]; //this whole part only changes when trailing/using bananas/shells
    u32 activeItemCount; // eg 0x2 if 2 remaining spinning shells
    u32 unknown_0x54;
    Vec3 playerLeft;
    Vec3 playerUp;
    Vec3 playerFront;
    Vec3 pos;
    Vec3 unknown_0x88;
    u8 unknown_0x94[0xb0-0x94];
    Vec3 itemScale;
    u8 unknown_0xbc[0xc0-0xbc];
    Vec3 unknown_0xc0;
    u8 unknown_0xcc[0xd0-0xcc];
    Vec2 rotatingRadius;
    float unknown_0xd8[2];
    float itemScaleFactor;
    Vec3 itemPos; //relative to the player 0xE4
    u8 unknown_0xf0[0x174-0xF0];
    u16 spawnedObjs[3];
    u8 unknown_0x17a[0x180-0x17a];
}; //Total Size 0x180

class ItemHolderPlayer {
public:
    PlayerPointers *playerPointers;
    PlayerModel *model;
    u8 unknown_0xC[0x19-0xC];
    u8 id;
    bool isHuman;
    bool isRemote;
    bool isBike;
    Player *player;
    PlayerModel *model2;
    Vec3 unknown_0x24;
    u8 unknown_0x30[0x44-0x30];
    PlayerItemPoint itemPoint;  //currently in player.h but will end up in KMP.h
    PlayerRoulette roulette;
    PlayerInventory inventory;
    ItemHolderPlayerSub itemHolderPlayerSub;
    u32 localPlayerNum;
    u8 unknown_0x238[0x248-0x238];
}; //Total Size 0x248

class ItemHolderItem { // one instance per object ID
public:
    ItemObjectId itemObjectId;
    ItemObject **itemObject;
    u32 capacity; //unsure what the diff is with limit
    u32 capacity2;
    u32 objCount; //count on the track, including trailing/spinning
    u8 unknown_0x14[0x1c-0x14];
    u32 limit;
    u8 unknown_0x20[0x24-0x20];
};//Total Size 0x24

class ItemHolder : public EGG::Disposer {
public:
    u8 playerCount;
    u8 unknown_0x11[3];
    ItemHolderPlayer *players;
    ItemHolderPlayer *otherLocalOnlinePlayersplayer[12];
    ItemHolderItem itemHolderItem[0xF]; //One per objectId
    UnkType *unknown_ptr[16];
    ItemObject itemObj;
    u8 unknown_0x418[0x430-0x418];
};//Total Size 0x430

extern ItemHolder *itemholder;