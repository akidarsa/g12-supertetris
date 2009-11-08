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
     boardTwo = new TetrisBoard;



/*     startButton = new QPushButton(tr("&Start"));
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
     configureButtonTwo->setFocusPolicy(Qt::NoFocus); */

     //connect(startButton, SIGNAL(clicked()), board, SLOT(start()));
     //connect(startButton, SIGNAL(clicked()), boardTwo, SLOT(start())); //Alex
     //connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
     //connect(pauseButton, SIGNAL(clicked()), board, SLOT(pause()));
     //connect(pauseButton, SIGNAL(clicked()), boardTwo, SLOT(pause()));	//Alex
     //connect(demoButton, SIGNAL(clicked()), board, SLOT(startDemo())); //Alex
     //connect(demoButton, SIGNAL(clicked()), boardTwo, SLOT(startDemo())); //Alex
	 


     //connect(configureButton, SIGNAL(clicked()), this, SLOT(keyConfig()));
     //connect(configureButtonTwo, SIGNAL(clicked()), this, SLOT(keyConfigTwo()));
	 //connect(configOneButton, SIGNAL(clicked()), this, SLOT(keyConfig));
	 //connect(configTwoButton, SIGNAL(clicked()), this, SLOT(keyConfigTwo));
	 //connect(exitButton, SIGNAL(clicked()), this, SLOT(sys.exit()));



     //connect(board, SIGNAL(scoreChanged(int)), scoreLcd, SLOT(display(int)));
     //connect(board, SIGNAL(levelChanged(int)), levelLcd, SLOT(display(int)));
     //connect(board, SIGNAL(linesRemovedChanged(int)),linesLcd, SLOT(display(int)));

     createStatus();
     createStatus2();
     createControl();
     connect(startButton, SIGNAL(clicked()), board, SLOT(start()));
     connect(startButton, SIGNAL(clicked()), boardTwo, SLOT(start()));
     connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
     connect(pauseButton, SIGNAL(clicked()), board, SLOT(pause()));
     connect(pauseButton, SIGNAL(clicked()), boardTwo, SLOT(pause()));
     connect(demoButton, SIGNAL(clicked()), boardTwo, SLOT(startDemo()));
     connect(configureButton, SIGNAL(clicked()), this, SLOT(keyConfig()));
     connect(configureButtonTwo, SIGNAL(clicked()), this, SLOT(keyConfigTwo()));
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
     connect(board, SIGNAL(advChanged(int)), ui_advantage1, SLOT(setNum(int)));
     connect(boardTwo, SIGNAL(advChanged(int)), ui_advantage2, SLOT(setNum(int)));
     connect(board, SIGNAL(linesRemovedChanged(int)),linesLcd, SLOT(display(int)));
     connect(boardTwo, SIGNAL(linesRemovedChanged(int)), linesLcd2, SLOT(display(int)));
     connect(board, SIGNAL(timeToAddLines(TetrisShape*)), boardTwo, SLOT(addLines(TetrisShape*)));
     connect(boardTwo, SIGNAL(timeToAddLines(TetrisShape*)), board, SLOT(addLines(TetrisShape*)));
     connect(board, SIGNAL(iLost(bool)), boardTwo, SLOT(gameOver(bool)));
     connect(boardTwo, SIGNAL(iLost(bool)), board, SLOT(gameOver(bool)));

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



  nextPieceLabel = new QLabel;
  nextPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
  nextPieceLabel->setAlignment(Qt::AlignCenter);
  board->setNextPieceLabel(nextPieceLabel);

	
  nextPieceLabel2 = new QLabel;
  nextPieceLabel2->setFrameStyle(QFrame::Box | QFrame::Raised);
  nextPieceLabel2->setAlignment(Qt::AlignCenter);
  boardTwo->setNextPieceLabel(nextPieceLabel2);
     //layout->addWidget(createLabel(tr("NEXT")), 0, 0);
     //layout->addWidget(nextPieceLabel, 1, 0);
     //layout->addWidget(configureButton, 4, 0);
     //layout->addWidget(configureButtonTwo, 5, 0);
     //layout->addWidget(startButton, 2, 0);
     layout->addWidget(ui_statusGroup, 0, 0);
     layout->addWidget(board, 0, 1, 5, 1);
     layout->addWidget(boardTwo, 0, 2, 5, 1);
     //layout->addWidget(test, 0, 1, 6, 1);
     layout->addWidget(ui_statusGroup2, 0, 3);
     layout->addWidget(ui_controlGroup, 5, 0, 1, 4);
     //layout->addWidget(createLabel(tr("LINES REMOVED")), 2, 3);
     //layout->addWidget(linesLcd, 3, 3);
     //layout->addWidget(quitButton, 4, 3);
     //layout->addWidget(pauseButton, 5, 3);
     //layout->addWidget(demoButton, 3, 0);

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
     //resize(550, 370); //original size
     resize(1200, 640);
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
  QLabel * advantage1 = new QLabel("Advantage: ");
  ui_advantage1 = new QLabel("     ");
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
  QLabel * advantage2 = new QLabel("Advantage: ");
  ui_advantage2 = new QLabel("     ");
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
  statusLayout2 -> addWidget(advantage2, 6, 0);
  statusLayout2 -> addWidget(ui_advantage2, 6, 1);

  ui_statusGroup2 = new QGroupBox(tr("Player 2"));
  ui_statusGroup2 -> setLayout(statusLayout2);
}

