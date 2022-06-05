#include <cstring>
#include "Terminator.hpp"
#include "DataStorage.hpp"
#include "structures.hpp"

using namespace Duennschiss;
using namespace Struct;
using namespace Data;
using namespace Terminator;

#define MIN(x,y) ((y) ^ (((x) ^ (y)) & -((x) < (y))))

DataIO::DataIO(char *dbName, bool createNew)
{
  this->dbname = dbName;
  this->dbfile = fopen(this->dbname, "a");

  if (this->dbfile == NULL)
    T1000::kill(T1000::eCouldNotOpenDatabase);

  int fsize = ftell(this->dbfile);

  rewind(this->dbfile);

  if (fsize == 0)
  {
    DataIO::initFile();
  }
  else if (fsize < sizeof(MAGIC))
  {
    fclose(this->dbfile);
    T1000::kill(T1000::eMagicWrongLength);
  }
  else
  {
    uint16_t aMagicMoment = 0xcafe;
    fclose(this->dbfile);
    this->dbfile = fopen(this->dbname, "rb");
    if (this->dbfile == NULL)
      T1000::kill(T1000::eCouldNotOpenDatabase);

    fread(&aMagicMoment, sizeof(MAGIC), 1, this->dbfile);
    aMagicMoment = SWP_W(aMagicMoment);
    if (aMagicMoment != MAGIC)
    {
      printf("Should: 0x%04x, got 0x%04x\n", MAGIC, aMagicMoment);
      fclose(this->dbfile);
      T1000::kill(T1000::eMagicIsWrong);
    }
    fclose(this->dbfile);
    this->dbfile = fopen(this->dbname, "a");
    if (this->dbfile == NULL)
      T1000::kill(T1000::eCouldNotOpenDatabase);
  }
}

void DataIO::initFile(void)
{
  UU32 d = {MAGIC};
  DataIO::writeNBytes(&d, 2);
}

Struct::T_LineEntry DataIO::findEntryByTimestamp(Struct::T_Timestamp ts)
{
  T_LineEntry e;
  return e;
}

Struct::T_LineEntry DataIO::findNthEntry(uint32_t n)
{
  T_LineEntry e;
  return e;
}

void DataIO::loadNEntries(Struct::T_LineEntry *e, uint32_t n)
{
}

bool DataIO::storeNEntries(Struct::T_LineEntry *e, uint32_t n)
{
  uint32_t i = 0;
  uint16_t psize;
  uint8_t dsize;
  T_EntryContainer *currPL = &(e->payload);
  while (i++ < n)
  {
    fwrite(&(e->timestamp), sizeof(T_Timestamp), 1, this->dbfile);
    psize = e->payloadLen;
    fwrite(&psize, sizeof(psize), 1, this->dbfile);
    do
    {
      dsize = currPL->sizeBytes;
      fwrite(&(currPL->sizeBytes), sizeof(currPL->sizeBytes), 1, this->dbfile);
      dsize -= sizeof(currPL->type);
      fwrite(&(currPL->type), sizeof(currPL->type), 1, this->dbfile);
      fwrite(currPL->data, dsize, 1, this->dbfile);
      currPL = currPL->nxtEntry;
    } while (currPL != NULL);
  }

  return true;
}

uint32_t DataIO::writeNBytes(UU32 *data, uint32_t n)
{
  return DataIO::writeNBytesWPadding(data, n, 0, 0);
}

uint32_t DataIO::writeNBytesWPadding(UU32 *data, uint32_t n, uint32_t paddingWhen, uint32_t paddingN)
{
  uint8_t off;
  uint32_t written = 0;
  uint32_t min = 0;
  // write until MIN(n, paddingWhen)
  min = paddingWhen ^ ((n ^ paddingWhen) & -(n < paddingWhen));
  written += min;
  n -= written;
  off = DataIO::writeNPadHelper(data, min, 0, 0, 0);

  // write padding
  written += paddingN;
  DataIO::writeNPadHelper(data, 0, 0, 0, paddingN);

  // continue after padding
  written += n;
  DataIO::writeNPadHelper(data, n, off, 0, 0);

  return written;
}

uint8_t DataIO::writeNPadHelper(UU32 *data, uint32_t n, uint8_t bOff, uint32_t paddingWhen, uint32_t paddingN)
{
  uint8_t bp = bOff;
  UU32 pad = {0};
  uint32_t i;
  uint16_t s;

  while (n > 0)
  {
    if (((((uint8_t) n / 4) > 0) || (n % 4 == 0)) && (bp % 2 == 0)) { // int
      i = SWP_D(data->i);
      fwrite(&i, sizeof(i), 1, this->dbfile);
      n -= 4;
      bp += 4;
    } else if (((((uint8_t) n / 2) > 0) || (n % 2 == 0)) && (bp % 2 == 0)) { // short
      s = SWP_W(data->s[bp >> 1]);
      fwrite(&s, sizeof(s), 1, this->dbfile);
      n -= 2;
      bp += 2;
    } else { // byte
      fwrite(data->b + bp++, 1, 1, this->dbfile);
      --n;
    }
    
    //clamp bp to 4
    bp = MIN(4, bp);
    data += bp == 4;
    bp %= 4;
  }
  while (paddingN > 0)
  {
    switch (paddingN % 4) {
      case 0:
        fwrite (&(pad.i), sizeof(pad.i), 1, this->dbfile);
        paddingN -= 4;
        break;
      case 2:
        fwrite (&(pad.s[0]), sizeof(pad.s[0]), 1, this->dbfile);
        paddingN -= 2;
        break;
      default:
        fwrite(&pad, 1, 1, this->dbfile);
        --paddingN;
    }
  }
  return bp;
}

uint32_t DataIO::fillNByteswithV(uint32_t n, uint8_t v)
{
  uint32_t nbrUnions = (n >> 2) + ((n % 4) > 0);
  UU32 *u = (UU32 *)malloc(nbrUnions * sizeof(UU32));
  uint32_t t = n;
  // while ((t--) > 0)
  //   *((uint8_t *)(u + t)) = v;
  std::memset(u, nbrUnions << 2, sizeof(*u));
  t = DataIO::writeNBytes((UU32 *)u, n);
  free(u);
  return t;
}
