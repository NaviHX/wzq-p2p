#ifndef __GAME_H__
#define __GAME_H__

int hostGame();
int connectGame(const char *ip);
void work();

void *keyBoardListener(void *p);
void initMap();
void drawMap();

#endif