/**
******************************************************************************
* @file    INTERNAL_ADC.h
* @author  Majid Derhambakhsh
* @version V0.2.0
* @date    11-17-2018
* @brief
* @support Majid.do16@gmail.com
******************************************************************************
* @description  Enable internal Attiny ADC
*   
* @attention    This file is for "AVR GCC" & "Codevision Avr" 
******************************************************************************
*/

#ifndef __INTERNAL_ADC_H_
#define __INTERNAL_ADC_H_

/************************ Compiler & Library Controll ************************/ 

/*----------------------------------------------------------*/

#ifdef __CODEVISIONAVR__  /* Chech compiler */

 #include <io.h>            /* Import AVR IO library */

/*----------------------------------------------------------*/

#elif defined(__GNUC__)   /* Chech compiler */

 #include <avr/io.h>        /* Import AVR IO library */
 #include <avr/interrupt.h> /* Import interrupt library */
 
/*----------------------------------------------------------*/

#else                     /* Compiler not found */

#error Compiler not supported  /* Send error */

#endif

/*----------------------------------------------------------*/

#include <stdint.h> /* Import standard integer library */

/*************************************** Start Defines ***************************************/

/*--------------------- Define For ADC Register ---------------------*/   /* Default Set */

 #define ADC_Multiplexer_Selection_Register  ADMUX   /* Define for adc register */
 #define ADC_Control_And_Status_Register_A   ADCSRA  /* Define for adc register */
 #define ADC_Control_And_Status_Register_B   ADCSRB  /* Define for adc register */
 #define ADC_DATA_REGISTER                   ADCW
                                                     
/*------------------------ Inline function --------------------------*/   /* Default Set */

 #define START_ADC_CONVERSION()  (ADCSRA |= 0x40) /* for start conversion */

/*-------------------- Define For Assembly Code ---------------------*/   /* Default Set */

#ifdef __CODEVISIONAVR__  /* Chech compiler */

 #define ENABLE_GLOBAL_INTERRUPT   #asm("sei") /* Define for global interrupt enable */
 #define DISABLE_GLOBAL_INTERRUPT  #asm("cli") /* Define for global interrupt disable */

/*-------------------------------------------------------*/

#elif defined(__GNUC__)   /* Chech compiler */

 #define ENABLE_GLOBAL_INTERRUPT   __asm__ ("sei"); /* Define for global interrupt enable */
 #define DISABLE_GLOBAL_INTERRUPT  __asm__ ("cli"); /* Define for global interrupt disable */

#endif

/*----------------------------- Public ------------------------------*/   /* Default Set */
 
#ifdef __CODEVISIONAVR__  /* Chech compiler */

 #define INTERRUPT(vector)  interrupt [vector] void adc_isr(void)
 #define ADC_CONVERSION_COMPLETE_VECTOR  ADC_INT /* ADC conversion complete interrupt vector number */

/*-------------------------------------------------------*/

#elif defined(__GNUC__)   /* Chech compiler */

 #define INTERRUPT(vector)  ISR(vector)
 #define ADC_CONVERSION_COMPLETE_VECTOR  ADC_vect /* ADC conversion complete interrupt vector number */

#endif

/*-------------------------------------------------------*/

 #define AnalogToDigital  Analog_To_Digital_Initialize /* Select func */
 #define ENUM_U8_T(ENUM_NAME)    Enum_##ENUM_NAME;  typedef uint8_t ENUM_NAME /* Config enum size */

/**************************************** End Defines ****************************************/

/*************************************** Create Enums ****************************************/

typedef enum /* Enum for config input ADC channel */
{

 Channel0 = 0x00, /* ADC channel 0 */
 Channel1 = 0x01, /* ADC channel 1 */
 Channel2 = 0x02, /* ADC channel 2 */
 Channel3 = 0x03, /* ADC channel 3 */
 
}ENUM_U8_T( AdcChannel_t );

typedef enum /* Enum for adc adjust result */
{

 Left = 0x20, /* Left result */
 Right = 0x00, /* Right result */

}ENUM_U8_T( AdjustResult_t );

typedef enum /* Enum for config adc voltage refrence */
{

 VccRefrence = 0x00, /* Vcc refrence */
 InternalRefrence = 0x40, /* Internal refrence */
 
}ENUM_U8_T( VoltageRefrence_t );

typedef enum /* Enum for config adc trigger source */
{

 FreeRunning        = 0x00, /* Free running mode */
 AnalogComparator   = 0x01, /* Analog comparator */
 ExternalInterrupt0 = 0x02, /* External interrupt 0 */
 TimerCompareMatchA = 0x03, /* Timer compare match a */ 
 TimerOverflow      = 0x04, /* Timer overflow */
 TimerCompareMatchB = 0x05, /* Timer compare match b */
 PinChangeInterrupt = 0x06, /* Pin change interrupt */ 

}ENUM_U8_T( TriggerSource_t );

typedef enum /* Enum for set status */
{

 False = 0, /* False status */
 True = 1, /* True status */

}ENUM_U8_T( Status_t );

/************************************* Function Pointer **************************************/

typedef void( *AdcMode_t )( void ); /* Function pointer for select adc initialize */

/************************************** Create Structs ***************************************/

extern struct AdcModeInit /* Struct for config ADC mode */
{

 AdcMode_t Mode; /* Select adc mode */
 
}InternalAdc;

extern struct AnalogToDigitalInitialize /* Struct for config analog to digital */
{
 
 AdcChannel_t       Channel; /* This variable is for select adc channel */
 AdjustResult_t     AdjustResult; /* This variable is for select adc adjust result */
 VoltageRefrence_t  VoltageRefrence; /* This variable is for select adc voltage refrence */
 TriggerSource_t    TriggerSource; /* This variable is for select adc trigger source */
 uint8_t            Prescaler;
 
 Status_t           Enable : 1; /* This flag is for adc enable */
 Status_t           AutoTriggerEnable : 1; /* This flag is for auto trigger enable */ 
 Status_t           InterruptEnable :1; /* This flag is for interrupt enable */

}AnalogToDigitalConfig; 

extern struct Flag /* Struct for ADC Flags */
{

 uint8_t ConversionComplete : 1; /* This bit writen 1 when ADC conversion completes */
 
}AdcStatus;
                                   
/*************************************** Create Variable *************************************/

extern volatile uint16_t adc_input_voltage; /* Variable for receive adc input voltage */

/************************************** Create Functions *************************************/

void Analog_To_Digital_Initialize( void ); /* Function for initialize analog to digital mode */

void Adc_Init(void); /* Function for initialize ADC */

/************************************* End Of The Program ************************************/

#endif
