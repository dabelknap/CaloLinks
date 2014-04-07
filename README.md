##Calo Links

This package provides methods for reading and writing text files that contain
the link data produced by the oRSC that is recieved by the MP7/CTP7. It contains
two classes: `CaloLinks` and `CrateLinks`. A `BuildFile.xml` was provided so the
package can be used in CMSSW if desired.

 - `CrateLinks` contains the tables that define the bit-fields, and it handles
   the link data for a single RCT crate. It also contains methods that allow you
   to set/get the individual named RCT bits.
 - `CaloLinks` is a collection of 18 `CrateLinks`, to represent the full RCT
   system. It contains the methods for reading/writing with text files.

###Testing and Usage

The `Makefile` compiles `tests/tests.cc`. This code reads an example test file
produced by oRSCPatterns (https://github.com/uwcms/oRSCPatterns), which is
located here: `tests/data/two_events.txt`. The file contains the link data for
two events. The `read_from_file(...)` method reads a single event from the file,
and `write_to_file(...)` then writes the data to `test.txt` using the same
format. Another call to `read_from_file(...)` will read the next block of link
data in the text file. A simple `diff` between `test.txt` and
`data/two_events.txt` should confirm that the read/write operations were
successfull.

###Modifying the Bit-Fields

At some point we may wish to redefine the layout of the bit-fields. To do this,
modify `CrateLinks::define_link_tables()`. After making modifications, you must
run `scripts/checkCrateLinkTabls.py` to validate the link tables.
