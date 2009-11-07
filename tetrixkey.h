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
    static const int LEFT = 0;
    static const int RIGHT = 1;
    static const int ROTATE = 2;
    static const int SOFTDOWN = 3;
    static const int MAGICDOWN = 4;

private:
    QPushButton * leftButton;
    QPushButton * rightButton;
    QPushButton * rotateButton;
    QPushButton * softDownButton;
    QPushButton * hardDownButton;
    int leftVar;
    int rightVar;
    int rotVar;
    int downVar;
    int mdownVar;



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
