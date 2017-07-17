#ifndef GAME_H
#define GAME_H
#define SCORE_BONUS 2
#include "random"
#include "time.h"

struct point{
    int _x,_y;
};

class game
{
public:
    game(int x, int y, int next_n, int colors, int line);
    ~game();
    void startGame(int **fieldv, int *nextv);
    bool step(int **fieldv, int *nextv, int *scorev, point from, point to);
    void skipStep(int** fieldv, int* nextv, int* scorev);
    void allowedMoves(int** temp,point from);
    void gimmeField(int** fieldv);
    void gimmeNext(int* nextv);
    bool isFineshed();
private:
    int dfs_k;
    int **field;
    int **temp;
    int _x;//height
    int _y;//wight
    int *next;
    point **next_c;
    int _next_n;//new balls count
    int _score;
    int _colors;//colors count
    int _line;//how many must be in line
    bool end;
    void random(point* &here);
    bool isFull();
    bool inField(const point &pnt);
    bool inField(const int &x, const int &y);
    void dfs(point from);
    bool findLines(point &from);
    void clearTemp();
    void delLines();
    bool genNext();
    bool isEmpty();
};

#endif // GAME_H
