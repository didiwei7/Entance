#include "qmyxml.h"


QMyXml::QMyXml()
{
}

/** 插入点位数据
 * @brief
 * @arguments
            QXmlStreamWriter &stream   输入的QXmlStreamWriter对象
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
void QMyXml::MyXml_insert(QXmlStreamWriter &stream,
                          int row, const QString &point_name, const QString &point_doc,
                          double X, double Y, double Z)
{
    stream.writeStartElement(QString("Point%1").arg(row));
    stream.writeAttribute("ID", QString("%1").arg(row));
    stream.writeAttribute("Point_name", point_name);
    stream.writeAttribute("Point_doc", point_doc);
    stream.writeAttribute("X_axis", QString("%1").arg(X));
    stream.writeAttribute("Y_axis", QString("%1").arg(Y));
    stream.writeAttribute("Z_axis", QString("%1").arg(Z));
    stream.writeEndElement();
}

/** 解析点位数据
 * @brief
 * @arguments
            const QString &filepath  输入的文件路径
 * @return  NULL
 * @author  Didiwei
 * @date    2017-11-23
 */
void QMyXml::MyXml_analysis(const QString &filepath)
{
    QFile loadFile(filepath);
    if (!loadFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"Error: cannot open file";
        return;
    }

    QXmlStreamReader xml_reader;

    // 设置文件，这时会将流设置为初始状态
    xml_reader.setDevice(&loadFile);

    // 如果没有读到文档结尾，而且没有出现错误
    while (!xml_reader.atEnd())
    {
        // 读取下一个记号，它返回记号的类型
        QXmlStreamReader::TokenType type = xml_reader.readNext();

        // 下面便根据记号的类型来进行不同的输出
        if (type == QXmlStreamReader::StartDocument)
        {
            qDebug() << xml_reader.documentEncoding() << xml_reader.documentVersion();
        }

        if (type == QXmlStreamReader::StartElement)
        {
            qDebug() << "<" << xml_reader.name() << ">";
            if (xml_reader.attributes().hasAttribute("ID"))
            {
                qDebug() << xml_reader.attributes().value("ID");
            }
            if (xml_reader.attributes().hasAttribute("Point_name"))
            {
                qDebug() << xml_reader.attributes().value("Point_name");
            }
            if (xml_reader.attributes().hasAttribute("Point_doc"))
            {
                qDebug() << xml_reader.attributes().value("Point_doc");
            }

            if (xml_reader.attributes().hasAttribute("X_axis"))
            {
                qDebug() << xml_reader.attributes().value("X_axis");
            }
            if (xml_reader.attributes().hasAttribute("Y_axis"))
            {
                qDebug() << xml_reader.attributes().value("Y_axis");
            }
            if (xml_reader.attributes().hasAttribute("Z_axis"))
            {
                qDebug() << xml_reader.attributes().value("Z_axis");
            }

        }
        if (type == QXmlStreamReader::Characters && !xml_reader.isWhitespace())
        {
            qDebug() << xml_reader.text();
        }

        if (type == QXmlStreamReader::EndElement)
        {
            qDebug() << "";
        }
    }

    // 如果读取过程中出现错误，那么输出错误信息
    if (xml_reader.hasError()) {
        qDebug() << "error: " << xml_reader.errorString();
    }

}
