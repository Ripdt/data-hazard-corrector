#pragma once
#include "NOPInsertionDataHazardCorrector.h"

class NOPWithForwardingDataHazardCorrector : public NOPInsertionDataHazardCorrector
{
public:
  NOPWithForwardingDataHazardCorrector(
    const std::string hazardPath
  );

private:
  bool HasConflictWithInstructions(
    Instruction* previousInstruction,
    Instruction* followingInstruction
  ) const override;
};

