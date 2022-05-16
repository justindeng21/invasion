#include "player.h"



Player::Player(int id, QString name, bool isComputer){
    id_ = id;

    name_ = name;

    isComputer_ = isComputer;

    nextPlayer_ = NULL;

    cannons_ = new std::vector<Projectile*>;

    army_ = new std::vector<Soldier*>;
}
