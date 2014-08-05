#ifndef SHIPSYSTEM
#define SHIPSYSTEM
#include "BulletSystem.h"
#include "Spaceship.h"
using namespace Core;
#define MAXSHIPS 10

class Spaceship;
class BulletSystem;

class ShipSystem
{
	unsigned int numberofShips;
	RandomItemsGenerator rand;
	Spaceship** shipList;
public:
	ShipSystem();
	~ShipSystem();
	Spaceship* assignTarget();
	unsigned int numberofPlayers();
	bool addShip(Spaceship* ship);
	void shot(BulletSystem& bullets, ParticleSystem& particles);
	bool update(const float& dt, bool warp, ParticleSystem& Psystem, BulletSystem& Bsystem, unsigned int& score);
	bool update(const float& dt, bool warp, ParticleSystem& Psystem, BulletSystem& Bsystem, Walls& walls, unsigned int& score);
	void draw(Graphics& graphics);
	void refresh();
};

#endif