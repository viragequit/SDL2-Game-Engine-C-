#include "src/engine/Engine.h"
#include "src/timer/Timer.h"



int main(int argc, char *argv[]) {
	
	Engine::getInstance()->initialize();
	
	
	while(Engine::getInstance()->isRunning()) {
		
		Engine::getInstance()->pollEvents();
		
		Engine::getInstance()->update();
		
		Engine::getInstance()->render();
		
		Timer::getInstance()->tick();
	}
	
	Engine::getInstance()->destroy();
	
	return 0;
}