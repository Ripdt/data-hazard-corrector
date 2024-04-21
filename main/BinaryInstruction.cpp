#include "BinaryInstruction.h"

BinaryInstruction::BinaryInstruction(
  const std::string& _instruction
) :
  Instruction(_instruction),
  type(ConvertOpCodeFromInstructionToOperationType(instruction))
{
}

BinaryOperationType BinaryInstruction::ConvertOpCodeFromInstructionToOperationType(
  const std::string& instruction
) const
{
  return BinaryOperationType(instruction.substr(BINARY_INSTRUCTION_LENGTH - OPCODE_LENGTH, OPCODE_LENGTH));
}

std::string BinaryInstruction::DestinyRegister() const
{
  return instruction.substr(DESTINY_REGISTER_BEGIN, type.DestinyRegisterLength());
}

std::string BinaryInstruction::FirstRegister() const
{
  return instruction.substr(FIRST_REGISTER_BEGIN, type.FirstRegisterLength());
}

std::string BinaryInstruction::SecondRegister() const
{
  return instruction.substr(SECOND_REGISTER_BEGIN, type.SecondRegisterLength());
}
