#ifndef CONTROLLINEEDIT_H
#define CONTROLLINEEDIT_H

#include <QLineEdit>

class ControlLineEdit : public QLineEdit
{

    Q_OBJECT

public:
    ControlLineEdit(QString label, QWidget *parent = 0);
    QString getCaption();
    static int keyList[];
    void setKeyVal(int idx);
    int getKeyVal();
    void setValue(int key);
    //bool isSetOn();
    //void turnSetOff();

signals:
    void keyChanged();

protected:
    void mousePressEvent(QMouseEvent *evt);
    void keyPressEvent(QKeyEvent *evt);

private:
    QString caption;
    bool setKeyOn;
    int keyVal;
    //void checkDuplicate(QKeyEvent *evt);
};

#endif // CONTROLLINEEDIT_H
