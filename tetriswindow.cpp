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

 #include <QtGui>
 #include <iostream>

 #include "tetrisboard.h"
#include "tetrixkey.h"
#include "tetriswindow.h"
//#include "tetrisnetwork.h"

using namespace std;

 TetrisWindow::TetrisWindow()
 {

    p1LftKey = Qt::Key_A;
    p1RgtKey = Qt::Key_D;
    p1RotKey = Qt::Key_W;
    p1DwnKey = Qt::Key_S;
    p1DrpKey = Qt::Key_B;

    p2LftKey = Qt::Key_Left;
    p2RgtKey = Qt::Key_Right;
    p2RotKey = Qt::Key_Up;
    p2DwnKey = Qt::Key_Down;
    p2DrpKey = Qt::Key_Space;

	setFocusPolicy(Qt::StrongFocus);
	 
     board = new TetrisBoard;
     boardTwo = new TetrisBoard;

	verizon = new TetrisNetwork;

     createStatus();
     createStatus2();
     createControl();
     /*Single player start*/
     connect(startButton, SIGNAL(clicked()), board, SLOT(start()));
     connect(startButton, SIGNAL(clicked()), boardTwo, SLOT(reset()));
     /*Human vs. Human start*/
     connect(startHHButton, SIGNAL(clicked()), board, SLOT(start()));
     connect(startHHButton, SIGNAL(clicked()), boardTwo, SLOT(start()));
     /*Human vs. Computer start*/
     connect(startHCButton, SIGNAL(clicked()), board, SLOT(start()));
     connect(startHCButton, SIGNAL(clicked()), boardTwo, SLOT(startDemo()));
     /*Computer vs. Computer start*/
     connect(startCCButton, SIGNAL(clicked()), board, SLOT(startDemo()));
     connect(startCCButton, SIGNAL(clicked()), boardTwo, SLOT(startDemo()));
     /*Network Controls*/
     connect(startNetButton, SIGNAL(clicked()), verizon, SLOT(exec()));
     connect(verizon, SIGNAL(netConnected(QString)), ui_netStatus, SLOT(setText(QString)));
     connect(verizon, SIGNAL(netConnected(QString)), board, SLOT(setConnected(QString))); 
     connect(endNetButton, SIGNAL(clicked()), verizon, SLOT(closeSocket()));
     connect(board, SIGNAL(toNetCommand(QString)), verizon, SLOT(command(QString)));
     //connect(verizon, SIGNAL(fromNetCommand(QString)), boardTwo, SLOT(
     /*other controls*/
     connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
     connect(pauseButton, SIGNAL(clicked()), board, SLOT(pause()));
     connect(pauseButton, SIGNAL(clicked()), boardTwo, SLOT(pause()));
     connect(configureButton, SIGNAL(clicked()), this, SLOT(keyConfig()));
     /*updates stats*/
     connect(board, SIGNAL(pieceChanged(int)), ui_pieceCountLabel, SLOT(setNum(int)));
     connect(board, SIGNAL(piece4Changed(int)), ui_piece4Label, SLOT(setNum(int)));
     connect(board, SIGNAL(piece5Changed(int)), ui_piece5Label, SLOT(setNum(int)));
     connect(board, SIGNAL(piece6Changed(int)), ui_piece6Label, SLOT(setNum(int)));
     connect(board, SIGNAL(piece7Changed(int)), ui_piece7Label, SLOT(setNum(int)));
     connect(board, SIGNAL(blocksChanged(int)), ui_blockCountLabel, SLOT(setNum(int)));
     connect(boardTwo, SIGNAL(pieceChanged(int)), ui_pieceCountLabel2, SLOT(setNum(int)));
     connect(boardTwo, SIGNAL(piece4Changed(int)), ui_piece4Label2, SLOT(setNum(int)));
     connect(boardTwo, SIGNAL(piece5Changed(int)), ui_piece5Label2, SLOT(setNum(int)));
     connect(boardTwo, SIGNAL(piece6Changed(int)), ui_piece6Label2, SLOT(setNum(int)));
     connect(boardTwo, SIGNAL(piece7Changed(int)), ui_piece7Label2, SLOT(setNum(int)));
     connect(boardTwo, SIGNAL(blocksChanged(int)), ui_blockCountLabel2, SLOT(setNum(int)));
     /*deals with line removal*/
     connect(board, SIGNAL(linesRemovedChanged(int)),linesLcd, SLOT(display(int)));
     connect(boardTwo, SIGNAL(linesRemovedChanged(int)), linesLcd2, SLOT(display(int)));
     connect(board, SIGNAL(timeToAddLines(TetrisShape*)), boardTwo, SLOT(addLines(TetrisShape*)));
     connect(boardTwo, SIGNAL(timeToAddLines(TetrisShape*)), board, SLOT(addLines(TetrisShape*)));
     connect(board, SIGNAL(iLost(bool)), boardTwo, SLOT(gameOver(bool)));
     connect(boardTwo, SIGNAL(iLost(bool)), board, SLOT(gameOver(bool)));
     connect(board, SIGNAL(gameIsStart(bool)), this, SLOT(keyGrabStart(bool)));
     QGridLayout *layout = new QGridLayout;

  nextPieceLabel = new QLabel;
  nextPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
  nextPieceLabel->setAlignment(Qt::AlignCenter);
  board->setNextPieceLabel(nextPieceLabel);

	
  nextPieceLabel2 = new QLabel;
  nextPieceLabel2->setFrameStyle(QFrame::Box | QFrame::Raised);
  nextPieceLabel2->setAlignment(Qt::AlignCenter);
  boardTwo->setNextPieceLabel(nextPieceLabel2);
     layout->addWidget(ui_statusGroup, 0, 0);
     layout->addWidget(board, 0, 1, 5, 1);
     layout->addWidget(boardTwo, 0, 2, 5, 1);
     layout->addWidget(ui_statusGroup2, 0, 3);
     layout->addWidget(ui_controlGroup, 5, 0, 1, 4);
  layout -> addWidget(createLabel(tr("NEXT")), 1, 0);
  layout -> addWidget(nextPieceLabel, 2, 0);
  layout -> addWidget(createLabel(tr("LINES REMOVED")), 3, 0);
  layout -> addWidget(linesLcd, 4, 0);

  layout -> addWidget(createLabel(tr("NEXT")), 1, 3);
  layout -> addWidget(nextPieceLabel2, 2, 3);
  layout -> addWidget(createLabel(tr("LINES REMOVED")), 3, 3);
  layout -> addWidget(linesLcd2, 4, 3);
     setLayout(layout);

     setWindowTitle(tr("Super Tetris"));
     resize(1200,800);
 }

 QLabel *TetrisWindow::createLabel(const QString &text)
 {
     QLabel *lbl = new QLabel(text);
     lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
     return lbl;
 }

