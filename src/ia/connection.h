/*=================================================
 *                 CONNECTION.H                   *
 *           Authors: Defonte & Rolland           *
 *------------------------------------------------*
 * Fichier.h contenant les fonction bluetooth     *
 *================================================*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
// Socket, used for Bluetooth socket
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
using namespace std;


// Bluetooth headers
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int init_bluetooth(char *btAddress, int robot);

//int robot  == robot.id
//direction robot : robot.dir
//direction scanne : robot.dir_scan

//Envoyer une direction robot : send_direction ( robot.id , robot.dir , 0 )
//Envoyer une direction scanne : send_direction ( robot.id , 0 , robot.dir_scan )
//Envoyer les deux : send_direction ( robot.id , robot.dir , robot.dir_scan )
//Envoyer une confirmation de réception :   send_direction ( robot.id , 0 , 0 )

void send_direction (int robot, int direction,int direction_scanne);

int nxt_sendmessage(int mbox, char *message, int nxtSocket);
int recevoir (int id_robot);
