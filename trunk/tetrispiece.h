/*
 * File:   Tetrispiece.h
 * Author: ee462a1
 *
 * Created on October 5, 2009, 9:15 AM
 */

/****************************************************************************
 **
 ** Copyright (C) 2004-2008 Trolltech ASA. All rights reserved.
 **
 ** This file is part of the documentation of the Qt Toolkit.
 **
 ** This file may be used under the terms of the GNU General Public
 ** License versions 2.0 or 3.0 as published by the Free Software
 ** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
 ** included in the packaging of this file.  Alternatively you may (at
 ** your option) use any later version of the GNU General Public
 ** License if such license has been publicly approved by Trolltech ASA
 ** (or its successors, if any) and the KDE Free Qt Foundation. In
 ** addition, as a special exception, Trolltech gives you certain
 ** additional rights. These rights are described in the Trolltech GPL
 ** Exception version 1.2, which can be found at
 ** http://www.trolltech.com/products/qt/gplexception/ and in the file
 ** GPL_EXCEPTION.txt in this package.
 **
 ** Please review the following information to ensure GNU General
 ** Public Licensing requirements will be met:
 ** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
 ** you are unsure which license is appropriate for your use, please
 ** review the following information:
 ** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
 ** or contact the sales department at sales@trolltech.com.
 **
 ** In addition, as a special exception, Trolltech, as the sole
 ** copyright holder for Qt Designer, grants users of the Qt/Eclipse
 ** Integration plug-in the right for the Qt/Eclipse Integration to
 ** link to functionality provided by Qt Designer and its related
 ** libraries.
 **
 ** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
 ** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
 ** granted herein.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **
 ****************************************************************************/

#ifndef TetrisPIECE_H
#define TetrisPIECE_H
#include <stdio.h>

enum TetrisShape {
    NoShape, Mark, Shaped
};

class TetrisPiece {
public:

    TetrisPiece() {
        setShape(NoShape);
    }

    void setRandomShape();
    void setShape(TetrisShape shape);
    void setShape(int*, int);
    void setShape(char*, int);

    TetrisShape shape() const {
        return pieceShape;
    }

    int x(int index) const {
        switch (blocks) {
            case 4:
                return coords[index][0];
                break;
            case 5:
                return coords5[index][0];
                break;
            case 6:
                return coords6[index][0];
                break;
            case 7:
                return coords7[index][0];
                break;
        }
        return 0;
    }

    int y(int index) const {
        switch (blocks) {
            case 4:
                return coords[index][1];
                break;
            case 5:
                return coords5[index][1];
                break;
            case 6:
                return coords6[index][1];
                break;
            case 7:
                return coords7[index][1];
                break;
        }
        return 0;
    }
    int minX() const;
    int maxX() const;
    int minY() const;
    int maxY() const;
    int blocks;
    TetrisPiece rotatedLeft() const;
    TetrisPiece rotatedRight() const;

    void setX(int index, int x) {
        switch (blocks) {
            case 4:
                coords[index][0] = x;
                break;
            case 5:
                coords5[index][0] = x;
                break;
            case 6:
                coords6[index][0] = x;
                break;
            case 7:
                coords7[index][0] = x;
                break;
        }
    }

    void setY(int index, int y) {
        switch (blocks) {
            case 4:
                coords[index][1] = y;
                break;
            case 5:
                coords5[index][1] = y;
                break;
            case 6:
                coords6[index][1] = y;
                break;
            case 7:
                coords7[index][1] = y;
                break;
        }
    }

    void setFilePointer(FILE* fpr){fp = fpr;}     
    FILE* getFilePointer() {return fp;}

    int size() const
    {
	return blocks;
    }

    TetrisShape pieceShape;
    int coords[4][2];
    int coords5[5][2];
    int coords6[6][2];
    int coords7[7][2];
    FILE *fp;
};

#endif

