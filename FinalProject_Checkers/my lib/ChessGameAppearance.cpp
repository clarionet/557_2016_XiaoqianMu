#include "ChessGame.h"
#include "PieceFactory.h"

void ChessGame::setup_light_and_material() {
    // create an apperance object.

    _default_light_source._lightPos = glm::vec4(20.0,20.0,20.0, 1.0);
    _default_light_source._ambient_intensity = 0.2;
    _default_light_source._specular_intensity = 5.5;
    _default_light_source._diffuse_intensity = 2.0;
    _default_light_source._attenuation_coeff = 0.0;

    // add the light to this apperance object

    //Spot light
    _spot_light_source._lightPos = glm::vec4(10.0,10.0,10.0, 1.0);
    _spot_light_source._ambient_intensity = 0.3;
    _spot_light_source._specular_intensity = 1.0;
    _spot_light_source._diffuse_intensity = 10.0;
    _spot_light_source._attenuation_coeff = 0.01;
    _spot_light_source._cone_angle = 30;
    _spot_light_source._cone_direction = glm::vec3(5.0, 5.0, 5.0);

    // Create a material object
    _default_material._diffuse_material = glm::vec3(1.0, 0.0, 0.2);
    _default_material._ambient_material = glm::vec3(1.0, 0.0, 0.2);
    _default_material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    _default_material._shininess = 12.0;
    _default_material._transparency = 1.0;

    // Add the material to the apperance object

    // -------------------------- white tile =---------------------


    _white_tile_material._diffuse_material = glm::vec3(1.0, 1.0, 1.0);
    _white_tile_material._ambient_material = glm::vec3(1.0, 1.0, 1.0);
    _white_tile_material._specular_material = glm::vec3(1.0, 1.0, 1.0);

    // _white_tile_material._diffuse_material = glm::vec3(1.0, 0.0, 0.2);
    // _white_tile_material._ambient_material = glm::vec3(1.0, 0.0, 0.2); _white_tile_material._specular_material = glm::vec3(1.0, 1.0, 1.0);
    //

    _white_tile_material._shininess = 12.0;
    _white_tile_material._transparency = 1.0;


    // -------------------------- black tile =---------------------

    _black_tile_material._diffuse_material = glm::vec3(0.0, 0.0, 0.0);
    _black_tile_material._ambient_material = glm::vec3(0.0, 0.0, 0.0);
    _black_tile_material._specular_material = glm::vec3(0.0, 0.0, 0.0);

    _black_tile_material._shininess = 12.0;
    _black_tile_material._transparency = 1.0;

    // set 1
    _set_1_light_source._lightPos = glm::vec4(10.0, 10.0,40.0, 1.0);
    _set_1_light_source._ambient_intensity = 0.2;
    _set_1_light_source._specular_intensity = 5.5;
    _set_1_light_source._diffuse_intensity = 2.0;
    _set_1_light_source._attenuation_coeff = 0.0;

    _set_1_spot_light_source._lightPos = glm::vec4(20.0, 10.0, -5.0, 1.0);
    _set_1_spot_light_source._ambient_intensity = 0.3;
    _set_1_spot_light_source._specular_intensity = 1.0;
    _set_1_spot_light_source._diffuse_intensity = 10.0;
    _set_1_spot_light_source._attenuation_coeff = 0.005;
    _set_1_spot_light_source._cone_angle = 20;
    _set_1_spot_light_source._cone_direction = glm::vec3(1.0, -1.0, 1.0);

    _set_1_spot_light_source_2._lightPos = glm::vec4(-3.0, 10.0, -7.0, 1.0);
    _set_1_spot_light_source_2._ambient_intensity = 0.3;
    _set_1_spot_light_source_2._specular_intensity = 1.0;
    _set_1_spot_light_source_2._diffuse_intensity = 10.0;
    _set_1_spot_light_source_2._attenuation_coeff = 0.005;
    _set_1_spot_light_source_2._cone_angle = 25;
    _set_1_spot_light_source_2._cone_direction = glm::vec3(5.0, -1.0, 1.0);

    _set_1_spot_light_source_3._lightPos = glm::vec4(22.5, 30.0, 2.5, 1.0);
    _set_1_spot_light_source_3._ambient_intensity = 0.3;
    _set_1_spot_light_source_3._specular_intensity = 10.0;
    _set_1_spot_light_source_3._diffuse_intensity = 7.0;
    _set_1_spot_light_source_3._attenuation_coeff = 0.005;
    _set_1_spot_light_source_3._cone_angle = 25;
    _set_1_spot_light_source_3._cone_direction = glm::vec3(22.5, -1.0, 2.5);

    _set_1_material._diffuse_material = glm::vec3(0.0, 0.0, 0.10);
    _set_1_material._ambient_material = glm::vec3(0.0, 0.0, 0.10);
    _set_1_material._specular_material = glm::vec3(0.0, 0.0, 0.10);

    _set_1_material._shininess = 12.0;
    _set_1_material._transparency = 0.9;

    // set 2
    _set_2_spot_light_source._lightPos = glm::vec4(22.5, 15.0, 32.0, 1.0);
    _set_2_spot_light_source._ambient_intensity = 0.3;
    _set_2_spot_light_source._specular_intensity = 1.0;
    _set_2_spot_light_source._diffuse_intensity = 10.0;
    _set_2_spot_light_source._attenuation_coeff = 0.005;
    _set_2_spot_light_source._cone_angle = 30;
    _set_2_spot_light_source._cone_direction = glm::vec3(22.5, -1.0, 37.0);

    _set_2_material._diffuse_material = glm::vec3(0.10, 0.0, 0.0);
    _set_2_material._ambient_material = glm::vec3(0.10, 0.0, 0.0);
    _set_2_material._specular_material = glm::vec3(0.10, 0.0, 0.0);

    _set_2_material._shininess = 12.0;
    _set_2_material._transparency = 0.9;
}


