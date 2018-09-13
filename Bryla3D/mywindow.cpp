#include "mywindow.h"
#include "ui_mywindow.h"
#include "iostream"
#include "cmath"
#include "vector"
#include "cstdlib"
#include "ctime"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    ui -> setupUi(this);
    acceleration=1;
    szer = ui -> frame -> width();
    wys = ui -> frame -> height();
    poczX = ui -> frame -> x();
    poczY = ui -> frame -> y();
    x=0;
    y=0;
    z=0;
    img = new QImage(szer, wys, QImage::Format_RGB32);
    img -> fill(QColor(Qt::black).rgb());
    front=new QImage();
    back=new QImage();
    front->load("kopernik.jpg");
    back->load("chill.jpg");
    ptr = img -> bits();
    frt = front->bits();
    bck = back->bits();
    sc.x= img->width()/2;
    sc.y = img->height()/2;
    sf.x = front->width()/2;
    sf.y = front->height()/2;
    sb.x = back->width()/2;
    sb.y = back->width()/2;
    setTexture();
    setPoints();
    drawEdges(frt);
}

MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::on_quit_clicked()
{
    qApp -> quit();
}

void MyWindow::on_reset_clicked()
{
    acceleration=1;
    somethingHappened(1);
}

void MyWindow::somethingHappened(int k)
{
    unsigned char* source = frt;;
    for(int i=0;i<6+rand()%6;i++){
        for(int j=0;j<=100;j++){
            usleep(acceleration);
            img -> fill(QColor(Qt::black).rgb());
            setPoints();
            rotate(j,1);
            if(j==25) source=bck;
            if(j==75) source=frt;
            drawEdges(source);

            acceleration+=1+(rand()%10);
            repaint();
        }
    }
}

void MyWindow::rotate(int j,int d)
{
    int halfImgX = szer / 2, halfImgY = wys / 2, hAlp_X, hAlp_Y, hAlp_Z, edgeLength;
    edgeLength = 150;

    for (unsigned int i = 0; i <= walls.size() - 1; i++)
    {
        walls[i].x -=halfImgX;
        walls[i].y -=halfImgY;
            hAlp_X = ((walls[i].x * cos(M_PI/50*j)) + (walls[i].z * sin(M_PI/50*j)));
            hAlp_Z = (((-1 * walls[i].x) * sin(M_PI/50*j)) + (walls[i].z * cos(M_PI/50*j)));
            walls[i].x = hAlp_X;
            walls[i].z = hAlp_Z;
        walls[i].x +=halfImgX;
        walls[i].y +=halfImgY;
    }
}


void MyWindow::paintEvent(QPaintEvent*)
{

    QPainter p(this);
    p.drawImage(8,88,*img);
}

void MyWindow::setTexture()
{
    double r1 = front->width()/2;
    double r2 = back->width()/2;
    double aJump = (2*M_PI/18.0);
    double phi = aJump;
    int xa1,ya1,xa2,ya2;
    int x_1=r1;
    int y_1=0;
    int x_2=r2;
    int y_2=0;
    for(int i=0;i<=360/18;i++,phi+=aJump)
    {
        xa1 = r1*cos(phi);
        ya1 = r1*sin(phi);
        addTexturePoint(x_1+(front->width()/2),(front->height()/2)-y_1);
        addTexturePoint(xa1+(front->width()/2),(front->height()/2)-ya1);
        x_1=xa1;
        y_1=ya1;

        xa2 = r2*cos(phi);
        ya2 = r2*sin(phi);
        addTexturePoint(x_2+(back->width()/2),(back->height()/2)-y_2);
        addTexturePoint(xa2+(back->width()/2),(back->height()/2)-ya2 );
        x_2=xa2;
        y_2=ya2;
    }
}

