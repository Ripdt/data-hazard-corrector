#include "BinaryDataHazardCorrector.h"

#include "BinaryInstruction.h"

BinaryDataHazardCorrector::BinaryDataHazardCorrector(
  const std::string hazardPath
) :
  DataHazardCorrector(hazardPath)
{
}

Instruction* BinaryDataHazardCorrector::CreateInstruction(
  const std::string& instruction
) const
{
  return new BinaryInstruction(instruction);
}

std::string BinaryDataHazardCorrector::NoOperationInstruction() const
{
  return std::string(BINARY_INSTRUCTION_LENGTH, '0');
}