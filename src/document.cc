#include "../include/document.h"

// Constructor
Document::Document(std::vector<Term> terms) {
  terms_ = terms;
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
    terms_[pos].addRepetitions();
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

// Método de escritura
void
Document::write(std::ostream& os) {
  os << "[ ";
  for (Term term: terms_) {
    os << term << " ";
  }
  os << "]";
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