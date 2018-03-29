#include "led.h"

static stLedEnv_t le = {NULL, 0};

void ledInit(stLed_t *leds, _U32 cnt) {
	if (le.init || leds == NULL || cnt == 0) {
		return;
	}
	
	le.leds = leds;
	le.cnt	= cnt;
}

void ledOn(_U8 ledIdx) {
	if (ledIdx > le.cnt - 1) {
		return;
	}

	stLed_t *led = &le.leds[ledIdx];

	LED_ON(led.port, led.pin);
}

void ledOff(_U8 ledIdx) {
	if (ledIdx > le.cnt - 1) {
		return;
	}

	stLed_t *led = &le.leds[ledIdx];

	LED_OF(led.port, led.pin);
}

void ledBlink(_U8 ledIdx, _U16 periodCnt, _U16 tickOn, _U16 tickOff) {
	if (ledIdx > le.cnt - 1) {
		return;
	}
	
	stLed_t *led = &le.leds[ledIdx];

	led->periodCnt	= periodCnt;
	led->tickOn			= tickOn;
	led->tickOff		= tickOff;

	_SCHEDULE_ADD(&led->task, 10, ledScheduleTaskFunc,led);
}

void ledScheduleTaskFunc(void *task) {
	stScheduleTask_t *t = (stScheduleTask_t*)task;
	if (t == NULL) {
		return;
	}

	stLed_t *led = (stLed_t *)t->args;
	if (led == NULL) {
		return;
	}

	if (led->periodCnt = 0) {
		_LED_OF(led->port, led->pin);
		return;
	}

	led->val = !led->val;

	if (led->val) {
		_LED_ON(led->port, led->pin);

		_SCHEDULE_ADD(&led->task, led->tickOn, ledScheduleTaskFunc,led);
	} else {	
		_LED_OF(led->port, led->pin);

		_SCHEDULE_ADD(&led->task, led->tickOff, ledScheduleTaskFunc,led);

		--led->periodCnt;
	}
}
