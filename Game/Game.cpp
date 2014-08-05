#include "Game.h"

Clock Game::clock;

#ifdef PROFILING
Clock Game::profileClock;
#endif

Clock Game::spawnclock;

RandomItemsGenerator Game::rand;

//Resolutions
const int Game::RESWIDTH = 1280;
const int Game::RESHEIGHT = 720;

//Set up spaceship

//Set up asteroid
const float Game::ASTEROIDDIAMETER = 25;
LerpableAsteroid Game::firstAsteroid(ASTEROIDDIAMETER, RESWIDTH, RESHEIGHT);
const float Game::rate = 1000;

//Set up asteroid chain
AsteroidChainController Game::chain;
const float Game::offset = 100;
const float Game::angleRate = 1;      
const float Game::changeRate = 2;

//Set up Boundaries
unsigned int Boundary::totalBoundaries = 0;
Walls Game::wall(RESWIDTH, RESHEIGHT);

Engine::ParticleSystem Game::particleSystem;
BulletSystem Game::Bsystem;
ShipSystem Game::Ssystem;

#ifdef PROFILING
Profiler Game::profile("data.csv");
#endif

unsigned int Game::lives;

unsigned int Game::score;

float Game::cooldown = 1;

#ifdef PROFILING
float Game::shipsystem, Game::asteroids, Game::particles;
#endif

Game::Modes Game::mode;

bool Game::running = false;

void Game::Draw(Core::Graphics& graphics)
{
	if (mode == Start || mode == Over)
	{
		graphics.SetColor(WHITE);
#ifdef ARROWCONTROL
		graphics.DrawString(0, 0, "Select a mode by pressing a number:\n1=Warp\n2=Bounce\n3=Mode1 with walls\n4=Mode2 with walls.\n\nAccelerate/decelerate using up/down.\nTurn using left/right.\nGreen enemy ships will follow you.\nGreen enemy ships will respawn after 2 seconds.\nIf there is no cyan player ship present, respawn a player ship instead.\nAlso will lose 1 life.\nMax ships is 10.\nRed turret will rotate to where the mouse is pointing at.\nEnemy turrets rotate randomly.\nLeft-Click to fire bullet.\nPlayer accuracy is 90%.\nEnemy accuracy is 50%\nPress Esc to quit.");
#else
		graphics.DrawString(0, 0, "Select a mode by pressing a number:\n1=Warp\n2=Bounce\n3=Mode1 with walls\n4=Mode2 with walls.\n\nAccelerate/decelerate using W/S.\nTurn using A/D.\nGreen enemy ships will follow you.\nGreen enemy ships will respawn after 2 seconds.\nIf there is no cyan player ship present, respawn a player ship instead.\nAlso will lose 1 life.\nMax ships is 10.\nRed turret will rotate to where the mouse is pointing at.\nEnemy turrets rotate randomly.\nLeft-Click to fire bullet.\nPlayer accuracy is 90%.\nEnemy accuracy is 50%\nPress Esc to quit.");
#endif

		if (mode == Over)
		{
			graphics.SetColor(BLOODRED);
			std::stringstream ss(std::stringstream::in | std::stringstream::out);
			ss << "Game Over" << "\nFinal Score: " << score;
			graphics.DrawString(RESWIDTH / 2, RESHEIGHT / 2, ss.str().c_str());
		}

	}

	if (running)
	{
#ifdef PROFILING
		float shipdraw, asteroiddraw, particledraw, boundarydraw, interval;
#endif
		graphics.SetColor(WHITE);
		std::stringstream ss1(std::stringstream::in | std::stringstream::out);
		ss1 << "Score: " << score << "\nLife: ";
		graphics.DrawString(0, 0, ss1.str().c_str());

		drawLife(graphics, lives, 50, 20);

#ifdef PROFILING
		profileClock.Start();
#endif

		Ssystem.draw(graphics);

#ifdef PROFILING
		shipdraw = profileClock.Stop() * 1000;
		profile.addEntry("Ship system draw", shipdraw);

		profileClock.Start();
#endif

		firstAsteroid.Draw(graphics);
		chain.draw(graphics);

#ifdef PROFILING
		asteroiddraw = profileClock.Stop() * 1000;
		profile.addEntry("Asteroid draw", asteroiddraw);

		profileClock.Start();
#endif

		particleSystem.Draw(graphics);
		Bsystem.draw(graphics);

#ifdef PROFILING
		particledraw = profileClock.Stop() * 1000;
		profile.addEntry("Particle and bullet draw", particledraw);

		profileClock.Start();
#endif

		if (mode == Mode3 || mode == Mode4)
		{
			wall.DrawAllBounds(graphics);
		}

#ifdef PROFILING
		boundarydraw = profileClock.Stop() * 1000;
		profile.addEntry("Boundary draw", boundarydraw);

		graphics.SetColor(WHITE);

		interval = clock.Interval();
		profile.addEntry("SPF", interval * 1000);
		profile.addEntry("FPS", 1 / interval);

		std::stringstream ss(std::stringstream::in | std::stringstream::out);

		ss << (interval * 1000) << " mSPF\n" << (1 / interval) << " FPS\n";
		ss << shipsystem << " mShip Update\n" << shipdraw << " mShip Draw\n";
		ss << asteroids << " mAsteroid Update\n" << asteroiddraw << " mAsteroid Draw\n";
		ss << particles << " mParticle Update\n" << particledraw << " mParticle Draw\n";
		ss << boundarydraw << " mBoundary Draw";

		graphics.DrawString(0, RESHEIGHT - 200, ss.str().c_str());
#endif

#ifdef _DEBUG
		_CrtMemState state;
		_CrtMemCheckpoint(&state);
		std::stringstream states(std::stringstream::in | std::stringstream::out);
		
		states << "ICounts: " << state.lCounts[_CLIENT_BLOCK] << "\nISizes: " << state.lSizes[_CLIENT_BLOCK] << "\nIHighWaterCount: " << state.lHighWaterCount;
		graphics.SetColor(WHITE);
		graphics.DrawString(0, 200, states.str().c_str());
#endif
	}
}

