/*******************************************************************************
 * @brief   Calculator for inductive learning.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @note
 *  - 2018.09.08  Created.
 ******************************************************************************/

#ifndef __CALCULATE_H__
#define __CALCULATE_H__

/* API Prototypes ------------------------------------------------------------*/
int DoModeling(const int data_size, const int category_size, int* const data, int* const label, int* const predict);
int DoPredict(const int category_size, int* const data, int* const model);

#endif
