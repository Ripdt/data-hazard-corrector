#include "DataHazardCorrectorFactory.h"

#include "DataHazardCorrector.h"

#include "AssemblyDataHazardCorrector.h"
#include "BinaryDataHazardCorrector.h"
#include "HexadecimalDataHazardCorrector.h"

DataHazardCorrector* DataHazardCorrectorFactory::CreateCorrector(
  const std::string hazardPath
)
{
  if (IsBinary(hazardPath))
    return new BinaryDataHazardCorrector(hazardPath);

  //if (IsHexadecimal(hazardPath))
  //  return new HexadecimalDataHazardCorrector(hazardPath);

  //if (IsAssembly(hazardPath))
  //  return new AssemblyDataHazardCorrector(hazardPath);

  return nullptr;
}

//TODO: check binary file
bool DataHazardCorrectorFactory::IsBinary(
  const std::string& hazardPath
)
{
  return true;
}

//TODO: check hex file
bool DataHazardCorrectorFactory::IsHexadecimal(
  const std::string& hazardPath
)
{
  return false;
}

//TODO: check assembly file
bool DataHazardCorrectorFactory::IsAssembly(
  const std::string& hazardPath
)
{
  return false;
}
