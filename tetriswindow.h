 /****************************************************************************
 **
 ** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
 ** All rights reserved.
 ** Contact: Nokia Corporation (qt-info@nokia.com)
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial Usage
 ** Licensees holding valid Qt Commercial licenses may use this file in
 ** accordance with the Qt Commercial License Agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Nokia.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Nokia gives you certain additional
 ** rights.  These rights are described in the Nokia Qt LGPL Exception
 ** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 ** If you have questions regarding the use of this file, please contact
 ** Nokia at qt-info@nokia.com.
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

 #ifndef TETRISWINDOW_H
 #define TETRISWINDOW_H

 #include <QtGui>
 //#include <QFrame>
 //#include <QWidget>
#include "tetrisnetwork.h"


 class QLCDNumber;
 class QLabel;
 class QPushButton;
 class QGroupBox;

 class TetrisBoard;

 class TetrisWindow : public QWidget
 {
     Q_OBJECT

 public:
     TetrisWindow();
     virtual ~TetrisWindow();

 signals:
	 void keyGrabber(QKeyEvent *event);

 private:
	TetrisNetwork * verizon;
     QLabel *createLabel(const QString &text);
     void createStatus();
     void createStatus2();
     void createControl();
     TetrisBoard *board;
     TetrisBoard *boardTwo;
     QLabel *nextPieceLabel;
     QLabel *nextPieceLabel2;
     QGroupBox * ui_statusGroup;
     QGroupBox * ui_statusGroup2;
     QGroupBox * ui_controlGroup;
     QGroupBox * ui_networkGroup;
     QGroupBox * ui_localGroup;
     QLabel * ui_pieceCountLabel;
     QLabel * ui_piece4Label;
     QLabel * ui_piece5Label;
     QLabel * ui_piece6Label;
     QLabel * ui_piece7Label;
     QLabel * ui_blockCountLabel;
     QLabel * ui_pieceCountLabel2;
     QLabel * ui_piece4Label2;
     QLabel * ui_piece5Label2;
     QLabel * ui_piece6Label2;
     QLabel * ui_piece7Label2;
     QLabel * ui_blockCountLabel2;
     QLabel * ui_linesRemoved2;
     QLabel * ui_netStatus;
     //QLCDNumber *scoreLcd;
     //QLCDNumber *levelLcd;
     QLCDNumber *linesLcd;
     QLCDNumber *linesLcd2;
     QPushButton *startButton;
     QPushButton *startHHButton;
     QPushButton *startHCButton;
     QPushButton *startCCButton;
     QPushButton *startNetButton;
     QPushButton *endNetButton;
     QPushButton *quitButton;
     QPushButton *pauseButton;
     QPushButton *configureButton;
    int p1LftKey;
    int p1RgtKey;
    int p1RotKey;
    int p1DwnKey; //Moves one line DOWN
    int p1DrpKey; //DROPS piece to bottom

    int p2LftKey;
    int p2RgtKey;
    int p2RotKey;
    int p2DwnKey; //Moves one line DOWN
    int p2DrpKey; //DROPS piece to bottom

    void keyPressEvent(QKeyEvent *event);
    int tempLftVar[2];
    int tempRgtVar[2];
    int tempRotVar[2];
    int tempDwnVar[2];
    int tempDrpVar[2];
    bool keyStarted;

private slots:
	void keyConfig();
	void keyGrabStart(bool started)
	{
	    keyStarted = started;
	};

	void p1Left();
	void p1Right();
	void p1Rotate(); 
	void p1Fall();
	void p1Win();
	void p1Lose();
	void p1Gameover(); 
	void p1Piece(string piece);
	void p1Attack(string line);
	void p2Left();
	void p2Right();
	void p2Rotate();
	void p2Fall(); 
	void p2Win();
	void p2Lose();
	void p2Gameover();
	void p2Piece(string piece);
	void p2Attack(string line);
	//void configure();
        void setConnect(QString status)
        {
            if(status == "Connected") {
                startNetButton->setEnabled(false);
                endNetButton->setEnabled(true);
            }
            else {
                startNetButton->setEnabled(true);
                endNetButton->setEnabled(false);
            }
        };
        void netStart(QString mode);
 };

 #endif

