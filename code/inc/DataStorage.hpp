#pragma once

#include <cstdint>
#include <stdbool.h>
#include <stdio.h>

#include "structures.hpp"

using namespace Duennschiss;

namespace Duennschiss
{
  namespace Data
  {
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
      Struct::T_LineEntry findEntryByTimestamp(Struct::T_Timestamp);
      Struct::T_LineEntry findNthEntry(uint32_t);
      void loadNEntries(Struct::T_LineEntry *, uint32_t);
      bool storeNEntries(Struct::T_LineEntry *, uint32_t);

    private:
      void initFile(void);
    };
  };
};