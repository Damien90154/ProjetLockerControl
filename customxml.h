#ifndef CUSTOMXML_H
#define CUSTOMXML_H

#include <QtXml>
#include <QIODevice>
#include <QFile>
#include <QTextStream>


class CustomXml
{
    public:
        CustomXml(QString filename , QString Domroot);
        ~CustomXml();


        bool OpenFileXml(QIODevice::OpenMode mode = QIODevice::ReadWrite);
        void CloseFileXml();

        bool WriteFileXml(QString childroot,QString element, QString attribut, QString value);
        bool WriteFileXml(QString childroot,QString element, QString attribut);
        QString Getvalue(QString childroot,QString element,QString attribut);

        bool IsOpenFile();
        bool IsFileXmlEmtpy();
        bool isElemExist(QString childroot, QString element);
        bool isChildrootExist(QString childroot);


    private:
        bool InitializationFileXml(QIODevice::OpenMode mode = QIODevice::ReadWrite);


        QDomDocument *m_doc;
        QFile *m_fileXml;

        QDomElement m_root;
        QDomElement m_childroot;
        QDomElement m_element;
        QDomAttr m_attribut;
        QDomNode m_noeud_root;
        QDomNode m_noeud_child;
        QString m_Filename , m_Domroot;

};

#endif // CUSTOMXML_H
