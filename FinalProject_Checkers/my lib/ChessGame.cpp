
#include "ChessGame.h"
#include "PieceFactory.h"
#include "RayIntersectionTest.h"

#include <algorithm>

#define MOVE_SPEED	0.1f

int ChessGame::size_of_tile = 5;

const glm::vec3 ChessGame::rayUp(0.0, 0.0f, size_of_tile/2.f);
const glm::vec3 ChessGame::rayDown(0.0, 0.0f, -size_of_tile/2.f);
const glm::vec3 ChessGame::rayLeft(size_of_tile/2.f, 0.0f, 0.0f);
const glm::vec3 ChessGame::rayRight(-size_of_tile/2.f, 0.0f, 0.0f);

ChessGame::ChessGame() {
    setup_light_and_material();
    build_chess_board();
    build_chess_pieces();
    add_extra_board_layer();
}


ChessPiece* ChessGame::getChessPiecesAt(int idx) {
    return _pieces[idx];
}
#define PC_SCALE	4.5f
#define PC_OFFSET_X	0.5f
#define PC_OFFSET_Z 0.5f

void ChessGame::build_chess_board() {

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {

            ChessPiece* t = PieceFactory::get("tile");


            if((i + j) % 2 == 0 ) {
                t->setApperance(*(getWhiteTileAppearance()));
            } else {
                t->setApperance(*(getBlackTileAppearance()));
            }

            t->init();

            glm::vec3 loc(size_of_tile/2 + j*size_of_tile + PC_OFFSET_X, 0.0f, size_of_tile*i + size_of_tile/2 + PC_OFFSET_Z);
            t->setLocation(loc);
            glm::mat4 tranform =  glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(glm::vec3(j*size_of_tile,  i*size_of_tile, 0)) * glm::scale(glm::vec3(5.0, 5.0f, 5.0f));;
            t->setMatrix(tranform);

            _tiles.push_back(t);

        }

    }
}

void ChessGame::build_chess_pieces() {
    // generate blue pawns
    for (size_t i = 0; i < 8; i+=2)
        for(size_t j=0;j<3;j++){
            ChessPiece* pawn1 = PieceFactory::get("pawn");
            
            pawn1->setApperance(*(getSet1Appearance()));
            pawn1->init();
            
            glm::vec3 loc(size_of_tile/2 + (((j+1)%2)+i)*size_of_tile + PC_OFFSET_X, 0.0f, j*size_of_tile + size_of_tile/2 + PC_OFFSET_Z);
            glm::mat4 tranform = glm::translate(loc) * glm::scale(glm::vec3(PC_SCALE, PC_SCALE, PC_SCALE));
            pawn1->setMatrix(tranform);
            pawn1->setLocation(loc);
            pawn1->setPlayer(1);
            pawn1->setKing(false);
            
            _pieces.push_back(pawn1);
        }
    // generate red pawns
     for (size_t i = 0; i < 8; i+=2)
         for(size_t j=5;j<8;j++){
             ChessPiece* pawn2 = PieceFactory::get("pawn");

             pawn2->setApperance(*(getSet2Appearance()));
             pawn2->init();

             glm::vec3 loc = glm::vec3(size_of_tile/2 + (((j+1)%2)+i)*size_of_tile + PC_OFFSET_X, 0.0f, size_of_tile*j + size_of_tile/2 + PC_OFFSET_Z);
             glm::mat4 tranform2 = glm::translate(loc) * glm::scale(glm::vec3(PC_SCALE, PC_SCALE, PC_SCALE));
             pawn2->setMatrix(tranform2);
             pawn2->setLocation(loc);
             pawn2->setPlayer(0);
             pawn2->setKing(false);

             _pieces.push_back(pawn2);
        }
    
}


void ChessGame::draw() {
    for(int i=0; i<_tiles.size(); i++)
    {
        ChessPiece* tile = _tiles[i];
        tile->draw();
    }

    for(int i=0; i<_pieces.size(); i++)
    {
        ChessPiece* piece = _pieces[i];
        piece->draw();
    }

    draw_extra_layer();

    handle_animation();

}


void ChessGame::initPicking() {
    glLoadIdentity();
    glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

    for(int i=0; i<_tiles.size(); i++)
    {
        ChessPiece* tile = _tiles[i];
        setInitPicking(tile);
    }


    for(int i=0; i<_pieces.size(); i++)
    {
        ChessPiece* piece = _pieces[i];
        setInitPicking(piece);
    }

}

void ChessGame::setInitPicking(ChessPiece* piece) {
    ObjectId *oid = piece->getObjectId();
    glUseProgram(piece->getProgram());
	int l0 = glGetUniformLocation(piece->getProgram(), "select_mode");
	int sel0 = glGetUniformLocation(piece->getProgram(), "is_selected");
	int coll0 = glGetUniformLocation(piece->getProgram(), "is_collision");
	glUniform1i(l0, false);
	glUniform1i(sel0, false);
	glUniform1i(coll0, false);
    glUniform4f( glGetUniformLocation(piece->getProgram(), "select_color_id"), oid->r, oid->g, oid->b,1.0 );
}


