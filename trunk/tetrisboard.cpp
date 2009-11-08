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

 #include "tetrisboard.h"
 #include "ConfigDialog.h"
#include<iostream>

using namespace std;

class ControlLineEdit;

 TetrisBoard::TetrisBoard(QWidget *parent)
     : QFrame(parent)
 {
     setFrameStyle(QFrame::Panel | QFrame::Sunken);
     //setFocusPolicy(Qt::StrongFocus);
     isStarted = false;
     isGameOver = false;
     isPaused = false;
     isInDemo = false;
     Up = (int) Qt::Key_Up;
     Down = (int) Qt::Key_Down;
     Left = (int) Qt::Key_Left;
     Right = (int) Qt::Key_Right;
     dropLineV = (int) Qt::Key_Space;
     dropOneLineV = (int) Qt::Key_D;
     clearBoard();
     fp = NULL;
     //myDialog = new ConfigDialog;
     singlePlay = false;
     advantage = 0;
 }

 void TetrisBoard::setNextPieceLabel(QLabel *label)
 {
     nextPieceLabel = label;
 }

 QSize TetrisBoard::sizeHint() const
 {
     return QSize(BoardWidth * 15 + frameWidth() * 2,
                  BoardHeight * 15 + frameWidth() * 2);
 }

 QSize TetrisBoard::minimumSizeHint() const
 {
     return QSize(BoardWidth * 5 + frameWidth() * 2,
                  BoardHeight * 5 + frameWidth() * 2);
 }

 void TetrisBoard::start()
 {
     if (isPaused)
         return;

     isStarted = true;
     isInDemo = false;
     isGameOver = false;
     isWaitingAfterLine = false;
     numLinesRemoved = 0;
     numPiecesDropped = 0;
     num4Pieces = 0;
     num5Pieces = 0;
     num6Pieces = 0;
     num7Pieces = 0;
     numBlocks = 0;
     score = 0;
     advantage = 0;
     level = 1;
     clearBoard();
     if (fp != NULL)
        fclose(fp);
     if (qApp->argc() == 3)
     {
         if (strcmp(qApp->argv()[1],"-f") == 0)
         {
                fp = fopen(qApp->argv()[2],"r");
         }
     }
     nextPiece.setFilePointer(fp);
     curPiece.setFilePointer(fp);
     nextPiece.setRandomShape();
     emit advChanged(advantage);
     emit linesRemovedChanged(numLinesRemoved);
     emit scoreChanged(score);
     emit levelChanged(level);
     emit pieceChanged(numPiecesDropped);
     emit piece4Changed(num4Pieces);
     emit piece5Changed(num5Pieces);
     emit piece6Changed(num6Pieces);
     emit piece7Changed(num7Pieces);
     emit blocksChanged(numBlocks);

     newPiece();
     timer.start(timeoutTime(), this);
 }

 void TetrisBoard::startDemo()
 {
     if (isPaused)
         return;

     isStarted = true;
     isInDemo = true;
     isTested = false;
     isGameOver = false;
     isWaitingAfterLine = false;
     numLinesRemoved = 0;
     numPiecesDropped = 0;
     num4Pieces = 0;
     num5Pieces = 0;
     num6Pieces = 0;
     num7Pieces = 0;
     numBlocks = 0;
     score = 0;
     advantage = 0;
     level = 12; //it has a 12th level intellect
     clearBoard();
     if (fp != NULL)
        fclose(fp);
     if (qApp->argc() == 3)
     {
         if (strcmp(qApp->argv()[1],"-f") == 0)
         {
                fp = fopen(qApp->argv()[2],"r");
         }
     }
     nextPiece.setFilePointer(fp);
     curPiece.setFilePointer(fp);
     nextPiece.setRandomShape();
     emit advChanged(advantage);
     emit linesRemovedChanged(numLinesRemoved);
     emit scoreChanged(score);
     emit levelChanged(level);
     emit pieceChanged(numPiecesDropped);
     emit piece4Changed(num4Pieces);
     emit piece5Changed(num5Pieces);
     emit piece6Changed(num6Pieces);
     emit piece7Changed(num7Pieces);
     emit blocksChanged(numBlocks);

     newPiece();
     timer.start(timeoutTime(), this);
 }

 void TetrisBoard::pause()
 {
     if (!isStarted)
         return;

     isPaused = !isPaused;
     if (isPaused) {
         timer.stop();
     } else {
         timer.start(timeoutTime(), this);
     }
     update();
 }

