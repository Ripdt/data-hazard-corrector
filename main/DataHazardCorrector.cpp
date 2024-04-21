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
      .filename()
      .string()
      .append("_corrected")
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
  int i = 0;
  for (Instruction* instruction : instructions) {
    const std::string firstRegister = instruction->FirstRegister();
    const bool firstIsConflicted = !lastDestiny.empty() && firstRegister.compare(lastDestiny) == 0;

    const std::string secondRegister = instruction->SecondRegister();
    const bool secondIsConflicted = !lastDestiny.empty() && secondRegister.compare(lastDestiny) == 0;

    if (firstIsConflicted || secondIsConflicted) {
      Instruction* nop = CreateInstruction(NoOperationInstruction());
      correctedInstructions.push_back(nop);
    }
    correctedInstructions.push_back(instruction);
    lastDestiny = instruction->DestinyRegister();
  }
}

void DataHazardCorrector::WriteCorrectedFile() const
{
  std::ofstream corrected(correctedPath);
  if (corrected.is_open())
    for (const Instruction* instruction : correctedInstructions)
      corrected << instruction->ToString() << std::endl;
  corrected.close();
}

std::string DataHazardCorrector::CorrectedPath() const
{
  return correctedPath;
}
