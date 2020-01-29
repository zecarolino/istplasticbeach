#ifndef _DMA_H_
#define _DMA_H_

#include "ends.h"

#ifndef str
#define str(s) #s /* stringify */
#endif

void dma(void *src, void *dst, int siz, int dir) {
	asm("\trdw R11\n\taddi 2\n\twrw RB\n\trdwb\n\trdwb\n");
	asm("\twrw DMA_EXT_ADDR_ADDR\n");
	asm("\trdw R11\n\taddi 3\n\twrw RB\n\trdwb\n\trdwb\n");
	asm("\twrw DMA_INT_ADDR_ADDR\n");
	asm("\trdw R11\n\taddi 4\n\twrw RB\n\trdwb\n\trdwb\n");
	asm("\twrw DMA_SIZE_ADDR\n");
	asm("\trdw R11\n\taddi 5\n\twrw RB\n\trdwb\n\trdwb\n");
	asm("\twrw DMA_DIRECTION_ADDR\n");
	asm("_dmaw\tldi 1\n\tand DMA_STATUS_ADDR\n\tbneqi _dmaw\n\tnop\n");
}

#define dmaConfig(src,dst,siz,dir,lab) \
	asm("\tldi " str(src) "\n\twrw DMA_EXT_ADDR_ADDR\n" \
		"\tldi " str(dst) "\n\twrw DMA_INT_ADDR_ADDR\n" \
		"\tldi " str(siz) "\n\twrw DMA_SIZE_ADDR\n" \
		"\tldi " str(dir) "\n\twrw DMA_DIRECTION_ADDR\n" \
		str(lab) "\tldi 1\n\tand DMA_STATUS_ADDR\n\tbneqi " \
		str(lab) "\n\tnop\n")

#define dmaSource(src) asm("\tldi " str(src) "\n\twrw DMA_EXT_ADDR_ADDR\n");
#define dmaDestination(dst) asm("\tldi " str(dst) "\n\twrw DMA_INT_ADDR_ADDR\n")
#define dmaSize(siz) asm("\tldi " str(siz) "\n\twrw DMA_SIZE_ADDR\n")
#define dmaDirection(dir) asm("\tldi " str(dir) "\n\twrw DMA_DIRECTION_ADDR\n")
#define dmaWait(lab) asm( str(lab) "\tldi 1\n\tand DMA_STATUS_ADDR\n\tbneqi " \
		str(lab) "\n\tnop\n")

#endif /* _DMA_H_ */
