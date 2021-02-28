#ifndef CLASSIFIER_KNN_H
#define CLASSIFIER_KNN_H

#include "Classifier.h"
#include "TrainingSet.h"
#include "Document.h"
#include<cmath> //k=sqrt(n) in Classify()
using namespace std;

class ClassifierKNN : public Classifier {
	
	private:
	
	TrainingSet trs;
	
	public:
	
	static int i_classification; // lo uso solo per le stampe (conto quanti documenti tento di classificare)
	
	ClassifierKNN(const TrainingSet& _trs);
	
	virtual string Classify(Document& doc,const string& _distance) const; // algoritmo KNN
	
	virtual ~ClassifierKNN(){}
};

#endif
