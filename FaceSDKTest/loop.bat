@echo off
set current_dir=.\build\FaceSDKTest
pushd %current_dir%
path = %path%.\..;.\..\..\Export\face\build_32\bin;.\..\..\Export\opencv\build\x86\vc11\bin;.\..\..\Export\Pre-built.2\dll\x86;

set i=1
:calculate
set /a i=%i%+1
if %i% == 101 (
	goto result
) else (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftError.inputImagesWithATooSmallSize
)
goto calculate
:result
pause
