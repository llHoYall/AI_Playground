/*******************************************************************************
 * @brief   Main file.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @note
 *  - 2018.10.22  Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include "neuron.h"
#include "nn.h"

/* Private Function Prototypes -----------------------------------------------*/
static void PrintMenu(void);

/* Main Routine --------------------------------------------------------------*/
int main(void) {
  int state = 1;
  while (state) {
    PrintMenu();
    int menu = getchar();
    switch (menu) {
      case '1': neuron();         break;
      case '2': NeuralNetwork();  break;

      case 'q':
      default:
        state = 0;
        break;
    }
    getchar();
  }

  return 0;
}

/* Private Functions ---------------------------------------------------------*/
static void PrintMenu(void) {
  printf("\n");
  printf("=== Menu ===\n");
  printf("1. Neuron\n");
  printf("2. Neural Network\n");
  printf("q. Exit\n");
  printf("============\n");
  printf("> ");
}
