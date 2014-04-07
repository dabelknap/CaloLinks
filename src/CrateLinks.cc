/**
 * Filename: CrateLinks.cc
 *
 * Description: Abstracts the output bits for a single RCT crate to be arranged
 *              into bitfields used in the oRSC -> CTP7/MP7 optical links
 *
 * Author: D. Austin Belknap, UW-Madison
 */

#include "../include/CrateLinks.h"


/**
 * Default contructor.
 */
CrateLinks::CrateLinks() {
  ZERO = 0;
  define_link_tables();
}


void
CrateLinks::check_RC_indicies(unsigned int card, unsigned int region) {
  if (card > 6) {
    throw std::invalid_argument("Invalid RC card index");
  }
  if (region > 1) {
    throw std::invalid_argument("Invalid RC region");
  }
}


void
CrateLinks::set_RCEt(unsigned int card, unsigned int region, unsigned int bit,
    uint8_t value) {
  check_RC_indicies(card, region);
  if (bit > 9) {
    throw std::invalid_argument("Invalid RC Et bit index");
  }
  RCEt[card][region][bit] = value & 0x1;
}


uint8_t
CrateLinks::get_RCEt(unsigned int card, unsigned int region,
    unsigned int bit) {
  check_RC_indicies(card, region);
  if (bit > 9) {
    throw std::invalid_argument("Invalid RC Et bit index");
  }
  return RCEt[card][region][bit];
}


void
CrateLinks::set_RCTau(unsigned int card, unsigned int region, uint8_t value) {
  check_RC_indicies(card, region);
  RCTau[card][region] = value & 0x1;
}


uint8_t
CrateLinks::get_RCTau(unsigned int card, unsigned int region) {
  check_RC_indicies(card, region);
  return RCTau[card][region];
}


void
CrateLinks::set_RCOf(unsigned int card, unsigned int region, uint8_t value) {
  check_RC_indicies(card, region);
  RCOf[card][region] = value & 0x1;
}


uint8_t
CrateLinks::get_RCOf(unsigned int card, unsigned int region) {
  check_RC_indicies(card, region);
  return RCOf[card][region];
}


void
CrateLinks::set_RCHad(unsigned int card, unsigned int region, uint8_t value) {
  check_RC_indicies(card, region);
  RCHad[card][region] = value & 0x1;
}


uint8_t
CrateLinks::get_RCHad(unsigned int card, unsigned int region) {
  check_RC_indicies(card, region);
  return RCHad[card][region];
}


void
CrateLinks::set_HFFg(unsigned int region, uint8_t value) {
  if (region > 7) {
    throw std::invalid_argument("Invalid HF region number");
  }
  HFFg[region] = value & 0x1;
}


uint8_t
CrateLinks::get_HFFg(unsigned int region) {
  if (region > 7) {
    throw std::invalid_argument("Invalid HF region number");
  }
  return HFFg[region];
}


void
CrateLinks::set_HFEt(unsigned int region, unsigned int bit, uint8_t value) {
  if (region > 7) {
    throw std::invalid_argument("Invalid HF region number");
  }
  if (bit > 7) {
    throw std::invalid_argument("Invalid HF Et bit number");
  }
  HFEt[region][bit] = value & 0x1;
}


uint8_t
CrateLinks::get_HFEt(unsigned int region, unsigned int bit) {
  if (region > 7) {
    throw std::invalid_argument("Invalid HF region number");
  }
  if (bit > 7) {
    throw std::invalid_argument("Invalid HF Et bit number");
  }
  return HFEt[region][bit];
}


void
CrateLinks::set_NEPos(unsigned int cand, unsigned int bit, uint8_t value) {
  if (cand > 3) {
    throw std::invalid_argument("Invalid NE candidate index");
  }
  if (bit > 3) {
    throw std::invalid_argument("Invalid NE position bit index");
  }
  NEPos[cand][bit] = value & 0x1;
}


