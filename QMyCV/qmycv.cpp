#include "qmycv.h"

using namespace cv;

QMyCV::QMyCV(QWidget *parent) : QWidget(parent)
{
    this->setupUi();
    this->connect_signals_slots();
}

/** 初始化 Ui
 * @brief   初始化Ui
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-12-08
 */
void QMyCV::setupUi()
{
    // 【1】 初始化其他控件
    this->init_slider();

    // 【2】 初始化控件
    img_scrollArea_src = new QScrollArea();
    img_scrollArea_dst = new QScrollArea();

    img_label_src = new QLabel();
    img_label_dst = new QLabel();

    img_scrollArea_src->setWidget(img_label_src);
    img_scrollArea_dst->setWidget(img_label_dst);

    // 【3】 初始化导航栏
    c_NavigationBar_cv = new QVNavigationBar();
    c_NavigationBar_cv->setSelectColor("#FFC0CB");
    c_NavigationBar_cv->setRowHeight(30);
    c_NavigationBar_cv->setWidth(80);
    c_NavigationBar_cv->addItem(QStringLiteral("撤销"));
    c_NavigationBar_cv->addItem(QStringLiteral("打开"));
    c_NavigationBar_cv->addItem(QStringLiteral("保存"));

    // 【4】 布局
    // layout_1 为 1 级布局， layout_2 为 2 级布局
    // layout_2_1 为 2 级布局的第一个布局 ......
    QHBoxLayout *layout_1 = new QHBoxLayout();
    QVBoxLayout *layout_2 = new QVBoxLayout();

    layout_2->addWidget(slider_burl);
    layout_2->addWidget(slider_gsuss);
    layout_2->addWidget(slider_canny_threshold1);
    layout_2->addWidget(slider_canny_threshold2);
    layout_2->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    layout_1->addWidget(img_scrollArea_src);
    layout_1->addWidget(img_scrollArea_dst);
    layout_1->addLayout(layout_2);
    layout_1->addWidget(c_NavigationBar_cv);

    // 【5】 载入控件
    this->setLayout(layout_1);
}

/** 初始化 slider
 * @brief   初始化 slider
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-12-08
 */
void QMyCV::init_slider()
{
    // 均值滤波
    slider_burl = new QMySlider();
    slider_burl->setText(QStringLiteral("均值滤波Burl"));
    slider_burl->setRange(1,100);

    slider_gsuss = new QMySlider();
    slider_gsuss->setText(QStringLiteral("高斯滤波Gauss"));
    slider_gsuss->setRange(1, 100);

    slider_canny_threshold1 = new QMySlider();
    slider_canny_threshold2 = new QMySlider();
    slider_canny_threshold1->setText(QStringLiteral("Canny threshold1"));
    slider_canny_threshold2->setText(QStringLiteral("Canny threshold2"));
    slider_canny_threshold1->setRange(1, 200);
    slider_canny_threshold2->setRange(1, 200);
}

/** 连接信号槽
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-12-08
 */
void QMyCV::connect_signals_slots()
{
    // 【1】 导航栏响应
    connect(c_NavigationBar_cv, &QVNavigationBar::currentItemChanged,
            this, &QMyCV::on_btn_changed);

    // 【2】 图像处理
    connect(slider_burl,  &QMySlider::sliderValueChanged, this, &QMyCV::update_burl);
    connect(slider_gsuss, &QMySlider::sliderValueChanged, this, &QMyCV::update_gauss);
    connect(slider_canny_threshold1, &QMySlider::sliderValueChanged,
            this, &QMyCV::update_canny);
    connect(slider_canny_threshold2, &QMySlider::sliderValueChanged,
            this, &QMyCV::update_canny);
}

/** 显示Mat型矩阵到Label中
 * @brief
 * @arguments
            Mat img 输入图像
 * @return  NULL
 * @author  Didiwei
 * @date    2017-12-08
 */
