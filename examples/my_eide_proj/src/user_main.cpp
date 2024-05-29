#include <user_main.h>
#include <main.h>

#include <FreeRTOS.h>
#include <task.h>

void StartDefaultTask(void const *argument)
{
    (void)argument;

    while (true) {
        HAL_GPIO_TogglePin(Led_GPIO_Port, Led_Pin);
        vTaskDelay(500);
    }

    vTaskDelete(nullptr); // 删除当前线程
}
