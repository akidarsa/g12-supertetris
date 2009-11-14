/*tetrisnetwork.cpp*/
#include <QtGui>
#include <stdlib.h>
#include <string> //may need string.h
#include <iostream>
#include <sys/time.h>
#include "tetrisnetwork.h"
using namespace std;


/**
 * STUFF THAT NEEDS TO BE IMPLEMENTED
 *
 * 1). Checking what the network is sending
 *
 * 2). Disable all other button once one option is sent
 *
 *
 *
 * */

TetrisNetwork::TetrisNetwork()
{
    isConnected = false;
    socket = NULL;
    createServerGroupBox();
    createAnswerGroupBox();
    createModeGroupBox();
    startButton = new QPushButton("Start");
    connect(startButton, SIGNAL(clicked()), this, SLOT(sendStart()));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(serverGroupBox);
    mainLayout->addWidget(answerGroupBox);
    mainLayout->addWidget(modeGroupBox);
    mainLayout->addWidget(startButton);
    setLayout(mainLayout);
    setWindowTitle(tr("Tetris Network.Live"));
}

TetrisNetwork:: ~TetrisNetwork()
{
  delete serverGroupBox;
  delete answerGroupBox;
  delete closeButton;
}

void TetrisNetwork::createModeGroupBox()
{
    modeGroupBox = new QGroupBox(tr("Network Play Modes"));
    QGridLayout *layout = new QGridLayout;
    hvsnButton = new QPushButton("Human Mode");
    cvsnButton = new QPushButton("Computer Mode");
    qualifierButton = new QPushButton("Qualifier Mode");
    connect(hvsnButton, SIGNAL(clicked()), this, SLOT(sendGame1()));
    connect(cvsnButton, SIGNAL(clicked()), this, SLOT(sendGame2()));
    connect(qualifierButton, SIGNAL(clicked()), this, SLOT(sendGame3()));
    layout -> addWidget(hvsnButton, 1, 0);
    layout -> addWidget(cvsnButton, 2, 0);
    layout -> addWidget(qualifierButton, 3, 0);    
    modeGroupBox->setLayout(layout);
}
void TetrisNetwork::createServerGroupBox()
{
  serverGroupBox = new QGroupBox(tr("Network Information"));
  QGridLayout *layout = new QGridLayout;
  serverLabel = new QLabel("Server: ");
  serverName = new QLineEdit("127.0.0.1");
  layout -> addWidget(serverLabel, 0, 0);
  layout -> addWidget(serverName, 0, 1);
  portLabel = new QLabel("Port: ");
  portNumber = new QLineEdit("9462");
  connectButton = new QPushButton("Engage");
  connect(connectButton, SIGNAL(clicked()), this, SLOT(connectServer()));
  layout -> addWidget(portLabel, 1, 0);
  layout -> addWidget(portNumber, 1, 1);
  layout -> addWidget(connectButton, 2, 1);
  serverGroupBox->setLayout(layout);
}

void TetrisNetwork::createAnswerGroupBox()
{
  answerGroupBox = new QGroupBox(tr("Answers From Server"));
  QHBoxLayout *layout = new QHBoxLayout;
  tetrisAnswer = new QTextEdit;
  layout -> addWidget(tetrisAnswer);
  answerGroupBox -> setLayout(layout);
}

void TetrisNetwork::connectServer()
{
  QString hostport(serverName -> text());
  hostport.append(":");
  hostport.append(portNumber -> text());
  QString textContent(hostport);
  tetrisAnswer -> append(hostport);
  socket = new QTcpSocket();
  connect(socket, SIGNAL(hostFound()), this, SLOT(reportHostFound()));
  connect(socket, SIGNAL(connected()), this, SLOT(reportConnected()));
  connect(socket, SIGNAL(readyRead()), this, SLOT(getMessage()));
  connect(socket, SIGNAL(connectionClosed()), this, SLOT(connectionClosed()));
  socket -> connectToHost(serverName -> text(), (portNumber -> text()).toInt());
  socket -> write("ID=19251\n");
  hvsnButton->setEnabled(true);
  cvsnButton->setEnabled(true);
  qualifierButton->setEnabled(true);
}

