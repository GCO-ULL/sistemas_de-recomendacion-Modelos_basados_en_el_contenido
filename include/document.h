#pragma once

#include <iostream>
#include <vector>
#include <tgmath.h>

#include "../include/term.h"
#include "../include/json.h"

using json = nlohmann::json;

class Document {
  public:
    // Constructor && Destructor
    Document(std::vector<Term> = {});
    ~Document();

    // Getters
    std::vector<Term> getTerms();

    // Setters
    void setTerms(std::vector<Term>);

    // Operaciones
    int findTerm(Term);
    void addTerm(Term);
    bool removeTerm(Term);
    bool removeTotalTerm(Term);

    // Operaciones de edición
    void removeStopWords(std::vector<std::string>);
    void lexematize(json);
  
    // E/S
    void write(std::ostream& = std::cout);
    void read(std::istream& = std::cin);

    // Otro
    double getLength();
    unsigned countWords();
    double cosineSimilarity(Document); // Implementar!!!

  private:
    std::vector<Term> terms_;
};

// Operadores sobrecargados de E/S
std::ostream& operator<<(std::ostream&, Document&);
std::istream& operator>>(std::istream&, Document&);

std::vector<std::string> split(std::string, char);
void removeChar(std::string&, char);
void lowercase(std::string&);