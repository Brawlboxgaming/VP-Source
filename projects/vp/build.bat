@echo off
SETLOCAL EnableDelayedExpansion

cls

:: Make build folder
mkdir build

::Hardcoded because yes
mkdir build\tileset

:: CPP compilation settings
SET CC="../../cw/mwcceppc.exe"
SET CFLAGS=-I- -i ../../libraries/ -i ../vp/ -i ../CommonCodes -Cpp_exceptions off -enum int -O4,s -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -maxerrors 1
SET CPPFILES=
for %%f in (*.cpp) do SET "CPPFILES=%%~nf !CPPFILES!"
SET COMMONCPPFILES=
for %%f in (../CommonCodes/*.cpp) do SET "COMMONCPPFILES=%%~nf !COMMONCPPFILES!"

:: Compile CPP
SET OBJECTS=
FOR %%H IN (%CPPFILES%) DO (
    echo "Compiling %%H.cpp..."
    %CC% %CFLAGS% -c -o build/%%H.o %%H.cpp
    SET "OBJECTS=build/%%H.o !OBJECTS!"
)

SET COMMONOBJECTS=
FOR %%H IN (%COMMONCPPFILES%) DO (
    echo "Compiling %%H.cpp..."
    %CC% %CFLAGS% -c -o build/%%H.o "../CommonCodes/%%H.cpp"
    SET "COMMONOBJECTS=build/%%H.o !COMMONOBJECTS!"
)

::C:/devkitPro/devkitPPC/bin/powerpc-eabi-readelf -s build/%%H.o

:: Link
echo Linking...
"../../Kamek/bin/Debug/Kamek" %OBJECTS% -dynamic -externals=../../symbols.txt -versions=../../versions.txt -output-kamek=build\$KV$.bin
if %ErrorLevel% equ 0 (
    move /Y build/*.bin "../vp" >NUL
    copy /Y *.bin "./files/Uploaded Packs/varietypack/boot/" >NUL
)

rmdir /Q /S build

:end
ENDLOCAL