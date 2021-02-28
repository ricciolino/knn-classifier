#ifndef DISTANZA_EUCLIDEA_H
#define DISTANZA_EUCLIDEA_H

#include "Distance.h"
using namespace std;

class DistanzaEuclidea : public Distance {
	
	public:
	
	DistanzaEuclidea(){}
	
	virtual float GetDistance(const Document& d1,const Document& d2) const;
	
	virtual ~DistanzaEuclidea(){}
};

#endif
