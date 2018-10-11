#ifndef CTEST_CPP_
#define CTEST_CPP_ 
#include <limits.h>
#include <gtest/gtest.h>
#include "../Euclidean.cpp"
#include <cmath>

TEST(initializationTest, one) {
	double l[]={1.,1.};
	Euclidean<2> a(l);

	ASSERT_TRUE(std::abs(sqrt(2)-a.length())<0.001);
}

TEST(assignmentTest, two) 
{
	double l[]={23,47};
	Euclidean<2> one(l);
	Euclidean<2> two=one;
	EXPECT_EQ(two[0],23);
	EXPECT_EQ(two[1],47);
} 

TEST(lenghtShouldEqualOneTest, one) {
	double l[]={1,1};
	Euclidean<2> a(l);
	a.normalize();
	//std::cout<<a.length();

	ASSERT_TRUE(std::abs(1.-a.length())<0.001);
}

TEST(calculateLenghtTest, one) {
	double l[]={3,4};
	Euclidean<2> a(l); 

	EXPECT_EQ(5,a.length());
}

TEST(additionTest, one) {
	double l[]={1,2};
	Euclidean<2> a(l); 
	Euclidean<2> b(l);
	Euclidean<2> c(l);

	c=a+b;
	ASSERT_TRUE(c==a+b);
}

TEST(substractionTest, one) {
	double l[]={1,2};
	Euclidean<2> a(l); 
	Euclidean<2> b(l);
	Euclidean<2> c;

	c=a-b;

	ASSERT_TRUE(c==a-b);
}

TEST(multiplicationTest, one) 
{
	double l[]={22,2};
	Euclidean<(std::size_t)2> a(l); 
	Euclidean<(std::size_t)2> b(l); 
	a=a*3;
	ASSERT_TRUE(a==b*3);
}

TEST(modificationTest, one) 
{
	double l[]={23,47};
	Euclidean<2> one(l);
	one[0]=4;
	Euclidean<2> two=Euclidean<2>(one);
	EXPECT_EQ(two[0],4);
	EXPECT_EQ(two[1],47);
}



int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



#endif

