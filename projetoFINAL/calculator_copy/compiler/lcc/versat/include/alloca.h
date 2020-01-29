#ifndef _ALLOCA_H_
#define _ALLOCA_H_

#ifndef str
#define str(s) #s /* stringify */
#endif

/* function must have a frame (arguments or locals) */

/* 'siz' must be a global var and its value is replaced by the result */
#define alloca(siz) \
	asm("\tldi " str(siz) "\n\twrw RB\n\trdwb\n\trdwb\n\twrw RB\n" \
		"\trdw R12\n\tsub RB\n\twrw R12\n" \
		"\tldi " str(siz) "\n\twrw RB\n\trdw R12\n\twrwb\n")

/* 'pos' must be a global var and its value is set to sp=R12 position */
#define sp(pos) \
	asm("\tldi " str(pos) "\n\twrw RB\n\trdw R12\n\twrwb\n")

#endif /* _ALLOCA_H_ */
