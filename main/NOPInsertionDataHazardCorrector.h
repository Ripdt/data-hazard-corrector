#ifndef NOPINSERTIONDATAHAZARDCORRECTORH
#define NOPINSERTIONDATAHAZARDCORRECTORH

#include "DataHazardCorrector.h"

class NOPInsertionDataHazardCorrector : public DataHazardCorrector
{
public:
  NOPInsertionDataHazardCorrector(
    const std::string hazardPath
  );

protected:
  void ResolveDataHazards() override;

private:
  void InsertFixedInstruction();
};

#endif // NOPINSERTIONDATAHAZARDCORRECTORH




