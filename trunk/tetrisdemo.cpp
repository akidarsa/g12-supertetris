#include "tetrisdemo.h"
#include <stdio.h>
#include <math.h>
#include <QtCore>
Demo::Demo(TetrisShape* hostBoard, TetrisPiece piece, TetrisPiece next,
		int height, int width, long long numLinesRemoved1) {
	//duplicate game board
	BoardHeight = height;
	BoardWidth = width; //here's a comment
	board = new TetrisShape[height * width];
	testBoard = new TetrisShape[height * width];
	numLinesRemoved = numLinesRemoved1;

	for (int i = 0; i < BoardHeight * BoardWidth; ++i) {
		board[i] = hostBoard[i];
	}
	//duplicate shape
	curPiece.setShape(piece.shape());
        curPiece.setFilePointer(piece.getFilePointer());
        nextPiece.setShape(next.shape());
        nextPiece.setFilePointer(piece.getFilePointer());
	testPiece.setShape(piece.shape());
        testPiece.setFilePointer(piece.getFilePointer());
}
void Demo::restoreBoard() {
	for (int i = 0; i < BoardHeight * BoardWidth; ++i) {
		testBoard[i] = board[i];
	}
}
int Demo::dropDown() {
	int dropHeight = 0;
	int newY = curY;
	while (true) {
		if (!tryMove(testPiece, curX, newY - 1)){
			break;}
		--newY;
		++dropHeight;

	}
	return (dropHeight);
}
void Demo::markPiece() {
	for (int i = 0; i < testPiece.size(); ++i) {
		int x = curX + testPiece.x(i);
		int y = curY - testPiece.y(i);
		shapeAt(x, y) = Mark;
	}
	return;
}
void Demo::pieceDropped() {
	for (int i = 0; i < testPiece.size(); ++i) {
		int x = curX + testPiece.x(i);
		int y = curY - testPiece.y(i);
		shapeAt(x, y) = testPiece.shape();
	}
	return;
}
int Demo::removeFullLines() {
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
			for (int j = 0; j < BoardWidth; ++j) {
				shapeAt(j, BoardHeight - 1) = NoShape;
			}
		}
	}
	return numFullLines;
}
bool Demo::tryMove(const TetrisPiece &newPiece, int newX, int newY) {
	for (int i = 0; i < newPiece.size(); ++i) {
		int x = newX + newPiece.x(i);
		int y = newY - newPiece.y(i);

		if (x < 0 || x >= BoardWidth || y < 0 || y >= (BoardHeight+4)) {
			return false;
		}
		if (shapeAt(x, y) != NoShape) {
			return false;
		}
	}
	curX = newX;
	curY = newY;
	return true;
}
PieceMovement Demo::ratePosition(TetrisPiece curPiece) {
        testPiece = curPiece;
	PieceMovement p;//p includes two numbers:x=movement, rotation=number of rotations
	double maxScore = -100000;
	for (int i = 0; i < 4; i++) { //rotation loop
		testPiece = testPiece.rotatedRight();
		//move from leftmost to right most
		for (int j = 0 - testPiece.minX(); j < BoardWidth - testPiece.maxX(); j++) {
			curY = BoardHeight - 1 + testPiece.minY();
			double score = 0;
			restoreBoard();
			curX = j;
			if (tryMove(testPiece, curX, curY)) {
				evaluateBoard(&score);
				if (score > maxScore) {
					maxScore = score;
					p.rotation = i;
					p.x = j;
				}
			}//if
		}//for
	}//for
	return p;
}
int Demo::getEliminateBlocks() {
	markPiece();
	bool fullLine = true;
	bool blockExist = false;
	int eliminateBlocks = 0;
	for (int y = 0; y < BoardHeight; y++) {
		fullLine = true;
		blockExist = false;
		for (int x = 0; x < BoardWidth; x++) {
			if (shapeAt(x, y) == NoShape) {
				fullLine = false;
				break;
			}
			if (shapeAt(x, y) == Mark) {
				blockExist = true;
			}
		}
		if (fullLine && blockExist) {
			eliminateBlocks++;
			if (eliminateBlocks == 4)
				break;
		}
	}
	pieceDropped();
	return eliminateBlocks;
}
int Demo::getBlocksHeight() {
	int height = 0;
	for (int y = 0; y < BoardHeight; y++) {
		for (int x = 0; x < BoardWidth; x++) {
			if (shapeAt(x, y) != NoShape) {
				height++;
				break;
			}
		}
	}
	return height;
}
int Demo::getRowRoughness(int row) {
	TetrisShape curPiece;
	TetrisShape neighbor;
	int roughness = 0;
	for (int x = 0; x < BoardWidth - 1; x++) {
		curPiece = shapeAt(x, row);
		neighbor = shapeAt(x + 1, row);
		if ((curPiece != NoShape && neighbor == NoShape) || (curPiece
				== NoShape && neighbor != NoShape))
			roughness++;
	}
	return roughness;
}
int Demo::getColumnRoughness(int col) {
	TetrisShape curPiece;
	TetrisShape neighbor;
	int roughness = 0;
	for (int y = 0; y < BoardHeight - 2; y++) {
		curPiece = shapeAt(col, y);
		neighbor = shapeAt(col, y + 1);
		if ((curPiece != NoShape && neighbor == NoShape) || (curPiece
				== NoShape && neighbor != NoShape))
			roughness++;
	}
	return roughness;
}
int Demo::getHoles() {
	int holes = 0;
	bool startHole = false;

	for (int x = 0; x < BoardWidth; x++) {
		startHole = false;
		for (int y = BoardHeight - 1; y >= 0; y--) {
			if (shapeAt(x, y) != NoShape) {
				startHole = true;
				continue;
			} else {
				if (startHole)
					holes++;
			}
		}
	}
	return holes;
}
void Demo::evaluateBoard(double* score) {
	*score = 0;
	int dropLine = dropDown();
	int hiRow = BoardHeight - dropLine - 1;
	int lowRow = hiRow - testPiece.maxY() + testPiece.minY();
	//step 1 : calculate the average height of the current piece
	double pieceAverageHeight = (double) (hiRow + lowRow) / 2;
	//step2: calculate the rows that this piece can remove, and how much of itself is removed with lines
	int blocksEliminated = getEliminateBlocks();
	int rowsEliminated = removeFullLines();
	int removeLineScore = rowsEliminated * blocksEliminated * BoardWidth;
	//step3: calculate the roughness of whole board
	//we define NoShape<->any shape change increases the level of roughness
	int blocksHeight = getBlocksHeight();
	int roughness = 0;
	for (int y = 0; y < blocksHeight; y++) {
		roughness += getRowRoughness(y);
	}
	for (int x = 0; x < BoardWidth; x++) {
		roughness += getColumnRoughness(x);
	}
	//step4: get how many holes there are in the board
	int holes = getHoles();

	*score -= pieceAverageHeight;
	*score += removeLineScore;
	*score -= roughness;
	*score -= holes;
	/*for (int n = BoardHeight - 1; n>= 0; n --){
		printf("\n");
		for(int x = (BoardWidth * n); x <= (BoardWidth * n + BoardWidth-1); ++x) {
			switch(testBoard[x]) {
			case NoShape:
				printf(" ");
				break;
			default:
				printf("0");
				break;
			}
	    }
	}
	printf("\n--------------------\n");
	if(pieceAverageHeight > 0) {
		printf("\n***Move Score***\n");
		printf("X = %d, Y = %d\n", curX, curY);
		printf("pieceAverageHeight = %lf\n", pieceAverageHeight);
		printf("removeLineScore = %d\n", removeLineScore);
		printf("roughness = %d\n", roughness);
		printf("holes = %d\n", holes);
		printf("total score = %lf\n ****** \n", *score);
	}*/
}