void TetrisWindow::createStatus()
{
  QGridLayout * statusLayout = new QGridLayout;
  linesLcd = new QLCDNumber(5);
  linesLcd->setSegmentStyle(QLCDNumber::Filled);
  QLabel * pieceCount = new QLabel("# of pieces: ");
  ui_pieceCountLabel = new QLabel("      ");
  QLabel * piece4 = new QLabel("4 block pieces: ");
  ui_piece4Label = new QLabel("      ");
  QLabel * piece5 = new QLabel("5 block pieces: ");
  ui_piece5Label = new QLabel("      ");
  QLabel * piece6 = new QLabel("6 block pieces: ");
  ui_piece6Label = new QLabel("      ");
  QLabel * piece7 = new QLabel("7 block pieces: ");
  ui_piece7Label = new QLabel("      ");
  QLabel * blockCount = new QLabel("# of blocks: ");
  ui_blockCountLabel = new QLabel("      ");
  statusLayout -> addWidget(pieceCount, 0, 0);
  statusLayout -> addWidget(ui_pieceCountLabel, 0, 1);
  statusLayout -> addWidget(piece4, 1, 0);
  statusLayout -> addWidget(ui_piece4Label, 1, 1);
  statusLayout -> addWidget(piece5, 2, 0);
  statusLayout -> addWidget(ui_piece5Label, 2, 1);
  statusLayout -> addWidget(piece6, 3, 0);
  statusLayout -> addWidget(ui_piece6Label, 3, 1);
  statusLayout -> addWidget(piece7, 4, 0);
  statusLayout -> addWidget(ui_piece7Label, 4, 1);
  statusLayout -> addWidget(blockCount, 5, 0);
  statusLayout -> addWidget(ui_blockCountLabel, 5, 1);
  ui_statusGroup = new QGroupBox(tr("Player 1"));
  ui_statusGroup -> setLayout(statusLayout);
}

