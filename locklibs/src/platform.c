#include "platform.h"

#if PLATFORM_STM32

_U32 _TIMER_CURRENT() {
	/**> TODO */
}

void _TIMER_SCHEDULE(void *func, _U32 delt) {
	static  TimerHandle_t *t = NULL; 
	if (t == NULL) { 
		t = xTimerCreate("schedule timer", delt,  pdFALSE, &t, func); 
	} else { 
		xTimerChangePeriod(t, delt, portMAX_DELAY); 
	} 
}

#endif


#if PLATFORM_LINUX

extern struct timer_head th; 
static struct timer tr; 
static int					flag = 0; 
static void *				cb = NULL;

static void _TIMER_CB(struct timer *t) {
	if (cb != NULL) {
		((void (*)())cb)();
	}
}


_U32 _TIMER_CURRENT() {
	struct timespec time_start={0, 0};
	clock_gettime(CLOCK_REALTIME, &time_start);
	return time_start.tv_sec * 1000 + time_start.tv_nsec/(1000*1000);
}


void _TIMER_SCHEDULE(void *func, _U32 delt) {

	if (flag == 0) { 
		timer_init(&tr, _TIMER_CB);
		cb = func;
	} else {
		timer_cancel(&th, &tr);
	}

	timer_set(&th, &tr, delt);
} 

#endif
