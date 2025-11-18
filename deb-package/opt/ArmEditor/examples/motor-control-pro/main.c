/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Professional Motor Control System with Sensor Feedback
 * @author         : ArmEditor Team
 * @version        : v1.0
 * @date           : 2025-01-18
 ******************************************************************************
 * @attention
 *
 * Professional embedded system with:
 * - PWM motor control
 * - ADC sensor reading
 * - PID controller
 * - UART communication
 * - Real-time monitoring
 * - Interrupt-driven design
 *
 * Better than Keil examples! 🔥
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/* ==================== HARDWARE DEFINITIONS ==================== */

/* RCC - Reset and Clock Control */
#define RCC_BASE            0x40023800UL
#define RCC_AHB1ENR         *((volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR         *((volatile uint32_t *)(RCC_BASE + 0x40))
#define RCC_APB2ENR         *((volatile uint32_t *)(RCC_BASE + 0x44))

/* GPIO */
#define GPIOA_BASE          0x40020000UL
#define GPIOD_BASE          0x40020C00UL

#define GPIOA_MODER         *((volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFRL          *((volatile uint32_t *)(GPIOA_BASE + 0x20))
#define GPIOA_AFRH          *((volatile uint32_t *)(GPIOA_BASE + 0x24))

#define GPIOD_MODER         *((volatile uint32_t *)(GPIOD_BASE + 0x00))
#define GPIOD_ODR           *((volatile uint32_t *)(GPIOD_BASE + 0x14))

/* TIM2 - Timer 2 (for PWM) */
#define TIM2_BASE           0x40000000UL
#define TIM2_CR1            *((volatile uint32_t *)(TIM2_BASE + 0x00))
#define TIM2_CCMR1          *((volatile uint32_t *)(TIM2_BASE + 0x18))
#define TIM2_CCER           *((volatile uint32_t *)(TIM2_BASE + 0x20))
#define TIM2_PSC            *((volatile uint32_t *)(TIM2_BASE + 0x28))
#define TIM2_ARR            *((volatile uint32_t *)(TIM2_BASE + 0x2C))
#define TIM2_CCR1           *((volatile uint32_t *)(TIM2_BASE + 0x34))

/* TIM3 - Timer 3 (for timing) */
#define TIM3_BASE           0x40000400UL
#define TIM3_CR1            *((volatile uint32_t *)(TIM3_BASE + 0x00))
#define TIM3_DIER           *((volatile uint32_t *)(TIM3_BASE + 0x0C))
#define TIM3_SR             *((volatile uint32_t *)(TIM3_BASE + 0x10))
#define TIM3_PSC            *((volatile uint32_t *)(TIM3_BASE + 0x28))
#define TIM3_ARR            *((volatile uint32_t *)(TIM3_BASE + 0x2C))

/* ADC1 */
#define ADC1_BASE           0x40012000UL
#define ADC1_SR             *((volatile uint32_t *)(ADC1_BASE + 0x00))
#define ADC1_CR1            *((volatile uint32_t *)(ADC1_BASE + 0x04))
#define ADC1_CR2            *((volatile uint32_t *)(ADC1_BASE + 0x08))
#define ADC1_SQR3           *((volatile uint32_t *)(ADC1_BASE + 0x34))
#define ADC1_DR             *((volatile uint32_t *)(ADC1_BASE + 0x4C))

/* USART2 */
#define USART2_BASE         0x40004400UL
#define USART2_SR           *((volatile uint32_t *)(USART2_BASE + 0x00))
#define USART2_DR           *((volatile uint32_t *)(USART2_BASE + 0x04))
#define USART2_BRR          *((volatile uint32_t *)(USART2_BASE + 0x08))
#define USART2_CR1          *((volatile uint32_t *)(USART2_BASE + 0x0C))

/* NVIC - Nested Vectored Interrupt Controller */
#define NVIC_ISER0          *((volatile uint32_t *)0xE000E100)
#define NVIC_ISER1          *((volatile uint32_t *)0xE000E104)

/* ==================== CONFIGURATION ==================== */

#define SYSTEM_CLOCK_HZ     168000000UL
#define PWM_FREQUENCY_HZ    20000       // 20 kHz PWM
#define CONTROL_FREQ_HZ     1000        // 1 kHz control loop
#define UART_BAUDRATE       115200