void TetrisWindow::createStatus2()
{
  QGridLayout * statusLayout2 = new QGridLayout;
  linesLcd2 = new QLCDNumber(5);
  linesLcd2->setSegmentStyle(QLCDNumber::Filled);
  QLabel * pieceCount = new QLabel("# of pieces: ");
  ui_pieceCountLabel2 = new QLabel("      ");
  QLabel * piece4 = new QLabel("4 block pieces: ");
  ui_piece4Label2 = new QLabel("      ");
  QLabel * piece5 = new QLabel("5 block pieces: ");
  ui_piece5Label2 = new QLabel("      ");
  QLabel * piece6 = new QLabel("6 block pieces: ");
  ui_piece6Label2 = new QLabel("      ");
  QLabel * piece7 = new QLabel("7 block pieces: ");
  ui_piece7Label2 = new QLabel("      ");
  QLabel * blockCount = new QLabel("# of blocks: ");
  ui_blockCountLabel2 = new QLabel("      ");
  statusLayout2 -> addWidget(pieceCount, 0, 0);
  statusLayout2 -> addWidget(ui_pieceCountLabel2, 0, 1);
  statusLayout2 -> addWidget(piece4, 1, 0);
  statusLayout2 -> addWidget(ui_piece4Label2, 1, 1);
  statusLayout2 -> addWidget(piece5, 2, 0);
  statusLayout2 -> addWidget(ui_piece5Label2, 2, 1);
  statusLayout2 -> addWidget(piece6, 3, 0);
  statusLayout2 -> addWidget(ui_piece6Label2, 3, 1);
  statusLayout2 -> addWidget(piece7, 4, 0);
  statusLayout2 -> addWidget(ui_piece7Label2, 4, 1);
  statusLayout2 -> addWidget(blockCount, 5, 0);
  statusLayout2 -> addWidget(ui_blockCountLabel2, 5, 1);
  ui_statusGroup2 = new QGroupBox(tr("Player 2"));
  ui_statusGroup2 -> setLayout(statusLayout2);
}

void TetrisWindow::createControl()
{
    QGridLayout * controlLayout = new QGridLayout;
    //Local buttons start here
    QGridLayout * localLayout = new QGridLayout;
    startButton = new QPushButton(tr("&Single Player"));
    startButton->setFocusPolicy(Qt::NoFocus);
    startHHButton = new QPushButton(tr("&Human vs. Human"));
    startHHButton->setFocusPolicy(Qt::NoFocus);
    startHCButton = new QPushButton(tr("Human &vs. Computer"));
    startHCButton->setFocusPolicy(Qt::NoFocus);
    startCCButton = new QPushButton(tr("&Computer vs. Computer"));
    startCCButton->setFocusPolicy(Qt::NoFocus);
    localLayout -> addWidget(startButton, 0, 0);
    localLayout -> addWidget(startHHButton, 1, 0);
    localLayout -> addWidget(startHCButton, 2, 0);
    localLayout -> addWidget(startCCButton, 3, 0);
    ui_localGroup = new QGroupBox(tr("Start - Local"));
    ui_localGroup -> setLayout(localLayout);
    //Network Buttons Start here, local ends
    QGridLayout * networkLayout = new QGridLayout;
    startNetButton = new QPushButton(tr("&Play on Network"));
    startNetButton->setFocusPolicy(Qt::NoFocus);
    QLabel * netStatusLabel = new QLabel("Network Status: ");
    ui_netStatus = new QLabel("Disconnected");
    endNetButton = new QPushButton(tr("&Disconnect"));
    endNetButton->setFocusPolicy(Qt::NoFocus);
    networkLayout -> addWidget(startNetButton, 0, 0);
    networkLayout -> addWidget(netStatusLabel, 1, 0);
    networkLayout -> addWidget(ui_netStatus, 1, 1);
    networkLayout -> addWidget(endNetButton, 2, 0);
    ui_networkGroup = new QGroupBox(tr("Start - Network"));
    ui_networkGroup -> setLayout(networkLayout);
    //Network buttons end here
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setFocusPolicy(Qt::NoFocus);
    configureButton = new QPushButton(tr("&Key Configure"));
    configureButton->setFocusPolicy(Qt::NoFocus);
    controlLayout -> addWidget(ui_localGroup, 0 , 0, 4, 1);
    controlLayout -> addWidget(ui_networkGroup, 0, 1, 4, 1);
    controlLayout -> addWidget(configureButton, 0, 2);
    controlLayout -> addWidget(pauseButton, 1, 2);
    controlLayout -> addWidget(quitButton, 3, 2);
    ui_controlGroup = new QGroupBox(tr("Menu"));
    ui_controlGroup -> setLayout(controlLayout);
}

