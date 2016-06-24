#include "src/ia/murs_impasse.h"

#include <mutex>
std::mutex my_mutex_impasse;
bool find;

// _____________ CAS 1 ___________  DEPLACEMENT 1 ____________ //
// _____________________________________________________________________________________________  //

void aller_haut_tantque_1 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = UP;

            send_direction ( robot->id , 0 , robot->dir_scan);

            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }

        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
        {
             direction_UP_murs_UP_1 (robot,maze,x_begin,y_begin);
             break;
        }

        cout << "HAUT TQ NOT LEFT" << endl;
        robot->dir = UP;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();

        drawVisited(maze, robot);
    }
}


void aller_gauche_tantque_1 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = LEFT;

            send_direction ( robot->id , 0 , robot->dir_scan);

            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }

        if(robot->x == 0 )
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0))
        {
            aller_haut_tantque_1 (robot,maze,LEFT,x_begin,y_begin);

        }

        cout << "GAUCHE TQ NOT x == 0" << endl;
        robot->dir = LEFT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();

        drawVisited(maze, robot);
    }
}




void aller_bas_tantque_1 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = DOWN;

            send_direction ( robot->id ,0 , robot->dir_scan);

            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }

        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {
            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0))
        {
            cout << "ASTART  " << endl;
            draw(maze, robot);
            drawVisited(maze, robot);
             cout << "LE COURANT : " << x_begin << robot->y - 1 <<  endl;
            cout << "LE BUT : " << x_begin << robot->y - 1 <<  endl;

             find_path_not_ricochet(robot->x,robot->y,x_begin,robot->y - 1,maze,robot);
             robot->x = x_begin;
             robot->y = robot->y - 1;
        }

        cout << "BAS TQ NOT RIGHT" << endl;
        robot->dir = DOWN;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();

        drawVisited(maze, robot);
    }
}



void aller_droite_tantque_1 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = RIGHT;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }

        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & RIGHT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) != 0))
        {
            aller_bas_tantque_1(robot,maze,RIGHT,x_begin,y_begin);
        }

        cout << "DROITE TQ NOT UP" << endl;
        robot->dir = RIGHT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();

        drawVisited(maze, robot);
    }
}



void direction_UP_murs_UP_1 (Robot* robot,repr* maze,int x_begin, int y_begin)
{
    int receive;
    aller_droite_tantque_1 (robot,maze,UP,x_begin,y_begin);

    if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) == 0)
    {
        cout << "On envoie une demande de scanne !" << endl;

        robot->dir_scan = UP;

        send_direction ( robot->id , 0 , robot->dir_scan);
        receive = recevoir(robot->id);

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();
    }

    if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
    {
         direction_UP_murs_UP_1 (robot,maze,x_begin,y_begin);
    }

    robot->dir = UP;
    robot->dir_scan = LEFT;

    send_direction (robot->id, robot->dir,robot->dir_scan);
    robot->y++;

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir (robot,receive,maze);
    my_mutex_impasse.unlock();

    send_direction (robot->id,0,0);

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir_scan  (robot,receive,maze);
    my_mutex_impasse.unlock();

    aller_haut_tantque_1 (robot,maze,LEFT,x_begin,y_begin);

    aller_gauche_tantque_1 (robot,maze,UP,x_begin,y_begin);

}


// __________ CAS 2 _______ DEPLACEMENT 1 ________________//
// _____________________________________________________________________________________________  ///

void aller_bas_tantque_2 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = DOWN;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0))
        {
             direction_DOWN_murs_DOWN_2 (robot,maze,x_begin,  y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = DOWN;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}


void aller_gauche_tantque_2 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = LEFT;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(robot->x == 0 )
        {
            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0))
        {
            aller_bas_tantque_2 (robot,maze,LEFT,x_begin,y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = LEFT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}





void aller_haut_tantque_2 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = UP;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
        {
            find_path_not_ricochet(robot->x,robot->y,x_begin,robot->y - 1 ,maze,robot);
            robot->x = x_begin;
            robot->y = robot->y - 1;
        }

        robot->dir = UP;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}


