#include <iostream>
#include <fstream>
#include <iomanip>
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

// Impresión de datos de un documento
void
printDocumentData(Document doc, std::vector<Document> vDocs, std::ostream& os = std::cout) {
  os << "+----------------------------------------------------------------------+\n";
  // os << "| Indice" << "    \t" << "| Terminos" << "\t\t\t" << "| TF" << "\t\t" << "| IDF" << "\t\t" << "| TF-IDF     |" << std::endl;
  os << std::left << std::setw(11)  << " Indice";
  os << std::left << std::setw(15) << "Terminos";
  os << std::left << std::setw(15) << "Cantidad";
  os << std::left << std::setw(10) << "TF";
  os << std::left << std::setw(10) << "IDF";
  os << std::left << std::setw(10) << "TF-IDF" << std::endl;
  os << "+----------------------------------------------------------------------+\n";
  double documentLength = doc.getLength();
  for (int i = 0; i < doc.getTerms().size(); i++) {
    double termTF = doc.getTerms()[i].getTF();
      // os << "| [" << i << "]" << "\t\t" << "| " << doc.getTerms()[i] << "\t\t\t\t" << "| " << termTF << "\t" << "| " << getIDF(doc.getTerms()[i], vDocs) << "\t" << "| " << termTF / documentLength <<"\n";
      os << ' ' << std::left << std::setw(10) << i;
      os << std::left << std::setw(15) << doc.getTerms()[i].getText();
      os << std::left << std::setw(15) << doc.getTerms()[i].getRepetitions();
      os << std::left << std::setw(10) << termTF;
      os << std::left << std::setw(10) << getIDF(doc.getTerms()[i], vDocs);
      os << std::left << std::setw(10) << termTF / documentLength;
      os << '\n';
  }
}

// Impresión de similaridades de documentos
void
printSimilarities(std::vector<Document> vector, std::ostream& os = std::cout) {
  os << "SIMILARITIES:\n\n";
  for(unsigned i = 0; i < vector.size(); i++) {
    for (unsigned j = 0; j < vector.size(); j++) {
      if (i != j) { 
        os << "cos(" << i + 1 << "," << j + 1 << ") = " << vector[i].cosineSimilarity(vector[j]) << "\n";
      }
    }
  }
}

int main(int argc, char* argv[]) {
    
  // Comprobamos que se haya ejecutado de la forma correcta
  if (!argv[1]) {
    std::cout << "Modo de empleo: ";
    std::cout << "./main [documents.txt] [stop_words.txt] [lexeme.json] [output.txt]\n" ;
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

  // Lectura de documentos
  while (!inputDocuments.eof()) {
    Document doc;
    inputDocuments >> doc;
    doc.removeStopWords(stopWords);
    doc.lexematize(lexemeData);
    vDocs.push_back(doc);
  }

  // Escritura
  if (argc >= 5) {
    std::ofstream output(argv[4]);
    if (output.fail()) {
      std::cout << "No se pudo abrir el archivo de escritura, ";
      std::cout << "comprueba si se ingresó un nombre correcto\n";
      inputDocuments.close();
      inputStopWords.close();
      inputLexeme.close();
      return 1;
    }
    for (unsigned i = 0; i < vDocs.size(); i++) {
      output << "DOCUMENTO " << i + 1 <<":\n\n";
      printDocumentData(vDocs[i], vDocs, output);
      output << "\n";
    }
    printSimilarities(vDocs, output);
    output.close();
  } else {
    for (unsigned i = 0; i < vDocs.size(); i++) {
      std::cout << "DOCUMENTO " << i + 1 <<":\n\n";
      printDocumentData(vDocs[i], vDocs);
      std::cout << "\n";
    }
    printSimilarities(vDocs);
  }

  // Cierre de ficheros
  inputDocuments.close();
  inputStopWords.close();
  inputLexeme.close();

  return 0;
}

