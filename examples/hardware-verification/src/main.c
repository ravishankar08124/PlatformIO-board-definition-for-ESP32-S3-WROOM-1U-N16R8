#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_flash.h"
#include "esp_err.h"
#include "esp_heap_caps.h"

void app_main(void)
{
    while (1)
    {
        uint32_t flash_size = 0;

        esp_err_t result = esp_flash_get_size(NULL, &flash_size);

        printf("\n============================\n");
        printf("ESP32-S3-N16R8 HARDWARE TEST\n");
        printf("============================\n");

        /* Flash verification */
        if (result == ESP_OK)
        {
            printf("Flash size     : %lu MB\n",
                   (unsigned long)(flash_size / (1024 * 1024)));
        }
        else
        {
            printf("Flash read failed: %s\n",
                   esp_err_to_name(result));
        }

        /* PSRAM verification */
        size_t total_psram =
            heap_caps_get_total_size(MALLOC_CAP_SPIRAM);

        size_t free_psram =
            heap_caps_get_free_size(MALLOC_CAP_SPIRAM);

        if (total_psram > 0)
        {
            printf("PSRAM detected : YES\n");

            printf("Total PSRAM    : %lu MB\n",
                   (unsigned long)(total_psram / (1024 * 1024)));

            printf("Free PSRAM     : %lu bytes\n",
                   (unsigned long)free_psram);
        }
        else
        {
            printf("PSRAM detected : NO\n");
        }

        printf("============================\n");

        fflush(stdout);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
