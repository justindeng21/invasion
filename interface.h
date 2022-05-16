#ifndef INTERFACE_H
#define INTERFACE_H



#include "ui_interface.h"
#include "player.h"







QT_BEGIN_NAMESPACE
namespace Ui { class interface; }
QT_END_NAMESPACE

#define APP_WIDTH 1736
#define APP_HEIGHT 1193

class Board;

class interface : public QMainWindow
{
    Q_OBJECT

public:


    /*
     * Constructor & destructor
     */
    interface(QWidget *parent = nullptr);

    ~interface();



    static interface * getInstance();

    static interface * instance_;



    /*
     * Misc methods
     */
    void resize_window();
    void delay_(int time);




private slots:

    void on_test_clicked();




private:

    Board * board_;



    Ui::interface *ui;

    QGraphicsView * view;

    QGraphicsScene * scene;

};


class Board : public QGraphicsScene{
public:


    Board(interface * window);

    ~Board();


    double get_event_x(){return event_x;};

    double get_event_y(){return event_y;};

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void initialize();

    void SetCurrentPlayer();

    void SwapPlayers();

    void SetLines();

    bool FireCannons(double x, double y, bool flag, std::vector<Cell*> intersectingWalls);

    void RemoveLines();

    void ResetCannon();

    bool CheckIntersection();

    std::vector<Cell*> get_intersectingWalls();

    void DeleteWalls();

    void DeploySoldiers();



private:


    double event_x;

    double event_y;

    std::vector<Cell*> wall_;

    std::vector<QGraphicsLineItem *> lines_;

    std::vector<Player*> players_;

    interface * interface_;

    Player * currentPlayer_;


    std::vector<Projectile*> * currentCannon_;

    std::vector<Soldier*> * currentArmy_;

    std::vector<Soldier*> * currentOps_;






};




#endif // INTERFACE_H