void QMyCV::show_cvImg_to_label(Mat img)
{
    // 【1】 转换为 rgb
    cvtColor(img, img, CV_BGR2RGB);

    // 【2】 将图像数据Copy到QImage中
    QImage qimg = QImage(img.data, img.cols, img.rows,
                         img.cols * img.channels(),
                         QImage::Format_RGB888);

    // 【3】 在Label中显示
    img_label_dst->clear();
    img_label_dst->setPixmap(QPixmap::fromImage(qimg));
    img_label_dst->resize(img_label_dst->pixmap()->size());
}

/** 槽函数 响应导航栏
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-12-08
 */
void QMyCV::on_btn_changed(const int &index)
{
    if (0 == index)
    {

    }
    else if (1 == index)
    {
         this->on_openFile();
    }
    else if (2 == index)
    {

    }
    else
    {
        return;
    }
}

/** 槽函数 打开
 * @brief
        【1】 打开文件对话框,获取文件路径
        【2】 获取Mat型数据
        【3】 显示在Label中
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-12-08
 */
void QMyCV::on_openFile()
{
    // 【1】 打开文件对话框,获取文件路径
    const QStringList imgSysPaths = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QString imgPath = QFileDialog::getOpenFileName(NULL, QStringLiteral("Open File"),
                            imgSysPaths.isEmpty() ? QDir::homePath() : imgSysPaths.first(),
                            QStringLiteral("Image files (*.png *.bmp *.jpg *.jpeg) ;; All files (*.*)"));

    if(imgPath.isEmpty())
    {
        qDebug() << QStringLiteral("打开失败");
        return;
    }

    // 【2】 获取Mat型数据
    img_src = imread(imgPath.toStdString());
    Mat img_src_copy = img_src.clone();

    // 【3】 显示在Label中
    cvtColor(img_src_copy, img_src_copy, CV_BGR2RGB);

    img_show_src = QImage(img_src_copy.data, img_src_copy.cols, img_src_copy.rows,
                          img_src_copy.cols * img_src_copy.channels(),
                          QImage::Format_RGB888);

    img_label_src->clear();
    img_label_src->setPixmap(QPixmap::fromImage(img_show_src));
    img_label_src->resize(img_label_src->pixmap()->size());

    img_label_dst->clear();
    img_label_dst->setPixmap(QPixmap::fromImage(img_show_src));
    img_label_dst->resize(img_label_dst->pixmap()->size());
}

/** 槽函数 均值滤波
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-12-08
 */
void QMyCV::update_burl(const int &value)
{
    Mat img_copy = img_src.clone();

    blur(img_copy, img_copy, Size(value, value));

    this->show_cvImg_to_label(img_copy);
}

/** 槽函数 高斯滤波
 * @brief
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-12-08
 */
void QMyCV::update_gauss(const int &value)
{
    Mat img_copy = img_src.clone();

    int v = value/2 * 2 + 1;

    GaussianBlur(img_copy, img_copy, Size(v, v), 0, 0);

    this->show_cvImg_to_label(img_copy);
}

/** 槽函数 Canny
 * @brief   与opencv2不同.opencv3下用新的操作实现
 *          效果：边缘会保留原来的颜色
 * @arguments   NULL
 * @return  NULL
 * @author  Didiwei
 * @date    2017-12-08
 */
void QMyCV::update_canny()
{
    Mat img_copy = img_src.clone();

    int value1 = slider_canny_threshold1->currentValue();
    int value2 = slider_canny_threshold2->currentValue();

    // 【1】 转换为灰度
    cvtColor(img_copy, img_copy, COLOR_BGR2GRAY);

    // 【2】 使用Canny算子
    Canny(img_copy, img_copy, value1, value2, 3);

    // 【3】 创建一个矩阵来存放它
    Mat dst;
    dst.create(img_src.size(), img_src.type());
    dst = Scalar::all(0);

    // 【4】 拷贝到输出图像
    img_src.copyTo(dst, img_copy);

    // 【5】 显示图像
    this->show_cvImg_to_label(dst);
}

void QMyCV::update_img()
{

}
