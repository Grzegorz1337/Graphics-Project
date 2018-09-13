#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QSlider>
namespace Ui
{
    class MyWindow;
}

class MyWindow : public QMainWindow
{  
    Q_OBJECT

public:
    explicit MyWindow(QWidget *parent = 0);
    ~MyWindow();

private:
    Ui::MyWindow *ui;
    QImage *img;
    QImage *front;
    QImage *back;
    QSlider *s;  
    void paintEvent(QPaintEvent*);
    int szer, wys, poczX, poczY;
    int x,y,z;
    int acceleration;
    unsigned char *ptr,*frt,*bck;
    struct point {int x; int y; int z;};
    point sc,sf,sb;
    std::vector <point> walls;
    std::vector <point> text;
    void drawLine(double, double, double, double);
    void addPoint(int, int, int);
    void addTexturePoint(int,int);
    struct cube {point a,b,c,d,e,f,g,h;};
    int translationX, translationY, translationZ,  halfImgX = szer/2,halfImgY=wys/2, hAlp_X, hAlp_Y, hAlp_Z, edgeLength;
    double scaleX,scaleY,scaleZ, rotateOX, rotateOY, rotateOZ;
    void drawEdges(unsigned char *src);
    void rotate(int j,int d);
    void setPoints();
    void texture(point a,point b,point c,point at,point bt,point ct,unsigned char *src);
    void setTexture();
    void setPixelColor(int x, int y, int r, int g, int b);
    int getPixelColor(int x, int y, char part,unsigned char *src);
    void fill(unsigned char* src);

private slots:
    void on_quit_clicked();
    void on_reset_clicked();
    void somethingHappened(int k);
};

#endif
