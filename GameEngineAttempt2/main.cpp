#include <iostream>
#include "GameEngine.h"

int main()
{
	GameEngine& g = GameEngine::GetInstance();
	g.Initialize();
	g.CreateEntities();
	return 0;
}