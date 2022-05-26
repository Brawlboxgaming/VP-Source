#pragma once
#include <kamek.h>
#include <egg.h>

struct FileStats{
    u32 fileSize;
    u32 filePos;
};

class SystemManager{
public: 
    char rippedPath[64]; //which file to rip from disc, such as ghost, savebanner.tpl etc...
    u8 unknown_0x40[0x58-0x40];
    u32 isWideScreen;
    u32 gameLanguage;
    u32 strapScreenLanguage;
    u32 isProgressiveScan;
    u32 isRGB60;
    u32 unknown_0x6c[2];
    float framerate;
    float frameratePAL50;
    float frameDuration;
    bool isNdev;
    u8 unknown_0x81[0x84-0x81];
    u32 regionId;
    u8 unknown_0x88[0X98-0X88];
    const char *ndevArg;
    u32 dolStart;
    u32 dolEnd;
    u32 dolSize;
    u8 unknown_0xa8[0x10Fc-0xa8];
    u16 latitude;
    u16 longitude;
}; //total size 0x1100

extern SystemManager *systemManager;

class ArchiveFile{
    u32 unknown_0x0;
    u32 arcHandle;
    void *filePtr;
    u32 size;
    void *heap;
    void *filePtrTmp;
    u32 sizeTmp;
    void *heapPtrTmp;
    u32 status;
};//total size 0x24


class ArchiveLoader{
    ArchiveLoader(); //0x8052a538 vtable 
    virtual void func_vtable(); //0x808b31c8
    u16 sourceCount;
    u8 unknown_0xA[0x10-0xA];
    char **archiveSuffix;
    UnkType *unknown_0x14;
    u32 *srcType;
};//total size 0x1c

class ArchiveLoadHandle{
    ArchiveLoader *archive;
    u8 unknown_0x4[0xc-0x4];
    char archivePath[40];
    u8 unknown_0x34[0x4c-0x34];
    void *heap;
    void *targetHeap;
}; //total size 0x54


class ArchiveRoot{
public:
    ArchiveRoot(); //0x8053fcec vtable 0x808b3bfc
    virtual void func_vtable();
    ArchiveLoader *archives[0x9];
    ArchiveLoader kartArchiveHandles[12];
    ArchiveLoader kartArchiveHandles2[12];
    ArchiveFile contentArchives[4];
    ArchiveLoadHandle loadHandles[7];
    void* tastThread;
    EGG::Disposer disposer;
    u8 unknown_0x598[0x61c-0x598];
}; //total size 0x61C

class IOStream{
public:
    virtual void func_vtable();
    bool mAvailable;
    u8 unknown_0x5[3];
    u32 mAsyncResult;
    void *mCallBack;
    void *mArg;
}; //total size 0x14

class DVDCommandBlock{
public:
    void *next;
    void *prev;
    u32 command;
    u32 state;
    u32 offset;
    u32 length;
    void *addr;
    u32 curTransferSize;
    u32 transferredSize;
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBuffSize;
    u8 unknown_0x2e[2];
    u32 *address;
    u32 length2;
    u32 unknown_0x38;
};

class DVDFileStream : IOStream{
public:
    FileStats mStats;
    void *unknown_0x1C;
    void *mCancelArg;
    bool mIsCanceling;
    u8 unknown_0x25[3];
    DVDCommandBlock dvdInfo;
    UnkType *stream; //pointer to self?
    u32 mPriority;
    bool mIsBusy;
    bool mCloseOnDestroyFlg;
    bool mCloseEnableFlg;
    u8 unknown_0x6f;
    u32 mOffset;
    u32 mSize;
}; //total size 0x78