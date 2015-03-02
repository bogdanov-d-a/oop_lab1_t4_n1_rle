@echo off

set loopIter=1
:LoopStart


del %loopIter%.tmp >nul 2>&1

RLE.exe pack %loopIter%.bin %loopIter%.tmp
fc %loopIter%.tmp %loopIter%.rle

del %loopIter%.tmp

RLE.exe unpack %loopIter%.rle %loopIter%.tmp
fc %loopIter%.tmp %loopIter%.bin

del %loopIter%.tmp


if %loopIter% lss 6 (
	set /a loopIter=%loopIter%+1
	goto LoopStart
)


RLE.exe unpack 7.rle 7.tmp
del 7.tmp

RLE.exe unpack 8.rle 8.tmp
del 8.tmp


pause
