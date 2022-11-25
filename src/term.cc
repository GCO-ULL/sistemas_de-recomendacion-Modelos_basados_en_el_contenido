#include "../include/term.h"

// Constructor
Term::Term(std::string text) {
  text_ = text;
  repetitions_ = 1;
}

// Destructor
Term::~Term() {}

// Getters
std::string
Term::getText() {
  return text_;
}

unsigned
Term::getRepetitions() {
  return repetitions_;
}

// Setters
void
Term::setText(std::string text) {
  text_ = text;
}

// Incrementa el numero de repeticiones
void
Term::addRepetitions(unsigned reps) {
  repetitions_ += reps;
}

// Decrementa el número de repeticiones
void
Term::deleteRepetitions(unsigned reps) {
  if (repetitions_ <= reps) {
    throw "Wrong number of repetitions to delete";
  } else {
    repetitions_ -= reps;
  }
}

// Cálculo del Term Frequenty
double
Term::getTF() {
  return 1.0 + log10(repetitions_);
}

// Método de escritura
void
Term::write(std::ostream& os) {
  os << text_ << "(" << repetitions_ << ")";
}

// Metodo de lectura
void
Term::read(std::istream& is) {
  is >> text_;
  repetitions_ = 1;
}
// Sobrecarga del operador "=="
bool
Term::operator==(const Term& term) const {
  return text_ == term.text_;
}

// Sobrecarga del operador de escritura
std::ostream& operator<<(std::ostream& os, Term& term) {
  term.write(os);
  return os;
}

// Sobrecarga del operador de lectura
std::istream& operator>>(std::istream& is, Term& term) {
  term.read(is);
  return is;
}