#ifndef INSTRUCTIONH
#define INSTRUCTIONH

#include <string>

class Instruction
{
public:
  Instruction(
    const std::string& _instruction
  );

  std::string ToString() const;

  virtual std::string DestinyRegister() const = 0;

  virtual std::string FirstRegister() const = 0;

  virtual std::string SecondRegister() const = 0;

protected:
  const std::string instruction;
};

#endif // !INSTRUCTIONH