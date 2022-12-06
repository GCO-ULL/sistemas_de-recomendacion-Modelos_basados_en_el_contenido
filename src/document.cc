#include "../include/document.h"

// Constructor
Document::Document(std::vector<Term> terms) {
  terms_ = {};
  for (Term term: terms) {
    addTerm(term);
  }
}

// Destructor
Document::~Document() {
  terms_.clear();
}

// Getters
std::vector<Term>
Document::getTerms() {
  return terms_;
}

// Setters
void
Document::setTerms(std::vector<Term> terms) {
  terms_ = terms;
}

// Comprueba si un término pertenece a un documento
int
Document::findTerm(Term term) {
  for (unsigned i = 0; i < terms_.size(); i++) {
    if (term == terms_[i]) {
      return i;
    }
  }
  return -1;
}

// Añade un término al documento
void
Document::addTerm(Term term) {
  int pos = findTerm(term);
  if (pos == -1) {
    terms_.push_back(term);
  } else {
    terms_[pos].addRepetitions(term.getRepetitions());
  }
}

// Elimina un término del documento
bool
Document::removeTerm(Term term) {
  int pos = findTerm(term);
  if (pos == -1) {
    return false;
  } else {
    if (terms_[pos].getRepetitions() == 1) {
      terms_.erase(terms_.begin() + pos);
    } else {
      terms_[pos].deleteRepetitions();
    }
    return true;
  }
}

// Elimina un término y todas sus repeticiones del documento
bool
Document::removeTotalTerm(Term term) {
  int pos = findTerm(term);
  if (pos == -1) {
    return false;
  } else {
    terms_.erase(terms_.begin() + pos);
    return true;
  }
}

// Eliminación de palabras de parada
void
Document::removeStopWords(std::vector<std::string> vector) {
  for (std::string word: vector) {
    removeTotalTerm(Term(word));
  }
}


// Operación de lexematización
void
Document::lexematize(json data) {
  std::vector<Term> termsCopy = terms_;
  for (Term term: termsCopy) {
    std::string value = data.value(term.getText(), "not found");
    if (value != "not found") {
      addTerm(Term(value, term.getRepetitions()));
      removeTotalTerm(term);
    }
  }
}

// Calcula el tamaño del vector del documento
double
Document::getLength() {
  float vectorSize = 0.0;
  for (Term term: terms_) {
    vectorSize += pow(term.getTF(), 2.0); 
  }
  return sqrt(vectorSize);
}

// Cuenta el número total de términos del documento
unsigned
Document::countWords() {
  unsigned count = 0;
  for (Term term: terms_) {
    count += term.getRepetitions();
  }
  return count;
}

// Calcula el TF-IDF de un término del documento si se encuentra
double
Document::getTFIDF(Term term) {
  int pos = findTerm(term); 
  if (pos != -1) {
    return terms_[pos].getTF() / getLength();
  } else {
    throw "term doesnt exist on the document";
  }
}

double
Document::cosineSimilarity(Document doc) {
  double similarity = 0.0;
  for (Term term: terms_) {
    int pos = doc.findTerm(term);
    if (pos != -1) {
      similarity += getTFIDF(term) * doc.getTFIDF(term);
    }
  }
  return similarity;
}

// Método de escritura
void
Document::write(std::ostream& os) {
  os << "{\n";
  for (unsigned i = 0; i < terms_.size() - 1; i++) {
    os << "  [" << i << "] " << terms_[i] << ",\n";
  }
  os << "  [" << terms_.size() - 1 << "] " << terms_[terms_.size() - 1] << "\n}";
}

// Método de lectura
void
Document::read(std::istream& is) {
  std::string line;
  getline(is, line);

  // Cambiamos todas las palabras a minúsculas
  lowercase(line);

  // Eliminamos los puntos y comas
  removeChar(line, '.');
  removeChar(line, ',');

  // Separamos las palabras por espacios
  std::vector<std::string> lineVector = split(line, ' ');
  removeSpaces(lineVector);

  // Añadimos los términos
  for (std::string el: lineVector) {
    addTerm(Term(el));
  }
}


// Operador de escritura sobrecargado
std::ostream& operator<<(std::ostream& os, Document& doc) {
  doc.write(os);
  return os;
}


// Operador de lectura sobrecargado
std::istream& operator>>(std::istream& is, Document& doc) {
  doc.read(is);
  return is;
}

// Elimina un carácter de un string
void
removeChar(std::string& str, char ch) {
  str.erase(std::remove(str.begin(), str.end(), ch), str.end());
}

// Convierte un string a vector separado por un patrón que se introduce por parámetro
std::vector<std::string>
split(std::string str, char pattern) {  
    int posInit = 0;
    int posFound = 0;
    std::string splitted;
    std::vector<std::string> results;
    
    while(posFound >= 0){
        posFound = str.find(pattern, posInit);
        splitted = str.substr(posInit, posFound - posInit);
      posInit = posFound + 1;
      results.push_back(splitted);
  }

  return results;
}

// Transforma los elementos de un string a minúscula
void lowercase(std::string& str) {
  std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){
    return std::tolower(c); 
  });
}

// Elimina los elementos vacios de un vector
void removeSpaces(std::vector<std::string>& vector) {
  for (int i = 0; i < vector.size(); i++) {
    if (vector[i] == "") {
      vector.erase(vector.begin() + i);
    }
  }
}