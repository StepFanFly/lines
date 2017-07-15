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
    ui->graphicsView_score->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_score->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    next=NULL;
    scene=NULL;
    elems=NULL;
    m_game=NULL;
    temp=NULL;
    next_elems=NULL;
    scene_next=NULL;
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
            for(int i=0;i<_num_x;i++){
                for(int j=0;j<_num_y;j++){
                    if(1==temp[i][j])elems[i][j]->setType(-1);
                }
            }

        }else{
            if(_smth_pressed){
                clearTemp();
                point to={x,y};
                if(m_game->step(temp,next,&_score,_pressed,to)){
                    ui->lcdnumber->display(_score);
                    for(int i=0;i<_next_n;i++){
                        next_elems[i]->setType(next[i]);
                    }
                    for(int i=0;i<_next_n;i++){
                        next_elems[i]=new gridElem(scene_next,_size,next[i],_colors);
                        scene_next->addItem(next_elems[i]);
                        next_elems[i]->setPos(i*_size,0);
                    }
                    m_game->gimmeField(temp);
                    for(int i=0;i<_num_x;i++){
                        for(int j=0;j<_num_y;j++){
                            elems[i][j]->setPressed(false);
                            elems[i][j]->setType(temp[i][j]);
                        }
                    }
                }

                _smth_pressed=false;
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
    if(NULL!=next)delete[] next;
    if(NULL!=scene)delete scene;
    if(NULL!=m_game)delete m_game;
    if(NULL!=next_elems)delete next_elems;
    if(NULL!=elems){
        for(int i=0;i<_num_x;i++){
            delete[] elems[i];
        }
        delete[] elems;
    }
    if(NULL!=temp){
        for(int i=0;i<_num_x;i++){
            delete[] temp[i];
        }
        delete[] temp;
    }
    ui->lcdnumber->display(0);
    _smth_pressed=false;
    _num_x=x;
    _num_y=y;
    _score=0;
    _next_n=next_n;
    _colors=colors;
    _in_line=in_line;
    int t_x=_num_x*_size;
    int t_y=_num_y*_size;
    next=new int[_next_n];
    next_elems=new gridElem*[_next_n];
    scene= new QGraphicsScene();
    scene_next=new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView_score->setScene(scene_next);
    scene->setSceneRect(0,0,t_x,t_y);
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
    ui->graphicsView->setMinimumHeight(_size*_num_y+2);
    ui->graphicsView->setMinimumWidth(_size*_num_x+2);
    ui->graphicsView->setMaximumHeight(_size*_num_y+2);
    ui->graphicsView->setMaximumWidth(_size*_num_x+2);
    setMinimumHeight(_size*_num_y+84);
    setMaximumHeight(_size*_num_y+64);
    int itmp=_size*_next_n+2+280<_size*_num_x+26?_size*_num_x+26:_size*_next_n+2+280;
    setMinimumWidth(itmp);
    setMaximumWidth(itmp);
    ui->graphicsView_score->setMaximumWidth(_size*_next_n+2);
    ui->graphicsView_score->setMinimumWidth(_size*_next_n+2);
    ui->graphicsView_score->setMinimumHeight(42);
    ui->graphicsView_score->setMaximumHeight(42);
    ui->graphicsView_score->setAlignment(Qt::AlignCenter);
    scene_next->setSceneRect(0,0,_size*_next_n,_size*_next_n);
    for(int i=0;i<_next_n;i++){
        next_elems[i]=new gridElem(scene_next,_size,next[i],_colors);
        scene_next->addItem(next_elems[i]);
        next_elems[i]->setPos(i*_size,0);
    }
    show();
}

void MainWindow::showEvent(QShowEvent *event){
    QWidget::showEvent(event);
    QBrush brh;
    QColor tmp;
    tmp.setHsv(0,0,75);
    brh.setColor(tmp);
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
    connect(ask,SIGNAL(on_rejected()),this,SLOT(on_rejected()));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "Закрыть","Уверены?",QMessageBox::Yes|QMessageBox::No)){
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

void MainWindow::on_rejected()
{
    show();
}
