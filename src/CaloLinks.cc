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
  if (!outfile.is_open()) {
    throw std::runtime_error("File is not open");
  }

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


/**
 * Read the link values in from a formatted text file and fill a CrateLink object
 */
void
CaloLinks::read_from_file(std::ifstream& infile) {
  if (!infile.is_open()) {
    throw std::runtime_error("File is not open");
  }

  if (infile.eof()) {
    throw std::runtime_error("End of file");
  }

  std::vector<uint32_t> link1[18];
  std::vector<uint32_t> link2[18];

  std::string str;
  long int val;

  // retrieve event info from file
  while (infile >> str) {
    if (str == "run:") {
      infile >> val;
      run = (unsigned int)val;
    }
    if (str == "lumi:") {
      infile >> val;
      lumi = (unsigned int)val;
    }
    if (str == "event:") {
      infile >> val;
      event = (unsigned int)val;
      break;
    }
  }

  getline(infile, str);
  getline(infile, str);
  getline(infile, str);

  // loop over the grid of link data
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 36; ++j) {

      infile >> std::hex >> val;
      uint32_t value = (uint32_t)val;

      if (j % 2 == 0) {
        link1[j/2].push_back(value);
      }
      else {
        link2[j/2].push_back(value);
      }
    }
  }
  infile >> std::dec;
  getline(infile, str);
  getline(infile, str);

  // load the link vectors into the CrateLink objects
  for (int i = 0; i < 18; ++i) {
    RCTlinks[i].set_links(link1[i], 1);
    RCTlinks[i].set_links(link2[i], 2);
  }
}
