#include <QtGui>
#include "tetrixkey.h"

TetrixKey::TetrixKey(QWidget * parent) : QDialog(parent) {
    this -> resize(200, 300);
    QGridLayout *layout = new QGridLayout;
    leftButton = new QPushButton(tr("&Left"));
    rightButton = new QPushButton(tr("&Right"));
    rotateButton = new QPushButton(tr("&Rotate"));
    softDownButton = new QPushButton(tr("&Soft Down"));
    hardDownButton = new QPushButton(tr("&Hard Down"));

    layout->addWidget(leftButton, 0, 0);
    layout->addWidget(rightButton, 1, 0);
    layout->addWidget(rotateButton, 2, 0);
    layout->addWidget(softDownButton, 3, 0);
    layout->addWidget(hardDownButton, 4, 0);
    this->setLayout(layout);

    leftVar = 0;
    rightVar = 0;
    rotVar = 0;
    downVar = 0;
    mdownVar = 0;


    connect(leftButton, SIGNAL(clicked()), this, SLOT(makepopup()));
    connect(rightButton, SIGNAL(clicked()), this, SLOT(makepopup()));
    connect(rotateButton, SIGNAL(clicked()), this, SLOT(makepopup()));
    connect(softDownButton, SIGNAL(clicked()), this, SLOT(makepopup()));
    connect(hardDownButton, SIGNAL(clicked()), this, SLOT(makepopup()));

}

void TetrixKey::makepopup() {
    QObject *p = QObject::sender();

    TetrixBox setkey;
    setkey.exec();


    if (p == leftButton) {
        leftVar = setkey.getKey();
    } else if (p == rightButton) {
        rightVar = setkey.getKey();
    } else if (p == rotateButton) {
        rotVar = setkey.getKey();
    } else if (p == softDownButton) {
        downVar = setkey.getKey();
    } else if (p == hardDownButton) {
        mdownVar = setkey.getKey();
    }

}

int TetrixKey::getKey(int action) {
    switch (action) {
        case SOFTDOWN:
            return downVar;
        case LEFT:
            return leftVar;
        case RIGHT:
            return rightVar;
        case MAGICDOWN:
            return mdownVar;
        case ROTATE:
            return rotVar;
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
