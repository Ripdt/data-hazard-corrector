#ifndef REORDERDATAHAZARDCORRECTIONH
#define REORDERDATAHAZARDCORRECTIONH

#include "DataHazardCorrector.h"

class ReorderDataHazardCorrection : public DataHazardCorrector
{
public:
  ReorderDataHazardCorrection(
    const std::string _hazardPath
  );

private:
  void ResolveDataHazards() override;
};

#endif