void TetrisWindow::keyPressEvent(QKeyEvent *event) 
{
    QWidget::keyPressEvent(event);

	if (keyStarted == 1)
	{

    if ((event->key()) == p1LftKey) 
	{
        board->moveLeft(1);
    } 
	else if ((event->key()) == p1RgtKey) 
	{
        board->moveRight(1);
    } 
	else if ((event->key()) == p1RotKey) 
	{
        board->rotateRight(1);
    } 
	else if ((event->key()) == p1DrpKey) 
	{
        board->dropDown(1);
    } 
	else if ((event->key()) == p1DwnKey) 
	{
        board->oneLineDown(1);
    } 
    else if ((event->key()) == p2LftKey) 
	{
        boardTwo->moveLeft(1);
    } 
	else if ((event->key()) == p2RgtKey) 
	{
        boardTwo->moveRight(1);
    } 
	else if ((event->key()) == p2RotKey) 
	{
        boardTwo->rotateRight(1);
    } 
	else if ((event->key()) == p2DrpKey) 
	{
        boardTwo->dropDown(1);
    } 
	else if ((event->key()) == p2DwnKey) 
	{
        boardTwo->oneLineDown(1);
	}
	else 
	{
        QWidget::keyPressEvent(event);
    }
	}

}

void TetrisWindow::keyConfig() 
{
	tempLftVar[0] = p1LftKey;
	tempRgtVar[0] = p1RgtKey;
	tempRotVar[0] = p1RotKey;
	tempDwnVar[0] = p1DwnKey;
	tempDrpVar[0] = p1DrpKey;

	tempLftVar[1] = p2LftKey;
	tempRgtVar[1] = p2RgtKey;
	tempRotVar[1] = p2RotKey;
	tempDwnVar[1] = p2DwnKey;
	tempDrpVar[1] = p2DrpKey;

    TetrixKey dialog;
    board->pause();
	boardTwo->pause();
    dialog.exec();
    p1LftKey = dialog.getKey(TetrixKey::LFT1);
    p1RgtKey = dialog.getKey(TetrixKey::RGT1);
    p1RotKey = dialog.getKey(TetrixKey::ROT1);
    p1DwnKey = dialog.getKey(TetrixKey::DWN1);
    p1DrpKey = dialog.getKey(TetrixKey::DRP1);

    p2LftKey = dialog.getKey(TetrixKey::LFT2);
    p2RgtKey = dialog.getKey(TetrixKey::RGT2);
    p2RotKey = dialog.getKey(TetrixKey::ROT2);
    p2DwnKey = dialog.getKey(TetrixKey::DWN2);
    p2DrpKey = dialog.getKey(TetrixKey::DRP2);

	if(p2LftKey == 0 or p2LftKey == p1LftKey)
	{
		p1LftKey = tempLftVar[0];
		p2LftKey = tempLftVar[1];
	}
	if(p2RgtKey == 0 or p2RgtKey == p1RgtKey)
	{
		p1RgtKey = tempRgtVar[0];
		p2RgtKey = tempRgtVar[1];
	}
	if(p2RotKey == 0 or p2RotKey == p1RotKey)
	{
    		p1RotKey = tempRotVar[0];
    		p2RotKey = tempRotVar[1];
	}
	if(p2DwnKey == 0 or p2DwnKey == p1DwnKey)
	{
    		p1DwnKey = tempDwnVar[0];
    		p2DwnKey = tempDwnVar[1];
	}
	if(p2DrpKey == 0 or p2DrpKey == p1DrpKey)
	{
		p1DrpKey = tempDrpVar[0];
		p2DrpKey = tempDrpVar[1];
	}
    
	board->pause();
	boardTwo->pause();
}

