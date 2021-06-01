#include <vector>
#include <iostream>

class TestBase {
public:
	int a;
	virtual void run() = 0;
};

std::vector<TestBase *> tests;

#define TEST(testName) \
	class testName : public TestBase { \
	public: \
		testName() { \
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
		tests[i]->run();
	}
}
