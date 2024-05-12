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
    double CalculatePerformanceOverhead() const;
    double CalculateExecutionTime(double clockTime) const;
    size_t OriginalInstructionCount() const { return instructions.size(); }
    size_t CorrectedInstructionCount() const { return correctedInstructions.size(); }

protected:
    const std::string hazardPath;
    const std::string correctedPath;

    std::vector<Instruction*> instructions;
    std::vector<Instruction*> correctedInstructions;

private:
    std::string GenerateCorrectedPath(
        const std::string _hazardPath
    ) const;

    void InsertFixedInstructions();

    void GetInstructionsFromHazardFile();

    virtual Instruction* CreateInstruction(
        const std::string& instruction
    ) const = 0;

    virtual void ResolveDataHazards() = 0;

    virtual std::string NoOperationInstruction() const = 0;

    void WriteCorrectedFile() const;
};

#endif // DATAHAZARDCORRECTORH