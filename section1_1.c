#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "stdio.h"
#include "inttypes.h"

/* SYMBOLIC CONSTANTS */

#define UP     1U
#define DOWN   2U
#define LEFT   4U
#define RIGHT  8U
#define CENTRE 16U


void initJoystick(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE); // Enable clock for GPIO Port A
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE); // Enable clock for GPIO Port B
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE); // Enable clock for GPIO Port C

	// PC0 Input
	GPIO_InitTypeDef GPIO_InitStructAll; // Define typedef struct for setting pins
	GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct
	GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_IN; // Set as input
	GPIO_InitStructAll.GPIO_PuPd = GPIO_PuPd_DOWN; // Set as pull down
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_0; // Set so the configuration is on pin C0
	GPIO_Init(GPIOC, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen

	// PA4 Input
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_4; // Set so the configuration is on pin A4
	GPIO_Init(GPIOA, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen

	// PB5 Input
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_5; // Set so the configuration is on pin B5
	GPIO_Init(GPIOB, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen

	// PC1 Input
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_1; // Set so the configuration is on pin A4
	GPIO_Init(GPIOC, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen

	// PB0 Input
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_0; // Set so the configuration is on pin A4
	GPIO_Init(GPIOB, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen
}


uint8_t readJoystick(void)
{
	uint8_t up     = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);
	uint8_t down   = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0);
	uint8_t left   = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1);
	uint8_t right  = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0);
	uint8_t centre = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5);

	uint8_t joystickBits = 0U;

	joystickBits |= up     << 0U;
	joystickBits |= down   << 1U;
	joystickBits |= left   << 2U;
	joystickBits |= right  << 3U;
	joystickBits |= centre << 4U;

	return joystickBits;
}


int main(void)
{
	uart_init( 9600 ); // Initialize USB serial at 9600 baud
	initJoystick();
	initLed();
	//initInterrupts();
	//initStopwatch(&stopwatch);
	//initTimer();

	uint8_t joystickState;

	while(1)
	{
		uint8_t newJoystickState = readJoystick();

		if (newJoystickState != joystickState)
		{
			joystickState = newJoystickState;
			printf("Joystick: %d\n", joystickState);
			readStopwatchInputs(&stopwatch, joystickState);
		}

		setLed(joystickState);
	}
}


int main(void)
{
	uart_init( 9600 ); // Initialize USB serial at 9600 baud
	initJoystick();
	initLed();

	uint8_t joystickState;

	while(1)
	{
		uint8_t newJoystickState = readJoystick();

		if (newJoystickState != joystickState)
		{
			joystickState = newJoystickState;
			printf("Joystick: %d\n", joystickState);
		}

		setLed(joystickState);
	}
}


