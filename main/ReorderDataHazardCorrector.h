#ifndef REORDERDATAHAZARDCORRECTORH
#define REORDERDATAHAZARDCORRECTORH

#include "NOPInsertionDataHazardCorrector.h"

class ReorderDataHazardCorrector : public NOPInsertionDataHazardCorrector
{
public:
  ReorderDataHazardCorrector(
    const std::string _hazardPath
  );

private:
  void ResolveDataHazards() override;
};

#endif