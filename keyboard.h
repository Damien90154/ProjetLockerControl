#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>

namespace Ui {
class KeyBoard;
}

class KeyBoard : public QWidget
{
  Q_OBJECT

  public:
    explicit KeyBoard(QWidget *parent = 0);
    ~KeyBoard();
    void setVisibleB_Ok(bool visible);   
    void setTextButtonOK(QString text);

    void retranslateUi();
private slots:
    void set_A();
    void set_B();
    void set_C();
    void set_D();
    void set_E();
    void set_F();
    void set_G();
    void set_H();
    void set_I();
    void set_J();
    void set_K();
    void set_L();
    void set_M();
    void set_N();
    void set_O();
    void set_P();
    void set_Q();
    void set_R();
    void set_S();
    void set_T();
    void set_U();
    void set_V();
    void set_W();
    void set_X();
    void set_Y();
    void set_Z();
    void set_ABC();
    void set_123();
    void SUPPR();
    void Ok();
    void set_0();
    void set_1();
    void set_2();
    void set_3();
    void set_4();
    void set_5();
    void set_6();
    void set_7();
    void set_8();
    void set_9();

  signals:
    void SendCarac(QChar);
    void SupprLastCaract();
    void ButtonOKCliked();

  private:
    Ui::KeyBoard *ui;
};

#endif // KEYBOARD_H
