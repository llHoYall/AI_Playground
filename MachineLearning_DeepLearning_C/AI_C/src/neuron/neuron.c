/*******************************************************************************
 * @brief   Neuron.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @history
 *    2018.10.20  Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "neuron_config.h"

/* Private Function Prototypes -----------------------------------------------*/
static void InitWeight(double* const w);
static int GetData(const char* const filename, double* const data);
static double Forward(double* const w, double* const data);
static double F(const double u);

/* APIs ----------------------------------------------------------------------*/
void Neuron(void) {
  double w[_NUM_OF_INPUT + 1];
  double data[_MAX_NUM_OF_INPUT][_NUM_OF_INPUT];

  InitWeight(w);
  int number_of_data = GetData("./resources/neuron_data.txt", &data[0][0]);
  for (int i = 0; i < number_of_data; ++i) {
    printf("%d", i);
    printf(", %lf, %lf", data[i][0], data[i][1]);
    double output = Forward(w, &data[i][0]);
    printf(", %lf\n", output);
  }
}

/* Private Functions ---------------------------------------------------------*/
static void InitWeight(double* const w) {
  *(w + 0) = 1;
  *(w + 1) = 1;
  *(w + 2) = 1.5;
}

static int GetData(const char* const filename, double* const data) {
  int number_of_data = 0;
  int i = 0;
  FILE* fp = fopen(filename, "r");
  if (fp) {
    while (1) {
      int ret = fscanf(fp, "%lf", data + (number_of_data * _NUM_OF_INPUT) + i);
      if (ret < 0) {
        break;
      }
      ++i;
      if (i >= _NUM_OF_INPUT) {
        i = 0;
        ++number_of_data;
      }
    }
    fclose(fp);
  } else {
    printf("File Open Error\n");
  }
  return number_of_data;
}

static double Forward(double* const w, double* const data) {
  int i = 0;
  double u = 0;
  for (i = 0; i < _NUM_OF_INPUT; ++i) {
    u += *(data + i) * *(w + i);
  }
  u -= *(w + i);
  return F(u);
}

static double F(const double u) {
  // Unit step function
  if (u >= 0) {
    return 1.0;
  } else {
    return 0.0;
  }

  // Sigmoid function
  // return 1.0 / (1.0 + exp(-u));
}
