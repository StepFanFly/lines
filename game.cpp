#include "game.h"
#include <QDebug>
#include <QString>
game::game(int x, int y,int next_n,int colors, int line)
{
    srand(time(NULL));
    end=false;
    _x=x;
    _y=y;
    _score=0;
    _next_n=next_n;
    _colors=colors;
    _line=line;
    next = new int[_next_n];
    next_c = new point*[_next_n];
    for(int i=0;i<_next_n;i++){
        next_c[i]=new point;
    }
    field = new int* [_x];
    temp = new int* [_x];
    for(int i=0;i<_x;i++){
        field[i]=new int[_y];
        temp[i]=new int[_y];
        for(int j=0;j<_y;j++){
            temp[i][j]=0;
            field[i][j]=0;
        }
    }
    genNext();
    for(int i=0;i<_next_n;i++){
        field[next_c[i]->_x][next_c[i]->_y]=next[i];
    }
    genNext();

}

void game::startGame(int **fieldv, int *nextv){
    for(int i=0;i<_next_n;i++){
        field[next_c[i]->_x][next_c[i]->_y]=next[i];
    }
    genNext();
    for(int i=0;i<_x;i++){
        for(int j=0;j<_y;j++){
            fieldv[i][j]=field[i][j];
        }
    }
    for(int i=0;i<_next_n;i++){
        nextv[i]=next[i];
    }
}

game::~game()
{
    for(int i=0;i<_x;i++){
        delete[] field[i];
        delete[] temp[i];
    }
    delete[] field;
    delete[] temp;
    for(int i=0;i<_next_n;i++){
        delete next_c[i];
    }
    delete[] next_c;
    delete[] next;
}

void game::random(point* &here)
{
    if(checkForEmpty()){
        bool yep=false;
        while(!yep){
            int xt=rand()%_x;
            int yt=rand()%_y;
            if(0==field[xt][yt]){
                here->_x=xt;
                here->_y=yt;
                yep=true;
            }
        }
    }else{
        here->_x=-1;
        here->_y=-1;
    }
}

bool game::inField(const int &x, const int &y){
    bool res=true;
    if(x<0||y<0||x>=_x||y>=_y)res=false;
    return res;
}

bool game::inField(const point &pnt){
    bool res=true;
    if(pnt._x<0||pnt._y<0||pnt._x>=_x||pnt._y>=_y)res=false;
    return res;
}

bool game::checkForEmpty()
{
    for(int i=0;i<_x;i++){
        for(int j=0;j<_y;j++){
            if(!field[i][j])return true;
        }
    }
    return false;
}

void game::dfs(point from)
{
    temp[from._x][from._y]=1;
    for(int i=0;i<4;i++){
        point to;
        switch (i) {
        case 0:
            to._x=from._x;
            to._y=from._y-1;
            break;
        case 1:
            to._x=from._x;
            to._y=from._y+1;
            break;
        case 2:
            to._x=from._x-1;
            to._y=from._y;
            break;
        case 3:
            to._x=from._x+1;
            to._y=from._y;
            break;
        default:
            break;
        }
        if(inField(to))if((0==field[to._x][to._y])&(0==temp[to._x][to._y])){
            dfs(to);
        }
    }
}

void game::clearTemp(){
    for(int i=0;i<_x;i++){
        for(int j=0;j<_y;j++){
            temp[i][j]=0;
        }
    }
}