void MyWindow::setPoints()
{
    int halfImgX = szer / 2, halfImgY = wys / 2, edgeLength;
    edgeLength = 200;
    int x1=halfImgX,x2=halfImgX+(edgeLength/2),y1=halfImgY,y2=halfImgY;
    double r = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
    int xa,ya;
    int x = r;
    int y = 0;
    double aJump = (2*M_PI/18.0);
    double phi = aJump;
    for(int i=0;i<=360/18;i++,phi+=aJump)
        {
            xa = r*cos(phi);
            ya = r*sin(phi);
            addPoint(x+x1,y1-y,0);
            addPoint(xa+x1,y1-ya,0);
            addPoint(x+x1,y1-y,(edgeLength/2)*0.01);
            addPoint(xa+x1,y1-ya,(edgeLength/2)*0.01);
            addPoint(x+x1,y1-y,(edgeLength/2)*0.02);
            addPoint(xa+x1,y1-ya,(edgeLength/2)*0.02);
            addPoint(x+x1,y1-y,(edgeLength/2)*0.03);
            addPoint(xa+x1,y1-ya,(edgeLength/2)*0.03);
            addPoint(x+x1,y1-y,(edgeLength/2)*0.04);
            addPoint(xa+x1,y1-ya,(edgeLength/2)*0.04);
            addPoint(x+x1,y1-y,(edgeLength/2)*0.05);
            addPoint(xa+x1,y1-ya,(edgeLength/2)*0.05);
            x=xa;
            y=ya;
        }
    for (unsigned int i = 0; i <= walls.size() - 1; i++)
    {
        //3D -> 2D
        walls[i].x = (walls[i].x / ((walls[i].z / 1000.0) + 1.0));
        walls[i].y = (walls[i].y / ((walls[i].z / 1000.0) + 1.0));
    }

}

void MyWindow::drawEdges(unsigned char *src)
{
    for(int i=0;i<walls.size();i+=12)
    {
        drawLine(walls[i].x,walls[i].y,walls[i+1].x,walls[i+1].y);
        drawLine(walls[i+2].x,walls[i+2].y,walls[i+3].x,walls[i+3].y);
        drawLine(walls[i+4].x,walls[i+4].y,walls[i+5].x,walls[i+5].y);
        drawLine(walls[i+6].x,walls[i+6].y,walls[i+7].x,walls[i+7].y);
        drawLine(walls[i+8].x,walls[i+8].y,walls[i+9].x,walls[i+9].y);
        drawLine(walls[i+10].x,walls[i+10].y,walls[i+11].x,walls[i+11].y);
    }
    for(int i=0;i<text.size();i+=4)
    {
        texture(walls[3*i],walls[3*i+1],sc,text[i],text[i+1],sf,src);
    }
    walls.clear();
    //update();
}

void MyWindow::addPoint(int x, int y, int z)
{
    walls.push_back(point());
    walls[walls.size() - 1].x = x;
    walls[walls.size() - 1].y = y;
    walls[walls.size() - 1].z = z;
}

void MyWindow::addTexturePoint(int x,int y)
{
    text.push_back(point());
    text[text.size()-1].x = x;
    text[text.size()-1].y = y;
    text[text.size()-1].z = 0;
}


void MyWindow::drawLine(double x1,double y1,double x2,double y2)
{
    int i,j,inx,iny;
    unsigned char *ptr;
    double a,b;
    a = ((y1-y2)*1.0)/((x1-x2)*1.0);
    b = (y1-((((y1-y2)*1.0)/((x1-x2)*1.0))*x1));
    inx = (x1<x2)?1:-1;
    iny = (y1<y2)?1:-1;
    for (j=y1;j!=y2;j+=iny)
    {
        ptr=img->scanLine(j);
        for (i=x1;i!=x2;i+=inx)
        {
            if(((a*i+b>=j-abs(a)) && (a*i+b<=j+abs(a))) || (((a*i+b>=j-1) && (a*i+b<=j+1))))
            {
               ptr[i*4]=0;
               ptr[i*4+1]=255;
               ptr[i*4+2]=255;
            }
        }
        if(x1==x2)
        {
            ptr[(int)x1*4]=0;
            ptr[(int)x1*4+1]=255;
            ptr[(int)x1*4+2]=255;
        }
    }
    if(y1==y2)
    {
        ptr=img->scanLine(y1);
        for (i=x1;i!=x2;i+=inx)
        {
            if(((a*i+b>=j-abs(a)) && (a*i+b<=j+abs(a))) || (((a*i+b>=j-1) && (a*i+b<=j+1))))
            {
               ptr[i*4]=0;
               ptr[i*4+1]=255;
               ptr[i*4+2]=255;
            }
        }
    }
}

