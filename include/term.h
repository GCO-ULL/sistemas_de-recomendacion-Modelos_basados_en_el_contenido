#pragma once

#include <iostream>
#include <tgmath.h>

class Term {
  public:
    // Constructor && Destructor
    Term(std::string, unsigned = 0);
    ~Term();

    // Getters
    std::string getText();
    unsigned getRepetitions();

    // Setters
    void setText(std::string);
    void setRepetitions(unsigned);

    // Operaciones
    void addRepetitions(unsigned = 1);
    void deleteRepetitions(unsigned = 1);

    // Calculo del Term frequenty
    double getTF();

  private:
    std::string text_;
    unsigned repetitions_;  
};