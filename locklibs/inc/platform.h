/** @brief		数据类型定义及一些常用的宏，平台相关的接口等
 *	@file			common.h
 *	@author		au
 *	@version	1.0
 *	@date			2018/3/29
 *	@note     -
 *	@sinc			-
 *
 */
#ifndef __PLATFORM_H_
#define __PLATFORM_H_

#ifdef __cplusplus
	extern "C" {
#endif


#define PLATFORM_LINUX 1
#define PLATFORM_STM32 0



/**< common used types */
#define _U8		unsigned char 
#define _U16	unsigned short
#define _U32	unsigned int
#define _I8		char
#define _I16	short
#define _I32	int
#define _F32	float
#define _BOOL	unsigned char


/**< Const Define */
#define _TRUE		1
#define _FALSE	0


#define _NULL		0



/**< STM32 INTERFACE ======================================================================================*/
#if PLATFORM_STM32

#define _PRINTF

/**< led controller interface */
#define _LED_ON(port, pin)		do { HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET); } while (0)
#define _LED_OF(port, pin)		do { HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);} while (0)
#define _LED_TG(port, pin)		do { HAL_GPIO_WritePin(port,	pin, !HAL_GPIO_ReadPin(port, pin)); } while (0)

/**< schedule interface */

/** _TIMER_CURRENT
 *  
 * 获取当前系统时钟,单位ms
 * 
 * @param none
 * 
 * @return none
 * 
 * @warning none
 * 
 * @note none
 *
 * @see none
 */
_U32 _TIMER_CURRENT();

/** _TIMER_SCHEDULE 
 * 
 * 开启调度, delt Ms 后回调 func
 * 
 * @param[in] func 回调函数
 * @param[in] delt 回调时间, 单位ms
 * 
 * @return none
 * 
 * @warning none
 * 
 * @note none
 *
 * @see none
 */
void _TIMER_SCHEDULE(void *func, _U32 delt);



/**< LINUX INTERFACE ======================================================================================*/
#elif PLATFORM_LINUX

#include "time.h"
#include "timer.h"
#include "log.h"

#define _PRINTF printf

#define _LED_ON(port, pin)		do { printf("LED_ON: P%d_%d\n", port, pin);} while (0)
#define _LED_OF(port, pin)		do { printf("LED_OF: P%d_%d\n", port, pin);} while (0)
#define _LED_TG(port, pin)		do { printf("LED_TG: P%d_%d\n", prot, pin);} while (0)

/**< schedule interface */

/** _TIMER_CURRENT
 *  
 * 获取当前系统时钟,单位ms
 * 
 * @param none
 * 
 * @return none
 * 
 * @warning none
 * 
 * @note none
 *
 * @see none
 */
_U32 _TIMER_CURRENT();

/** _TIMER_SCHEDULE 
 * 
 * 开启调度, delt Ms 后回调 func
 * 
 * @param[in] func 回调函数
 * @param[in] delt 回调时间, 单位ms
 * 
 * @return none
 * 
 * @warning none
 * 
 * @note none
 *
 * @see none
 */
void _TIMER_SCHEDULE(void *func, _U32 delt);

#endif


#ifdef __cplusplus
}
#endif

#endif
