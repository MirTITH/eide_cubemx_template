#include <main.h>

#ifdef __cplusplus
extern "C" {
#endif

// 在 .cpp 文件中，需要 extern C 声明，才能覆盖 .c 中的 weak 函数
// void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif

// void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
// {
//     // Do something
// }
