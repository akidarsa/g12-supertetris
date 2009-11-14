#ifndef TETRISTNETWORK_H
#define TETRISNETWORK_H

#include<QtGui>
#include<stdlib.h>
#include<string>
#include<iostream>
#include<sys/time.h>
#include<QtNetwork>
#include<QTcpServer>

class TetrisNetwork : public QDialog
{
	Q_OBJECT

	public:
		TetrisNetwork();
		virtual ~ TetrisNetwork();
        signals:
                void netConnected(QString command);
	private:
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
		void enableButtons();	


};

#endif
