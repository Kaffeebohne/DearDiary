#pragma once
#include <cstdlib>
#include <stdio.h>

namespace Terminator
{
  namespace T1000
  {
    enum tagKillReason
    {
      eNoError,
      eCouldNotOpenDatabase,
      eMagicWrongLength,
      eMagicIsWrong,
    };

    char *description[] = {
        "Nothing wrong",
        "I wasn't able to open the database file",
        "The Magic has the wrong length.",
        "The file has a wrong magic."};

    void kill(enum tagKillReason e)
    {
      fprintf(stderr, "[%d]: %s\n", e, description[e]);
      exit(e);
    }
  };
};