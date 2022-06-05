#pragma once

#include <cstdint>

namespace Duennschiss
{
  typedef union
  {
    uint32_t i;
    uint16_t s[2];
    uint8_t b[4];
  } UU32;

  typedef union
  {
    int32_t i;
    int16_t s[2];
    int8_t b[4];
  } SU32;
  
  namespace Struct
  {

#define MAGIC (uint16_t)0x1337
#define ALL_DAY (uint8_t)0xff
#define PADDING_BYTE 0

    enum : uint8_t
    {
      e_mgdl = 0,
      e_mmolL = 1
    };

    enum : uint8_t
    {
      e_NovoRapid,
      e_Levemir
    };

    enum : uint8_t
    {
      e_Coffee,
      e_Water,
      e_Tea
    };

    typedef enum : uint8_t
    {
      eMeasurement,
      eInjection,
      eLiquid,
      eNutrient,
      eWorkout,
      eText,
    } E_EntryType;

    typedef struct tagEntryContainer
    {
      uint8_t sizeBytes;
      E_EntryType type;
      uint8_t *data;
      struct tagEntryContainer *nxtEntry;
    } T_EntryContainer;

    typedef struct
    {
      uint8_t isBellyLeft : 1;
      uint8_t bellyX : 2;
      uint8_t bellyY : 3;
      uint8_t bellyP : 2;
      uint8_t isLeg : 1;
      uint8_t isLegLeft : 1;
      uint8_t legButtonX : 2;
      uint8_t legButtonY : 2;
      uint8_t legButtonP : 2;
    } T_InjDat;

    typedef struct
    {
      // date and time make already up for a unique identifier number
      // year is years since 1970
      uint16_t date;
      // time as 15 minute offsets from midnight
      uint8_t timeOff;
      uint8_t align : 8;
    } T_Timestamp;

    typedef struct tagLineEntry
    {
      T_Timestamp timestamp;
      uint16_t payloadLen;
      T_EntryContainer payload;
    } T_LineEntry;
  };
};