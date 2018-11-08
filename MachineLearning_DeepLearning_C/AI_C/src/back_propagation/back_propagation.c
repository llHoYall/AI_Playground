/*******************************************************************************
 * @brief   Back Propagation.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @history
 *		2018.11.07  Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include "hRandom.h"
#include "back_propagation_config.h"

/* Private Function Prototypes -----------------------------------------------*/
static void InitWeightHidden(double* const wh);
static void InitWeightOutput(double* const wo);
static int GetData(const char* const filename, double* const data);
static double Forward(const double* const wh, const double* const wo, double* const hi, const double* const data);
static double F(const double u);
static void LearnWeightOutput(double* const wo, const double* const hi, const double* const data, const double output);
static void LearnWeightHidden(double* const wh, const double* const wo, const double* const hi, const double* const data, const double output);

/* APIs ----------------------------------------------------------------------*/
void BackPropagation(void) {
	double data[_MAX_NUM_OF_INPUT][_NUM_OF_INPUT + 1];
	double wh[_NUM_OF_HIDDEN][_NUM_OF_INPUT + 1];
	double wo[_NUM_OF_HIDDEN + 1];
	double hi[_NUM_OF_HIDDEN + 1];

	hRandom_Init();
	InitWeightHidden(&wh[0][0]);
	InitWeightOutput(wo);

  int number_of_data = GetData("./resources/back_propagation_data.txt", &data[0][0]);

	int count = 0;
	double err = _ERROR_VALUE_INIT;
	while (err > _ERROR_VALUE_LIMIT) {
		err = 0.0;
		for (int i = 0; i < number_of_data; ++i) {
			double output = Forward(&wh[0][0], wo, hi, &data[i][0]);
			LearnWeightOutput(wo, hi, &data[i][0], output);
			LearnWeightHidden(&wh[0][0], wo, hi, &data[i][0], output);
			err += pow(output - data[i][_NUM_OF_INPUT], 2.0);
		}
		++count;
		fprintf(stderr, "%d\t%lf\n", count, err);
	}

	for (int i = 0; i < _NUM_OF_HIDDEN; ++i) {
		for (int j = 0; j < _NUM_OF_INPUT + 1; ++j) {
			printf("%f ", wh[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < _NUM_OF_HIDDEN + 1; ++i) {
		printf("%f ", wo[i]);
	}
	printf("\n");

	printf("%d\n", number_of_data);
	for (int i = 0; i < number_of_data; ++i) {
		for (int j = 0; j < _NUM_OF_INPUT + 1; ++j) {
			printf("%f ", data[i][j]);
		}
		double output = Forward(&wh[0][0], wo, hi, &data[i][0]);
		printf("%lf\n", output);
	}
}

/* Private Functions ---------------------------------------------------------*/
static void InitWeightHidden(double* const wh) {
	for (int i = 0; i < _NUM_OF_HIDDEN; ++i) {
		for (int j = 0; j < _NUM_OF_INPUT + 1; ++j) {
			*(wh + (i * (_NUM_OF_INPUT + 1)) + j) = hRandom_GenerateDouble(-1, 1);
		}
	}
}

static void InitWeightOutput(double* const wo) {
  for (int i = 0; i < _NUM_OF_HIDDEN + 1; ++i) {
		*(wo + i) = hRandom_GenerateDouble(-1, 1);
	}
}

static int GetData(const char* const filename, double* const data) {
  int number_of_data = 0;
  int i = 0;
  FILE* fp = fopen(filename, "r");
  if (fp) {
    while (1) {
      int ret = fscanf(fp, "%lf", data + (number_of_data * (_NUM_OF_INPUT + 1)) + i);
      if (ret < 0) {
        break;
      }
      ++i;
      if (i > _NUM_OF_INPUT) {
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
  // Sigmoid function
  return 1.0 / (1.0 + exp(-u));
}

static void LearnWeightOutput(double* const wo, const double* const hi, const double* const data, const double output) {
	double delta = (*(data + _NUM_OF_INPUT) - output) * output * (1 - output);
	int i;
	for (i = 0; i < _NUM_OF_HIDDEN; ++i) {
		*(wo + i) += _ALPHA * *(hi + i) * delta;
	}
	*(wo + i) += _ALPHA * (-1.0) * delta;
}

static void LearnWeightHidden(double* const wh, const double* const wo, const double* const hi, const double* const data, const double output) {
	for (int i = 0; i < _NUM_OF_HIDDEN; ++i) {
		double deltaj = *(hi + i) * (1 - *(hi + i)) * *(wo + i) * (*(data + _NUM_OF_INPUT) - output) * output * (1 - output);
		int j;
		for (j = 0; j < _NUM_OF_INPUT; ++j) {
			*(wh + (i * _NUM_OF_INPUT) + j) += _ALPHA * *(data + j) * deltaj;
		}
		*(wh + (i * _NUM_OF_INPUT) + j) += _ALPHA * (-1.0) * deltaj;
	}
}
