/** @brief		基与系统定时器实现的SCHEDULE 接口
 *	@file			led.h
 *	@author		au
 *	@version	1.0
 *	@date			2018/3/29
 *	@note     -
 *	@sinc			-
 *
 */

#ifndef __SCHEDULE_H_
#define __SCHEDULE_H_
#endif

#include <common.h>

#ifdef __cplusplus
    extern "C" {
#endif

/**< schedule interface */
typedef struct stScheduleTask {
	void				*func;
	void				*arg;
	_U32				start;
	_U32				delt;
	struct stScheduleTask *next
}stScheduleTask_t;


void schedule_add();
void schedule_del();
void schedule_current();


#ifdef __cplusplus
}
#endif
#endif
