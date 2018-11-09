/*******************************************************************************
 * @brief   Random module.
 * @author  llHoYall <hoya128@gmail.com>
 * @version v1.0
 * @history
 *  	2018.09.07  Created.
 ******************************************************************************/

#ifndef __HoYa_RANDOM_H__
#define __HoYa_RANDOM_H__

/* API Prototypes ------------------------------------------------------------*/
void hRandom_Init(void);
int hRandom_GenerateInt(const int min, const int max);
double hRandom_GenerateDouble(const double min, const double max);

#endif
