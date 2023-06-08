#include <stdlib.h>
#include <stdio.h>

#include "cut.h"

int main(void) {

    // CPU* cpu[CPUS_NUM];
    // create_cpus(cpu, CPUS_NUM);

    // FILE* procs_stat = fopen(PROC_STAT_PATH, "r");

    // if (!procs_stat){
    //     perror("fopen failed");
    //     return EXIT_FAILURE;
    // }

    // CPU* cpu = new_cpu();
    // printf("sizeof(cpu) = %zu\n", sizeof(cpu));

    // if (!fscanf(procs_stat, "%s %u %u %u %u %u %u %u %u %u %u\n", cpu->name, &cpu->user, &cpu->nice, &cpu->system, &cpu->idle, &cpu->iowait, &cpu->irq, &cpu->softirq, &cpu->steal, &cpu->guest, &cpu->guest_nice))
    // {
    //     perror("fscanf failed");
    //     return EXIT_FAILURE;
    // }

    
    // if(read_cpus_params(cpu, CPUS_NUM))
    // {
    //     perror("Read from /proc/stat failed");
    //     return EXIT_FAILURE;
    // }

    // print_cpus_info(cpu, CPUS_NUM);

    // // fclose(procs_stat);
    // delete_cpus(cpu, CPUS_NUM);

    print_cpus_usage();

    return EXIT_SUCCESS;
}
