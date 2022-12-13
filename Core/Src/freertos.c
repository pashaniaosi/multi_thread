/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "tim.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define STATIC
#define STACK_SIZE (configMINIMAL_STACK_SIZE * 4)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
static TaskHandle_t xSensor1TaskHandle;
#ifdef STATIC
StaticTask_t xSensor1TCB;
StackType_t xStack1[STACK_SIZE];
#endif

static TaskHandle_t xSensor2TaskHandle;
#ifdef STATIC
StaticTask_t xSensor2TCB;
StackType_t xStack2[STACK_SIZE];
#endif

static TaskHandle_t xSensor3TaskHandle;
#ifdef STATIC
StaticTask_t xSensor3TCB;
StackType_t xStack3[STACK_SIZE];
#endif

// extern volatile uint32_t CPU_RunTime;
static TaskHandle_t xCPUTaskHandle;
#ifdef STATIC
StaticTask_t xCPUTCB;
StackType_t xCPUStack[STACK_SIZE];
#endif
/* USER CODE END Variables */
/* Definitions for init */
osThreadId_t initHandle;
const osThreadAttr_t init_attributes = {
  .name = "init",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
static void vSensor1TaskEntry(void *parameter);
static void vSensor2TaskEntry(void *parameter);
static void vSensor3TaskEntry(void *parameter);
static void vCPUTaskEntry(void *parameter);
/* USER CODE END FunctionPrototypes */

void INIT(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{
  CPU_RunTime = 0UL;
}

__weak unsigned long getRunTimeCounterValue(void)
{
  return CPU_RunTime;
}
/* USER CODE END 1 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of init */
  // initHandle = osThreadNew(INIT, NULL, &init_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
#ifdef STATIC
  xSensor1TaskHandle = xTaskCreateStatic(vSensor1TaskEntry, "sensor1", STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, xStack1, &xSensor1TCB);
  xSensor2TaskHandle = xTaskCreateStatic(vSensor2TaskEntry, "sensor2", STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, xStack2, &xSensor2TCB);
  xSensor3TaskHandle = xTaskCreateStatic(vSensor3TaskEntry, "sensor3", STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, xStack3, &xSensor3TCB);
  xCPUTaskHandle = xTaskCreateStatic(vCPUTaskEntry, "cpuinfo", STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, xCPUStack, &xCPUTCB);
#endif

#ifdef DYNAMIC
  BaseType_t xReturn;
  xReturn = xTaskCreate(vSensor1TaskEntry, "sensor1", configMINIMAL_STACK_SIZE * 4, NULL, tskIDLE_PRIORITY + 1, &xSensor1TaskHandle);
  if (xReturn != pdPASS) {
    printf("Error creating task for sensor1.\r\n");
  }
  xReturn = xTaskCreate(vSensor2TaskEntry, "sensor2", configMINIMAL_STACK_SIZE * 4, NULL, tskIDLE_PRIORITY + 1, &xSensor2TaskHandle);
  if (xReturn != pdPASS) {
    printf("Error creating task for sensor2.\r\n");
  }
  xReturn = xTaskCreate(vSensor3TaskEntry, "sensor3", configMINIMAL_STACK_SIZE * 4, NULL, tskIDLE_PRIORITY + 1, &xSensor3TaskHandle);
  if (xReturn != pdPASS) {
    printf("Error creating task for sensor3.\r\n");
  }
#endif

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_INIT */
/**
  * @brief  Function implementing the init thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_INIT */
__weak void INIT(void *argument)
{
  /* USER CODE BEGIN INIT */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1000);
    printf("init\r\n");
  }
  /* USER CODE END INIT */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
static void vSensor1TaskEntry(void *parameter) {
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 1000;
  xLastWakeTime = xTaskGetTickCount();
  for (;;) {
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    __NOP();
    printf("sensor1.\r\n");
  }
}

static void vSensor2TaskEntry(void *parameter) {
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 2000;
  xLastWakeTime = xTaskGetTickCount();
  for (;;) {
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    __NOP();
    printf("sensor2.\r\n");
  }
}

static void vSensor3TaskEntry(void *parameter) {
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 4000;
  xLastWakeTime = xTaskGetTickCount();
  for (;;) {
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    __NOP();
    printf("sensor3.\r\n");
  }
}

static void vCPUTaskEntry(void *parameter)
{
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 8000;
  xLastWakeTime = xTaskGetTickCount();
  uint8_t *cpu_runinfo = (uint8_t *)pvPortMalloc(400 * sizeof(uint8_t));
  for (;;) {
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    memset(cpu_runinfo, 0, 400);
    vTaskList((char *) cpu_runinfo);
    printf("--------------------------------------------------\r\n");
    printf("Name                  Status  Prio   Stack     Seq\r\n");
    printf("%s", cpu_runinfo);
    printf("--------------------------------------------------\r\n");

    memset(cpu_runinfo, 0, 400);
    vTaskGetRunTimeStats((char *) cpu_runinfo);
    printf("Name                  Count          Usage\r\n");
    printf("%s", cpu_runinfo);
    printf("--------------------------------------------------\r\n");
  }
}
/* USER CODE END Application */

