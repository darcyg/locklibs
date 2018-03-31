#include "backlight.h"

static stBackLight_t be = {0, 0};

void backLightInit(_U8 port, _U8 pin) {
	be.port = port;
	be.pin = pin;
	_GPIO_CONFIG(port, pin, _GPIO_MODE_OUT, _GPIO_NOPULL, _GPIO_SPEED_LOW);
	
	backLightOff();
}

void backLightOn() {
	_GPIO_CONFIG(port, pin, _GPIO_MODE_OUT, _GPIO_NOPULL, _GPIO_SPEED_LOW);
	_GPIO_HIGH(port, pin);
}

void backLightOff() {
	_GPIO_LOW(port, pin);
	_GPIO_CONFIG(port, pin, _GPIO_MODE_ANALOG, _GPIO_NOPULL, _GPIO_SPEED_LOW);
}


