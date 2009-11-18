/* This is the class that will keep track of the
 * x position and the rotation of the current piece*/

#ifndef _PIECEMOVEMENT_H
#define	_PIECEMOVEMENT_H

class PieceMovement {
public:
    int x;
    int rotation;

    PieceMovement() {
        x = 0;
        rotation = 0;
    };
};

#endif	/* _PIECEMOVEMENT_H */

