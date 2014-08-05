#include "ShipSystem.h"

ShipSystem::ShipSystem()
{
	shipList = new Spaceship*[0];
	LOG(Info, "Started ship system.")
}

ShipSystem::~ShipSystem()
{
	for (unsigned int i = 0; i < numberofShips; i++)
	{
		delete shipList[i];
	}

	delete[] shipList;
}

Spaceship* ShipSystem::assignTarget()
{
	if (numberofPlayers() > 0)
	{
		for (unsigned int i = 0; i < numberofShips; i++)
		{
			if (shipList[i]->isaPlayer())
			{
				return shipList[i];
			}
		}
	}
	return shipList[(int)rand.RandomRangedFloat(0, (float)numberofShips)];
}

unsigned int ShipSystem::numberofPlayers()
{
	unsigned int num = 0;
	for (unsigned int i = 0; i < numberofShips; i++)
	{
		if (shipList[i]->isaPlayer())
		{
			num++;
		}
	}
	return num;
}

bool ShipSystem::addShip(Spaceship* ship)
{
	if (numberofShips < MAXSHIPS)
	{
		Spaceship** newList = new Spaceship*[numberofShips + 1];

		for (unsigned int i = 0; i < numberofShips; i++)
		{
			newList[i] = shipList[i];
		}

		newList[numberofShips] = ship;
		numberofShips++;
		delete[] shipList;
		shipList = newList;
		return true;
	}
	else
	{
		delete ship;
		LOG(Warning, "Shipsystem full. Deleting ship...")
		return false;
	}
}

void ShipSystem::shot(BulletSystem& bullets, ParticleSystem& particles)
{
	for (unsigned int i = 0; i < numberofShips; i++)
	{
		for (unsigned int j = 0; j < bullets.getNumber(); j++)
		{
			if (shipList[i]->isShot(*(bullets.getlist()[j]), particles))
			{
				bullets.getlist()[j]->setLife(0);
			}
		}
	}
}

bool ShipSystem::update(const float& dt, bool warp, ParticleSystem& Psystem, BulletSystem& Bsystem, unsigned int& score)
{
	shot(Bsystem, Psystem);
	bool isChanged = false;
	for (unsigned int i = 0; i < numberofShips; i++)
	{
		if (!shipList[i]->Update(dt, warp, Psystem, Bsystem, assignTarget()))
		{
			if (shipList[i]->isaPlayer())
			{
				delete shipList[i];
				for (unsigned int j = i; j < numberofShips - 1; j++)
				{
					shipList[j] = shipList[j + 1];
				}
				numberofShips--;
				isChanged = true;
				break;
			}
			else
			{
				delete shipList[i];
				for (unsigned int j = i; j < numberofShips - 1; j++)
				{
					shipList[j] = shipList[j + 1];
				}
				numberofShips--;
				isChanged = true;
			}
		}
	}

	if (isChanged)
	{
		Spaceship** newList = new Spaceship*[numberofShips];

		for (unsigned int i = 0; i < numberofShips; i++)
		{
			newList[i] = shipList[i];
		}

		delete[] shipList;
		shipList = newList;

		if (numberofPlayers() > 0)
		{
			score += 100;
		}
	}

	return(numberofPlayers() > 0);
}

bool ShipSystem::update(const float& dt, bool warp, ParticleSystem& Psystem, BulletSystem& Bsystem, Walls& walls, unsigned int& score)
{
	shot(Bsystem, Psystem);
	bool isChanged = false;
	for (unsigned int i = 0; i < numberofShips; i++)
	{
		if (!shipList[i]->Update(dt, warp, Psystem, Bsystem, assignTarget(), walls))
		{
			if (shipList[i]->isaPlayer())
			{
				delete shipList[i];
				for (unsigned int j = i; j < numberofShips - 1; j++)
				{
					shipList[j] = shipList[j + 1];
				}
				numberofShips--;
				isChanged = true;
				break;
			}
			else
			{
				delete shipList[i];
				for (unsigned int j = i; j < numberofShips - 1; j++)
				{
					shipList[j] = shipList[j + 1];
				}
				numberofShips--;
				isChanged = true;
			}
		}
	}

	if (isChanged)
	{
		Spaceship** newList = new Spaceship*[numberofShips];

		for (unsigned int i = 0; i < numberofShips; i++)
		{
			newList[i] = shipList[i];
		}

		delete[] shipList;
		shipList = newList;

		if (numberofPlayers() > 0)
		{
			score += 100;
		}
	}

	return(numberofPlayers() > 0);
}

void ShipSystem::draw(Graphics& graphics)
{
	for (unsigned int i = 0; i < numberofShips; i++)
	{
		shipList[i]->Draw(graphics);
	}
}

void ShipSystem::refresh()
{
	Spaceship** newList = new Spaceship*[0];
	for (unsigned int i = 0; i < numberofShips; i++)
	{
		delete shipList[i];
	}
	delete[] shipList;
	numberofShips = 0;
	shipList = newList;
}