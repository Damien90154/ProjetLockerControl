#include "country.h"
#include <QApplication>
Country::Country()
{
    m_Linguist = new QTranslator();
    SetFrench();
}

Country::~Country()
{
    delete m_Linguist;
}

void Country::SetFrench()
{
    qApp->removeTranslator(m_Linguist);
    m_Linguist->load(":/Linguist/french");
    qApp->installTranslator(m_Linguist);
}

void Country::SetEnglish()
{
    qApp->removeTranslator(m_Linguist);
    m_Linguist->load(":/Linguist/english");
    qApp->installTranslator(m_Linguist);
}

void Country::SetDeutsch()
{
    qApp->removeTranslator(m_Linguist);
    m_Linguist->load(":/Linguist/german");
    qApp->installTranslator(m_Linguist);
}

void Country::SetEspanol()
{
    qApp->removeTranslator(m_Linguist);
    m_Linguist->load(":/Linguist/spain");
    qApp->installTranslator(m_Linguist);
}
