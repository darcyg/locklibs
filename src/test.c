#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "log.h"
#include "parse.h"
#include "file_event.h"
#include "test.h"
#include "jansson.h"
#include "json_parser.h"
#include "timer.h"
#include "udp.h"

#include "schedule.h"
#include "ledx.h"


static stTestEnv_t ee;

static stScheduleTask_t st;


static stLed_t leds[] = {
	{8, 1, 0, 0, 0, 0},
	{8, 2, 0, 0, 0, 0},
	{8, 3, 0, 0, 0, 0},
};

static void test_func(void *arg) {
	schedule_add(&st, 1000, test_func, &st);
}


int		test_init(void *_th, void *_fet, int port) {
	ee.th = _th;
	ee.fet = _fet;

	ee.port = port;

	timer_init(&ee.step_timer, test_run);
	lockqueue_init(&ee.eq);
	
	ee.fd = udp_create(ee.port);
	file_event_reg(ee.fet, ee.fd, test_in, NULL, NULL);

	//schedule_add(&st, 1000, test_func, &st);

	ledInit(leds,sizeof(leds)/sizeof(leds[0]));

	log_debug("11111");
	ledBlink(0, 100, 100, 200);
	log_debug("11111");
	ledBlink(1, 100, 200, 100);
	log_debug("11111");

	return 0;
}

int		test_step() {
	timer_cancel(ee.th, &ee.step_timer);
	timer_set(ee.th, &ee.step_timer, 10);
	return 0;
}

int		test_push(stEvent_t *e) {
	lockqueue_push(&ee.eq, e);
	test_step();
	return 0;
}

void	test_run(struct timer *timer) {
	stEvent_t *e;

	if (!lockqueue_pop(&ee.eq, (void**)&e)) {
		return;
	}

	if (e == NULL) {
		return;
	}

	/* Deal The Event */
	//state_machine_step(&smApp, e);

	FREE(e);

	test_step();
	return;
}

void	test_in(void *arg, int fd) {
	char buf[1024];	
	int  size = 0;
	char cliip[32];
	int  cliport;

		
	int ret = udp_recv(fd, buf, sizeof(buf), cliip, &cliport, 4, 800);
	if (ret < 0) {
		log_debug("what happend?");
		return;
	}

	if (ret == 0) {
		log_debug("error!");
		return;
	}

	size = ret;
	buf[size] = 0;

	char load[1024];
	int load_len = ret - 4;
	strncpy(load, buf + 3, ret - 4);
	load[load_len] = 0;
	
	log_info("[RECV]:%s", load);

	return;
}
