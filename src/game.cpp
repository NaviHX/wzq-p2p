#include "wzq.hpp"
#include "game.h"
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <termios.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

wzq _wzq;
int status;
int color; // 1/B or 2/W
int xloc, yloc;
int socket_fd;

char getch()
{
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    memcpy(&newt, &oldt, sizeof(newt));
    newt.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    char c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

int hostGame()
{
    color = 1;
    status = 1;

    // 创建套接字
    int server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 绑定
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(12000);
    bind(server_fd, (struct sockaddr *)&myaddr, sizeof(myaddr));

    // 监听
    listen(server_fd, 1);

    struct sockaddr_in client_addr;
    int addr_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&addr_len);
    socket_fd = client_fd;
    initMap();
    work();

    close(client_fd);
    return 0;
}
int connectGame(const char *ip)
{
    color = 2;
    status = 1;

    // 创建套接字
    int client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 连接
    struct sockaddr_in myaddr;
    memset(&myaddr, 0, sizeof(sockaddr_in));
    myaddr.sin_family = AF_INET;
    inet_aton(ip, &myaddr.sin_addr);
    myaddr.sin_port = htons(12000);
    connect(client_fd, (sockaddr *)&myaddr, sizeof(myaddr));
    socket_fd = client_fd;
    work();
}
void *keyBoardListener(void *p)
{
    int key = getch();
    int color = _wzq.getMap(_wzq.getCurseX(), _wzq.getCurseY());
    switch (key)
    {
    case 'a':
        if (_wzq.moveLeft() != -1)
            printf("\e[1D");
        break;
    case 's':
        if (_wzq.moveDown() != -1)
            printf("\e[1B");
        break;
    case 'd':
        if (_wzq.moveRight() != -1)
            printf("\e[1C");
        break;
    case 'w':
        if (_wzq.moveUp() != -1)
            printf("\e[1A");
        break;
    case 'f':
        // 记录位置
        xloc = _wzq.getCurseX();
        yloc = _wzq.getCurseY();
        // 更改状态
        status = (status == 1 ? 2 : 1);
        break;
    default:
        break;
    }
}
void initMap()
{
    printf("\ec"); //清屏
    printf("+---------------+\n"); // 1
    printf("|               |\n"); // 2
    printf("|               |\n"); // 3
    printf("|               |\n"); // 4
    printf("|               |\n"); // 5
    printf("|               |\n"); // 6
    printf("|               |\n"); // 7
    printf("|               |\n"); // 8
    printf("|               |\n"); // 9
    printf("|               |\n"); // 10
    printf("|               |\n"); // 11
    printf("|               |\n"); // 12
    printf("|               |\n"); // 13
    printf("|               |\n"); // 14
    printf("|               |\n"); // 15
    printf("|               |\n"); // 16
    printf("+---------------+\n"); // 17
    printf("\nPress \"WASD\" to move cursor.\n"); // 19
    printf("Press \"F\" to place piece\n"); // 20
    printf("\e[2;2H");
}
void work()
{
    pthread_t pid;
    pthread_create(&pid, NULL, keyBoardListener, NULL);
    while (status != 0)
    {
        char buf[16];
        if (status == color)
        {
            while (status == color)
            {
                // loop until press 'f'
            }
            // 落子
            // 发送报文
            
        }
        else
        {
            // 接受报文
            // 落子
        }
        // 检查棋盘
    }
}
