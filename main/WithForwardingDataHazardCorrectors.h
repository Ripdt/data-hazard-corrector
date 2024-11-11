#ifndef NOPWITHFORWARDINGDATAHAZARDCORRECTORH
#define NOPWITHFORWARDINGDATAHAZARDCORRECTORH

#include "NOPInsertionDataHazardCorrector.h"
#include "ReorderDataHazardCorrector.h"

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

//--------------------------------------------------------------------------------------------------------------

class ReorderWithForwardingDataHazardCorrector : public ReorderDataHazardCorrector
{
public:
  ReorderWithForwardingDataHazardCorrector(
    const std::string hazardPath
  );

private:
  bool HasConflictWithInstructions(
    Instruction* previousInstruction,
    Instruction* followingInstruction
  ) const override;
};

#endif
