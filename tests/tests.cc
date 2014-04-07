#include <iostream>
#include <fstream>

#include "CaloLinks.h"

int main() {
  std::ifstream infile("./data/two_events.txt");
  std::ofstream outfile("test.txt");

  CaloLinks links;

  // read two events from the input file
  for (int i = 0; i < 2; ++i) {
    // reads a single event from the file
    links.read_from_file(infile);

    // write that event to an output file
    links.write_to_file(outfile);
  }

  infile.close();
  outfile.close();
}
