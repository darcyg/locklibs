#include "backlightx.h"

static stBackLight_t be = {0, 0};

void backLightInit(_U8 port, _U8 pin) {
	be.port = port;
	be.pin = pin;
	
	backLightOff();
}

void backLightOn() {
	_GPIO_CONFIG(be.port, be.pin, _GPIO_MODE_OUT_PP, _GPIO_NOPULL, _GPIO_SPEED_LOW);
	_GPIO_HIGH(be.port, be.pin);
}

void backLightOff() {
	_GPIO_LOW(be.port, be.pin);
	_GPIO_CONFIG(be.port, be.pin, _GPIO_MODE_ANALOG, _GPIO_NOPULL, _GPIO_SPEED_LOW);
}


