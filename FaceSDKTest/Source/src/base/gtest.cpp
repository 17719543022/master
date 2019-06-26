#include <gtest/gtest.h>
#include <string.h>

extern bool isFlow;

int main(int argc, char **argv){
	if(strcmp(argv[1], "smartirsec2018")==0){
		isFlow = true;
	}

	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
