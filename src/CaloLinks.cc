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
 * Write the link values of all 18 crates to a formatted text file.
 */
void
CaloLinks::write_to_file(std::ofstream& outfile) {
  outfile << "run: " << run << " lumi: " << lumi << " event: " << event << std::endl;

  std::vector<uint32_t> link1[18];
  std::vector<uint32_t> link2[18];

  // grab link data for all 18 crates
  for (int i = 0; i < 18; ++i) {
    link1[i] = RCTlinks[i].link_values(1);
    link2[i] = RCTlinks[i].link_values(2);
  }

  // Crate number labels
  outfile << std::setw(2) << std::uppercase << std::setfill('0');
  for (int i = 0; i < 18; ++i) {
    outfile << "Crate " << std::setw(2) << i;
    if (i < 17) {
      outfile << "          ";
    }
  }

  // Link number labels
  outfile << std::endl;
  for (int i = 0; i < 18; ++i) {
    outfile << "Link1    Link2";
    if (i < 17) {
      outfile << "    ";
    }
  }

  // print link data as 6 32-bit words per link
  outfile << std::endl;
  for (int i = 0 ; i < 6; ++i) {
    for (int j = 0; j < 18; ++j) {
      outfile << std::setw(8) << std::hex << int(link1[j].at(i)) << " ";
      outfile << std::setw(8) << std::hex << int(link2[j].at(i)) << " ";
    }
    outfile << std::endl;
  }
  outfile << std::dec << std::endl;
}
