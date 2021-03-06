#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gridelem.h"
#include "setupdialog.h"
#include "game.h"
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    gridElem* **elems;
    game *m_game;
    int** temp;
    int* next;
    gridElem* *next_elems;
    QGraphicsScene *scene_next;
    int _num_x;
    int _num_y;
    int _size;//grid size px
    int _next_n;//new balls count
    int _colors;//how many colors
    int _in_line;//how many balls in line
    bool _smth_pressed;
    point _pressed;
    int _score;
    setupDialog *ask;
    void gameLoop();
    void clearTemp();
private slots:
    void slot1(int x,int y,int type);
    void on_accepted(int x, int y, int next_n, int colors, int in_line);
    void on_pushButton_clicked();
    void omg_hide();
    void on_pushButton_2_clicked();
    void on_rejected();
    void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_H
