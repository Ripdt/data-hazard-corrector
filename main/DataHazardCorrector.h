#ifndef DATAHAZARDCORRECTORH
#define DATAHAZARDCORRECTORH

#include <string>
#include <list>

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
    double CalculatePerformanceOverhead() const;
    double CalculateExecutionTime(double clockTime) const;
    size_t OriginalInstructionCount() const { return instructions.size(); }
    size_t CorrectedInstructionCount() const { return correctedInstructions.size(); }

protected:
    std::string NoOperationInstruction() const;

    virtual bool HasConflictWithInstructions(
      Instruction* previousInstruction,
      Instruction* followingInstruction
    ) const;

    const std::string hazardPath;
    const std::string correctedPath;

    std::list<Instruction*> instructions;
    std::list<Instruction*> correctedInstructions;

private:
    std::string GenerateCorrectedPath(
        const std::string _hazardPath
    ) const;

    void InsertFixedInstructions();

    void GetInstructionsFromHazardFile();

    virtual void ResolveDataHazards() = 0;

    void WriteCorrectedFile() const;
};

#endif // DATAHAZARDCORRECTORH