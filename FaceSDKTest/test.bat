@echo off
set current_dir=.\Export\build\FaceSDKTest
pushd %current_dir%
path = %path%;.\..\..\face\build_32\bin;.\..\..\opencv\build\x86\vc11\bin;.\..\..\Pre-built.2\dll\x86;
echo prepare pics first, and then update configuration to config.ini!

:testsuits
echo 1.standard single thread flow
echo 2.standard multi thread flow
echo 3.ftISDetTrack
echo 4.ftISFeature
echo 5.ftISCompare
echo 6.ftError
echo 7.ftAppliance
echo 8.All Above
echo q.Quit
for /f "delims=" %%i in ('echo please enter your choice: ') do set /p=%%i<nul
set /p test_suits=
if %test_suits% equ 1 ( 
	goto singleflow
) else if %test_suits% equ 2 (
	goto multiflow
) else if %test_suits% equ 3 (
	goto detectsuits
) else if %test_suits% equ 4 (
	goto featuresuits
) else if %test_suits% equ 5 (
	goto comparesuits
) else if %test_suits% equ 6 (
	goto :errorsuits
) else if %test_suits% equ 7 (
	goto :othersuits
) else if %test_suits% equ 8 (
	.\Debug\FaceSDKTest.exe --gtest_filter=*.*
) else if %test_suits% equ q (
	exit
) else (
	goto :testsuits
)
goto testsuits

:singleflow
echo 1.ISFaceDetectRgb+ISGetFeatureWithFacePosPath+ISCompare
echo 2.ISFaceDetectRgb+ISGetFeatureWithFacePosPath+ISCompareMN
echo 3.ISFaceDetectRgb+ISGetFeatureWithFacePosPath+ISCompareMNfaster
echo 4.Back Home
echo q.Quit
for /f "delims=" %%i in ('echo please enter your choice: ') do set /p=%%i<nul
set /p single_flow=
if %single_flow% equ 1 (
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISDetTrack.ISFaceDetectRgb_SingleThread
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISFeature.ISGetFeatureWithFacePosPath_SingleThread
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISCompare.ISCompare_SingleThread
) else if %single_flow% equ 2 (
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISDetTrack.ISFaceDetectRgb_SingleThread
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISFeature.ISGetFeatureWithFacePosPath_SingleThread
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISCompare.ISCompareMN_SingleThread
) else if %single_flow% equ 3 (
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISDetTrack.ISFaceDetectRgb_SingleThread
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISFeature.ISGetFeatureWithFacePosPath_SingleThread
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISCompare.ISCompareMNfaster_SingleThread
) else if %single_flow% equ 4 (
	goto testsuits
) else if %single_flow% equ q (
	exit
) else (
	goto singleflow
)
goto singleflow

:multiflow
echo 1.ISFaceDetectRgb+ISGetFeatureWithFacePosPath+ISCompare
echo 2.ISFaceDetectRgb+ISGetFeatureWithFacePosPath+ISCompareMN
echo 3.ISFaceDetectRgb+ISGetFeatureWithFacePosPath+ISCompareMNfaster
echo 4.Back Home
echo q.Quit
for /f "delims=" %%i in ('echo please enter your choice: ') do set /p=%%i<nul
set /p multi_suits=
if %multi_suits% equ 1 (
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISDetTrack.ISFaceDetectRgb_MultiThread
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISFeature.ISGetFeatureWithFacePosPath_MultiThread
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISCompare.ISCompare_MultiThread
) else if %multi_suits% equ 2 (
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISDetTrack.ISFaceDetectRgb_MultiThread
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISFeature.ISGetFeatureWithFacePosPath_MultiThread
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISCompare.ISCompareMN_MultiThread
) else if %multi_suits% equ 3 (
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISDetTrack.ISFaceDetectRgb_MultiThread
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISFeature.ISGetFeatureWithFacePosPath_MultiThread
	.\Debug\FaceSDKTest.exe smartirsec2018 --gtest_filter=ftISCompare.ISCompareMNfaster_MultiThread
) else if %multi_suits% equ 4 (
	goto testsuits
) else if %multi_suits% equ q (
	exit
) else (
	goto multiflow
)
goto multiflow

:detectsuits
echo 1.ISFaceDetectPath
echo 2.ISFaceDetectRgb
echo 3.ISFaceDetTrackRgb
echo 4.ISCalFaceInfoPath
echo 5.All Above
echo 6.Back Home
echo q.Quit
for /f "delims=" %%i in ('echo please enter your choice: ') do set /p=%%i<nul
set /p detect_suits=
if %detect_suits% equ 1 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISDetTrack.ISFaceDetectPath*
) else if %detect_suits% equ 2 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISDetTrack.ISFaceDetectRgb*
) else if %detect_suits% equ 3 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISDetTrack.ISFaceDetTrackRgb*
) else if %detect_suits% equ 4 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISDetTrack.ISCalFaceInfoPath*
) else if %detect_suits% equ 5 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISDetTrack.*
) else if %detect_suits% equ 6 (
	goto testsuits
) else if %detect_suits% equ q (
	exit
) else (
	goto detectsuits
)
goto detectsuits

