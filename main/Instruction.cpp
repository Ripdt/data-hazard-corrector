#include "Instruction.h"

#include <string>

Instruction::Instruction(
  const std::string& _instruction
) :
  instruction(_instruction),
  type(ConvertOpCodeFromInstructionToOperationType(_instruction))
{
}

BinaryOperationType Instruction::ConvertOpCodeFromInstructionToOperationType(
  const std::string& instruction
) const
{
  return BinaryOperationType(instruction.substr(BINARY_INSTRUCTION_LENGTH - OPCODE_LENGTH, OPCODE_LENGTH));
}

std::string Instruction::ToString() const
{
  return instruction;
}

std::string Instruction::DestinyRegister() const
{
  return instruction.substr(DESTINY_REGISTER_BEGIN, type.DestinyRegisterLength());
}

std::string Instruction::FirstRegister() const
{
  return instruction.substr(FIRST_REGISTER_BEGIN, type.FirstRegisterLength());
}

std::string Instruction::SecondRegister() const
{
  return instruction.substr(SECOND_REGISTER_BEGIN, type.SecondRegisterLength());
}

const BinaryOperationType& Instruction::Type() const
{
  return type;
}