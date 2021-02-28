#include "./header/DistanzaEuclidea.h"
using namespace std;

float DistanzaEuclidea::GetDistance(const Document& d1,const Document& d2) const {
	float refuse = 0; //incrementa gli scarti al quadrato
	int flag = 0; //se rimane == 0  allora d1 e d2 non hanno parole in comune e la distanza non è definita (return -1.0)
	
	// CERCO IN d2 LE OCCORRENZE CHE SONO ANCHE IN d1 E INCREMENTO REFUSE SOMMANDO TUTTI GLI SCARTI 
	// QUADRATICI (se un'occorenza di d2 non è in d1 sommo (n°_occorrenze_parola_di_d2 - 0)^2 )
	for( map<string,int>::const_iterator iter = d2.begin(); iter != d2.end(); ++iter) {
		if( d1.find(iter->first) != d1.end() ) {
			flag++;
			refuse += ( ( (d1.find(iter->first))->second ) - ( iter->second ) ) * 
			          ( ( (d1.find(iter->first))->second ) - ( iter->second ) ) ;
		}
		else
			refuse += ( iter->second ) * ( iter->second ); // + (n°_occorrenze_parola_di_d2 - 0)^2
	}
	
	// ORA ITERO SU d1 ANDANDO A SOMMARE I CONTRIBUTI SOLO DEGLI SCARTI CHE NON HO GIA CONSIDERATO MENTRE ITERAVO SU d2
	// CONTROLLO ANCHE CHE OVVIAMENTE FLAG SIA != 0 SENNO' NON HA SENSO DEFINIRE LA DISTANZA
	if( flag != 0 ) {
		for( map<string,int>::const_iterator iter = d1.begin(); iter != d1.end(); ++iter) {
			if( d2.find(iter->first) == d2.end() ) // se == d2.end(), iter->first è una parola che non c'è in d2
				refuse += ( iter->second ) * ( iter->second ); // // + (n°_occorrenze_parola_di_d2 - 0)^2
		}
	}
	
	if(flag == 0) return -1.0;
	return sqrt(refuse); //se è definita una distanza (almeno una parola in comune) ritorno distanza euclidea
}
