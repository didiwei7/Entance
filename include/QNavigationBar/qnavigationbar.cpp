#include "qnavigationbar.h"


QNavigationBar::QNavigationBar(QWidget *parent)
    : QWidget(parent)
{
    backgroundColor = "#E4E4E4";
    selectedColor   = "#2CA7F8";
    rowHeight       = 40;
    currentIndex    = 0;

    this->setMouseTracking(true);
    this->setFixedWidth(150);
}


void QNavigationBar::addItem(const QString &title)
{
    listItems << title;

    this->update();
}

void QNavigationBar::setWidth(const int &width)
{
    this->setFixedWidth(width);
}

void QNavigationBar::setBackgroundColor(const QString &color)
{
    backgroundColor = color;

    this->update();
}

void QNavigationBar::setSelectColor(const QString &color)
{
    selectedColor = color;

    this->update();
}

void QNavigationBar::setRowHeight(const int &height)
{
    rowHeight = height;

    this->update();
}

void QNavigationBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw background color.
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(backgroundColor));
    painter.drawRect(rect());

    // Draw Items
    int count = 0;
    for (const QString &str : listItems) {
        QPainterPath itemPath;
        itemPath.addRect(QRect(0, count * rowHeight, width(), rowHeight));

        if (currentIndex == count) {
            painter.setPen("#FFFFFF");
            painter.fillPath(itemPath, QColor(selectedColor));
        }else {
            painter.setPen("#202020");
            painter.fillPath(itemPath, QColor(backgroundColor));
        }

        painter.drawText(QRect(0, count * rowHeight, width(), rowHeight), Qt::AlignVCenter | Qt::AlignHCenter, str);

        ++count;
    }
}

void QNavigationBar::mousePressEvent(QMouseEvent *e)
{
    if (e->y() / rowHeight < listItems.count()) {
        currentIndex = e->y() / rowHeight;

        emit currentItemChanged(currentIndex);

        this->update();
    }
}

void QNavigationBar::mouseMoveEvent(QMouseEvent *e)
{
    //    if (e->y() / rowHeight < listItems.count()) {
    //        // qDebug() << e->y() / rowHeight;
    //    }
}

void QNavigationBar::mouseReleaseEvent(QMouseEvent *e)
{

}
