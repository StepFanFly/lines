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
    bool step(int** field, int* next, int* score, point from, point to);
    void allowedMoves(int** temp,point from);
    void gimmeField(int** fieldv);
    void gimmeNext(int* nextv);
    bool isFineshed();
private:
    int **field;
    int **temp;
    int _x;//строки
    int _y;//столбцы
    int *next;
    point **next_c;
    int _next_n;//сколько новых шариков
    int _score;
    int _colors;//сколько вариантов цветов
    int _line;//сколько надо в ряд
    bool end;
    void random(point* &here);
    bool checkForEmpty();
    bool inField(const point &pnt);
    bool inField(const int &x, const int &y);
    void dfs(point from);
    bool findLines(point &from);
    void clearTemp();
    void delLines();
    bool genNext();
};

#endif // GAME_H