void ChessGame::preDrawPicking() {

    for(int i=0; i<_tiles.size(); i++)
    {
        ChessPiece* piece = _tiles[i];
        setPreDrawPicking(piece);
    }

    for(int i=0; i<_pieces.size(); i++)
    {
        ChessPiece* piece = _pieces[i];
        setPreDrawPicking(piece);
    }
}

void ChessGame::setPreDrawPicking(ChessPiece *piece) {
    glUseProgram(piece->getProgram());
    int l0 = glGetUniformLocation(piece->getProgram(), "select_mode");

    glUniform1i(l0, true);

    // render
    piece->draw();
    glUniform1i(l0, false);

}

void ChessGame::handleSelectedColor(float col[4]) {
    int id = ObjectIdFactory::getIdFromColor(col);

    ChessPiece* p = getObjectById(id);

    if(_selected_piece != NULL && _selected_piece != _clicked_piece && _selected_piece != _clicked_tile) {
        unhighlightAPiece(_selected_piece);
    }

    if(p != NULL) {
        _selected_piece = p;
        highlightAPiece(p);

    }

}
void ChessGame::unhighlightAPiece(ChessPiece *p) {
	glUseProgram(p->getProgram());
	int uniform_id = glGetUniformLocation(p->getProgram(), "is_selected");

	glUniform1i(uniform_id, false);

	glUseProgram(0);
}

void ChessGame::highlightAPiece(ChessPiece *p) {
	glUseProgram(p->getProgram());
	int uniform_id = glGetUniformLocation(p->getProgram(), "is_selected");

	glUniform1i(uniform_id, true);

	glUseProgram(0);
}

void ChessGame::unhighlightCollision(ChessPiece *p) {
	glUseProgram(p->getProgram());
	int uniform_id = glGetUniformLocation(p->getProgram(), "is_collision");

	glUniform1i(uniform_id, false);

	glUseProgram(0);
}

void ChessGame::highlightCollision(ChessPiece *p) {
	glUseProgram(p->getProgram());
	int uniform_id = glGetUniformLocation(p->getProgram(), "is_collision");

	glUniform1i(uniform_id, true);

	glUseProgram(0);
}

ChessPiece* ChessGame::getObjectById(int id) {

    for(int i=0; i<_pieces.size(); i++)
    {
        ChessPiece* piece = _pieces[i];
        if(piece->getObjectId()->id == id) return piece;
    }

    for(int i=0; i<_tiles.size(); i++)
    {
        ChessPiece* piece = _tiles[i];
        if(piece->getObjectId()->id == id) return piece;
    }

    return NULL;

}

void ChessGame::movePiece(ChessPiece *current_pos, ChessPiece * to_pos){

    _animating_piece = current_pos;
    _destination_tile = to_pos;

}

bool ChessGame::checkFeasiblemove(){
    float chesspos_x=_clicked_piece->getLocation().x, chesspos_z=_clicked_piece->getLocation().z;
    int diff_x=_clicked_piece->getLocation().x-_clicked_tile->getLocation().x;
    //int diff_y=_clicked_piece->getLocation().y-_clicked_tile->getLocation().y;
    int diff_z=_clicked_piece->getLocation().z-_clicked_tile->getLocation().z;
    
    
    if(_clicked_piece->getPlayer()==1&&_clicked_piece->getPlayer()==current_player){

        if(abs(diff_x)==size_of_tile && diff_z==-size_of_tile)
            return true;
        
        if(_clicked_piece->isKing()&&abs(diff_x)==size_of_tile && diff_z==size_of_tile)
            return true;
        
        if(abs(diff_x)==2*size_of_tile&&diff_z==-2*size_of_tile)
            return true;
        
        if(_clicked_piece->isKing()&&abs(diff_x)==-2*size_of_tile&&diff_z==2*size_of_tile)
            return true;
        

    }
    
    if(_clicked_piece->getPlayer()==0&&_clicked_piece->getPlayer()==current_player){
        if(abs(diff_x)==size_of_tile && diff_z== size_of_tile)
            return true;
        
        if(_clicked_piece->isKing()&&abs(diff_x)==size_of_tile && diff_z==-size_of_tile)
            return true;
        
        if(abs(diff_x)==2*size_of_tile&&diff_z==2*size_of_tile)
            return true;
        
        if(_clicked_piece->isKing()&&abs(diff_x)==-2*size_of_tile&&diff_z==-2*size_of_tile)
            return true;
    }
    
    return false;
    

}

void ChessGame::handleMouseRelease() {
    if(_selected_piece == NULL) {
        _clicked_piece = NULL;
        _clicked_tile = NULL;
        return;
    }

    if(_clicked_piece !=NULL && _selected_piece->getType() == "tile") { // click on tile
        if(_clicked_tile) unhighlightAPiece(_clicked_tile);

        _clicked_tile = _selected_piece;
        
        if(checkFeasiblemove())
            movePiece(_clicked_piece, _clicked_tile);
        
    } else if (_selected_piece->getType() == "pawn") { // click on a piece
        if(_clicked_piece) unhighlightAPiece(_clicked_piece);
        if(_clicked_tile) unhighlightAPiece(_clicked_tile);

        _clicked_piece = _selected_piece;
         unhighlightAPiece(_clicked_piece);

    }
}


