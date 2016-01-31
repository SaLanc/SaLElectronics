
#ifndef SAL_H_
#define SAL_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <compiler.h>


#define INPUT 0
#define OUTPUT 1
#define OUTSTRONG 3
#define TRUE 1
#define FALSE 0

#define ATOMIC_SECTION_ENTER   { register uint32_t __atomic; \
	__asm volatile ("mrs %0, primask" : "=r" (__atomic) ); \
	__asm volatile ("cpsid i");
#define ATOMIC_SECTION_LEAVE   __asm volatile ("msr primask, %0" : : "r" (__atomic) ); }

#define CONTAINER_OF(ptr, type, field_name) \
((type *) (((uint8_t *)ptr) - offsetof(type, field_name)))

#include <SaLMath.h>


#include <boardDefines.h>

#include <samd21g18a.h>
#include <samd21.h>

#include <SaLClocks.h>

#include <SaLPort.h>

#include <SaLBitBang.h>

#include <SaLDelay.h>

#include <SaLBuzzer.h>

#include <SaLSample.h>

#include <SaLAltimeter.h>



#ifdef HAS_MS5607
#include <MS5607.h>
#endif

#ifdef HAS_ADXL345
#include <ADXL345.h>
#endif

#ifdef HAS_MTK3329
#include <MTK3329.h>
#endif




#endif

