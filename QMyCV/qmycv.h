#ifndef QMYCV_H
#define QMYCV_H

#include "qmycv_global.h"

#include "opencv2/opencv.hpp"
#include "../QMySlider/qmyslider.h"
#include "../QNavigationBar/qnavigationbar.h"

#include <QtWidgets>
#include <QWidget>
#include <QObject>

class QMYCVSHARED_EXPORT QMyCV : public QWidget
{
    Q_OBJECT
public:
    QMyCV(QWidget *parent = 0);

private:
    void init_slider();

private:
    void setupUi();
    void connect_signals_slots();

private:
    void show_cvImg_to_label(cv::Mat img);

private:
    void update_burl(const int &value);
    void update_gauss(const int &value);
    void update_canny();

    void update_img();          // 暂时就这样了,先不弄了

private:
    QScrollArea *img_scrollArea_src;
    QScrollArea *img_scrollArea_dst;

    QLabel      *img_label_src;
    QLabel      *img_label_dst;

    QMySlider   *slider_burl;
    QMySlider   *slider_gsuss;
    QMySlider   *slider_canny_threshold1;
    QMySlider   *slider_canny_threshold2;

    QVNavigationBar *c_NavigationBar_cv;

private:
    cv::Mat img_src;
    cv::Mat img_dst;

    QImage img_show_src;
    QImage img_show_dst;


private:
    void on_btn_changed(const int &index);
    void on_openFile();
};

#endif // QMYCV_H
