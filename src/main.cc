#include <iostream>

#include "../include/term.h"

int main(int argc, char* argv[]) {

  unsigned reps = 0;
  std::cin >> reps;

  Term t1("Analytics", reps);
  std::cout << "t1 TF = " << t1.getTF() << "\n";
  return 0;
}