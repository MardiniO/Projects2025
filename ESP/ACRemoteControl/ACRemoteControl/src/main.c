# include "freertos/FreeRTOS.h"
# include "freertos/task.h"
# include "driver/gpio.h"
# include "rom/gpio.h"
# include <stdio.h>


# define LEDPIN 13
# define BLINK_PERIOD_MS 1000

void init_hw () {
    gpio_pad_select_gpio ( LEDPIN );
    gpio_set_direction ( LEDPIN , GPIO_MODE_OUTPUT );
}

void app_main () {
    init_hw ();
    while (1) {
        gpio_set_level ( LEDPIN , 1);
        printf (" LED ON \ n ");
        vTaskDelay ( BLINK_PERIOD_MS / portTICK_PERIOD_MS );
        gpio_set_level ( LEDPIN , 0);
        printf (" LED OFF \ n ");
        vTaskDelay ( BLINK_PERIOD_MS / portTICK_PERIOD_MS );
    }
}