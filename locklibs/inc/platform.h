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
          

#define PLATFORM_LINUX 0
#define PLATFORM_STM32 1



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




#define _PRINTF

/**< gpio controller interface */
#if PLATFORM_STM32
#define _GPIO_MODE_OUT_PP       ((_U32)0x00000001U)
#define _GPIO_NOPULL            ((_U32)0x00000000U)
#define _GPIO_SPEED_LOW         ((_U32)0x00000000U)
#define _GPIO_MODE_ANALOG       ((_U32)0x00000003U)
#elif PLATFORM_LINUX
#endif
void _GPIO_CONFIG(_U8 port, _U8 pin, _U8 mode, _U8 pull, _U8 speed);
void _GPIO_HIGH(_U8 port, _U8 pin);
void _GPIO_LOW(_U8 port, _U8 pin);

/**< led controller interface */
void _LED_ON(_U8 port, _U8 pin);
void _LED_OF(_U8 port, _U8 pin);
void _LED_TG(_U8 port, _U8 pin);


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



#ifdef __cplusplus
}
#endif

#endif