void aller_droite_tantque_2 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = RIGHT;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }

        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
        {
            aller_haut_tantque_2(robot,maze,RIGHT,x_begin,y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = RIGHT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();

    }
}



void direction_DOWN_murs_DOWN_2 (Robot* robot,repr* maze,int x_begin, int y_begin)
{
    int receive;
    aller_droite_tantque_2 (robot,maze,DOWN,x_begin,y_begin);

    if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) == 0)
    {
        cout << "On envoie une demande de scanne !" << endl;

        robot->dir_scan = UP;

        send_direction ( robot->id , 0 , robot->dir_scan);
        receive = recevoir(robot->id);

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();
    }

    if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0))
    {
         direction_DOWN_murs_DOWN_2 (robot,maze,x_begin,  y_begin);
    }

    robot->dir = DOWN;
    robot->dir_scan = LEFT;

    send_direction (robot->id, robot->dir,robot->dir_scan);
    robot->y--;

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir (robot,receive,maze);
    my_mutex_impasse.unlock();

    send_direction (robot->id,0,0);

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir_scan  (robot,receive,maze);
    my_mutex_impasse.unlock();

    aller_bas_tantque_2 (robot,maze,LEFT,x_begin,y_begin);

    aller_gauche_tantque_2 (robot,maze,DOWN,x_begin,y_begin);

}


// _____________ CAS 1 ___________ DEPLACEMENT 2 ______________________ //
// _____________________________________________________________________________________________  ///

void aller_droite_tantque_3 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = RIGHT;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
        {
            direction_RIGHT_murs_RIGHT_3 (robot, maze, x_begin, y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = RIGHT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();

    }
}


void aller_haut_tantque_3 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = UP;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(robot->y == y_begin)
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
        {
            aller_droite_tantque_3 (robot,maze,UP,x_begin,y_begin);
        }

        robot->dir = UP;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}



void aller_gauche_tantque_3 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = LEFT;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0) )
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0))
        {
            find_path_not_ricochet(robot->x,robot->y,robot->x - 1,y_begin,maze,robot);
            robot->x = robot->x - 1;
            robot->y = y_begin;
        }

        robot->dir = LEFT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}

void aller_bas_tantque_3 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = DOWN;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }

        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0))
        {
             aller_gauche_tantque_3 (robot,maze,DOWN,x_begin,y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = DOWN;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}


void direction_RIGHT_murs_RIGHT_3 (Robot* robot,repr* maze,int x_begin, int y_begin)
{
    int receive;
    aller_bas_tantque_3 (robot,maze,RIGHT,x_begin,y_begin);

    if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) == 0)
    {
        cout << "On envoie une demande de scanne !" << endl;

        robot->dir_scan = RIGHT;

        send_direction ( robot->id , 0 , robot->dir_scan);
        receive = recevoir(robot->id);

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();
    }

    if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & RIGHT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) != 0))
    {
         direction_RIGHT_murs_RIGHT_3 (robot,maze,x_begin,  y_begin);
    }
    robot->dir = RIGHT;
    robot->dir_scan = UP;

    send_direction (robot->id, robot->dir,robot->dir_scan);
    robot->x++;

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir (robot,receive,maze);
    my_mutex_impasse.unlock();

    send_direction (robot->id,0,0);

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir_scan  (robot,receive,maze);
    my_mutex_impasse.unlock();

    aller_droite_tantque_3 (robot,maze,UP,x_begin,y_begin);

    aller_haut_tantque_3 (robot,maze,RIGHT,x_begin,y_begin);

}


// __________________ CAS 2 _____________ DEPLACEMENT 2 ___________________________//
// _____________________________________________________________________________________________  ///

