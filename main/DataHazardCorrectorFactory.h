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

  DataHazardCorrectorFactory() = default;
};

#endif // !DATAHAZARDCORRECTORFACTORYH