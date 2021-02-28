#include "./header/Document.h"

//EXTRAPOLATE
void Document::extrapolate(const size_t pos, const string& word) {
	if( pos == 0 ) {
		string substr1 = word.substr( pos + 1 );
		words[substr1]++;
	}
	else if( pos == word.size() - 1 ) {
		string substr1 = word.substr( 0 , pos );
		words[substr1]++;
	}
	else {
		string substr1 = word.substr( 0 , pos );
		string substr2 = word.substr( pos + 1 );
		words[substr1]++;
		words[substr2]++;
	}
}

//COSTRUTTORE
Document::Document(const string& file_name) {
	ifstream is(file_name);
	if(!is.good()) cerr << "errore apertura file" << endl;
	else {
		//SI CONTROLLA CHE IL DOCUMENTO DA CREARE NON SIA UN DOCUMENTO VUOTO (IN TAL CASO (is >> document_class) RITORNERÀ false)
		//E VIENE SETTATO IL SUO DATO MEMBRO document_class = "" (CLASSE DI DOCUMENTO SCONOSCIUTA)
		//ASSUMENDO CHE OGNI DOCUMENTO DEVE ESSERE UN FILE DI TESTO CON LA PRIMA RIGA DI UNA SOLA PAROLA CHE STABILISCE LA SUA
		//CLASSE DI APPARTENENZA, SI CONTROLLA SE QUESTA È == "unknow_class" (IN TAL CASO IL DOCUMENTO È DI CLASSE SCONOSCIUTA)
		//E VIENE COSÌ SETTATO IL SUO DATO MEMBRO document_class = ""
		if( !(is >> document_class) || (document_class == "unknow_class") )
			document_class = "";
		
		//SI CREA BUG-OF-WORDS DEL DOCUMENTO
		string _word;
		while(is>>_word) {
			// SE WORD È UNO DEI SEGUENTI SIMBOLI ALLORA NON L'AGGIUNGO AL BUG-OF-WORDS
			if( _word != "\'" &&
				_word != "!" &&
				_word != "?" &&
				_word != "-" &&
				_word != "." &&
				_word != ":" &&
				_word != "," &&
				_word != ";" ) {
					// SE IN WORD È PRESENTE UN OCCORRENZA DEI SEGUENTI SIMBOLI SPEZZO LA STRINGA E SEPARO LE PAROLE 
					if( _word.find('\'') != string::npos ) {
						size_t _pos = _word.find('\'');
						extrapolate(_pos,_word);
					}
					else if( _word.find('!') != string::npos ) {
						size_t _pos = _word.find('!');
						extrapolate(_pos,_word);
					}
					else if( _word.find('?') != string::npos ) {
						size_t _pos = _word.find('?');
						extrapolate(_pos,_word);
					}
					else if( _word.find('-') != string::npos ) {
						size_t _pos = _word.find('-');
						extrapolate(_pos,_word);
					}
					else if( _word.find('.') != string::npos ) {
						size_t _pos = _word.find('.');
						extrapolate(_pos,_word);
					}
					else if( _word.find(':') != string::npos ) {
						size_t _pos = _word.find(':');
						extrapolate(_pos,_word);
					}
					else if( _word.find(',') != string::npos ) {
						size_t _pos = _word.find(',');
						extrapolate(_pos,_word);
					}
					else if( _word.find(';') != string::npos ) {
						size_t _pos = _word.find(';');
						extrapolate(_pos,_word);
					}
					else
						words[_word]++;	//equivalente a fare: words.insert(make_pair(_word, 0))->second++;
			}
		}
	}
	is.close();
}

//STAMPA
void Document::Print() const {
	cout << document_class << endl;
	map<string,int>::const_iterator iter = words.begin();
	for( ; iter != words.end() ; ++iter)
		cout << iter->first << " -> " << iter->second << endl;
}

//GETTER
map<string,int>::const_iterator Document::find(const string& word) const {
	if( words.find(word) != words.end() )
		return words.find(word);
	else
		return words.end();
}
