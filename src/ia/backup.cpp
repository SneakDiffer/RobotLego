#include <iostream>
#include <fstream>
#include <stdlib.h>     /* atoi */
#include <string>
#include "representation.h"
#include "global.h"


using namespace std;
/*SAVE*/
void save(repr r){
    //On ouvre le fichier backup.txt
    ofstream file("backup.txt",ios::out);
    //On vérifie qu'il est bien ouvert
    if(file){
        //On met l'information sur les dimmenssions du tableau
        file << conf::SIZE_X << endl;
        file << conf::SIZE_Y << endl;
        //On met tout les éléments du du tableau wall
        for(unsigned int i = 0 ; i< r.wall.size();i++){
            if(i== r.wall.size()-1){
                file<< r.wall[i] ;
            }else{
                file<< r.wall[i] <<endl;
            }

        }
        //On ferme le fichier
        file.close();
    }else{
        //On a pas réussit à ouvrir le fichier
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
}

/*LOAD*/
repr load(){
    string ligne;
    int i =0;
    //On ouvre le fichier
    ifstream file("backup.txt");
    //On vérifie qu'il est bien ouvert
    if(file){
        getline(file,ligne);
        conf::SIZE_X = atoi(ligne.c_str());

        getline(file,ligne);
        conf::SIZE_Y = atoi(ligne.c_str());

        repr newR(conf::SIZE_X,conf::SIZE_Y);
        while(getline(file,ligne)){
            newR.wall[i] = atoi(ligne.c_str());
            i++;
        }
        file.close();
        return newR;
    }else{
        //On a pas réussit à ouvrir le fichier
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
    return repr(0,0);
}
