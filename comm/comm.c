#include "comm.h"
#include "string.h"

extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;

__align(8) Data485 Buffer485;

logic transmitcomplete;

extern logic receiveflag;

void UART_Start(UART_HandleTypeDef *huart)
{
		__HAL_UART_CLEAR_IDLEFLAG(&huart2); 
		__HAL_UART_ENABLE_IT(&huart2,UART_IT_IDLE); 																							//UART IDLE INTERRUPT AKTIF EDILDI.
		HAL_UART_Receive_DMA(&huart2, (uint8_t*)Buffer485.Received, UART_BUFFER_SIZE); //DMA Receive Bufferinda verilen boyut kadar yer aciliyor.
}																																													  //ve verilen adrese datalar kaydediliyor.
void USER_UART_IRQHandler(UART_HandleTypeDef *huart)
{
		if(__HAL_UART_GET_FLAG(&huart2, UART_FLAG_IDLE))   //IDLE Interruptinin set olmasi isteniyor.
		{
		  	HAL_UART_DMAStop(&huart2);	
			__HAL_UART_CLEAR_IDLEFLAG(&huart2);	
			__HAL_UART_DISABLE_IT(&huart2, UART_IT_IDLE);
			Buffer485.ReceivedLengthBuffer = 0; 
			Buffer485.ReceivedLengthBuffer  =  UART_BUFFER_SIZE - hdma_usart2_rx.Instance->CNDTR; 
			receiveflag = True;
			hdma_usart2_rx.Instance->CNDTR = 0;
		}
}

void hwl_DisableITSources(void)
{
   __HAL_UART_DISABLE_IT(&huart2, UART_IT_PE);
   __HAL_UART_DISABLE_IT(&huart2, UART_IT_TXE);
   __HAL_UART_DISABLE_IT(&huart2, UART_IT_TC);
   __HAL_UART_DISABLE_IT(&huart2, UART_IT_RXNE);
   __HAL_UART_DISABLE_IT(&huart2, UART_IT_IDLE);
}

void AllClearFlags(void)
{
	  __HAL_UART_DISABLE_IT(&huart2, UART_IT_IDLE);
	
		__HAL_UART_CLEAR_FEFLAG(&huart2);
		__HAL_UART_CLEAR_OREFLAG(&huart2);
		__HAL_UART_CLEAR_PEFLAG(&huart2);
		__HAL_UART_CLEAR_NEFLAG(&huart2);
}
void TransmitDataBuffer(uint8_t *data,uint8_t size)
{
	HAL_UART_Transmit_IT(&huart2,data,size);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart2.Instance == USART2)
	{
		transmitcomplete = True;
	}
}

//uint8_t x = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if( huart->Instance == USART2 )
  {
		 //Rxcompleteflag = 1;
	}
}
