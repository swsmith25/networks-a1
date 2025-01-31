// windows
_WIN32_WINNT = 0x601
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <ws2spi.h>
// original
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>

#define PORT_MAX (1 << 16) - 1 // 65535
#define BUFFER_SIZE 1000
#define MAX_CLIENT 10

/* get_time function */
/* Input: None */
/* Output: current time in seconds */
/* (double data type and ns precision) */
double get_time(void)
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + (now.tv_nsec * 1e-9);
}

void handle_server(int port)
{
    /* TODO: Implement server mode operation here */
    /* 1. Create a TCP/IP socket with `socket` system call */
    /* 2. `bind` socket to the given port number */
    /* 3. `listen` for TCP connections */
    /* 4. Wait for the client connection with `accept` system call */
    /* 5. After the connection is established, received data in chunks of 1000 bytes */
    /* 6. When the connection is closed, the program should print out the elapsed time, */
    /*    the total number of bytes received (in kilobytes), and the rate */
    /*    at which the program received data (in Mbps) */

    return;
}

void handle_client(const char *addr, int port, int duration)
{
    /* TODO: Implement client mode operation here */
    /* 1. Create a TCP/IP socket with socket system call */
    /* 2. `connect` to the server specified by arguments (`addr`, `port`) */
    /* 3. Send data to the connected server in chunks of 1000bytes */
    /* 4. Close the connection after `duration` seconds */
    /* 5. When the connection is closed, the program should print out the elapsed time, */
    /*    the total number of bytes sent (in kilobytes), and the rate */
    /*    at which the program sent data (in Mbps) */

    return;
}

int main(int argc, char *argv[])
{
    /* argument parsing */
    int mode = 0, server_tcp_port = 0, duration = 0;
    char *server_host_ipaddr = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "csh:p:t:")) != -1)
    {
        switch (opt)
        {
        case 'c':
            mode = 1;
            break;
        case 's':
            mode = 2;
            break;
        case 'h':
            server_host_ipaddr = optarg;
            break;
        case 'p':
            server_tcp_port = atoi(optarg);
            break;
        case 't':
            duration = atoi(optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s -c -h <server_host_ipaddr> -p <server_tcp_port> -t <duration_in_sec>\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (mode == 0)
    {
        fprintf(stderr, "Please specify either -c (client mode) or -s (server mode).\n");
        exit(EXIT_FAILURE);
    }

    if (mode == 1)
    {
        if (server_host_ipaddr == NULL || duration == 0 || server_tcp_port == 0)
        {
            fprintf(stderr, "Client mode requires -h, -p, and -t options.\n");
            exit(EXIT_FAILURE);
        }

        /* TODO: Implement argument check here */
        /* 1. Check server_tcp_port is within the port number range */
        /* 2. Check the duration is a positive number */

        printf("Client mode: Server IP = %s, Port = %d, Time Window = %d\n", server_host_ipaddr, server_tcp_port, duration);
        handle_client(server_host_ipaddr, server_tcp_port, duration);
    }
    else if (mode == 2)
    {
        // Server mode logic goes here
        if (server_tcp_port == 0)
        {
            fprintf(stderr, "Server mode requires -p option.\n");
            exit(EXIT_FAILURE);
        }

        /* TODO: Implement argument check here */
        /* Check server_tcp_port is within the port number range */

        printf("Server mode, Port = %d\n", server_tcp_port);
        handle_server(server_tcp_port);
    }

    return 0;
}
