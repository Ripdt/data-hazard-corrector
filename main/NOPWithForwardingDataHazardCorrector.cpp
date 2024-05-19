#include "NOPWithForwardingDataHazardCorrector.h"

#include "Instruction.h"

NOPWithForwardingDataHazardCorrector::NOPWithForwardingDataHazardCorrector(
  const std::string hazardPath
) :
  NOPInsertionDataHazardCorrector(hazardPath)
{
}

bool NOPWithForwardingDataHazardCorrector::HasConflictWithInstructions(
  Instruction* previousInstruction, 
  Instruction* followingInstruction
) const
{
  if (!NOPInsertionDataHazardCorrector::HasConflictWithInstructions(previousInstruction, followingInstruction)) {
    return false;
  }

  return previousInstruction->Type() == BinaryOperationType::B_TYPE || // branch-use hazard
         previousInstruction->Type() == BinaryOperationType::I2_TYPE;  // load-use hazard
}
