#include "PlayerMovement.h"
#include <conio.h>

void PlayerMovement::BeginUpdate(Engine::Actor & i_player)
{
	switch (_getch())
	{
		case 'A':
		case 'a':
			i_player.GetPosition().decrementXValue();
			if (i_player.GetPosition().GetX() < -GRID_SIZE)
				i_player.GetPosition().SetX((float)-GRID_SIZE);
			break;
		case 'D':
		case 'd':
			i_player.GetPosition().incrementXValue();
			if (i_player.GetPosition().GetX() > GRID_SIZE)
				i_player.GetPosition().SetX((float)GRID_SIZE);
			break;
		case 'W':
		case 'w':
			i_player.GetPosition().incrementYValue();
			if (i_player.GetPosition().GetY() > GRID_SIZE)
				i_player.GetPosition().SetY((float)GRID_SIZE);
			break;
		case 'S':
		case 's':
			i_player.GetPosition().decrementYValue();
			if (i_player.GetPosition().GetY() < -GRID_SIZE)
				i_player.GetPosition().SetY((float)-GRID_SIZE);
			break;
		case 'Q':
		case 'q':
			PLAYING = false;
			break;
		default:
			return;
	}
}
