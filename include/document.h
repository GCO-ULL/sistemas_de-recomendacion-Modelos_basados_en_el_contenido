#pragma once

#include <iostream>
#include <vector>

#include "../include/term.h"

class Document {
  public:
    // Constructor && Destructor
    Document(std::vector<Term> = {});
    ~Document();

    // Getters
    std::vector<Term> getTerms();

    // vectorters
    void setTerms(std::vector<Term>);

    // Operaciones
    int findTerm(Term);
    void addTerm(Term);
    bool removeTerm(Term);
  
    // E/S
    void write(std::ostream& = std::cout);
    void read(std::istream& = std::cin);

    // Otro
    double getLength(); // Implementar!!

  private:
    std::vector<Term> terms_;
};

// Operadores sobrecargados de E/S
std::ostream& operator<<(std::ostream&, Document&);
//std::istream& operator>>(std::istream&, Document&);