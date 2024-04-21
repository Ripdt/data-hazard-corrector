#include "Instruction.h"

#include <string>

Instruction::Instruction(
  const std::string& _instruction
) :
  instruction(_instruction)
{
}

std::string Instruction::ToString() const
{
  return instruction;
}