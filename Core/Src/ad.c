#include "ad.h"

void ad_init() {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);

	ADC_InitTypeDef adcInitTypeDef;
	adcInitTypeDef.ADC_Mode = ADC_Mode_Independent;
	adcInitTypeDef.ADC_DataAlign = ADC_DataAlign_Right;
	adcInitTypeDef.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adcInitTypeDef.ADC_ContinuousConvMode = DISABLE;    // 连续
	adcInitTypeDef.ADC_ScanConvMode = DISABLE;          // 连续转换
	adcInitTypeDef.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1, &adcInitTypeDef);

	ADC_Cmd(ADC1, ENABLE);
	// ADC 校准
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t ad_get_value() {
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}
