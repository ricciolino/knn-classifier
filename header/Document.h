#ifndef DOCUMENT_H
#define DOCUMENT_H

#include<map>
#include<fstream>
#include<string>
#include<iostream>
using namespace std;

class Document {
	
	private:
	
	map<string,int> words; // BUG-OF-WORDS
	string document_class; // CLASSE DEL DOCUMENTO ( "" SE SCONOSCIUTA )
	
	void extrapolate(const size_t pos, const string& word); // USATO NEL COSTRUTTORE PER GESTIRE ESPRESSIONI TIPO: l'arbitro
															// l'arbitro: parola da considerare -> arbitro
	public:
	
	//COSTRUTTORI
	Document():document_class(""){}
	Document(const string& file_name);
	
	//GETTERS
	inline string GetClass() const { return document_class; }
	inline map<string,int>::const_iterator begin() const { return words.begin(); }
	inline map<string,int>::const_iterator end() const { return words.end(); }
	map<string,int>::const_iterator find(const string& word) const;
	
	//SETTERS
	inline void SetClass(const string& _document_class) { document_class=_document_class; }
	
	//STAMPA
	void Print() const;
	
	//OPERATOR (NECESSARIO PER multiset<document>)
	bool operator<(const Document& d) const { return this->GetClass()<d.GetClass(); }
};

#endif