void TetrisNetwork::reportConnected()
{
  tetrisAnswer -> append("connected");
  isConnected = true;
  emit netConnected("Connected");
}

void TetrisNetwork::reportHostFound()
{
  tetrisAnswer -> append("host found");
}

void TetrisNetwork::getMessage()
{
  int numBytes = socket->bytesAvailable();
  char data[numBytes + 1];
  socket->read( data, numBytes );
  data[numBytes] = '\0'; // terminate the char *
  QString newMessage(data);
  srvMsg = newMessage;
  tetrisAnswer -> append(newMessage);
}

void TetrisNetwork::closeSocket()
{
  if (isConnected == true)
    {

      socket -> write("19125:GAMEOVER\n");
      socket -> flush();
    }
  emit netConnected("Disconnected");
  accept(); // close the dialog window
}

void TetrisNetwork::connectionClosed()
{
  tetrisAnswer -> append("connection closed\n");
}

void TetrisNetwork::command(QString order)
{
  if(order == "LEFT")
  {
    socket -> write("LEFT\n");
  }
  else if(order == "Right")
  {
    socket -> write("RIGHT\n");
  }
  else if(order == "ROTATE")
  {
    socket -> write("ROTATE\n");
  }
  else if(order == "ROTATE")
  {
    socket -> write("ROTATE\n");
  }
  else if(order == "FALL")
  {
    socket -> write("FALL\n");
  }
  else if(order == "PIECE")
  {
    socket -> write("PIECE\n");
  }
  else if(order == "ATTACK")
  {
    socket -> write("ATTACK\n");
  }
  else if(order == "GAMEOVER")
  {
    socket -> write("GAMEOVER\n");
  }
  else if(order == "WIN")
  {
    socket -> write("WIN\n");
  }
  else if(order == "LOSE")
  {
    socket -> write("LOSE\n");
  }
  
}

void TetrisNetwork::sendGame1()
{
//	while(srvMsg.compare("GAMETYPE?") == 1)
//	{
		cout << "test 2 passed" << endl;
		socket -> write("GAMETYPE=tetris\n");
		tetrisAnswer -> append("Human Vs Network Selected\n");
		tetrisAnswer -> append("Sending GameType");
		getMessage();
//	}
    hvsnButton->setEnabled(false);
    cvsnButton->setEnabled(false);
    qualifierButton->setEnabled(false);
    startButton->setEnabled(true);
}

void TetrisNetwork::sendGame2()
{
    cout << "test 2 passed" << endl;
    socket -> write("GAMETYPE=tetris\n");
    tetrisAnswer -> append("Computer Vs Network Selected\n");
    tetrisAnswer -> append("Sending GameType");
    getMessage();
    hvsnButton->setEnabled(false);
    cvsnButton->setEnabled(false);
    qualifierButton->setEnabled(false);      
    startButton->setEnabled(true);  
}

void TetrisNetwork::sendGame3()
{
    cout << "test 2 passed" << endl;
    socket -> write("GAMETYPE=tetris-qualifier\n");
    tetrisAnswer -> append("Qualifier Mode Selected\n");
    tetrisAnswer -> append("Sending GameType");
    getMessage();
    hvsnButton->setEnabled(false);
    cvsnButton->setEnabled(false);
    qualifierButton->setEnabled(false);
    startButton->setEnabled(true);
}

void TetrisNetwork::sendStart()
{
    cout << "test 3 passed" << endl;
    socket -> write("READY\n");
    tetrisAnswer -> append("The game has started.\n Good Luck!");
    getMessage();
    this->accept();
}

void TetrisNetwork::disableButtons()
{
  hvsnButton->setEnabled(false);
  cvsnButton->setEnabled(false);
  qualifierButton->setEnabled(false);
  startButton->setEnabled(false);
}