void aller_droite_tantque_4 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = RIGHT;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
        {
           direction_RIGHT_murs_RIGHT_4 (robot, maze, x_begin, y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = RIGHT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();

    }
}


void aller_bas_tantque_4 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = DOWN;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(robot->y == y_begin)
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0))
        {
             aller_droite_tantque_4 (robot,maze,DOWN,x_begin,y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = DOWN;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}



void aller_gauche_tantque_4 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = LEFT;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0) )
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0))
        {
            find_path_not_ricochet(robot->x,robot->y,robot->x - 1,y_begin,maze,robot);
            robot->x = robot->x - 1;
            robot->y = y_begin;
        }

        robot->dir = LEFT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}


void aller_haut_tantque_4 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = UP;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }

        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
        {
            aller_gauche_tantque_4 (robot,maze,UP,x_begin,y_begin);
        }

        robot->dir = UP;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}


void direction_RIGHT_murs_RIGHT_4 (Robot* robot,repr* maze,int x_begin, int y_begin)
{
    int receive;
    aller_haut_tantque_4 (robot,maze,RIGHT,x_begin,y_begin);

    if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) == 0)
    {
        cout << "On envoie une demande de scanne !" << endl;

        robot->dir_scan = RIGHT;

        send_direction ( robot->id , 0 , robot->dir_scan);
        receive = recevoir(robot->id);

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();
    }

    if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & RIGHT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) != 0))
    {
         direction_RIGHT_murs_RIGHT_4 (robot,maze,x_begin,  y_begin);
    }

    robot->dir = RIGHT;
    robot->dir_scan = DOWN;

    send_direction (robot->id, robot->dir,robot->dir_scan);
    robot->x++;

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir (robot,receive,maze);
    my_mutex_impasse.unlock();

    send_direction (robot->id,0,0);

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir_scan  (robot,receive,maze);
    my_mutex_impasse.unlock();

    aller_droite_tantque_4 (robot,maze,DOWN,x_begin,y_begin);

    aller_bas_tantque_4 (robot,maze,RIGHT,x_begin,y_begin);

}

// ____________ CAS 1 _____________ DEPLACEMENT 3 ______________ //


void aller_haut_tantque_5 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = UP;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
        {
             direction_UP_murs_UP_5 (robot,maze,x_begin, y_begin);
             break;
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = UP;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}




void aller_droite_tantque_5 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = RIGHT;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(robot->x == x_begin)
        {
            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
        {
           aller_haut_tantque_5(robot,maze,RIGHT,x_begin,y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = RIGHT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();

    }
}


void aller_bas_tantque_5 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = DOWN;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0))
        {
             find_path_not_ricochet(robot->x,robot->y,x_begin,robot->y -1,maze,robot);
             robot->x = x_begin;
             robot->y = robot->y - 1;
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = DOWN;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}


void aller_gauche_tantque_5 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = LEFT;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }

        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0))
        {
            aller_bas_tantque_5(robot,maze,LEFT,x_begin,y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = LEFT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}


void direction_UP_murs_UP_5 (Robot* robot,repr* maze,int x_begin, int y_begin)
{
    int receive;
    aller_gauche_tantque_5(robot,maze,UP,x_begin,y_begin);

    if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) == 0)
    {
        cout << "On envoie une demande de scanne !" << endl;

        robot->dir_scan = UP;

        send_direction ( robot->id , 0 , robot->dir_scan);
        receive = recevoir(robot->id);

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();
    }

    if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
    {
         direction_UP_murs_UP_5 (robot,maze,x_begin,  y_begin);
    }


    robot->dir = UP;
    robot->dir_scan = RIGHT;

    send_direction (robot->id, robot->dir,robot->dir_scan);
    robot->y++;

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir (robot,receive,maze);
    my_mutex_impasse.unlock();

    send_direction (robot->id,0,0);

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir_scan  (robot,receive,maze);
    my_mutex_impasse.unlock();

    aller_haut_tantque_5(robot,maze,RIGHT,x_begin,y_begin);

    aller_droite_tantque_5 (robot,maze,UP,x_begin,y_begin);

}