/** void TetrisBoard::configure()
 {
     if (!isPaused)
         pause();
     myDialog->board = this;
     myDialog->exec();
     if (isPaused)
        pause();
 }**/

/** void TetrisBoard::saveKeys()
 {
     Up = myDialog->getKey(0);
     Down = myDialog->getKey(1);
     Left = myDialog->getKey(2);
     Right = myDialog->getKey(3);
     dropLineV = myDialog->getKey(4);
     dropOneLineV = myDialog->getKey(5);
     pause();
 }**/

 void TetrisBoard::paintEvent(QPaintEvent *event)
 {
     QFrame::paintEvent(event);

     QPainter painter(this);
     QRect rect = contentsRect();

     // This brings up the "Pause" Screen
     // if (isPaused) {
          //painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
     //     return;
     // }

     //Display Game Over
      if (isGameOver) {
          if(isWin) {
              painter.drawText(rect, Qt::AlignCenter, tr("You Won! \\(^_^)/"));
              return;
          }
          else {
              painter.drawText(rect, Qt::AlignCenter, tr("You Lose! (>_<)"));
              return;
          }

      }

     int boardTop = rect.bottom() - BoardHeight*squareHeight();

     for (int i = 0; i < BoardHeight; ++i) {
         for (int j = 0; j < BoardWidth; ++j) {
             TetrisShape shape = shapeAt(j, BoardHeight - i - 1);
             if (shape != NoShape)
                 drawSquare(painter, rect.left() + j * squareWidth(),
                            boardTop + i * squareHeight(), shape);
         }
     }

     if (curPiece.shape() != NoShape) {
         for (int i = 0; i < curPiece.size(); ++i) {
             int x = curX + curPiece.x(i);
             int y = curY - curPiece.y(i);
             drawSquare(painter, rect.left() + x * squareWidth(),
                        boardTop + (BoardHeight - y - 1) * squareHeight(),
                        curPiece.shape());
         }
     }
 }

void TetrisBoard::moveLeft()
{
	if(!isGameOver)
	{
		tryMove(curPiece, curX - 1, curY);
	}
}

void TetrisBoard::moveRight()
{
	if(!isGameOver)
	{
		tryMove(curPiece, curX + 1, curY);
	}
}

void TetrisBoard::rotateRight()
{
	if(!isGameOver)
	{
		tryMove(curPiece.rotatedRight(), curX, curY);
	}
}

void TetrisBoard::rotateLeft()
{
	if(!isGameOver)
	{
		tryMove(curPiece.rotatedLeft(), curX, curY);
	}
}


