#include <unistd.h>
#include <stdlib.h>

#include "structures.hpp"
#include "DataStorage.hpp"

using namespace Duennschiss;
using namespace Struct;
using namespace Data;

int main(int argc, char **argv)
{
#if 0
  char c;
  while ((c = getopt(argc, argv, "")) != -1)
  {
    switch (c)
    {

    default:
      break;
    }
  }
#else
  (void)argc;
  (void)argv;
#endif
  uint8_t data = 0x2a;
  char *fname = "./storage.db";
  DataIO db = DataIO(fname, true);
  T_LineEntry entrie = {
      .timestamp = {
          .year = 22,
          .month = 6,
          .day = 1,
          .timeOff = ALL_DAY},
      .payload = {.sizeBytes = 1 + sizeof(eText), .type = eText, .data = &data, .nxtEntry = NULL}};
  db.storeNEntries(&entrie, 1);
}