#include"uart.h"
#include"stdint.h"
#include"main.h"

UART_HandleTypeDef huart3;

void uart_init (void)
{
    huart3.Instance = USART3;
    huart3.Init.BaudRate = 115200;//Le baudrate est à modifier selon le projet 
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart3) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_NVIC_SetPriority(USART3_4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_4_IRQn);
}

//Mode sans interruption 
void uart_send(UART_HandleTypeDef *huart, char data[], uint16_t size)//Envoie d'un caractère sur le terminal en précisant l'UART, 
                                                                    //la data et sa taille
{
    HAL_UART_Transmit(huart,(uint8_t *) data, size, HAL_MAX_DELAY);//Fonctions permettant l'envois avec l'ajout d'un parametre 
                                                                  //qui définit le temps max accordé pour l'envoie.   
}

void  uart_receive(UART_HandleTypeDef *huart, char Data[], uint16_t size)
{
    HAL_UART_Receive(huart, (uint8_t *) Data, size, HAL_MAX_DELAY);
}

//Mode interrupt
void uart_send_IT(UART_HandleTypeDef *huart, char data[], uint16_t size)
{
    HAL_UART_Transmit_IT(huart, (uint8_t *) data, size);   
}
void  uart_receive_IT(UART_HandleTypeDef *huart, char Data[], uint16_t size)
{
    HAL_UART_Receive_IT(huart, (uint8_t *) Data, size);
}



