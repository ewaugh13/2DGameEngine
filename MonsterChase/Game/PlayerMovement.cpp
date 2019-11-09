#include "PlayerMovement.h"
#include <conio.h>

//PlayerMovement::PlayerMovement(PlayerMovement & i_OtherPMovement)
//{
//	this->m_GridSize = i_OtherPMovement.m_GridSize;
//	this->m_Playing = i_OtherPMovement.m_Playing;
//}

void PlayerMovement::BeginUpdate(Actor & i_Actor)
{
	switch (_getch())
	{
		case 'A':
		case 'a':
			i_Actor.GetPosition().decrementXValue();
			if (i_Actor.GetPosition().GetX() < -GRID_SIZE)
				i_Actor.GetPosition().SetX((float)-GRID_SIZE);
			break;
		case 'D':
		case 'd':
			i_Actor.GetPosition().incrementXValue();
			if (i_Actor.GetPosition().GetX() > GRID_SIZE)
				i_Actor.GetPosition().SetX((float)GRID_SIZE);
			break;
		case 'W':
		case 'w':
			i_Actor.GetPosition().incrementYValue();
			if (i_Actor.GetPosition().GetY() > GRID_SIZE)
				i_Actor.GetPosition().SetY((float)GRID_SIZE);
			break;
		case 'S':
		case 's':
			i_Actor.GetPosition().decrementYValue();
			if (i_Actor.GetPosition().GetY() < -GRID_SIZE)
				i_Actor.GetPosition().SetY((float)-GRID_SIZE);
			break;
		case 'Q':
		case 'q':
			PLAYING = false;
			break;
		default:
			return;
	}
}
