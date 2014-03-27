/**
 * Filename: CaloLinks.h
 *
 * Description:
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
    ~CaloLinks() { }

    CrateLinks& get_crate(unsigned int crate);

    void write_to_file(std::ofstream outfile);
};

#endif
