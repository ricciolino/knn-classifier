#include "./header/DistanzaSimilaritaCoseno.h"
using namespace std;

float DistanzaSimilaritaCoseno::GetDistance(const Document& d1, const Document& d2) const {
	float pscal = 0;
	float d1norm = 0;
	float d2norm = 0;
	int flag = 0; //se rimane == 0  allora d1 e d2 non hanno parole in comune e la distanza non è definita (return -1.0)
	
	//CALCOLO LA NORMA DI d1
	for( map<string,int>::const_iterator iter = d1.begin(); iter != d1.end(); ++iter )
		d1norm += (iter->second) * (iter->second);
	
	//CERCO IN d2 LE OCCORRENZE CHE SONO ANCHE IN d1 (prodotto scalare fa 0 altrimenti)
	//INCREMENTO pscal E CALCOLO LA NORMA DI d2
	for( map<string,int>::const_iterator iter = d2.begin(); iter != d2.end(); ++iter ) {
		if( d1.find(iter->first) != d1.end() ) {
			flag++;
			pscal += ( (d1.find(iter->first))->second ) * ( iter->second );
		}
		d2norm += ( iter->second ) * ( iter->second );
	}
	d1norm = sqrt(d1norm);
	d2norm = sqrt(d2norm);
	//
	//				     < d1 , d2 >		       pscal
	// cos(theta) = --------------------- = -------------------
	//				 || d1 || * || d2 ||	  d1norm * d2norm
	//
	if( flag == 0 ) return -1.0;
	else {
		float cos = pscal / ( d1norm * d2norm );
		return ( 1 - cos );
	}
}
