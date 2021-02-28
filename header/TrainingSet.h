#ifndef TRAINING_SET_H
#define TRAINING_SET_H

#include<set>
#include<map>
using namespace std;

class TrainingSet {
	
	private:
	multiset<Document> documents;
	map<string,int> classes;
	
	public:
	
	//GETTERS
	inline int GetSize() const { return documents.size(); }//PER CONTROLLARE CHE I CLASSIFICATORI NON SI APPOGIANO A TRS VUOTI
	inline multiset<Document>::const_iterator begin() const { return documents.begin(); }
	inline multiset<Document>::const_iterator end() const { return documents.end(); }
	
	//AGGIUNTA DOCUMENTI
	void Add(const Document& doc) {
		if( doc.GetClass() != "" ) {
			documents.insert(doc);
			classes[doc.GetClass()]++;
		}
	}
	
	//STAMPA LE CLASSI DI DOCUMENTO CHE 'CONOSCE' IL TRAINING SET
	void Print() const {
		map<string,int>::const_iterator iter = classes.begin();
		cout << "\nIL TRS CONOSCE LE SEGUENTI CLASSI DI DOCUMENTO:\n" << endl;
		for( ; iter != classes.end() ; ++iter )
			cout << iter->first << " -> " << iter->second << endl;
	}
};

#endif
