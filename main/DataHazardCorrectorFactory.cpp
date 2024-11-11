#include "DataHazardCorrectorFactory.h"

#include "DataHazardCorrector.h"
#include "NOPInsertionDataHazardCorrector.h"
#include "WithForwardingDataHazardCorrectors.h"
#include "ReorderDataHazardCorrector.h"

DataHazardCorrector* DataHazardCorrectorFactory::CreateCorrector(
  const int typeOfCorrector,
  const std::string hazardPath
)
{
  if (typeOfCorrector == 1) return new NOPInsertionDataHazardCorrector(hazardPath);
  if (typeOfCorrector == 2) return new NOPWithForwardingDataHazardCorrector(hazardPath);
  if (typeOfCorrector == 3) return new ReorderDataHazardCorrector(hazardPath);
  if (typeOfCorrector == 4) return new ReorderWithForwardingDataHazardCorrector(hazardPath);

  throw std::exception();
}