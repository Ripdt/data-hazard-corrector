#ifndef BINARYOPERATIONTYPE
#define BINARYOPERATIONTYPE

#define BINARY_INSTRUCTION_LENGTH 32
#define OPCODE_LENGTH 7
#define SECOND_REGISTER_BEGIN   BINARY_INSTRUCTION_LENGTH - 25
#define FIRST_REGISTER_BEGIN    BINARY_INSTRUCTION_LENGTH - 20
#define DESTINY_REGISTER_BEGIN  BINARY_INSTRUCTION_LENGTH - 12

#include <string>

class BinaryOperationType {
public:
  enum {
    R_TYPE = 0b00110011,
    I_TYPE = 0b00010011,
    S_TYPE = 0b00100011,
    B_TYPE = 0b01100011,
    U_TYPE = 0b00110111,
    J_TYPE = 0b01101111,
    NOP    = 0
  };

  BinaryOperationType(
    const std::string& opcode
  );

  bool operator==(
    const BinaryOperationType& otherValue
    ) const;

  bool operator==(
    const int otherValue
    ) const;

  int ConvertString(
    const std::string& opcode
  );

  std::string ToString() const;

  size_t FirstRegisterLength() const;

  size_t SecondRegisterLength() const;

  size_t DestinyRegisterLength() const;

private:
  std::string ToString(
    int type
  ) const;

  const int value;
};

#endif // !BINARYOPERATIONTYPE




