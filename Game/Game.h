#ifndef GAME
#define GAME

#include "Engine.h"
#include <sstream>
#include "Clock.h"
#include "Colors.h"
#include "Spaceship.h"
#include "LerpableAsteroid.h"
#include "AsteroidChainController.h"
#include "Walls.h"
#include "Bullet.h"
#include "PlayerShip.h"
#include "ShipSystem.h"
#include "Profiler.h"
#include "EnemyShip.h"
#include "EnemyTurret.h"
#include "PlayerTurret.h"
#include "Logger.h"
#include "LifeDisplay.h"

#define ARROWCONTROL

class Game
{
	static RandomItemsGenerator rand;

	static Clock clock, spawnclock;

#ifdef PROFILING
	static Clock profileClock;
#endif

	//Set up spaceship
	static void setUpSpaceship();
	static void setUpEnemy();

	//Set up asteroid
	static const float ASTEROIDDIAMETER;
	static LerpableAsteroid firstAsteroid;
	static const float rate;

	//Set up asteroid chain
	static AsteroidChainController chain;
	static const float offset;
	static const float angleRate;
	static const float changeRate;
	static void setUpChain();

	//Set up Boundaries
	static Walls wall;

	static Engine::ParticleSystem particleSystem;
	static BulletSystem Bsystem;
	static ShipSystem Ssystem;

#ifdef PROFILING
	static Profiler profile;
#endif

	static void Draw(Core::Graphics& graphics);
	static bool Update(float dt);
	static bool Shipupdates(float& dt);

	static unsigned int lives;
	static unsigned int score;

	static float cooldown;

#ifdef PROFILING
	static float shipsystem, asteroids, particles;
#endif
	
	static enum Modes{Start, Mode1, Mode2, Mode3, Mode4, Over};
	static Modes mode;
	static bool running;

public:
	//Resolutions
	static const int RESWIDTH;
	static const int RESHEIGHT;

	Game();
};

#endif