:featuresuits
echo 1.ISGetFeaturePath
echo 2.ISGetFeatureWithFacePosPath(Run ISFaceDetectPath Earlier)
echo 3.Back Home
echo q.Quit
for /f "delims=" %%i in ('echo please enter your choice: ') do set /p=%%i<nul
set /p feature_suits=
if %feature_suits% equ 1 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISFeature.ISGetFeaturePath*
) else if %feature_suits% equ 2 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISFeature.ISGetFeatureWithFacePosPath*
) else if %feature_suits% equ 3 (
	goto testsuits
) else if %feature_suits% equ q (
	exit
) else (
	goto featuresuits
)
goto featuresuits

:comparesuits
echo 1.Run This Case First, Which Generate Feature And Pca Files For Other Cases
echo 2.ISCompare
echo 3.ISCompareMN
echo 4.ISCompareMNfaster
echo 5.All Above
echo 6.Back Home
echo q.Quit
for /f "delims=" %%i in ('echo please enter your choice: ') do set /p=%%i<nul
set /p compare_suits=
if %compare_suits% equ 1 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISCompare.prepareFeatureAndPcaRapidlyUsingMultiThread
) else if %compare_suits% equ 2 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISCompare.ISCompare_*
) else if %compare_suits% equ 3 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISCompare.ISCompareMN_*
) else if %compare_suits% equ 4 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISCompare.ISCompareMNfaster_*
) else if %compare_suits% equ 5 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISCompare.*
) else if %compare_suits% equ 6 (
	goto testsuits
) else if %compare_suits% equ q (
	exit
) else (
	goto comparesuits
)
goto comparesuits

:errorsuits
echo 1.inputImagesWithATooSmallSize
echo 2.inputImagesCanNotBeFound
echo 3.detectWithOutCreatingDectectChannel
echo 4.inputImagesDetectedNoFace
echo 5.inputImagesGetNoFeature
echo 6.whatImageLeadsToGetFeatureError
echo 7.whatIsCompareMNError
echo 8.All Above
echo 9.Back Home
echo q.Quit
for /f "delims=" %%i in ('echo please enter your choice: ') do set /p=%%i<nul
set /p error_suits=
if %error_suits% equ 1 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftError.inputImagesWithATooSmallSize
)else if %error_suits% equ 2 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftError.inputImagesCanNotBeFound
) else if %error_suits% equ 3 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftError.detectWithOutCreatingDectectChannel
) else if %error_suits% equ 4 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftError.inputImagesDetectedNoFace
) else if %error_suits% equ 5 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftError.inputImagesGetNoFeature
) else if %error_suits% equ 6 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftError.whatImageLeadsToGetFeatureError
) else if %error_suits% equ 7 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftError.whatIsCompareMNError
) else if %error_suits% equ 8 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftError.*
) else if %error_suits% equ 9 (
	goto testsuits
) else if %error_suits% equ q (
	exit
) else (
	goto errorsuits
)
goto errorsuits

:othersuits
echo 1.dumpVersionNo
echo 2.ISGetFeatureLength_Check
echo 3.dumpConfigIni
echo 4.theGivenPictureHasMoreThan15FacesBeDetected
echo 5.whatFaceReturnsEarlierInOutResultAndWhatLater
echo 6.personAndIdCardCompareOfOneDirectory
echo 7.personAndIdCardCompareOfOneDirectorySteply
echo 8.camera
echo 9.All Above
echo 10.Back Home
echo q.Quit
for /f "delims=" %%i in ('echo please enter your choice: ') do set /p=%%i<nul
set /p other_suits=
if %other_suits% equ 1 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftAppliance.dumpVersionNo
)else if %other_suits% equ 2 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftAppliance.ISGetFeatureLength_Check
) else if %other_suits% equ 3 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftAppliance.dumpConfigIni
) else if %other_suits% equ 4 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftAppliance.theGivenPictureHasMoreThan15FacesBeDetected
) else if %other_suits% equ 5 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftAppliance.whatFaceReturnsEarlierInOutResultAndWhatLater
) else if %other_suits% equ 6 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftAppliance.personAndIdCardCompareOfOneDirectory
) else if %other_suits% equ 7 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftAppliance.personAndIdCardCompareOfOneDirectorySteply
) else if %other_suits% equ 8 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftAppliance.camera
) else if %other_suits% equ 9 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftAppliance.*
) else if %other_suits% equ 10 (
	goto testsuits
) else if %other_suits% equ q (
	exit
) else (
	goto othersuits
)
goto othersuits

popd

pause