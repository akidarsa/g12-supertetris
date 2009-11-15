#ifndef TETRISDEMO_H_
#define TETRISDEMO_H_

#include "tetrispiece.h"
#include "PieceMovement.h"

class Demo {
public:
	Demo(TetrisShape*, TetrisPiece, TetrisPiece, int, int, long long);
        virtual ~ Demo();
	void restoreBoard();
//	void restoreBoard2();
	TetrisShape &shapeAt(int x, int y) {
		return testBoard[(y * BoardWidth) + x];
	}
/*	TetrisShape &shapeAt2(int x, int y){
		return testBoard2[(y*BoardWidth) + x];
	}
*/
	int dropDown();
//	int dropDown1();
//	int dropDown2();
	void markPiece();
	void pieceDropped();
//	void markPiece2();
//	void pieceDropped1();
//	void pieceDropped2();
	int removeFullLines();
//	int removeFullLines2();
	void dropfirstpiece(int);
	bool tryMove(const TetrisPiece &newPiece, int newX, int newY);
//	bool tryMove2(const TetrisPiece &newPiece, int newX, int newY);
	PieceMovement ratePosition(TetrisPiece);
	void evaluateBoard(double* score);
//	void evaluateBoard2(double* score);
	int getEliminateBlocks();
//	int getEliminateBlocks2();
	int getBlocksHeight();
//	int getBlocksHeight2();
	int getRowRoughness(int);
//	int getRowRoughness2(int);
	int getColumnRoughness(int);
//	int getColumnRoughness2(int);
	int getHoles();
//	int getHoles2();
	int getbalance();
//	int getbalance2();

	TetrisPiece curPiece;
	TetrisPiece nextPiece;
	TetrisPiece testPiece;
//	TetrisPiece qPiece;
//	PieceMovement q[5]; //the top 5 moves for the first piece
	int curX;
	int curY;
	int BoardWidth;
	int BoardHeight;
	TetrisShape* board;
	TetrisShape* testBoard;
//	TetrisShape* testBoard2;
	int numLinesRemoved;
};

#endif /* TETRISDEMO_H_ */