void ChessGame::handleCollision(){
    bool collision = false;
    int count = 0;
    for (int i = 0; i < _pieces.size(); i++)
    {
        collision = false;
        ChessPiece *p = _pieces[i];
        glm::vec3 s = _clicked_piece->getLocation();
        s += glm::vec3(0.f, .1f, .0f);

        if (p->getPlayer() != _clicked_piece->getPlayer() &&
            sqrt(pow(s.x - p->getLocation().x,2) + pow(s.z - p->getLocation().z,2)) < size_of_tile)
        {
            _intersectList.clear();
            count++;
        
            glm::vec3 e = s + (sqrt(2.f)/2.f) * (rayUp + rayRight);
            if (RayIntersectionTest::intersect(s, e, *p, _intersectList)) {
                collision = true;
            }

            e = s + (sqrt(2.f)/2.f) * (rayDown + rayRight);
            if (RayIntersectionTest::intersect(s, e, *p, _intersectList)) {
                collision = true;
            }

            e = s + (sqrt(2.f)/2.f) * (rayDown + rayLeft);
            if (RayIntersectionTest::intersect(s, e, *p, _intersectList)) {
                collision = true;
            }

            e = s + (sqrt(2.f)/2.f) * (rayUp + rayLeft);
            if (RayIntersectionTest::intersect(s, e, *p, _intersectList)) {
                collision = true;
            }
        }

        if (collision)
        {
            highlightCollision(p);
            _pieces.erase(_pieces.begin()+i);
        } else {
            unhighlightCollision(p);
        }
    }
}


void ChessGame::handle_animation() {
    if(_animating_piece == NULL || _destination_tile == NULL) return;
    

    glm::vec3 direction = _destination_tile->getLocation()-_animating_piece->getLocation();
    //cout<<"x:"<<direction.x<<endl;
    direction = direction.operator/=(100);
    //cout<<"x/100:"<<direction.x<<endl;

    if(abs(_animating_piece->getLocation().x-_destination_tile->getLocation().x)>=0.05
         ||abs(_animating_piece->getLocation().z-_destination_tile->getLocation().z)>=0.05){
       _animating_piece->translatePiece(direction);
        handleCollision();
    } else {
        _animating_piece = NULL;
        _destination_tile = NULL;
        current_player=abs(current_player-1);
        update_chessboard();
    }
}

void ChessGame::update_chessboard(){
    //int num_king=0;
                //_clicked_piece->setKing(true);
                for(int i=0;i<_pieces.size();i++){
                    if(_pieces[i]->getPlayer()==1&&!_pieces[i]->isKing()){

                        if(abs(_pieces[i]->getLocation().z-(7*size_of_tile + size_of_tile/2 + PC_OFFSET_Z))<0.1){
                            //_pieces[i]->setKing(true);
                            float chesspos_x=_pieces[i]->getLocation().x, chesspos_z=_pieces[i]->getLocation().z;
                            _pieces.erase(_pieces.begin()+i);
                            ChessPiece* king1 = PieceFactory::get("king");
                            
                            king1->setApperance(*(getSet1Appearance()));
                            king1->init();
                            
                            glm::vec3 loc(chesspos_x, 0.0f, chesspos_z);
                            glm::mat4 tranform = glm::translate(loc) * glm::scale(glm::vec3(PC_SCALE, PC_SCALE, PC_SCALE));
                            king1->setMatrix(tranform);
                            king1->setLocation(loc);
                            king1->setPlayer(1);
                            king1->setKing(true);
                            _pieces.insert(_pieces.begin()+i, king1);
                        }
                    }
                    if(_pieces[i]->getPlayer()==0&&!_pieces[i]->isKing()){
                        
                        if(abs(_pieces[i]->getLocation().z-( size_of_tile/2 + PC_OFFSET_Z))<0.1){
                            //_pieces[i]->setKing(true);
                            float chesspos_x=_pieces[i]->getLocation().x, chesspos_z=_pieces[i]->getLocation().z;
                            _pieces.erase(_pieces.begin()+i);
                            ChessPiece* king2 = PieceFactory::get("king");
                            
                            king2->setApperance(*(getSet2Appearance()));
                            king2->init();
                            
                            glm::vec3 loc(chesspos_x, 0.0f, chesspos_z);
                            glm::mat4 tranform = glm::translate(loc) * glm::scale(glm::vec3(PC_SCALE, PC_SCALE, PC_SCALE));
                            king2->setMatrix(tranform);
                            king2->setLocation(loc);
                            king2->setPlayer(1);
                            king2->setKing(true);
                            _pieces.insert(_pieces.begin()+i, king2);
                        }
                    }
                }
   // cout<<"# King, blue: "<<num_king<<endl;
            
}