// ____________ CAS 2 _____________ DEPLACEMENT 3 ______________ //




void aller_bas_tantque_6 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = DOWN;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0))
        {
             direction_DOWN_murs_DOWN_6 (robot,maze,x_begin, y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = DOWN;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}


void aller_droite_tantque_6 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = RIGHT;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }

        if(robot->x == conf::SIZE_X - 1)
        {
            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
        {
            aller_bas_tantque_6(robot,maze,RIGHT,x_begin,y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = RIGHT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();

    }
}

void aller_haut_tantque_6 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{


    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = UP;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
        {
            find_path_not_ricochet(robot->x,robot->y,x_begin,robot->y -1 ,maze,robot);
            robot->x = x_begin;
            robot->y = robot->y -1;
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = UP;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}



void aller_gauche_tantque_6 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = LEFT;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0))
        {
            aller_bas_tantque_6(robot,maze,LEFT,x_begin,y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = LEFT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}

void direction_DOWN_murs_DOWN_6 (Robot* robot,repr* maze,int x_begin, int y_begin)
{
    int receive;
    aller_gauche_tantque_6(robot,maze,DOWN,x_begin,y_begin);

    if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) == 0)
    {
        cout << "On envoie une demande de scanne !" << endl;

        robot->dir_scan = DOWN;

        send_direction ( robot->id , 0 , robot->dir_scan);
        receive = recevoir(robot->id);

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();
    }

    if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0))
    {
         direction_DOWN_murs_DOWN_6 (robot,maze,x_begin,  y_begin);
    }


    robot->dir = DOWN;
    robot->dir_scan = RIGHT;

    send_direction (robot->id, robot->dir,robot->dir_scan);
    robot->y--;

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir (robot,receive,maze);
    my_mutex_impasse.unlock();

    send_direction (robot->id,0,0);

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir_scan  (robot,receive,maze);
    my_mutex_impasse.unlock();

    aller_bas_tantque_6(robot,maze,RIGHT,x_begin,y_begin);

    aller_droite_tantque_6(robot,maze,DOWN,x_begin,y_begin);

}


// ____________ CAS 1 _____________ DEPLACEMENT 4 ______________ //


void aller_droite_tantque_7 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = RIGHT;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {
            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
        {
            find_path_not_ricochet(robot->x,robot->y,robot->x -1,y_begin,maze,robot);
            robot->x = robot->x - 1;
            robot->y = y_begin;
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = RIGHT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();

    }
}

void aller_haut_tantque_7 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = UP;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
        {
            aller_droite_tantque_7(robot,maze,LEFT,x_begin,y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = UP;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}

void aller_gauche_tantque_7 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = LEFT;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {
            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0))
        {
            direction_LEFT_murs_LEFT_7 (robot,maze,x_begin,y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = LEFT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}

void aller_bas_tantque_7 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = DOWN;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(robot->y == 0)
        {
            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0))
        {
             aller_gauche_tantque_7(robot,maze,DOWN,x_begin,y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = DOWN;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}


void direction_LEFT_murs_LEFT_7 (Robot* robot,repr* maze,int x_begin, int y_begin)
{
    int receive;
    aller_haut_tantque_7(robot,maze,LEFT,x_begin,y_begin);

    if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) == 0)
    {
        cout << "On envoie une demande de scanne !" << endl;

        robot->dir_scan = LEFT;

        send_direction ( robot->id , 0 , robot->dir_scan);
        receive = recevoir(robot->id);

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();
    }

    if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0))
    {
         direction_LEFT_murs_LEFT_7 (robot,maze,x_begin,  y_begin);
    }


    robot->dir = LEFT;
    robot->dir_scan = UP;

    send_direction (robot->id, robot->dir,robot->dir_scan);
    robot->x--;

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir (robot,receive,maze);
    my_mutex_impasse.unlock();

    send_direction (robot->id,0,0);

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir_scan  (robot,receive,maze);
    my_mutex_impasse.unlock();

    aller_gauche_tantque_7(robot,maze,DOWN,x_begin,y_begin);

    aller_bas_tantque_7(robot,maze,LEFT,x_begin,y_begin);
}



