#ifndef DATAHAZARDCORRECTORFACTORYH
#define DATAHAZARDCORRECTORFACTORYH

#include <string>

class DataHazardCorrector;

class DataHazardCorrectorFactory
{
public:
  static DataHazardCorrector* CreateCorrector(
    const std::string hazardPath
  );

private:
  static bool IsBinary(
    const std::string& hazardPath
  );

  static bool IsHexadecimal(
    const std::string& hazardPath
  );

  static bool IsAssembly(
    const std::string& hazardPath
  );

  DataHazardCorrectorFactory() = default;
};

#endif // !DATAHAZARDCORRECTORFACTORYH