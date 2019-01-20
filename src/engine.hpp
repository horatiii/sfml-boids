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
		double vLimit; 
		void update();
		Engine(unsigned int boidQuantity); 

	private:
		/*calculates vector into center of the mass of neighbouring boids*/
		Position cohesion(Boid &b, std::vector<Boid*> neighbours);

		/*calculates vector that preserves boid from colliding neighbouring boids*/
		Position separation(Boid& b, std::vector<Boid*> neighbours);

		/*calculates vector that aligns flock movement*/
		Position alignment(Boid &b, std::vector<Boid*> neighbours); 

		/*checks whether boid go out of boundaries and if so,  improves its position*/
		void examineBoundaries(Boid &b); 
		std::vector<Boid*> getNeighbours(Boid &b); 
}; 


Engine::Engine(unsigned int boidQuantity): viewDist(VIEW_DIST),vLimit(VLIM)
{
	for(unsigned int bq=0;bq<boidQuantity;++bq)
	{
		Position p({randomFlat(0.,SCREEN_WIDTH),randomFlat(0.,SCREEN_WIDTH)});
		Boid b(p);
		b.color.r=(unsigned char)randomFlat(0,255);
		b.color.g=(unsigned char)randomFlat(0,255);
		b.color.b=(unsigned char)randomFlat(0,255);
		b.velocity[0] = randomFlat(0,1);
		b.velocity[1] = randomFlat(0,1);
		boids.push_back(b);
	}

}

void Engine::update()
{
	for (Boid& b: boids)
	{
		std::vector<Boid*> neighbours = getNeighbours(b); 
		Position goal({0.,0.}); 
		goal = goal + (0.15 * cohesion(b,neighbours));
		goal = goal + (0.5509 * separation(b, neighbours)); 
		goal = goal + (0.58 * alignment(b, neighbours));

		b.velocity = b.velocity + (0.005 * goal);
		b.limitVelocity(vLimit); 

	}
	for (Boid &b: boids)
	{
		b.position = b.position + b.velocity;
		examineBoundaries(b); 
	}
} 

std::vector<Boid*> Engine::getNeighbours(Boid &b)
{
	std::vector<Boid*> neighbours;
	
	for(Boid &neighbour:boids)
		if(&b!=&neighbour)
		{
			if((b.position-neighbour.position).length()<viewDist)
			{
				neighbours.push_back(&neighbour);
			}
		}

	return std::move(neighbours);
}

Position Engine::alignment(Boid &b, std::vector<Boid*> neighbours)//course and velocity is updated
{
	Position aux({0.,0.});
	for(const Boid* neighbour: neighbours)
	{
		aux = aux + neighbour->velocity - b.velocity; 
	} 

	if(neighbours.size()>0)
	{
		aux = aux * (1./(double)neighbours.size());
	}

	aux.normalize();
	return Position(aux);
}



Position Engine::cohesion(Boid &b, std::vector<Boid*> neighbours)
{
	Position aux({0.,0.});

	for(Boid* neighbour:neighbours)
	{ 
		aux = aux + neighbour->position;
	}

	if(neighbours.size()>0)
	{
		aux = aux * (1./(double)neighbours.size()); 
		aux = aux - b.position; 
	}

	 return Position(aux);

}

Position Engine::separation(Boid& b, std::vector<Boid*> neighbours)
{ 
	Position aux({0.,0.,});
	std::vector<Boid*> sep_neighbours;

	for(Boid *neighbour: neighbours)
	{
		if(&b!=neighbour)
		{
			if((b.position-neighbour->position).length()<SEPARATION_DIST)
			{
				sep_neighbours.push_back(neighbour); 
			} 
		}
	}


	for(Boid *neighbour: sep_neighbours)
	{
		aux = aux + b.position - neighbour->position;
	}
	

	if(sep_neighbours.size()>0)
	{
		aux = aux * (1./(double)sep_neighbours.size());
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
