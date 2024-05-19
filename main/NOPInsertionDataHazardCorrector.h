#ifndef NOPINSERTIONDATAHAZARDCORRECTORH
#define NOPINSERTIONDATAHAZARDCORRECTORH

#include "DataHazardCorrector.h"

class NOPInsertionDataHazardCorrector : public DataHazardCorrector
{
public:
  NOPInsertionDataHazardCorrector(
    const std::string hazardPath
  );

private:
  void ResolveDataHazards() override;

  bool HasConflictWithInstructions(
    Instruction* previousInstruction,
    Instruction* followingInstruction
  ) const;

  void InsertFixedInstruction();

  Instruction* CreateInstruction(
    const std::string& instruction
  ) const override;

  std::string NoOperationInstruction() const override;
};

#endif // NOPINSERTIONDATAHAZARDCORRECTORH




