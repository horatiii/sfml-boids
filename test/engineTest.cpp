#ifndef CTEST_CPP_
#define CTEST_CPP_ 
//#include <limits.h>
#include <gtest/gtest.h>
//#include "../boid.hpp"
#include <cmath>


TEST(substractionTest, one) {

	ASSERT_TRUE(1==5);
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



#endif

