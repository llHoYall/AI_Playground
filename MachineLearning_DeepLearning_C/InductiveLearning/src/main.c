/*******************************************************************************
 * @brief   Main file.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @note
 *  - 2018.09.04  Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "config.h"
#include "hRandom.h"
#include "ReadData.h"
#include "Modeling.h"

/* Main Routine --------------------------------------------------------------*/
int main(void) {
  int data[_NUM_OF_DATASET][_NUM_OF_CATEGORY];
  int label[_NUM_OF_DATASET];
  memset(data, INT_MAX, sizeof(data));
  memset(label, INT_MAX, sizeof(label));
  ReadTrainingData("./resources/training_data.txt", _NUM_OF_DATASET, _NUM_OF_CATEGORY, &data[0][0], label);

  int predict[_NUM_OF_CATEGORY];
  int best_predict[_NUM_OF_CATEGORY];
  int match = 0;
  int best_match = 0;
  hRandom_Init();
  for (int i = 0; i < _NUM_OF_TRY; ++i) {
    for (int j = 0; j < _NUM_OF_CATEGORY; ++j) {
      predict[j] = hRandom_Generate(0, 2);
    }
    match = DoModeling(_NUM_OF_DATASET, _NUM_OF_CATEGORY, &data[0][0], label, predict);
    if (best_match < match) {
      memcpy(best_predict, predict, sizeof(predict));
      best_match = match;
    }
  }
  printf("=== Result ===\n");
  for (int k = 0; k < _NUM_OF_CATEGORY; ++k) {
    printf("%1d ", best_predict[k]);
  }
  printf(": matched = %d\n", best_match);

  printf("=== Test ===\n");
  ReadTestData("./resources/test_data.txt", _NUM_OF_DATASET, _NUM_OF_CATEGORY, &data[0][0]);
  for (int i = 0; i < _NUM_OF_TEST_DATASET; ++i) {
    for (int j = 0; j < _NUM_OF_CATEGORY; ++j) {
      printf("%1d ", data[i][j]);
    }
    int result = DoPredict(_NUM_OF_CATEGORY, data[i], best_predict) == 10 ? 1 : 0;
    printf(": Predict = %d\n", result);
  }

  return 0;
}
