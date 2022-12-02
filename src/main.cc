#include <iostream>
#include <fstream>
#include "../include/json.h"
#include "../include/document.h"

using json = nlohmann::json;

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

  json lexemeData = json::parse(inputLexeme);

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

  Term t1("Analytics");
  t1.addRepetitions(20);
  Term t2("Data");  
  t2.addRepetitions(23);
  //Term t3("Cloud");  
  //t3.addRepetitions(7);
  Term t4("Smart");  
  t4.addRepetitions(1);
  Term t5("Insight");
  t5.addRepetitions(1);

  Document d1(std::vector<Term>({t1, t2, t4, t5}));

  std::cout << d1 << "\n";
  std::cout << "VECTOR SIZE == " << d1.getLength() << "\n";

  inputDocuments.close();
  inputStopWords.close();
  inputLexeme.close();

  return 0;
}

