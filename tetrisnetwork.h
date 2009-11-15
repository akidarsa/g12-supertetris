#ifndef TETRISTNETWORK_H
#define TETRISNETWORK_H

#include<QtGui>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<sys/time.h>
#include<QtNetwork>
#include<QTcpServer>
using namespace std;

class TetrisNetwork : public QDialog
{
	Q_OBJECT

	public:
		TetrisNetwork();
		virtual ~ TetrisNetwork();
        signals:
                void netConnected(QString command);
		void serverLeft1();
		void serverRight1();
		void serverFall1();
		void serverRotate1();
		void serverWin1();
		void serverLose1();
		void serverGameover1();
		void serverAttack1(string line);
		void serverPiece1(string piece);

		void serverLeft2();
		void serverRight2();
		void serverFall2();
		void serverRotate2();
		void serverWin2();
		void serverLose2();
		void serverGameover2();
		void serverAttack2(string line);
		void serverPiece2(string piece);
                void netGameMode(QString mode);
	private:
		void commandEmitter();
		QLineEdit * serverName;
		QLineEdit * portNumber;
		bool isConnected;
		QTcpSocket * socket;
		QPushButton * closeButton;
                void createModeGroupBox();
		void createServerGroupBox();
		void createAnswerGroupBox();  
		QGroupBox *serverGroupBox;
		QGroupBox *answerGroupBox;
                QGroupBox *modeGroupBox;
		QTextEdit * tetrisAnswer;
		QString srvMsg;
		QLabel * serverLabel;
		QLabel * portLabel;
		QPushButton * connectButton;
		QPushButton * startButton;
		QPushButton * hvsnButton;
		QPushButton * cvsnButton;
		QPushButton * qualifierButton;
                bool humanMode;
                bool computerMode;
                bool qualifierMode;
		
	private slots:
		void connectionClosed();
		void reportConnected();
		void reportHostFound();
		void closeSocket();
		void command(QString order);
		void getMessage();
		void connectServer();
		void sendStart();
		void sendGame1();
		void sendGame2();
		void sendGame3();
		void disableButtons();	


};

#endif