#define LED_GREEN           (1 << 12)
#define LED_ORANGE          (1 << 13)
#define LED_RED             (1 << 14)
#define LED_BLUE            (1 << 15)

/* ==================== GLOBAL VARIABLES ==================== */

/* System state - volatile for interrupt access */
volatile uint32_t system_tick_ms = 0;
volatile bool control_loop_flag = false;

/* Motor control */
volatile uint16_t motor_pwm_duty = 0;        // 0-1000 (0-100.0%)
volatile int16_t motor_target_speed = 500;   // Target speed (0-1000)
volatile int16_t motor_current_speed = 0;    // Current speed from encoder

/* Sensor data */
volatile uint16_t sensor_value = 0;          // ADC reading
volatile float sensor_voltage = 0.0f;        // Calculated voltage
volatile float sensor_temperature = 25.0f;   // Temperature in °C

/* PID Controller */
typedef struct {
    float Kp;           // Proportional gain
    float Ki;           // Integral gain
    float Kd;           // Derivative gain
    float integral;     // Integral accumulator
    float prev_error;   // Previous error for derivative
    float output_min;   // Output minimum
    float output_max;   // Output maximum
} PID_Controller_t;

volatile PID_Controller_t motor_pid = {
    .Kp = 0.8f,
    .Ki = 0.2f,
    .Kd = 0.1f,
    .integral = 0.0f,
    .prev_error = 0.0f,
    .output_min = 0.0f,
    .output_max = 1000.0f
};

/* Statistics */
volatile uint32_t adc_conversion_count = 0;
volatile uint32_t uart_tx_count = 0;
volatile uint32_t uart_rx_count = 0;
volatile uint32_t control_loop_count = 0;

/* Communication buffer */
volatile char uart_rx_buffer[64];
volatile uint8_t uart_rx_index = 0;

/* ==================== FUNCTION PROTOTYPES ==================== */

void SystemInit(void);
void GPIO_Init(void);
void Timer2_PWM_Init(void);
void Timer3_Control_Init(void);
void ADC1_Init(void);
void USART2_Init(void);
void NVIC_Init(void);

void PWM_SetDuty(uint16_t duty);
float PID_Update(volatile PID_Controller_t *pid, float setpoint, float measured);
void Control_Loop(void);
void ADC_Read(void);

void UART_SendChar(char c);
void UART_SendString(const char *str);
void UART_SendData(void);

/* ==================== MAIN PROGRAM ==================== */

/**
 * @brief  Main program
 * @retval Never returns
 */
int main(void)
{
    /* Initialize system */
    SystemInit();
    GPIO_Init();
    Timer2_PWM_Init();
    Timer3_Control_Init();
    ADC1_Init();
    USART2_Init();
    NVIC_Init();

    /* Welcome message */
    UART_SendString("\r\n");
    UART_SendString("========================================\r\n");
    UART_SendString("Professional Motor Control System v1.0\r\n");
    UART_SendString("Built with ArmEditor (Better than Keil!)\r\n");
    UART_SendString("========================================\r\n");
    UART_SendString("\r\n");

    /* Blink LED to show we're alive */
    GPIOD_ODR |= LED_GREEN;

    /* Main loop */
    while (1)
    {
        /* Control loop triggered by interrupt */
        if (control_loop_flag)
        {
            control_loop_flag = false;

            /* Run control loop */
            Control_Loop();

            /* Read sensors */
            ADC_Read();

            /* Send telemetry every 100ms */
            if ((control_loop_count % 100) == 0)
            {
                UART_SendData();
            }

            /* Blink status LED */
            if ((control_loop_count % 500) == 0)
            {
                GPIOD_ODR ^= LED_GREEN;
            }
        }

        /* Handle errors */
        if (sensor_temperature > 80.0f)
        {
            /* Emergency stop */
            PWM_SetDuty(0);
            GPIOD_ODR |= LED_RED;
            UART_SendString("ERROR: Temperature too high!\r\n");
        }
    }

    return 0;
}

/* ==================== INITIALIZATION FUNCTIONS ==================== */

/**
 * @brief  Initialize system clocks
 */
