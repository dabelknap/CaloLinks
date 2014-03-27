/**
 * Filename: CaloLinks.cc
 *
 * Description: Contains methods for acessing the link info for specific crates
 *              as well as the ability to write the link data to a file.
 *
 * Author: D. Austin Belknap, UW-Madison
 */

#include "../include/CaloLinks.h"


/**
 * Assign event ID to identify a particular collection of RCT links
 */
CaloLinks::CaloLinks(unsigned int Event, unsigned int Lumi, unsigned int Run) {
  event = Event;
  lumi = Lumi;
  run = Run;
}


/**
 * Allows you to access the individual crates by reference - no need to use
 * pointers.
 */
CrateLinks&
CaloLinks::get_crate(unsigned int crate) {
  if (crate > 17) {
    throw std::invalid_argument("Invalid crate number.");
  }
  return RCTlinks[crate];
}


/**
 * Write the link values of all 18 craters to a formatted text file.
 */
void
CaloLinks::write_to_file(std::ofstream& outfile) {
  outfile << "run: " << run << " lumi: " << lumi << " event: " << event << std::endl;

  // For all RCT crates
  for (int i = 0; i < 18; ++i) {

    // retrive the bit values for each link
    std::vector<uint8_t> link1 = RCTlinks[i].link_values(1);
    std::vector<uint8_t> link2 = RCTlinks[i].link_values(2);

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
