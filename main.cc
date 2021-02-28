#include "./header/Document.h"
#include "./header/TrainingSet.h"
#include "./header/ClassifierKNN.h"
#include<vector>
#include<cstdlib>
using namespace std;

bool check_all_right( const string& outcome , const string& doc_name , const string& distance );

int main( int argc , char** argv ) {
	
	if(argc != 4) {
		cerr << "inserire criterio di distanza, numero di doc da classificare e numero di doc del trs, sintassi:" << endl;
		cerr << "./knn 'criterio_distanza' 'numero_doc_da_classificare' 'numero_doc_del_trs'" << endl;
		return 1; 
	}

	// ISTANZIO IL TRAINING-SET AGGIUNGENDO I DOCUMENTI DI CLASSE NOTA
	TrainingSet trs;
	for( int i = 0 ; i < atoi( argv[3] ) ; ++i )
		trs.Add( Document( "./document/trs/trs" + to_string(i+1) + ".txt" ) );
	trs.Print(); cout << endl;
	
	// CREO UN CLASSIFICATORE KNN CHE SI BASA SU TRAINING-SET CREATO
	ClassifierKNN knn(trs);
	
	// PRENDO IN INPUT DOCUMENTI DA CLASSIFICARE
	vector<Document> doc;
	for( int i = 0 ; i < atoi( argv[2] ) ; ++i )
		doc.push_back( Document ( "./document/to_be_classified/doc" + to_string(i+1) + ".txt" ) );
	
	// INVOCO METODO ASTRATTO Classify() SAPENDO CHE:
	// SE MI RITORNA --> "" <-- IL DOCUMENTO È STATO CLASSIFICATO DI CLASSE SCONOSCIUTA (CASO LIMITE)
	// SE MI RITORNA --> "empty_training_set" <-- IL DOCUMENTO NON È STATO CLASSIFICATO (QUINDI È RIMASTO DI CLASSE SCONOSCIUTA)
	//											  POICHÈ IL CLASSIFICATORE CREATO SI BASA SU UN TRAINING-SET NULLO
	// SE MI RITORNA --> "wrong_distance" <-- IL DOCUMENTO NON È STATO CLASSIFICATO (QUINDI È RIMASTO DI CLASSE SCONOSCIUTA)
	//											  POICHÈ IL CRITERIO DI DISTANZA SPECIFICATO NON È CORRETTO
	for( int i = 0 ; i < atoi( argv[2] ) ; ++i ) {
		cout << "\nDISTANZE TRA doc" + to_string(i+1) + " E I k VICINI:" << endl;
		if( check_all_right( knn.Classify( doc[i] , argv[1] ) , "doc" + to_string(i+1) , argv[1] ) == false ) return 1;
	}
	
	cout << endl;
	return 0;
}

bool check_all_right( const string& outcome , const string& doc_name , const string& distance ) {
	if( outcome == "empty_training_set" ) {
		cerr << "impossibile classificare " << doc_name << ", TrainingSet nullo" << endl;
		return false;
	}
	if( outcome == "wrong_distance" ) {
		cerr << "impossibile classificare " << doc_name << ", criterio di distanza '" << distance << "' non definito" << endl;
		cerr << "distanze possibili:" << endl;
		cerr << "-dsc (DistanzaSimilaritaCoseno)" << endl << "-de (DistanzaEuclidea)" << endl;
		return false;
	}
	cout << "--> " << doc_name << " è di classe: " << ( outcome == "" ? "sconosciuta" : outcome ) << endl;
	return true;
}


