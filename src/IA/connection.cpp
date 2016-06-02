#include "connection.h"

int nxtSocket;
int status;
int max_message_size=80;

int init_bluetooth(char *btAddress)     {
	struct sockaddr_rc addr={0};

	// Allocate a socket
	nxtSocket = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
	// Set what type and who to connect to
	addr.rc_family = AF_BLUETOOTH;
	addr.rc_channel = (uint8_t) 1;
	str2ba(btAddress, &addr.rc_bdaddr);
	// Connect to the NXT
	status = connect(nxtSocket, (struct sockaddr
	*
	)&addr, sizeof(addr) );
	if (status < 0) {
	perror("Error connecting Bluetooth");
	return status;
	}
	return 0;
}


int nxt_sendmessage(int mbox, char *message)    {
unsigned char btlength[2]={0x00,0x00};
unsigned char cmd[max_message_size];
unsigned char reply[max_message_size];
int result, msgsize, replylength;
int error = 0;

//create the messagewrite command
msgsize = strlen(message) + 1; // add one for null termination
if (msgsize > (max_message_size - 4) )  {
fprintf(stderr, "messagewrite : message is to long");
return -1;
}
// nxt command
cmd[0] = 0x00;
cmd[1] = 0x09;
cmd[2] = mbox;
cmd[3] = msgsize;
memcpy(&cmd[4], message, msgsize);
// bluetooth length
btlength[0]= 4 + msgsize;
// send bluetooth length
if ( (result = write(nxtSocket, btlength, 2)) < 0)      {
perror("error sending messagewrite command ");
return result;
}
// send message
if ( (result = write(nxtSocket, cmd, btlength[0])) < 0) {
perror("error sending messagewrite command ");
return result;
}

		/* ___________ READ REPLY __________ */
if ( (result = read(nxtSocket, reply, 2)) < 0)  {
perror("error receiving messagewrite reply ");
return result;
}
replylength = reply[0] + (reply[1]
*
256);
// get return package
if ( (result = read(nxtSocket, reply, replylength)) < 0)        {
perror("error receiving messagewrite reply ");
return result;
}

// ____________quick check to make sure we got everything___________
if (replylength != result)      {
fprintf(stderr,
"messagewrite : lengths do not match : %d != %d\n",
replylength, result);
}
if (reply[0] != 0x02)   {
fprintf(stderr, "messagewrite : byte 0 : %hhx != 0x02\n", reply[0]);
error = 1;
}
// byte 1
if (reply[1] != 0x09)   {
fprintf(stderr, "messagewrite : byte 1 : %hhx != 0x13\n", reply[1]);
error = 1;
}
// byte 2
if (reply[2] != 0x00)   {
fprintf(stderr, "messagewrite : byte 2, status : %hhx \n", reply[2]);
error = 1;
}
if (error)      {
return -1;
}
return 0;
}




int nxt_readmessage(int mbox, unsigned char ** message)   {
unsigned char btlength[2]={0x00,0x00};
unsigned char cmd[5]={0x0};
unsigned char reply[max_message_size];
int result, cmdlength, msgsize;
int error = 0;

// nxt command
cmd[0] = 0x00;
cmd[1] = 0x13;
cmd[2] = mbox+10;
cmd[3] = 0x00;
cmd[4] = 0x01;
// bluetooth message length
btlength[0] = 5;
// send bluetooth length
if ( (result = write(nxtSocket, btlength, 2)) < 0)      {
perror("error sending messageread command ");
return result;
}
// send command
if ( (result = write(nxtSocket, cmd, 5)) < 0)   {
perror("error sending messageread command ");
return result;
}
//- read reply -----------------------------------------
// get bluetooth message length
if ( (result = read(nxtSocket, reply, 2)) < 0)  {
perror("error receiving messageread reply ");
return result;
}
cmdlength = reply[0] + (reply[1]
*
256);
// get return package
if ( (result = read(nxtSocket, reply, cmdlength)) < 0)  {
perror("error recieveing messageread reply ");
return result;
}
// quick check to make sure we got everything
if (cmdlength != result)        {
fprintf(stderr,
"messageread : lengths do not match : %d != %d\n",
cmdlength, result);
}

printf(" teste relou \n");
/*test relou*/
if (reply[0] != 0x02)   {      // byte 0
//fprintf(stderr, "messageread : byte 0 : %hhx != 0x02\n", reply[0]);
error = 1;
}
if (reply[1] != 0x13)   {      // byte 1
//fprintf(stderr, "messageread : byte 1 : %hhx != 0x13\n", reply[1]);
error = 1;
}
if (reply[2] == 0x40)   {      // byte 2
return reply[2];
}
if (reply[2] != 0x00)   {
//fprintf(stderr, "messageread : byte 2, status : %hhx \n", reply[2]);
error = 1;
}
if (reply[3] != 0x00)   {      // byte 3
//fprintf(stderr, "messageread : byte 3, mbox: %hhx != 0x00\n", reply[3]);
error = 1;
}
if (error)      { return -1; }
//byte 4

msgsize = reply[4];
*message = (char *)malloc(sizeof(char *) * msgsize + 2);
//printf("reply[5-%d]: %s\n", msgsize+6, &reply[5]);
// byte 5-63: message data
memcpy( *message, &reply[5], msgsize);
printf("message: %s\n", * message);
return 0;
}