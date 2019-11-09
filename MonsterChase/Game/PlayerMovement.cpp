#include "PlayerMovement.h"
#include <conio.h>

void PlayerMovement::BeginUpdate(Actor & i_Actor)
{
	switch (_getch())
	{
		case 'A':
		case 'a':
			i_Actor.GetPosition().decrementXValue();
			if (i_Actor.GetPosition().GetX() < -this->m_GridSize)
				i_Actor.GetPosition().SetX((float)-this->m_GridSize);
			break;
		case 'D':
		case 'd':
			i_Actor.GetPosition().incrementXValue();
			if (i_Actor.GetPosition().GetX() > this->m_GridSize)
				i_Actor.GetPosition().SetX((float)this->m_GridSize);
			break;
		case 'W':
		case 'w':
			i_Actor.GetPosition().incrementYValue();
			if (i_Actor.GetPosition().GetY() > this->m_GridSize)
				i_Actor.GetPosition().SetY((float)this->m_GridSize);
			break;
		case 'S':
		case 's':
			i_Actor.GetPosition().decrementYValue();
			if (i_Actor.GetPosition().GetY() < -this->m_GridSize)
				i_Actor.GetPosition().SetY((float)-this->m_GridSize);
			break;
		case 'Q':
		case 'q':
			this->playing = false;
			break;
		default:
			return;
	}
}
