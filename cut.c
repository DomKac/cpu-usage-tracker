#include <stdlib.h>
#include <stdio.h>

#include "cut.h"

#define PROC_STAT_PATH "/proc/stat"


int main(void) {

    FILE* procs_stat = fopen(PROC_STAT_PATH, "r");

    if (!procs_stat){
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    CPU* cpu = new_cpu();
    printf("sizeof(cpu) = %zu\n", sizeof(cpu));

    if (!fscanf(procs_stat, "%s %u %u %u %u %u %u %u %u %u %u\n", cpu->name, &cpu->user, &cpu->nice, &cpu->system, &cpu->idle, &cpu->iowait, &cpu->irq, &cpu->softirq, &cpu->steal, &cpu->guest, &cpu->guest_nice))
    {
        perror("fscanf failed");
        return EXIT_FAILURE;
    }

    print_cpu_info(cpu);

    fclose(procs_stat);
    free(cpu);

    return EXIT_SUCCESS;
}
