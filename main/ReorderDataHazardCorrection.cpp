#include "ReorderDataHazardCorrection.h"

#include <algorithm>
#include "Instruction.h"

ReorderDataHazardCorrection::ReorderDataHazardCorrection(
  const std::string _hazardPath
) :
  DataHazardCorrector(_hazardPath)
{
}

void ReorderDataHazardCorrection::ResolveDataHazards()
{
  typedef std::list<Instruction*>::iterator iter;
  Instruction* previousInstruction = nullptr;
  for (iter it = instructions.begin(); it != instructions.end(); it++) {
    if (HasConflictWithInstructions(previousInstruction, *it)) {
      bool swapped = false;
      for (iter jt = it; jt != instructions.end(); jt++) {
        if (!HasConflictWithInstructions(previousInstruction, *jt) && !HasConflictWithInstructions(*jt, *it)) {
          correctedInstructions.push_back(*jt);
          std::iter_swap(it, jt); // Swap the position of jt and it in list instructions
          swapped = true;
          break;
        }
      }
      if (!swapped) {
        auto nop = new Instruction(NoOperationInstruction());
        correctedInstructions.push_back(nop);
        correctedInstructions.push_back(*it);
      }
    }
    else {
      correctedInstructions.push_back(*it);
    }
    previousInstruction = *it;
  }
}
