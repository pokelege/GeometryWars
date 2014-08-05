#include "BulletSystem.h"

BulletSystem::BulletSystem()
{
	bulletList = new Bullet*[0];
	LOG(Info, "Started bulletsystem.");
}

BulletSystem::~BulletSystem()
{
	for (unsigned int i = 0; i < numberofBullets; i++)
	{
		delete bulletList[i];
	}

	delete[] bulletList;
}

unsigned int& BulletSystem::getNumber()
{
	return numberofBullets;
}

Bullet** BulletSystem::getlist()
{
	return bulletList;
}

void BulletSystem::addBullet(Bullet* effect)
{
	if (numberofBullets < MAXBULLETS)
	{
		Bullet** newList = new Bullet*[numberofBullets + 1];

		for (unsigned int i = 0; i < numberofBullets; i++)
		{
			newList[i] = bulletList[i];
		}

		newList[numberofBullets] = effect;
		numberofBullets++;
		delete[] bulletList;
		bulletList = newList;
	}
	else
	{
		delete effect;
		LOG(Warning, "Bullet system full. Deleting bullet...");
	}
}

void BulletSystem::update(const float& dt)
{
	bool isChanged = false;
	for (unsigned int i = 0; i < numberofBullets; i++)
	{
		if (!bulletList[i]->update(dt))
		{
			delete bulletList[i];
			for (unsigned int j = i; j < numberofBullets - 1; j++)
			{
				bulletList[j] = bulletList[j + 1];
			}
			numberofBullets--;
			isChanged = true;
		}
	}

	if (isChanged)
	{
		Bullet** newList = new Bullet*[numberofBullets];

		for (unsigned int i = 0; i < numberofBullets; i++)
		{
			newList[i] = bulletList[i];
		}

		delete[] bulletList;
		bulletList = newList;
	}
}

void BulletSystem::draw(Core::Graphics& graphics)
{
	for (unsigned int i = 0; i < numberofBullets; i++)
	{
		bulletList[i]->draw(graphics);
	}
}

void BulletSystem::refresh()
{
	Bullet** newList = new Bullet*[0];
	for (unsigned int i = 0; i < numberofBullets; i++)
	{
		delete bulletList[i];
	}
	numberofBullets = 0;
	delete[] bulletList;
	bulletList = newList;
}