/*******************************************************************************
 * @brief   Calculator for inductive learning.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @note
 *  - 2018.09.08  Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include "Modeling.h"

/* APIs ----------------------------------------------------------------------*/
int DoModeling(const int data_size, const int category_size, int* const data, int* const label, int* const predict) {
  int matched_data = 0;
  int matched_category;

  for (int i = 0; i < data_size; ++i) {
    matched_category = 0;
    for (int j = 0; j < category_size; ++j) {
      if (*(data + (i * category_size) + j) == *(predict + j)) {
        ++matched_category;
      } else if (2 == *(predict + j)) {
        ++matched_category;
      }
    }
    if ((matched_category == category_size) && (*(label + i) == 1)) {
      ++matched_data;
    } else if ((matched_category != category_size) && (*(label + i) == 0)) {
      ++matched_data;
    }
  }
  return matched_data;
}

int DoPredict(const int category_size, int* const data, int* const model) {
  int predict = 0;
  for (int i = 0; i < category_size; ++i) {
    if (*(model + i) == 2) {
      ++predict;
    } else if (*(data + i) == *(model + i)) {
      ++predict;
    }
  }
  return predict;
}