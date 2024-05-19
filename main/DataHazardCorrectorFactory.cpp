#include "DataHazardCorrectorFactory.h"

#include "DataHazardCorrector.h"
#include "NOPInsertionDataHazardCorrector.h"
#include "NOPWithForwardingDataHazardCorrector.h"

DataHazardCorrector* DataHazardCorrectorFactory::CreateCorrector(
  const int typeOfCorrector,
  const std::string hazardPath
)
{
  if (typeOfCorrector == 1) return new NOPInsertionDataHazardCorrector(hazardPath);
  if (typeOfCorrector == 2) return new NOPWithForwardingDataHazardCorrector(hazardPath);
  if (typeOfCorrector == 3) return new NOPInsertionDataHazardCorrector(hazardPath);
  if (typeOfCorrector == 4) return new NOPInsertionDataHazardCorrector(hazardPath);

  throw std::exception("not valid type");
}