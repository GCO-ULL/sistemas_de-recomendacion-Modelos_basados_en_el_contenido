#pragma once

#include <iostream>
#include <tgmath.h>

class Term {
  public:
    // Constructor && Destructor
    Term(std::string);
    ~Term();

    // Getters
    std::string getText();
    unsigned getRepetitions();

    // Setters
    void setText(std::string);

    // Operaciones
    void addRepetitions(unsigned = 1);
    void deleteRepetitions(unsigned = 1);

    // Calculo del Term frequenty
    double getTF();

    // Sobrecarga de operadores
    bool operator==(const Term&) const;

    // E/S
      void write(std::ostream& = std::cout);
      void read(std::istream& = std::cin);

  private:
    std::string text_;
    unsigned repetitions_;
};

// Operadores sobrecargados de E/S
std::ostream& operator<<(std::ostream&, Term&);
std::istream& operator>>(std::istream&, Term&);