#include "platform.h"

#if PLATFORM_STM32



#include "stm32l0xx_hal.h"          
#include "FreeRTOS.h"
#include "timers.h"



#define GPIO_PORT(port) ((GPIO_TypeDef*)(IOPPERIPH_BASE + 0x00000000U + 0x400 * (port)))
#define GPIO_PIN(pin) (1 << (pin))
#define GPIO_MODE(mode) (mode)
#define GPIO_PULL(pull) (pull)
#define GPIO_SPEED(speed) (speed)



_U32 _TIMER_CURRENT() {
  HAL_GetTick();
  return 0;
}

void _TIMER_SCHEDULE(void *func, _U32 delt) {
  static  TimerHandle_t *t = _NULL; 
  if (t == _NULL) { 
    t = xTimerCreate("schedule timer", delt,  pdFALSE, &t, (TimerCallbackFunction_t)func); 
  } else { 
    xTimerChangePeriod(t, delt, portMAX_DELAY); 
  } 
}

void _LED_ON(_U8 port, _U8 pin) {
  HAL_GPIO_WritePin(GPIO_PORT(port), GPIO_PIN(pin), GPIO_PIN_SET);
}
void _LED_OF(_U8 port, _U8 pin) { 
  HAL_GPIO_WritePin(GPIO_PORT(port), GPIO_PIN(pin), GPIO_PIN_RESET);
}
void _LED_TG(_U8 port, _U8 pin) {
  HAL_GPIO_WritePin(GPIO_PORT(port), GPIO_PIN(pin), (GPIO_PinState)!HAL_GPIO_ReadPin(GPIO_PORT(port), GPIO_PIN(pin)));
} 

void _GPIO_CONFIG(_U8 port, _U8 pin, _U8 mode, _U8 pull, _U8 speed) {
  GPIO_InitTypeDef GPIO_InitStructure; 

  GPIO_InitStructure.Pin = GPIO_PIN(pin);
  GPIO_InitStructure.Mode = GPIO_MODE(mode);
  GPIO_InitStructure.Pull = GPIO_PULL(pull);
  GPIO_InitStructure.Speed = GPIO_SPEED(speed);

  HAL_GPIO_Init(GPIO_PORT(port), &GPIO_InitStructure);
}

void _GPIO_HIGH(_U8 port, _U8 pin) {
	HAL_GPIO_WritePin(GPIO_PORT(port), GPIO_PIN(pin), GPIO_PIN_SET); 
}

void _GPIO_LOW(_U8 port, _U8 pin) {
	HAL_GPIO_WritePin(GPIO_PORT(port), GPIO_PIN(pin), GPIO_PIN_RESET); 
}


#endif


#if PLATFORM_LINUX

#include "time.h"
#include "timer.h"
#include "log.h"

extern struct timer_head th; 
static struct timer tr; 
static int					flag = 0; 
static void *				cb = _NULL;

static void _TIMER_CB(struct timer *t) {
  if (cb != _NULL) {
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

inline void _LED_ON(_U8 port, _U8 pin) {
  printf("LED_ON: %d_%d\n", port, pin);
}
inline void _LED_OF(_U8 port, _U8 pin) { 
  printf("LED_OF: P%d_%d\n", port, pin);
}
inline void _LED_TG(_U8 port, _U8 pin) {
  printf("LED_TG: P%d_%d\n", prot, pin);
} 
#endif
