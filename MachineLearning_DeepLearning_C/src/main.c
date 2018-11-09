/*******************************************************************************
 * @brief   Main file.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @history
 *    2018.10.22  Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include "neuron.h"
#include "nn.h"
#include "back_propagation.h"

/* Private Function Prototypes -----------------------------------------------*/
static void PrintMenu(void);

/* Main Routine --------------------------------------------------------------*/
int main(void) {
  int state = 1;
  while (state) {
    PrintMenu();
    int menu = getchar();
    switch (menu) {
      case '7': Neuron();           break;
      case '8': NeuralNetwork();    break;
      case '9': BackPropagation();  break;

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
  printf("7. Neuron\n");
  printf("8. Neural Network\n");
  printf("9. Back Propagation\n");
  printf("q. Exit\n");
  printf("============\n");
  printf("> ");
}
