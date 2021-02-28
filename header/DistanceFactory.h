#ifndef DISTANCE_FACTORY_H
#define DISTANCE_FACTORY_H

#include "Distance.h"
#include "DistanzaEuclidea.h"
#include "DistanzaSimilaritaCoseno.h"
using namespace std;

class DistanceFactory { //DESIGN PATTERN FACTORY
	public:
	static Distance* Build(const string& distance) {
		if(distance == "-de") return new DistanzaEuclidea();
		else if(distance == "-dsc") return new DistanzaSimilaritaCoseno();
		else return NULL;
	}
};

#endif
