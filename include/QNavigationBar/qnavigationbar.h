#ifndef QNAVIGATIONBAR_H
#define QNAVIGATIONBAR_H

#include "qnavigationbar_global.h"

#include <QtWidgets>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

class QNAVIGATIONBARSHARED_EXPORT QNavigationBar : public QWidget
{
    Q_OBJECT
public:
    explicit QNavigationBar(QWidget *parent=0);

    void addItem(const QString &title);
    void setWidth(const int &width);
    void setBackgroundColor(const QString &color);
    void setSelectColor(const QString &color);
    void setRowHeight(const int &height);

protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    QList<QString> listItems;
    QString backgroundColor;
    QString selectedColor;
    int rowHeight;
    int currentIndex;

signals:
    void currentItemChanged(const int &index);
};

#endif // QNAVIGATIONBAR_H
