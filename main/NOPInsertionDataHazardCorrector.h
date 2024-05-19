#ifndef NOPINSERTIONDATAHAZARDCORRECTORH
#define NOPINSERTIONDATAHAZARDCORRECTORH

#include "DataHazardCorrector.h"

class NOPInsertionDataHazardCorrector : public DataHazardCorrector
{
public:
  NOPInsertionDataHazardCorrector(
    const std::string hazardPath
  );

protected:
  virtual bool HasConflictWithInstructions(
    Instruction* previousInstruction,
    Instruction* followingInstruction
  ) const;

private:
  void ResolveDataHazards() override;

  void InsertFixedInstruction();

  Instruction* CreateInstruction(
    const std::string& instruction
  ) const override;

  std::string NoOperationInstruction() const override;
};

#endif // NOPINSERTIONDATAHAZARDCORRECTORH




