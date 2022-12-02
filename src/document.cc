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
void read(std::istream& is) {
  // Falta implementar
}


// Operador de escritura sobrecargado
std::ostream& operator<<(std::ostream& os, Document& doc) {
  doc.write(os);
  return os;
}

/*
// Operador de lectura sobrecargado
std::istream& operator>>(std::istream& is, Document& doc) {
  doc.read(is);
  return is;
}
*/