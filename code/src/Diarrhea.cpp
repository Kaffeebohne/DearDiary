#include <unistd.h>
#include <stdlib.h>

#include "structures.hpp"
#include "DataStorage.hpp"
#include "Utilities.hpp"

using namespace Duennschiss;
using namespace Struct;
using namespace Data;
using namespace Utils;

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
  // T_LineEntry entrie = {
  //     .timestamp = {
  //         .year = 22,
  //         .month = 6,
  //         .day = 1,
  //         .timeOff = ALL_DAY},
  //     .payload = {.sizeBytes = 1 + sizeof(eText), .type = eText, .data = &data, .nxtEntry = NULL}};
  // db.storeNEntries(&entrie, 1);
  T_Timestamp ts;
  Utilities::dateToTimestamp(&ts, 2022, 6, 1);
  Utilities::insertTimeInTimestamp(&ts, 8, 15);
  Utilities::printTimestamp(ts);

  Utilities::timestampFromString(&ts, "01.01.1970 00:00h");
  Utilities::printTimestamp(ts);
}