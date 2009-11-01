#include "ControlLineEdit.h"
#include <QtGui>

ControlLineEdit::ControlLineEdit(QString label, QWidget *parent)
        : caption(label), QLineEdit(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setText(caption);
    setReadOnly(true);
    setAlignment(Qt::AlignHCenter);
    setMaxLength(5);
    setKeyOn = false;
}

int ControlLineEdit::keyList[] = {Qt::Key_Up, Qt::Key_Down, Qt::Key_Left, Qt::Key_Right, Qt::Key_Space, Qt::Key_D};

void ControlLineEdit::setKeyVal(int idx)
{
    keyVal = idx;
}

QString ControlLineEdit::getCaption()
{
    return caption;
}

void ControlLineEdit::mousePressEvent(QMouseEvent *evt)
{
    clear();
    setReadOnly(false);
    setKeyOn = true;
}

void ControlLineEdit::setValue(int key)
{
    switch(key)
    {
        case Qt::Key_F1:
            setText("F1");
            caption = "F1";
            break;
        case Qt::Key_F2:
            setText("F2");
            caption = "F2";
            break;
        case Qt::Key_F3:
            setText("F3");
            caption = "F13";
            break;
        case Qt::Key_F4:
            setText("F4");
            caption = "F4";
            break;
        case Qt::Key_F5:
            setText("F5");
            caption = "F5";
            break;
        case Qt::Key_F6:
            setText("F6");
            caption = "F6";
            break;
        case Qt::Key_F7:
            setText("F7");
            caption = "F7";
            break;
        case Qt::Key_F8:
            setText("F8");
            caption = "F8";
            break;
        case Qt::Key_F9:
            setText("F9");
            caption = "F9";
            break;
        case Qt::Key_F10:
            setText("F10");
            caption = "F10";
            break;
        case Qt::Key_F11:
            setText("F11");
            caption = "F11";
            break;
        case Qt::Key_F12:
            setText("F12");
            caption = "F12";
            break;
        case Qt::Key_Home:
            setText("Home");
            caption = "Home";
            break;
        case Qt::Key_End:
            setText("End");
            caption = "End";
            break;
        case Qt::Key_PageUp:
            setText("PgUp");
            caption = "PgUp";
            break;
        case Qt::Key_PageDown:
            setText("PgDn");
            caption = "PgDn";
            break;
        case Qt::Key_Escape:
            setText("ESC");
            caption = "ESC";
            break;
        case Qt::Key_Tab:
            setFocus();
            setText("Tab");
            caption = "Tab";
            break;
        case Qt::Key_Backspace:
            setText("BkSp");
            caption = "BkSp";
            break;
        case Qt::Key_Enter:
            setText("Enter");
            caption = "Enter";
            break;
        case Qt::Key_Insert:
            setText("Inst");
            caption = "Inst";
            break;
        case Qt::Key_Delete:
            setText("Del");
            caption = "Del";
            break;
        case Qt::Key_Space:
            setText("Space");
            caption = "Space";
            break;
        case Qt::Key_Control:
            setText("Ctrl");
            caption = "Ctrl";
            break;
        case Qt::Key_Alt:
            setText("Alt");
            caption = "Alt";
            break;
        case Qt::Key_CapsLock:
            setText("Caplk");
            caption = "Caplk";
            break;
        case Qt::Key_Shift:
            setText("Shft");
            caption = "Shft";
            break;
        case Qt::Key_NumLock:
            setText("Numlk");
            caption = "Numlk";
            break;
        case Qt::Key_Return:
            setText("Enter");
            caption = "Enter";
            break;
        case Qt::Key_Up:
            setText("Up");
            caption = "Up";
            break;
        case Qt::Key_Down:
            setText("Down");
            caption = "Down";
            break;
        case Qt::Key_Right:
            setText("Right");
            caption = "Right";
            break;
        case Qt::Key_Left:
            setText("Left");
            caption = "Left";
            break;
        default:
            setText(QString(key));
            caption = QString(key);
            break;
    }
    setKeyVal(key);
    emit keyChanged();
}
/*
void ControlLineEdit::turnSetOff()
{
    setKeyOn = false;
}

bool ControlLineEdit::isSetOn()
{
    return setKeyOn;
}
*/
void ControlLineEdit::keyPressEvent(QKeyEvent *evt)
{
    if(setKeyOn == false)
    {
        return;
    }
    setValue(evt->key());
    setReadOnly(true);
    setKeyOn = false;
    return;
}

int ControlLineEdit::getKeyVal()
{
    return keyVal;
}
/*
void ControlLineEdit::checkDuplicate(QKeyEvent *evt)
{
    for(int i = 0; i < 6; i ++)
    {
        if((evt->key() == keyList[i]))// && (i != keyVal))
        {
            int tmp;
            tmp = keyList[keyVal];
            keyList[keyVal] = evt->key();
            keyList[i] = tmp;
        }
        else
            keyList[keyVal] = evt->key();
    }
}
*/
