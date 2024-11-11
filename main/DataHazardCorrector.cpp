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
      .append("_fixed.txt")
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
        instructions.push_back(new Instruction(line));
    }

  rom.close();
}

bool DataHazardCorrector::HasConflictWithInstructions(
  Instruction* previousInstruction,
  Instruction* followingInstruction
) const
{
  if (previousInstruction == nullptr) {
    return false;
  }

  const std::string destinyRegisterOfPreviousInstruction = previousInstruction->DestinyRegister();
  const bool hasADestiny = destinyRegisterOfPreviousInstruction != "" && destinyRegisterOfPreviousInstruction != "00000";
  if (!hasADestiny) {
    return false;
  }

  const bool firstIsConflicted = followingInstruction->FirstRegister() == destinyRegisterOfPreviousInstruction;
  const bool secondIsConflicted = followingInstruction->SecondRegister() == destinyRegisterOfPreviousInstruction;

  return firstIsConflicted || secondIsConflicted;
}

void DataHazardCorrector::WriteCorrectedFile() const
{
  std::ofstream correctedFile(correctedPath);
  if (correctedFile.is_open())
    for (const Instruction* instruction : correctedInstructions)
      correctedFile << instruction->ToString() << std::endl;
  correctedFile.close();
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

std::string DataHazardCorrector::CorrectedPath() const
{
  return correctedPath;
}

std::string DataHazardCorrector::NoOperationInstruction() const
{
  return "00000000000000000000000000010011"; // addi x0, x0, 0
}
