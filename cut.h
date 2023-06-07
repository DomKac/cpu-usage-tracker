#include <stdio.h>
#include <stdlib.h>


typedef struct cpu
{
    unsigned user;
    unsigned nice;
    unsigned system;
    unsigned idle;
    unsigned iowait;
    unsigned irq;
    unsigned softirq;
    unsigned steal;
    unsigned guest;
    unsigned guest_nice;
} cpu;