// ____________ CAS 2 _____________ DEPLACEMENT 4 ______________ //

void aller_gauche_tantque_8 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = LEFT;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0))
        {
            direction_LEFT_murs_LEFT_8 (robot,maze,x_begin,y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = LEFT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}


void aller_haut_tantque_8 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = UP;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(robot->y == conf::SIZE_Y - 1)
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
        {
             aller_gauche_tantque_8 (robot,maze,UP,x_begin,y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = UP;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}




void aller_droite_tantque_8 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & RIGHT) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = RIGHT;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & UP) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & UP) != 0))
        {
            find_path_not_ricochet(robot->x,robot->y,robot->x -1,y_begin,maze,robot);
            robot->x = robot->x - 1;
            robot->y = y_begin;
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = RIGHT;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->x++;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();

    }
}


void aller_bas_tantque_8 (Robot *robot, repr* maze,int direction_scanne,int x_begin, int y_begin)
{
    int receive;
    while(1)
    {
        if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) == 0)
        {
            cout << "On envoie une demande de scanne !" << endl;

            robot->dir_scan = DOWN;

            send_direction ( robot->id , 0 , robot->dir_scan);
            receive = recevoir(robot->id);

            send_direction (robot->id,0,0);

            receive = recevoir(robot->id);
            while(!my_mutex_impasse.try_lock()) {};
            ad_information_dir_scan  (robot,receive,maze);
            my_mutex_impasse.unlock();
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) == 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & direction_scanne) != 0))
        {

            break;
        }
        if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & DOWN) != 0))
        {
             aller_droite_tantque_8(robot,maze,DOWN,x_begin,y_begin);
        }

        cout << "LEFT TANT QUE ROBOT PAS SUR 0" << endl;
        robot->dir = DOWN;
        robot->dir_scan = direction_scanne;

        send_direction (robot->id, robot->dir,robot->dir_scan);
        robot->y--;

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir (robot,receive,maze);
        my_mutex_impasse.unlock();

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();


    }
}


void direction_LEFT_murs_LEFT_8 (Robot* robot,repr* maze,int x_begin, int y_begin)
{
    int receive;
    aller_bas_tantque_8 (robot,maze,LEFT,x_begin,y_begin);

    if((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) == 0)
    {
        cout << "On envoie une demande de scanne !" << endl;

        robot->dir_scan = LEFT;

        send_direction ( robot->id , 0 , robot->dir_scan);
        receive = recevoir(robot->id);

        send_direction (robot->id,0,0);

        receive = recevoir(robot->id);
        while(!my_mutex_impasse.try_lock()) {};
        ad_information_dir_scan  (robot,receive,maze);
        my_mutex_impasse.unlock();
    }

    if(((maze->wall[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0) && ((maze->visited[getIndexWallVisited(robot->x, robot->y)] & LEFT) != 0))
    {
         direction_LEFT_murs_LEFT_8 (robot,maze,x_begin,  y_begin);
    }

    robot->dir = LEFT;
    robot->dir_scan = UP;

    send_direction (robot->id, robot->dir,robot->dir_scan);
    robot->x--;

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir (robot,receive,maze);
    my_mutex_impasse.unlock();

    send_direction (robot->id,0,0);

    receive = recevoir(robot->id);
    while(!my_mutex_impasse.try_lock()) {};
    ad_information_dir_scan  (robot,receive,maze);
    my_mutex_impasse.unlock();

    aller_gauche_tantque_8 (robot,maze,UP,x_begin,y_begin);

    aller_haut_tantque_8 (robot,maze,UP,x_begin,y_begin);

}
