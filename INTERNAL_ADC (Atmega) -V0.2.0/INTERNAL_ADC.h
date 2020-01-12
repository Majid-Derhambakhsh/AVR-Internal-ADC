/*
------------------------------------------------------------------------------
~ File   : INTERNAL_ADC.h
~ Author : Majid Derhambakhsh
~ Version: V0.2.0
~ Created: 05/21/2019 01:41:00 PM
~ Brief  :
~ Support: Majid.do16@gmail.com
------------------------------------------------------------------------------
~ Description: Enable internal Atmega ADC

~ Attention  : This file is for "AVR GCC" & "CodeVision Avr"
------------------------------------------------------------------------------
*/

#ifndef __INTERNAL_ADC_H_
#define __INTERNAL_ADC_H_

/************************ Compiler & Library Controll ************************/ 

/*----------------------------------------------------------*/

#ifdef __CODEVISIONAVR__  /* Check compiler */

 #include <io.h>            /* Import AVR IO library */

/*----------------------------------------------------------*/

#elif defined(__GNUC__)   /* Check compiler */

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
 #define ADC_DATA_REGISTER                   ADCW
                                                     
/*------------------------ Inline function --------------------------*/   /* Default Set */

 #define START_ADC_CONVERSION()  (ADCSRA |= 0x40) /* for start conversion */

/*-------------------- Define For Assembly Code ---------------------*/   /* Default Set */

#ifdef __CODEVISIONAVR__  /* Check compiler */

 #define ENABLE_GLOBAL_INTERRUPT   #asm("sei") /* Define for global interrupt enable */
 #define DISABLE_GLOBAL_INTERRUPT  #asm("cli") /* Define for global interrupt disable */

/*-------------------------------------------------------*/

#elif defined(__GNUC__)   /* Check compiler */

 #define ENABLE_GLOBAL_INTERRUPT   __asm__ ("sei"); /* Define for global interrupt enable */
 #define DISABLE_GLOBAL_INTERRUPT  __asm__ ("cli"); /* Define for global interrupt disable */

#endif

/*----------------------------- Public ------------------------------*/   /* Default Set */
 
#ifdef __CODEVISIONAVR__  /* Check compiler */

 #define INTERRUPT(vector)  interrupt [vector] void adc_isr(void)
 #define ADC_CONVERSION_COMPLETE_VECTOR  ADC_INT /* ADC conversion complete interrupt vector number */

/*-------------------------------------------------------*/

#elif defined(__GNUC__)   /* Check compiler */

 #define INTERRUPT(vector)  ISR(vector)
 #define ADC_CONVERSION_COMPLETE_VECTOR  ADC_vect /* ADC conversion complete interrupt vector number */

#endif

/*-------------------------------------------------------*/

 #define AnalogToDigital  Analog_To_Digital_Initialize /* Select function */
 #define ENUM_U8_T(ENUM_NAME)    Enum_##ENUM_NAME;  typedef uint8_t ENUM_NAME /* Config enum size */

/**************************************** End Defines ****************************************/

/*************************************** Create Enums ****************************************/

typedef enum /* Enum for config input ADC channel */
{

 Channel0 = 0x00, /* ADC channel 0 */
 Channel1 = 0x01, /* ADC channel 1 */
 Channel2 = 0x02, /* ADC channel 2 */
 Channel3 = 0x03, /* ADC channel 3 */
 Channel4 = 0x04, /* ADC channel 4 */
 Channel5 = 0x05, /* ADC channel 5 */
 Channel6 = 0x06, /* ADC channel 6 */
 Channel7 = 0x07  /* ADC channel 7 */

}ENUM_U8_T( AdcChannel_t );

typedef enum /* Enum for adc adjust result */
{

 Left = 0x20, /* Left result */
 Right = 0x00, /* Right result */

}ENUM_U8_T( AdjustResult_t );

typedef enum /* Enum for config adc voltage reference */
{

 ArefRefrence     = 0x00, /* Aref reference */
 AVccRefrence     = 0x00, /* Vcc reference */
 InternalRefrence = 0xC0, /* Internal reference */
 
}ENUM_U8_T( VoltageRefrence_t );

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
 VoltageRefrence_t  VoltageRefrence; /* This variable is for select adc voltage reference */
 uint8_t            Prescaler;
 
 Status_t           Enable : 1; /* This flag is for adc enable */
 Status_t           FreeRunning_AutoTriggerSelect : 1; /* This flag is for free running-Auto trigger mode */
 Status_t           InterruptEnable :1; /* This flag is for interrupt enable */

}AnalogToDigitalConfig; 

extern struct Flag /* Struct for ADC Flags */
{

 uint8_t ConversionComplete : 1; /* This bit written 1 when ADC conversion completes */
 
}AdcStatus;
                                   
/*************************************** Create Variable *************************************/

extern volatile uint16_t adc_input_voltage; /* Variable for receive adc input voltage */

/************************************** Create Functions *************************************/

void Analog_To_Digital_Initialize( void ); /* Function for initialize analog to digital mode */

void Adc_Init(void); /* Function for initialize ADC */

/************************************* End Of The Program ************************************/

#endif
