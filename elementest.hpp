#include <vector>
#include <iostream>
#include <stdlib.h>

bool lastTestFailed = false;
int failureLine = 0;
const char *failureFile;
int testsFailed = 0;

class TestBase {
public:
	int a;
	const char *_testName;
	void run_test() {
		lastTestFailed = false;
		run();
		if (lastTestFailed)
		{
			testsFailed++;
			std::cout << "\033[1;31m" << _testName << " failed" << "\033[0m" << std::endl;
		}
		else
		{
			std::cout << "\033[1;32m" << _testName << " ✓" << "\033[0m" << std::endl;
		}
	}
	virtual void run() = 0;
};

std::vector<TestBase *> tests;

#define TEST(testName) \
	class testName : public TestBase { \
	public: \
		testName() { \
			_testName = #testName; \
			tests.push_back(this);\
		} \
		void run(void); \
	}; \
	testName global_##testName;\
	void testName::run()

void run_tests()
{
	for (size_t i = 0; i < tests.size(); i++)
	{
		tests[i]->run_test();
	}
	std::cout << std::endl << "------" << std::endl;
	std::cout << "Total tests: " << tests.size() << ", failed: " << testsFailed << std::endl;
}

#define ASSERT_EQ(expected, actual) {\
	failureLine = __LINE__;\
	failureFile = __FILE__;\
	if (expected != actual) { \
		std::cout << "Expected " << expected << ", but got " << #actual << ", which is " << actual << std::endl;\
		std::cout << "In file: " << failureFile << ", line " << failureLine << std::endl;\
		lastTestFailed = true;\
		return;\
	}\
}

#define EXPECT_EQ(expected, actual) {\
	failureLine = __LINE__;\
	failureFile = __FILE__;\
	if (expected != b) { \
		std::cout << "Expected " << expected << ", but got " << #actual << ", which is " << actual << std::endl;\
		std::cout << "In file: " << failureFile << ", line " << failureLine << std::endl;\
		lastTestFailed = true;\
	}\
}