/**
******************************************************************************
* @file    INTERNAL_ADC.c
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

#include "INTERNAL_ADC.h"
 
/*-------------------------- Create Struct --------------------------*/

struct AdcModeInit InternalAdc; /* Struct for select ADC mode */
struct AnalogToDigitalInitialize AnalogToDigitalConfig; /* Struct for config analog to digital */
struct Flag AdcStatus; /* Struct for ADC Flags */

/*------------------------- Create Variable -------------------------*/

volatile uint16_t adc_input_voltage = 0; /* Variable for receive adc input voltage */

/*------------------------- Create Function -------------------------*/

INTERRUPT(ADC_CONVERSION_COMPLETE_VECTOR)
{

 adc_input_voltage = ADC_DATA_REGISTER; /* Get adc voltage */
 AdcStatus.ConversionComplete = 1; /* Set conversion complete flag */

}

/*-----------------------------------*/

void Analog_To_Digital_Initialize( void ) /* Function for initialize analog to digital mode */
{
 
 /*------------------------------- Config ADC -------------------------------*/

 ADC_Multiplexer_Selection_Register = AnalogToDigitalConfig.Channel | AnalogToDigitalConfig.AdjustResult | AnalogToDigitalConfig.VoltageRefrence; /* Config channel - adjust result & voltage refrence */
 ADC_Control_And_Status_Register_A = (AnalogToDigitalConfig.Enable << ADEN) | (AnalogToDigitalConfig.AutoTriggerEnable << ADATE) | (AnalogToDigitalConfig.InterruptEnable << ADIE) | AnalogToDigitalConfig.Prescaler; /* Config 'prescaler' - 'enable bit' - 'auto trigger enable bit' & 'interrupt enable bit' */
 ADC_Control_And_Status_Register_B = AnalogToDigitalConfig.TriggerSource; /* Config trigger source */

 /*------------------------------- Subprogram -------------------------------*/ 

 if( AnalogToDigitalConfig.InterruptEnable == True ) /* Check 'interrupt enable bit' status */
 {
 
  ENABLE_GLOBAL_INTERRUPT /* Enable global interrupt */
 
 }
 else
 {
 
  DISABLE_GLOBAL_INTERRUPT /* Disable global interrupt */
 
 }
 /* End function */
}

/*-----------------------------------*/

void Adc_Init(void) /* Function for initialize ADC */
{

 InternalAdc.Mode(); /* Config ADC */ 
 
}

/* End Program */