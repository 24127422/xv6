#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
    char *xargv[MAXARG];
    char buf[512];
    int start_idx = 1;

    if (argc < 2) {
        fprintf(2, "Usage: xargs command...\n"); 
        exit(1);
    }

    
    if (argc >= 3 && strcmp(argv[1], "-n") == 0) {
        start_idx = 3;
    }
    
    
    int base_argc = 0;
    for (int i = start_idx; i < argc; i++) {
        xargv[base_argc++] = argv[i];
    }

    int buf_idx = 0;
    char c;
    
    
    while (read(0, &c, 1) == 1) {
        if (c == '\n') {
            buf[buf_idx] = '\0'; 

            
            if (fork() == 0) {
                
                xargv[base_argc] = buf;
                xargv[base_argc + 1] = 0; 
                
                exec(xargv[0], xargv); 
                fprintf(2, "exec %s failed\n", xargv[0]);
                exit(1);
            }
            
            wait(0);
            buf_idx = 0; 
        } else {
            if (buf_idx < sizeof(buf) - 1) {
                buf[buf_idx++] = c;
            }
        }
    }
    exit(0);
}
