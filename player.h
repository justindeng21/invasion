#ifndef PLAYER_H
#define PLAYER_H

#include "cell.h"

class Player{


    public:

        Player(int id, QString name, bool isComputer);

        void computer();

        std::vector<Projectile * > * getCannons(){return cannons_;};

        std::vector<Soldier * > * getArmy(){return army_;};

        void setNextPlayer(Player * nextPlayer){nextPlayer_ = nextPlayer;}

        Player * getNextPlayer(){return nextPlayer_;};

        int get_id(){return id_;};


    private:

        int id_;

        QString name_;

        bool isComputer_;

        std::vector<Projectile * > * cannons_;

        std::vector<Soldier * > * army_;

        Player * nextPlayer_;

};



#endif // PLAYER_H
