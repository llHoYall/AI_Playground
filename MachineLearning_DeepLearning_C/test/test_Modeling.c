#include "unity.h"
#include "Modeling.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_Modeling_DoModeling_MatchedOne(void) {
	int data[1][10] = {
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1
	};
	int label[1] = {
		1
	};
	int predict[10] = {
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1
	};
	int matched_data = DoModeling(1, 10, &data[0][0], label, predict);
	TEST_ASSERT_EQUAL_INT(matched_data, 1);
}

void test_Modeling_DoModeling_MatchedZero(void) {
	int data[1][10] = {
		0, 1, 0, 0, 0, 1, 1, 0, 1, 0
	};
	int label[1] = {
		0
	};
	int predict[10] = {
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1
	};
	int matched_data = DoModeling(1, 10, &data[0][0], label, predict);
	TEST_ASSERT_EQUAL_INT(matched_data, 1);
}

void test_Modeling_DoModeling_Unmatched(void) {
	int data[1][10] = {
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1
	};
	int label[1] = {
		1
	};
	int predict[10] = {
		0, 1, 0, 0, 0, 1, 1, 0, 1, 0
	};
	int matched_data = DoModeling(1, 10, &data[0][0], label, predict);
	TEST_ASSERT_EQUAL_INT(matched_data, 0);
}

void test_Modeling_DoPredict_PredictOne(void) {
	int data[10] = {
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1
	};
	int model[10] = {
		1, 0, 2, 0, 0, 2, 1, 0, 0, 2
	};
	int predict = DoPredict(10, data, model);
	TEST_ASSERT_EQUAL_INT(predict, 10);
}

void test_Modeling_DoPredict_PredictZero(void) {
	int data[10] = {
		1, 0, 0, 0, 0, 0, 1, 0, 0, 1
	};
	int model[10] = {
		1, 0, 2, 0, 1, 2, 1, 0, 0, 2
	};
	int predict = DoPredict(10, data, model);
	TEST_ASSERT_EQUAL_INT(predict, 9);
}
