#include <iostream>
#include <fstream>

#include "CaloLinks.h"

int main() {
  std::ifstream infile("./data/example_output.txt");
  std::ofstream outfile("test.txt");

  CaloLinks links;

  for (int i = 0; i < 2; ++i) {
    links.read_from_file(infile);

    links.write_to_file(outfile);
  }

  infile.close();
  outfile.close();
}
