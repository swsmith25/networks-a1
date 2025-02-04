// windows
#ifdef _WIN32
#define _WIN32_WINNT 0x601
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <ws2spi.h>
#else
//linux
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

// works for any OS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// unsure what this works for
#include <pthread.h>


#define PORT_MAX (1 << 16) - 1 // 65535
#define BUFFER_SIZE 1000
#define MAX_CLIENT 10


/**
 * @brief Get the time funtion
 * 
 * @return double current time in seconds
 * (double data type and ns precision)
 */
double get_time(void)
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec + (now.tv_nsec * 1e-9);
}


/**
 * @brief ?
 * 
 * @param arg 
 * @return void* 
 */
void *communicate(void *arg) {
    int client_socket = *(int *)arg;
    char buffer[BUFFER_SIZE];
    
    long bytes_received = 0;

    free(arg);
    arg=NULL;

    double start_time = get_time();
    /* 5. After the connection is established, receive data in chunks of 1000 bytes */
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int read_size = read(client_socket, buffer, BUFFER_SIZE);
        
        if (read_size <= 0) {
            printf("Client disconnected\n");
            break;
        }

        bytes_received += read_size; //track recieved
    }

    close(client_socket);

    /* 6. When the connection is closed, the program should print out the elapsed time, */
    /*    the total number of bytes received (in kilobytes), and the rate */
    /*    at which the program received data (in Mbps) */
    double total_time = get_time() - start_time;
    printf("Elapsed time: %f\n", total_time);
    printf("Kbytes received: %li kilobytes\n", bytes_received/1000);
    printf("Throughput: %f Mbps\n", ((bytes_received * 8.0) / (total_time * 1000000))); 

    return NULL;
}


/**
 * @brief server communication
 * 
 * @param port 
 */
void handle_server(int port)
{
    struct sockaddr_in server_addr;
    int addr_size = sizeof(server_addr);

    /* 1. Create a TCP/IP socket with `socket` system call */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        fprintf(stderr, "Error creating socket.\n");
        exit(EXIT_FAILURE);
    }
    
    /* 2. `bind` socket to the given port number */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *)&server_addr, addr_size) != 0)
    {
        fprintf(stderr, "Error binding socket.\n");
        exit(EXIT_FAILURE);
    }

    /* 3. `listen` for TCP connections */
    if (listen(sockfd, MAX_CLIENT) != 0)
    {
        fprintf(stderr, "Error listening for connections.\n");
        exit(EXIT_FAILURE);
    }

    /* 4. Wait for the client connection with `accept` system call */
    printf("Server listening on port %d\n", port);

    while (1)
    {
        int *client_socket = malloc(sizeof(int));
        if ((*client_socket = accept(sockfd, (struct sockaddr *)&server_addr, (socklen_t *)&addr_size)) < 0) {
            fprintf(stderr, "Error accepting connection.\n");
            free(client_socket);
            continue;
        }
        printf("New client connected.\n");
        
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, communicate, client_socket) != 0) {
            fprintf(stderr, "Error creating thread.\n");
            free(client_socket);
        }
        pthread_detach(thread_id);
    }

    close(sockfd);
}


/**
 * @brief client mode messages
 * 
 * @param addr 
 * @param port 
 * @param duration 
 */
void handle_client(const char *addr, int port, int duration)
{
    
    struct sockaddr_in serv_addr;
    char *message = "Hello from client";
    
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    
    /* 1. Create a TCP/IP socket with socket system call */
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        fprintf(stderr, "Error creating socket.\n");
        exit(EXIT_FAILURE);
    }

    /* 2. `connect` to the server specified by arguments (`addr`, `port`) */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, addr, &serv_addr.sin_addr) <= 0) {
        fprintf(stderr, "Invalid address/Address not supported.\n");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        fprintf(stderr, "Connection failed.\n");
        exit(EXIT_FAILURE);
    }

    /* 3. Send data to the connected server in chunks of 1000bytes */
    double start_time = get_time();
    long bytes_sent = 0;
    while (get_time() - start_time < duration)
    {
        int curr_bytes_sent = send(sock, buffer, BUFFER_SIZE, 0);
        if (curr_bytes_sent < 0)
        {
            fprintf(stderr, "Error sending data.\n");
            break;
        }
        //fprintf(stdout, "bytes sent: %ld\n", bytes_sent);
        bytes_sent += curr_bytes_sent; //i.e plus 1000
    }

    /* 4. Close the connection after `duration` seconds */
    close(sock);

    /* 5. When the connection is closed, the program should print out the elapsed time, */
    /*    the total number of bytes sent (in kilobytes), and the rate */
    /*    at which the program sent data (in Mbps) */
    double total_time = get_time() - start_time;
    printf("Elapsed time: %f\n", total_time);
    printf("Kbytes sent: %li kilobytes\n", bytes_sent/1000);
    printf("Throughput: %f Mbps\n", ((bytes_sent * 8.0) / (total_time * 1000000)));
    //MBps = (kilobytes_sent * 8.0) / total_time * 1000.0;
}




/**
 * @brief main runna funciton
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
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

        /* Argument checking */
        /* 1. Check server_tcp_port is within the port number range */
        if (server_tcp_port < 1 || server_tcp_port > PORT_MAX)
        {
            fprintf(stderr, "Server TCP port number is out of range.\n");
            exit(EXIT_FAILURE);
        }
        /* 2. Check the duration is a positive number */
        if (duration <= 0)
        {
            fprintf(stderr, "Please enter a positive duration value.\n");
            exit(EXIT_FAILURE);
        }

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

        /* Argument checking */
        /* Check server_tcp_port is within the port number range */
        if (server_tcp_port < 1 || server_tcp_port > PORT_MAX)
        {
            fprintf(stderr, "Server TCP port number is out of range.\n");
            exit(EXIT_FAILURE);
        }

        printf("Server mode, Port = %d\n", server_tcp_port);
        handle_server(server_tcp_port);
    }

    return 0;
}
