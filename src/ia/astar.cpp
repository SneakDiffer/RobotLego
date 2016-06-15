
#include "astar.h"
#define HAUT 1
#define DROITE 2
#define BAS 3
#define GAUCHE 4

std::deque<Case> ouvert;
std::deque<Case> ferme;


std::deque<int> chemin;


int affiche_ouvert ()
{
    unsigned int i;
    for(i = 0 ; i < ouvert.size(); i++)
    {
        cout << "ouvert indice " << i << "  coord x : " <<  ouvert[i].x << " y : " << ouvert[i].y << endl;

    }
    return 0;
}

int affiche_ferme ()
{
    unsigned int i;
    for(i = 0 ; i < ferme.size(); i++)
    {
        cout << "ferme indice " << i << "  coord x : " <<  ferme[i].x << " y : " << ferme[i].y << endl;

    }
    return 0;
}

bool be_ouvert (int x, int y)
{
    unsigned int i;
    for(i = 0 ; i < ouvert.size(); i++)
    {
        if(ouvert[i].x == x && ouvert[i].y == y)
        {
            return true;
        }
    }
    return false;
}

bool be_ferme (int x, int y)
{
    unsigned int i;
    for(i = 0 ; i < ferme.size(); i++)
    {
        if((ferme[i].x == x) && (ferme[i].y == y))
        {
            return true;
        }
    }
    return false;
}

int return_indice (int x,int y)
{
    unsigned int i;
    for(i = 0 ; i < ouvert.size(); i++)
    {
        if(ouvert[i].x == x && ouvert[i].y == y)
        {
            return i;
        }
    }
    return 0;
}

int return_H (int x1, int x2)
{
    int i = 0;
    if(x1 < x2)
    {
       while(x1 != x2)
       {
         x1 += 1;
         i += 1;
       }
       return i;
    }
    if(x2 < x1)
    {
        while(x1 != x2)
        {
            x2 += 1;
            i += 1;
        }
        return i;
    }
    return 0;
}

void new_Case (int new_x, int  new_y, int ancienne_direction, int G_parent, int x_goal, int y_goal,Case *parent)
{

    Case new_case;
    new_case.x = new_x;
    new_case.y = new_y;
    new_case.ancienne_direction = ancienne_direction;
    new_case.G = G_parent + 1;
    new_case.H = return_H(new_x,x_goal) + return_H(new_y,y_goal);
    new_case.F = new_case.G + new_case.H;

    new_case.parent = parent;
    ouvert.push_back(new_case);

}


void return_ouvert_not_ricochet (Case *courant,int x_goal, int y_goal,repr reper)
{
    if(!be_ferme(courant->x, courant->y + 1) && ((reper.wall[getIndexWallVisited(courant->x, courant->y)] & UP) == 0)
            && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & UP) != 0)
    {
        if(!be_ouvert(courant->x, courant->y + 1))
        {
            new_Case (courant->x,courant->y + 1, HAUT,courant->G, x_goal, y_goal,courant);
        }
        else
        {
            int indice = return_indice(courant->x, courant->y + 1);
            int G = courant->G + 1;
            int F = G + ouvert[indice].H;
            if(F < ouvert[indice].F)
            {
                new_Case (courant->x,courant->y + 1, HAUT,courant->G, x_goal, y_goal,courant);
            }
        }
    }
    if(!be_ferme(courant->x + 1, courant->y ) && ((reper.wall[getIndexWallVisited(courant->x, courant->y)] & RIGHT) == 0)
            && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & RIGHT) != 0)
    {
        if(!be_ouvert(courant->x + 1, courant->y ))
        {
            new_Case (courant->x + 1,courant->y, DROITE,courant->G, x_goal, y_goal,courant);
        }
        else
        {
            int indice = return_indice(courant->x + 1, courant->y);
            int G = courant->G + 1;
            int F = G + ouvert[indice].H;
            if(F < ouvert[indice].F)
            {
                new_Case (courant->x + 1,courant->y, DROITE,courant->G, x_goal, y_goal,courant);
            }
        }
    }
    if(!be_ferme(courant->x, courant->y - 1) && ((reper.wall[getIndexWallVisited(courant->x, courant->y)] & DOWN) == 0)
            && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & DOWN) != 0)
    {
        if(!be_ouvert(courant->x, courant->y - 1))
        {
            new_Case (courant->x,courant->y - 1, BAS,courant->G, x_goal, y_goal,courant);
        }
        else
        {
            int indice = return_indice(courant->x, courant->y - 1);
            int G = courant->G + 1;
            int F = G + ouvert[indice].H;
            if(F < ouvert[indice].F)
            {
                new_Case (courant->x,courant->y - 1, BAS,courant->G, x_goal, y_goal,courant);
            }
        }
    }
    if(!be_ferme(courant->x - 1, courant->y ) && ((reper.wall[getIndexWallVisited(courant->x, courant->y)] & LEFT) == 0)
            && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & LEFT) != 0)
    {
        if(!be_ouvert(courant->x - 1, courant->y))
        {
            new_Case (courant->x - 1,courant->y, GAUCHE,courant->G, x_goal, y_goal,courant);
        }
        else
        {
            int indice = return_indice(courant->x - 1, courant->y);
            int G = courant->G + 1;
            int F = G + ouvert[indice].H;
            if(F < ouvert[indice].F)
            {
                new_Case (courant->x - 1,courant->y , GAUCHE,courant->G, x_goal, y_goal,courant);
            }
        }
    }
}



