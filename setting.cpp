#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    connect(ui->B_Home,SIGNAL(clicked()),this,SLOT(ReturnHome()));

}

Setting::~Setting()
{
    delete ui;
}

void Setting::ReturnHome()
{
    m_ShowWidgets->ShowWConsoleWindows();
}

void Setting::retranslateUi()
{
    ui->retranslateUi(this);
}
