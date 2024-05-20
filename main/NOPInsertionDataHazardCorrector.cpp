#include "NOPInsertionDataHazardCorrector.h"

#include "Instruction.h"

NOPInsertionDataHazardCorrector::NOPInsertionDataHazardCorrector(
  const std::string hazardPath
) :
  DataHazardCorrector(hazardPath)
{
}

void NOPInsertionDataHazardCorrector::ResolveDataHazards()
{
  Instruction* actualInstruction = nullptr;
  Instruction* previousInstruction = nullptr;
  Instruction* prePreviousInstruction = nullptr;

  for (std::list<Instruction*>::iterator it = instructions.begin(); it != instructions.end(); it++) {
    prePreviousInstruction = previousInstruction;
    previousInstruction = actualInstruction;
    actualInstruction = *it;

    const bool foundConflict2InstructionsBefore = HasConflictWithInstructions(prePreviousInstruction, actualInstruction);
    const bool foundConflictWithPreviousInstructions = HasConflictWithInstructions(previousInstruction, actualInstruction);

    if (foundConflict2InstructionsBefore) {
      InsertFixedInstruction();
      if (foundConflictWithPreviousInstructions) {
        InsertFixedInstruction();
        previousInstruction = nullptr;
      }
    }
    else if (foundConflictWithPreviousInstructions) {
      InsertFixedInstruction();
      InsertFixedInstruction();
      previousInstruction = nullptr;
    }
    correctedInstructions.push_back(*it);
  }
}

void NOPInsertionDataHazardCorrector::InsertFixedInstruction()
{
  auto nop = new Instruction(NoOperationInstruction());
  correctedInstructions.push_back(nop);
}