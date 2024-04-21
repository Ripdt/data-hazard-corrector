#ifndef BINARYINSTRUCTIONH
#define BINARYINSTRUCTIONH

#include "Instruction.h"
#include "BinaryOperationType.h"

class BinaryInstruction : public Instruction
{
public:
  BinaryInstruction(
    const std::string& _instruction
  );

  std::string DestinyRegister() const override;

  std::string FirstRegister() const override;

  std::string SecondRegister() const override;

private:
  BinaryOperationType ConvertOpCodeFromInstructionToOperationType(
    const std::string& _instruction
  ) const;

  const BinaryOperationType type;
};

#endif // !BINARYINSTRUCTIONH