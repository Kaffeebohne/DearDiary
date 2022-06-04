#include "Terminator.hpp"
#include "DataStorage.hpp"

using namespace Duennschiss;
using namespace Struct;
using namespace Data;
using namespace Terminator;

DataIO::DataIO(char *dbName, bool createNew)
{
  this->dbname = dbName;
  this->dbfile = fopen(this->dbname, createNew ? "w+" : "a");

  if (this->dbfile == NULL)
    T1000::kill(T1000::eCouldNotOpenDatabase);

  fseek(this->dbfile, 0, SEEK_SET);
  int fbegin = ftell(this->dbfile);

  fseek(this->dbfile, 0, SEEK_END);
  int fend = ftell(this->dbfile);

  int fsize = fend - fbegin;

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
    uint16_t fileMagic;
    fread(&fileMagic, sizeof(MAGIC), 1, this->dbfile);
    if (fileMagic != MAGIC)
    {
      fclose(this->dbfile);
      T1000::kill(T1000::eMagicIsWrong);
    }
  }
}

void DataIO::initFile(void)
{
  uint16_t magic = MAGIC;
  fwrite(&magic, sizeof(MAGIC), 1, this->dbfile);
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
  uint8_t dsize;
  T_EntryContainer *currPL = &(e->payload);
  while (i++ < n)
  {
    fwrite(&(e->timestamp), sizeof(T_Timestamp), 1, this->dbfile);
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