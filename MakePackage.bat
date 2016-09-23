@echo off

rem The first parameter is the output package file, the second parameter is the compiler/tools directory
rem Usage example for Code::Blocks: MakePackage.bat $exe_output "${CODEBLOCKS}\NVMTools\bin"


if NOT '%2' == '' set path=%2

nvmcc -g -c main.c -o main.o
nvmcc -g -c useri.c -o useri.o


npackage -pk %1 -add 5FFF.21:useri.o -add 5FFF.06:graph.bin -add 5FFF.fe:desc_GMF.bin -add 5FFF.01:font.bin -add 1F50.02:main.o

