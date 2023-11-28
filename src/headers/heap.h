#include <stdlib.h>
#include <malloc.h>
#include <stdint.h>

int getTotalHeap(void) {
   extern char __StackLimit, __bss_end__;
   return &__StackLimit  - &__bss_end__;
}

int getFreeHeap(void) {
   struct mallinfo m = mallinfo();
   return (getTotalHeap() - m.uordblks);
}