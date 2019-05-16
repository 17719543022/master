set current_dir=.\Project\FaceSDKTest
pushd %current_dir%
path = %path%.\..;.\..\..\Export\face\build_32\bin;.\..\..\Export\opencv\build\x86\vc11\bin;.\..\..\Export\Pre-built.2\dll\x86;
.\Debug\FaceSDKTest.exe
popd

pause