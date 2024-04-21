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

std::string BinaryOperationType::ToString() const
{
  return ToString(value);
}

std::string BinaryOperationType::ToString(
  int type
) const
{
  std::string str("");
  int numbering = 1;
  while (type != 0) {
    const int remainder = type % 2;
    str = std::to_string(remainder) + str;
    type /= 2;
  }

  return std::string(OPCODE_LENGTH - str.length(), '0') + str;
}

size_t BinaryOperationType::FirstRegisterLength() const
{
  switch (value) {
    case R_TYPE:
    case I_TYPE:
    case U_TYPE:
    case J_TYPE:
    case S_TYPE:
    case B_TYPE:
      return 5;
    case NOP:
    default:
      return 0;
  }
}

size_t BinaryOperationType::SecondRegisterLength() const
{
  switch (value) {
  case R_TYPE:
  case S_TYPE:
  case B_TYPE:
    return 5;
  case I_TYPE:
  case U_TYPE:
  case J_TYPE:
  case NOP:
  default:
    return 0;
  }
}

size_t BinaryOperationType::DestinyRegisterLength() const
{
  switch (value) {
    case R_TYPE:
    case I_TYPE:
    case U_TYPE:
    case J_TYPE:
      return 5;
    case S_TYPE:
    case B_TYPE:
    case NOP:
    default:
      return 0;
  }
}
