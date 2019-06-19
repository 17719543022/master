@echo off
set current_dir=.\build\FaceSDKTest
pushd %current_dir%
path = %path%.\..;.\..\..\Export\face\build_32\bin;.\..\..\Export\opencv\build\x86\vc11\bin;.\..\..\Export\Pre-built.2\dll\x86;
echo prepare pics first, and then update configuration to config.ini!

:testsuits
echo 1.ISDetTrack
echo 2.ISFeature
echo 3.ISCompare
echo 4.Error Code Coverage
echo 5.Other Cases
echo 6.All Above
echo q.Quit
for /f "delims=" %%i in ('echo please enter your choice: ') do set /p=%%i<nul
set /p test_suits=
if %test_suits% equ 1 ( 
	goto detectsuits 
) else if %test_suits% equ 2 (
	goto featuresuits
) else if %test_suits% equ 3 (
	goto comparesuits
) else if %test_suits% equ 4 (
	goto :errorsuits
) else if %test_suits% equ 5 (
	goto :othersuits
) else if %test_suits% equ 6 (
	.\Debug\FaceSDKTest.exe --gtest_filter=*.*
) else if %test_suits% equ q (
	exit
) else (
	goto :testsuits
)
goto testsuits

:detectsuits
echo 1.ISFaceDetectPath
echo 2.ISFaceDetTrackRgb
echo 3.ISCalFaceInfoPath
echo 4.All Above
echo 5.Back Home
echo q.Quit
for /f "delims=" %%i in ('echo please enter your choice: ') do set /p=%%i<nul
set /p detect_suits=
if %detect_suits% equ 1 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISDetTrack.ISFaceDetectPath*
) else if %detect_suits% equ 2 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISDetTrack.ISFaceDetTrackRgb*
) else if %detect_suits% equ 3 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISDetTrack.ISCalFaceInfoPath*
) else if %detect_suits% equ 4 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISDetTrack.*
) else if %detect_suits% equ 5 (
	goto testsuits
) else if %detect_suits% equ q (
	exit
) else (
	goto detectsuits
)
goto detectsuits

:featuresuits
echo 1.ISGetFeaturePath
echo 2.Back Home
echo q.Quit
for /f "delims=" %%i in ('echo please enter your choice: ') do set /p=%%i<nul
set /p feature_suits=
if %feature_suits% equ 1 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftISFeature.ISGetFeaturePath*
) else if %feature_suits% equ 2 (
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
echo 7.camera
echo 8.All Above
echo 9.Back Home
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
	.\Debug\FaceSDKTest.exe --gtest_filter=ftAppliance.camera
) else if %other_suits% equ 8 (
	.\Debug\FaceSDKTest.exe --gtest_filter=ftAppliance.*
) else if %other_suits% equ 9 (
	goto testsuits
) else if %other_suits% equ q (
	exit
) else (
	goto othersuits
)
goto othersuits

popd

pause