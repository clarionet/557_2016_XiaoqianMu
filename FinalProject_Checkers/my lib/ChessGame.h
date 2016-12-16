#pragma once

// stl include
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// GLEW include
#include <GL/glew.h>

// GLM include files
//#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ChessPiece.h"
#include "HCI557Common.h"
#include "Plane3D.h"

using namespace std;

class ChessGame {

private:
    vector<ChessPiece*> _pieces;
    vector<ChessPiece*> _tiles;
    

    vector<ChessPiece*> _animating_locations;
    ChessPiece* _animating_piece;
    ChessPiece* _destination_tile;


  	vector<glm::vec3> _intersectList;

    GLDirectLightSource _default_light_source;
    GLSpotLightSource _spot_light_source;

    GLDirectLightSource _set_1_light_source;
    GLSpotLightSource _set_1_spot_light_source;
    GLSpotLightSource _set_1_spot_light_source_2;
    GLSpotLightSource _set_1_spot_light_source_3;

    GLSpotLightSource _set_2_spot_light_source;


    GLMaterial _default_material;
    GLMaterial _wood_material;
    GLMaterial _metal_material;
    GLMaterial _white_tile_material;
    GLMaterial _black_tile_material;

    GLMaterial _set_1_material;
    GLMaterial _set_2_material;

    void setInitPicking(ChessPiece* obj);
    void setPreDrawPicking(ChessPiece* obj);
    
    ChessPiece * _selected_piece;
    ChessPiece * _clicked_piece;
    ChessPiece * _clicked_tile;
    GLPlane3D * _extra_layer;

//	const static glm::vec3 moveUp;
//	const static glm::vec3 moveDown;
//	const static glm::vec3 moveLeft;
//	const static glm::vec3 moveRight;

	const static glm::vec3 rayUp;
	const static glm::vec3 rayDown;
	const static glm::vec3 rayLeft;
	const static glm::vec3 rayRight;

public:
    static int size_of_tile;
    int current_player=1;

    ChessGame();

    ChessPiece* getChessPiecesAt(int idx);
    void build_chess_board();
    void build_chess_pieces();
    void setup_light_and_material();
    void draw();
    void preDrawPicking();
    void initPicking();
	void handleSelectedColor(float col[4]);
	void unhighlightAPiece(ChessPiece* p);
	void highlightAPiece(ChessPiece* p);

	void unhighlightCollision(ChessPiece* p);
	void highlightCollision(ChessPiece* p);

    void movePiece(ChessPiece* current_pos, ChessPiece* to_pos);

    void add_extra_board_layer();

    ChessPiece* getObjectById(int id);

    GLAppearance* getDefaultAppearance();
    GLAppearance* getWhiteTileAppearance();
    GLAppearance* getBlackTileAppearance();
    GLAppearance* getWaterAppearance();
    GLAppearance* getSet1Appearance();
    GLAppearance* getSet2Appearance();
    GLAppearance* getSet1Appearance_king();
    GLAppearance* getSet2Appearance_king();

	void handleMouseRelease();
	void handleKeyPress(int, int);
    void handleCollision();
    bool checkFeasiblemove();
    void update_chessboard();

    void draw_extra_layer();
    void handle_animation();
    int location;
};
