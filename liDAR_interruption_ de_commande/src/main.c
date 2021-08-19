/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "uart.h"
#include "lidar_cmd.h"
#include "lidar_protoc.h"
#include"stdio.h"
#include "stdlib.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void uart_init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
 uint8_t e[2];//Définition de la taille de notre mémoire pour la réponse (2 octets)
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  uart_init();
  /* USER CODE BEGIN 2 */
  
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  rplidar_cmd_packet_t env; //Definition d'un paquet d'envoi
  /*rplidar_payload_express_scan_t payload;*///Définition d'un payload
  /*uint8_t checksum;*/ //Definition d'un checksum

  /*Toute les commande disponible*/

  /*Commande sans réponse*/
  //Command STOP pour mettre fin a une requete à réponse multiple
  /*env.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env.cmd_flag=RPLIDAR_CMD_STOP;*/

  //Command RESET pour revenir à l'état de repos et pouvoir balayer l'environnement
  /*env.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env.cmd_flag=RPLIDAR_CMD_RESET;*/

  /*commande avec unique réponse*/
  //Envois d'une commande pour avoir les infos du Lidar (modele, firmware, numero de série, numero de la version de l'HW)
  /*env.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env.cmd_flag= RPLIDAR_CMD_GET_DEVICE_INFO;*/

  //Envois d'une commande pour avoir la santé du Lidar, par exemple s'il plante, cela permet d'avoir une indication sur la nature du problème
  env.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env.cmd_flag=RPLIDAR_CMD_GET_DEVICE_HEALTH;

  //Envois d'une commande pour avoir la durée d'un acquisition du Lidar + d'en déduire sa vitesse de rotation du moteur
  /*env.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env.cmd_flag=RPLIDAR_CMD_GET_SAMPLERATE;*/
  
  /*Commande de balayage avec plusieurs réponses du LiDAR*/
  //Envois d'une commande pour forcer un balayage (utile pour debugger)
  /*env.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env.cmd_flag=RPLIDAR_CMD_FORCE_SCAN;*/

  //Envoie d'une commande scan pour avoir la map en mode scan "normal", attention si le lidar est en "protection stop state" faire un "RESET" sinon le lidar n'enverra rien.
  /*env.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env.cmd_flag=RPLIDAR_CMD_SCAN;*/

  /*Commande avec plusieurs réponse du LiDAR et nécessitant un payload*/
  /*//Envois d'une commande de balayage express "normal" ou "Legacy" pour obtenir plus de point et avec une vitesse de moteur supérieur
  //Envois d'un premier paquet pour la commande
  env.syncByte=RPLIDAR_CMD_SYNC_BYTE;
  env.cmd_flag=RPLIDAR_CMD_EXPRESS_SCAN;
  env.size=0x05;
  //envoi d'un second paquet pour le payload
  payload.working_mode=RPLIDAR_EXPRESS_SCAN_MODE_NORMAL;
  payload.working_flags=0x0000;
  payload.param=0x0000;
  //envois du checksum
  checksum=0x22;*/

  uart_send(&huart3,(uint8_t *) &env, sizeof(env));
  uart_receive_IT(&huart3,(uint8_t *) e, sizeof(e));
  //Envoi d'un payload (si besoin)
  /*uart_send(&huart3,(uint8_t *) &payload, sizeof(payload));*/
  //Envoi d'un checksum (si besoin)
  //uart_send(&huart3,(uint8_t *) &checksum, sizeof(checksum));

  while (1)
  {

    /* USER CODE END WHILE */
    
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI48;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  rplidar_cmd_packet_t env;
  /*Si on détecte les deux start flag caractéristiques d'une réponse liDAR sur l'UART3*/
  if ((huart->Instance==USART3)&&(e[0]==RPLIDAR_ANS_SYNC_BYTE1)&&(e[1]==RPLIDAR_ANS_SYNC_BYTE2))
  {
    env.syncByte=RPLIDAR_CMD_SYNC_BYTE;
    env.cmd_flag=RPLIDAR_CMD_GET_DEVICE_INFO;//on envoie la commande pour avoir les infos du liDAR.
    uart_send(&huart3,(uint8_t *) &env, sizeof(env));
  }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
