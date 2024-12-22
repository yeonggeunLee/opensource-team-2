#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345
#define BUFFER_SIZE 1024

typedef struct {
    int socket;
    char username[50];
} Client;

Client clients[100];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast_message(char *message, int sender_socket) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; i++) {
        if (clients[i].socket != sender_socket) {
            send(clients[i].socket, message, strlen(message), 0);
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void handle_file_transfer(int client_socket) {
    char file_name[BUFFER_SIZE];
    int bytes_received = recv(client_socket, file_name, BUFFER_SIZE, 0);
    if (bytes_received <= 0) {
        perror("파일 이름 수신 실패");
        return;
    }
    file_name[bytes_received] = '\0';

    printf("파일 이름: %s\n", file_name);

    FILE *file = fopen(file_name, "wb");
    if (file == NULL) {
        perror("파일 열기 실패");
        return;
    }

    char buffer[BUFFER_SIZE];
    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytes_received, file);
    }

    fclose(file);
    printf("파일 전송 완료: %s\n", file_name);

    char received_message[BUFFER_SIZE];
    snprintf(received_message, sizeof(received_message), "FILE_RECEIVED:%s", file_name);
    send(client_socket, received_message, strlen(received_message), 0);
}

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    free(arg);

    char username[50];
    recv(client_socket, username, 50, 0);

    pthread_mutex_lock(&clients_mutex);
    clients[client_count].socket = client_socket;
    strcpy(clients[client_count].username, username);
    client_count++;
    pthread_mutex_unlock(&clients_mutex);
    
    printf("%s가 접속하였습니다.\n", username);

    char buffer[BUFFER_SIZE];
    sprintf(buffer, "%s 님이 입장하셨습니다.\n", username);
    broadcast_message(buffer, client_socket);

    while (1) {
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            break;
        }

        buffer[bytes_received] = '\0';

        if (strncmp(buffer, "/file", 5) == 0) {
            handle_file_transfer(client_socket);
        } else {
            broadcast_message(buffer, client_socket);
        }
    }

    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; i++) {
        if (clients[i].socket == client_socket) {
            for (int j = i; j < client_count - 1; j++) {
                clients[j] = clients[j + 1];
            }
            client_count--;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);

    close(client_socket);
    pthread_exit(NULL);
}

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("소켓 생성 실패");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("바인딩 실패");
        return 1;
    }

    if (listen(server_socket, 10) == -1) {
        perror("리스닝 실패");
        return 1;
    }

    printf("서버가 %d번 포트에서 실행 중입니다.\n", PORT);

    while (1) {
        addr_size = sizeof(client_addr);
        int *client_socket = malloc(sizeof(int));
        *client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
        if (*client_socket == -1) {
            perror("클라이언트 연결 실패");
            free(client_socket);
            continue;
        }

        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, client_socket);
        pthread_detach(thread);
    }

    close(server_socket);
    return 0;
}

