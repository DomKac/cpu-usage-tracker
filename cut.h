#include <stdio.h>
#include <stdlib.h>

typedef struct CPU
{
    char name[8];
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
} CPU;

CPU* new_cpu(void);
void print_cpu_info(const CPU* cpu);

CPU* new_cpu(void) {
    CPU* cpu = (CPU*)malloc(sizeof(CPU));
    return cpu;
}

void print_cpu_info(const CPU* cpu) {
    printf("%s ", cpu->name);
    printf("%u ", cpu->user);
    printf("%u ", cpu->nice);
    printf("%u ", cpu->system);
    printf("%u ", cpu->idle);
    printf("%u ", cpu->iowait);
    printf("%u ", cpu->irq);
    printf("%u ", cpu->softirq);
    printf("%u ", cpu->steal);
    printf("%u ", cpu->guest);
    printf("%u\n", cpu->guest_nice);
}



