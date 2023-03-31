#include "../inc/uls.h"

int main(int argc, char* argv[]) {
    
    uls_command_t* command = mx_parse_uls_command(argc, argv);
    mx_execute_uls_command(command);
    
   
    mx_clear_files_list(command->files);
    free(command->flags);
    free(command);
    
    return 0;
}

