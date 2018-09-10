/*******************************************************************************
 * @brief   Read data from file.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @note
 *  - 2018.09.04  Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include "ReadData.h"

/* APIs ----------------------------------------------------------------------*/
void ReadTrainingData(const char* const filename, const int data_size, const int category_size, int* const data, int* const label) {
  FILE* fp = fopen(filename, "r");
  if (fp) {
    for (int i = 0; i < data_size; ++i) {
      for (int j = 0; j < category_size; ++j) {
        fscanf(fp, "%d", data + (i * category_size) + j);
      }
      fscanf(fp, "%d", label + i);
    }
    fclose(fp);
  } else {
    printf("File Open Error\n");
  }
}

void ReadTestData(const char* const filename, const int data_size, const int category_size, int* const data) {
  FILE* fp = fopen(filename, "r");
  if (fp) {
    for (int i = 0; i < data_size; ++i) {
      for (int j = 0; j < category_size; ++j) {
        fscanf(fp, "%d", data + (i * category_size) + j);
      }
    }
    fclose(fp);
  } else {
    printf("File Open Error\n");
  }
}