void return_ouvert_ricochet (Case *courant,int x_goal, int y_goal,repr reper)
{
    if(courant->ancienne_direction == HAUT && !be_ferme(courant->x, courant->y + 1)
            && ((reper.wall[getIndexWallVisited(courant->x, courant->y)] & UP) == 0)
            && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & UP) != 0)
    {
        if(!be_ouvert(courant->x, courant->y + 1))
        {
            new_Case (courant->x,courant->y + 1, HAUT,courant->G, x_goal, y_goal,courant);
        }
        else
        {
            int indice = return_indice(courant->x, courant->y + 1);
            int G = courant->G + 1;
            int F = G + ouvert[indice].H;
            if(F < ouvert[indice].F)
            {
                new_Case (courant->x,courant->y + 1, HAUT,courant->G, x_goal, y_goal,courant);
            }
        }
    }
    if(courant->ancienne_direction == DROITE && !be_ferme(courant->x + 1, courant->y )
            && ((reper.wall[getIndexWallVisited(courant->x, courant->y)] & RIGHT) == 0)
            && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & RIGHT) != 0)
    {
        if(!be_ouvert(courant->x + 1, courant->y ))
        {
            new_Case (courant->x + 1,courant->y, DROITE,courant->G, x_goal, y_goal,courant);
        }
        else
        {
            int indice = return_indice(courant->x + 1, courant->y);
            int G = courant->G + 1;
            int F = G + ouvert[indice].H;
            if(F < ouvert[indice].F)
            {
                new_Case (courant->x + 1,courant->y, DROITE,courant->G, x_goal, y_goal,courant);
            }
        }
    }
    if(courant->ancienne_direction == BAS && !be_ferme(courant->x, courant->y - 1)
            && ((reper.wall[getIndexWallVisited(courant->x, courant->y)] & DOWN) == 0)
            && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & DOWN) != 0)
    {
        if(!be_ouvert(courant->x, courant->y - 1))
        {
            new_Case (courant->x,courant->y - 1, BAS,courant->G, x_goal, y_goal,courant);
        }
        else
        {
            int indice = return_indice(courant->x, courant->y - 1);
            int G = courant->G + 1;
            int F = G + ouvert[indice].H;
            if(F < ouvert[indice].F)
            {
                new_Case (courant->x,courant->y - 1, BAS,courant->G, x_goal, y_goal,courant);
            }
        }
    }
    if(courant->ancienne_direction == GAUCHE && !be_ferme(courant->x - 1, courant->y )
            && ((reper.wall[getIndexWallVisited(courant->x, courant->y)] & LEFT) == 0)
            && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & LEFT) != 0)
    {
        if(!be_ouvert(courant->x - 1, courant->y))
        {
            new_Case (courant->x - 1,courant->y, GAUCHE,courant->G, x_goal, y_goal,courant);
        }
        else
        {
            int indice = return_indice(courant->x - 1, courant->y);
            int G = courant->G + 1;
            int F = G + ouvert[indice].H;
            if(F < ouvert[indice].F)
            {
                new_Case (courant->x - 1,courant->y , GAUCHE,courant->G, x_goal, y_goal,courant);
            }
        }
    }

    if(courant->ancienne_direction == HAUT && ((reper.wall[getIndexWallVisited(courant->x, courant->y)] & UP) != 0)
            && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & UP) != 0)
    {
        if(((reper.wall[getIndexWallVisited(courant->x, courant->y)] & LEFT) == 0) && !be_ferme(courant->x - 1, courant->y)
                && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & LEFT) != 0)
        {
            if(!be_ouvert(courant->x - 1, courant->y))
            {
                new_Case (courant->x - 1,courant->y, GAUCHE,courant->G, x_goal, y_goal,courant);
            }
            else
            {
                int indice = return_indice(courant->x - 1, courant->y);
                int G = courant->G + 1;
                int F = G + ouvert[indice].H;
                if(F < ouvert[indice].F)
                {
                    new_Case (courant->x - 1,courant->y , GAUCHE,courant->G, x_goal, y_goal,courant);
                }
            }
        }
        if(((reper.wall[getIndexWallVisited(courant->x, courant->y)] & RIGHT) == 0) && !be_ferme(courant->x + 1, courant->y)
                && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & RIGHT) != 0)
        {
            if(!be_ouvert(courant->x + 1, courant->y))
            {
                new_Case (courant->x + 1,courant->y, DROITE,courant->G, x_goal, y_goal,courant);
            }
            else
            {
                int indice = return_indice(courant->x + 1, courant->y);
                int G = courant->G + 1;
                int F = G + ouvert[indice].H;
                if(F < ouvert[indice].F)
                {
                    new_Case (courant->x + 1,courant->y, DROITE,courant->G, x_goal, y_goal,courant);
                }
            }
        }
    }

    if(courant->ancienne_direction == DROITE && ((reper.wall[getIndexWallVisited(courant->x, courant->y)] & RIGHT) != 0)
            && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & RIGHT) != 0)
    {
        if(((reper.wall[getIndexWallVisited(courant->x, courant->y)] & DOWN) == 0) && !be_ferme(courant->x , courant->y - 1)
                && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & DOWN) != 0)
        {
            if(!be_ouvert(courant->x , courant->y - 1))
            {
                new_Case (courant->x,courant->y - 1, BAS,courant->G, x_goal, y_goal,courant);

            }
            else
            {
                int indice = return_indice(courant->x , courant->y - 1);
                int G = courant->G + 1;
                int F = G + ouvert[indice].H;
                if(F < ouvert[indice].F)
                {
                    new_Case (courant->x,courant->y - 1, BAS,courant->G, x_goal, y_goal,courant);

                }
            }
        }
        if(((reper.wall[getIndexWallVisited(courant->x, courant->y)] & UP) == 0) && !be_ferme(courant->x , courant->y + 1)
                && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & UP) != 0)
        {
            if(!be_ouvert(courant->x , courant->y + 1))
            {
                new_Case (courant->x,courant->y + 1, HAUT,courant->G, x_goal, y_goal,courant);
            }
            else
            {
                int indice = return_indice(courant->x , courant->y + 1);
                int G = courant->G + 1;
                int F = G + ouvert[indice].H;
                if(F < ouvert[indice].F)
                {
                    new_Case (courant->x,courant->y + 1, HAUT,courant->G, x_goal, y_goal,courant);
                }
            }
        }
    }

    if(courant->ancienne_direction == BAS && ((reper.wall[getIndexWallVisited(courant->x, courant->y)] & DOWN) != 0)
            && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & DOWN) != 0)
    {
        if(((reper.wall[getIndexWallVisited(courant->x, courant->y)] & LEFT) == 0) && !be_ferme(courant->x - 1, courant->y)
                && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & LEFT) != 0)
        {
            if(!be_ouvert(courant->x - 1, courant->y))
            {
                new_Case (courant->x - 1,courant->y, GAUCHE,courant->G, x_goal, y_goal,courant);
            }
            else
            {
                int indice = return_indice(courant->x - 1, courant->y);
                int G = courant->G + 1;
                int F = G + ouvert[indice].H;
                if(F < ouvert[indice].F)
                {
                    new_Case (courant->x - 1,courant->y , GAUCHE,courant->G, x_goal, y_goal,courant);

                }
            }
        }
        if(((reper.wall[getIndexWallVisited(courant->x, courant->y)] & RIGHT) == 0) && !be_ferme(courant->x + 1, courant->y)
                && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & RIGHT) != 0)
        {
            if(!be_ouvert(courant->x + 1, courant->y))
            {
                new_Case (courant->x + 1,courant->y, DROITE,courant->G, x_goal, y_goal,courant);
            }
            else
            {
                int indice = return_indice(courant->x + 1, courant->y);
                int G = courant->G + 1;
                int F = G + ouvert[indice].H;
                if(F < ouvert[indice].F)
                {
                    new_Case (courant->x + 1,courant->y, DROITE,courant->G, x_goal, y_goal,courant);
                }
            }
        }
    }

    if(courant->ancienne_direction == GAUCHE && ((reper.wall[getIndexWallVisited(courant->x, courant->y)] & LEFT) != 0)
            && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & LEFT) != 0)
    {
        if(((reper.wall[getIndexWallVisited(courant->x, courant->y)] & DOWN) == 0) && !be_ferme(courant->x, courant->y  -1)
                && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & DOWN) != 0)
        {
            if(!be_ouvert(courant->x, courant->y  -1))
            {
                new_Case (courant->x,courant->y - 1, BAS,courant->G, x_goal, y_goal,courant);
            }
            else
            {
                int indice = return_indice(courant->x, courant->y  -1);
                int G = courant->G + 1;
                int F = G + ouvert[indice].H;
                if(F < ouvert[indice].F)
                {
                    new_Case (courant->x,courant->y - 1, BAS,courant->G, x_goal, y_goal,courant);
                }
            }
        }
        if(((reper.wall[getIndexWallVisited(courant->x, courant->y)] & UP) == 0) && !be_ferme(courant->x, courant->y + 1)
                && (reper.visited[getIndexWallVisited(courant->x, courant->y)] & UP) != 0)
        {
            if(!be_ouvert(courant->x, courant->y + 1))
            {
                new_Case (courant->x,courant->y + 1, HAUT,courant->G, x_goal, y_goal,courant);
            }
            else
            {
                int indice = return_indice(courant->x, courant->y + 1);
                int G = courant->G + 1;
                int F = G + ouvert[indice].H;
                if(F < ouvert[indice].F)
                {
                    new_Case (courant->x,courant->y + 1, HAUT,courant->G, x_goal, y_goal,courant);
                }
            }
        }
    }
}

