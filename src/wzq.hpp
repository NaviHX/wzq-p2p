#ifndef __WZQ_HPP__
#define __WZQ_HPP__

#include <cstdio>
#include <cstdlib>
#include <cstring>

class wzq
{
private:
    int map[15][15];
    int curseX;
    int curseY;

public:
    int getCurseX() { return curseX; }
    int getCurseY() { return curseY; }
    void moveUp()
    {
        if (curseY > 0)
            curseY--;
    }
    void moveDown()
    {
        if (curseY < 14)
            curseY++;
    }
    void moveRight()
    {
        if (curseX < 14)
            curseX++;
    }
    void moveLeft()
    {
        if (curseX > 0)
            curseX--;
    }
    int place(int x, int y, int color)
    {
        if (map[y][x] == 0)
        {
            map[y][x] = color;
            return checkMap(x, y, color);
        }
        return -1;
    }
    int getMap(int x, int y)
    {
        if (x >= 0 && x < 15 && y >= 0 && y < 15)
            return map[y][x];
        return -1;
    }
    bool checkMap(int x, int y, int color)
    {
        int tx, ty;
        int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
        int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
        int total[8] = {0};
        for (int i = 0; i < 8; i++)
        {
            tx = x + dx[i];
            ty = y + dy[i];
            while (total[i] < 4 && map[ty][tx] == color && tx >= 0 && tx < 15 && ty >= 0 && ty < 15)
            {
                tx += dx[i];
                ty += dy[i];
                total[i]++;
            }
        }
        for (int i = 0; i < 4; i++)
            if (total[i] + total[i + 4] >= 4)
                return true;
        return false;
    }

public:
    wzq()
    {
        curseX = 7, curseY = 7;
        memset(map, 0, sizeof(int));
    }
    ~wzq() = default;
};

#endif