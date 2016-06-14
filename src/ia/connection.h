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

// Bluetooth headers
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int init_bluetooth(char *btAddress, int robot);

//int robot  == robot.id
//direction : 1 HAUT   2 DROITE   3 BAS     4 GAUCHE
void send_direction (int robot, int direction);

int nxt_sendmessage(int mbox, char *message, int nxtSocket);
int recevoir ();
