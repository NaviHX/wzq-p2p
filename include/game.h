#ifndef __GAME_H__
#define __GAME_H__

struct msg
{
    char type;
    char x;
    char y;
};

int hostGame();
int connectGame(const char *ip);
void *keyBoardListener(void *p);
void initMap();
void work();

msg msgParser(char* buf);
char* dumpToChar(msg buf);

#endif