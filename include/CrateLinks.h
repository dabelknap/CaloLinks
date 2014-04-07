/**
 * Filename: CrateLinks.h
 *
 * Description: Abstracts the JSC output for a single RCT crate into the
 *              bit-fields used in the oRSC -> MP7/CTP7 optical links.
 *
 * Author: D. Ausitn Belknap, UW-Madison
 */

#ifndef _CRATELINKS_h
#define _CRATELINKS_h

#include <iostream>
#include <stdexcept>
#include <vector>
#include <stdint.h>


/**
 * This class abstracts the JSC bits for a single RCT crate. It contains methods
 * for defining the various RCT bits, and arranges them into the bit-fields used
 * in the optical links.
 */
class CrateLinks {
  private:
    // RC Et, Index: RC number, region, bit number
    uint8_t RCEt[7][2][10];

    // RC Tau Veto, Index: RC number, region
    uint8_t RCTau[7][2];

    // RC Overflow, Index: RC number, region
    uint8_t RCOf[7][2];

    // RC HAD Veto (MIP), Index: RC number, region
    uint8_t RCHad[7][2];

    // HF Finegrain, Index: Region
    uint8_t HFFg[8];

    // HF Et, Index: Region, bit number
    uint8_t HFEt[8][8];


    // Non-Iso EG position (0 Region, 1-3 card)
    // Index: candidate index, bit-number
    uint8_t NEPos[4][4];

    // Non-Iso EG Et, Index: cand. index, bit number
    uint8_t NEEt[4][6];

    // Iso EG position (0 Region, 1-3 card)
    // Index: candidate index, bit-number
    uint8_t IEPos[4][4];

    // Iso EG Et, Index: cand. index, bit number
    uint8_t IEEt[4][6];

    uint8_t ZERO;


    uint8_t* Link1 [24][8];
    uint8_t* Link2 [24][8];

    void define_link_tables();

    static void check_RC_indicies(unsigned int card, unsigned int region);


  public:
    CrateLinks();
    ~CrateLinks() {};

    void set_RCEt(unsigned int card, unsigned int region, unsigned int bit,
        uint8_t value);
    void set_RCTau(unsigned int card, unsigned int region, uint8_t value);
    void set_RCOf(unsigned int card, unsigned int region, uint8_t value);
    void set_RCHad(unsigned int card, unsigned int region, uint8_t value);

    void set_HFFg(unsigned int region, uint8_t value);
    void set_HFEt(unsigned int region, unsigned int bit, uint8_t value);

    void set_NEPos(unsigned int cand, unsigned int bit, uint8_t value);
    void set_NEEt(unsigned int cand, unsigned int bit, uint8_t value);

    void set_IEPos(unsigned int cand, unsigned int bit, uint8_t value);
    void set_IEEt(unsigned int cand, unsigned int bit, uint8_t value);


    uint8_t get_RCEt(unsigned int card, unsigned int region, unsigned int bit);
    uint8_t get_RCTau(unsigned int card, unsigned int region);
    uint8_t get_RCOf(unsigned int card, unsigned int region);
    uint8_t get_RCHad(unsigned int card, unsigned int region);

    uint8_t get_HFFg(unsigned int region);
    uint8_t get_HFEt(unsigned int region, unsigned int bit);

    uint8_t get_NEPos(unsigned int cand, unsigned int bit);
    uint8_t get_NEEt(unsigned int cand, unsigned int bit);

    uint8_t get_IEPos(unsigned int cand, unsigned int bit);
    uint8_t get_IEEt(unsigned int cand, unsigned int bit);


    void print_table(int link);

    std::vector<uint32_t> link_values(int link);

    void set_links(std::vector<uint32_t>& link_values, int link);
};

#endif
