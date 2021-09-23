#include "qpaintbox.h"

//QPaintBox::QPaintBox(QWidget *parent) : QWidget(parent)
QPaintBox::QPaintBox(int aWidth, int aHeight, QWidget *parent) : QWidget(parent)
{
    if(parent){
//        this->setGeometry(parent->geometry());
        aWidth = parent->width();
        aHeight = parent->height();
    }

    this->resize(aWidth, aHeight);
    pixelCanvas=new QPixmap(aWidth, aHeight);
    pixelCanvas->fill(Qt::black);
}
//------------------------------------------------------------------------------
void QPaintBox::paintEvent(QPaintEvent * /* event */){
    QPainter Canvas(this);

    Canvas.drawPixmap(0,0,*pixelCanvas);

}
//------------------------------------------------------------------------------
void QPaintBox::resizeEvent(QResizeEvent */* event */){
    QPixmap aux(this->width(), this->height());

    aux.copy(pixelCanvas->rect());
    pixelCanvas->scaled(aux.width(), aux.height());
    pixelCanvas->swap(aux);
}
//------------------------------------------------------------------------------
void QPaintBox::setWidth(int aWidth){
    pixelCanvas->size().setWidth(aWidth);
    this->resize(aWidth, this->height());
}
//------------------------------------------------------------------------------
void QPaintBox::setHeight(int aHeight){
    pixelCanvas->size().setWidth(aHeight);
    this->resize(this->width(), aHeight);
}
//------------------------------------------------------------------------------
void QPaintBox::mousePressEvent(QMouseEvent *event){
    emit(OnMousePress(event));
}
//------------------------------------------------------------------------------
void QPaintBox::mouseReleaseEvent(QMouseEvent *event){
    emit(OnMouseRelease(event));
}
//------------------------------------------------------------------------------
void QPaintBox::mouseMoveEvent(QMouseEvent *event){
    emit(OnMouseMove(event));
}
//------------------------------------------------------------------------------
QPixmap *QPaintBox::getCanvas(){
    return pixelCanvas;
}
//------------------------------------------------------------------------------

