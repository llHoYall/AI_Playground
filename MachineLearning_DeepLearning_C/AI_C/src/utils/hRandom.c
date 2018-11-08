/*******************************************************************************
 * @brief   Random module.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @history
 *    2018.09.07  Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "hRandom.h"

/* APIs ----------------------------------------------------------------------*/
void hRandom_Init(void) {
  srand(time(NULL));
}

int hRandom_GenerateInt(const int min, const int max) {
  return (rand() % (max + 1 - min)) + min;
}

double hRandom_GenerateDouble(const double min, const double max) {
  return (((double)rand() / RAND_MAX) * (max - min)) + min;
}
