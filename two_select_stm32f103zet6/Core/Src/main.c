/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <rtthread.h>

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

/* USER CODE BEGIN PV */
extern float theta_err,rho_err;
extern uint8_t buffer_1_i,buffer_1_f,buffer_2_i,buffer_2_f,buffer_3;


uint8_t cmd;
uint8_t TL=2,TR=2;

int Target_Velocity_L,Target_Velocity_R
    ,Reality_Velocity_L,Reality_Velocity_R;   
int Target_Position_L,Target_Position_R
    ,Reality_Position_L,Reality_Position_R; 

int i;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//void base1(void)
//{
//	
//	
//			control_x(0);
//	control_y(0);	
//		
//}	
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
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */
		OLED_Init();
//	HAL_UART_Receive_IT(&huart1,(void *)&cmd, 1); 	
 
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {	
	
//		Target_Velocity_L=Rpm_Encoder_Cnt(3,11,9.6,100);  
//		Target_Velocity_R=Rpm_Encoder_Cnt(3,11,9.6,100); 
			
//		speed = Moto_Speed(Reality_Velocity[1],500,30,100);

//	
		printf("串口打印测试\n");
//		HAL_Delay(1000);
//		Target_Position_L=Num_Encoder_Cnt(2,11,9.6);  
//		Target_Position_R=Num_Encoder_Cnt(2,11,9.6);
//		OLED_ShowNum(3,1,speed_L,6);
//		
//		OLED_ShowNum(4,1,Reality_Position_R,6);
//		OLED_ShowNum(4,8,Reality_Velocity_R,6);
//		Data_send(Target_Position_L,Reality_Position_L,0,0);
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */




//串口接收中断函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint16_t Serial_RxData;
  if(huart->Instance==USART1){
		Serial_RxData=cmd;	
//		openmv_receive(Serial_RxData);		
	}	
	HAL_UART_Receive_IT(&huart1,(void *)&cmd, 1);  
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    int Moto_L = 0 , Moto_R = 0; 
    if (htim->Instance == TIM2)
    {
//			
      	Reality_Velocity_L = Read_Encoder(5); 
				Reality_Velocity_R = Read_Encoder(4);	
	      Reality_Position_L += Reality_Velocity_L;                   /* 实际位置脉冲�? */
        Reality_Position_R += Reality_Velocity_R;  

			
				Moto_L = Position_PID(Reality_Position_L,Target_Position_L);  /* 位置式位置控�? */                           /* 位置环输出限�? */
				Moto_R = Position_PID(Reality_Position_R,Target_Position_R);  /* 位置式位置控�? */   
				set_motor(Moto_L ,Moto_R );  	

////			/* 实际位置脉冲�? */
//        Moto_L = Position_PID(Reality_Position_R,Target_Position_L);  /* 位置式位置控�? */        
//        Moto_L = limit(Moto_L,Target_Velocity_L);                    /* 位置环输出限�? */
//      
//        Moto_R = Position_PID(Reality_Position_R ,Target_Position_R);  /* 位置式位置控�? */        
//        Moto_R = limit(Moto_R,Target_Velocity_R);                    /* 位置环输出限�? */
////        Moto_L = Incremental_PID(Reality_Velocity_L,Moto_L);      /* 增量式�?�度控制 */
////			
////        Moto_R = Incremental_PID(Reality_Velocity_R,Moto_R);      /* 增量式�?�度控制 */
//        set_motor(Moto_L,Moto_R);                                      /* 赋�?? */
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