/** void TetrisBoard::keyPressEvent(QKeyEvent *event)
 {
     if (!isStarted || isPaused || isInDemo || curPiece.shape() == NoShape) {
         QFrame::keyPressEvent(event);
         return;
     }

	 //cout << (int)(event->key()) << endl;

     int CurrentKey = (int) event->key();

     if (Left == CurrentKey){
     }
     else if (Right == CurrentKey)
     {
         tryMove(curPiece, curX + 1, curY);
     }
     else if (Down == CurrentKey){
         tryMove(curPiece.rotatedRight(), curX, curY);
     }
     else if (Up == CurrentKey)
     {
         tryMove(curPiece.rotatedLeft(), curX, curY);
     }
     else if (dropLineV == CurrentKey)
     {
         dropDown();
     }
     else if (dropOneLineV == CurrentKey)
     {
         oneLineDown();
     }
     else
     {
         QFrame::keyPressEvent(event);
     }
     switch (event->key()) {
     case Qt::Key_Left:
         tryMove(curPiece, curX - 1, curY);
         break;
     case Qt::Key_Right:
         tryMove(curPiece, curX + 1, curY);
         break;
     case Qt::Key_Down:
         tryMove(curPiece.rotatedRight(), curX, curY);
         break;
     case Qt::Key_Up:
         tryMove(curPiece.rotatedLeft(), curX, curY);
         break;
     case Qt::Key_Space:
         dropDown();
         break;
     case Qt::Key_D:
         oneLineDown();
         break;
     default:
         QFrame::keyPressEvent(event);
		 }
 }**/

 void TetrisBoard::timerEvent(QTimerEvent *event)
 {
     if (event->timerId() == timer.timerId()) {
         if (isWaitingAfterLine) {
             isWaitingAfterLine = false;
             newPiece();
             timer.start(timeoutTime(), this);
         } else {
             if(isInDemo && !isTested) {
                 Demo demoChoice(board, curPiece, nextPiece, BoardHeight, BoardWidth, numLinesRemoved);
		 isTested = true;
                 PieceMovement result = demoChoice.ratePosition(curPiece);
                 switch (result.rotation % 4) {
                     case 1:
                         curPiece = curPiece.rotatedLeft();
                         curPiece = curPiece.rotatedLeft();
                         break;
                     case 2:
                         curPiece = curPiece.rotatedRight();
                         break;
                     case 3:
                         break;
                     default:
                         curPiece = curPiece.rotatedLeft();
                 }
                 curY = BoardHeight - 1 + curPiece.minY();
                 if(tryMove(curPiece, result.x, curY)) {
                     //printf("moved to %d\ntest1\n", result.x);
                 } else {
                     //printf("bhaa: result.x=%d\ntest1\n", result.x);
                 }
                //dropDown();
             }
             else {
                oneLineDown();
             }
         }
     } else {
         QFrame::timerEvent(event);
     }
 }

 void TetrisBoard::clearBoard()
 {
     for (int i = 0; i < BoardHeight * BoardWidth; ++i)
         board[i] = NoShape;
 }

 void TetrisBoard::dropDown()
 {
	 if(!isGameOver)
	 {
     int dropHeight = 0;
     int newY = curY;
     while (true) {
         if (!tryMove(curPiece, curX, newY - 1))
             break;
         --newY;
         ++dropHeight;
     }
     pieceDropped(dropHeight);
	 }
 }

 void TetrisBoard::oneLineDown()
 {
	 if(!isGameOver)
	 {
     if (!tryMove(curPiece, curX, curY - 1))
         pieceDropped(0);
	 }
 }

 void TetrisBoard::pieceDropped(int dropHeight)
 {
     for (int i = 0; i < curPiece.size(); ++i) {
         int x = curX + curPiece.x(i);
         int y = curY - curPiece.y(i);
         shapeAt(x, y) = curPiece.shape();
     }

     ++numPiecesDropped;
     /*if (numPiecesDropped % 25 == 0) {
         ++level;
         timer.start(timeoutTime(), this);
         emit levelChanged(level);
     }*/

     score += dropHeight + 7;
     emit scoreChanged(score);
     emit pieceChanged(numPiecesDropped);
     switch(curPiece.size()) {
     case 4:
     	num4Pieces++;
        numBlocks += 4;
        emit piece4Changed(num4Pieces);
        break;
     case 5:
	num5Pieces++;
        numBlocks += 5;
        emit piece5Changed(num5Pieces);
        break;
     case 6:
        num6Pieces++;
        numBlocks += 6;
        emit piece6Changed(num6Pieces);
        break;
     case 7:
        num7Pieces++;
        numBlocks += 7;
        emit piece7Changed(num7Pieces);
        break;
     default:
        break;
     }
     emit blocksChanged(numBlocks);

     removeFullLines();
     isTested = false;
     if (!isWaitingAfterLine)
         newPiece();
 }

 void TetrisBoard::removeFullLines()
 {
     int numFullLines = 0;

     for (int i = BoardHeight - 1; i >= 0; --i) {
         bool lineIsFull = true;

         for (int j = 0; j < BoardWidth; ++j) {
             if (shapeAt(j, i) == NoShape) {
                 lineIsFull = false;
                 break;
             }
         }

         if (lineIsFull) {
             ++numFullLines;
             for (int k = i; k < BoardHeight - 1; ++k) {
                 for (int j = 0; j < BoardWidth; ++j)
                     shapeAt(j, k) = shapeAt(j, k + 1);
             }
             for (int j = 0; j < BoardWidth; ++j)
                 shapeAt(j, BoardHeight - 1) = NoShape;
         }
     }

     if (numFullLines > 0) {
         numLinesRemoved += numFullLines;
         score += 10 * numFullLines;
         emit linesRemovedChanged(numLinesRemoved);
         emit scoreChanged(score);
         advantage += numFullLines;
         emit advChanged(advantage);
         emit timeToAddLines(numFullLines, curPiece, curX);
         timer.start(500, this);
         isWaitingAfterLine = true;
         curPiece.setShape(NoShape);
         update();
     }
 }

 void TetrisBoard::addLines(int linestoAdd, TetrisPiece piece1, int px)
 {
     advantage -= linestoAdd;
     emit advChanged(advantage);
     if (advantage > 0) {
         linestoAdd = linestoAdd - advantage;
     }
     //move all rows up one
     for(int i = 0; i < linestoAdd; ++i) {
         for(int m = BoardHeight - 1; m > 0; m--) {
             for(int n = 0; n < BoardWidth; ++n) {
                 shapeAt(n,m) = shapeAt(n, m-1);
              }
         }
         //create the bottom row
         for(int j = 0; j < BoardWidth; ++j) {
             shapeAt(j,0) = Shaped;
         }
         //make squares with cur piece = NoShape
         for (int j = 0; j < piece1.size(); ++j) {
             int x = px + piece1.x(j);
             if(piece1.y(j) == i) {
                 shapeAt(x, i) = NoShape;
             }
         }
     }
 }

 void TetrisBoard::newPiece()
 {
     curPiece = nextPiece;
     nextPiece.setRandomShape();
     showNextPiece();
     curX = BoardWidth / 2 + 1;
     curY = BoardHeight - 1 + curPiece.minY();

     if (!tryMove(curPiece, curX, curY)) {
         curPiece.setShape(NoShape);
         timer.stop();
         isStarted = false;
         isGameOver = true;
         emit iLost(true);
         isWin = false;
         update();
     }
 }

 void TetrisBoard::showNextPiece()
 {
     if (!nextPieceLabel)
         return;

     int dx = nextPiece.maxX() - nextPiece.minX() + 1;
     int dy = nextPiece.maxY() - nextPiece.minY() + 1;

     QPixmap pixmap(dx * squareWidth(), dy * squareHeight());
     QPainter painter(&pixmap);
     painter.fillRect(pixmap.rect(), nextPieceLabel->palette().background());

     for (int i = 0; i < nextPiece.size(); ++i) {
         int x = nextPiece.x(i) - nextPiece.minX();
         int y = nextPiece.y(i) - nextPiece.minY();
         drawSquare(painter, x * squareWidth(), y * squareHeight(),
                    nextPiece.shape());
     }
     nextPieceLabel->setPixmap(pixmap);
 }

 bool TetrisBoard::tryMove(const TetrisPiece &newPiece, int newX, int newY)
 {
     for (int i = 0; i < newPiece.size(); ++i) {
         int x = newX + newPiece.x(i);
         int y = newY - newPiece.y(i);
        /* printf("i = %d\n",i);
         printf("x = %d, y = %d\n",newX,newY);
         printf("px = %d, py = %d\n",newPiece.x(i),newPiece.y(i));
         printf("BoardHeight = %d\n", BoardHeight);
         printf("minx = %d, miny = %d\n\n",newPiece.minX(),newPiece.minY());*/
         if (x < 0 || x >= BoardWidth || y < 0 || y >= (BoardHeight+4))
             return false;
         if (shapeAt(x, y) != NoShape)
             return false;
     }

     curPiece = newPiece;
     curX = newX;
     curY = newY;
     update();
     return true;
 }

 void TetrisBoard::drawSquare(QPainter &painter, int x, int y, TetrisShape shape)
 {
     static const QRgb colorTable[8] = {
         0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
         0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
     };

     QColor color = colorTable[int(shape)];
     painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
                      color);

     painter.setPen(color.light());
     painter.drawLine(x, y + squareHeight() - 1, x, y);
     painter.drawLine(x, y, x + squareWidth() - 1, y);

     painter.setPen(color.dark());
     painter.drawLine(x + 1, y + squareHeight() - 1,
                      x + squareWidth() - 1, y + squareHeight() - 1);
     painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                      x + squareWidth() - 1, y + 1);
 }
 
