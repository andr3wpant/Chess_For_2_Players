#include "king.h"
#include "game.h"
#include "pawn.h"
extern Game *game;
King::King(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setImage();
}

void King::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/images/king1.png"));
    else
        setPixmap(QPixmap(":/images/king.png"));
}

//допустимые ходы короля
void King::moves()
{

    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();

        if(col > 0 && row > 0 && !(game->collection[row-1][col-1]->getChessPieceColor() == team)) {//вверх, налево
            location.append(game->collection[row-1][col-1]);
            game->collection[row-1][col-1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(col < 7 && row > 0 && !(game->collection[row-1][col+1]->getChessPieceColor() == team)) { // вверх, направо
            location.append(game->collection[row-1][col+1]);
            game->collection[row-1][col+1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(row>0 && !(game->collection[row-1][col]->getChessPieceColor() == team)) {//наверх
            location.append(game->collection[row-1][col]);
            game->collection[row-1][col]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(row<7 && !(game->collection[row+1][col]->getChessPieceColor() == team)) {//вниз
            location.append(game->collection[row+1][col]);
            game->collection[row+1][col]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(col>0 && !(game->collection[row][col-1]->getChessPieceColor() == team)) {// налево
            location.append(game->collection[row][col-1]);
            game->collection[row][col-1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(col<7 && !(game->collection[row][col+1]->getChessPieceColor() == team)) {//направо
            location.append(game->collection[row][col+1]);
            game->collection[row][col+1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(col > 0 && row < 7  && !(game->collection[row+1][col-1]->getChessPieceColor() == team)) {//вниз и налево
            location.append(game->collection[row+1][col-1]);
            game->collection[row+1][col-1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }
        if(col < 7 && row < 7 && !(game->collection[row+1][col+1]->getChessPieceColor() == team)) {//вниз и направо
            location.append(game->collection[row+1][col+1]);
            game->collection[row+1][col+1]->setColor(Qt::darkRed);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(Qt::red);
            }
        }


            findUnSafeLocation();


}
//если ход недопустим - клетка закрашивается тёмно-синим
void King::findUnSafeLocation() {
    QList <ChessPiece *> pList = game->alivePiece;
    for(size_t i = 0,n = pList.size(); i < n; i++) {

        if(pList[i]->getSide() != this->getSide())
        {
            QList <ChessBox *> bList = pList[i]->moveLocation();

            for(size_t j = 0, n = bList.size(); j < n; j++) {
                Pawn *c = dynamic_cast<Pawn *> (pList[i]) ;
                if(c)
                    continue;
                for(size_t k = 0, n = location.size(); k < n; k++) {
                   if(bList[j] == location [k]) {
                       location[k]->setColor(Qt::blue);
                   }
                }
            }
        }
    }
}
