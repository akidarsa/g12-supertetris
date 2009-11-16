/*tetrisnetwork.cpp*/
#include <QtDebug>
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

}

void TetrisNetwork::reportConnected()
{
  tetrisAnswer -> append("connected");
  socket -> write("ID=19251\n");
  hvsnButton->setEnabled(true);
  cvsnButton->setEnabled(true);
  qualifierButton->setEnabled(true);
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
  srvMsg.clear();
  srvMsg = newMessage;
  commandEmitter();
  tetrisAnswer -> append(newMessage);
}

void TetrisNetwork::commandEmitter(){
  string msg(srvMsg.toLatin1());
  string whatIFound(srvMsg.toLatin1());
  int ago[10];
  int pos[10];
  int i = 0;
  pos[i]=0;
  ago[i]=msg.find("\n");
  while(i!=10&&ago[i] != -1){ 
	i++; 
	pos[i] = msg.find(":",pos[i-1]+1);
	if(pos[i] != -1){ pos[i] = ago[i-1];}
	ago[i] = msg.find("\n",ago[i-1]+1);
  }
  for(int j=0; j<i; j++){
    if(pos[j] != -1){ whatIFound.clear(); whatIFound = msg.substr(pos[j],ago[j]-pos[j]+1); 
}
    else{ break; }
    if(whatIFound.find("19251") != string::npos){
     if(whatIFound.find("LEFT") != string::npos) {
        emit serverLeft1();
     } if(whatIFound.find("RIGHT") != string::npos) {
        emit serverRight1();
     } if(whatIFound.find("ROTATE") != string::npos) {
       emit serverRotate1();
     } if(whatIFound.find("FALL") != string::npos) {
       emit serverFall1();
     } if(whatIFound.find("WIN") != string::npos) {
       emit serverWin1();
     } if(whatIFound.find("LOSE") != string::npos) { 
       emit serverLose1();
     } if(whatIFound.find("GAMEOVER") != string::npos) {
       emit serverGameover1();
     } if(whatIFound.find("PIECE") != string::npos) {
       pos[j] = whatIFound.find("PIECE");
       ago[j] -= pos[j]+6;
       whatIFound = whatIFound.substr(pos[j]+6,ago[j]);
       size_t tempo = whatIFound.find("\n");
       if(tempo!=string::npos){
         whatIFound=whatIFound.erase(tempo);
       }
	   //whatIFound.erase(ago[j]-1);
       emit serverPiece1(whatIFound);
     } if(whatIFound.find("ATTACK") != string::npos) {
       pos[j] = whatIFound.find("ATTACK");
       ago[j] -= pos[j]+7;
       whatIFound = whatIFound.substr(pos[j]+7,ago[j]);
       emit serverAttack1(whatIFound);
     } //else { return; }
   } else {
     if(whatIFound.find("LEFT") != string::npos) {
       emit serverLeft2();
     } else if(whatIFound.find("RIGHT") != string::npos) {
       emit serverRight2();
     } else if(whatIFound.find("ROTATE") != string::npos) {
       emit serverRotate2();
     } else if(whatIFound.find("FALL") != string::npos) {
       emit serverFall2(); 
     } if(whatIFound.find("WIN") != string::npos) {
       emit serverWin2();
     } if(whatIFound.find("LOSE") != string::npos) { 
       emit serverLose2();
     } else if(whatIFound.find("GAMEOVER") != string::npos) {
       emit serverGameover1();
     } else if(whatIFound.find("PIECE") != string::npos) {
       pos[j] = whatIFound.find("PIECE");
       ago[j] -= pos[j]+6;
       whatIFound = whatIFound.substr(pos[j]+6,ago[j]);
       emit serverPiece2(whatIFound);
     } else if(whatIFound.find("ATTACK") != string::npos) {
       pos[j] = whatIFound.find("ATTACK");
       ago[j] -= pos[j]+7;
       whatIFound = whatIFound.substr(pos[j]+7,ago[j]);
       emit serverAttack2(whatIFound);
     } //else { return; }
   }
 }
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
    socket -> write("19251:LEFT\n");
  }
  else if(order == "RIGHT")
  {
    socket -> write("19251:RIGHT\n");
  }
  else if(order == "ROTATE")
  {
    socket -> write("19251:ROTATE\n");
  }
  else if(order == "FALL")
  {
    socket -> write("19251:FALL\n");
  }
  else if(order == "PIECE")
  {
    socket -> write("19251:PIECE\n");
  }
  else if(order == "ATTACK")
  {
    socket -> write("19251:ATTACK\n");
  }
  else if(order == "GAMEOVER")
  {
    socket -> write("19251:GAMEOVER\n");
  }
  else if(order == "WIN")
  {
    socket -> write("19251:WIN\n");
  }
  else if(order == "LOSE")
  {
    socket -> write("19251:LOSE\n");
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
    humanMode = true;
    computerMode = false;
    qualifierMode = false;
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
    humanMode = false;
    computerMode = true;
    qualifierMode = false;
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
    humanMode = false;
    computerMode = false;
    qualifierMode = true;
}

void TetrisNetwork::sendStart()
{
    cout << "test 3 passed" << endl;
    socket -> write("READY\n");
    tetrisAnswer -> append("The game has started.\n Good Luck!");
    getMessage();
    this->accept();
    if(humanMode) {
        emit netGameMode("human");
    }
    else if(computerMode) {
        emit netGameMode("computer");
    }
    else if(qualifierMode) {
        emit netGameMode("qualifier");
    }
}

void TetrisNetwork::disableButtons()
{
  hvsnButton->setEnabled(false);
  cvsnButton->setEnabled(false);
  qualifierButton->setEnabled(false);
  startButton->setEnabled(false);
}
