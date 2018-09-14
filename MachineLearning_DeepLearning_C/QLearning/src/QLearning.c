/*******************************************************************************
 * @brief   Q learning module.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @note
 *  - 2018.09.11  Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include "hRandom.h"
#include "QLearning.h"

/* APIs ----------------------------------------------------------------------*/
int SelectA(const double epsilon, const int old_s, int* const q) {
  int s;
  if (hRandom_GenerateDouble(0.0, 1.0) < epsilon) {
    if (hRandom_GenerateInt(0, 1) == 0) {
      s = 2 * old_s + 1;
    } else {
      s = 2 * old_s + 2;
    }
  } else {
    if (q[2 * old_s + 1] > q[2 * old_s + 2]) {
      s = 2 * old_s + 1;
    } else {
      s = 2 * old_s + 2;
    }
  }
  return s;
}

int UpdateQ(const double alpha, const double gamma, const int s, int* const q) {
  int new_q;
  int max_q;

  if (s > 6) {
    if (14 == s) {
      new_q = q[s] + alpha * (1000 - q[s]);
    } else if (11 == s) {
      new_q = q[s] + alpha * ( 500 - q[s]);
    } else {
      new_q = q[s];
    }
  } else {
    if (q[2 * s + 1] > q[2 * s + 2]) {
      max_q = q[2 * s + 1];
    } else {
      max_q = q[2 * s + 2];
    }
    new_q = q[s] + alpha * (gamma * max_q - q[s]);
  }
  return new_q;
}