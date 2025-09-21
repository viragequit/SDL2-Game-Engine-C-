#include "TestLevel.h"
#include "../engine/Engine.h"
#include "../graphics/TextureManager.h"
#include "../timer/Timer.h"
#include <iostream>


TestLevel::TestLevel(bool show) {

	draw_level = show;

	stop_watch = StopWatch();

	//load textures for level
	TextureManager::getInstance()->load("death_cloud", "assets/sprites/particles/enemy_explosion.png");

	TextureManager::getInstance()->load("sky", "assets/sprites/parallax_sprites/vb_res_castle_field_static.png");

	TextureManager::getInstance()->load("trees", "assets/sprites/parallax_sprites/gold_forest_1.png");

	TextureManager::getInstance()->load("clouds", "assets/sprites/parallax_sprites/gold_forest_0.png");

	TextureManager::getInstance()->load("castle_field_tiles", "assets/sprites/tilesets/golden_forest_tileset.png");

	TextureManager::getInstance()->load("player", "assets/sprites/player/chinns_new_spritesheet.png");

	TextureManager::getInstance()->loadStreaming("forest_floor", "assets/sprites/pseudo_sprites/forest_floor.png");

	//item textures
	TextureManager::getInstance()->load("acorn", "assets/sprites/items/golden_acorn.png");

	//enemy textures
	TextureManager::getInstance()->load("bigeye", "assets/sprites/enemies/eye_monster_big.png");
	TextureManager::getInstance()->load("minieye", "assets/sprites/enemies/eye_monster_mini.png");



	map = new Tilemap("castle_field_tiles", "assets/tilemaps/chinns_forest.csv", 192, 14, 16, 16, 21);

	player = new Player("player", 40, 64, 32, 32);

	bigeye = new BigEye("bigeye", 216, 108, 32, 32);

	player->setMap(map);
	
	bg1 = new ParallaxLayer("sky", 0, 0, 0.0, 1); //0.22

	bg2 = new ParallaxLayer("clouds", 0, 0, 0.25, 1); //0.24
	
	bg3 = new ParallaxLayer("trees", 0, 0, 0.5, 1); //0.24


	death = new DeathExplosion("death_cloud", 264, 142);
}

TestLevel::TestLevel() {
	
	
}


TestLevel::~TestLevel() {
	
	
}


void TestLevel::draw() {

	if (draw_level == true) {

		bg1->draw();
		bg2->draw();
		bg3->draw();

		map->draw();

		bigeye->draw();

		player->draw();

		//death->draw();
	}
}


void TestLevel::destroy() {

	player->destroy();

	bigeye->destroy();
	
	delete bg1;
	delete bg2;
	delete bg3;
	//delete bg4;
	//delete bg5;
	//delete bg6;

	delete death;
	delete player;

	//delete enemies
	delete bigeye;
	
	delete map;

	std::cout << "Test Level deleted." << std::endl;
}


//Update all things TestLevel related (movement, animation)
void TestLevel::update(float dT) {
	
	//Parallax Testing----------------------------------
	bg1->update(dT);
	bg2->update(dT);
	bg3->update(dT);
	//bg4->update(dT);
	//bg5->update(dT);
	//bg6->update(dT);
	//--------------------------------------------------

	death->update(dT);
	player->update(dT);

	//enemy updates
	bigeye->update(dT);

	//std::cout << "Time: " << stop_watch.getTicks() / 1000.0f << std::endl;
}