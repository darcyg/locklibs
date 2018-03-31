#include "ledx.h"

static stLedEnv_t le = {_NULL, 0, 0};

static void ledScheduleTaskFunc(void *arg);

void ledInit(stLed_t *leds, _U32 cnt) {
	if (le.init || leds == _NULL || cnt == 0) {
		return;
	}
	
	le.leds = leds;
	le.cnt	= cnt;
}

void ledOn(_U8 ledIdx) {
	if (ledIdx > le.cnt - 1) {
		return;
	}

	stLed_t *led = le.leds + ledIdx;

        printf("%p", led);
	_LED_ON(led->port, led->pin);
}

void ledOff(_U8 ledIdx) {
	if (ledIdx > le.cnt - 1) {
		return;
	}

	stLed_t *led = le.leds + ledIdx;

	_LED_OF(led->port, led->pin);
}

void ledBlink(_U8 ledIdx, _U16 periodCnt, _U16 tickOn, _U16 tickOff) {
	if (ledIdx > le.cnt - 1) {
		return;
	}
	
	stLed_t *led = le.leds + ledIdx;

	led->periodCnt	= periodCnt;
	led->tickOn			= tickOn;
	led->tickOff		= tickOff;

	schedule_add(&led->task, 10, (void*)ledScheduleTaskFunc,led);
}

void ledScheduleTaskFunc(void *arg) {
	stLed_t *led = (stLed_t *)arg;
	if (led == _NULL) {
		return;
	}

	if (led->periodCnt == 0) {
		_LED_OF(led->port, led->pin);
		return;
	}

	led->val = !led->val;

	if (led->val) {
		_LED_ON(led->port, led->pin);

		schedule_add(&led->task, led->tickOn, (void*)ledScheduleTaskFunc,led);
	} else {	
		_LED_OF(led->port, led->pin);

		schedule_add(&led->task, led->tickOff, (void*)ledScheduleTaskFunc,led);

		--led->periodCnt;
	}
}
