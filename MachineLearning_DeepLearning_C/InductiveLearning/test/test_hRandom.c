#include "unity.h"
#include "hRandom.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_hRandom_GenerateRandomNumber(void) {
	hRandom_Init();
	for (int i = 0; i < 10; ++i) {
			TEST_ASSERT_INT_WITHIN(1, 1, hRandom_Generate(0, 2));
	}
}
