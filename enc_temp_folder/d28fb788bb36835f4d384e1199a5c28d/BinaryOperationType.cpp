#include "BinaryOperationType.h"

BinaryOperationType::BinaryOperationType(
  const std::string& opcode
) :
  value(ConvertString(opcode))
{
}

bool BinaryOperationType::operator==(
  const BinaryOperationType& otherValue
  ) const
{
  return *this == otherValue.value;
}

bool BinaryOperationType::operator==(
  const int otherValue
  ) const
{
  return value == otherValue;
}

int BinaryOperationType::ConvertString(
  const std::string& opcode
)
{
  return std::stoi(opcode, nullptr, 2);
}

size_t BinaryOperationType::FirstRegisterLength() const
{
  switch (value) {
    case U_LUI_TYPE:
    case U_AUIPC_TYPE:
    case J_JALR_TYPE:
    case I_TYPE:
    case I2_TYPE:
    case I3_FENCE_TYPE:
    case I3_EXCEPTION_TYPE:
    case B_TYPE:
    case S_TYPE:
    case R_TYPE:
      return 5;
    case J_JAL_TYPE:
    case NOP:
    default:
      return 0;
  }
}

size_t BinaryOperationType::SecondRegisterLength() const
{
  switch (value) {
  case B_TYPE:
  case S_TYPE:
  case R_TYPE:
    return 5;
  case U_LUI_TYPE:
  case U_AUIPC_TYPE:
  case J_JAL_TYPE:
  case J_JALR_TYPE:
  case I_TYPE:
  case I2_TYPE:
  case I3_FENCE_TYPE:
  case I3_EXCEPTION_TYPE:
  case NOP:
  default:
    return 0;
  }
}

size_t BinaryOperationType::DestinyRegisterLength() const
{
  switch (value) {
    case U_LUI_TYPE:
    case U_AUIPC_TYPE:
    case J_JAL_TYPE:
    case J_JALR_TYPE:
    case I_TYPE:
    case I2_TYPE:
    case I3_FENCE_TYPE:
    case I3_EXCEPTION_TYPE:
    case R_TYPE:
      return 5;
    case B_TYPE:
    case S_TYPE:
    case NOP:
    default:
      return 0;
  }
}
