#ifndef DATAHAZARDCORRECTORFACTORYH
#define DATAHAZARDCORRECTORFACTORYH

#include <string>

class DataHazardCorrector;

class DataHazardCorrectorFactory
{
public:
  static DataHazardCorrector* CreateCorrector(
    const int typeOfCorrector,
    const std::string hazardPath
  );

private:

  DataHazardCorrectorFactory() = default;
};

#endif // !DATAHAZARDCORRECTORFACTORYH