#ifndef INSTRUCTIONH
#define INSTRUCTIONH

#include <string>

#include "BinaryOperationType.h"

class Instruction
{
public:
  Instruction(
    const std::string& _instruction
  );

  std::string ToString() const;

  std::string DestinyRegister() const;

  std::string FirstRegister() const;

  std::string SecondRegister() const;

  const BinaryOperationType& Type() const;

private:
  BinaryOperationType ConvertOpCodeFromInstructionToOperationType(
    const std::string& _instruction
  ) const;

  const BinaryOperationType type;

protected:
  const std::string instruction;
};

#endif // !INSTRUCTIONH