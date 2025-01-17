/**
 *  @brief
 *  @details
 *  @author    Ludovic A. 
 *  @date      2015 /2016/2017/2018
 *  @bug       No known bugs
 *  @copyright GNU Public License v3
 */

#include <QPen>
#include <QBrush>
#include <QDebug>

#include "item_scaleruler.h"

Item_scaleRuler::Item_scaleRuler(QGraphicsItem * parent) :
    QGraphicsLineItem(parent)
{
    QPen pen;
    pen.setColor(Qt::yellow);
    pen.setWidth(5);
    pen.setStyle(Qt::DotLine);
    pen.setCosmetic(true);//Very important to keep it visible when zooming out.
    pen.setCapStyle(Qt::FlatCap);
    setPen(pen);

    reset();
}


void Item_scaleRuler::reset()
{
    setLine(-50000, -50000, -50000, -50000);
    remainingClicks = 2;
}


void Item_scaleRuler::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (remainingClicks == 2)
    {
        //Set the starting point of the ruler
        origin = event->scenePos();
        setLine(origin.x(),origin.y(),origin.x(),origin.y());

    }

    remainingClicks--;

    if (remainingClicks == 0)
        //reset to allow for a new drawing
        remainingClicks = 2;

}


void Item_scaleRuler::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (remainingClicks == 1)
    {
        setLine(origin.x(),origin.y(),(event->scenePos()).x(),(event->scenePos()).y());
        emit newMeasure(line().length());
    }
}
