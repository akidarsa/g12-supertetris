#ifndef TETRIXKEY_H
#define TETRIXKEY_H

#include<QFrame>
#include<QtGui>

class QLabel;
class QPushButton;

class TetrixKey : public QDialog {
    Q_OBJECT

public:
    TetrixKey(QWidget *parent = 0);
    int getKey(int action);

    enum {
        LFT1, LFT2, RGT1, RGT2, ROT1, ROT2, DWN1, DWN2, DRP1, DRP2
    };

    virtual ~TetrixKey() {
        delete hardDownButton2;
        delete softDownButton2;
        delete rotateButton2;
        delete rightButton2;
        delete leftButton2;
        delete hardDownButton1;
        delete softDownButton1;
        delete rotateButton1;
        delete rightButton1;
        delete leftButton1;
    }


private:
    QPushButton * leftButton1;
    QPushButton * rightButton1;
    QPushButton * rotateButton1;
    QPushButton * softDownButton1;
    QPushButton * hardDownButton1;
    int leftVar1;
    int rightVar1;
    int rotVar1;
    int downVar1;
    int mdownVar1;

    QPushButton * leftButton2;
    QPushButton * rightButton2;
    QPushButton * rotateButton2;
    QPushButton * softDownButton2;
    QPushButton * hardDownButton2;
    int leftVar2;
    int rightVar2;
    int rotVar2;
    int downVar2;
    int mdownVar2;

private slots:
    void makepopup();

};

class TetrixBox : public QDialog {
    Q_OBJECT

public:
    TetrixBox(QWidget *parent = 0);
    int getKey();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    int tempKey;
};

#endif
