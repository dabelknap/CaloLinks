#include <iostream>
#include <fstream>

#include "CaloLinks.h"

int main() {
  std::ifstream infile("./data/single_event.txt");
  std::ofstream outfile("test.txt");

  CaloLinks links;

  links.read_from_file(infile);

  links.write_to_file(outfile);

  infile.close();
  outfile.close();
}
