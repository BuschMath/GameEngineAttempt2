#include <iostream>
#include "GameEngine.h"

int main()
{
	GameEngine& g = GameEngine::GetInstance();
	g.Initialize();
	
	while(true)
		g.Render();
	
	return 0;
}