/*******************************************************************************
 * @brief   Main file.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @note
 *  - 2018.10.03  Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "config.h"

/* Definitions ---------------------------------------------------------------*/
#define _WEIGHT   0
#define _VALUE    1

/* Private Function Prototypes -----------------------------------------------*/
static int GenerateRandomInt(const int limit);
static void InitKnapsack(int* const baggage);
static void InitPool(int* const pool);
static void Mating(const int* const baggage, const int* const pool, int* const ng_pool);
static int EvalFitness(const int* const baggage, const int* const gen);
static int SelectParent(const int* const roulette, const int total_fitness);
static void Crossing(const int* const pool1, const int* const pool2, int* const ng_pool1, int* const ng_pool2);
static void Mutation(int* const ng_pool);
static void SelectNextGeneration(const int* const baggage, const int* const ng_pool, int* const pool);
static void PrintGA(const int* const baggage, const int* const pool);

/* Main Routine --------------------------------------------------------------*/
int main(void) {
  int baggage[_NUM_OF_BAGGAGE][2] = { 0, };
  int pool[_NUM_OF_POOL][_NUM_OF_BAGGAGE] = { 0, };
  int next_gen_pool[_NUM_OF_POOL * 2][_NUM_OF_BAGGAGE] = { 0, };

  srand(time(NULL));
  InitKnapsack(&baggage[0][0]);
  InitPool(&pool[0][0]);

  for (int i = 0; i < _LAST_GENERATION; ++i) {
    printf("%dth generation\n", i);
    Mating(&baggage[0][0], &pool[0][0], &next_gen_pool[0][0]);
    Mutation(&next_gen_pool[0][0]);
    SelectNextGeneration(&baggage[0][0], &next_gen_pool[0][0], &pool[0][0]);

    PrintGA(&baggage[0][0], &pool[0][0]);
  }

  return 0;
}

/* Private Functions ---------------------------------------------------------*/
static int GenerateRandomInt(const int limit) {
  int rnd;
  while((rnd = ((double)rand() / RAND_MAX) * limit) == limit) ;
  return rnd;
}

static void InitKnapsack(int* const baggage) {
  for (int i = 0; i < _NUM_OF_BAGGAGE; ++i) {
    *(baggage + (i * 2) + _WEIGHT) = GenerateRandomInt(100);
    *(baggage + (i * 2) + _VALUE) = GenerateRandomInt(100);
  }
}

static void InitPool(int* const pool) {
	for (int i = 0; i < _NUM_OF_POOL; ++i) {
		for (int j = 0; j < _NUM_OF_BAGGAGE; ++j) {
			*(pool + (i * _NUM_OF_BAGGAGE) + j) = GenerateRandomInt(2);
		}
	}
}

static void Mating(const int* const baggage, const int* const pool, int* const ng_pool) {
  int roulette[_NUM_OF_POOL] = { 0, };
  int total_fitness = 0;
  for (int i = 0; i < _NUM_OF_POOL; ++i) {
    roulette[i] = EvalFitness(baggage, pool + (i * _NUM_OF_BAGGAGE));
    total_fitness += roulette[i];
  }

  int mama;
  int papa;
  for (int i = 0; i < _NUM_OF_POOL; ++i) {
    do {
      mama = SelectParent(&roulette[0], total_fitness);
      papa = SelectParent(&roulette[0], total_fitness);
    } while (mama == papa);

    Crossing(pool + (mama * _NUM_OF_BAGGAGE), pool + (papa * _NUM_OF_BAGGAGE), ng_pool + (i * 2 * _NUM_OF_BAGGAGE), ng_pool + ((i * 2 + 1) * _NUM_OF_BAGGAGE));
  }
}

static int EvalFitness(const int* const baggage, const int* const pool) {
  int weight = 0;
  int value = 0;
  for (int i = 0; i < _NUM_OF_BAGGAGE; ++i) {
    weight += (*(baggage + (i * 2) + _WEIGHT)) * (*(pool + i));
    value += (*(baggage + (i * 2) + _VALUE)) * (*(pool + i));
  }
  if (weight >= _WEIGHT_LIMIT) {
    value = 0;
  }
  return value;
}

static int SelectParent(const int* const roulette, const int total_fitness) {
  int accumulate = 0;
  int ball = GenerateRandomInt(total_fitness);
  int i;
  for (i = 0; i < _NUM_OF_POOL; ++i) {
    accumulate += *(roulette + i);
    if (accumulate > ball) {
      break;
    }
  }
  return i;
}

static void Crossing(const int* const pool1, const int* const pool2, int* const ng_pool1, int* const ng_pool2) {
  int cross_point = GenerateRandomInt(_NUM_OF_BAGGAGE);
  int i;
  for (i = 0; i < cross_point; ++i) {
    *(ng_pool1 + i) = *(pool1 + i);
    *(ng_pool2 + i) = *(pool2 + i);
  }
  for (; i < _NUM_OF_BAGGAGE; ++i) {
    *(ng_pool2 + i) = *(pool1 + i);
    *(ng_pool1 + i) = *(pool2 + i);
  }
}

static void Mutation(int* const ng_pool) {
  for (int i = 0; i < _NUM_OF_POOL * 2; ++i) {
    for (int j = 0; j < _NUM_OF_BAGGAGE; ++j) {
      if ((double)GenerateRandomInt(100) / 100.0 <= _MUTATION_RATE) {
        *(ng_pool + (i * _NUM_OF_BAGGAGE) + j) ^= 0x01;
      }
    }
  }
}

static void SelectNextGeneration(const int* const baggage, const int* const ng_pool, int* const pool) {
  int roulette[_NUM_OF_POOL * 2] = { 0, };
  for (int i = 0; i < _NUM_OF_POOL; ++i) {
    int total_fitness = 0;
    int j;
    for (j = 0; j < _NUM_OF_POOL * 2; ++j) {
      roulette[j] = EvalFitness(baggage, ng_pool + (j * _NUM_OF_BAGGAGE));
      total_fitness += roulette[j];
    }

    int index = GenerateRandomInt(total_fitness);
    int accumulate = 0;
    for (j = 0; j < _NUM_OF_POOL * 2; ++j) {
      accumulate += roulette[j];
      if (accumulate > index) {
        break;
      }
    }

    for (int k = 0; k < _NUM_OF_BAGGAGE; ++k) {
      *(pool + (i * _NUM_OF_BAGGAGE) + k) = *(ng_pool + (j * _NUM_OF_BAGGAGE) + k);
    }
  }
}

static void PrintGA(const int* const baggage, const int* const pool) {
  int best_fitness = 0;
  int elite_pool;
  double total_fitness = 0;
  for (int i = 0; i < _NUM_OF_POOL; ++i) {
    for (int j = 0; j < _NUM_OF_BAGGAGE; ++j) {
      printf("%1d", *(pool + (i * _NUM_OF_BAGGAGE) + j));
    }
    int fitness = EvalFitness(baggage, pool + (i * _NUM_OF_BAGGAGE));
    printf("\t%d\n", fitness);
    if (fitness > best_fitness) {
      best_fitness = fitness;
      elite_pool = i;
    }
    total_fitness += fitness;
  }
  printf("%d\t%d\t", elite_pool, best_fitness);
  printf("%lf\n", total_fitness / _NUM_OF_POOL);
}
