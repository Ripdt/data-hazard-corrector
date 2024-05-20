#ifndef NOPINSERTIONDATAHAZARDCORRECTORH
#define NOPINSERTIONDATAHAZARDCORRECTORH

#include "DataHazardCorrector.h"

class NOPInsertionDataHazardCorrector : public DataHazardCorrector
{
public:
  NOPInsertionDataHazardCorrector(
    const std::string hazardPath
  );

private:
  void ResolveDataHazards() override;

  void InsertFixedInstruction();
};

#endif // NOPINSERTIONDATAHAZARDCORRECTORH




