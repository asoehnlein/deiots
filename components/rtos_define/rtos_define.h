#define MYAPP_RTOS_TASK_STACK_SIZE_LARGE (8192)

/**********
 * RTOS vTaskDelay() parameter
 */

#define RTOS_DELAY_0             (0)
#define RTOS_DELAY_1MILLISEC     (   1 / portTICK_PERIOD_MS)
#define RTOS_DELAY_5MILLISEC     (   5 / portTICK_PERIOD_MS)
#define RTOS_DELAY_10MILLISEC    (  10 / portTICK_PERIOD_MS)
#define RTOS_DELAY_25MILLISEC    (  25 / portTICK_PERIOD_MS)
#define RTOS_DELAY_50MILLISEC    (  50 / portTICK_PERIOD_MS)
#define RTOS_DELAY_75MILLISEC    (  50 / portTICK_PERIOD_MS)
#define RTOS_DELAY_100MILLISEC   ( 100 / portTICK_PERIOD_MS)
#define RTOS_DELAY_125MILLISEC   ( 125 / portTICK_PERIOD_MS)
#define RTOS_DELAY_150MILLISEC   ( 150 / portTICK_PERIOD_MS)
#define RTOS_DELAY_200MILLISEC   ( 200 / portTICK_PERIOD_MS)
#define RTOS_DELAY_250MILLISEC   ( 250 / portTICK_PERIOD_MS)
#define RTOS_DELAY_500MILLISEC   ( 500 / portTICK_PERIOD_MS)
#define RTOS_DELAY_1SEC          ( 1 * 1000 / portTICK_PERIOD_MS)
#define RTOS_DELAY_2SEC          ( 2 * 1000 / portTICK_PERIOD_MS)
#define RTOS_DELAY_3SEC          ( 3 * 1000 / portTICK_PERIOD_MS)
#define RTOS_DELAY_5SEC          ( 5 * 1000 / portTICK_PERIOD_MS)
#define RTOS_DELAY_10SEC         (10 * 1000 / portTICK_PERIOD_MS)
#define RTOS_DELAY_15SEC         (15 * 1000 / portTICK_PERIOD_MS)
#define RTOS_DELAY_30SEC         (30 * 1000 / portTICK_PERIOD_MS)
#define RTOS_DELAY_1MINUTE       ( 1 * 60 * 1000 / portTICK_PERIOD_MS)
#define RTOS_DELAY_5MINUTES      ( 5 * 60 * 1000 / portTICK_PERIOD_MS)
#define RTOS_DELAY_15MINUTES     (15 * 60 * 1000 / portTICK_PERIOD_MS)
#define RTOS_DELAY_MAX           (portMAX_DELAY)

// Use this priority to create all your RTOS tasks so all tasks are ginve equal cputime using the Round Robin method
//      @doc https://www.freertos.org/RTOS-task-priority.html

#define RTOS_TASK_PRIORITY_NORMAL (5)
