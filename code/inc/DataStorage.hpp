#pragma once

#include <cstdint>
#include <stdbool.h>
#include <stdio.h>
#include <endian.h>

#include "structures.hpp"

using namespace Duennschiss;

namespace Duennschiss
{
  namespace Data
  {

#if __BYTE_ORDER == __BIG_ENDIAN
#define SWP_W(v) (v)
#define SWP_D(v) (v)
#define SWP_Q(v) (v)
#else
#define SWP_W(v) (((v) << 8 & 0xff00) | ((v) >> 8 & 0x00ff))
#define SWP_D(v) (((v) << 24 & 0xff000000) | ((v) <<  8 & 0x00ff0000) | \
                  ((v) >>  8 & 0x0000ff00) | ((v) >> 24 & 0x000000ff))
#define SWP_Q(v) (((v) << 56 & 0xff00000000000000) | \
                  ((v) << 40 & 0x00ff000000000000) | \
                  ((v) << 24 & 0x0000ff0000000000) | \
                  ((v) <<  8 & 0x000000ff00000000) |  \
                  ((v) >>  8 & 0x00000000ff000000) |  \
                  ((v) >> 24 & 0x0000000000ff0000) | \
                  ((v) >> 40 & 0x000000000000ff00) | \
                  ((v) >> 56 & 0x00000000000000ff))

#endif // byte order

    class DataIO
    {
    public:
      DataIO(char *dbName, bool createNew);
      ~DataIO()
      {
        fclose(this->dbfile);
      }

    private:
      char *dbname;
      FILE *dbfile;

    public:
      Struct::T_LineEntry findEntryByTimestamp(Struct::T_Timestamp ts);
      Struct::T_LineEntry findNthEntry(uint32_t n);
      void loadNEntries(Struct::T_LineEntry *ts, uint32_t n);
      bool storeNEntries(Struct::T_LineEntry *ts, uint32_t n);
      uint32_t fillNByteswithV(uint32_t n, uint8_t v);

    private:
      void initFile(void);
      uint32_t writeNBytes(UU32 *data, uint32_t n);
      uint32_t writeNBytesWPadding(UU32 *data, uint32_t n, uint32_t paddingWhen, uint32_t paddingN);
      uint8_t writeNPadHelper(UU32 *data, uint32_t n, uint8_t bOff, uint32_t paddingWhen, uint32_t paddingN);
    };
  };
};