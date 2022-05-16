#include "cell.h"





#define CELL_SIZE 10
#define NUM_COLORS 6


int Cell::num_cells  = 0;



/*
 *
 * Constructor
 *
 */
Cell::Cell(double x, double y) : x_(x), y_(y), origin_x(x), origin_y(y){
    width_ = 5;
    height_ = 5;
    color_ = Qt::white;
    destinationReached_ = false;
    cell_id_ = num_cells;
    num_cells++;
}

Cell::Cell(double x, double y, QColor color) : x_(x), y_(y), origin_x(x), origin_y(y), color_(color){
    width_ = 10;
    height_ = 10;
    destinationReached_ = false;
    cell_id_ = num_cells;
    //num_cells++;
}

Cell::Cell(){
    x_ = 0;
    y_ = 0;
    width_ = 760;
    height_ = 760;
    destinationReached_ = false;
    cell_id_ = num_cells;
    color_ = Qt::black;
    //num_cells++;
}



/*
 *
 * Create bounding rect
 *
 */
QRectF Cell::boundingRect() const {
    return QRectF(x_, y_, width_, height_);
}



/*
 *
 * sets Shape
 *
 */

QPainterPath Cell::shape() const {
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}



/*
 *
 * Sets Coords
 *
 */
void Cell::set_coords(double x, double y){
    set_x(x);
    set_y(y);
}





/*
 *
 * Draws the Cell
 *
 */

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget)
    Q_UNUSED(option)
    painter->setBrush(QBrush(color_));
    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
}


/*
 *
 * Returns slope and y-intercept given x,y
 *
 */
std::vector<double> * Cell::GetLine(double x, double y){

    std::vector<double> * variables = new std::vector<double>; //container for slope and y_intercept
    double slope;

    double y_intercept;


    double denominator = this->get_x_() - x;
    double numerator = this->get_y_() - y;



    if(denominator != 0){
        slope = numerator/denominator;

    }

    else{
        return variables;
    }


    y_intercept = this->get_y_() - (slope*this->get_x_());

    variables->push_back(slope);
    variables->push_back(y_intercept);

    return variables;

}


Projectile::Projectile(double x, double y, QColor color) : Cell(x,y,color){

}

Soldier::Soldier(double x, double y, QColor color) : Cell(x,y,color) {

}







