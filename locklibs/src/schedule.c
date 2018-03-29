#include "schedule.h"

static stScheduleTask_t * task_list = _NULL;

static stScheduleTask_t * schedule_search(stScheduleTask_t * at) {
	stScheduleTask_t *curr = task_list;
	
	while (curr != _NULL) {
		if (curr == at) {
			break;
		}
		curr = curr->next;
	}

	return curr;
}

static stScheduleTask_t * _schedule_add(stScheduleTask_t *at) {
	stScheduleTask_t *prev = task_list;
	
	while (prev != _NULL && prev->next != _NULL) {
		prev = prev->next;
	}

	if (prev == _NULL) {
		task_list = at;
	} else {
		prev->next = at;
	}

	at->next = _NULL;

	return at;
}

static stScheduleTask_t *schedule_first_task_to_exec() {
	stScheduleTask_t *curr = task_list;
	stScheduleTask_t *min  = curr;

	
	while (curr != _NULL) {
		if (curr->start + curr->delt <= min->start + min->delt) {
			min = curr;
		}
		curr = curr->next;
	}
	
	return min;
}

static _U32 schedule_current() {
	return _TIMER_CURRENT();
}

static _I32 schedule_first_task_delay() {
	stScheduleTask_t *min = schedule_first_task_to_exec();
	if (min == _NULL) {
		return -1;
	}
	_I32 ret = min->start + min->delt - schedule_current();

	if (ret < 0) {
		ret = 0; //10ms
	}

	return ret;
}


static void schedule_execute() {
	_I32 delt = schedule_first_task_delay();
	if (delt < 0) {
		return;
	}

	if (delt == 0) {
		stScheduleTask_t *t = schedule_first_task_to_exec();
		schedule_del(t);

		((void (*)(void*))t->func)(t->arg);
	}

	delt = schedule_first_task_delay();
	if (delt < 0) {
		return;
	}

	_TIMER_SCHEDULE(schedule_execute, delt);
}

////////////////////////////////////////////////////////////////////////
void schedule_add(stScheduleTask_t *at, _U32 ms, void *func, void *arg) {
	
	if (schedule_search(at) == _NULL) {
		_schedule_add(at);
	}

	at->func = func;
	at->arg = arg;
	at->start = schedule_current();
	at->delt = ms;

	schedule_execute();
}

void schedule_del(stScheduleTask_t *at) {
	stScheduleTask_t *prev = _NULL;
	stScheduleTask_t *curr = task_list;

	while (curr != _NULL) {
		if (curr == at) {
			break;
		}
	
		prev = curr;
		curr = curr->next;
	}

	if (curr == at && curr != _NULL) {
		if (prev == _NULL) {
			task_list = curr->next;
		} else {
			prev->next = curr->next;
		}
	}
}

_BOOL schedule_empty() {
	return (task_list == _NULL);
}

