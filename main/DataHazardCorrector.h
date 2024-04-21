#ifndef DATAHAZARDCORRECTORH
#define DATAHAZARDCORRECTORH

#include <string>
#include <vector>

class Instruction;

class DataHazardCorrector
{
public:
  DataHazardCorrector(
    const std::string _hazardPath
  );

  ~DataHazardCorrector();

  void Correct();

  std::string CorrectedPath() const;

protected:
  const std::string hazardPath;
  const std::string correctedPath;

  std::vector<Instruction*> instructions;
  std::vector<Instruction*> correctedInstructions;

private:
  std::string GenerateCorrectedPath(
    const std::string _hazardPath
  ) const;

  void GetInstructionsFromHazardFile();

  virtual Instruction* CreateInstruction(
    const std::string& instruction
  ) const = 0;

  void ResolveDataHazards();

  virtual std::string NoOperationInstruction() const = 0;

  void WriteCorrectedFile() const;
};

#endif // DATAHAZARDCORRECTORH