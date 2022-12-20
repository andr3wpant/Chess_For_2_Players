#include "chessbox.h"
#include "game.h"
#include <QDebug>
#include "king.h"

extern Game *game;
ChessBox::ChessBox(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    //создание квадратной шахматной доски
    setRect(0,0,100,100);
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHasChessPiece(false);
    setChessPieceColor("NONE");
    currentPiece = NULL;
}

ChessBox::~ChessBox()
{
    delete this;
}

void ChessBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

        //если сначала нажали на фигуру, а потом отменили (нажали туда же второй раз)
        if(currentPiece == game->pieceToMove && currentPiece){

            currentPiece->mousePressEvent(event);
            return;
        }

        //если выбрана фигура
        if(game->pieceToMove){
            //если выбран тот же цвет
            if(this->getChessPieceColor() == game->pieceToMove->getSide())
                return;
            //удаление съеденной фигуры
            QList <ChessBox *> movLoc = game->pieceToMove->moveLocation();
            //проверка, что выбранное поле - в области допустимых ходов
            int check = 0;
            for(size_t i = 0, n = movLoc.size(); i < n;i++) {
                if(movLoc[i] == this) {
                    check++;

                }
            }
            // if not prsent return
            if(check == 0)
                return;
            //меняем цвет на обычный
             game->pieceToMove->decolor();

             game->pieceToMove->firstMove = false;
             //для "поедания" фигуры противника, если она в области доступных ходов

            if(this->getHasChessPiece()){
                this->currentPiece->setIsPlaced(false);
                this->currentPiece->setCurrentBox(NULL);
                game->placeInDeadPlace(this->currentPiece);

            }
            //восстановление цвета покинутой клетки
            game->pieceToMove->getCurrentBox()->setHasChessPiece(false);
            game->pieceToMove->getCurrentBox()->currentPiece = NULL;
            game->pieceToMove->getCurrentBox()->resetOriginalColor();
            placePiece(game->pieceToMove);

            game->pieceToMove = NULL;
            //смена очереди хода
            game->changeTurn();
            checkForCheck();
        }
        //выбор, кода поставить фигуру
        else if(this->getHasChessPiece())
        {
            this->currentPiece->mousePressEvent(event);
        }
}

void ChessBox::setColor(QColor color)
{
    brush.setColor(color);
    setBrush(color);
}

void ChessBox::placePiece(ChessPiece *piece)
{

    piece->setPos(x()+50- piece->pixmap().width()/2  ,y()+50-piece->pixmap().width()/2);
    piece->setCurrentBox(this);
    setHasChessPiece(true,piece);
    currentPiece = piece;


}

void ChessBox::resetOriginalColor()
{
    setColor(originalColor);
}



void ChessBox::setOriginalColor(QColor value)
{
    originalColor = value;
    setColor(originalColor);
}

bool ChessBox::getHasChessPiece()
{
    return hasChessPiece;
}

void ChessBox::setHasChessPiece(bool value, ChessPiece *piece)
{
    hasChessPiece = value;
    if(value)
        setChessPieceColor(piece->getSide());
    else
        setChessPieceColor("NONE");
}

void ChessBox::checkForCheck()
{
    int c = 0;
    QList <ChessPiece *> pList = game->alivePiece;
    for(size_t i = 0,n=pList.size(); i < n; i++ ) {

        King * p = dynamic_cast<King *> (pList[i]);
        if(p){
            continue;
        }
        pList[i]->moves();
        pList[i]->decolor();
        QList <ChessBox *> bList = pList[i]->moveLocation();
        for(size_t j = 0,n = bList.size(); j < n; j ++) {
            King * p = dynamic_cast<King *> (bList[j]->currentPiece);
            if(p) {
                if(p->getSide() == pList[i]->getSide())
                    continue;
                bList[j]->setColor(Qt::blue);
                pList[i]->getCurrentBox()->setColor(Qt::darkRed);
                if(!game->check->isVisible())
                    game->check->setVisible(true);
                else{
                    bList[j]->resetOriginalColor();
                    pList[i]->getCurrentBox()->resetOriginalColor();
                    game->gameOver();
                }
                c++;

            }
        }


    }
    if(!c){
        game->check->setVisible(false);
        for(size_t i = 0,n=pList.size(); i < n; i++ )
            pList[i]->getCurrentBox()->resetOriginalColor();
    }
}

QString ChessBox::getChessPieceColor()
{
    return chessPieceColor;
}

void ChessBox::setChessPieceColor(QString value)
{
    chessPieceColor = value;
}
