/*tetrisnetwork.cpp*/
#include <QtGui>
#include <stdlib.h>
#include <string> //may need string.h
#include <iostream>
#include <sys/time.h>
#include "tetrisnetwork.h"
using namespace std;

TetrisNetwork::TetrisNetwork()
{
    isConnected = false;
    socket = NULL;
    createServerGroupBox();
    createAnswerGroupBox();
    closeButton = new QPushButton("Close");
    connect(closeButton, SIGNAL(clicked()), this, SLOT(closeSocket()));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(serverGroupBox);
    mainLayout->addWidget(answerGroupBox);
    mainLayout->addWidget(closeButton);
    setLayout(mainLayout);
    setWindowTitle(tr("Connect to Tetris Server"));
}

TetrisNetwork:: ~TetrisNetwork()
{
  delete serverGroupBox;
  delete answerGroupBox;
  delete closeButton;
}

void TetrisNetwork::createServerGroupBox()
{
  serverGroupBox = new QGroupBox(tr("Server Information"));
  QGridLayout *layout = new QGridLayout;
  serverLabel = new QLabel("Server: ");
  serverName = new QLineEdit("127.0.0.1");
  layout -> addWidget(serverLabel, 0, 0);
  layout -> addWidget(serverName, 0, 1);
  portLabel = new QLabel("Port: ");
  portNumber = new QLineEdit("9462");
  connectButton = new QPushButton("Connect");
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
  if(srvMsg.compare("ID?"))
  {
    socket -> write("ID=19251");
  }

}

void TetrisNetwork::reportConnected()
{
  tetrisAnswer -> append("connected");
  isConnected = true;
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
  if(srvMsg.compare("GAMETYPE?")==1)
  {
    socket -> write("GAMETYPE=tetris\n");
  }
  if(srvMsg.compare("READY?")==1)
  {
    socket -> write("READY");
  }
}

void TetrisNetwork::closeSocket()
{
  if (isConnected == true)
    {
      socket -> write("bye\n");
      socket -> flush();
    }
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
