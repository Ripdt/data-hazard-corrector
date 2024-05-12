#include "DataHazardCorrectorFactory.h"

#include "DataHazardCorrector.h"
#include "NOPInsertionDataHazardCorrector.h"

DataHazardCorrector* DataHazardCorrectorFactory::CreateCorrector(
  const std::string hazardPath
)
{
  return new NOPInsertionDataHazardCorrector(hazardPath);
}