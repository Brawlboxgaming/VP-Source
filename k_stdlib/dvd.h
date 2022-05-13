#pragma once

#include <kamek.h>

struct DVDFileInfo
{
    u8 unknown_0x0[0x3c - 0x0];
};

extern "C" {

bool DVDOpen(const char * path, DVDFileInfo * fileInfo);
s32 DVDReadPrio(DVDFileInfo * fileInfo, void * buffer, u32 len, u32 offset, u32 prio);
bool DVDClose(DVDFileInfo * fileInfo);

}
