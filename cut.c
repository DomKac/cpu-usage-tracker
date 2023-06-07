#include <stdlib.h>
#include <stdio.h>

#define PROC_STAT_PATH "/proc/stat"



int main(void) {

    FILE* procs_stat = fopen(PROC_STAT_PATH, "r");
    char const text[] = "Roger roger";

    if (!procs_stat){
        perror("fopen failed");
        return EXIT_FAILURE ;
    }

    

    
    fprintf(stderr, "%s\n", text);

    fclose(procs_stat);

    return EXIT_SUCCESS;
}
