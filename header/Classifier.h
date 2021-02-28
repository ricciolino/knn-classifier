#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include "Document.h"
#include<string>
using namespace std;

class Classifier{
	
	protected:
	
	bool good; //controlla se ho istanziato un classificatore in maniera corretta ( trs != vuoto )
	
	public:
	
	inline bool isGood() const { return ( good == true ); }
	
	virtual string Classify(Document& doc,const string& _distance) const = 0; //METODO ASTRATTO CHE ClassifierKNN DEVE IMPLEMENTARE
	
	~Classifier(){}
};

#endif
