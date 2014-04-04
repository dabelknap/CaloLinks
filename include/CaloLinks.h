/**
 * Filename: CaloLinks.h
 *
 * Description: This class contains the collection for CrateLink objects to
 *              represent all 18 RCT crates. It includes a method to write the
 *              link values to a formatted text file.
 *
 * Author: D. Austin Belknap, UW-Madison
 */

#ifndef _CALOLINKS_h
#define _CALOLINKS_h

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdint.h>

#include "CrateLinks.h"


class CaloLinks {
  private:
    CrateLinks RCTlinks[18];

    unsigned int event;
    unsigned int lumi;
    unsigned int run;


  public:
    CaloLinks(unsigned int event, unsigned int lumi, unsigned int run);
    CaloLinks() { };
    ~CaloLinks() { }

    CrateLinks& get_crate(unsigned int crate);

    void write_to_file(std::ofstream& outfile);

    void read_from_file(std::ifstream& infile);
};

#endif
