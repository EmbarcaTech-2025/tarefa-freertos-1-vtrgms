#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"

#define GREEN_LED_PIN 11
#define BLUE_LED_PIN 12
#define RED_LED_PIN 13
#define BUZZER_PIN 21
#define BUZZER_FREQUENCY 100
#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6

// Handles das tarefas
TaskHandle_t led_task_handle = NULL;
TaskHandle_t buzzer_task_handle = NULL;

void cycle_led(void *params) {
    gpio_init(RED_LED_PIN);
    gpio_init(BLUE_LED_PIN);
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_set_dir(BLUE_LED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);

    while (1) {
        gpio_put(RED_LED_PIN, 1);
        gpio_put(GREEN_LED_PIN, 0);
        gpio_put(BLUE_LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_put(RED_LED_PIN, 0);
        gpio_put(GREEN_LED_PIN, 1);
        gpio_put(BLUE_LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_put(RED_LED_PIN, 0);
        gpio_put(GREEN_LED_PIN, 0);
        gpio_put(BLUE_LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void beep_buzzer(void *params){
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * 4096));
    pwm_init(slice_num, &config, true);

    while (1) {
        pwm_set_gpio_level(BUZZER_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(5000));
        pwm_set_gpio_level(BUZZER_PIN, 2048);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void button_monitor(void *params) {
    gpio_init(BUTTON_A_PIN);
    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);
    gpio_pull_up(BUTTON_B_PIN);

    bool led_suspended = false;
    bool buzzer_suspended = false;

    while (1) {
        if (!gpio_get(BUTTON_A_PIN)) {
            if (led_suspended) {
                vTaskResume(led_task_handle);
                led_suspended = false;
            } else {
                vTaskSuspend(led_task_handle);
                led_suspended = true;
            }
            vTaskDelay(pdMS_TO_TICKS(300)); // debounce
        }
        if (!gpio_get(BUTTON_B_PIN)) {
            if (buzzer_suspended) {
                vTaskResume(buzzer_task_handle);
                buzzer_suspended = false;
            } else {
                vTaskSuspend(buzzer_task_handle);
                buzzer_suspended = true;
            }
            vTaskDelay(pdMS_TO_TICKS(300)); // debounce
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

int main() {
    stdio_init_all();

    xTaskCreate(cycle_led, "Blink LED", 256, NULL, 1, &led_task_handle);
    xTaskCreate(beep_buzzer, "Beep Buzzer", 256, NULL, 1, &buzzer_task_handle);
    xTaskCreate(button_monitor, "Button Monitor", 256, NULL, 2, NULL);

    vTaskStartScheduler();
    while (true) {}
}
