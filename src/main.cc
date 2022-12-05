#include <iostream>
#include <fstream>
#include "../include/document.h"

// Cuenta el número de términos de todo el corpus de documentos
unsigned
countTerms(std::vector<Document> documents) {
    unsigned count = 0;
  for (Document doc: documents) {
    count += doc.countWords();
  }
  return count;
}

// Calcula el DF de un término en un corpus de documentos
unsigned
getDF(Term term, std::vector<Document> documents) {
  unsigned count = 0;
  for (Document doc: documents) {
    int pos = doc.findTerm(term);
    if (pos != -1) {
      count += doc.getTerms()[pos].getRepetitions();
    }
  }
  return count;
}

// Calcula el IDF de un término en un corpus de documentos
double
getIDF(Term term, std::vector<Document> documents) {
    return log10((double)countTerms(documents) / (double)getDF(term, documents));
}

// Lectura de fichero de stop-words
std::vector<std::string>
readStopWordsFile(std::ifstream& is) {
  std::vector<std::string> vector;
  std::string str;
  while (!is.eof()) {
    getline(is, str);
    vector.push_back(str);
  }
  return vector;
}


/*
Document 1
Indice  Terminos   TF     IDF    TF-IDF
[1]      casa     0.2323  23.44    0.44
[2]      arbol    0.6677  655.33   0.33
[3]      anita    0.2133  34.44    0.11

Document 2

*/

// Impresión de datos de un documento
void
printDocumentData(Document doc, std::vector<Document> vDocs, std::ostream& os = std::cout) {
  os << "Indice" << "\t" << "Terminos" << "\t" << "TF" << "\t" << "IDF" << "\t" << "TF-IDF" << std::endl;
  double documentLength = doc.getLength();
  for (int i = 0; i < doc.getTerms().size(); i++) {
    double termTF = doc.getTerms()[i].getTF();
    os << "[" << i << "]" << "\t" << doc.getTerms()[i] << "\t" << termTF << "\t" << getIDF(doc.getTerms()[i], vDocs) << "\t" << termTF / documentLength << "\n";
  }
}

int main(int argc, char* argv[]) {
    
  // Comprobamos que se haya ejecutado de la forma correcta
  if (!argv[1]) {
    std::cout << "Modo de empleo: ";
    std::cout << "./main [documents.txt] [stop_words.txt] [lexeme.json]\n" ;
    std::cout << "Pruebe './main --help' para más información.\n";   
    return 1;
  }

  // En caso de usar como parámetro "--help"
  std::string help = "--help";
  if(argv[1] == help) {
    std::ifstream help_txt;
    help_txt.open("help.txt");
    if (!help_txt.fail()) {
      while (!help_txt.eof()) {
        std::getline(help_txt, help);
        std::cout << help << "\n";
      }
    }
    help_txt.close();
    return 1;
  }

  // Archivo de lectura de documentos
  std::ifstream inputDocuments;
  inputDocuments.open(argv[1]);

  if (inputDocuments.fail()) {
    std::cout << "No se pudo abrir archivo de lectura de documentos, ";
    std::cout << "comprueba si se ingresó un nombre correcto\n";
    return 1;
  }

  // Archivo de lectura de stop-words
  std::ifstream inputStopWords;
  inputStopWords.open(argv[2]);

  if (inputStopWords.fail()) {
    std::cout << "No se pudo abrir archivo de lectura de palabras de parada, ";
    std::cout << "comprueba si se ingresó un nombre correcto\n";
    inputDocuments.close();
    return 1;
  }

  // Archivo de lectura lexematizacion
  std::ifstream inputLexeme(argv[3]);

  if (inputLexeme.fail()) {
    std::cout << "No se pudo abrir el archivo de lexematización, ";
    std::cout << "comprueba si se ingresó un nombre correcto\n";
    inputDocuments.close();
    inputStopWords.close();
    return 1;
  }

  // Vector de palabras vacías
  std::vector<std::string> stopWords = readStopWordsFile(inputStopWords);

  // JSON de lexematización
  json lexemeData = json::parse(inputLexeme);
  
  // Inicialización del vector de Documentos
  std::vector<Document> vDocs;


  while (!inputDocuments.eof()) {
    Document doc;
    inputDocuments >> doc;
    //std::cout << doc;
    //std::cout << "DOC ANTES >> " << doc << "\n";
    doc.removeStopWords(stopWords);
    //std::cout << doc << "\n";
    //std::cout << "DOC REMOVE STOPWORDS >> " << doc << "\n";
    doc.lexematize(lexemeData);
    //std::cout << "DOC LEXEMATIZE >> " << doc << "\n";
    vDocs.push_back(doc);
  }

  // Impresión de los datos del vector de documentos
  //for (Document doc: vDocs) {
    std::cout << vDocs[1] << "\n";
    //printDocumentData(doc, vDocs);
  //}
  //Document doc =  vDocs[vDocs.size() -1];

  //std::cout << doc << "\n";

  //doc.removeStopWords(readStopWordsFile(inputStopWords));

  //std::cout << doc << "\n";

  // Descripción del menú principal (idea)
  /*
    - Leemos cada documento linea por linea sobrecargando el operador de lectura de Document
    - Los metemos en un vector de documentos vector<Document>
    - Recorremos el vector
    - Para cada documento
      - Para cada termino dentro del documento
        - Mostramos posicion del termino, termino, TF, IDF (usando funcion d arriba), TF-IDF (que es la resta de TF - lengthVector del documento)
    - Luego las similaridades:
      - Función cosineSimilarity(Document de la clase document)
    LISTO!! objecciones: contacten alu0101321219@ull.edu.es (de 2 a 4 no respondo)
  */
/*
  Term t1("was", 21);
  Term t2("Data", 24);  
  Term t3("Cloud", 8);  
  Term t4("Smart", 2);
  Term t5("is", 2);

  Document d1(std::vector<Term>({t1, t2, t3, t4, t5}));

  std::cout << d1 << "\n";
  d1.lexematize(lexemeData);
  std::cout << d1 << "\n";
  //std::cout << "VECTOR SIZE == " << d1.getLength() << "\n";
*/
  inputDocuments.close();
  inputStopWords.close();
  inputLexeme.close();

  return 0;
}

