#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "connection.h"
#include "representation.h"
#include "global.h"
using namespace std;

int main()
{
  char btaddress[18] = "00:16:53:16:13:88";
    cout << "Hello world!" << endl;
      // initiate bluetooth connection
  if (init_bluetooth(btaddress) < 0)      {
     cout << "marche pas " << endl;
  }

  // //Envoi message :
  // char reply2[3];
  // sprintf(reply2, "12");
  // nxt_sendmessage(4,reply2);
  // printf(" tu as bien envoyé ! \n");
  //Reception message :
  while(1)
  {
    int recu = recevoir();
    printf(" %d \n",recu);
  }
 conf::SIZE_X = 5;

    return 0;
   }
