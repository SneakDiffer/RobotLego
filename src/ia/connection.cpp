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






int recevoir ()
{

	unsigned char buf[9];
    //int nbytes = 8;
	int i = 0;
    int len = 0;
	int chiffre = 0;

    while(1){
        do{
            len =read(nxtSocket, &buf[i], 1);
           // printf("[%d]\n", buf[i]);
            //printf("number of bytes returned:  %d\n", i);
            i++;
        }while(i <= 10);
        i=0;
        //chiffre=(int)buf[6]; //ca envoie sur le bit 6
        printf("-------------%d\n", chiffre);
        break;
    }
    return chiffre;
}