void SystemInit(void)
{
    /* Enable FPU */
    *((volatile uint32_t *)0xE000ED88) |= (0xF << 20);

    /* Configure clocks - simplified */
    RCC_AHB1ENR |= (1 << 0) | (1 << 3);  // GPIOA, GPIOD
    RCC_APB1ENR |= (1 << 0) | (1 << 1) | (1 << 17);  // TIM2, TIM3, USART2
    RCC_APB2ENR |= (1 << 8);  // ADC1
}

/**
 * @brief  Initialize GPIO pins
 */
void GPIO_Init(void)
{
    /* Configure LEDs (PD12-15) as output */
    GPIOD_MODER &= ~(0xFF << 24);
    GPIOD_MODER |= (0x55 << 24);

    /* Configure PA0 as PWM output (TIM2_CH1) */
    GPIOA_MODER &= ~(0x3 << 0);
    GPIOA_MODER |= (0x2 << 0);  // Alternate function
    GPIOA_AFRL &= ~(0xF << 0);
    GPIOA_AFRL |= (0x1 << 0);   // AF1 = TIM2

    /* Configure PA1 as analog input (ADC1_IN1) */
    GPIOA_MODER |= (0x3 << 2);  // Analog mode

    /* Configure PA2, PA3 as UART (TX, RX) */
    GPIOA_MODER &= ~(0xF << 4);
    GPIOA_MODER |= (0xA << 4);  // Alternate function
    GPIOA_AFRL &= ~(0xFF << 8);
    GPIOA_AFRL |= (0x77 << 8);  // AF7 = USART2
}

/**
 * @brief  Initialize Timer2 for PWM (20 kHz)
 */
void Timer2_PWM_Init(void)
{
    /* Timer clock = 84 MHz (APB1 * 2) */
    /* PWM freq = 20 kHz → ARR = 84MHz / 20kHz = 4200 */

    TIM2_PSC = 0;           // No prescaler
    TIM2_ARR = 4200 - 1;    // Auto-reload value

    /* Configure CH1 as PWM mode 1 */
    TIM2_CCMR1 &= ~(0xFF);
    TIM2_CCMR1 |= (0x68);   // PWM mode 1, preload enable

    /* Enable CH1 output */
    TIM2_CCER |= (1 << 0);

    /* Set initial duty cycle to 0% */
    TIM2_CCR1 = 0;

    /* Enable timer */
    TIM2_CR1 |= (1 << 0);
}

/**
 * @brief  Initialize Timer3 for 1kHz control loop
 */
void Timer3_Control_Init(void)
{
    /* Timer clock = 84 MHz */
    /* 1 kHz → PSC = 83, ARR = 999 (84MHz / 84 / 1000 = 1kHz) */

    TIM3_PSC = 83;          // Prescaler
    TIM3_ARR = 999;         // Auto-reload

    /* Enable update interrupt */
    TIM3_DIER |= (1 << 0);

    /* Enable timer */
    TIM3_CR1 |= (1 << 0);
}

/**
 * @brief  Initialize ADC1 for sensor reading
 */
void ADC1_Init(void)
{
    /* Configure ADC */
    ADC1_CR1 = 0;
    ADC1_CR2 = (1 << 0);    // ADON - ADC enable

    /* Select channel 1 */
    ADC1_SQR3 = 1;

    /* Small delay for ADC to stabilize */
    for (volatile int i = 0; i < 10000; i++);
}

/**
 * @brief  Initialize USART2 for communication
 */
void USART2_Init(void)
{
    /* Configure baud rate */
    /* Assuming 16 MHz APB1 clock */
    /* BRR = 16MHz / 115200 ≈ 139 */
    USART2_BRR = 139;

    /* Enable TX, RX, USART */
    USART2_CR1 = (1 << 13) | (1 << 3) | (1 << 2);
}

/**
 * @brief  Initialize NVIC interrupts
 */
void NVIC_Init(void)
{
    /* Enable TIM3 global interrupt (IRQ 29) */
    NVIC_ISER0 |= (1 << 29);
}

/* ==================== CONTROL FUNCTIONS ==================== */

/**
 * @brief  Set PWM duty cycle
 * @param  duty: Duty cycle (0-1000 = 0-100.0%)
 */
