#ifndef WIDGET_H
#define WIDGET_H
#include"AlphaBetaPurningAlgo.hpp"
#include <QWidget>
#include <qcursor.h>
#include <QDebug>
#include <QMouseEvent>
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QImage>
#include <QPixmap>
#include <QSize>


using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    AlphaBetaPurningAlgo my_algo;
    bool game_win = 0;
    bool choose_first = 0;
    QImage white_backg;
    QImage CompChess;//叉
    QImage HumanChess; //圆
    vector<QLabel*>my_chessboard_lable;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void mousePressEvent(QMouseEvent *event);        //单击
//    void paintEvent(QPaintEvent *e, int pos);
    QImage ScaleImage2Label(QImage qImage, QLabel* qLabel)
    {
        QImage qScaledImage;
        QSize qImageSize = qImage.size();
//        qDebug()<<qImage.size()<<endl;
        QSize qLabelSize = qLabel->size();
//        qDebug()<<qLabel->size()<<endl;
        double dWidthRatio = 1.0*qImageSize.width() / qLabelSize.width();
        double dHeightRatio = 1.0*qImageSize.height() / qLabelSize.height();
        if (dWidthRatio>dHeightRatio) {
            qScaledImage = qImage.scaledToWidth(qLabelSize.width());
        }
        else {
            qScaledImage = qImage.scaledToHeight(qLabelSize.height());
        }
        return qScaledImage;
    }
    void imageIni();

private slots:
    void on_pushButton_compFirst_clicked();

    void on_pushButton_humanFirst_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
