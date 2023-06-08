#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>

#define PROC_STAT_PATH "/proc/stat"
#define CPUS_NUM 9

typedef struct CPU
{
    // enum {user = 0, nice = 1, system = 2, idle = 3, iowait = 3, irq = 4, softirq = 5, steal = 6, guest = 7, guest_nice = 9, param_size = 10};
    
    char name[8];
    // unsigned param[param_size];
    
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
void create_cpus(CPU* [], const size_t);

int read_cpus_params(CPU* [], size_t);
void print_cpu_info(const CPU*);
void print_cpus_info(CPU* [], size_t);

void delete_cpus(CPU* [], const size_t);

double cpu_usage(const CPU*, CPU*);
void cpus_usage(CPU* [], CPU* []);
void print_cpus_usage(void);

CPU* new_cpu(void) {
    CPU* cpu = (CPU*)malloc(sizeof(CPU));
    return cpu;
}

void create_cpus(CPU* cpu[], const size_t cpus_num) {
    
    // możliwe że tu będzie zmiana na 
    
    for (size_t i = 0; i < cpus_num; i++)
        cpu[i] = new_cpu(); 
}



// void print_cpu_info(const CPU* cpu) {
//     printf("%s ", cpu->name);
//     for (size_t i = 0; i < cpu->param_size; i++)
//         printf("%u ", cpu->param[i]);
//     puts("");
// }

// do zmiany
int read_cpus_params(CPU* cpu[], size_t cpu_num) {
    
    FILE* proc_stat = fopen(PROC_STAT_PATH, "r");
    
    if (!proc_stat){
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < cpu_num; i++)
    {
        if (!fscanf(proc_stat, "%s %u %u %u %u %u %u %u %u %u %u\n", cpu[i]->name, &cpu[i]->user, &cpu[i]->nice, &cpu[i]->system, &cpu[i]->idle, &cpu[i]->iowait, &cpu[i]->irq, &cpu[i]->softirq, &cpu[i]->steal, &cpu[i]->guest, &cpu[i]->guest_nice))
        {
            perror("fscanf failed");
            fclose(proc_stat);
            return EXIT_FAILURE;
        }
    }
    
    fclose(proc_stat);
    return EXIT_SUCCESS;
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

void print_cpus_info(CPU* cpu[], size_t cpu_num) {
    for (size_t i = 0; i < cpu_num; i++)
        print_cpu_info(cpu[i]);
}

void delete_cpus(CPU* cpu[], const size_t cpus_num) {
    for (size_t i = 0; i < cpus_num; i++)
        free(cpu[i]);
}

double cpu_usage(const CPU* cpu, CPU* prev) {
    unsigned PrevIdle = prev->idle + prev->iowait;
    unsigned Idle = cpu->idle + cpu->iowait;

    unsigned PrevNonIdle = prev->user + prev->nice + prev->system + prev->irq + prev->softirq + prev->steal;
    unsigned NonIdle = cpu->user + cpu->nice + cpu->system + cpu->irq + cpu->softirq + cpu->steal;

    unsigned PrevTotal = PrevIdle + PrevNonIdle;
    unsigned Total = Idle + NonIdle;

    // differentiate: actual value minus the previous one
    unsigned totald = Total - PrevTotal;
    unsigned idled = Idle - PrevIdle;

    // prev = cpu;
    memcpy(prev, cpu, sizeof(unsigned)*10 + sizeof(char)*8);

    return (totald - idled) / (double)totald * 100.0;
}

void cpus_usage(CPU* cpu[], CPU* prev[]) {
    for (size_t i = 0; i < CPUS_NUM; i++)
    {
        double cpu_use = cpu_usage(cpu[i], prev[i]);
        printf("%s %.2f%%\n", cpu[i]->name, cpu_use);
    }
}

void print_cpus_usage(void) {
    
    // Will store current cpus info after reading proc/stat
    CPU* cpu[CPUS_NUM];
    create_cpus(cpu, CPUS_NUM);

    // Previous cpus stats
    CPU* prev[CPUS_NUM];
    create_cpus(prev, CPUS_NUM);
    read_cpus_params(prev, CPUS_NUM);

    for (size_t i = 0; i < 10; ++i)
    {
        read_cpus_params(cpu, CPUS_NUM);
        cpus_usage(cpu, prev);
        puts("");
        sleep(1);
    }
    
    delete_cpus(cpu, CPUS_NUM);
    delete_cpus(prev, CPUS_NUM);
}
