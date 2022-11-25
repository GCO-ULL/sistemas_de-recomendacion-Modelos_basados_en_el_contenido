#pragma once

#include <iostream>
#include <set>

#include "../include/term.h"

class Document {
  public:
    // Constructor && Destructor
    Document(std::set<Term> = {});
    ~Document();

    // Getters
    std::set<Term> getTerms();

    // Setters
    void setTerms(std::set<Term>);

    // Operaciones
    bool checkTerm(Term);
    bool addTerm(Term);
    bool removeTerm(Term);
  
    // Otro
    double getLength(); // Implementar!!

  private:
    std::set<Term> terms_;  
};