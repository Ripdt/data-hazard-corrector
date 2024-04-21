#ifndef BINARYDATAHAZARDCORRECTORH
#define BINARYDATAHAZARDCORRECTORH

#include "DataHazardCorrector.h"

class BinaryDataHazardCorrector : public DataHazardCorrector
{
public:
  BinaryDataHazardCorrector(
    const std::string hazardPath
  );

private:
  Instruction* CreateInstruction(
    const std::string& instruction
  ) const override;

  std::string NoOperationInstruction() const override;
};

#endif // BINARYDATAHAZARDCORRECTORH




