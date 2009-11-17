#include <QtGui>
#include "tetrixkey.h"

TetrixKey::TetrixKey(QWidget * parent) : QDialog(parent) {
    this -> resize(200, 300);
    QGridLayout *layout = new QGridLayout;
    

    //P1 Buttons
    leftButton1 = new QPushButton(tr("Set P1 Left"));
    rightButton1 = new QPushButton(tr("Set P1 Right"));
    rotateButton1 = new QPushButton(tr("Set P1 Rotate"));
    softDownButton1 = new QPushButton(tr("Set P1 Soft Down"));
    hardDownButton1 = new QPushButton(tr("Set P1 Hard Down"));
    layout->addWidget(leftButton1, 0, 0);
    layout->addWidget(rightButton1, 1, 0);
    layout->addWidget(rotateButton1, 2, 0);
    layout->addWidget(softDownButton1, 3, 0);
    layout->addWidget(hardDownButton1, 4, 0);

    //P2 Buttons
    leftButton2 = new QPushButton(tr("Set P2 Left"));
    rightButton2 = new QPushButton(tr("Set P2 Right"));
    rotateButton2 = new QPushButton(tr("Set P2 Rotate"));
    softDownButton2 = new QPushButton(tr("Set P2 Soft Down"));
    hardDownButton2 = new QPushButton(tr("Set P2 Hard Down"));
    layout->addWidget(leftButton2, 0, 2);
    layout->addWidget(rightButton2, 1, 2);
    layout->addWidget(rotateButton2, 2, 2);
    layout->addWidget(softDownButton2, 3, 2);
    layout->addWidget(hardDownButton2, 4, 2);
    this->setLayout(layout);

    leftVar1 = 0;
    rightVar1 = 0;
    rotVar1 = 0;
    downVar1 = 0;
    mdownVar1 = 0;

    leftVar2 = 0;
    rightVar2 = 0;
    rotVar2 = 0;
    downVar2 = 0;
    mdownVar2 = 0;

    connect(leftButton1, SIGNAL(clicked()), this, SLOT(makepopup()));
    connect(rightButton1, SIGNAL(clicked()), this, SLOT(makepopup()));
    connect(rotateButton1, SIGNAL(clicked()), this, SLOT(makepopup()));
    connect(softDownButton1, SIGNAL(clicked()), this, SLOT(makepopup()));
    connect(hardDownButton1, SIGNAL(clicked()), this, SLOT(makepopup()));

    connect(leftButton2, SIGNAL(clicked()), this, SLOT(makepopup()));
    connect(rightButton2, SIGNAL(clicked()), this, SLOT(makepopup()));
    connect(rotateButton2, SIGNAL(clicked()), this, SLOT(makepopup()));
    connect(softDownButton2, SIGNAL(clicked()), this, SLOT(makepopup()));
    connect(hardDownButton2, SIGNAL(clicked()), this, SLOT(makepopup()));

}

void TetrixKey::makepopup() {
    QObject *p = QObject::sender();

    TetrixBox setkey;
    setkey.exec();

    if (p == leftButton1) {
        leftVar1 = setkey.getKey();
    } else if (p == rightButton1) {
        rightVar1 = setkey.getKey();
    } else if (p == rotateButton1) {
        rotVar1 = setkey.getKey();
    } else if (p == softDownButton1) {
        downVar1 = setkey.getKey();
    } else if (p == hardDownButton1) {
        mdownVar1 = setkey.getKey();
    } else if (p == leftButton2) {
        leftVar2 = setkey.getKey();
    } else if (p == rightButton2) {
        rightVar2 = setkey.getKey();
    } else if (p == rotateButton2) {
        rotVar2 = setkey.getKey();
    } else if (p == softDownButton2) {
        downVar2 = setkey.getKey();
    } else if (p == hardDownButton2) {
        mdownVar2 = setkey.getKey();
    }
}

int TetrixKey::getKey(int action) {
    switch (action) {
        case LFT1:
            return leftVar1;
        case RGT1:
            return rightVar1;
        case ROT1:
            return rotVar1;
        case DWN1:
            return downVar1;
        case DRP1:
            return mdownVar1;

        case LFT2:
            return leftVar2;
        case RGT2:
            return rightVar2;
        case ROT2:
            return rotVar2;
        case DWN2:
            return downVar2;
        case DRP2:
            return mdownVar2;
	}

    return 0;
}

/* TetrixBox Implementations */

TetrixBox::TetrixBox(QWidget *parent) : QDialog(parent) {

    QGridLayout *layout = new QGridLayout;
    resize(100, 70);
    QLabel *label1 = new QLabel("Press a button. Or ESC to close.");
    layout->addWidget(label1, 0, 0);
    setLayout(layout);

}

int TetrixBox::getKey() {
    return tempKey;
}

void TetrixBox::keyPressEvent(QKeyEvent *event) {
    tempKey = event->key();
    accept();
}
