#include "../include/term.h"

// Constructor
Term::Term(std::string text, unsigned repetitions) {
  text_ = text;
  repetitions_ = repetitions;
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

void
Term::setRepetitions(unsigned repetitions) {
  repetitions_ = repetitions;
}

// Incrementa el numero de repeticiones
void
Term::addRepetitions(unsigned reps) {
  repetitions_ += reps;
}

// Decrementa el número de repeticiones
void
Term::deleteRepetitions(unsigned reps) {
  if (repetitions_ < reps) {
    throw "Wrong number of repetitions to delete";
  } else {
    repetitions_ -= reps;
  }
}

// Cálculo del Term Frequenty
double
Term::getTF() {
  if (repetitions_== 0) {
    return 0.0;
  } else {
    return 1.0 + log10(repetitions_);
  }
}
