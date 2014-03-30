#include <iostream>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#include "RoboteqDevice.h"
#include "ErrorCodes.h"
#include "Constants.h"

using namespace std;
void quitSequence(int sig);
RoboteqDevice device;


int main(int argc, char *argv[])
{
        int i;
	string response = "";
	if(argc<2){
	  cout<<"Need Port";
	  return -1;}
	int status = device.Connect(argv[1]);

	if(status != RQ_SUCCESS)
	{
		cout<<"Error connecting to device: "<<status<<"."<<endl;
		return 1;
	}
	
	for(i=0;i<1;i++){
	cout<<"- SetCommand(_GO, 2, 100)...";
	if((status = (device.SetCommand(_GO, 1, 300)+device.SetCommand(_GO,2,300))) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	}
	signal(SIGTSTP,quitSequence);
	while(1);
	return 0;
}

void quitSequence(int sig){
  int status=1;
  cout<<"- SetCommand(_GO, 2, 0)...";
  while((status != RQ_SUCCESS)){
    if((device.SetCommand(_GO, 1, 0)!=RQ_SUCCESS)||(device.SetCommand(_GO,2,0)!=RQ_SUCCESS)){
      status=16;
    }
    else{
      status=RQ_SUCCESS;
    }
    if(status==RQ_SUCCESS){
      cout<<"succeeded."<<endl;;
    }
    else{
      cout<<"failed --> "<<status<<endl;
    }
  }
  device.Disconnect();
  kill(getpid(),SIGKILL);
}
