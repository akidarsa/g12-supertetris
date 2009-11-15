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

 #include <QtCore>
 
 #include <stdlib.h>
 #include <string.h>
 #include <fstream>

 #include "tetrispiece.h"
 #include "tetriswindow.h"

 void TetrisPiece::setRandomShape()
 {
     //setShape(TetrisShape(qrand() % 7 + 1));
     setShape(TetrisShape(qrand() % 4 + 1));
 }

 void TetrisPiece::setShape(TetrisShape shape)
 {
     /*static const int coordsTable[8][4][2] = {
         { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
         { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
         { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
         { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
         { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
         { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
         { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
         { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }
     };

     for (int i = 0; i < 4 ; i++) {
         for (int j = 0; j < 2; ++j)
             coords[i][j] = coordsTable[shape][i][j];
     }*/

     for (int i = 0; i < 7; i++)
     {
        coords[i][0] = 0;
        coords[i][1] = 0;
     }
     
     pieceShape = shape;
     if ((shape != NoShape) & (shape != Mark))
     {
         if (fp == NULL)
         {
            randomPieceRep();
         }
         else
         {
             char str[49];
             char c;
             int i = 0;
             c = (char) fgetc(fp);
             while ((c != '\n') & (c != EOF))
             {
                 str[i] = c;
                 c = (char) fgetc(fp);
                 i++;
             }
             str[i] = '\0';
             if (i == 16)
             {
                 pieceShape = Piece4;
             }
             else if (i == 25)
             {
                 pieceShape = Piece5;
             }
             else if (i == 36)
             {
                 pieceShape = Piece6;
             }
             else if (i == 49)
             {
                 pieceShape = Piece7;
             }
             if (c == EOF)
			 {
                 pieceShape = NoShape;
			 }
             setCoords(str);
         }
     }
     else
     {
         setFilePointer(NULL);
     }
 }

 /*char* TetrisPiece::setFileName()
 {
     if (qApp->argc() == 3)
     {
         if (strcmp(qApp->argv()[1],"-f") == 0)
         {
             char* TetrisPiece::FileName = qApp->argv()[2];
             if (TetrisPiece::fp == NULL)
             {
                FILE* TetrisPiece::fp = fopen(TetrisPiece::FileName,"r");
             }
             char temp = fgetc(fp);
             char* Line = temp;
             while ((temp != '\n') || (temp != EOF))
             {
                 strcat(Line,temp);
             }
             printf("%s",Line);
         }
     }
     
 }*/
  TetrisPiece:: ~TetrisPiece()
  {
      fclose(fp); 
  }

 void TetrisPiece::setFilePointer(FILE* fpr)
 {
     fp = fpr;
 }

 void TetrisPiece::randomPieceRep()
 {
     static const char* table4[7] =  {"1111000000000000",
                         "0100110010000000",
                         "1110100000000000",
                         "1100100010000000",
                         "0110110000000000",
                         "1100110000000000",
                         "1110010000000000"};

     static const char* table5[18] = {"0100011100010000000000000",
                        "0110001000110000000000000",
                        "0110011000010000000000000",
                        "0010011100100000000000000",
                        "1110010100000000000000000",
                        "1111100000000000000000000",
                        "1111010000000000000000000",
                        "1000011110000000000000000",
                        "1111001000000000000000000",
                        "0100011110000000000000000",
                        "0010011100010000000000000",
                        "1100011000100000000000000",
                        "0010001100110000000000000",
                        "0100011000100001000000000",
                        "1000011100100000000000000",
                        "1110011000000000000000000",
                        "0111011000000000000000000",
                        "1110010000100000000000000"};

     static const char* table6[60] = {"001110111000000000000000000000000000",
			"011100111000000000000000000000000000",
			"010000010000110000100000100000000000",
			"001000001000011000110000000000000000",
			"001100011000110000000000000000000000",
			"001000011000110000100000000000000000",
			"000100001100111000000000000000000000",
			"010000110000110000100000000000000000",
			"111000110000100000000000000000000000",
			"001000001000111000010000000000000000",
			"001100111000010000000000000000000000",
			"111000101100000000000000000000000000",
			"111100101000000000000000000000000000",
			"111000101000100000000000000000000000",
			"011100110100000000000000000000000000",
			"111000111000000000000000000000000000",
			"111100010100000000000000000000000000",
			"001000111000100000100000000000000000",
			"000100011100110000000000000000000000",
			"001000111000110000000000000000000000",
			"101000111000100000000000000000000000",
			"000100111100010000000000000000000000",
			"001000011000110000010000000000000000",
			"001000111100001000000000000000000000",
			"010000111000110000000000000000000000",
			"001100001000111000000000000000000000",
			"011000010000110000100000000000000000",
			"011000110000110000000000000000000000",
			"111000010000110000000000000000000000",
			"010000011000010000110000000000000000",
			"001100111000001000000000000000000000",
			"111000110000010000000000000000000000",
			"010000011000110000010000000000000000",
			"011000110000011000000000000000000000",
			"011000110000010000010000000000000000",
			"011100110000010000000000000000000000",
			"111000101000001000000000000000000000",
			"111110100000000000000000000000000000",
			"100000111110000000000000000000000000",
			"111110010000000000000000000000000000",
			"010000111110000000000000000000000000",
			"111110001000000000000000000000000000",
			"111111000000000000000000000000000000",
			"100000111100100000000000000000000000",
			"111100110000000000000000000000000000",
			"011110110000000000000000000000000000",
			"111100100000100000000000000000000000",
			"010000111100100000000000000000000000",
			"111100100100000000000000000000000000",
			"000100111100100000000000000000000000",
			"110000111100000000000000000000000000",
			"110000011110000000000000000000000000",
			"100000100000111100000000000000000000",
			"100000111100000100000000000000000000",
			"111100011000000000000000000000000000",
			"111100010000010000000000000000000000",
			"001000111100010000000000000000000000",
			"010000010000111100000000000000000000",
			"001000111000011000000000000000000000",
			"001000111000010000010000000000000000"};

     static const char* table7[195] = {"1000000100000011110000001000000000000000000000000",
			"1100000011110000001000000000000000000000000000000",
			"0010000111000010000001000000100000000000000000000",
			"0001000011100001000001100000000000000000000000000",
			"0010000111000010000001100000000000000000000000000",
			"0001000011100011000000100000000000000000000000000",
			"1010000111000010000001000000000000000000000000000",
			"0001000111100001000000100000000000000000000000000",
			"1111000010100000010000000000000000000000000000000",
			"0001000111100001010000000000000000000000000000000",
			"0010000111100001010000000000000000000000000000000",
			"0100000111100001010000000000000000000000000000000",
			"1000000111100001010000000000000000000000000000000",
			"1111100001010000000000000000000000000000000000000",
			"0100000111000011100000000000000000000000000000000",
			"0111000110100000010000000000000000000000000000000",
			"0001000011100011010000000000000000000000000000000",
			"0100000011100011010000000000000000000000000000000",
			"1111000110100000000000000000000000000000000000000",
			"1110000101000010100000000000000000000000000000000",
			"0010000111000010100001000000000000000000000000000",
			"1110000101000010000001000000000000000000000000000",
			"0111000010100011000000000000000000000000000000000",
			"0111000110100001000000000000000000000000000000000",
			"1000000111000010100001000000000000000000000000000",
			"1111000010100001000000000000000000000000000000000",
			"0001000111100010100000000000000000000000000000000",
			"1111000101000000100000000000000000000000000000000",
			"0010000111100010100000000000000000000000000000000",
			"0100000111100010100000000000000000000000000000000",
			"1111000101000010000000000000000000000000000000000",
			"0111100110100000000000000000000000000000000000000",
			"1000000111100010100000000000000000000000000000000",
			"1111100010100000000000000000000000000000000000000",
			"0010000111000010110000000000000000000000000000000",
			"1111000101100000000000000000000000000000000000000",
			"0100000111000010110000000000000000000000000000000",
			"1110000101100010000000000000000000000000000000000",
			"0111000110110000000000000000000000000000000000000",
			"1000000111000010110000000000000000000000000000000",
			"1111000010110000000000000000000000000000000000000",
			"0011000111100001000000000000000000000000000000000",
			"0011000111000001100000000000000000000000000000000",
			"1011000111000001000000000000000000000000000000000",
			"0001100111100000100000000000000000000000000000000",
			"0010000001000011110000100000000000000000000000000",
			"0010000001100011100000100000000000000000000000000",
			"0010000001000000100001110000010000000000000000000",
			"0110000001000011100000100000000000000000000000000",
			"0011000001000011100000100000000000000000000000000",
			"0010000001100001100001100000000000000000000000000",
			"0010000001000000100000110000110000000000000000000",
			"0110000001000001100001100000000000000000000000000",
			"0011000001000001100001100000000000000000000000000",
			"0010000001000001100001110000000000000000000000000",
			"0010000011000001100001100000000000000000000000000",
			"0010000001000011100001100000000000000000000000000",
			"0010000001000001100001100000100000000000000000000",
			"0001000000100000110001110000000000000000000000000",
			"0100000010000011000001000000100000010000000000000",
			"0010000001000001100000100000110000000000000000000",
			"0100000010000011000001000000110000000000000000000",
			"0001110111100000000000000000000000000000000000000",
			"0011100111000010000000000000000000000000000000000",
			"1011100111000000000000000000000000000000000000000",
			"0011100111000001000000000000000000000000000000000",
			"0111100111000000000000000000000000000000000000000",
			"0010000001110011100000000000000000000000000000000",
			"0111000111000010000000000000000000000000000000000",
			"1111000111000000000000000000000000000000000000000",
			"0100000011100011100000000000000000000000000000000",
			"0111000111000001000000000000000000000000000000000",
			"0010000001000011100000100000010000000000000000000",
			"0100000110000011000001000000100000000000000000000",
			"0010000001000001100001100000010000000000000000000",
			"0010000001000001110001100000000000000000000000000",
			"0001100001100011100000000000000000000000000000000",
			"0011000011000011000001000000000000000000000000000",
			"0011000111000011000000000000000000000000000000000",
			"0111000011000011000000000000000000000000000000000",
			"0001000001100011100000100000000000000000000000000",
			"0010000111000011000001000000000000000000000000000",
			"0010000011000011000001100000000000000000000000000",
			"0000100000110011110000000000000000000000000000000",
			"0001000001100011100001000000000000000000000000000",
			"0001000101100011100000000000000000000000000000000",
			"0011000001100011100000000000000000000000000000000",
			"0001000001100011110000000000000000000000000000000",
			"0001000001100011100000010000000000000000000000000",
			"0010000111000001100000100000000000000000000000000",
			"1100000110000011000001000000000000000000000000000",
			"0010000011000011100000100000000000000000000000000",
			"1111000011000001000000000000000000000000000000000",
			"1000000111000011000001000000000000000000000000000",
			"1110000110000011000000000000000000000000000000000",
			"1110000111000010000000000000000000000000000000000",
			"0001000000100011110000010000000000000000000000000",
			"0010000101000011100000100000000000000000000000000",
			"0010000001000011100000110000000000000000000000000",
			"0011000111000010000001000000000000000000000000000",
			"0010000001000011100001000000100000000000000000000",
			"0010000111100010000001000000000000000000000000000",
			"0001000111100011000000000000000000000000000000000",
			"0101000011100011000000000000000000000000000000000",
			"0001100011100011000000000000000000000000000000000",
			"0001000011110011000000000000000000000000000000000",
			"0001000111100001100000000000000000000000000000000",
			"1010000111000011000000000000000000000000000000000",
			"0110000111000011000000000000000000000000000000000",
			"0010000111000011000000100000000000000000000000000",
			"1000000101000011100001000000000000000000000000000",
			"1010000111000010100000000000000000000000000000000",
			"0000100111110000100000000000000000000000000000000",
			"1001000111100001000000000000000000000000000000000",
			"0001000111110001000000000000000000000000000000000",
			"0110000011000011000000100000000000000000000000000",
			"0010000011000011000000100000010000000000000000000",
			"0001000111110000010000000000000000000000000000000",
			"0010000111100001100000000000000000000000000000000",
			"0110000111100000100000000000000000000000000000000",
			"0011000111100000100000000000000000000000000000000",
			"0010000001000011110000010000000000000000000000000",
			"0010000111100000110000000000000000000000000000000",
			"0010000111110000100000000000000000000000000000000",
			"0001100000100011110000000000000000000000000000000",
			"0111000001000011100000000000000000000000000000000",
			"0010000001100000100001110000000000000000000000000",
			"0011000001000011110000000000000000000000000000000",
			"0011000001000011100000010000000000000000000000000",
			"0011100001000011100000000000000000000000000000000",
			"0001000001100000100001110000000000000000000000000",
			"0110000010000011000001100000000000000000000000000",
			"0100000011000001000001100000100000000000000000000",
			"0110000010000011100001000000000000000000000000000",
			"0010000011000001000001100000100000000000000000000",
			"0110000110000011100000000000000000000000000000000",
			"0110000110000011000000100000000000000000000000000",
			"1100000011000001000001100000000000000000000000000",
			"0100000010000001100000100000110000000000000000000",
			"0100000011000001000001100000010000000000000000000",
			"0001100111100000010000000000000000000000000000000",
			"0010000001100011100000010000000000000000000000000",
			"0011000111000000110000000000000000000000000000000",
			"0011000111000000100000010000000000000000000000000",
			"1110000110000001000000100000000000000000000000000",
			"1111000110000001000000000000000000000000000000000",
			"0100000010000001100001100000010000000000000000000",
			"0111000110000001100000000000000000000000000000000",
			"0111000110000001000000100000000000000000000000000",
			"0111100110000001000000000000000000000000000000000",
			"1110000101000000100000010000000000000000000000000",
			"1000000111110010000000000000000000000000000000000",
			"1111100100000010000000000000000000000000000000000",
			"1111100110000000000000000000000000000000000000000",
			"0100000111110010000000000000000000000000000000000",
			"1111100101000000000000000000000000000000000000000",
			"1111100100100000000000000000000000000000000000000",
			"0001000111110010000000000000000000000000000000000",
			"1111110100000000000000000000000000000000000000000",
			"1111100100010000000000000000000000000000000000000",
			"0000100111110010000000000000000000000000000000000",
			"1000000100000011111000000000000000000000000000000",
			"1000000111110001000000000000000000000000000000000",
			"1100000111110000000000000000000000000000000000000",
			"1000000111110000010000000000000000000000000000000",
			"1001000111110000000000000000000000000000000000000",
			"1000000111111000000000000000000000000000000000000",
			"1000000111110000001000000000000000000000000000000",
			"1111100011000000000000000000000000000000000000000",
			"1111100010000001000000000000000000000000000000000",
			"0010000111110001000000000000000000000000000000000",
			"1111110010000000000000000000000000000000000000000",
			"0110000111110000000000000000000000000000000000000",
			"0100000010000011111000000000000000000000000000000",
			"0100000111111000000000000000000000000000000000000",
			"1111100001000000100000000000000000000000000000000",
			"1111110001000000000000000000000000000000000000000",
			"0010000111111000000000000000000000000000000000000",
			"1111111000000000000000000000000000000000000000000",
			"1100000111100010000000000000000000000000000000000",
			"1100000011110001000000000000000000000000000000000",
			"1000000100000011110001000000000000000000000000000",
			"1000000111100010000001000000000000000000000000000",
			"1000000111100010010000000000000000000000000000000",
			"1001000111100010000000000000000000000000000000000",
			"0111110110000000000000000000000000000000000000000",
			"0111100110010000000000000000000000000000000000000",
			"0000100011110011000000000000000000000000000000000",
			"1111000100000010000001000000000000000000000000000",
			"1111000100100010000000000000000000000000000000000",
			"0001000111100010000001000000000000000000000000000",
			"0100000010000011110001000000000000000000000000000",
			"1111000100110000000000000000000000000000000000000",
			"1111000100100000010000000000000000000000000000000",
			"1100000011111000000000000000000000000000000000000"};


     if (size() == 4)
     {
         setCoords(table4[(qrand() % 7)]);
     }
     else if (size() == 5)
     {
         setCoords(table5[(qrand() % 18)]);
     }
     else if (size() == 6)
     {
         setCoords(table6[(qrand() % 60)]);
     }
     else if (size() == 7)
     {
         setCoords(table7[(qrand() % 195)]);
     }
     shiftToTopLeft(size());
 }

 void TetrisPiece::setCoords(const char* piecerep)
 {
     int counter = 0;
     //printf("Coords:");
     for (int y = 0; y < size();y++)
     {
         for (int x = 0; x < size();x++)
         {
             if (piecerep[y+(x*size())] == '1')
             {
                coords[counter][0] = x - size()/2;
                coords[counter][1] = size()/2 - y;
                counter++;
                //printf("%d,%d -",coords[counter-1][0],coords[counter-1][1]);
             }
         }
     }
 }

 int TetrisPiece::size() const
 {
     if (pieceShape == Piece4)
         return(4);
     else if (pieceShape == Piece5)
         return(5);
     else if (pieceShape == Piece6)
         return(6);
     else if (pieceShape == Piece7)
         return(7);
     else
         return(4);
 }

 int TetrisPiece::minX() const
 {
     int min = coords[0][0];
     for (int i = 1; i < size(); ++i)
         min = qMin(min, coords[i][0]);
     return min;
 }

 int TetrisPiece::maxX() const
 {
     int max = coords[0][0];
     for (int i = 1; i < size(); ++i)
         max = qMax(max, coords[i][0]);
     return max;
 }

 int TetrisPiece::minY() const
 {
     int min = coords[0][1];
     for (int i = 1; i < size(); ++i)
         min = qMin(min, coords[i][1]);
     return min;
 }

 int TetrisPiece::maxY() const
 {
     int max = coords[0][1];
     for (int i = 1; i < size(); ++i)
         max = qMax(max, coords[i][1]);
     return max;
 }

 TetrisPiece TetrisPiece::rotatedLeft()
 {
     //if (pieceShape == OShape)
         //return *this;

     TetrisPiece result;
     result.setFilePointer(getFilePointer());
     result.pieceShape = pieceShape;
     for (int i = 0; i < size(); ++i) {
         result.setX(i, y(i));
         result.setY(i, -x(i));
     }
     result.shiftToTopLeft(size());
     return result;
 }

 TetrisPiece TetrisPiece::rotatedRight()
 {
     //if (pieceShape == OShape)
        // return *this;
     TetrisPiece result;
 //    result.setFilePointer(getFilePointer());
     result.pieceShape = pieceShape;
     for (int i = 0; i < size(); ++i) {
         result.setX(i, -y(i));
         result.setY(i, x(i));
     }
     result.shiftToTopLeft(size());
     return result;
 }

 void TetrisPiece::shiftToTopLeft(int s)
{ 
	int shftSize = s/2;
	int shftx = abs(minX())%shftSize;
	int shfty = abs(minY())%shftSize;
	if(minX() >= 0){ shftx+=shftSize; }
	if(minY() >= 0){ shfty+=shftSize; }
	for (int i = 0; i< size(); i++){
		setX(i, x(i)-shftx);
		setY(i, y(i)-shfty);
	}
}
