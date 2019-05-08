#include "stdafx.h"
#include <stdlib.h>
#include <pthread.h>
#include <gtest/gtest.h>
#include "config.h"

TEST(ftMultiThread, dumpConfigFileOfIniFormat)
{
	GConfig::getInstance().dump();
}

TEST(ftMultiThread, detect1000FacesWithSingleThreadAndDetermineCost)
{
	string imgPath = GConfig::getInstance().getImgPath();

}