/**
 * Filename: CaloLinks.cc
 *
 * Description:
 *
 * Author: D. Austin Belknap, UW-Madison
 */

#include "../include/CaloLinks.h"


CaloLinks::CaloLinks(unsigned int Event, unsigned int Lumi, unsigned int Run) {
  event = Event;
  lumi = Lumi;
  run = Run;
}


CrateLinks&
CaloLinks::get_crate(unsigned int crate) {
  if (crate > 17) {
    throw std::invalid_argument("Invalid crate number.");
  }
  return RCTlinks[crate];
}


void
CaloLinks::write_to_file(std::ofstream outfile) {
  outfile << "run: " << run << " lumi: " << lumi << " event: " << event << std::endl;

  for (int i = 0; i < 18; ++i) {
    RCTlinks[i].populate_link_tables();

    std::vector<uint8_t> link1 = RCTlinks[i].link_values(1);
    std::vector<uint8_t> link2 = RCTlinks[i].link_values(2);

    // Print the contents of each link into the text file
    outfile << std::setw(2) << std::uppercase << std::setfill('0');
    outfile << "Crate " << std::setw(2) << i << " Link 0 ";

    for (int j = 0; j < 24; ++j) {
        outfile << " " << std::setw(2) << std::hex << int(link1.at(j)) << std::dec;
    }

    outfile << std::endl;
    outfile << "Crate " << std::setw(2) << i << " Link 1 ";

    for (int j = 0; j < 24; ++j) {
        outfile << " " << std::setw(2) << std::hex << int(link2.at(j)) << std::dec;
    }
    outfile << std::endl;
  }
}
