/** @brief		数据类型定义及一些常用的宏
 *	@file			common.h
 *	@author		au
 *	@version	1.0
 *	@date			2018/3/29
 *	@note     -
 *	@sinc			-
 *
 */
#ifndef __COMMON_H_
#define __COMMON_H_
#endif
#ifdef __cplusplus
    extern "C" {
#endif


/**< common used types */
#define _U8		unsigned char 
#define _U16	unsigned short
#define _U32	unsigned int
#define _I8		char
#define _I16	short
#define _I32	int
#define _F32	float
#define _BOOL	unsigned char

#define _TRUE		1
#define _FALSE	0


#define PLATFORM_LINUX 1
#define PLATFORM_STM32 0


/**< STM32 INTERFACE ======================================================================================*/
#if PLATFORM_STM32

#define _PRINTF

/**< led controller interface */
#define _LED_ON(port, pin)		do { HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET); } while (0)
#define _LED_OF(port, pin)		do { HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);} while (0)
#define _LED_TG(port, pin)		do { HAL_GPIO_WritePin(port,	pin, !HAL_GPIO_ReadPin(port, pin)); } while (0)

/**< schedule interface */
#define _TIMER_CURRENT()
#define _TIMER_SCHEDULE(func, delt) do { \
	static  TimerHandle_t *t = NULL; \
	if (t == NULL) { \
		t = xTimerCreate("schedule timer", delt,  pdFALSE, &t, func); \
	} else { \
		xTimerChangePeriod(t, delt, portMAX_DELAY); \
	} \
} while (0)

#endif

/**< LINUX INTERFACE ======================================================================================*/
#if PLATFORM_LINUX

#define _PRINTF printf

#define _LED_ON(port, pin)		do { printf("LED_ON: P%d_%d\n", port, pin);} while (0)
#define _LED_OF(port, pin)		do { printf("LED_OF: P%d_%d\n", port, pin);} while (0)
#define _LED_TG(port, pin)		do { printf("LED_TG: P%d_%d\n", prot, pin);} while (0)

/**< schedule interface */
#define _TIMER_CURRENT()
#define _TIMER_SCHEDULE(func, delt) do { \
	static  TimerHandle_t *t = NULL; \
	if (t == NULL) { \
		t = xTimerCreate("schedule timer", delt,  pdFALSE, &t, func); \
	} else { \
		xTimerChangePeriod(t, delt, portMAX_DELAY); \
	} \
} while (0)

#endif

#ifdef __cplusplus
}
#endif
#endif
