#ifndef CELL_H
#define CELL_H


#include <QPainter>
#include <QLabel>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include <QDebug>
#include <QApplication>
#include <QColor>
#include <QPaintEvent>
#include <QPixmap>
#include <QTimer>
#include <QTime>
#include <QThread>



#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <fstream>

class Cell : public QObject, public QGraphicsItem {

    // this makes it so that we can emit signals
    Q_OBJECT

    public:

        Cell(double x, double y, QColor color);
        Cell(double x, double y);
        Cell();

        QRectF boundingRect() const override; // creates the bounding rectangle
        QPainterPath shape() const override; // creates the shape itself



        // paints the cell
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

        /// getter functions:
        ///
        int get_id() {return cell_id_;}; // getter for the id_

        double get_x_() { return x_; }; // getter for the x_ coordinate

        double get_y_() { return y_; }; // getter for the y_ coordinate


        QColor getColor() {return color_; } // getter for the color of the bar


        // setter functions:
        void set_id(int new_id) { cell_id_ = new_id; }; // sets the new id

        void setColor(QColor color){color_ = color;}; // setter for the color of the bar



        // sets a cell active by updating the avatar, updating the current player id, and the bool value
        //void setActive(QString new_player_avatar, int new_player_id) {active_ = true; current_player_overlay_ = new_player_avatar; current_player_ = new_player_id; };
        // sets a cell inactive by updating the color, updating the current player id to -1, and the bool value
        //void setInactive() {active_ = false; current_player_overlay_ = ""; current_player_ = -1; };

        //void mousePressEvent(QGraphicsSceneMouseEvent *event) override; // overrides the mousePressEvent for the cell grid

        void set_x(double new_x){x_ = new_x;};
        void set_y(double new_y){y_ =new_y;};

        void set_coords(double x, double y);


        std::vector<double> * GetLine(double x,double y);

        void set_DestinationReached_flag(bool flag){destinationReached_ = flag;};//setter

        bool get_DestinationReached_flag(){return destinationReached_;};//getter

        void ResetCoords(){set_x(origin_x);set_y(origin_y);};//setter


        bool Check_intersection();



    private:

        int cell_id_; // dictates the id of the cell

        double x_; // dictates the x coordinate
        double y_; // dictates the y coordinate

        int width_; // dictates the width
        int height_; // dictates the height


        double origin_x;
        double origin_y;

        bool destinationReached_; //indicates if the moving cell has reached its destination

        QColor color_; // dictates the color

        QColor original_color_; // dictates the original_color_

        static int num_cells;

};



class Projectile : public Cell{

    public:

        Projectile(double x, double y, QColor color);


};



class Soldier : public Cell{

public:

    Soldier(double x, double y, QColor color);

};




#endif // CELL_H