void direction_begin (Case *courant,int x_goal,int y_goal,repr reper,int largeur,int longueur)
{
    if(courant->x == 0 && courant->y == 0)
    {
        courant->ancienne_direction = HAUT;
        return_ouvert_ricochet(courant,x_goal,y_goal,reper);
        courant->ancienne_direction = DROITE;
        return_ouvert_ricochet(courant,x_goal,y_goal,reper);
    }
    if(courant->x == largeur && courant->y == 0)
    {
        courant->ancienne_direction = HAUT;
        return_ouvert_ricochet(courant,x_goal,y_goal,reper);
        courant->ancienne_direction = GAUCHE;
        return_ouvert_ricochet(courant,x_goal,y_goal,reper);
    }
    if(courant->x == 0 && courant->y == longueur)
    {
        courant->ancienne_direction = BAS;
        return_ouvert_ricochet(courant,x_goal,y_goal,reper);
        courant->ancienne_direction = DROITE;
        return_ouvert_ricochet(courant,x_goal,y_goal,reper);
    }
    if(courant->x == largeur && courant->y == longueur)
    {
        courant->ancienne_direction = BAS;
        return_ouvert_ricochet(courant,x_goal,y_goal,reper);
        courant->ancienne_direction = GAUCHE;
        return_ouvert_ricochet(courant,x_goal,y_goal,reper);
    }
}

