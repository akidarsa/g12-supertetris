#include <QtGui>
#include "ConfigDialog.h"
#include "tetrisboard.h"
#include "ControlLineEdit.h"

ConfigDialog::ConfigDialog(QWidget *parent)
        : QDialog(parent)
{
    setWindowTitle("Configuration");
    upLabel = new QLabel("Rotate Left");
    downLabel = new QLabel("Rotate Right");
    leftLabel = new QLabel("Left");
    rightLabel = new QLabel("Right");
    dropLabel = new QLabel("Drop Down");
    dropOneLabel = new QLabel("Drop One Line");

    upLineEdit = new ControlLineEdit("Up");
    upLineEdit->setKeyVal(Qt::Key_Up);
    downLineEdit = new ControlLineEdit("Down");
    downLineEdit->setKeyVal(Qt::Key_Down);
    leftLineEdit = new ControlLineEdit("Left");
    leftLineEdit->setKeyVal(Qt::Key_Left);
    rightLineEdit = new ControlLineEdit("Right");
    rightLineEdit->setKeyVal(Qt::Key_Right);
    dropLineEdit = new ControlLineEdit("Space");
    dropLineEdit->setKeyVal(Qt::Key_Space);
    dropOneLineEdit = new ControlLineEdit("D");
    dropOneLineEdit->setKeyVal(Qt::Key_D);

    okButton = new QPushButton(tr("Ok"));
    cancelButton = new QPushButton(tr("Cancel"));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(upLabel, 0, 0);
    layout->addWidget(upLineEdit, 0, 1);
    layout->addWidget(downLabel, 1, 0);
    layout->addWidget(downLineEdit, 1, 1);
    layout->addWidget(leftLabel, 2, 0);
    layout->addWidget(leftLineEdit, 2, 1);
    layout->addWidget(rightLabel, 3, 0);
    layout->addWidget(rightLineEdit, 3, 1);
    layout->addWidget(dropLabel, 4, 0);
    layout->addWidget(dropLineEdit, 4, 1);
    layout->addWidget(dropOneLabel, 5, 0);
    layout->addWidget(dropOneLineEdit, 5, 1);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(okButton);
    hLayout->addWidget(cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    mainLayout->addLayout(hLayout);
    setLayout(mainLayout);

    connect(upLineEdit, SIGNAL(keyChanged()), this, SLOT(updateFromUpKeys()));
    connect(downLineEdit, SIGNAL(keyChanged()), this, SLOT(updateFromDownKeys()));
    connect(leftLineEdit, SIGNAL(keyChanged()), this, SLOT(updateFromLeftKeys()));
    connect(rightLineEdit, SIGNAL(keyChanged()), this, SLOT(updateFromRightKeys()));
    connect(dropLineEdit, SIGNAL(keyChanged()), this, SLOT(updateFromDropKeys()));
    connect(dropOneLineEdit, SIGNAL(keyChanged()), this, SLOT(updateFromDropOneKeys()));

    connect(okButton, SIGNAL(clicked()), this, SLOT(saveKeys()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));

}

int ConfigDialog::getKey(int rep)
{
    switch(rep)
    {
        case 0:
            return(upLineEdit->getKeyVal());
        case 1:
            return(downLineEdit->getKeyVal());
        case 2:
            return(leftLineEdit->getKeyVal());
        case 3:
            return(rightLineEdit->getKeyVal());
        case 4:
            return(dropLineEdit->getKeyVal());
        case 5:
            return(dropOneLineEdit->getKeyVal());
        default:
            return(-1);
    }
}

void ConfigDialog::saveKeys()
{
    connect(this,SIGNAL(saveKeysSignal()), board, SLOT(saveKeys()));
    emit saveKeysSignal();
    close();
}

void ConfigDialog::updateFromUpKeys()
{
    if(upLineEdit->getKeyVal() == dropOneLineEdit->getKeyVal())
    {
        dropOneLineEdit->clear();
    }
    if(upLineEdit->getKeyVal() == downLineEdit->getKeyVal())
    {
        downLineEdit->clear();
    }
    if(upLineEdit->getKeyVal() == leftLineEdit->getKeyVal())
    {
        leftLineEdit->clear();
    }
    if(upLineEdit->getKeyVal() == rightLineEdit->getKeyVal())
    {
        rightLineEdit->clear();
    }
    if(upLineEdit->getKeyVal() == dropLineEdit->getKeyVal())
    {
        dropLineEdit->clear();
    }
    return;
}

void ConfigDialog::updateFromDownKeys()
{
    if(downLineEdit->getKeyVal() == dropOneLineEdit->getKeyVal())
    {
        dropOneLineEdit->clear();
    }
    if(downLineEdit->getKeyVal() == upLineEdit->getKeyVal())
    {
        upLineEdit->clear();
    }
    if(downLineEdit->getKeyVal() == leftLineEdit->getKeyVal())
    {
        leftLineEdit->clear();
    }
    if(downLineEdit->getKeyVal() == rightLineEdit->getKeyVal())
    {
        rightLineEdit->clear();
    }
    if(downLineEdit->getKeyVal() == dropLineEdit->getKeyVal())
    {
        dropLineEdit->clear();
    }
    return;
}

void ConfigDialog::updateFromLeftKeys()
{
    if(leftLineEdit->getKeyVal() == dropOneLineEdit->getKeyVal())
    {
        dropOneLineEdit->clear();
    }
    if(leftLineEdit->getKeyVal() == downLineEdit->getKeyVal())
    {
        downLineEdit->clear();
    }
    if(leftLineEdit->getKeyVal() == upLineEdit->getKeyVal())
    {
        upLineEdit->clear();
    }
    if(leftLineEdit->getKeyVal() == rightLineEdit->getKeyVal())
    {
        rightLineEdit->clear();
    }
    if(leftLineEdit->getKeyVal() == dropLineEdit->getKeyVal())
    {
        dropLineEdit->clear();
    }
    return;
}

void ConfigDialog::updateFromRightKeys()
{
    if(rightLineEdit->getKeyVal() == dropOneLineEdit->getKeyVal())
    {
        dropOneLineEdit->clear();
    }
    if(rightLineEdit->getKeyVal() == downLineEdit->getKeyVal())
    {
        downLineEdit->clear();
    }
    if(rightLineEdit->getKeyVal() == leftLineEdit->getKeyVal())
    {
        leftLineEdit->clear();
    }
    if(rightLineEdit->getKeyVal() == upLineEdit->getKeyVal())
    {
        upLineEdit->clear();
    }
    if(rightLineEdit->getKeyVal() == dropLineEdit->getKeyVal())
    {
        dropLineEdit->clear();
    }
    return;
}

void ConfigDialog::updateFromDropKeys()
{
    if(dropLineEdit->getKeyVal() == dropOneLineEdit->getKeyVal())
    {
        dropOneLineEdit->clear();
    }
    if(dropLineEdit->getKeyVal() == downLineEdit->getKeyVal())
    {
        downLineEdit->clear();
    }
    if(dropLineEdit->getKeyVal() == leftLineEdit->getKeyVal())
    {
        leftLineEdit->clear();
    }
    if(dropLineEdit->getKeyVal() == rightLineEdit->getKeyVal())
    {
        rightLineEdit->clear();
    }
    if(dropLineEdit->getKeyVal() == upLineEdit->getKeyVal())
    {
        upLineEdit->clear();
    }
    return;
}

void ConfigDialog::updateFromDropOneKeys()
{
    if(dropOneLineEdit->getKeyVal() == upLineEdit->getKeyVal())
    {
        upLineEdit->clear();
    }
    if(dropOneLineEdit->getKeyVal() == downLineEdit->getKeyVal())
    {
        downLineEdit->clear();
    }
    if(dropOneLineEdit->getKeyVal() == leftLineEdit->getKeyVal())
    {
        leftLineEdit->clear();
    }
    if(dropOneLineEdit->getKeyVal() == rightLineEdit->getKeyVal())
    {
        rightLineEdit->clear();
    }
    if(dropOneLineEdit->getKeyVal() == dropLineEdit->getKeyVal())
    {
        dropLineEdit->clear();
    }
    return;
}

ConfigDialog::~ConfigDialog()
{   
}
