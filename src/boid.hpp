#ifndef BOID_HPP
#define BOID_HPP

#include <vector>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Euclidean.cpp"
#include "config.hpp" 

typedef Euclidean<2> Position;

/*represents single boid*/
class Boid
{
	public:
		sf::CircleShape cs;
		Position position;
		Position velocity;
		Boid(Position p):position(p), cs(THICKNESS) {}
		sf::Color color;
		Boid(): cs(THICKNESS) {};
		/*limits velocity with respect to vlim*/
		void limitVelocity(double vlim);
};

void Boid::limitVelocity(double vlim)
{
	if(velocity.length()>vlim)
	{
		velocity = (velocity*(1./velocity.length())) * vlim; 
	}
}

/*auxiliary function to calculate random value on given range*/
double randomFlat(double left,double right)
{
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_real_distribution<double> uni(left,right); // guaranteed unbiased

	return uni(rng);
}

#endif
