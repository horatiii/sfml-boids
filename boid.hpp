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
class Boid
{
	public:
		sf::CircleShape cs;
		Position position;
		Position velocity;
		Boid(Position p):position(p), cs(THICKNESS) {}
		sf::Color color;
		Boid(): cs(THICKNESS) {};
		void limitVelocity(double vlim);
		void moveToward(Position p);
};

void Boid::limitVelocity(double vlim)
{
	if(velocity.length()>vlim)
	{
		velocity = (velocity*(1/velocity.length())) * vlim; 
	}
}

void Boid::moveToward(Position p)
{
	position=position + p;
}

double randomFlat(double left,double right)
{
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_real_distribution<double> uni(left,right); // guaranteed unbiased

	return uni(rng);
}

#endif