bool Game::Update(float dt)
{
	if (mode == Start || mode == Over)
	{
		if (Core::Input::IsPressed('1'))
		{
			mode = Mode1;
			lives = 5;
			score = 0;
			Ssystem.refresh();
			Bsystem.refresh();
			particleSystem.Refresh();
			setUpSpaceship();
			wall = Walls(RESWIDTH, RESHEIGHT);
		}
		else if (Core::Input::IsPressed('2'))
		{
			mode = Mode2;
			lives = 5;
			score = 0;
			Ssystem.refresh();
			Bsystem.refresh();
			particleSystem.Refresh();
			setUpSpaceship();
			wall = Walls(RESWIDTH, RESHEIGHT);
		}
		else if (Core::Input::IsPressed('3'))
		{
			mode = Mode3;
			lives = 5;
			score = 0;
			Ssystem.refresh();
			Bsystem.refresh();
			particleSystem.Refresh();
			setUpSpaceship();
			wall = Walls(RESWIDTH, RESHEIGHT);
		}
		else if (Core::Input::IsPressed('4'))
		{
			mode = Mode4;
			lives = 5;
			score = 0;
			Ssystem.refresh();
			Bsystem.refresh();
			particleSystem.Refresh();
			setUpSpaceship();
			wall = Walls(RESWIDTH, RESHEIGHT);
		}
	}
	else
	{
#ifdef PROFILING
		profileClock.Start();
#endif
		bool players = Shipupdates(dt);
		players;
		if (spawnclock.fromStart() > cooldown && players)
		{
			setUpEnemy();
			spawnclock.Start();
		}
		else if (spawnclock.fromStart() > cooldown)
		{
			setUpSpaceship();
			lives--;
			if (lives == 0)
			{
				mode = Over;
				running = false;
				return false;
			}
			spawnclock.Start();
		}

#ifdef PROFILING
		shipsystem = profileClock.Stop() * 1000;
		profile.addEntry("Ship system", shipsystem);


		profileClock.Start();
#endif

		firstAsteroid.move(rate * dt);

		for (int i = 0; i < ASTEROIDCHAINSIZE; i++)
		{
			chain.setRotateAsteroid(i, (angleRate + (changeRate * i)) * dt);
		}

		chain.update();

#ifdef PROFILING
		asteroids = profileClock.Stop() * 1000;
		profile.addEntry("Asteroids", asteroids);

		profileClock.Start();
#endif

		particleSystem.Update(dt);
		Bsystem.update(dt);

#ifdef PROFILING
		particles = profileClock.Stop() * 1000;
		profile.addEntry("Particles and Bullets", particles);
#endif
		running = true;
	}

	if (Core::Input::IsPressed(VK_ESCAPE))
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool Game::Shipupdates(float& dt)
{
	if (mode == Mode1)
	{
		return Ssystem.update(dt, true, particleSystem, Bsystem, score);
	}
	else if (mode == Mode2)
	{
		return Ssystem.update(dt, false, particleSystem, Bsystem, score);
	}

	else if (mode == Mode3)
	{
		return Ssystem.update(dt, true, particleSystem, Bsystem, wall, score);
	}
	else
	{
		return Ssystem.update(dt, false, particleSystem, Bsystem, wall, score);
	}
}

Game::Game()
{
	LOG(Info, "Initializing Game...");
	setUpChain();
	Core::RegisterDrawFn(Draw);
	Core::RegisterUpdateFn(Update);
	clock.Start();
	spawnclock.Start();
	mode = Start;
	LOG(Info, "Finished Initializing Game...");
}

void Game::setUpChain()
{
	ChainableAsteroid asteroids[] =
	{
		ChainableAsteroid(ASTEROIDDIAMETER, Engine::Vector2(offset, 0)),
		ChainableAsteroid(ASTEROIDDIAMETER, Engine::Vector2(offset * 2, 0)),
		ChainableAsteroid(ASTEROIDDIAMETER, Engine::Vector2(offset * 3, 0)),
		ChainableAsteroid(ASTEROIDDIAMETER, Engine::Vector2(offset * 4, 0)),
		ChainableAsteroid(ASTEROIDDIAMETER, Engine::Vector2(offset * 5, 0))
	};

	int size = sizeof(asteroids) / sizeof(*asteroids);

	for (int i = 0; i < size; i++)
	{
		chain.setAsteroid(i, asteroids[i]);
		chain.setScaleAsteroid(i, (float)i * (float)0.5);
	}

	chain.setFirstParentAsteroid(&firstAsteroid);
}

void Game::setUpSpaceship()
{
	PlayerTurret turret(10, 10, (float)0.1, 1000, (float)0.1);
	
#ifdef ARROWCONTROL
	int keyconfig[5] =
	{
		VK_UP,
		VK_DOWN,
		VK_LEFT,
		VK_RIGHT,
		VK_LBUTTON
	};
#else

	int keyconfig[5] =
	{
		VK_W,
		VK_S,
		VK_A,
		VK_D,
		VK_LBUTTON
	};
#endif

	if (
		Ssystem.addShip(new PlayerShip(25, Vector2(RESWIDTH / 2, RESHEIGHT / 2), 1000, (float)3.14, 1, RESWIDTH, RESHEIGHT, turret, keyconfig)))
	{
		particleSystem.AddParticle(new MagicAbsorb(Vector2(RESWIDTH / 2, RESHEIGHT / 2), -50, 50, 1, 100, 5));
	}
}

void Game::setUpEnemy()
{
	EnemyTurret turret(10, 10, (float)0.2, 1000, (float)0.5);
	float randa = rand.RandomRangedFloat(0, (float)RESWIDTH);
	float randb = rand.RandomRangedFloat(0, (float)RESHEIGHT);
	if (Ssystem.addShip(new EnemyShip(25, Vector2(randa, randb), 100, 1, RESWIDTH, RESHEIGHT, turret, Ssystem.assignTarget())))
	{
		particleSystem.AddParticle(new MagicAbsorb(Vector2(randa, randb), -50, 50, 1, 100, 5));
	}
}