#include <kamek.h>
#include <dvd.h>
#include <base/rvl_sdk.h>

struct LECTHeader
{
    u32 magic;
    u32 version;
    u32 buildNum;
    void * loadAddress;
    void (*mainFunc)();
    u32 size;
    u32 paramSectionOffset;
    char region;
    char debugFlag;
    u8 leVersion;
    u8 _1f;
};

static void notFoundError()
{
    u32 fg = 0xffffffff;
    u32 bg = 0x000000ff;
    OSFatal(&fg, &bg, "Error: LE-Code bin not found");
}

static int loadLECode()
{
    DVDFileInfo file;
    LECTHeader header __attribute__((aligned(0x20)));
    
    // Get path
    const char * path;
    switch (*(char *)0x80000003)
    {
        case 'E':
            path = "/rel/lecode-USA.bin";
            break;
        case 'J':
            path = "/rel/lecode-JAP.bin";
            break;
        case 'P':
            path = "/rel/lecode-PAL.bin";
            break;
        case 'K':
            path = "/rel/lecode-KOR.bin";
            break;
    }

    OSReport("Loading %s\n", path);

    // Open file
    if (!DVDOpen(path, &file))
        notFoundError();

    // Read header
    DVDReadPrio(&file, (void *)&header, sizeof(header), 0, 2);

    // Read full file
    DVDReadPrio(&file, header.loadAddress, header.size, 0, 2);

    // Call entry function
    LECTHeader * newHeader = (LECTHeader *) header.loadAddress;
    newHeader->mainFunc();

    return 0;
}

kmOnLoad(loadLECode);