void MyWindow::texture(point a,point b,point c,point at,point bt,point ct,unsigned char *src)
{
    int min_X = a.x;
    int max_X = a.x;
    int min_Y = a.y;
    int max_Y = a.y;
    int interpolation_R, interpolation_G, interpolation_B;
    point A = a, B = b, C = c, At = at, Bt = bt, Ct = ct;
    double u, v, w, Xt, Yt;
    if(min_X>b.x) min_X=b.x;
    if(min_X>c.x) min_X=c.x;
    if(max_X<b.x) max_X=b.x;
    if(max_X<c.x) max_X=c.x;
    if(min_Y>b.y) min_Y=b.y;
    if(min_Y>c.y) min_Y=c.y;
    if(max_Y<b.y) max_Y=b.y;
    if(max_Y<c.y) max_Y=c.y;
    for (int i = min_Y; i <= max_Y; i++)
    {
        for (int j = min_X; j <= max_X; j++)
        {
            v = (double)((((j - A.x) * (C.y - A.y)) - ((C.x - A.x) * (i - A.y)))*1.0) / ((((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y)))*1.0);
            w = (double)((((B.x - A.x) * (i - A.y)) - ((j - A.x) * (B.y - A.y)))*1.0) / ((((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y)))*1.0);
            u = 1.0 - v - w;
            if (u > 0 && u < 1 && v > 0 && v < 1 && w > 0 && w < 1)
            {
                Xt = u * At.x + v * Bt.x + w * Ct.x;
                Yt = u * At.y + v * Bt.y + w * Ct.y;

                interpolation_R = (Yt - floor(Yt)) * ((1 - (Xt - floor(Xt))) * getPixelColor(floor(Xt), floor(Yt) + 1, 'r',src) + (Xt - floor(Xt)) * getPixelColor(floor(Xt) + 1, floor(Yt) + 1, 'r',src)) + (1 - (Yt - floor(Yt))) * ((1 - (Xt - floor(Xt))) * getPixelColor(floor(Xt), floor(Yt), 'r',src) + (Xt - floor(Xt)) * getPixelColor(floor(Xt) + 1, floor(Yt), 'r',src));
                interpolation_G = (Yt - floor(Yt)) * ((1 - (Xt - floor(Xt))) * getPixelColor(floor(Xt), floor(Yt) + 1, 'g',src) + (Xt - floor(Xt)) * getPixelColor(floor(Xt) + 1, floor(Yt) + 1, 'g',src)) + (1 - (Yt - floor(Yt))) * ((1 - (Xt - floor(Xt))) * getPixelColor(floor(Xt), floor(Yt), 'g',src) + (Xt - floor(Xt)) * getPixelColor(floor(Xt) + 1, floor(Yt), 'g',src));
                interpolation_B = (Yt - floor(Yt)) * ((1 - (Xt - floor(Xt))) * getPixelColor(floor(Xt), floor(Yt) + 1, 'b',src) + (Xt - floor(Xt)) * getPixelColor(floor(Xt) + 1, floor(Yt) + 1, 'b',src)) + (1 - (Yt - floor(Yt))) * ((1 - (Xt - floor(Xt))) * getPixelColor(floor(Xt), floor(Yt), 'b',src) + (Xt - floor(Xt)) * getPixelColor(floor(Xt) + 1, floor(Yt), 'b',src));

                setPixelColor(j, i, interpolation_R, interpolation_G, interpolation_B);
            }
        }
    }
}

void MyWindow::setPixelColor(int x, int y, int r, int g, int b)
{
    if ((x >= 0) && (y >= 0) && (x < szer) && (y < szer))
    {

        ptr[szer*4*y + 4*x + 2] = r;
        ptr[szer*4*y + 4*x + 1] = g;
        ptr[szer*4*y + 4*x] = b;
    }
}

int MyWindow::getPixelColor(int x, int y, char part,unsigned char *src)
{
    if((x >= 0) && (y >= 0) && (x < back->width()) && (y < back->height())){
    if (src==frt)
    {
        switch (part)
        {
            case 'r':
                return frt[front->width()*4*y + 4*x + 2];
                break;
            case 'g':
                return frt[front->width()*4*y + 4*x + 1];
                break;
            case 'b':
                return frt[front->width()*4*y + 4*x];
                break;
        }
    }
    else
    {
        switch (part)
        {
            case 'r':
                return bck[back->width()*4*y + 4*x + 2];
                break;
            case 'g':
                return bck[back->width()*4*y + 4*x + 1];
                break;
            case 'b':
                return bck[back->width()*4*y + 4*x];
                break;
        }
    }
    }
    return 0;
}
