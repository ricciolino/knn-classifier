#ifndef DISTANCE_H
#define DISTANCE_H

#include<cmath> //per sqrt()
#include "Document.h"
using namespace std;

class Distance { //classe pura astratta
	
	public:
	
	virtual float GetDistance(const Document& d1,const Document& d2) const = 0;
	
	virtual ~Distance(){}
};

#endif
