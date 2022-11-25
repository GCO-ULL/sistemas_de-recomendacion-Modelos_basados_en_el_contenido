#include "../include/document.h"

// Constructor
Document::Document(std::set<Term> terms) {
  terms_ = terms;
}

// Destructor
Document::~Document() {
  terms_.clear();
}

// Getters
std::set<Term>
Document::getTerms() {
  return terms_;
}

// Setters
void
Document::setTerms(std::set<Term> terms) {
  terms_ = terms;
}

// Comprueba si un término pertenece a un documento
bool
Document::checkTerm(Term term) {
  for (Term t: terms_) {
    if (term == t) {
      return true;
    }
  }
  return false;
}

// Añade un término al documento
bool
Document::addTerm(Term term) {
  if (checkTerm(term)) {
    return false;
  } else {
    terms_.insert(term);
    return true;
  }
}

// Elimina un término del documento
bool
Document::removeTerm(Term term) {
  if (checkTerm(term)) {
    terms_.erase(term);
    return true;
  } else {
    return false;
  }
}