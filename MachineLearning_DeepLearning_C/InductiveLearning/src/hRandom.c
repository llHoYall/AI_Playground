/*******************************************************************************
 * @brief   Random module.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @note
 *  - 2018.09.07  Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hRandom.h"

/* APIs ----------------------------------------------------------------------*/
void hRandom_Init(void) {
  srand(time(NULL));
}

int hRandom_Generate(const int min, const int max) {
  return (rand() % (max + 1 - min)) + min;
}
