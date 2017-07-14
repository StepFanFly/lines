#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    _size = 40;
    ui->setupUi(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::clearTemp(){
    for(int i=0;i<_num_x;i++){
        for(int j=0;j<_num_y;j++){
            temp[i][j]=0;
        }
    }
}

void MainWindow::slot1(int x,int y,int type){
    if(!m_game->isFineshed()){
        if(type>0){

            _smth_pressed=true;
            _pressed._x=x;
            _pressed._y=y;
            m_game->gimmeField(temp);
            for(int i=0;i<_num_x;i++){
                for(int j=0;j<_num_y;j++){
                    elems[i][j]->setPressed(false);
                    elems[i][j]->setType(temp[i][j]);
                }
            }
            elems[x][y]->setPressed(true);
            clearTemp();
            m_game->allowedMoves(temp,_pressed);
            QString tmp;
            for(int i=0;i<_num_x;i++){
                tmp.clear();
                for(int j=0;j<_num_y;j++){

                    if(1==temp[i][j])elems[i][j]->setType(-1);
                    tmp.append(QString::number(temp[i][j]));
                    tmp.append("-");
                }
                qDebug()<<tmp;
            }
        }else{
            if(_smth_pressed){
                clearTemp();
                point to={x,y};
                if(m_game->step(temp,next,&_score,_pressed,to)){
                    ui->lcdNumber->display(_score);
                    qDebug()<<_score;
                    for(int i=0;i<_num_x;i++){
                        for(int j=0;j<_num_y;j++){
                            elems[i][j]->setPressed(false);
                            elems[i][j]->setType(temp[i][j]);
                        }
                    }
                }
            }
        }
    }else{
        QMessageBox msg;
        msg.setStyleSheet("QLabel{min-width: 120px}");
        msg.setWindowTitle("Game over pal");
        msg.setText("Счет: "+QString::number(_score));
        msg.exec();
    }
    scene->update();
}

void MainWindow::on_accepted(int x, int y, int next_n, int colors, int in_line)
{
    if(!next)delete[] next;
    if(!scene)delete scene;
    if(!m_game)delete m_game;
    if(!elems){
        for(int i=0;i<_num_x;i++){
            for(int j=0;j<_num_y;j++){
                delete elems[i][j];
            }
            delete[] elems[i];
        }
        delete[] elems;
    }
    if(!temp){
        for(int i=0;i<_num_x;i++){
            delete[] temp[i];
        }
        delete[] temp;
    }
    ui->lcdNumber->display(0);
    next=new int[_next_n];
    _smth_pressed=false;
    _num_x=x;
    _num_y=y;
    _score=0;
    _next_n=next_n;
    _colors=colors;
    _in_line=in_line;
    int t_x=_num_x*_size;
    int t_y=_num_y*_size;
    scene= new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0,0,t_x,t_y);
    QColor r1;
    r1.setHsv(0,0,75);
    QPen rpan;
    rpan.setColor(r1);
    QBrush wbr;
    wbr.setColor(r1);
    scene->addRect(0,0,scene->width(),scene->height(),rpan,wbr);
    m_game = new game(x,y,next_n,colors,in_line);
    temp=new int*[_num_x];
    elems = new gridElem** [_num_x];
    for(int i=0;i<_num_x;i++){
        temp[i]=new int[_num_y];
        elems[i]=new gridElem*[_num_y];
        for(int j=0;j<_num_y;j++){
            elems[i][j]=new gridElem(scene,_size,0,_colors);
            scene->addItem(elems[i][j]);
            elems[i][j]->moveTo(i,j);
            elems[i][j]->setPos(i*_size,j*_size);
            connect(elems[i][j], SIGNAL(signal1(int,int,int)),this,SLOT(slot1(int,int,int)));
        }
    }
    m_game->gimmeField(temp);
    m_game->gimmeNext(next);
    for(int i=0;i<_num_x;i++){
        for(int j=0;j<_num_y;j++){
            elems[i][j]->setType(temp[i][j]);
        }
    }
    show();
}

void MainWindow::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    //ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
    QBrush brh;
    QColor tmp;
    tmp.setHsv(0,0,75);
    brh.setColor(tmp);
    //ui->graphicsView->setBackgroundBrush(brh);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    setupDialog *ask;
    ask=new setupDialog;
    connect(ask,SIGNAL(omg_hide()),this,SLOT(omg_hide()));
    ask->show();
    connect(ask,SIGNAL(on_accepted(int,int,int,int,int)),this,SLOT(on_accepted(int,int,int,int,int)));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "Закрыть",
                          "Уверены?",
                          QMessageBox::Yes|QMessageBox::No))
    {
    event->accept();
    }
}

void MainWindow::omg_hide()
{
    this->hide();
}

void MainWindow::on_pushButton_2_clicked()
{
    close();
}