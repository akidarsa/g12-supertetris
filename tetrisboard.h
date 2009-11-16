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

 #ifndef TETRISBOARD_H
 #define TETRISBOARD_H

 #include <QBasicTimer>
 #include <QFrame>
 #include <QPointer>
 #include <string>
 #include "tetrispiece.h"
 #include "PieceMovement.h"
 #include "tetrisdemo.h"
 using namespace std;

 class QLabel;

 class TetrisBoard : public QFrame
 {
     Q_OBJECT

 public:
     TetrisBoard(QWidget *parent = 0);

     void setNextPieceLabel(QLabel *label);
     QSize sizeHint() const;
     QSize minimumSizeHint() const;
     void serverMove(char a);
     void dropDown();
     void dropDown(int b);
     void oneLineDown();
     void oneLineDown(int a);
	 bool moveLeft();
	 bool moveRight();
	 bool rotateRight();
	 bool rotateLeft();
	 void moveLeft(int a);
	 void moveRight(int a);
	 void rotateRight(int a);
	 void rotateLeft(int a);

 public slots:
     void start();
     void pause();
     void startDemo();
     //void configure();
     //void saveKeys();
     void bufferLines(TetrisShape *line);
     void gameOver(bool winOrLose) {
         isGameOver = true;
         curPiece.setShape(NoShape);
         timer.stop();
         isStarted = false;
         if (winOrLose) {
             isWin = true;
         }
         else {
             isWin = false;
         }
         update();
     }
     void reset();
     void setConnect(QString status) {
         if(status == "Connected") {
             isConnected = true;
         }
         else {
             isConnected = false;
         }
     }
     void getNetPiece(string piece) {
         netPiece = piece;
     }
     

 signals:
     void scoreChanged(int score);
     void levelChanged(int level);
     void linesRemovedChanged(int numLines);
     void pieceChanged(int numPiecesDropped);
     void piece4Changed(int num4Pieces);
     void piece5Changed(int num5Pieces);
     void piece6Changed(int num6Pieces);
     void piece7Changed(int num7Pieces);
     void blocksChanged(int numBlocks);
     void addLineToBuffer(TetrisShape *line);
     void iLost(bool winOrLose);
     void gameIsStart(bool started);
     void toNetCommand(QString command);

protected:
     void paintEvent(QPaintEvent *event);
     //void keyPressEvent(QKeyEvent *event);
     void timerEvent(QTimerEvent *event);

 private:
     enum { BoardWidth = 20, BoardHeight = 30 };

     TetrisShape &shapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }
     int timeoutTime() { return 1000 / (1 + level); }
     int squareWidth() { return contentsRect().width() / BoardWidth; }
     int squareHeight() { return contentsRect().height() / BoardHeight; }
     void clearBoard();
     void pieceDropped(int dropHeight);
     void removeFullLines();
     void newPiece();
     void showNextPiece();
     bool tryMove(const TetrisPiece &newPiece, int newX, int newY);
     void drawSquare(QPainter &painter, int x, int y, TetrisShape shape);
     void drawSquare(QPainter &painter, int x, int y, TetrisPiece shape);
     void clearBuffer();
     void addLines();
     QBasicTimer timer;
     QPointer<QLabel> nextPieceLabel;
     bool isStarted;
     bool isGameOver;
     bool isWin; //must be placed after isGameOver is true
     bool isPaused;
     bool isInDemo;
     bool isTested;
     bool isWaitingAfterLine;
     bool isConnected;
     TetrisPiece curPiece;
     TetrisPiece nextPiece;
     int curX;
     int curY;
     int numLinesRemoved;
     int numPiecesDropped;
     int score;
     int level;
     int num4Pieces; //counts number of 4 block pieces
     int num5Pieces; //counts number of 5 block pieces
     int num6Pieces; //counts number of 6 block pieces
     int num7Pieces; //counts number of 7 block pieces
     int numBlocks; //counts number of blocks in pieces
     TetrisShape board[BoardWidth * BoardHeight];
     FILE* fp;
     int Up;
     int Down;
     int Left;
     int Right;
     int dropLineV;
     int dropOneLineV;
     bool singlePlay;
     bool attackMode;
     TetrisShape lineBuffer[BoardHeight][BoardWidth];
     int linesinBuffer;
     bool linesHaveBeenAdded; //checks if lines have been added to other board
     string netPiece;
     
 };

 #endif

