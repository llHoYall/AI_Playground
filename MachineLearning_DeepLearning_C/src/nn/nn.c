/*******************************************************************************
 * @brief   Neural Network.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @history
 *    2018.10.22  Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nn_config.h"

/* Private Function Prototypes -----------------------------------------------*/
static void InitWeightHidden(double* const wh);
static void InitWeightOutput(double* const wo);
static int GetData(const char* const filename, double* const data);
static double Forward(const double* const wh, const double* const wo, double* const hi, const double* const data);
static double F(const double u);

/* APIs ----------------------------------------------------------------------*/
void NeuralNetwork(void) {
	double wh[_NUM_OF_HIDDEN][_NUM_OF_INPUT + 1];
	double wo[_NUM_OF_HIDDEN + 1];
  double hi[_NUM_OF_HIDDEN + 1];
  double data[_MAX_NUM_OF_INPUT][_NUM_OF_INPUT];

	InitWeightHidden(&wh[0][0]);
  InitWeightOutput(wo);

  int number_of_data = GetData("./resources/nn_data.txt", &data[0][0]);

  for (int i = 0; i < number_of_data; ++i) {
    printf("%d", i);
    for (int j = 0; j < _NUM_OF_INPUT; ++j) {
      printf(", %lf", data[i][j]);
    }
    double output = Forward(&wh[0][0], wo, hi, &data[i][0]);
    printf(", %lf\n", output);
  }
}

/* Private Functions ---------------------------------------------------------*/
static void InitWeightHidden(double* const wh) {
  *(wh + (0 * (_NUM_OF_INPUT + 1)) + 0) = -2;
  *(wh + (0 * (_NUM_OF_INPUT + 1)) + 1) = 3;
  *(wh + (0 * (_NUM_OF_INPUT + 1)) + 2) = -1;
  *(wh + (1 * (_NUM_OF_INPUT + 1)) + 0) = -2;
  *(wh + (1 * (_NUM_OF_INPUT + 1)) + 1) = 1;
  *(wh + (1 * (_NUM_OF_INPUT + 1)) + 2) = 0.5;
}

static void InitWeightOutput(double* const wo) {
  *(wo + 0) = -60;
  *(wo + 1) = 94;
  *(wo + 2) = -1;
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

static double Forward(const double* const wh, const double* const wo, double* const hi, const double* const data) {
  int i;
  for (i = 0; i < _NUM_OF_HIDDEN; ++i) {
    double u = 0;
    int j;
    for (j = 0; j < _NUM_OF_INPUT; ++j) {
      u += (*(data + j)) * (*(wh + (i * (_NUM_OF_INPUT + 1)) + j));
    }
    u -= *(wh + (i * (_NUM_OF_INPUT + 1)) + j);
    *(hi + i) = F(u);
  }

  double output = 0;
  for (i = 0; i < _NUM_OF_HIDDEN; ++i) {
    output += (*(hi + i)) * (*(wo + i));
  }
  output -= *(wo + i);
  return F(output);
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
