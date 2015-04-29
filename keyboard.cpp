#include "keyboard.h"
#include "ui_keyboard.h"

KeyBoard::KeyBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeyBoard)
{
    ui->setupUi(this);

    connect(ui->B_ABC,SIGNAL(clicked()),this,SLOT(set_ABC()));
    connect(ui->B_123,SIGNAL(clicked()),this,SLOT(set_123()));
    connect(ui->B_SUPP,SIGNAL(pressed()),this,SLOT(SUPPR()));
    connect(ui->B_SUPPR,SIGNAL(pressed()),this,SLOT(SUPPR()));
    connect(ui->B_OK,SIGNAL(clicked()),this,SLOT(Ok()));
    connect(ui->B_OK_2,SIGNAL(clicked()),this,SLOT(Ok()));
    connect(ui->B_A,SIGNAL(clicked()),this,SLOT(set_A()));
    connect(ui->B_B,SIGNAL(clicked()),this,SLOT(set_B()));
    connect(ui->B_C,SIGNAL(clicked()),this,SLOT(set_C()));
    connect(ui->B_D,SIGNAL(clicked()),this,SLOT(set_D()));
    connect(ui->B_E,SIGNAL(clicked()),this,SLOT(set_E()));
    connect(ui->B_F,SIGNAL(clicked()),this,SLOT(set_F()));
    connect(ui->B_G,SIGNAL(clicked()),this,SLOT(set_G()));
    connect(ui->B_H,SIGNAL(clicked()),this,SLOT(set_H()));
    connect(ui->B_I,SIGNAL(clicked()),this,SLOT(set_I()));
    connect(ui->B_J,SIGNAL(clicked()),this,SLOT(set_J()));
    connect(ui->B_K,SIGNAL(clicked()),this,SLOT(set_K()));
    connect(ui->B_L,SIGNAL(clicked()),this,SLOT(set_L()));
    connect(ui->B_M,SIGNAL(clicked()),this,SLOT(set_M()));
    connect(ui->B_N,SIGNAL(clicked()),this,SLOT(set_N()));
    connect(ui->B_O,SIGNAL(clicked()),this,SLOT(set_O()));
    connect(ui->B_P,SIGNAL(clicked()),this,SLOT(set_P()));
    connect(ui->B_Q,SIGNAL(clicked()),this,SLOT(set_Q()));
    connect(ui->B_R,SIGNAL(clicked()),this,SLOT(set_R()));
    connect(ui->B_S,SIGNAL(clicked()),this,SLOT(set_S()));
    connect(ui->B_T,SIGNAL(clicked()),this,SLOT(set_T()));
    connect(ui->B_U,SIGNAL(clicked()),this,SLOT(set_U()));
    connect(ui->B_V,SIGNAL(clicked()),this,SLOT(set_V()));
    connect(ui->B_W,SIGNAL(clicked()),this,SLOT(set_W()));
    connect(ui->B_X,SIGNAL(clicked()),this,SLOT(set_X()));
    connect(ui->B_Y,SIGNAL(clicked()),this,SLOT(set_Y()));
    connect(ui->B_Z,SIGNAL(clicked()),this,SLOT(set_Z()));
    connect(ui->B_0,SIGNAL(clicked()),this,SLOT(set_0()));
    connect(ui->B_1,SIGNAL(clicked()),this,SLOT(set_1()));
    connect(ui->B_2,SIGNAL(clicked()),this,SLOT(set_2()));
    connect(ui->B_3,SIGNAL(clicked()),this,SLOT(set_3()));
    connect(ui->B_4,SIGNAL(clicked()),this,SLOT(set_4()));
    connect(ui->B_5,SIGNAL(clicked()),this,SLOT(set_5()));
    connect(ui->B_6,SIGNAL(clicked()),this,SLOT(set_6()));
    connect(ui->B_7,SIGNAL(clicked()),this,SLOT(set_7()));
    connect(ui->B_8,SIGNAL(clicked()),this,SLOT(set_8()));
    connect(ui->B_9,SIGNAL(clicked()),this,SLOT(set_9()));

    this->setVisible(false);
    set_123();
}

KeyBoard::~KeyBoard()
{
    delete ui;
}

void KeyBoard::retranslateUi()
{
    ui->retranslateUi(this);
}

void KeyBoard::setTextButtonOK(QString text)
{
    ui->B_OK->setText(text);
    ui->B_OK_2->setText(text);
}

void KeyBoard::setVisibleB_Ok(bool visible)
{
    ui->B_OK->setVisible(visible);
    ui->B_OK_2->setVisible(visible);
}

void KeyBoard::set_ABC()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void KeyBoard::set_123()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void KeyBoard::set_A()
{
    emit SendCarac('A');
}

void KeyBoard::set_B()
{
    emit SendCarac('B');
}

void KeyBoard::set_C()
{
    emit SendCarac('C');
}

void KeyBoard::set_D()
{
    emit SendCarac('D');
}

void KeyBoard::set_E()
{
    emit SendCarac('E');
}

void KeyBoard::set_F()
{
    emit SendCarac('F');
}

void KeyBoard::set_G()
{
    emit SendCarac('G');
}

void KeyBoard::set_H()
{
    emit SendCarac('H');
}

void KeyBoard::set_I()
{
    emit SendCarac('I');
}

void KeyBoard::set_J()
{
    emit SendCarac('J');
}

void KeyBoard::set_K()
{
    emit SendCarac('K');
}

void KeyBoard::set_L()
{
    emit SendCarac('L');
}

void KeyBoard::set_M()
{
    emit SendCarac('M');
}

void KeyBoard::set_N()
{
    emit SendCarac('N');
}

void KeyBoard::set_O()
{
    emit SendCarac('O');
}

void KeyBoard::set_P()
{
    emit SendCarac('P');
}

void KeyBoard::set_Q()
{
    emit SendCarac('Q');
}

void KeyBoard::set_R()
{
    emit SendCarac('R');
}

void KeyBoard::set_S()
{
    emit SendCarac('S');
}

void KeyBoard::set_T()
{
    emit SendCarac('T');
}

void KeyBoard::set_U()
{
    emit SendCarac('U');
}

void KeyBoard::set_V()
{
    emit SendCarac('V');
}

void KeyBoard::set_W()
{
    emit SendCarac('W');
}

void KeyBoard::set_X()
{
    emit SendCarac('X');
}

void KeyBoard::set_Y()
{
    emit SendCarac('Y');
}

void KeyBoard::set_Z()
{
    emit SendCarac('Z');
}

void KeyBoard::set_0()
{
    emit SendCarac('0');
}

void KeyBoard::set_1()
{
    emit SendCarac('1');
}

void KeyBoard::set_2()
{
    emit SendCarac('2');
}

void KeyBoard::set_3()
{
    emit SendCarac('3');
}

void KeyBoard::set_4()
{
    emit SendCarac('4');
}

void KeyBoard::set_5()
{
    emit SendCarac('5');
}

void KeyBoard::set_6()
{
    emit SendCarac('6');
}

void KeyBoard::set_7()
{
    emit SendCarac('7');
}

void KeyBoard::set_8()
{
    emit SendCarac('8');
}

void KeyBoard::set_9()
{
    emit SendCarac('9');
}

void KeyBoard::SUPPR()
{
    emit SupprLastCaract();
}

void KeyBoard::Ok()
{   
    emit ButtonOKCliked();
}
