#include "PieceFactory.h"

#include <algorithm>

ChessPiece* PieceFactory::get(string type) {
    if(type == "pawn") return new ChessPiece("../data/checkerpawn.obj", type);

    if(type == "king") return new ChessPiece("../data/crown.obj", type);

    if(type == "tile") return new ChessPiece("../data/tile.obj", type);

    return new ChessPiece();

}
