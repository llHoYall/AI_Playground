/*******************************************************************************
 * @brief   Main file.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @note
 *  - 2018.09.11  Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include "config.h"
#include "hRandom.h"
#include "QLearning.h"

/* Definitions ---------------------------------------------------------------*/
#define _DEPTH  3

/* Main Routine --------------------------------------------------------------*/
int main(void) {
  int q[_NUM_OF_NODE];
  hRandom_Init();
  for (int i = 0; i < _NUM_OF_NODE; ++i) {
    q[i] = hRandom_GenerateInt(0, 100);
  }

  for (int i = 0; i < _NUM_OF_NODE; ++i) {
    printf("%d ", q[i]);
  }
  printf("\n");

  int s;
  for (int i = 0; i < _NUM_OF_TRAINING; ++i) {
    s = 0;
    for (int j = 0; j < _DEPTH; ++j) {
      s = SelectA(_EPSILON, s, q);
      q[s] = UpdateQ(_ALPHA, _GAMMA, s, q);
    }
  }

  for (int i = 0; i < _NUM_OF_NODE; ++i) {
    printf("%d ", q[i]);
  }
  printf("\n");

  return 0;
}
