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
  std::vector<std::string> registers;
  std::string lastDestiny;
  for (Instruction* instruction : instructions) {
    const std::string firstRegister = instruction->FirstRegister();
    const std::string secondRegister = instruction->SecondRegister();

    const bool lastInstructionHadADestiny = lastDestiny != "";
    const bool firstIsConflicted = lastInstructionHadADestiny && firstRegister == lastDestiny;
    const bool secondIsConflicted = lastInstructionHadADestiny && secondRegister == lastDestiny;

    if (firstIsConflicted || secondIsConflicted) {
      InsertFixedInstructions();
    }
    correctedInstructions.push_back(instruction);

    lastDestiny = instruction->DestinyRegister();
  }
}

void NOPInsertionDataHazardCorrector::InsertFixedInstructions()
{
  Instruction* nop1 = CreateInstruction(NoOperationInstruction());
  Instruction* nop2 = CreateInstruction(NoOperationInstruction());

  correctedInstructions.push_back(nop1);
  correctedInstructions.push_back(nop2);
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