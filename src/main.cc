#include <iostream>

#include "../include/document.h"

int main(int argc, char* argv[]) {

  Term t1("Analytics");
  //t1.addRepetitions(1);
  Term t2("Data");  
  t2.addRepetitions(114);
  Term t3("Cloud");  
  t3.addRepetitions(7);
  Term t4("Smart");  
  t4.addRepetitions(9);
  Term t5("Insight");
  t5.addRepetitions(18);

  Document d1(std::vector<Term>({t1, t2, t3, t4, t5}));

  std::cout << "D1 > " << d1 << "\n";
  d1.removeTerm(Term("Analytics"));
  std::cout << "D1 > " << d1 << "\n";
  std::cout << "D1 > " << d1 << "\n";

  return 0;
}