bool game::findLines(point &from)
{
    bool res=false;
    int tgt = field[from._x][from._y];
    if(tgt<=0)return false;
    int next=tgt;
    int step1=0;
    //vertical find start
    while(tgt==next){
        step1+=1;
        if(inField(from._x-step1,from._y)){
            next=field[from._x-step1][from._y];
        }else{
            next=0;
        };
    }
    next=tgt;
    int step2=0;
    while(tgt==next){
        step2+=1;
        if(inField(from._x+step2,from._y)){
            next=field[from._x+step2][from._y];
        }else{
            next=0;
        };
    }
    int length=step1+step2-1;
    if(length>=_line){
        res=true;
        for(int i=0;i<step1;i++){
            temp[from._x-i][from._y]=1;
        }
        for(int i=0;i<step2;i++){
            temp[from._x+i][from._y]=1;
        }
    }
    //vertical find stop
    //horisontal find start
    next=tgt;
    step1=0;
    while(tgt==next){
        step1+=1;
        if(inField(from._x,from._y-step1)){
            next=field[from._x][from._y-step1];
        }else{
            next=0;
        };
    }
    next=tgt;
    step2=0;
    while(tgt==next){
        step2+=1;
        if(inField(from._x,from._y+step2)){
            next=field[from._x][from._y+step2];
        }else{
            next=0;
        };
    }
    length=step1+step2-1;
    if(length>=_line){
        res=true;
        for(int i=0;i<step1;i++){
            temp[from._x][from._y-i]=1;
        }
        for(int i=0;i<step2;i++){
            temp[from._x][from._y+i]=1;
        }
    }
    //horisontal find stop
    //lefd diagonal find start
    next=tgt;
    step1=0;
    while(tgt==next){
        step1+=1;
        if(inField(from._x-step1,from._y-step1)){
            next=field[from._x-step1][from._y-step1];
        }else{
            next=0;
        };
    }
    next=tgt;
    step2=0;
    while(tgt==next){
        step2+=1;
        if(inField(from._x+step2,from._y+step2)){
            next=field[from._x+step2][from._y+step2];
        }else{
            next=0;
        };
    }
    length=step1+step2-1;
    if(length>=_line){
        res=true;
        for(int i=0;i<step1;i++){
            temp[from._x-i][from._y-i]=1;
        }
        for(int i=0;i<step2;i++){
            temp[from._x+i][from._y+i]=1;
        }
    }
    //left diagonal find stop
    //right diagonal find start
    next=tgt;
    step1=0;
    while(tgt==next){
        step1+=1;
        if(inField(from._x+step1,from._y-step1)){
            next=field[from._x+step1][from._y-step1];
        }else{
            next=0;
        };
    }
    next=tgt;
    step2=0;
    while(tgt==next){
        step2+=1;
        if(inField(from._x-step2,from._y+step2)){
            next=field[from._x-step2][from._y+step2];
        }else{
            next=0;
        };
    }
    length=step1+step2-1;
    if(length>=_line){
        res=true;
        for(int i=0;i<step1;i++){
            temp[from._x+i][from._y-i]=1;
        }
        for(int i=0;i<step2;i++){
            temp[from._x-i][from._y+i]=1;
        }
    }
    //right diagonal find stop
    return res;
}

void game::delLines(){
    for(int i=0;i<_x;i++){
        for(int j=0;j<_y;j++){
            if(1==temp[i][j]){
                _score+=SCORE_BONUS;
                field[i][j]=0;
            }
        }
    }
    clearTemp();
}

bool game::genNext(){
    point* nxt;
    for(int i=0;i<_next_n;i++){
        next[i]=rand()%_colors+1;
        nxt=new point;
        random(nxt);
        if(-1==nxt->_x)return false;
        field[nxt->_x][nxt->_y]=-1;
        next_c[i]->_x=nxt->_x;
        next_c[i]->_y=nxt->_y;
        delete nxt;
    }
    for(int i=0; i<_next_n;i++){
        field[next_c[i]->_x][next_c[i]->_y]=0;
    }
    return true;
}

bool game::isFineshed()
{
    return end;
}

bool game::step(int **fieldv, int *nextv, int *scorev, point from, point to)
{
    clearTemp();
    dfs(from);
    temp[from._x][from._y]=0;
    if(1==temp[to._x][to._y]){
        clearTemp();
        field[to._x][to._y]=field[from._x][from._y];
        field[from._x][from._y]=0;
        if(findLines(to)){
            delLines();
        }else{
            int k=0;
            bool bingo=false;
            while(checkForEmpty()&(k<_next_n)){
                if(0!=field[next_c[k]->_x][next_c[k]->_y]){
                    random(next_c[k]);
                }
                field[next_c[k]->_x][next_c[k]->_y]=next[k];
                if(findLines(*next_c[k]))bingo=true;
                k+=1;
            }
            if (bingo) delLines();
            genNext();
        }
        if(!checkForEmpty())end=true;
        for(int i=0;i<_x;i++){
            for(int j=0;j<_y;j++){
                fieldv[i][j]=field[i][j];
            }
        }
        for(int i=0;i<_next_n;i++){
            nextv[i]=next[i];
        }
        *scorev=_score;
    }else{
        return false;
    }

    return true;
}

void game::allowedMoves(int **allowed, point from)
{
    clearTemp();
    dfs(from);
    temp[from._x][from._y]=0;
    for(int i=0;i<_x;i++){
        for(int j=0;j<_y;j++){
            allowed[i][j]=temp[i][j];
        }
    }
}

void game::gimmeField(int **fieldv)
{
    for(int i=0;i<_x;i++){
        for(int j=0;j<_y;j++){
            fieldv[i][j]=field[i][j];
        }
    }
}

void game::gimmeNext(int *nextv)
{
    for(int i=0;i<_next_n;i++){
        nextv[i]=next[i];
    }
}