Case lowest_node ()
{
        Case min = ouvert[0];

        unsigned int i;
        int indice = 0;
        for(i = 1 ; i < ouvert.size(); i++)
        {
            if(ouvert[i].F < min.F)
            {
                min = ouvert[i];
                indice = i;
            }
        }

        ouvert.erase(ouvert.begin() + indice);
        return min;
}

Case return_node (int x, int y)
{
    unsigned int i;
    for(i = 0 ; i < ferme.size(); i++)
    {
        if(ferme[i].x == x && ferme[i].y == y)
        {
            return ferme[i];
        }
    }
}

void affiche_chemin (Case *courant,int x_dep, int y_dep)
{
    cout << " ----- CHEMIN A L'ENVERS-------" << endl;
    Case test = return_node(courant->x,courant->y);
    int x;
    int y;
    while(1)
    {
        if(test.ancienne_direction == HAUT)
        {
            cout << "HAUT " << endl;
            chemin.push_back(HAUT);
            y = -1;
            x= 0;
        }
        if(test.ancienne_direction == DROITE)
        {
            cout << "DROITE " << endl;
            chemin.push_back(DROITE);
            x = - 1;
            y = 0;
        }
        if(test.ancienne_direction == BAS)
        {
            cout << "BAS " << endl;
            chemin.push_back(BAS);
            x = 0;
            y = 1;
        }
        if(test.ancienne_direction == GAUCHE)
        {
            cout << "GAUCHE " << endl;
            chemin.push_back(GAUCHE);
            x = 1;
            y = 0;
        }
        if(test.x == x_dep && test.y == y_dep)
        {
            break;
        }
        test = return_node(test.x + x,test.y + y);
    }
}

