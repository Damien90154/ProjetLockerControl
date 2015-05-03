#include "customxml.h"

CustomXml::CustomXml(QString filename, QString Domroot)
{
    m_Filename = filename;
    m_Domroot = Domroot;

    m_fileXml = new QFile(filename);
    m_doc = new QDomDocument();


    if(InitializationFileXml())
    {
        qDebug()<<"Creation reussi";
    }
    else{
        qDebug()<<"Creation failed";
    }

}

CustomXml::~CustomXml()
{
    delete m_doc;
    delete m_fileXml;
}

bool CustomXml::InitializationFileXml( QIODevice::OpenMode mode)
{

    bool retour = false;
    int taille = 10;



    if(OpenFileXml(mode))
    {
        if(IsFileXmlEmtpy())
        {
            QDomProcessingInstruction procInstr = m_doc->createProcessingInstruction( "xml",
                   "version='1.0' encoding='UTF-8'");

            m_doc->appendChild(procInstr);
            m_doc->insertBefore(procInstr,m_doc->firstChild());

            m_root = m_doc->createElement(m_Domroot);
            m_doc->appendChild(m_root);
            QTextStream stream(m_fileXml);
            m_doc->save(stream,taille);


        }
        else{
            m_doc->setContent(m_fileXml);
            m_root = m_doc->documentElement();

        }
        retour = true;

    }
    else{
         qDebug()<<"ouverture impossible";
    }


    return retour;
}

bool CustomXml::OpenFileXml(QIODevice::OpenMode mode)
{
    bool retour = false;


    if(m_fileXml->open(mode))
    {
        retour = true;
    }

    return retour;
}

void CustomXml::CloseFileXml()
{
    m_fileXml->close();
}

bool CustomXml::IsOpenFile()
{
    bool retour = false;

    if(m_fileXml->isOpen())
    {
        retour = true;
    }

    return retour;

}

bool CustomXml::IsFileXmlEmtpy()
{
    bool retour = false;

    /*if(!m_doc->setContent(m_fileXml))
    {
        qDebug()<<"AUCUNE LIAISON entre le doc et le fichier xml";
        retour = true;
    }
    else{

            m_root = m_doc->documentElement();
            m_noeud_root = m_root.firstChild();

            while(!m_noeud_root.isNull())
            {
                if(!m_root.isNull())
                {
                    m_noeud_root = m_noeud_root.nextSibling();
                }
            }
        }*/

    if(m_fileXml->atEnd())
    {
        retour = true;
    }

    return retour;
}

bool CustomXml::isChildrootExist(QString childroot)
{

    bool retour = false;



        m_root = m_doc->documentElement();
        m_noeud_root = m_root.firstChild();

        while(!m_noeud_root.isNull() && (retour == false))
        {
            if(m_noeud_root.toElement().tagName() == childroot)
            {
                m_childroot = m_noeud_root.toElement();
                retour = true;
            }
            m_noeud_root = m_noeud_root.nextSibling();
        }


    return retour;
}

bool CustomXml::isElemExist(QString childroot,QString element)
{

    bool retour = false;


        m_root = m_doc->documentElement();
        m_noeud_root = m_root.firstChild();

        while(!m_noeud_root.isNull() && (retour == false))
        {
            if(m_noeud_root.toElement().tagName() == childroot)
            {
                m_noeud_child = m_noeud_root.toElement().firstChild();

                while(!m_noeud_child.isNull() && (retour == false))
                {
                    if(m_noeud_child.toElement().tagName() == element)
                    {
                        m_element = m_noeud_child.toElement();
                        retour = true;
                    }
                    m_noeud_child = m_noeud_child.nextSibling();
                }

            }
            m_noeud_root = m_noeud_root.nextSibling();
        }


    return retour;
}



bool CustomXml::WriteFileXml(QString childroot, QString element, QString attribut, QString value)
{
    bool retour = true;
    int taille = 10;


    m_root = m_doc->documentElement();

                if(!isChildrootExist(childroot))
                {


                    qDebug()<<"CRÉATION childroot";
                   m_childroot =  m_doc->createElement(childroot);
                   m_root.appendChild(m_childroot);
                   m_element = m_doc->createElement(element);
                   m_element.setAttribute(attribut,value);
                   m_childroot.appendChild(m_element);
                }
                else{

                    if(!isElemExist(childroot,element))
                    {

                        qDebug()<<"element n'existe pas";
                        m_element = m_doc->createElement(element);
                        m_element.setAttribute(attribut,value);
                        m_childroot.appendChild(m_element);


                    }
                    else{

                        m_element.setAttribute(attribut,value);
                        m_childroot.appendChild(m_element);
                    }
                }

OpenFileXml();
                QTextStream stream(m_fileXml);

                m_doc->save(stream,taille);

CloseFileXml();
    return retour;

}

bool CustomXml::WriteFileXml(QString childroot, QString element, QString attribut)
{
    bool retour = true;
    int taille = 10;


    m_root = m_doc->documentElement();

                if(!isChildrootExist(childroot))
                {
                    qDebug()<<"CRÉATION childroot";
                   m_childroot =  m_doc->createElement(childroot);
                   m_root.appendChild(m_childroot);
                   m_element = m_doc->createElement(element);
                   m_element.setAttribute(attribut,"");
                   m_childroot.appendChild(m_element);
                }
                else{

                    if(!isElemExist(childroot,element))
                    {

                        qDebug()<<"element n'existe pas";
                        m_element = m_doc->createElement(element);
                        m_element.setAttribute(attribut,"");
                        m_childroot.appendChild(m_element);


                    }
                    else{

                        m_element.setAttribute(attribut,"");
                        m_childroot.appendChild(m_element);
                    }
                }

    OpenFileXml();
                QTextStream stream(m_fileXml);

                m_doc->save(stream,taille);

    CloseFileXml();
    return retour;
}


QString CustomXml::Getvalue(QString childroot, QString element, QString attribut)
{
    QString value;


                    m_noeud_root = m_root.firstChild();

                    while(!m_noeud_root.isNull())
                    {
                        if(m_noeud_root.toElement().tagName() == childroot)
                        {
                            m_noeud_child = m_noeud_root.toElement().firstChild();

                            while(!m_noeud_child.isNull())
                            {
                                if(m_noeud_child.toElement().tagName() == element)
                                {
                                    if(m_noeud_child.toElement().hasAttribute(attribut))
                                    {
                                        value = m_noeud_child.toElement().attribute(attribut,0);
                                    }
                                }
                                m_noeud_child = m_noeud_child.nextSibling();
                            }

                        }
                        m_noeud_root = m_noeud_root.nextSibling();
                    }


    return value;

}
