#include "hardware/structs/xip_ctrl.h"

#define CACHE_BASE  0x10000000
#define CACHE_BYPASS 0x13000000

void reset_cache(void);
float get_cache_hit_rate(void);
int get_hits(void);
int get_misses(void);
void blink(void);

typedef float (*func_ptr_t_float)(void);
typedef void (*func_ptr_t_void)(void);
typedef int (*func_ptr_t_int)(void);
typedef void (*func_ptr_t_blink)(void);

func_ptr_t_float get_cache_hit_rate_nocache = (func_ptr_t_float) ((int)get_cache_hit_rate - CACHE_BASE) + CACHE_BYPASS;
func_ptr_t_void reset_cache_nocache = (func_ptr_t_void) ((int)reset_cache - CACHE_BASE) + CACHE_BYPASS;
func_ptr_t_int get_hits_nocache = (func_ptr_t_int) ((int)get_hits - CACHE_BASE) + CACHE_BYPASS;
func_ptr_t_int get_misses_nocache = (func_ptr_t_int) ((int) get_misses - CACHE_BASE) + CACHE_BYPASS;
func_ptr_t_blink bad_blink = (func_ptr_t_blink) ((int)blink - CACHE_BASE) + CACHE_BYPASS;

void reset_cache (void) {
    xip_ctrl_hw->ctr_acc = 0;
    xip_ctrl_hw->ctr_hit = 0;
}

int get_hits(void) {
    return xip_ctrl_hw->ctr_hit;
}

int get_misses(void) {
    return xip_ctrl_hw->ctr_acc - xip_ctrl_hw->ctr_hit;
}

float get_cache_hit_rate (void) {
    return xip_ctrl_hw->ctr_hit * 100.f / xip_ctrl_hw->ctr_acc;
}