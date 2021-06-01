#include "elementest.hpp"

TEST(elementestWorks) {
	ASSERT_EQ(4, 2+2);
}

TEST(failingTest) {
	ASSERT_EQ(5, 2+2);
}

int main(void) {
	run_tests();
}