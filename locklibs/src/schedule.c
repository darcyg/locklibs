#include "schedue.h"

static stScheduleTask_t * task_list = NULL;

static stScheduleTask_t * schedue_search(stScheduleTask_t * at) {
	stScheduleTask_t *curr = task_list;
	
	while (curr != NULL) {
		if (curr == at) {
			break;
		}
		curr = curr->next;
	}

	return curr;
}

static stScheduleTask_t * _schedue_add(stScheduleTask_t *at) {
	stScheduleTask_t *prev = task_list;
	
	while (prev != NULL && prev->next != NULL) {
		prev = prev->next;
	}

	if (prev == NULL) {
		task_list = at;
	} else {
		prev->next = at;
	}

	at->next = NULL;

	return at;
}

static stScheduleTask_t *schedue_first_task_to_exec() {
	stScheduleTask_t *curr = task_list;
	stScheduleTask_t *min  = curr;

	
	while (curr != NULL) {
		if (curr->start + curr->delt <= min->start + min->delt) {
			min = curr;
		}
		curr = curr->next;
	}
	
	return min;
}

static _I32 schedue_first_task_delay() {
	stScheduleTask_t *min = schedue_first_task_to_exec();
	if (min == NULL) {
		return -1;
	}
	_U32 ret = min->start + min->delt - schedue_current();

	if (ret < 0) {
		ret = 0; //10ms
	}
	
	return ret;
}

static _U32 schedue_current() {
	return _TIMER_CURRENT();
}

static void schedue_execute() {
	_I32 delt = schedue_first_task_delay();
	if (delt < 0) {
		return;
	}

	if (delt == 0) {
		stScheduleTask_t *t = schedue_first_task_to_exec();
		schedue_del(task);

		t->func(t->arg);
	}

	delt = schedue_first_task_delay();
	if (delt < 0) {
		return;
	}

	_TIMER_SCHEDULE(schedue_execute, delt);
}

////////////////////////////////////////////////////////////////////////
void schedue_add(stScheduleTask_t *at, _U32 ms, void *func, void *arg) {
	
	if (schedue_search(at) == NULL) {
		_schedue_add(at);
	}

	at->func = func;
	at->arg = arg;
	at->start = schedue_current();
	at->delt = ms;

	schedue_execute();
}

void schedue_del(stScheduleTask_t *at) {
	stScheduleTask_t *prev = NULL;
	stScheduleTask_t *curr = task_list;

	while (curr != NULL) {
		if (curr == at) {
			break;
		}
	
		prev = curr;
		curr = curr->next;
	}

	if (curr == at && curr != NULL) {
		if (prev == NULL) {
			task_list = curr->next;
		} else {
			prev->next = curr->next;
		}
	}
}


