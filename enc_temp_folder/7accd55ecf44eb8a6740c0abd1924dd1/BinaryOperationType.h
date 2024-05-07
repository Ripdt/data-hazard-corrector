#ifndef BINARYOPERATIONTYPEH
#define BINARYOPERATIONTYPEH

#define BINARY_INSTRUCTION_LENGTH 32
#define OPCODE_LENGTH 7
#define SECOND_REGISTER_BEGIN   BINARY_INSTRUCTION_LENGTH - 25
#define FIRST_REGISTER_BEGIN    BINARY_INSTRUCTION_LENGTH - 20
#define DESTINY_REGISTER_BEGIN  BINARY_INSTRUCTION_LENGTH - 12

#include <string>

class BinaryOperationType {
public:
  enum {

    U_LUI_TYPE   = 0b00110111,
    U_AUIPC_TYPE = 0b00010111,

    J_JAL_TYPE = 0b01101111,
    J_JALR_TYPE = 0b01100111,

    B_TYPE = 0b01100011,

    S_TYPE = 0b00100011,

    I_TYPE            = 0b00010011,
    I2_TYPE           = 0b00000011,
    I3_FENCE_TYPE     = 0b00001111,
    I3_EXCEPTION_TYPE = 0b01110011,

    R_TYPE = 0b00110011,

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

  size_t FirstRegisterLength() const;

  size_t SecondRegisterLength() const;

  size_t DestinyRegisterLength() const;

private:

  const int value;
};

#endif // !BINARYOPERATIONTYPEH




