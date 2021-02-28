#ifndef DISTANZA_SIMILARITA_COSENO_H
#define DISTANZA_SIMILARITA_COSENO_H

#include "Distance.h"
using namespace std;

class DistanzaSimilaritaCoseno : public Distance {
	
	public:
	
	DistanzaSimilaritaCoseno(){}
	
	virtual float GetDistance(const Document& d1,const Document& d2) const;
	
	virtual ~DistanzaSimilaritaCoseno(){}
};

#endif
