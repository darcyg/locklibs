/** @brief		基与系统定时器实现的SCHEDULE 接口
 *	@file			led.h
 *	@author		au
 *	@version	1.0
 *	@date			2018/3/29
 *	@note     被模块不对外开放,不作注释.
 *	@sinc			-
 *
 */

#ifndef __SCHEDULE_H_
#define __SCHEDULE_H_

#include <platform.h>

#ifdef __cplusplus
	extern "C" {
#endif

/**< schedule interface */
typedef struct stScheduleTask {
	void				*func;
	void				*arg;
	_U32				start;
	_U32				delt;
	struct stScheduleTask *next;
}stScheduleTask_t;

void schedule_add(stScheduleTask_t *at, _U32 ms, void *func, void *arg);
void schedule_del(stScheduleTask_t *at);
_BOOL schedule_empty();


#ifdef __cplusplus
}
#endif
#endif
