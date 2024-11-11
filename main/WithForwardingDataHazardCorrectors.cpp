#include "WithForwardingDataHazardCorrectors.h"

#include "Instruction.h"

//--------------------------------------------------------------------------------------------------------------

namespace Util {
  bool IsLoadOrBranchUseConflict(
    Instruction* previousInstruction
  )
  {
    return previousInstruction->Type() == BinaryOperationType::B_TYPE || // branch-use hazard
      previousInstruction->Type() == BinaryOperationType::I2_TYPE;  // load-use hazard
  }
}

//--------------------------------------------------------------------------------------------------------------

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

  return Util::IsLoadOrBranchUseConflict(previousInstruction);
}

//--------------------------------------------------------------------------------------------------------------

ReorderWithForwardingDataHazardCorrector::ReorderWithForwardingDataHazardCorrector(
  const std::string hazardPath
) :
  ReorderDataHazardCorrector(hazardPath)
{
}

bool ReorderWithForwardingDataHazardCorrector::HasConflictWithInstructions(
  Instruction* previousInstruction,
  Instruction* followingInstruction
) const
{
  if (!ReorderDataHazardCorrector::HasConflictWithInstructions(previousInstruction, followingInstruction)) {
    return false;
  }

  return Util::IsLoadOrBranchUseConflict(previousInstruction);
}

//--------------------------------------------------------------------------------------------------------------