void envoi_chemin (Robot robot)
{
    while(chemin.size() != 0)
    {
        switch(chemin.back())
        {
            case HAUT:
                send_direction (robot.id,HAUT);
                break;
            case BAS:
                send_direction (robot.id,BAS);
                break;
            case DROITE:
                send_direction (robot.id,DROITE);
                break;
            case GAUCHE:
                send_direction (robot.id,GAUCHE);
                break;
        }
        chemin.pop_back();
    }
}

int find_path_ricochet (int x_dep, int y_dep, int x_goal, int y_goal, int longueur, int largeur,repr reper,Robot robot)
{
    Case courant;
    courant.x = x_dep;
    courant.y = y_dep;
    courant.G = 0;
    courant.H = 0;
    courant.F = 0;

    ferme.push_back(courant);
    direction_begin (&courant,x_goal,y_goal,reper,largeur,longueur);
    while(1)
    {
        courant = lowest_node();

        ferme.push_back(courant);
        if(courant.x == x_goal && courant.y == y_goal)
        {
            if((reper.wall[getIndexWallVisited(courant.x, courant.y)] & DOWN) != 0 && (courant.ancienne_direction == BAS)
                    && (reper.visited[getIndexWallVisited(courant.x, courant.y)] & DOWN) != 0)
            {
                cout << "Chemin trouvée ! " << endl;
                affiche_chemin (&courant,x_dep, y_dep);
                envoi_chemin(robot);
                return 0;
                break;
            }
            if((reper.wall[getIndexWallVisited(courant.x, courant.y)] & UP) != 0 && courant.ancienne_direction == HAUT
                    && (reper.visited[getIndexWallVisited(courant.x, courant.y)] & UP) != 0)
            {
                cout << "Chemin trouvée !" << endl;
                 affiche_chemin (&courant,x_dep, y_dep);
                 envoi_chemin(robot);
                 return 0;
                break;
            }
            if((reper.wall[getIndexWallVisited(courant.x, courant.y)] & RIGHT) != 0 && courant.ancienne_direction == DROITE
                    && (reper.visited[getIndexWallVisited(courant.x, courant.y)] & RIGHT) != 0)
            {
                cout << "Chemin trouvée !  " << endl;
                 affiche_chemin (&courant,x_dep, y_dep);
                 envoi_chemin(robot);
                 return 0;
                break;
            }
            if((reper.wall[getIndexWallVisited(courant.x, courant.y)] & LEFT) != 0 && courant.ancienne_direction == GAUCHE
                    && (reper.visited[getIndexWallVisited(courant.x, courant.y)] & LEFT) != 0)
            {
                cout << "Chemin trouvée ! " << endl;
                affiche_chemin (&courant,x_dep, y_dep);
                envoi_chemin(robot);
                return 0;
                break;
            }

        }
        return_ouvert_ricochet(&courant,x_goal,y_goal,reper);

        if(ouvert.size() == 0)
        {
            cout << "Pas de solution ... " << endl;
            break;
        }
    }
    return -1;
}


int find_path_not_ricochet (int x_dep, int y_dep, int x_goal, int y_goal, repr reper,Robot robot)
{
    Case courant;
    courant.x = x_dep;
    courant.y = y_dep;
    courant.G = 0;
    courant.H = 0;
    courant.F = 0;

    ferme.push_back(courant);
    while(1)
    {
        courant = lowest_node();

        ferme.push_back(courant);
        if(courant.x == x_goal && courant.y == y_goal)
        {
            cout << "Chemin trouvée ! " << endl;
            affiche_chemin (&courant,x_dep, y_dep);
            envoi_chemin(robot);
            return 0;
            break;
        }
        return_ouvert_not_ricochet (&courant,x_goal,y_goal,reper);

        if(ouvert.size() == 0)
        {
            cout << "Pas de solution ... " << endl;
            break;
        }
    }
    return -1;
}

