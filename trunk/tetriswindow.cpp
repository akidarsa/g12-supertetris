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
 #include "tetriswindow.h"

 TetrisWindow::TetrisWindow()
 {
     board = new TetrisBoard;

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
     configureButton = new QPushButton(tr("&Configure"));
     configureButton->setFocusPolicy(Qt::NoFocus);

     connect(startButton, SIGNAL(clicked()), board, SLOT(start()));
     connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
     connect(pauseButton, SIGNAL(clicked()), board, SLOT(pause()));
     connect(demoButton, SIGNAL(clicked()), board, SLOT(startDemo()));
     connect(configureButton, SIGNAL(clicked()), board, SLOT(configure()));
     //connect(board, SIGNAL(scoreChanged(int)), scoreLcd, SLOT(display(int)));
     //connect(board, SIGNAL(levelChanged(int)), levelLcd, SLOT(display(int)));
     connect(board, SIGNAL(linesRemovedChanged(int)),
             linesLcd, SLOT(display(int)));

     createStatus();
     connect(board, SIGNAL(pieceChanged(int)), ui_pieceCountLabel, SLOT(setNum(int)));
     connect(board, SIGNAL(piece4Changed(int)), ui_piece4Label, SLOT(setNum(int)));
     connect(board, SIGNAL(piece5Changed(int)), ui_piece5Label, SLOT(setNum(int)));
     connect(board, SIGNAL(piece6Changed(int)), ui_piece6Label, SLOT(setNum(int)));
     connect(board, SIGNAL(piece7Changed(int)), ui_piece7Label, SLOT(setNum(int)));
     connect(board, SIGNAL(blocksChanged(int)), ui_blockCountLabel, SLOT(setNum(int)));
     QGridLayout *layout = new QGridLayout;
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
     setLayout(layout);

     setWindowTitle(tr("Super Tetris"));
     //resize(550, 370); //original size
     resize(750, 470);
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
  ui_statusGroup = new QGroupBox(tr("Player Stats"));
  ui_statusGroup -> setLayout(statusLayout);
}