uint8_t
CrateLinks::get_NEPos(unsigned int cand, unsigned int bit) {
  if (cand > 3) {
    throw std::invalid_argument("Invalid NE candidate index");
  }
  if (bit > 3) {
    throw std::invalid_argument("Invalid NE position bit index");
  }
  return NEPos[cand][bit];
}


void
CrateLinks::set_NEEt(unsigned int cand, unsigned int bit, uint8_t value) {
  if (cand > 3) {
    throw std::invalid_argument("Invalid NE candidate index");
  }
  if (bit > 5) {
    throw std::invalid_argument("Invalid NE Et bit index");
  }
  NEEt[cand][bit] = value & 0x1;
}


uint8_t
CrateLinks::get_NEEt(unsigned int cand, unsigned int bit) {
  if (cand > 3) {
    throw std::invalid_argument("Invalid NE candidate index");
  }
  if (bit > 5) {
    throw std::invalid_argument("Invalid NE Et bit index");
  }
  return NEEt[cand][bit];
}


void
CrateLinks::set_IEPos(unsigned int cand, unsigned int bit, uint8_t value) {
  if (cand > 3) {
    throw std::invalid_argument("Invalid IE candidate index");
  }
  if (bit > 3) {
    throw std::invalid_argument("Invalid IE position bit index");
  }
  IEPos[cand][bit] = value & 0x1;
}


uint8_t
CrateLinks::get_IEPos(unsigned int cand, unsigned int bit) {
  if (cand > 3) {
    throw std::invalid_argument("Invalid IE candidate index");
  }
  if (bit > 3) {
    throw std::invalid_argument("Invalid IE position bit index");
  }
  return IEPos[cand][bit];
}


void
CrateLinks::set_IEEt(unsigned int cand, unsigned int bit, uint8_t value) {
  if (cand > 3) {
    throw std::invalid_argument("Invalid IE candidate index");
  }
  if (bit > 5) {
    throw std::invalid_argument("Invalid IE Et bit index");
  }
  IEEt[cand][bit] = value & 0x1;
}


uint8_t
CrateLinks::get_IEEt(unsigned int cand, unsigned int bit) {
  if (cand > 3) {
    throw std::invalid_argument("Invalid IE candidate index");
  }
  if (bit > 5) {
    throw std::invalid_argument("Invalid IE Et bit index");
  }
  return IEEt[cand][bit];
}


/**
 * Output the link values as 6 32-bit integers.
 */
std::vector<uint32_t>
CrateLinks::link_values(int link_number) {
  std::vector<uint32_t> link;

  uint32_t val = 0;

  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 8; j++) {
      val <<= 1;

      if (link_number == 1) {
        val |= *Link1[i][j] & 0x1;
      }
      else if (link_number == 2) {
        val |= *Link2[i][j] & 0x1;
      }
      else {
        throw std::invalid_argument("Invalid link number given");
      }
    }
    if (i % 4 == 3) {
      link.push_back(val);
      val = 0;
    }
  }
  return link;
}


/**
 * Allows you to pass a vector of uint32_t's that contains the data of a given
 * link. Basically, it allows you to set the link values with the output of
 * link_values(...).
 */
void
CrateLinks::set_links(std::vector<uint32_t>& link_values, int link) {
  if (link_values.size() != 6) {
    throw std::invalid_argument("Vector of link values has the wrong length");
  }

  uint32_t val;

  // Because we retrieve the least-significant bit from val first, we have to
  // write the values into the link tables in reverse. e.g. the first 32-bit
  // word covers the first 4 rows in the table. We start at [3][7], and work our
  // way back to [0][0].
  if (link == 1) {
    for (int i = 0; i < 6; ++i) {
      val = link_values.at(i);

      for (int j = 31; j >=0; --j) {
        *(Link1[4*i + 3 - (31-j)/8][j % 8]) = val & 0x1;
        val >>= 1;
      }
    }
  }
  else if (link == 2) {
    for (int i = 0; i < 6; ++i) {
      val = link_values.at(i);

      for (int j = 31; j >=0; --j) {
        *(Link2[4*i + 3 - (31-j)/8][j % 8]) = val & 0x1;
        val >>= 1;
      }
    }
  }
  else {
    throw std::invalid_argument("set_links: Incorrect Link index given");
  }
}


