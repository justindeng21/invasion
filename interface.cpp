#include "interface.h"
#include "ui_interface.h"



interface * interface::instance_ = 0;

interface::interface(QWidget *parent) : QMainWindow(parent), ui(new Ui::interface)
{

   board_ = new Board(this);
   ui->setupUi(this);
   view = ui->graphicsView;
   scene = board_;
   view->setScene(scene);


   scene->setSceneRect(QRect(0 , 0, 750,750));


   resize_window();

}

interface::~interface()
{
    delete ui;
}

void interface::resize_window() {

    int x_component = rand() % 7 + APP_WIDTH; /// resize the screen, due to a Qt bug it won't show any alterations                                 /// until the screen is resized
    int y_component = rand() % 7 + APP_HEIGHT;
    this->resize(x_component,y_component);
    x_component = rand() % 7 + APP_WIDTH; /// resize the screen, due to a Qt bug it won't show any alterations                               /// until the screen is resized
    y_component = rand() % 7 + APP_HEIGHT;
    this->resize(x_component,y_component);


}

void interface::delay_(int time){
    QTime dieTime= QTime::currentTime().addMSecs(time);
    while (QTime::currentTime() < dieTime){
        QCoreApplication::processEvents(QEventLoop::ExcludeUserInputEvents);

    }
}


interface * interface::getInstance(){
    return instance_;
}

void interface::on_test_clicked(){
    //board_->initialize();
}
