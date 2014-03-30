#include <iostream>
#include <stdio.h>
#include <string.h>

#include "RoboteqDevice.h"
#include "ErrorCodes.h"
#include "Constants.h"

using namespace std;

int main(int argc, char *argv[])
{
        int i;
	string response = "";
	RoboteqDevice device;
	if(argc<2){
	  cout<<"Need Port";
	  return -1;}
	int status = device.Connect(argv[1]);

	if(status != RQ_SUCCESS)
	{
		cout<<"Error connecting to device: "<<status<<"."<<endl;
		return 1;
	}

	cout<<"- SetConfig(_DINA, 1, 1)...";
	if((status = device.SetConfig(_DINA, 1, 1)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;

	//Wait 10 ms before sending another command to device
	sleepms(10);

	int result;
	cout<<"- GetConfig(_DINA, 1)...";
	if((status = device.GetConfig(_DINA, 1, result)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"returned --> "<<result<<endl;

	//Wait 10 ms before sending another command to device
	sleepms(10);

	cout<<"- GetValue(_ANAIN, 1)...";
	if((status = device.GetValue(_ANAIN, 1, result)) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"returned --> "<<result<<endl;

	//Wait 10 ms before sending another command to device
	sleepms(10);
	
	for(i=0;i<1;i++){
	cout<<"- SetCommand(_GO, 2, 100)...";
	if((status = (device.SetCommand(_GO, 1, 300)+device.SetCommand(_GO,2,300))) != RQ_SUCCESS)
		cout<<"failed --> "<<status<<endl;
	else
		cout<<"succeeded."<<endl;
	sleep(10);
	}
	status=1;
	cout<<"- SetCommand(_GO, 2, 0)...";
	while((status != RQ_SUCCESS)){
	  status = (device.SetCommand(_GO, 1, 0)+device.SetCommand(_GO,2,0));
	  if(status==RQ_SUCCESS){
	    cout<<"succeeded."<<endl;;
	  }
	  else{
	    cout<<"failed --> "<<status<<endl;
	  }
}
	device.Disconnect();
	return 0;
}
