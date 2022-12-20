#include "bishop.h"
#include <QDebug>
#include "game.h"
extern Game *game;

Bishop::Bishop(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setImage();
}

void Bishop::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/images/bishop1.png"));
    else
        setPixmap(QPixmap(":/images/bishop.png"));
}

//Возможные ходы слона
void Bishop::moves()
{
    location.clear();
    int row = this->getCurrentBox()->rowLoc;
    int col = this->getCurrentBox()->colLoc;
    QString team = this->getSide();
    //Вверх налево

     for(int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--) {
       if(game->collection[i][j]->getChessPieceColor() == team ) {
           break;

       }
       else
       {
           location.append(game->collection[i][j]);
           if(boxSetting(location.last()) ){
               break;
           }
       }
    }

     //Вверх направо

      for(int i = row-1,j = col+1; i >= 0 && j <= 7; i--,j++) {
        if(game->collection[i][j]->getChessPieceColor() == team ) {
            break;

        }
        else
        {
            location.append(game->collection[i][j]);
            if(boxSetting(location.last())){
                break;
            }
        }
     }

      //Вниз направо

       for(int i = row+1,j = col+1; i <= 7 && j <= 7; i++,j++) {
         if(game->collection[i][j]->getChessPieceColor() == team ) {
             break;

         }
         else
         {
             location.append(game->collection[i][j]);
             if(boxSetting(location.last())){
                 break;
             }
         }
      }

       //Вниз налево

        for(int i = row+1,j = col-1; i <= 7 && j >= 0; i++,j--) {
          if(game->collection[i][j]->getChessPieceColor() == team ) {
              break;

          }
          else
          {
              location.append(game->collection[i][j]);
              if(boxSetting(location.last())){
                  break;
              }

          }
       }

}
