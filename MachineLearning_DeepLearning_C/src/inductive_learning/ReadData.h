/*******************************************************************************
 * @brief   Read data from file.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @note
 *  - 2018.09.04  Created.
 ******************************************************************************/

#ifndef __READ_DATA_H__
#define __READ_DATA_H__

/* API Prototypes ------------------------------------------------------------*/
void ReadTrainingData(const char* const filename, const int data_size, const int category_size, int* const data, int* const label);
void ReadTestData(const char* const filename, const int data_size, const int category_size, int* const data);

#endif
