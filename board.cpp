#include "interface.h"


Board::Board(interface * window){


    //creates a background
    Cell * backdrop = new Cell();
    this->addItem(backdrop);


    //creaate 2 players
    Player * player1 = new Player(0, QString("test_1"), false);
    Player * player2 = new Player(1, QString("test_2"), false);
    player1->setNextPlayer(player2);
    player2->setNextPlayer(player1);
    players_.push_back(player1);
    players_.push_back(player2);

    currentPlayer_ = player1;
    currentArmy_ = currentPlayer_->getArmy();
    currentCannon_ = currentPlayer_->getCannons();
    currentOps_ = currentPlayer_->getNextPlayer()->getArmy();

    interface_ = window;


    initialize();
}

Board::~Board(){

}


void Board::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->scenePos().x() <=750 && event->scenePos().x() >=0){
        event_x = event->scenePos().x();
        event_y = event->scenePos().y();





        if( abs((*currentCannon_)[0]->get_x_() - event_x) > 10){


            bool isIntersecting = CheckIntersection();
            std::vector<Cell*> intersectingWalls;

            if(isIntersecting == true){
                intersectingWalls = get_intersectingWalls();
            }


            SetLines();
            while(FireCannons(event_x,event_y,isIntersecting, intersectingWalls) == false);

            if(intersectingWalls.size() != 0){
                DeleteWalls();
            }

            ResetCannon();
            RemoveLines();



            interface_->resize_window();
            SwapPlayers();//changes turn
        }


    }






}




void Board::initialize(){

    int numWallCells = 152;


    for (int i = 0; i < numWallCells; i++ ) {            //make wall at x = 375
        Cell * newCell = new Cell(380, i * 5);
        Cell * newCell2 = new Cell(375, i * 5);
        Cell * newCell3 = new Cell(385, i * 5);



        wall_.push_back(newCell);
        wall_.push_back(newCell2);
        wall_.push_back(newCell3);
        this->addItem(newCell2);
        this->addItem(newCell);
        this->addItem(newCell3);
        interface_->delay_(1);
        interface_->resize_window();
    }

    Projectile * one = new Projectile(0,370,Qt::blue);
    Projectile * two = new Projectile(0,400,Qt::blue);
    Projectile * three = new Projectile(0,340,Qt::blue);
    currentCannon_->push_back(one);
    currentCannon_->push_back(two);
    currentCannon_->push_back(three);

    this->addItem(one);
    this->addItem(two);
    this->addItem(three);


    SwapPlayers();

    one = new Projectile(750,370,Qt::red);
    two = new Projectile(750,400,Qt::red);
    three = new Projectile(750,340,Qt::red);
    currentCannon_->push_back(one);
    currentCannon_->push_back(two);
    currentCannon_->push_back(three);

    this->addItem(one);
    this->addItem(two);
    this->addItem(three);

    SwapPlayers();


}

/*
 * Swaps currentPlayer object to the other player
 */
void Board::SwapPlayers(){



    currentPlayer_ = currentPlayer_->getNextPlayer();

    currentArmy_ = currentPlayer_->getArmy();

    currentCannon_ = currentPlayer_->getCannons();

    currentOps_ = currentPlayer_->getNextPlayer()->getArmy();


    return;
}



void Board::SetLines(){
    int x;
    int y;

    std::vector<Projectile*> cannons = (*currentPlayer_->getCannons());

    for (int i = 0; i  < 3; i++ ) {

        x = cannons[i]->get_x_();

        y = cannons[i]->get_y_();

        QGraphicsLineItem * newLine = this->addLine(x+5,y+5,event_x,event_y);
        newLine->setVisible(true);
        QColor red50 = Qt::red;
        red50.setAlphaF(0.5);
        newLine->setPen(QPen(red50, 3, Qt::SolidLine, Qt::RoundCap));
        lines_.push_back(newLine);

    }



}



