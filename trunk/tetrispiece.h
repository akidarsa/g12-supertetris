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
  #ifndef TETRISPIECE_H
 #define TETRISPIECE_H
#include <stdio.h>

 enum TetrisShape { NoShape, Piece4, Piece5, Piece6, Piece7, Mark };

 class TetrisPiece
 {
 public:
     TetrisPiece() { setShape(NoShape);}

     void setRandomShape();
     void setShape(TetrisShape shape);
     void setCoords(char* piecerep);
     void randomPieceRep();
     void setFilePointer(FILE* fpr);

     TetrisShape shape() const { return pieceShape; }
     int x(int index) const { return coords[index][0]; }
     int y(int index) const { return coords[index][1]; }
     int size() const;
     int minX() const;
     int maxX() const;
     int minY() const;
     int maxY() const;
     TetrisPiece rotatedLeft();
     TetrisPiece rotatedRight();
     FILE* getFilePointer() {return fp;}

 private:
     void setX(int index, int x) { coords[index][0] = x; }
     void setY(int index, int y) { coords[index][1] = y; }

     TetrisShape pieceShape;
     int coords[7][2];
     FILE* fp;
 };
 #endif
