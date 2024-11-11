#include "ReorderDataHazardCorrector.h"

#include <algorithm>
#include "Instruction.h"

ReorderDataHazardCorrector::ReorderDataHazardCorrector(
  const std::string _hazardPath
) :
  NOPInsertionDataHazardCorrector(_hazardPath)
{
}

void ReorderDataHazardCorrector::ResolveDataHazards()
{
  typedef std::list<Instruction*>::iterator iter;

  Instruction* previousInstruction = nullptr;
  for (iter it = instructions.begin(); it != instructions.end(); it++) {
    if (HasConflictWithInstructions(previousInstruction, *it)) {
      bool swapped = false;
      for (iter jt = it; jt != instructions.end(); jt++) {
        if (!HasConflictWithInstructions(previousInstruction, *jt) && !HasConflictWithInstructions(*jt, *it)) {
          std::iter_swap(it, jt);
          break;
        }
      }
    }
    previousInstruction = *it;
  }

  NOPInsertionDataHazardCorrector::ResolveDataHazards();
}
