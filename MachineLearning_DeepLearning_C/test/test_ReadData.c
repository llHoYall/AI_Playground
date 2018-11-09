#include <string.h>
#include "unity.h"
#include "config.h"
#include "ReadData.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_ReadData_ReadTrainingData(void) {
	int data[1][10];
  int label[1];
  memset(data, INT_MAX, sizeof(data));
  memset(label, INT_MAX, sizeof(label));
  ReadTrainingData("./test/unittest_data.txt", 1, 10, &data[0][0], label);
	TEST_ASSERT_EQUAL_INT(1, data[0][0]);
	TEST_ASSERT_EQUAL_INT(0, data[0][1]);
	TEST_ASSERT_EQUAL_INT(0, data[0][2]);
	TEST_ASSERT_EQUAL_INT(0, data[0][3]);
	TEST_ASSERT_EQUAL_INT(0, data[0][4]);
	TEST_ASSERT_EQUAL_INT(0, data[0][5]);
	TEST_ASSERT_EQUAL_INT(1, data[0][6]);
	TEST_ASSERT_EQUAL_INT(0, data[0][7]);
	TEST_ASSERT_EQUAL_INT(0, data[0][8]);
	TEST_ASSERT_EQUAL_INT(1, data[0][9]);
	TEST_ASSERT_EQUAL_INT(1, label[0]);
}

void test_ReadData_ReadTestData(void) {
	int data[1][10];
  memset(data, INT_MAX, sizeof(data));
  ReadTestData("./test/unittest_data.txt", 1, 10, &data[0][0]);
	TEST_ASSERT_EQUAL_INT(1, data[0][0]);
	TEST_ASSERT_EQUAL_INT(0, data[0][1]);
	TEST_ASSERT_EQUAL_INT(0, data[0][2]);
	TEST_ASSERT_EQUAL_INT(0, data[0][3]);
	TEST_ASSERT_EQUAL_INT(0, data[0][4]);
	TEST_ASSERT_EQUAL_INT(0, data[0][5]);
	TEST_ASSERT_EQUAL_INT(1, data[0][6]);
	TEST_ASSERT_EQUAL_INT(0, data[0][7]);
	TEST_ASSERT_EQUAL_INT(0, data[0][8]);
	TEST_ASSERT_EQUAL_INT(1, data[0][9]);
}
