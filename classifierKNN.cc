#include "./header/ClassifierKNN.h"
#include "./header/DistanceFactory.h"
using namespace std;

int ClassifierKNN::i_classification = 1; //contatore di quanti documento tento di classificare con il metodo Classify

ClassifierKNN::ClassifierKNN(const TrainingSet& _trs) {
	if(_trs.GetSize() == 0)
		this->good = false;
	else {
		this->good = true;
		trs = _trs;
	}
}

string ClassifierKNN::Classify(Document& doc, const string& _distance) const {
	// controllo correttezza di inizializzazione del classificatore (trs non può essere nullo)
	if( !(this->isGood()) ) return string("empty_training_set");
	
	//costruisco distanza
	Distance* distance = DistanceFactory::Build( _distance );
	if(distance == NULL) return string("wrong_distance");
	
			//cout<<"distanze fra doc" + to_string(ClassifierKNN::i_classification) + " e gli altri doc del trs:"<<endl;// PRINT ONLY
			ClassifierKNN::i_classification++; // tentata nuova classificazione...
			
	//SALVO IN UNA MULTIMAP LE VARIE DISTANZE TRA IL DOCUMENTO DA CLASSIFICARE ED I DOCUMENTI PRESENTI NEL TRAINING_SET
	//ITERO SUL TRAINING_SET ED INVOCO .insert() SULLA MULTIMAP INSERENDO LA COPPIA
	//						'valore distanza' -> 'classe documento'
	//'valore distanza' CHE È RITORNATO DAL METODO VIRTUALE GetDistance()
	multimap<float,string> dist_doc;
	multiset<Document>::const_iterator iter_trs = trs.begin();
	for( ; iter_trs != trs.end(); ++iter_trs ) {
		float dist = distance->GetDistance( *iter_trs , doc );
		if( dist != -1.0 ) // se la distanza non è definita non considero il documento del trs
			dist_doc.insert( make_pair( dist , iter_trs->GetClass() ) );
		  //pair<float,string> _pair ( dist , iter_trs->GetClass() );										// PRINT
		  //cout << "distanza tra doc e documento di " << _pair.second << ": " << _pair.first << endl;		//  ONLY
	}
	
	//SELEZIONO I K DOCUMENTI DEL TRAINING SET PIÙ VICINI AL DOCUMENTO IN INPUT (tra quelli messi in dist_doc al passo precedente)
	//LI METTO IN UNA MULTIMAP DI COPPIA 'classe documento' -> 'valore distanza' PER POI AL PROSSIMO PASSO ITERARCI SOPRA E
	//RIUSCIRE A CREARE UN CONTATORE DELLE DISTANZE CON UGUAL CHIAVE E UNA MEDIA DELLE STESSE DISTANZE
	//COSÌ HO UN CRITERIO PRIMARIO DI SCELTA PER LA CLASSIFICAZIONE: SI SCEGLIE LA CLASSE CON PIÙ RICCORRENZE TRA LE PRIME K
	//CRITERIO SECONDARIO: SE DUE CONTATORI SI EQUIVALGONO SI CLASSIFICA IL DOCUMENTO DI INPUT IN BASE ALLA MINIMA
	//DISTANZA MEDIA CALCOLATA PER OGNI CLASSE DI DOCUMENTO RIENTRATA TRA LE PRIME K															// PRINT ONLY
	const int k = static_cast<int>( sqrt(trs.GetSize()) );													
	const int n_dist = dist_doc.size(); // itero fino al minore tra il numero di distanze effettivamente prese in considerazione
	multimap<string,float> bigger_neighbors;							//in dist_doc e k (caso poco probabile)
	multimap<float,string>::const_iterator iter_k = dist_doc.begin();
	for( int i = 0 ; i < ( k <= n_dist ? k : n_dist ) ; ++i, ++iter_k) {
		bigger_neighbors.insert( make_pair( iter_k->second , iter_k->first ) );
		  pair<string,float> _pair( iter_k->second , iter_k->first );									// PRINT
		  cout << "distanza tra doc e documento di " << _pair.first << ": " << _pair.second << endl;	// ONLY
	}
		
	// ora ad ogni passo incremento greater per contare quanti documenti ci sono di una certa classe tra i primi k ed incremento
	// med con i rispettivi valori di distanza associati, appena esco dal ciclo di equal_range calcolo la media facendo med/greter
	// poi se il greater del passo attuale è > stretto di quello al passo prima aggiorno la classe candidata ad essere 
	// classe del documento da classificare ed associo la rispettiva media, se invece ho un caso di parità di contatori
	// ( greater == old_greater ) vado a controllare la media attuale med con old_med, scelgo la minore, ed aggiorno la classe 
	// candidata ad essere classe del documento da classificare, infine caso limite med == old_med -> classe_doc sconosciuta
	int greater = 0;
	int old_greater = 0;
	float med = 0;
	float old_med = 0;
	multimap<string,float>::const_iterator iter_neighbors = bigger_neighbors.begin();
	for( ; iter_neighbors != bigger_neighbors.end() ; ++iter_neighbors ) { //ciclo esterno sui doc più vicini selezionati
		pair < multimap<string,float>::const_iterator , multimap<string,float>::const_iterator > range;
		range = bigger_neighbors.equal_range( iter_neighbors->first ); //coppia di iteratori a equal_range
		multimap<string,float>::const_iterator i_eq = range.first;
		multimap<string,float>::const_iterator i_eq_prec; //mi serve per quando esco dal for (i_eq sarà == a range.second)
		for( ; i_eq != range.second ; ++i_eq ) {		  //allora con i_eq_prec riesco ad accedere all'ultimo elemento del range
			i_eq_prec = i_eq;
			greater++;
			med += i_eq->second;
		}
		med /= greater;
			
		if( greater > old_greater ) { // criterio di classificazione PRIMARIO: aggiorno la 'potenziale' classificazione del doc
			old_greater = greater;						// se il greater attuale è maggiore di old_greater
			old_med = med;
			doc.SetClass( i_eq_prec->first );
		}
		else if( (greater == old_greater) && (med < old_med) ){ // criterio di classificazione SECONDARIO: aggiorno la 'potenziale'
			old_med = med;										// classificazione del doc se, a parità di contatori, la med attuale
			doc.SetClass( i_eq_prec->first );					// è minore di old_med
		}
		else if(med == old_med)
			doc.SetClass(""); //caso limite -> documento sconosciuto
		
		iter_neighbors = i_eq_prec; // necessario per riprendere il ciclo for esterno sui documenti più vicini
		greater = 0;
		med = 0;
	}
	
	delete distance; // DEALLOCO PUNTATORE A Distanza CHE IN QUESTO SCOPE È SICURAMENTE DIVERSO DA NULL!
	
	return doc.GetClass(); // RITORNO LA CLASSE DEL DOCUMENTO
}
