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

using namespace std;

 TetrisWindow::TetrisWindow()
 {

	//myDialog = new ConfigDialog;

    leftVar = Qt::Key_Left;
    rightVar = Qt::Key_Right;
    rotRightVar = Qt::Key_Up;
    dropVar = Qt::Key_Down;
    mdropVar = Qt::Key_Space;

    leftVarTwo = Qt::Key_A;
    rightVarTwo = Qt::Key_D;
    rotRightVarTwo = Qt::Key_W;
    dropVarTwo = Qt::Key_S;
    mdropVarTwo = Qt::Key_B;

	setFocusPolicy(Qt::StrongFocus);
	 
     board = new TetrisBoard;
// This part onward till the next breakpoint is edited by Alex

	 boardTwo = new TetrisBoard;

     /**connect(boardTwo, SIGNAL(pieceChanged(int)), ui_pieceCountLabel, SLOT(setNum(int)));
     connect(boardTwo, SIGNAL(piece4Changed(int)), ui_piece4Label, SLOT(setNum(int)));
     connect(boardTwo, SIGNAL(piece5Changed(int)), ui_piece5Label, SLOT(setNum(int)));
     connect(boardTwo, SIGNAL(piece6Changed(int)), ui_piece6Label, SLOT(setNum(int)));
     connect(boardTwo, SIGNAL(piece7Changed(int)), ui_piece7Label, SLOT(setNum(int)));
     connect(boardTwo, SIGNAL(blocksChanged(int)), ui_blockCountLabel, SLOT(setNum(int)));**/


// This is the end of the edit done by Alex

     nextPieceLabel = new QLabel;
     nextPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
     nextPieceLabel->setAlignment(Qt::AlignCenter);
     board->setNextPieceLabel(nextPieceLabel);

     //scoreLcd = new QLCDNumber(5);
     //scoreLcd->setSegmentStyle(QLCDNumber::Filled);
     //levelLcd = new QLCDNumber(2);
     //levelLcd->setSegmentStyle(QLCDNumber::Filled);
     linesLcd = new QLCDNumber(5);
     linesLcd->setSegmentStyle(QLCDNumber::Filled);

     startButton = new QPushButton(tr("&Start"));
     startButton->setFocusPolicy(Qt::NoFocus);
     quitButton = new QPushButton(tr("&Quit"));
     quitButton->setFocusPolicy(Qt::NoFocus);
     pauseButton = new QPushButton(tr("&Pause"));
     pauseButton->setFocusPolicy(Qt::NoFocus);
     demoButton = new QPushButton(tr("&Demo"));
     demoButton->setFocusPolicy(Qt::NoFocus);
     configureButton = new QPushButton(tr("&Configure Player 1"));
     configureButton->setFocusPolicy(Qt::NoFocus);
     configureButtonTwo = new QPushButton(tr("&Configure Player 2"));
     configureButtonTwo->setFocusPolicy(Qt::NoFocus);

     connect(startButton, SIGNAL(clicked()), board, SLOT(start()));
     connect(startButton, SIGNAL(clicked()), boardTwo, SLOT(start())); //Alex
     connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
     connect(pauseButton, SIGNAL(clicked()), board, SLOT(pause()));
     connect(pauseButton, SIGNAL(clicked()), boardTwo, SLOT(pause()));	//Alex
     //connect(demoButton, SIGNAL(clicked()), board, SLOT(startDemo())); //Alex
     connect(demoButton, SIGNAL(clicked()), boardTwo, SLOT(startDemo())); //Alex
	 


     connect(configureButton, SIGNAL(clicked()), this, SLOT(keyConfig()));
     connect(configureButtonTwo, SIGNAL(clicked()), this, SLOT(keyConfigTwo()));
	 //connect(configOneButton, SIGNAL(clicked()), this, SLOT(keyConfig));
	 //connect(configTwoButton, SIGNAL(clicked()), this, SLOT(keyConfigTwo));
	 //connect(exitButton, SIGNAL(clicked()), this, SLOT(sys.exit()));



     //connect(board, SIGNAL(scoreChanged(int)), scoreLcd, SLOT(display(int)));
     //connect(board, SIGNAL(levelChanged(int)), levelLcd, SLOT(display(int)));
     connect(board, SIGNAL(linesRemovedChanged(int)),linesLcd, SLOT(display(int)));

     createStatus();
     connect(board, SIGNAL(pieceChanged(int)), ui_pieceCountLabel, SLOT(setNum(int)));
     connect(board, SIGNAL(piece4Changed(int)), ui_piece4Label, SLOT(setNum(int)));
     connect(board, SIGNAL(piece5Changed(int)), ui_piece5Label, SLOT(setNum(int)));
     connect(board, SIGNAL(piece6Changed(int)), ui_piece6Label, SLOT(setNum(int)));
     connect(board, SIGNAL(piece7Changed(int)), ui_piece7Label, SLOT(setNum(int)));
     connect(board, SIGNAL(blocksChanged(int)), ui_blockCountLabel, SLOT(setNum(int)));
     connect(board, SIGNAL(advChanged(int)), ui_advantage1, SLOT(setNum(int)));
     connect(boardTwo, SIGNAL(advChanged(int)), ui_advantage2, SLOT(setNum(int)));
     connect(boardTwo, SIGNAL(linesRemovedChanged(int)), ui_linesRemoved2, SLOT(setNum(int)));
     connect(board, SIGNAL(timeToAddLines(int,TetrisPiece,int)), boardTwo, SLOT(addLines(int,TetrisPiece,int)));
     connect(boardTwo, SIGNAL(timeToAddLines(int,TetrisPiece,int)), board, SLOT(addLines(int,TetrisPiece,int)));
     connect(board, SIGNAL(iLost(bool)), boardTwo, SLOT(gameOver(bool)));
     connect(boardTwo, SIGNAL(iLost(bool)), board, SLOT(gameOver(bool)));

	 /**QWidget *test = new QWidget;
	 QGridLayout *lout = new QGridLayout;
     lout->addWidget(board, 0, 1, 6, 1);
     lout->addWidget(boardTwo, 0, 2, 6, 1);
	 test->setLayout(lout);
	 //test->setFocusPolicy(Qt::StrongFocus);
	 QKeyEvent *event;
	 //test->keyPressEvent(event);
	 setFocusPolicy(Qt::StrongFocus);
	 QWidget::keyPressEvent(event);
	 cout << (int)(event->key()) << endl;
	 emit keyGrabber(event);**/
     QGridLayout *layout = new QGridLayout;

/**
     layout->addWidget(createLabel(tr("NEXT")), 0, 0);
     layout->addWidget(nextPieceLabel, 1, 0);
     //layout->addWidget(createLabel(tr("LEVEL")), 2, 0);
     //layout->addWidget(levelLcd, 3, 0);
     layout->addWidget(configureButton, 5, 0);
     layout->addWidget(startButton, 2, 0);
     layout->addWidget(board, 0, 1, 6, 1);
     //layout->addWidget(createLabel(tr("SCORE")), 0, 2);
     //layout->addWidget(scoreLcd, 1, 2);
     layout->addWidget(ui_statusGroup, 0, 2);
     layout->addWidget(createLabel(tr("LINES REMOVED")), 2, 2);
     layout->addWidget(linesLcd, 3, 2);
     layout->addWidget(quitButton, 4, 2);
     layout->addWidget(pauseButton, 5, 2);
     layout->addWidget(demoButton, 3, 0);
**/

// This part is edited by Alex
	
     layout->addWidget(createLabel(tr("NEXT")), 0, 0);
     layout->addWidget(nextPieceLabel, 1, 0);
	 layout->addWidget(configureButton, 4, 0);
     layout->addWidget(configureButtonTwo, 5, 0);
     layout->addWidget(startButton, 2, 0);
     layout->addWidget(board, 0, 1, 6, 1);
     layout->addWidget(boardTwo, 0, 2, 6, 1);
	 //layout->addWidget(test, 0, 1, 6, 1);
     layout->addWidget(ui_statusGroup, 0, 3);
     layout->addWidget(createLabel(tr("LINES REMOVED")), 2, 3);
     layout->addWidget(linesLcd, 3, 3);
     layout->addWidget(quitButton, 4, 3);
     layout->addWidget(pauseButton, 5, 3);
     layout->addWidget(demoButton, 3, 0);

// End of edit

     setLayout(layout);

     setWindowTitle(tr("Super Tetris"));
     //resize(550, 370); //original size
     resize(1200, 470);
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
  QLabel * advantage1 = new QLabel("Player 1 Adv.: ");
  ui_advantage1 = new QLabel("     ");
  QLabel * advantage2 = new QLabel("Player 2 Adv.: ");
  ui_advantage2 = new QLabel("     ");
  QLabel * linesRemoved2 = new QLabel("Player 2 Lines: ");
  ui_linesRemoved2 = new QLabel("     ");
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
  statusLayout -> addWidget(advantage1, 6, 0);
  statusLayout -> addWidget(ui_advantage1, 6, 1);
  statusLayout -> addWidget(advantage2, 7, 0);
  statusLayout -> addWidget(ui_advantage2, 7, 1);
  statusLayout -> addWidget(linesRemoved2, 8, 0);
  statusLayout -> addWidget(ui_linesRemoved2, 8, 1);
  ui_statusGroup = new QGroupBox(tr("Player Stats"));
  ui_statusGroup -> setLayout(statusLayout);
}

