#include "widget.h"
#include "ui_widget.h"

void Widget::imageIni()
{
    if(!(white_backg.load("/Users/chenziwei/Qt project/AI_AlphaBetaPurningAlgo/white_image.jpg"))) { //加载图像
        qDebug()<<"cant open this image"<<endl;
        //QMessageBox message(QMessageBox::Warning,"Information","cant open this image",QMessageBox::Yes|QMessageBox::No,NULL);
//        delete white_backg;
//        return;
    }

    white_backg = ScaleImage2Label(white_backg, ui->label_chessboard1);

    QImage temp = white_backg;
    QPainter painter(&temp);
    QPen my_pen;
    my_pen.setWidth(4); //设置线宽
    my_pen.setColor(Qt::green); //设置颜色
//    my_pen.setColor(QColor(14, 9, 234) );//rgb设置颜色
//    my_pen.setStyle(Qt::DashLine); //设置风格
    painter.setPen(my_pen);
    painter.drawLine(0,0,white_backg.width(),white_backg.height());
    painter.drawLine(white_backg.width(),0,0,white_backg.height());
    painter.end();
    CompChess = temp;

    temp = white_backg;
    painter.begin(&temp);
    painter.setPen(my_pen);
    painter.drawEllipse(QPoint(temp.width()/2,temp.height()/2),temp.width()/2 ,temp.height()/2);
    painter.end();
    HumanChess = temp;

//把列表控件放到一个vector里面方便管理
    my_chessboard_lable.push_back(ui->label_chessboard1);
    my_chessboard_lable.push_back(ui->label_chessboard2);
    my_chessboard_lable.push_back(ui->label_chessboard3);
    my_chessboard_lable.push_back(ui->label_chessboard4);
    my_chessboard_lable.push_back(ui->label_chessboard5);
    my_chessboard_lable.push_back(ui->label_chessboard6);
    my_chessboard_lable.push_back(ui->label_chessboard7);
    my_chessboard_lable.push_back(ui->label_chessboard8);
    my_chessboard_lable.push_back(ui->label_chessboard9);
    for(int i = 0; i < my_chessboard_lable.size(); ++i){
        my_chessboard_lable[i]->setPixmap(QPixmap::fromImage(white_backg));
    }
}
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    imageIni();//制作好圆圈图和叉叉图




}
void Widget::mousePressEvent(QMouseEvent *event)
{//单击
    // 如果是鼠标左键按下
    if (event->button() == Qt::LeftButton){
        for(int i = 0; i < my_chessboard_lable.size(); ++i){
            if(my_chessboard_lable[i]->geometry().contains(this->mapFromGlobal(QCursor::pos()))){
                qDebug()<<"在该控件"<<i<<endl;
                if(choose_first == 0){
                    qDebug()<<"请选择电脑或者人先手"<<endl;
                    return;
                }
                my_chessboard_lable[i]->setPixmap(QPixmap::fromImage(HumanChess));
                my_algo.chessboard[i] = -1;//下棋
                int pos = my_algo.QT_gameStart(game_win);
                if (game_win == 1&&pos == INT_MIN){
                    qDebug()<<"人赢了"<<endl;
                    return;
                }
                else if(game_win == 1){
                    my_chessboard_lable[pos]->setPixmap(QPixmap::fromImage(CompChess));
                    qDebug()<<"电脑赢了"<<endl;
                    return;
                }
                if(pos == -2){
                    qDebug()<<"打平了"<<endl;
                    return;
                }
                my_chessboard_lable[pos]->setPixmap(QPixmap::fromImage(CompChess));
            }
        }
    }
//    // 如果是鼠标右键按下
//    else if (event->button() == Qt::RightButton){
//        qDebug() << "right click";
//    }

}
Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_compFirst_clicked()
{
    for(int i = 0; i < my_chessboard_lable.size(); ++i){
        my_chessboard_lable[i]->setPixmap(QPixmap::fromImage(white_backg));
    }
    choose_first = 1;
    my_algo.QT_clear();
    int pos = my_algo.QT_gameStart(game_win);
    my_chessboard_lable[pos]->setPixmap(QPixmap::fromImage(CompChess));
}

void Widget::on_pushButton_humanFirst_clicked()
{
    for(int i = 0; i < my_chessboard_lable.size(); ++i){
        my_chessboard_lable[i]->setPixmap(QPixmap::fromImage(white_backg));
    }
    choose_first = 1;
    my_algo.QT_clear();
}
