/** @brief		TOUCH 操作函数接口
 *	@file			backlightx.h
 *	@author		au
 *	@version	1.0
 *	@date			2018/3/29
 *	@note     -
 *	@sinc			-
 *
 */
#ifndef __TOUCHX_H_
#define __TOUCHX_H_

#include "platform.h"
#include "schedule.h"

#ifdef __cplusplus
    extern "C" {
#endif

typedef struct stBackLight {
	_U8 port;
	_U8 pin;
} stBackLight_t;

/** backLightOn()
 *
 * 打开背光 
 *
 * @param[in]  none
 * 
 * @return none
 *
 * @warning none
 *
 * @note none
 *
 * @see none
 */
void backLightOn();

/** backLightOff()
 *
 * 关闭背光 
 *
 * @param[in]  none
 * 
 * @return none
 *
 * @warning none
 *
 * @note none
 *
 * @see none
 */
void backLightOff();

#ifdef __cplusplus
}
#endif
#endif
