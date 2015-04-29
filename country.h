#ifndef COUNTRY_H
#define COUNTRY_H

#include <QTranslator>


class Country
{

public:
    Country();
    ~Country();

    void SetFrench();
    void SetEnglish();
    void SetDeutsch();
    void SetEspanol();

private:
    QTranslator *m_Linguist;

};

#endif // COUNTRY_H
