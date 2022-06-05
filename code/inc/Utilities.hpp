#pragma once
#include <stdint.h>
#include "structures.hpp"

namespace Duennschiss
{
  namespace Utils
  {
    class Utilities
    {
    public:
      static void dateToTimestamp(Struct::T_Timestamp *, uint16_t, uint8_t, uint8_t);
      static void timestampToDate(Struct::T_Timestamp, uint8_t *);
      static void insertTimeInTimestamp(Struct::T_Timestamp *, uint8_t, uint8_t);
      static void printTimestamp(Struct::T_Timestamp);
      static void timestampFromString(Struct::T_Timestamp *, char *);

    private:
      static void convertFromDateSpec(uint16_t *, uint8_t, uint8_t, uint8_t);
      static void convertToDateSpace(uint16_t, uint8_t *, uint8_t *, uint8_t *);
      static void convertFromTimeSpec(uint8_t *, uint8_t, uint8_t);
      static void convertToTimeSpec(uint8_t, uint8_t *, uint8_t *);
    };
  };
};