void TetrisWindow::createControl()
{
    QGridLayout * controlLayout = new QGridLayout;
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
    controlLayout -> addWidget(startButton, 0, 0);
    controlLayout -> addWidget(pauseButton, 1, 0);
    controlLayout -> addWidget(configureButton, 0, 1);
    controlLayout -> addWidget(configureButtonTwo, 1, 1);
    controlLayout -> addWidget(demoButton, 0, 2);
    controlLayout -> addWidget(quitButton, 1, 2);
    ui_controlGroup = new QGroupBox(tr("Menu"));
    ui_controlGroup -> setLayout(controlLayout);
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
	templeftVar = leftVar;
	temprightVar = rightVar;
	temprotRightVar = rotRightVar;
	tempdropVar = dropVar;
	tempmdropVar = mdropVar;

    TetrixKey dialog;
    board->pause();
	boardTwo->pause();
    dialog.exec();
    leftVar = dialog.getKey(TetrixKey::LEFT);
    rightVar = dialog.getKey(TetrixKey::RIGHT);
    rotRightVar = dialog.getKey(TetrixKey::ROTATE);
    dropVar = dialog.getKey(TetrixKey::SOFTDOWN);
    mdropVar = dialog.getKey(TetrixKey::MAGICDOWN);


	if(leftVar == 0)
	{
		leftVar = templeftVar;
	}
	if(rightVar == 0)
	{
		rightVar = temprightVar;
	}
	if(rotRightVar == 0)
	{
    rotRightVar = temprotRightVar;
	}
	if(dropVar == 0)
	{
    dropVar = tempdropVar;
	}
	if(mdropVar == 0)
	{
    mdropVar = tempmdropVar;
	}

    board->pause();
	boardTwo->pause();
}

void TetrisWindow::keyConfig() 
{
	templeftVar = leftVarTwo;
	temprightVar = rightVarTwo;
	temprotRightVar = rotRightVarTwo;
	tempdropVar = dropVarTwo;
	tempmdropVar = mdropVarTwo;

    TetrixKey dialog;
    board->pause();
	boardTwo->pause();
    dialog.exec();
    leftVarTwo = dialog.getKey(TetrixKey::LEFT);
    rightVarTwo = dialog.getKey(TetrixKey::RIGHT);
    rotRightVarTwo = dialog.getKey(TetrixKey::ROTATE);
    dropVarTwo = dialog.getKey(TetrixKey::SOFTDOWN);
    mdropVarTwo = dialog.getKey(TetrixKey::MAGICDOWN);

	if(leftVarTwo == 0)
	{
		leftVarTwo = templeftVar;
	}
	if(rightVarTwo == 0)
	{
		rightVarTwo = temprightVar;
	}
	if(rotRightVarTwo == 0)
	{
    rotRightVarTwo = temprotRightVar;
	}
	if(dropVarTwo == 0)
	{
    dropVarTwo = tempdropVar;
	}
	if(mdropVarTwo == 0)
	{
    mdropVarTwo = tempmdropVar;
	}
    
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