void Board::RemoveLines(){

    int numLines = lines_.size();

    for(int i = 0; i < numLines; i++){
        lines_[i]->setVisible(false);
    }
    lines_.clear();
}



bool Board::FireCannons(double x, double y, bool flag, std::vector<Cell*> intersectingWalls){

    std::vector<Projectile*> cannon = (*currentCannon_ );



    for(int i = 0; i < 3; i++){



        std::vector<double> * line_ = cannon[i]->GetLine(x,y);



        double slope = (*line_)[0];



        double y_intercept = (*line_)[1];

        double new_x_val = 0;
        double new_y_val = 0;

        int increment_value = 1;



        if(abs(slope) < 3)
            increment_value = 10;




        if(currentPlayer_->get_id() == 0){
            new_x_val = cannon[i]->get_x_() + increment_value;
            new_y_val = new_x_val * slope + y_intercept;


        }


        if(currentPlayer_->get_id() == 1){
            new_x_val = cannon[i]->get_x_() - increment_value;
            new_y_val = new_x_val * slope + y_intercept;
        }

        cannon[i]->set_coords(new_x_val,new_y_val);


        if(flag == true && intersectingWalls.size() != 0){

            int numIntersectingWalls = intersectingWalls.size();

            for (int j = 0; j < numIntersectingWalls; j++){

                if( abs(cannon[i]->get_x_() - intersectingWalls[j]->get_x_()) < 10){
                    new_y_val = 380 * slope + y_intercept;

                    return true;
                }

            }

        }




        if( abs(event_x - new_x_val) < 10 && abs(event_y - new_y_val) < 10  ){//If cannon reaches destination unimpedecd
            cannon[i]->set_coords(event_x,event_y);
            return true;
        }


    }

    interface_->resize_window();
    interface_->delay_(5);
    return false;


}


void Board::ResetCannon(){
    for (int i = 0; i < 3 ; i++ )
        (*currentCannon_)[i]->ResetCoords();
}

bool Board::CheckIntersection(){



    if(currentPlayer_->get_id() == 0 && event_x >= 375){
        return true;
    }

    else if(currentPlayer_->get_id() == 1 && event_x <= 390){
        return true;
    }

    else return false;


}


std::vector<Cell*> Board::get_intersectingWalls(){

    std::vector<double> * line_ = (*currentCannon_)[0]->GetLine(event_x,event_y);

    double slope = (*line_)[0];
    double y_intercept = (*line_)[1];

    double intercetion_point = slope * 380 + y_intercept;

    if(currentPlayer_->get_id() == 0){
        intercetion_point = slope * 375 + y_intercept;
    }

    else if(currentPlayer_->get_id() == 1){
        intercetion_point = slope * 385 + y_intercept;
    }



    int numWalls = wall_.size();

    std::vector<Cell*> intersetingWalls_;

    for (int i = 0; i <  numWalls; i++ ){
        if(  abs(wall_[i]->get_y_() - intercetion_point) < 30){
            intersetingWalls_.push_back(wall_[i]);
        }

    }

    return intersetingWalls_;


}

void Board::DeleteWalls(){


    std::vector<double> * line_ = (*currentCannon_)[0]->GetLine(event_x,event_y);

    double slope;

    double y_intercept;

    double intercetion_point;

    if(line_->size() != 0){
        slope = (*line_)[0];
        y_intercept = (*line_)[1];
        intercetion_point = slope * 380 + y_intercept;
    }

    else{
        intercetion_point = event_y;
    }




    int numWalls = wall_.size();



    std::vector<Cell*> non_intersetingWalls_;



    for (int i = 0; i <  numWalls; i++ ){
        if(  abs(wall_[i]->get_y_() - intercetion_point) < 30){
            wall_[i]->setVisible(false);
        }
        else
            non_intersetingWalls_.push_back(wall_[i]);

    }


    wall_ = non_intersetingWalls_;
}



void Board::DeploySoldiers(){

//    std::vector<Soldier*>

}


