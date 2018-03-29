/** @brief		LED 操作函数接口
 *	@file			led.h
 *	@author		au
 *	@version	1.0
 *	@date			2018/3/29
 *	@note     -
 *	@sinc			-
 *
 */
#ifndef __LED_H_
#define __LED_H_

#include "platform.h"
#include "schedule.h"

#ifdef __cplusplus
    extern "C" {
#endif

/**< led struct define */
typedef struct stLed {
	_U8		port;					/**< led 端口 */
	_U8		pin;					/**< led 引脚 */
	_U8		val;					/**< led on/off */

	_U16	periodCnt;		/**< led 闪烁模式下的 周期数 */
	_U16	tickOn;				/**< led 闪烁模式下的 单个周期内 on 状态的 tick 数 */
	_U16	tickOff;			/**< led 闪烁模式下的 单个周期内 off 状态的 tick  数 */

	stScheduleTask_t task;
}stLed_t;

/**< led module environment define */
typedef struct stLedEnv {
	stLed_t		*leds;		/**< led 数组 */
	_U32			cnt;			/**< 总的led的cnt */
	_BOOL			init;			/**< led module 是否初始化 */
}stLedEnv_t;

/** ledInit
 *
 * led 模块初始化
 *
 * @param[in]  leds 要初始化的led的数据
 * @param[in]  cnt  要初始化的led的总数
 * 
 * @return none
 *
 * @warning none
 *
 * @note none
 *
 * @see none
 */
void ledInit(stLed_t *leds, _U32 cnt);

/** ledOn
 *
 * 点亮led
 *
 * @param[in] ledIdx 要点亮的led在初始化数据结构中的序号,从0开始
 * 
 * @return none
 *
 * @warning none
 *
 * @note 
 *
 * @see none
 */
void ledOn(_U8 ledIdx);

/** ledOff
 *
 * 熄灭led
 *
 * @param[in]  ledIdx 要熄灭的led在初始化数据结构中的序号,从0开始
 * 
 * @return none
 *
 * @warning none
 *
 * @note 
 *
 * @see none
 */
void ledOff(_U8 ledIdx);

/** ledBlink
 *
 * 连续闪烁led
 *
 * @param[in]  ledIdx			操作的led在初始化数据结构中的序号,从0开始
 * @param[in]  periodCnt  要闪烁的总的周期数
 * @param[in]  tickOn			闪烁单周期内点亮的tick数
 * @param[in]  tickOff		闪烁单周期内熄灭的tick数
 * 
 * @return none
 *
 * @warning none
 *
 * @note none
 *
 * @see none
 */
void ledBlink(_U8 ledIdx, _U16 periodCnt, _U16 tickOn, _U16 tickOff);

#ifdef __cplusplus
}
#endif
#endif
