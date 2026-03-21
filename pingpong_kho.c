#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "user.h" 

int main(int argc, char *argv[]) {
    int p2c[2], c2p[2];
    char ball[1];

    if (pipe(p2c) < 0 || pipe(c2p) < 0) {
        fprintf(2, "Error creating pipes\n"); 
        exit(1);
    }

    int pid = fork();
    if (pid < 0) {
        fprintf(2, "Error creating fork\n");
        exit(1);
    }

    if (pid == 0) {
        // TIẾN TRÌNH CON
        close(p2c[1]);
        close(c2p[0]);

        if (read(p2c[0], ball, 1) == 1) {
            printf("%d: received ping\n", getpid());
        }

        write(c2p[1], "O", 1);
        
        close(p2c[0]);
        close(c2p[1]);
        
        exit(0);
    }
    else {
        // TIẾN TRÌNH CHA
        close(p2c[0]);
        close(c2p[1]);
        
        write(p2c[1], "O", 1);

        if (read(c2p[0], ball, 1) == 1) {
            printf("%d: received pong\n", getpid());
        }
        
        close(p2c[1]);
        close(c2p[0]);
        wait(0);
    }

    exit(0);
}
