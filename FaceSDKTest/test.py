#!/usr/bin/python
# -*- coding: UTF-8 -*-

import os
from goto import with_goto

os.chdir(os.getcwd()+"/build/Target")

@with_goto
def test():
	label .home
	print("1.ftISDetTrack*")
	print("2.ftISFeature*")
	print("3.ftISCompare*")
	print("4.ftError*")
	print("5.ftAppliance*")
	print("6.All Above")
	print("q.Quit")
	h = input("please enter your choice: ")

	label .detect
	if h == "1":
		print("1.ISFaceDetectPath")
		print("2.ISCalFaceInfoPath")
		print("3.All Above")
		print("4.Back Home")
		d = input("please enter your choice: ")
		if d == "1":
			os.system("./FaceSDKTest --gtest_filter=ftISDetTrack.ISFaceDetectPath*")
			goto .detect
		if d == "2":
			os.system("./FaceSDKTest --gtest_filter=ftISDetTrack.ISCalFaceInfoPath*")
			goto .detect
		if d == "3":
			os.system("./FaceSDKTest --gtest_filter=ftISDetTrack.*")
			goto .detect
		if d == "4":
			goto .home

	label .feature
	if h == "2":
		print("1.ISGetFeaturePath")
		print("2.Back Home")
		f = input("please enter your choice: ")
		if f == "1":
			os.system("./FaceSDKTest --gtest_filter=ftISFeature.ISGetFeaturePath*")
			goto .feature
		if f == "2":
			goto .home

	label .compare
	if h == "3":
		print("1.Run This Case First, Which Generate Feature And Pca Files For Other Cases")
		print("2.ISCompare")
		print("3.ISCompareMN")
		print("4.ISCompareMNfaster")
		print("5.All Above")
		print("6.Back Home")
		c = input("please enter your choice: ")
		if c == "1":
			os.system("./FaceSDKTest --gtest_filter=ftISCompare.prepareFeatureAndPcaRapidlyUsingMultiThread")
			goto .compare
		if c == "2":
			os.system("./FaceSDKTest --gtest_filter=ftISCompare.ISCompare*")
			goto .compare
		if c == "3":
			os.system("./FaceSDKTest --gtest_filter=ftISCompare.ISCompareMN*")
			goto .compare
		if c == "4":
			os.system("./FaceSDKTest --gtest_filter=ftISCompare.ISCompareMNfaster*")
			goto .compare
		if c == "5":
			os.system("./FaceSDKTest --gtest_filter=ftISCompare.*")
			goto .compare
		if c == "6":
			goto .home

	label .error
	if h == "4":
		print("1.inputImagesWithATooSmallSize")
		print("2.inputImagesCanNotBeFound")
		print("3.detectWithOutCreatingDectectChannel")
		print("4.inputImagesDetectedNoFace")
		print("5.inputImagesGetNoFeature")
		print("6.whatImageLeadsToGetFeatureError")
		print("7.whatIsCompareMNError")
		print("8.All Above")
		print("9.Back Home")
		e = input("please enter your choice: ")
		if e == "1":
			os.system("./FaceSDKTest --gtest_filter=ftError.inputImagesWithATooSmallSize")
			goto .error
		if e == "2":
			os.system("./FaceSDKTest --gtest_filter=ftError.inputImagesCanNotBeFound")
			goto .error
		if e == "3":
			os.system("./FaceSDKTest --gtest_filter=ftError.detectWithOutCreatingDectectChannel")
			goto .error
		if e == "4":
			os.system("./FaceSDKTest --gtest_filter=ftError.inputImagesDetectedNoFace")
			goto .error
		if e == "5":
			os.system("./FaceSDKTest --gtest_filter=ftError.inputImagesGetNoFeature")
			goto .error
		if e == "6":
			os.system("./FaceSDKTest --gtest_filter=ftError.whatImageLeadsToGetFeatureError")
			goto .error
		if e == "7":
			os.system("./FaceSDKTest --gtest_filter=ftError.whatIsCompareMNError")
			goto .error
		if e == "8":
			os.system("./FaceSDKTest --gtest_filter=ftError.*")
			goto .error
		if e == "9":
			goto .home

	label .appliance
	if h == "5":
		print("1.dumpVersionNo")
		print("2.ISGetFeatureLengthCheck")
		print("3.dumpConfigIni")
		print("4.theGivenPictureHas16FacesBeDetected")
		print("5.whatFaceReturnsEarlierInOutResultAndWhatLater")
		print("6.personAndIdCardCompareOfOneDirectory")
		print("7.camera")
		print("8.Back Home")
		a = input("please enter your choice: ")
		if a == "1":
			os.system("./FaceSDKTest --gtest_filter=ftAppliance.dumpVersionNo")
			goto .appliance
		if a == "2":
			os.system("./FaceSDKTest --gtest_filter=ftAppliance.ISGetFeatureLengthCheck")
			goto .appliance
		if a == "3":
			os.system("./FaceSDKTest --gtest_filter=ftAppliance.dumpConfigIni")
			goto .appliance
		if a == "4":
			os.system("./FaceSDKTest --gtest_filter=ftAppliance.theGivenPictureHas16FacesBeDetected")
			goto .appliance
		if a == "5":
			os.system("./FaceSDKTest --gtest_filter=ftAppliance.whatFaceReturnsEarlierInOutResultAndWhatLater")
			goto .appliance
		if a == "6":
			os.system("./FaceSDKTest --gtest_filter=ftAppliance.personAndIdCardCompareOfOneDirectory")
			goto .appliance
		if a == "7":
			os.system("./FaceSDKTest --gtest_filter=ftAppliance.camera")
			goto .appliance
		if a == "8":
			goto .home

	if h == "6":
		os.system("./FaceSDKTest --gtest_filter=*.*")
		goto .home

test()
