#include "dma_data_transfer.h"

uint16_t size_;

void dma_data_transfer_init(uint32_t addr_from, uint32_t addr_to, uint16_t size) {
	size_ = size;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_InitTypeDef dmaInitTypeDef;
	dmaInitTypeDef.DMA_PeripheralBaseAddr = addr_from;
	dmaInitTypeDef.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dmaInitTypeDef.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	dmaInitTypeDef.DMA_MemoryBaseAddr = addr_to;
	dmaInitTypeDef.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dmaInitTypeDef.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dmaInitTypeDef.DMA_BufferSize = size;
	dmaInitTypeDef.DMA_DIR = DMA_DIR_PeripheralSRC;
	dmaInitTypeDef.DMA_M2M = DMA_M2M_Enable;
	dmaInitTypeDef.DMA_Mode = DMA_Mode_Normal;
	dmaInitTypeDef.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1, &dmaInitTypeDef);

	DMA_Cmd(DMA1_Channel1, DISABLE);
}

void dma_data_transfer() {
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, size_);
	DMA_Cmd(DMA1_Channel1, ENABLE);

	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);
}
