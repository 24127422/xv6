#include "../kernel/types.h"
#include "../kernel/param.h"
#include "user.h"

int main(int argc, char *argv[]) {
    char *xargv[MAXARG];
    char buf[512];
    
    if (argc < 2) {
        printf("Usage: xargs command...\n");
        exit(1);
    }

    int base_argc = 0;
    for (int i = 1; i < argc; i++) {
        xargv[base_argc++] = argv[i];
    }

    int curr_argc = base_argc;
    int buf_idx = 0;
    char c;
    
    xargv[curr_argc] = buf; 

    while (read(0, &c, 1) == 1) {
        if (c == ' ' || c == '\n') {
            buf[buf_idx++] = '\0';
            curr_argc++;
            xargv[curr_argc] = &buf[buf_idx];

            if (c == '\n') {
                xargv[curr_argc] = 0; 
                
                if (fork() == 0) {
                    exec(xargv[0], xargv);
                    printf("exec %s failed\n", xargv[0]);
                    exit(1);
                }
                wait(0);
                
                buf_idx = 0;
                curr_argc = base_argc;
                xargv[curr_argc] = buf;
            }
        } else {
            buf[buf_idx++] = c;
        }
    }
    exit(0);
}
