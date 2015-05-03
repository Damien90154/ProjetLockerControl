#include "settingsystem.h"
#include "ui_settingsystem.h"

SettingSystem::SettingSystem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingSystem)
{
    ui->setupUi(this);
    m_Xml = new CustomXml("config.xml","SettingSystem");
    m_Xml->OpenFileXml();

    if(!m_Xml->IsFileXmlEmtpy())
    {
          m_Xml->CloseFileXml();
          m_Xml->WriteFileXml("ID_Console","id","code");
          m_Xml->WriteFileXml("ID_Console","id","site");
          m_Xml->WriteFileXml("Devices","type","name");
          m_Xml->WriteFileXml("Devices","type","port");
          m_Xml->WriteFileXml("Network","address","ip");
          m_Xml->WriteFileXml("Network","address","subnet_mask");
          m_Xml->WriteFileXml("Network","address","gateway");
          m_Xml->WriteFileXml("Network","address","DNS_preferred");
          m_Xml->WriteFileXml("Network","address","DNS_alernate");
          m_Xml->WriteFileXml("Server_LMS","address","ip");
          m_Xml->WriteFileXml("Server_rsync","address","ip");
          m_Xml->WriteFileXml("Server_rsync","user","name");
          m_Xml->WriteFileXml("Server_rsync","password","passwd");
          m_Xml->WriteFileXml("Softphone","sip","username");
          m_Xml->WriteFileXml("Softphone","sip","password");
          m_Xml->WriteFileXml("Softphone","sip","domain");
          m_Xml->WriteFileXml("Softphone","sip","proxy");


    }
    else
        m_Xml->CloseFileXml();


}

SettingSystem::~SettingSystem()
{
    delete ui;
}

void SettingSystem::on_B_Cancel_clicked()
{
    m_ShowWidgets->ShowWSetting();
}
