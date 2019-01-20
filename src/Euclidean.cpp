#ifndef CARTESIAN_HPP_
#define CARTESIAN_HPP_
#include <cmath>
#include <array>
#include <iostream>
#include <iomanip>
#include <vector>
#include <initializer_list>
#include <algorithm>

/*
 *Represents cartesian point.
 */
template<std::size_t N>
class Euclidean{
	public:
		std::array<double,N> a;
		double & operator [](std::size_t position);
		Euclidean operator+(const Euclidean &c);
		Euclidean operator-(const Euclidean &c);
		Euclidean& operator=(const Euclidean &other);
		bool operator==(const Euclidean &other);
		/*
		 * it returns euclidean distance from zero vector. For example, if position components are [1,1], length would equal sqrt(2).
		 */
		double length();
		/*
		 * this makes normalisation for euclidean point.
		 */
		void normalize();
		Euclidean<N>();
		Euclidean<N>(const std::array<double,N> & arr);
		Euclidean<N>(double *l);
		Euclidean(const Euclidean<N>& a)=default;
		Euclidean(std::initializer_list<double> args);
};

	template <std::size_t N>
Euclidean<N>::Euclidean(const std::array<double,N> & arr)
{
	a=arr;
}
	template <std::size_t N>
Euclidean<N>::Euclidean(std::initializer_list<double> args)
{
	unsigned i=0;
	for(double q: args)
	{
		a[i++]=q;
	}
}

	template <std::size_t N>	
std::ostream & operator<<(std::ostream& os, const Euclidean<N> & c)
{  
	for(std::size_t i=0;i<N;++i)
	{
		if(i<N-1)
			os << c.a[i]<< std::setw(14);  
		else
			os << c.a[i];  
	}
	os<<std::endl;

	return os;  
}  

template <std::size_t N>Euclidean<N> operator*(const Euclidean<N> &c, const double d);

template <std::size_t N>Euclidean<N> operator*(const double d, const Euclidean<N> &c);

template <std::size_t N> Euclidean<N>:: Euclidean()
{
	a = {0};
}

template <std::size_t N> void Euclidean<N>::normalize()
{
	double aux = this->length();
	if(aux!=0)
	{
		for(std::size_t i=0;i<a.size();i++)
		{
			a[i]= a[i]*(1./aux);	
		}
	}

}

template <std::size_t N> double Euclidean<N>::length(){
	double aux=0;

	for(std::size_t i=0;i<a.size();i++)
	{
		aux+= a[i]*a[i];	
	}
	return sqrt(aux);
}


template <std::size_t N> double & Euclidean<N>::operator[](std::size_t position)
{
	return a[position];
}

template <std::size_t N> Euclidean<N>:: Euclidean(double l[N] )
{
	for(std::size_t i=0;i<a.size();i++)
	{
		a[i]=l[i];
	}
}
template <std::size_t N> Euclidean<N> Euclidean<N>::operator+(const Euclidean<N> &c)
{
	std::array<double,N> aux;
	std::transform(a.begin(), a.end(), c.a.begin(), aux.begin(), std::plus<double>()); 
	return Euclidean<N>(aux);
}

template <std::size_t N> bool Euclidean<N>::operator==(const Euclidean<N> &other)
{
	return a == other.a;
}

template <std::size_t N> Euclidean<N> Euclidean<N>::operator-(const Euclidean<N> &c)
{
	std::array<double,N> aux;
	std::transform(a.begin(), a.end(), c.a.begin(), aux.begin(), std::minus<double>()); 
	return Euclidean<N>(aux);
}

template <std::size_t N> Euclidean<N>& Euclidean<N>::operator=(const Euclidean<N> & other)
{
	a=other.a;
	return *this;
}

template <std::size_t N>Euclidean<N> operator*(const Euclidean<N> &c, const double d)
{
	Euclidean<N> ret;
	for(std::size_t i=0;i<c.a.size();i++)
	{
		ret[i]=d*c.a[i];
	}
	return Euclidean<N>(ret);
}

template <std::size_t N>Euclidean<N> operator*(const double d, const Euclidean<N> &c)
{
	Euclidean<N> ret;
	for(std::size_t i=0;i<c.a.size();i++)
	{
		ret[i]=d*c.a[i];
	}
	return Euclidean<N>(ret);
}

/*
 * This auxiliary template class enables to calculate average solution for the set of values given with help of append function.
 * */
template <std::size_t N> 
class AverageSolution
{
	public:

		double sum;
		int count;

		AverageSolution<N>() 
		{
			clear();
		}

		/**
		 * This function returns average value from set given by append function.
		 */
		double get()
		{
			return sum/(double)count;
		}

		/**
		 * This function appends value to a sum. It also increases count. Finally one could calculate average solution.
		 */
		void append(double l)
		{
			sum+=l;
			++count;
		}

		/**
		 * This function resets sum and count variables to zero.
		 */
		void clear()
		{
			sum=0;
			count = 0;
		}

};
#endif
