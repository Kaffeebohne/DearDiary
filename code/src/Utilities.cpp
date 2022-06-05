#include <stdio.h>

#include "Utilities.hpp"

using namespace Duennschiss;
using namespace Struct;
using namespace Utils;

void Utilities::dateToTimestamp(Struct::T_Timestamp *ts, uint16_t y, uint8_t m, uint8_t d)
{
  uint8_t yO = (uint8_t)(y - 1970);
  ts->date = (yO & 0x7f) << 9 | (m & 0x0f) << 5 | (d & 0x1f);
}

void Utilities::timestampToDate(Struct::T_Timestamp ts, uint8_t *pDat)
{
}

void Utilities::insertTimeInTimestamp(Struct::T_Timestamp *ts, uint8_t h, uint8_t m)
{
  uint8_t offset = 4 * h;
  float norm = (float)m / 60.0f;
  float quant = 1.0f / 8.0f;
  float step = 1.0f / 4.0f;
  for (int i = 4; i > 0; --i)
  {
    offset += norm >= quant;
    quant += step;
  }
  ts->timeOff = offset;
}

void Utilities::printTimestamp(Struct::T_Timestamp ts)
{
  uint8_t d, M, y, h, m;
  uint16_t yh = 1970;
  d = ts.date & 0x001f;
  M = (ts.date & 0x01e0) >> 5;
  y = (ts.date & 0xfe00) >> 9;
  h = (uint8_t)((ts.timeOff * 15) / 60);
  m = (uint8_t)((ts.timeOff * 15) % 60);
  yh += y;
  printf("%02hhu.%02hhu.%04hu %02hhu:%02hhuh\n", d, M, yh, h, m);
}

void Utilities::timestampFromString(Struct::T_Timestamp *ts, char *str)
{
  uint8_t d, M, y, h, m;
  uint16_t yh;
  char c;
  sscanf(str, "%02hhu.%02hhu.%04hu %02hhu:%02hhu%c", &d, &M, &yh, &h, &m, &c);
  printf("Read: %hhu.%hhu.%hu %hhu:%hhu\n", d, M, yh, h, m);
  y = (uint8_t)yh - 1970;
  Utilities::convertFromDateSpec(&(ts->date), y, M, d);
  Utilities::convertFromTimeSpec(&(ts->timeOff), h, m);
}

void Utilities::convertFromDateSpec(uint16_t *date, uint8_t year, uint8_t month, uint8_t day)
{
  *date ^= *date;
  *date = (year & 0x7f) << 9 | (month & 0x0f) << 5 | (day & 0x1f);
}
void Utilities::convertToDateSpace(uint16_t date, uint8_t *year, uint8_t *month, uint8_t *day)
{
  *year = (date & 0xfe00) >> 9;
  *month = (date & 0x01e0) >> 5;
  *day = (date & 0x1f);
}
void Utilities::convertFromTimeSpec(uint8_t *timeOff, uint8_t h, uint8_t m)
{
  *timeOff = 4 * h;
  float norm = (float)m / 60.0f;
  float quant = 1.0f / 8.0f;
  float step = 1.0f / 4.0f;
  for (int i = 4; i > 0; --i)
  {
    *timeOff += norm >= quant;
    quant += step;
  }
}
void Utilities::convertToTimeSpec(uint8_t timeOff, uint8_t *h, uint8_t *m)
{
  uint16_t chunks = timeOff * 15;
  *h = (uint8_t)chunks / 60;
  *m = (uint8_t)chunks % 60;
}