void TetrisWindow::keyPressEvent(QKeyEvent *event) 
{
    QWidget::keyPressEvent(event);

    if ((event->key()) == leftVar) 
	{
        boardTwo->moveLeft();
    } 
	else if ((event->key()) == rightVar) 
	{
        boardTwo->moveRight();
    } 
	else if ((event->key()) == rotRightVar) 
	{
        boardTwo->rotateRight();
    } 
	else if ((event->key()) == mdropVar) 
	{
        boardTwo->dropDown();
    } 
	else if ((event->key()) == dropVar) 
	{
        boardTwo->oneLineDown();
    } 
    else if ((event->key()) == leftVarTwo) 
	{
        board->moveLeft();
    } 
	else if ((event->key()) == rightVarTwo) 
	{
        board->moveRight();
    } 
	else if ((event->key()) == rotRightVarTwo) 
	{
        board->rotateRight();
    } 
	else if ((event->key()) == mdropVarTwo) 
	{
        board->dropDown();
    } 
	else if ((event->key()) == dropVarTwo) 
	{
        board->oneLineDown();
	}
	else 
	{
        QWidget::keyPressEvent(event);
    }

}

void TetrisWindow::keyConfigTwo() 
{
    TetrixKey dialog;
    board->pause();
	boardTwo->pause();
    dialog.exec();
    leftVar = dialog.getKey(TetrixKey::LEFT);
    rightVar = dialog.getKey(TetrixKey::RIGHT);
    rotRightVar = dialog.getKey(TetrixKey::ROTATE);
    dropVar = dialog.getKey(TetrixKey::SOFTDOWN);
    mdropVar = dialog.getKey(TetrixKey::MAGICDOWN);
    board->pause();
	boardTwo->pause();
}

void TetrisWindow::keyConfig() 
{
    TetrixKey dialog;
    board->pause();
	boardTwo->pause();
    dialog.exec();
    leftVarTwo = dialog.getKey(TetrixKey::LEFT);
    rightVarTwo = dialog.getKey(TetrixKey::RIGHT);
    rotRightVarTwo = dialog.getKey(TetrixKey::ROTATE);
    dropVarTwo = dialog.getKey(TetrixKey::SOFTDOWN);
    mdropVarTwo = dialog.getKey(TetrixKey::MAGICDOWN);
    board->pause();
	boardTwo->pause();
}

/*void TetrisWindow::configure()
{
	QWidget *test = new QWidget;
	test-> resize(200,300);
	QGridLayout *layout = new QGridLayout;
	configOneButton = new QPushButton(tr("Player 1"));
	configTwoButton = new QPushButton(tr("Player 2"));
	//exitButton = new QPushButton(tr("Exit"));
	setWindowTitle("Key Config");
	layout->addWidget(configOneButton, 0, 1);
	layout->addWidget(configTwoButton, 0, 2);
	//layout->addWidget(exitButton, 0, 3);
	test->setLayout(layout);
	test->show();
}*/
