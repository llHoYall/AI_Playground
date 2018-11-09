/*******************************************************************************
 * @brief   Q learning module.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @note
 *  - 2018.09.11  Created.
 ******************************************************************************/

#ifndef __Q_LEARNING_H__
#define __Q_LEARNING_H__

/* API Prototypes ------------------------------------------------------------*/
int SelectA(const double epsilon, const int old_s, int* const q);
int UpdateQ(const double alpha, const double gamma, const int s, int* const q);

#endif