GLAppearance* ChessGame::getDefaultAppearance() {
    GLAppearance* appearance = new GLAppearance("../../data/shaders/multi_vertex_lights_ext.vs", "../../data/shaders/multi_vertex_lights.fs");

    appearance->addLightSource(_default_light_source);
    appearance->addLightSource(_spot_light_source);
    appearance->setMaterial(_default_material);
    appearance->finalize();

    // If you want to change appearance parameters after you init the object, call the update function
    appearance->updateLightSources();

    return appearance;

}
GLAppearance* ChessGame::getWhiteTileAppearance() {
    GLAppearance* appearance = new GLAppearance("../../data/shaders/multi_vertex_lights_ext.vs", "../../data/shaders/multi_vertex_lights.fs");

    appearance->addLightSource(_default_light_source);
    appearance->addLightSource(_spot_light_source);
    appearance->setMaterial(_white_tile_material);
    appearance->finalize();

    // If you want to change appearance parameters after you init the object, call the update function
    appearance->updateLightSources();

    return appearance;

}
GLAppearance* ChessGame::getBlackTileAppearance() {
    GLAppearance* appearance = new GLAppearance("../../data/shaders/multi_vertex_lights_ext.vs", "../../data/shaders/multi_vertex_lights.fs");

    appearance->addLightSource(_default_light_source);
    appearance->addLightSource(_spot_light_source);
    appearance->setMaterial(_black_tile_material);
    appearance->finalize();

    // If you want to change appearance parameters after you init the object, call the update function
    appearance->updateLightSources();

    return appearance;

}

GLAppearance* ChessGame::getWaterAppearance() {
    GLAppearance* apperance_0 = new GLAppearance("../../data/shaders/displacement_texture.vs", "../../data/shaders/displacement_texture.fs");
    
    GLDirectLightSource  light_source;
    light_source._lightPos = glm::vec4(00.0,5.0,20.0, 0.0);
    light_source._ambient_intensity = 0.2;
    light_source._specular_intensity = 7.5;
    light_source._diffuse_intensity = 1.0;
    light_source._attenuation_coeff = 0.0;
    
    // add the light to this apperance object
    apperance_0->addLightSource(light_source);
    
    
    GLSpotLightSource spotlight_source;
    spotlight_source._lightPos = glm::vec4(0.0,20.0,20.0, 1.0);
    spotlight_source._ambient_intensity = 0.2;
    spotlight_source._specular_intensity = 1.0;
    spotlight_source._diffuse_intensity = 8.0;
    spotlight_source._attenuation_coeff = 0.0002;
    spotlight_source._cone_direction = glm::vec3(-1.0, -1.0,-1.0);
    spotlight_source._cone_angle = 20.0;
    
    apperance_0->addLightSource(spotlight_source);
    
    // Create a material object
    GLMaterial material_0;
    material_0._diffuse_material = glm::vec3(0.8, 0.8, 0.8);
    material_0._ambient_material = glm::vec3(0.8, 0.8, 0.8);
    material_0._specular_material = glm::vec3(1.0, 1.0, 1.0);
    material_0._shininess = 12.0;
    material_0._transparency = 0.4;
    
    // Add the material to the apperance object
    apperance_0->setMaterial(material_0);
    
    GLMultiTexture* texture = new GLMultiTexture();
    // int texid = texture->loadAndCreateTextures("../../data/textures/water-texture.bmp", "../../data/maps/noisemap_2.bmp");
    int texid = texture->loadAndCreateTextures("../../data/textures/water-texture.bmp", "../../data/maps/dark.bmp"/*"../../data/maps/water_NRM.bmp"*/);
    //int texid = texture->loadAndCreateTexture("../../data/textures/texture_earth_128x128_a.bmp");
    // texture->setTextureBlendMode(1);
    apperance_0->setTexture(texture);
    
    //************************************************************************************************
    // Finalize the appearance object
    apperance_0->finalize();
    apperance_0->updateLightSources();
    
    return apperance_0;
    
}


