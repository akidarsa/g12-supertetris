#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
//#include <QLabel>
//#include "ControlLineEdit.h"
//#include <QPushButton>
#include "tetrisboard.h"

class QLabel;
class ControlLineEdit;
class QPushButton;
class TetrisBoard;

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    ConfigDialog(QWidget *parent = 0);
    virtual ~ConfigDialog();
    QLabel *upLabel;
    QLabel *downLabel;
    QLabel *leftLabel;
    QLabel *rightLabel;
    QLabel *dropLabel;
    QLabel *dropOneLabel;

    ControlLineEdit *upLineEdit;
    ControlLineEdit *downLineEdit;
    ControlLineEdit *leftLineEdit;
    ControlLineEdit *rightLineEdit;
    ControlLineEdit *dropLineEdit;
    ControlLineEdit *dropOneLineEdit;

    QPushButton *okButton;
    QPushButton *cancelButton;

    TetrisBoard *board;
    int getKey(int rep);

signals:
    void saveKeysSignal();

private slots:
    void updateFromUpKeys();
    void updateFromDownKeys();
    void updateFromLeftKeys();
    void updateFromRightKeys();
    void updateFromDropKeys();
    void updateFromDropOneKeys();
    void saveKeys();
    //~ConfigDialog();
//protected:
  //  void keyPressEvent(QKeyEvent *evt);
};

#endif // CONFIGDIALOG_H
