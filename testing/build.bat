@echo off
SETLOCAL EnableDelayedExpansion

:: Make build folder
mkdir build

::Hardcoded because yes
mkdir build\tileset

:: CPP compilation settings
SET CC="../cw/mwcceppc.exe"
SET CFLAGS=-I- -i ../k_stdlib -i ../testing -Cpp_exceptions off -enum int -O4,s -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -maxerrors 1
SET CPPFILES=
for %%f in (*.cpp) do SET "CPPFILES=%%~nf !CPPFILES!"


:: Destination (change as necessary)
SET "DEST=../testing"
SET "RIIVO=D:\Documents\Dolphin Emulator\Load\Kamek"
echo %RIIVO%

:: Compile CPP
SET OBJECTS=
FOR %%H IN (%CPPFILES%) DO (
    echo "Compiling %%H.cpp..."
    %CC% %CFLAGS% -c -o build/%%H.o %%H.cpp
    SET "OBJECTS=build/%%H.o !OBJECTS!"
)
:: Link
echo Linking...
"../Kamek/bin/Debug/Kamek" %OBJECTS% -dynamic -externals=../symbols.txt -versions=../versions.txt -output-kamek=build\$KV$.bin
if %ErrorLevel% equ 0 (
	xcopy /Y build\*.bin "%RIIVO%" >NUL
    move /Y build\*.bin %DEST% >NUL	
)


rmdir /Q /S build 
:end
ENDLOCAL