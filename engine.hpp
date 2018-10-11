//int array[1024] = {[0 ... 1023] = 5};
#ifndef ENGINE_
#define ENGINE_
#include "boid.hpp"
#include <vector>
#include "config.hpp"
#include "Euclidean.cpp"

class Engine
{
	public:
		std::vector<Boid> boids;
		std::vector<Boid*> neighbours;
		double viewDist;
		double stepDistRate;
		double vLimit; 
		void update();
		Engine(unsigned int boidQuantity); 

		/*these modification tools*/
		/*are safe and do not require exception handling*/
		void insertBoid();
		void deleteBoid();
		void modifySpeedLimit(double difference);
		void modifyViewDist(double difference);
		void collectParams();
		int toggleDescriptor;

	private:
		Position cohesion(Boid &b);
		Position separation(Boid& b);
		Position alignment(Boid &b); 
		void examineBoundaries(Boid &b); 
		void getNeighbours(Boid &b); 
};

void Engine::collectParams()
{
	/*
	 * getdata
	 */
}

void Engine::insertBoid()
{
	Position p({SCREEN_WIDTH/10.,randomFlat(0.,SCREEN_HEIGHT)});
	Boid b(p);
	boids.push_back(b);
}

void Engine::deleteBoid()
{
	boids.pop_back();
}

void Engine::modifySpeedLimit(double difference)
{
	if(vLimit+difference>0.)
		vLimit += difference;
}

void Engine::modifyViewDist(double difference)
{
	if(viewDist+difference>0)
		viewDist+=difference;
}

Engine::Engine(unsigned int boidQuantity): viewDist(VIEW_DIST),vLimit(VLIM)
{
	for(unsigned int bq=0;bq<boidQuantity;++bq)
	{
		Position p({randomFlat(0.,SCREEN_WIDTH/1.),randomFlat(0.,SCREEN_WIDTH/1.)});
		Boid b(p);
		b.color.r=(unsigned char)randomFlat(0,255);
		b.color.g=(unsigned char)randomFlat(0,255);
		b.color.b=(unsigned char)randomFlat(0,255);
		b.velocity[0]=randomFlat(-1,1);
		b.velocity[1]=randomFlat(-1,1);
		boids.push_back(b);
	}
}

void Engine::update()
{
	for (Boid& b: boids)
	{
		neighbours.clear();
		getNeighbours(b); 
		Position goal({0.,0.}); 
		goal = goal + cohesion(b);
		goal = goal + separation(b); 
		goal = goal + alignment(b);
		b.velocity = b.velocity + goal;
		b.limitVelocity(vLimit);
		b.moveToward(b.velocity);
		examineBoundaries(b); 
	}
} 

void Engine::getNeighbours(Boid &b)
{
	for(Boid &neighbour:boids)
		if(&b!=&neighbour)
		{
			if((b.position-neighbour.position).length()<viewDist)
			{
				neighbours.push_back(&neighbour);
			}
		}
}

Position Engine::alignment(Boid &b)
{
	Position aux({0.,0.});
	int neighbourCount = 0;
	for(const Boid* neighbour: neighbours)
	{
		aux = aux + neighbour-> velocity - b.velocity; 
		neighbourCount ++;
	} 

	if(neighbourCount>0)
	{
		aux = aux * (1./neighbourCount);
	}

	aux.normalize();
	return Position(aux);
}

Position Engine::cohesion(Boid &b)
{
	Position aux({0.,0.});
	int neighbourCount=0;

	//if(neighbours.size()>0)
	//{
	//aux=neighbours.at(0)->position;
	////calculating center of mass on cycled space
	//for(int i=1;i<neighbours.size();i++)
	//{
	//Boid *neighbour=neighbours.at(i);
	//double vX = neighbour->position[0] - aux[0];
	//double vY = neighbour->position[1] - aux[1]; 

	//vX=(std::abs(vX)>(SCREEN_WIDTH/2.))?(-1) *(vX/std::abs(vX))*(SCREEN_WIDTH - std::abs(vX)): vX;
	//vY=(std::abs(vY)>(SCREEN_HEIGHT/2.))?(-1)*(vY/std::abs(vY))*(SCREEN_HEIGHT - std::abs(vY)): vY;

	//aux = aux + (1./++neighbourCount)*( Position({vX,vY}));

	//}	

	//}


	for(Boid* neighbour:neighbours)
	{
		double vX = neighbour->position[0] - aux[0];
		double vY = neighbour->position[1] - aux[1]; 
		vX=(std::abs(vX)>(SCREEN_WIDTH/2))?(-1) *(vX/std::abs(vX))*(SCREEN_WIDTH - std::abs(vX)): vX;
		vY=(std::abs(vY)>(SCREEN_HEIGHT/2))?(-1)*(vY/std::abs(vY))*(SCREEN_HEIGHT - std::abs(vY)): vY;

		aux = aux + Position({vX,vY}); 
		neighbourCount++;
	}


	if(neighbours.size()>0) aux.normalize(); 

	return Position(aux);
}

Position Engine::separation(Boid& b)
{ 
	Position aux({0.,0.,});

	double avg=0.;
	for(Boid *neighbour: neighbours)
		avg+=(b.position - neighbour->position).length();

	if(neighbours.size()>0) 
		avg=avg/neighbours.size();

	for(Boid *neighbour: neighbours)
	{
		double vX = b.position[0] - neighbour->position[0] ;
		double vY = b.position[1] - neighbour->position[1]; 
		vX=(std::abs(vX)>(SCREEN_WIDTH/2)) ?(-1)*(avg/vX)*(SCREEN_WIDTH - std::abs(vX)) : vX;
		vY=(std::abs(vY)>(SCREEN_HEIGHT/2))?(-1)*(avg/vY)*(SCREEN_HEIGHT - std::abs(vY)): vY;
		//vX=(std::abs(vX)>(SCREEN_WIDTH/2)) ?(-1)*(vX/std::abs(vX))*(SCREEN_WIDTH - std::abs(vX)) : vX;
		//vY=(std::abs(vY)>(SCREEN_HEIGHT/2))?(-1)*(vY/std::abs(vY))*(SCREEN_HEIGHT - std::abs(vY)): vY;

		aux = aux + Position({vX,vY});
	}

	if(neighbours.size()>0)
	{
		aux.normalize();
	}
	return Position(aux);

}
void Engine::examineBoundaries(Boid& b)
{

	if(b.position[0]<0.)
	{
		b.position[0]=SCREEN_WIDTH+b.position[0];
	}

	if(b.position[1]<0.)
	{
		b.position[1]=SCREEN_HEIGHT+b.position[1];
	}

	b.position[0] = std::fmod(b.position[0],SCREEN_WIDTH);
	b.position[1] = std::fmod(b.position[1],SCREEN_HEIGHT);
}

#endif