void
CrateLinks::print_table(int link) {
  uint8_t* (*Link)[24][8];

  if (link == 1) {
    Link = &Link1;
  }
  else if (link == 2) {
    Link = &Link2;
  }
  else {
    throw std::invalid_argument("Invalid link number given.");
  }

  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 8; j++) {
      std::cout << (int)(*(*Link)[i][j]) << " ";
    }
    std::cout << std::endl;
  }
}


/**
 * Arrange the JSC output bits into the bitfields for the 2 oRSC optical links.
 */
void
CrateLinks::define_link_tables() {
  uint8_t* L1 [24][8] = {
    {&ZERO,             &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO},
    {&ZERO,             &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO},
    {&RCOf[6][1],       &RCOf[6][0],        &RCOf[5][1],        &RCOf[5][0],        &RCOf[4][1],        &RCOf[4][0],        &RCOf[3][1],        &RCOf[3][0]},
    {&RCOf[2][1],       &RCOf[2][0],        &RCOf[1][1],        &RCOf[1][0],        &RCOf[0][1],        &RCOf[0][0],        &RCTau[6][1],       &RCTau[6][0]},
    {&RCTau[5][1],      &RCTau[5][0],       &RCTau[4][1],       &RCTau[4][0],       &RCTau[3][1],       &RCTau[3][0],       &RCTau[2][1],       &RCTau[2][0]},
    {&RCTau[1][1],      &RCTau[1][0],       &RCTau[0][1],       &RCTau[0][0],       &RCEt[6][1][9],     &RCEt[6][1][8],     &RCEt[6][1][7],     &RCEt[6][1][6]},
    {&RCEt[6][1][5],    &RCEt[6][1][4],     &RCEt[6][1][3],     &RCEt[6][1][2],     &RCEt[6][1][1],     &RCEt[6][1][0],     &RCEt[6][0][9],     &RCEt[6][0][8]},
    {&RCEt[6][0][7],    &RCEt[6][0][6],     &RCEt[6][0][5],     &RCEt[6][0][4],     &RCEt[6][0][3],     &RCEt[6][0][2],     &RCEt[6][0][1],     &RCEt[6][0][0]},
    {&RCEt[5][1][9],    &RCEt[5][1][8],     &RCEt[5][1][7],     &RCEt[5][1][6],     &RCEt[5][1][5],     &RCEt[5][1][4],     &RCEt[5][1][3],     &RCEt[5][1][2]},
    {&RCEt[5][1][1],    &RCEt[5][1][0],     &RCEt[5][0][9],     &RCEt[5][0][8],     &RCEt[5][0][7],     &RCEt[5][0][6],     &RCEt[5][0][5],     &RCEt[5][0][4]},
    {&RCEt[5][0][3],    &RCEt[5][0][2],     &RCEt[5][0][1],     &RCEt[5][0][0],     &RCEt[4][1][9],     &RCEt[4][1][8],     &RCEt[4][1][7],     &RCEt[4][1][6]},
    {&RCEt[4][1][5],    &RCEt[4][1][4],     &RCEt[4][1][3],     &RCEt[4][1][2],     &RCEt[4][1][1],     &RCEt[4][1][0],     &RCEt[4][0][9],     &RCEt[4][0][8]},
    {&RCEt[4][0][7],    &RCEt[4][0][6],     &RCEt[4][0][5],     &RCEt[4][0][4],     &RCEt[4][0][3],     &RCEt[4][0][2],     &RCEt[4][0][1],     &RCEt[4][0][0]},
    {&RCEt[3][1][9],    &RCEt[3][1][8],     &RCEt[3][1][7],     &RCEt[3][1][6],     &RCEt[3][1][5],     &RCEt[3][1][4],     &RCEt[3][1][3],     &RCEt[3][1][2]},
    {&RCEt[3][1][1],    &RCEt[3][1][0],     &RCEt[3][0][9],     &RCEt[3][0][8],     &RCEt[3][0][7],     &RCEt[3][0][6],     &RCEt[3][0][5],     &RCEt[3][0][4]},
    {&RCEt[3][0][3],    &RCEt[3][0][2],     &RCEt[3][0][1],     &RCEt[3][0][0],     &RCEt[2][1][9],     &RCEt[2][1][8],     &RCEt[2][1][7],     &RCEt[2][1][6]},
    {&RCEt[2][1][5],    &RCEt[2][1][4],     &RCEt[2][1][3],     &RCEt[2][1][2],     &RCEt[2][1][1],     &RCEt[2][1][0],     &RCEt[2][0][9],     &RCEt[2][0][8]},
    {&RCEt[2][0][7],    &RCEt[2][0][6],     &RCEt[2][0][5],     &RCEt[2][0][4],     &RCEt[2][0][3],     &RCEt[2][0][2],     &RCEt[2][0][1],     &RCEt[2][0][0]},
    {&RCEt[1][1][9],    &RCEt[1][1][8],     &RCEt[1][1][7],     &RCEt[1][1][6],     &RCEt[1][1][5],     &RCEt[1][1][4],     &RCEt[1][1][3],     &RCEt[1][1][2]},
    {&RCEt[1][1][1],    &RCEt[1][1][0],     &RCEt[1][0][9],     &RCEt[1][0][8],     &RCEt[1][0][7],     &RCEt[1][0][6],     &RCEt[1][0][5],     &RCEt[1][0][4]},
    {&RCEt[1][0][3],    &RCEt[1][0][2],     &RCEt[1][0][1],     &RCEt[1][0][0],     &RCEt[0][1][9],     &RCEt[0][1][8],     &RCEt[0][1][7],     &RCEt[0][1][6]},
    {&RCEt[0][1][5],    &RCEt[0][1][4],     &RCEt[0][1][3],     &RCEt[0][1][2],     &RCEt[0][1][1],     &RCEt[0][1][0],     &RCEt[0][0][9],     &RCEt[0][0][8]},
    {&RCEt[0][0][7],    &RCEt[0][0][6],     &RCEt[0][0][5],     &RCEt[0][0][4],     &RCEt[0][0][3],     &RCEt[0][0][2],     &RCEt[0][0][1],     &RCEt[0][0][0]},
    {&ZERO,             &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO}
  };

  uint8_t* L2 [24][8] = {
    {&ZERO,             &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO},
    {&ZERO,             &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO},
    {&ZERO,             &ZERO,              &RCHad[6][1],       &RCHad[6][0],       &RCHad[5][1],       &RCHad[5][0],       &RCHad[4][1],       &RCHad[4][0]},
    {&RCHad[3][1],      &RCHad[3][0],       &RCHad[2][1],       &RCHad[2][0],       &RCHad[1][1],       &RCHad[1][0],       &RCHad[0][1],       &RCHad[0][0]},
    {&NEPos[3][3],      &NEPos[3][2],       &NEPos[3][1],       &NEPos[3][0],       &NEEt[3][5],        &NEEt[3][4],        &NEEt[3][3],        &NEEt[3][2]},
    {&NEEt[3][1],       &NEEt[3][0],        &NEPos[2][3],       &NEPos[2][2],       &NEPos[2][1],       &NEPos[2][0],       &NEEt[2][5],        &NEEt[2][4]},
    {&NEEt[2][3],       &NEEt[2][2],        &NEEt[2][1],        &NEEt[2][0],        &NEPos[1][3],       &NEPos[1][2],       &NEPos[1][1],       &NEPos[1][0]},
    {&NEEt[1][5],       &NEEt[1][4],        &NEEt[1][3],        &NEEt[1][2],        &NEEt[1][1],        &NEEt[1][0],        &NEPos[0][3],       &NEPos[0][2]},
    {&NEPos[0][1],      &NEPos[0][0],       &NEEt[0][5],        &NEEt[0][4],        &NEEt[0][3],        &NEEt[0][2],        &NEEt[0][1],        &NEEt[0][0]},
    {&IEPos[3][3],      &IEPos[3][2],       &IEPos[3][1],       &IEPos[3][0],       &IEEt[3][5],        &IEEt[3][4],        &IEEt[3][3],        &IEEt[3][2]},
    {&IEEt[3][1],       &IEEt[3][0],        &IEPos[2][3],       &IEPos[2][2],       &IEPos[2][1],       &IEPos[2][0],       &IEEt[2][5],        &IEEt[2][4]},
    {&IEEt[2][3],       &IEEt[2][2],        &IEEt[2][1],        &IEEt[2][0],        &IEPos[1][3],       &IEPos[1][2],       &IEPos[1][1],       &IEPos[1][0]},
    {&IEEt[1][5],       &IEEt[1][4],        &IEEt[1][3],        &IEEt[1][2],        &IEEt[1][1],        &IEEt[1][0],        &IEPos[0][3],       &IEPos[0][2]},
    {&IEPos[0][1],      &IEPos[0][0],       &IEEt[0][5],        &IEEt[0][4],        &IEEt[0][3],        &IEEt[0][2],        &IEEt[0][1],        &IEEt[0][0]},
    {&HFFg[7],          &HFFg[6],           &HFFg[5],           &HFFg[4],           &HFFg[3],           &HFFg[2],           &HFFg[1],           &HFFg[0]},
    {&HFEt[7][7],       &HFEt[7][6],        &HFEt[7][5],        &HFEt[7][4],        &HFEt[7][3],        &HFEt[7][2],        &HFEt[7][1],        &HFEt[7][0]},
    {&HFEt[6][7],       &HFEt[6][6],        &HFEt[6][5],        &HFEt[6][4],        &HFEt[6][3],        &HFEt[6][2],        &HFEt[6][1],        &HFEt[6][0]},
    {&HFEt[5][7],       &HFEt[5][6],        &HFEt[5][5],        &HFEt[5][4],        &HFEt[5][3],        &HFEt[5][2],        &HFEt[5][1],        &HFEt[5][0]},
    {&HFEt[4][7],       &HFEt[4][6],        &HFEt[4][5],        &HFEt[4][4],        &HFEt[4][3],        &HFEt[4][2],        &HFEt[4][1],        &HFEt[4][0]},
    {&HFEt[3][7],       &HFEt[3][6],        &HFEt[3][5],        &HFEt[3][4],        &HFEt[3][3],        &HFEt[3][2],        &HFEt[3][1],        &HFEt[3][0]},
    {&HFEt[2][7],       &HFEt[2][6],        &HFEt[2][5],        &HFEt[2][4],        &HFEt[2][3],        &HFEt[2][2],        &HFEt[2][1],        &HFEt[2][0]},
    {&HFEt[1][7],       &HFEt[1][6],        &HFEt[1][5],        &HFEt[1][4],        &HFEt[1][3],        &HFEt[1][2],        &HFEt[1][1],        &HFEt[1][0]},
    {&HFEt[0][7],       &HFEt[0][6],        &HFEt[0][5],        &HFEt[0][4],        &HFEt[0][3],        &HFEt[0][2],        &HFEt[0][1],        &HFEt[0][0]},
    {&ZERO,             &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO,              &ZERO}
  };


  // copy values into the class member arrays
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 8; j++) {
      Link1[i][j] = L1[i][j];
      Link2[i][j] = L2[i][j];
    }
  }
}
