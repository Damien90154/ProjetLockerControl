#include "showwidgets.h"

ShowWidgets::ShowWidgets()
{
   //initialisation
    m_StackedWidget = NULL;
    m_position_WBoxChoice = 0;
    m_position_WConsole = 0;
    m_position_WCustomer = 0;
    m_position_WDeliveryComfirm = 0;
    m_position_WEmptyBox = 0;
    m_position_WLogin = 0;
    m_position_WMenuDelivery = 0;
    m_position_WScanPackage = 0;
    m_position_WSetting = 0;
    m_position_WShowPackageBox = 0;
    m_position_WStowPackages = 0;
}

ShowWidgets::~ShowWidgets()
{

}

void ShowWidgets::ShowWBoxChoice()
{
    m_StackedWidget->setCurrentIndex(m_position_WBoxChoice);
}

void ShowWidgets::ShowWConsoleWindows()
{

    m_StackedWidget->setCurrentIndex(m_position_WConsole);
}

void ShowWidgets::ShowWCustomer()
{
    m_StackedWidget->setCurrentIndex(m_position_WCustomer);
}

void ShowWidgets::ShowWDeliveryConfirm()
{
    m_StackedWidget->setCurrentIndex(m_position_WDeliveryComfirm);
}

void ShowWidgets::ShowWLogin()
{

    m_StackedWidget->setCurrentIndex(m_position_WLogin);
}

void ShowWidgets::ShowWMenuDelivery()
{
    m_StackedWidget->setCurrentIndex(m_position_WMenuDelivery);
}

void ShowWidgets::ShowWOpenEmptyBox()
{
    m_StackedWidget->setCurrentIndex(m_position_WEmptyBox);
}


void ShowWidgets::ShowWPackageBox()
{
    m_StackedWidget->setCurrentIndex(m_position_WShowPackageBox);
}


void ShowWidgets::ShowWScanPackage()
{
    m_StackedWidget->setCurrentIndex(m_position_WScanPackage);
}

void ShowWidgets::ShowWSetting()
{
    m_StackedWidget->setCurrentIndex(m_position_WSetting);
}

void ShowWidgets::ShowWStowPackages()
{
    m_StackedWidget->setCurrentIndex(m_position_WStowPackages);
}

void ShowWidgets::ShowWMaintenanceMenu()
{
    m_StackedWidget->setCurrentIndex(m_position_WMaintenanceMenu);
}

void ShowWidgets::ShowWSQLite_Local_DatabaseManager()
{
    m_StackedWidget->setCurrentIndex(m_position_WSQLite_Local_DatabaseManager);
}

void ShowWidgets::ShowWSettingSystem()
{
    m_StackedWidget->setCurrentIndex(m_position_WSettingSystem);
}