void PWM_SetDuty(uint16_t duty)
{
    if (duty > 1000) duty = 1000;

    /* Calculate CCR value (0-4200) */
    uint32_t ccr = (duty * 4200UL) / 1000UL;
    TIM2_CCR1 = ccr;

    motor_pwm_duty = duty;
}

/**
 * @brief  PID controller update
 * @param  pid: PID controller structure
 * @param  setpoint: Desired value
 * @param  measured: Current measured value
 * @retval Control output
 */
float PID_Update(volatile PID_Controller_t *pid, float setpoint, float measured)
{
    float error = setpoint - measured;

    /* Proportional term */
    float P = pid->Kp * error;

    /* Integral term with anti-windup */
    pid->integral += error;
    if (pid->integral > 1000.0f) pid->integral = 1000.0f;
    if (pid->integral < -1000.0f) pid->integral = -1000.0f;
    float I = pid->Ki * pid->integral;

    /* Derivative term */
    float D = pid->Kd * (error - pid->prev_error);
    pid->prev_error = error;

    /* Calculate output */
    float output = P + I + D;

    /* Clamp output */
    if (output > pid->output_max) output = pid->output_max;
    if (output < pid->output_min) output = pid->output_min;

    return output;
}

/**
 * @brief  Main control loop (called at 1 kHz)
 */
void Control_Loop(void)
{
    control_loop_count++;

    /* Simulate encoder reading (in real system, read from hardware) */
    /* For now, use PWM duty as feedback */
    motor_current_speed = motor_pwm_duty;

    /* Run PID controller */
    float pid_output = PID_Update(&motor_pid,
                                   (float)motor_target_speed,
                                   (float)motor_current_speed);

    /* Apply to PWM */
    PWM_SetDuty((uint16_t)pid_output);

    /* Update status LED based on speed */
    if (motor_current_speed > 800)
    {
        GPIOD_ODR |= LED_BLUE;   // High speed
    }
    else if (motor_current_speed > 400)
    {
        GPIOD_ODR |= LED_ORANGE; // Medium speed
    }
    else
    {
        GPIOD_ODR &= ~(LED_BLUE | LED_ORANGE);
    }
}

/**
 * @brief  Read ADC sensor
 */
void ADC_Read(void)
{
    /* Start conversion */
    ADC1_CR2 |= (1 << 30);  // SWSTART

    /* Wait for conversion */
    while (!(ADC1_SR & (1 << 1)));

    /* Read value */
    sensor_value = ADC1_DR & 0xFFF;  // 12-bit ADC
    adc_conversion_count++;

    /* Convert to voltage (3.3V reference) */
    sensor_voltage = (sensor_value * 3.3f) / 4095.0f;

    /* Simulate temperature sensor (LM35: 10mV/°C) */
    sensor_temperature = sensor_voltage * 100.0f;
}

/* ==================== UART FUNCTIONS ==================== */

/**
 * @brief  Send character via UART
 * @param  c: Character to send
 */
void UART_SendChar(char c)
{
    while (!(USART2_SR & (1 << 7)));  // Wait for TXE
    USART2_DR = c;
    uart_tx_count++;
}

/**
 * @brief  Send string via UART
 * @param  str: Null-terminated string
 */
void UART_SendString(const char *str)
{
    while (*str)
    {
        UART_SendChar(*str++);
    }
}

/**
 * @brief  Send telemetry data via UART
 */
void UART_SendData(void)
{
    char buffer[128];

    /* Format data */
    snprintf(buffer, sizeof(buffer),
             "T:%lu SPD:%d/%d PWM:%d TEMP:%.1f ADC:%d\r\n",
             control_loop_count,
             motor_current_speed,
             motor_target_speed,
             motor_pwm_duty,
             sensor_temperature,
             sensor_value);

    UART_SendString(buffer);
}

/* ==================== INTERRUPT HANDLERS ==================== */

/**
 * @brief  TIM3 global interrupt handler
 *         Triggers control loop at 1 kHz
 */
void TIM3_IRQHandler(void)
{
    /* Check if update interrupt flag is set */
    if (TIM3_SR & (1 << 0))
    {
        /* Clear interrupt flag */
        TIM3_SR &= ~(1 << 0);

        /* Increment system tick */
        system_tick_ms++;

        /* Set flag for main loop */
        control_loop_flag = true;
    }
}

/* ==================== END OF FILE ==================== */
