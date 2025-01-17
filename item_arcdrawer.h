/**
 *  @brief
 *  @details
 *  @author    Ludovic A. 
 *  @date      2015 /2016/2017/2018
 *  @bug       No known bugs
 *  @copyright GNU Public License v3
 */

#ifndef ITEM_ARCDRAWER_H
#define ITEM_ARCDRAWER_H

#include <QAbstractGraphicsShapeItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

#include "item_arc.h"
#include "item_circle.h"
#include "item_line.h"
#include "gribouillotitem.h"


class Item_arcDrawer : public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT

public:
    enum { Type = ARC_DRAWER };
    int type() const
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return ARC_DRAWER;
    }

    explicit Item_arcDrawer(Item_circle* circle);
    explicit Item_arcDrawer(QColor penColor, int penWidth, QPointF center, QPointF radiusPoint);
    explicit Item_arcDrawer(QColor penColor, int penWidth, int windowSize, QPointF center,
                            QLineF sourceLine);
    explicit Item_arcDrawer(int windowSize, QPointF center, QLineF sourceLine);
    explicit Item_arcDrawer(QPointF center, QSizeF picSize);
    ~Item_arcDrawer(){}

    Item_arc* getArc();
    Item_circle* getSourceCircle();
    QLineF getAngledLine();

signals:
    void newMeasure(qreal spanAngle);

protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;
    void mousePressEvent(QGraphicsSceneMouseEvent * event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event) Q_DECL_OVERRIDE;

private:
    qreal startAngle;
    qreal spanAngle;
    qreal radius;
    qreal bRadius;

    QLineF firstVector;
    QLineF secondVector;
    QPointF mouseMovePos;
    bool paintArc = true;
    bool startClockwise = false;

    bool isProtractor = false;

    Item_circle* sourceCircle = nullptr;

};

#endif // ITEM_ARCDRAWER_H
