#include "unity.h"
#include "hRandom.h"

void setUp(void) {
	hRandom_Init();
}

void tearDown(void) {
}

void test_hRandom_GenerateRandomNumber_Int(void) {
	for (int i = 0; i < 10; ++i) {
		TEST_ASSERT_INT_WITHIN(50, 50, hRandom_GenerateInt(0, 100));
	}
}

void test_hRandom_GenerateRandomNumber_Double(void) {
	for (int i = 0; i < 10; ++i) {
		TEST_ASSERT_FLOAT_WITHIN(0.5, 0.5, hRandom_GenerateDouble(0, 1));
	}
}