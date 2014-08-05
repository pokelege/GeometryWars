#ifndef BULLETSYSTEM
#define BULLETSYSTEM
#include "DebugMemory.h"
#include "Bullet.h"

#define MAXBULLETS 200

class BulletSystem
{
	unsigned int numberofBullets;
	Bullet** bulletList;
public:
	BulletSystem();
	~BulletSystem();

	void addBullet(Bullet* bullet);
	void update(const float& dt);
	void draw(Graphics& graphics);
	unsigned int& getNumber();
	Bullet** getlist();
	void refresh();
};

#endif