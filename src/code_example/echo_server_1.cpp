#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>

int main(int argc, char* argv) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s <addr> <port>\n", argv[0]);
        return -1; 
    }

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in 
}