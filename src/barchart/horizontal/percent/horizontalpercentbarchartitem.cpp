/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "horizontalpercentbarchartitem_p.h"
#include "qabstractbarseries_p.h"
#include "qbarset_p.h"
#include "bar_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

HorizontalPercentBarChartItem::HorizontalPercentBarChartItem(QAbstractBarSeries *series, QGraphicsItem* item)
    : AbstractBarChartItem(series, item)
{
}

QVector<QRectF> HorizontalPercentBarChartItem::calculateLayout()
{
    QVector<QRectF> layout;

    // Use temporary qreals for accuracy
    qreal categoryCount = m_series->d_func()->categoryCount();
    qreal setCount = m_series->count();
//    bool barsVisible = m_series->isVisible();

    qreal barWidth = m_series->d_func()->barWidth();

    for(int category = 0; category < categoryCount; category++) {
        qreal sum = 0;
        qreal categorySum = m_series->d_func()->categorySum(category);
        for (int set = 0; set < setCount; set++) {
            qreal value = m_series->barSets().at(set)->at(category);
            QRectF rect;
            QPointF topLeft;
            if (domain()->type() == AbstractDomain::LogXYDomain
                    || domain()->type() == AbstractDomain::LogXLogYDomain)
                topLeft = domain()->calculateGeometryPoint(QPointF(set ? 100 * sum/categorySum : domain()->minX(), category + barWidth/2));
            else
                topLeft = domain()->calculateGeometryPoint(QPointF(set ? 100 * sum/categorySum : 0, category + barWidth/2));
            QPointF bottomRight = domain()->calculateGeometryPoint(QPointF(100 * (value + sum)/categorySum, category - barWidth/2));
            rect.setTopLeft(topLeft);
            rect.setBottomRight(bottomRight);
            layout.append(rect);
            sum +=value;
        }
    }

//    // AbstractDomain:
//    qreal width = geometry().width();
//    qreal height = geometry().height();
//    qreal rangeY = m_domainMaxY - m_domainMinY;
//    qreal rangeX = m_domainMaxX - m_domainMinX;
//    qreal scaleY = (height / rangeY);
//    qreal scaleX = (width / rangeX);
//    qreal rectHeight = scaleY * m_series->d_func()->barWidth(); // On horizontal chart barWidth of the barseries means height of the rect.

//    int itemIndex(0);
//    for (int category = 0; category < categoryCount; category++) {
//        qreal colSum = m_series->d_func()->categorySum(category);
//        qreal percentage = (100 / colSum);
//        qreal xPos = -scaleX * m_domainMinX + geometry().left();
//        for (int set = 0; set < setCount; set++) {
//            QBarSetPrivate *barSet = m_series->d_func()->barsetAt(set)->d_ptr.data();

//            qreal yPos = (m_domainMinY + 0.5 - barSet->pos(category)) * scaleY + geometry().bottom() - rectHeight / 2;

//            qreal rectWidth = barSet->value(category) * percentage * scaleX;
//            Bar *bar = m_bars.at(itemIndex);

//            QRectF rect(xPos, yPos - rectHeight, rectWidth, rectHeight);
//            layout.append(rect);
//            bar->setPen(barSet->m_pen);
//            bar->setBrush(barSet->m_brush);
//            if (qFuzzyCompare(rectHeight, 0))
//                bar->setVisible(false);
//            else
//                bar->setVisible(barsVisible);

//            QGraphicsSimpleTextItem *label = m_labels.at(itemIndex);

//            if (!qFuzzyCompare(m_series->d_func()->valueAt(set, category), 0)) {
//                int p = m_series->d_func()->percentageAt(set, category) * 100;
//                QString vString(QString::number(p));
//                vString.truncate(3);
//                vString.append("%");
//                label->setText(vString);
//            } else {
//                label->setText(QString(""));
//            }

//            label->setPos(xPos + (rect.width() / 2 - label->boundingRect().width() / 2),
//                          yPos - rectHeight / 2 - label->boundingRect().height() / 2);
//            label->setFont(barSet->m_labelFont);
//            label->setBrush(barSet->m_labelBrush);

//            itemIndex++;
//            xPos += rectWidth;
//        }
//    }
    return layout;
}

#include "moc_horizontalpercentbarchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

