#include "NOPInsertionDataHazardCorrector.h"

#include "BinaryInstruction.h"

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

bool NOPInsertionDataHazardCorrector::HasConflictWithInstructions(
  Instruction* previousInstruction,
  Instruction* followingInstruction
) const
{
  if (previousInstruction == nullptr) {
    return false;
  }

  const std::string destinyRegisterOfPreviousInstruction = previousInstruction->DestinyRegister();
  const bool hasADestiny = destinyRegisterOfPreviousInstruction != "" && destinyRegisterOfPreviousInstruction != "00000";
  if (!hasADestiny) {
    return false;
  }

  const bool firstIsConflicted = followingInstruction->FirstRegister() == destinyRegisterOfPreviousInstruction;
  const bool secondIsConflicted = followingInstruction->SecondRegister() == destinyRegisterOfPreviousInstruction;

  return firstIsConflicted || secondIsConflicted;
}

void NOPInsertionDataHazardCorrector::InsertFixedInstruction()
{
  Instruction* nop = CreateInstruction(NoOperationInstruction());
  correctedInstructions.push_back(nop);
}

Instruction* NOPInsertionDataHazardCorrector::CreateInstruction(
  const std::string& instruction
) const
{
  return new BinaryInstruction(instruction);
}

std::string NOPInsertionDataHazardCorrector::NoOperationInstruction() const
{
  return "00000000000000000000000000010011"; // addi x0, x0, 0
}