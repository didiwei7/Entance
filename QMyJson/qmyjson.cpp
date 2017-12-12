#include "qmyjson.h"


QMyJson::QMyJson()
{
}


/** 保存QJson对象到文件
 * @brief
 * @arguments
            const QString &filePath   输出的文件路径
            QJsonObject &jsonObject   输入的QJson对象
 * @return  NULL
 * @author  Didiwei
 * @date    2017-11-2
 */
bool QMyJson::MyJson_save(const QString &filePath, QJsonObject &jsonObject)
{
    QFile saveFile(filePath);

    if(!saveFile.open((QIODevice::WriteOnly)))
    {
        QMessageBox::warning(NULL, "Warning", QStringLiteral("保存文件失败"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return false;
    }

    QJsonDocument saveDoc(jsonObject);

    saveFile.write(saveDoc.toJson());

    return true;
}

/** 载入文件到QJson对象
 * @brief
 * @arguments
            const QString &filePath   输入的文件路径
            QJsonObject &jsonObject   输出的QJson对象
 * @return  NULL
 * @author  Didiwei
 * @date    2017-11-2
 */
bool QMyJson::MyJson_load(const QString &filePath, QJsonObject &jsonObject)
{
    QFile loadFile(filePath);

    if(!loadFile.open((QIODevice::ReadOnly)))
    {
        QMessageBox::warning(NULL, "Warning", QStringLiteral("打开文件失败"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return false;
    }

    // 读取数据
    QByteArray loadDate   = loadFile.readAll();

    // 将数据载入到Json文档
    QJsonDocument loadDoc = QJsonDocument::fromJson(loadDate);

    // 文档作为Json对象 输出
    jsonObject = loadDoc.object();
    return true;
}

/** 解析点位数据
 * @brief
 * @arguments
            QJsonObject &jsonObject  输入的QJson对象
 * @return  NULL
 * @author  Didiwei
 * @date    2017-11-23
 */
void QMyJson::MyJson_analysis(QJsonObject &jsonObject, int row)
{
    if (jsonObject.contains(QString("%1").arg(row)))
    {
        QJsonValue value_ID = jsonObject.value(QString("%1").arg(row));

        if (value_ID.isArray())
        {
            QJsonArray array = value_ID.toArray();
            int        nSize = array.size();

            for (int i = 0; i < nSize; ++i)
            {
                QJsonValue value_point = array.at(i);
                if (value_point.isString())
                {
                    QString point_string = value_point.toString();
                    qDebug() << QString("%1 :").arg(row) << point_string;
                }
                if (value_point.isDouble())
                {
                    double  point_double = value_point.toDouble();
                    qDebug() << QString("%1 :").arg(row) << point_double;
                }
            }
        }
    }
}

/** 插入点位数据
 * @brief
 * @arguments
            QJsonObject &jsonObject    输入的QJson对象
            int row                    行号
            const QString &point_name  点位名称
            const QString &point_doc   点位描述
            double X                   X
            double Y                   Y
            double Z                   Z
 * @return  NULL
 * @author  Didiwei
 * @date    2017-11-23
 */
void QMyJson::MyJson_insert(QJsonObject &jsonObject,
                            int row, const QString &point_name, const QString &point_doc,
                            double X, double Y, double Z)
{
    QJsonArray pointArray;
    pointArray.append(point_name);
    pointArray.append(point_doc);
    pointArray.append(X);
    pointArray.append(Y);
    pointArray.append(Z);

    jsonObject.insert(QString("%1").arg(row), QJsonValue(pointArray));
}