void ChessGame::add_extra_board_layer() {
    GLPlane3D* t = new GLPlane3D(0.0, 0.0, 0.0, 1.0, 1.0);

    t->setApperance(*(getWaterAppearance()));

    t->init();

    glm::mat4 tranform = glm::translate(glm::vec3(20, 0.1, 20))  * glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *   glm::scale(glm::vec3(5.0 * 8, 8*5.0f, 0.0f));
    t->setMatrix(tranform);

    glUseProgram(t->getProgram());
    location = glGetUniformLocation(t->getProgram(), "texture_delta");
    glUniform1f(location, 0.00f);
    glUniform1f(glGetUniformLocation(t->getProgram(), "bump_mode"), 0);

    _extra_layer = t;
}

void ChessGame::draw_extra_layer() {
    glUseProgram(_extra_layer->getProgram());
    float time = (float)clock()/CLOCKS_PER_SEC;
    float delta = 0.05f * sin(time * 50.0) + 0.05f;
    glUniform1f(location, delta);

    if(_extra_layer != NULL) _extra_layer->draw();
}

GLAppearance* ChessGame::getSet1Appearance() {
    GLAppearance* appearance = new GLAppearance("../../data/shaders/multi_vertex_lights_ext.vs", "../../data/shaders/multi_vertex_lights.fs");

    appearance->addLightSource(_set_1_light_source);
    appearance->addLightSource(_set_1_spot_light_source);
    appearance->addLightSource(_set_1_spot_light_source_2);
    
    appearance->addLightSource(_default_light_source);
    appearance->setMaterial(_set_1_material);
    appearance->finalize();
    
//    if(king){
//        GLTexture* texture = new GLTexture();
//        
//        int texid = texture->loadAndCreateTexture("../../data/textures/crown.bmp");
//        appearance->setTexture(texture);
//    }

    // If you want to change appearance parameters after you init the object, call the update function
    appearance->updateLightSources();

    return appearance;

}

GLAppearance* ChessGame::getSet2Appearance() {
    GLAppearance* appearance = new GLAppearance("../../data/shaders/multi_vertex_lights_ext.vs", "../../data/shaders/multi_vertex_lights.fs");

    appearance->addLightSource(_default_light_source);
    appearance->addLightSource(_spot_light_source);
    appearance->addLightSource(_set_2_spot_light_source);
    appearance->setMaterial(_set_2_material);
    appearance->finalize();

    // If you want to change appearance parameters after you init the object, call the update function
    appearance->updateLightSources();

    return appearance;

}
GLAppearance* ChessGame::getSet1Appearance_king() {
    GLAppearance* appearance = new GLAppearance("../../data/shaders/single_texture.vs", "../../data/shaders/single_texture.fs");
    
    appearance->addLightSource(_set_1_light_source);
    appearance->addLightSource(_set_1_spot_light_source);
    appearance->addLightSource(_set_1_spot_light_source_2);
    
    appearance->addLightSource(_default_light_source);
    appearance->setMaterial(_set_1_material);
    //appearance->finalize();
    
    GLTexture* texture = new GLTexture();
    int texid = texture->loadAndCreateTexture("../../data/textures/crown.bmp");
    appearance->setTexture(texture);
    appearance->finalize();
    
    // If you want to change appearance parameters after you init the object, call the update function
    appearance->updateLightSources();
    
    return appearance;
    
}

GLAppearance* ChessGame::getSet2Appearance_king() {
    GLAppearance* appearance = new GLAppearance("../../data/shaders/single_texture.vs", "../../data/shaders/single_texture.fs");
    
    appearance->addLightSource(_default_light_source);
    appearance->addLightSource(_spot_light_source);
    appearance->addLightSource(_set_2_spot_light_source);
    appearance->setMaterial(_set_2_material);
    appearance->finalize();
    
    GLTexture* texture = new GLTexture();
    int texid = texture->loadAndCreateTexture("../../data/textures/crown.bmp");
    appearance->setTexture(texture);
    
    
    // If you want to change appearance parameters after you init the object, call the update function
    appearance->updateLightSources();
    
    return appearance;
    
}

