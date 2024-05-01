#include "DataHazardCorrector.h"

#include <filesystem>
#include <fstream>

#include "Instruction.h"

DataHazardCorrector::DataHazardCorrector(
  const std::string _hazardPath
) :
  hazardPath(_hazardPath),
  correctedPath(GenerateCorrectedPath(_hazardPath))
{
}

DataHazardCorrector::~DataHazardCorrector()
{
  for (Instruction* instruction : correctedInstructions) {
    delete instruction;
  }
  correctedInstructions.clear();
  instructions.clear();
}

std::string DataHazardCorrector::GenerateCorrectedPath(
  const std::string _hazardPath
) const
{
  std::filesystem::path path(_hazardPath);
  path.replace_filename(
    path
      .stem()
      .string()
      .append("_corrected.txt")
  );
  std::filesystem::remove(path);
  return path.string();
}

void DataHazardCorrector::Correct()
{
  GetInstructionsFromHazardFile();
  ResolveDataHazards();
  WriteCorrectedFile();
}

void DataHazardCorrector::GetInstructionsFromHazardFile()
{
  std::ifstream rom(hazardPath);
  if (rom.is_open())
    while (!rom.eof()) {
      std::string line;
      std::getline(rom, line);
      if (!line.empty())
        instructions.push_back(CreateInstruction(line));
    }
  rom.close();
}

void DataHazardCorrector::ResolveDataHazards()
{
  std::vector<std::string> registers;
  std::string lastDestiny;
  for (Instruction* instruction : instructions) {
    const std::string firstRegister = instruction->FirstRegister();
    const std::string secondRegister = instruction->SecondRegister();

    const bool firstIsConflicted = !lastDestiny.empty() && firstRegister.compare(lastDestiny) == 0;
    const bool secondIsConflicted = !lastDestiny.empty() && secondRegister.compare(lastDestiny) == 0;

    if (firstIsConflicted && secondIsConflicted) {
        Instruction* nop = CreateInstruction(NoOperationInstruction());
        correctedInstructions.push_back(nop);
        correctedInstructions.push_back(instruction);
        correctedInstructions.push_back(nop);
    }
    else if (firstIsConflicted || secondIsConflicted) {
        Instruction* nop = CreateInstruction(NoOperationInstruction());
        correctedInstructions.push_back(nop);
        correctedInstructions.push_back(instruction);
    }
    else {
        correctedInstructions.push_back(instruction);
    }

    lastDestiny = instruction->DestinyRegister();
  }
}

double DataHazardCorrector::CalculatePerformanceOverhead() const 
{
  if (instructions.empty()) return 0;
  return 100.0 * (correctedInstructions.size() - instructions.size()) / instructions.size();
}

double DataHazardCorrector::CalculateExecutionTime(
    const double clockTime
) const 
{
  return correctedInstructions.size() * clockTime;
}

void DataHazardCorrector::WriteCorrectedFile() const
{
  std::ofstream correctedFile(correctedPath);
  if (correctedFile.is_open())
    for (const Instruction* instruction : correctedInstructions)
        correctedFile << instruction->ToString() << std::endl;
  correctedFile.close();
}

std::string DataHazardCorrector::CorrectedPath() const
{
  return correctedPath;
}
