#ifndef SHOWWIDGETS_H
#define SHOWWIDGETS_H


#include <QStackedWidget>


class ShowWidgets
{

  private:

    QStackedWidget *m_StackedWidget;

    //Positions Widgets
    int m_position_WLogin;
    int m_position_WSetting;
    int m_position_WCustomer;
    int m_position_WConsole;
    int m_position_WMenuDelivery;
    int m_position_WEmptyBox;
    int m_position_WBoxChoice;
    int m_position_WScanPackage;
    int m_position_WDeliveryComfirm;
    int m_position_WShowPackageBox;
    int m_position_WStowPackages;

  public:
    ShowWidgets();
    ~ShowWidgets();

    //getter
    int GetPosConsoleWindows(){return m_position_WConsole;}
    int GetPosBoxChoice(){return m_position_WBoxChoice;}
    int GetPosCustomer(){return m_position_WCustomer;}
    int GetPosDeliveryConfirm(){return m_position_WDeliveryComfirm;}
    int GetPosLogin(){return m_position_WLogin;}
    int GetPosMenuDelivery(){return m_position_WMenuDelivery;}
    int GetPosOpenEmptyBox(){return m_position_WEmptyBox;}
    int GetPosScanPackage(){return m_position_WScanPackage;}
    int GetPosShowPackageBox(){return m_position_WShowPackageBox;}
    int GetPosSetting(){return m_position_WSetting;}
    int GetPosStowPackages(){return m_position_WStowPackages;}
    template <typename T> T* GetWidget(int pos){
        return (T*)m_StackedWidget->widget(pos);
    }

    //setter
    void SetStackedWidget(QStackedWidget *stackedW){m_StackedWidget = stackedW;}
    void SetPosConsoleWindows(int TposConsole){m_position_WConsole = TposConsole;}
    void SetPosBoxChoice(int TposBoxChoice){m_position_WBoxChoice = TposBoxChoice;}
    void SetPosCustomer(int TposCustumer){m_position_WCustomer = TposCustumer;}
    void SetPosDeliveryConfirm(int TposDeliComf){m_position_WDeliveryComfirm = TposDeliComf;}
    void SetPosLogin(int TposLogin){m_position_WLogin = TposLogin;}
    void SetPosMenuDelivery(int TposMenuDeli){m_position_WMenuDelivery = TposMenuDeli;}
    void SetPosOpenEmptyBox(int TposOpenEmptybox){m_position_WEmptyBox = TposOpenEmptybox;}
    void SetPosScanPackage(int TposScanPackage){m_position_WScanPackage = TposScanPackage;}
    void SetPosShowPackageBox(int TposShowPackageBox){m_position_WShowPackageBox = TposShowPackageBox;}
    void SetPosSetting(int TposSetting){m_position_WSetting = TposSetting;}
    void SetPosStowPackages(int TposStowPackage){m_position_WStowPackages = TposStowPackage;}

    //show Widgets
    void ShowWConsoleWindows();
    void ShowWBoxChoice();
    void ShowWCustomer();
    void ShowWDeliveryConfirm();
    void ShowWLogin();
    void ShowWMenuDelivery();
    void ShowWOpenEmptyBox();
    void ShowWScanPackage();
    void ShowWPackageBox();
    void ShowWSetting();
    void ShowWStowPackages();


};

#endif // SHOWWIDGETS_H
