#include <iostream>

#include "DataHazardCorrector.h"
#include "DataHazardCorrectorFactory.h"

#include <conio.h>

void printMainMenu()
{
  std::cout << "******************************************************************************\n";
  std::cout << "**                                                                          **\n";
  std::cout << "**                                                                          **\n";
  std::cout << "**  DATA HAZARD CORRECTOR                                                   **\n";
  std::cout << "**                                                                          **\n";
  std::cout << "**                                                    BY FILIPI             **\n";
  std::cout << "******************************************************************************\n";
  std::cout << "\n\n";
  std::cout << "MAIN MENU:\n\n";
  std::cout << "1 - Correct dump file with NOP\n";
  std::cout << "2 - Help\n";
  std::cout << "3 - Quit\n";
}

void runCorrector()
{
  float clockTime = getClockTime();
  std::string resourcePath = getResourcePath();
  DataHazardCorrector* corrector = DataHazardCorrectorFactory::CreateCorrector(resourcePath);
  corrector->Correct();

  std::cout << "\nCorrected file can be found in " << corrector->CorrectedPath();

  delete corrector;
  _getch();
}

float getClockTime()
{
  double clockTime;

  std::cout << "Insert pipeline's clock time (GHz): ";
  std::cin >> clockTime;

  if (std::cin.fail()) {
    std::cerr << "Invalid value, please enter a valid value again." << std::endl;
    system("cls");
    return getClockTime();
  }

  std::cout << "Clock time configured for: " << clockTime << " GHz" << std::endl;

  return clockTime;
}

std::string getResourcePath()
{
  std::cout << "Insert filename:\n\tEx.: dump-file.txt\n\n";
  std::string line;
  std::getline(std::cin, line);
  std::string resourcePath(".\\resource\\" + line);

  return resourcePath;
}  

void printHelp()
{
  std::cout << "RULES TO USE\n\n";
  std::cout << "\t1. The dump file must be in the \"resource\" directory;\n";
  std::cout << "\t2. The filename can't have special characters;\n";
  std::cout << "\n\nHOW TO USE\n\n";
  std::cout << "\t1. Select the option \"1\" in the Main Menu;\n";
  std::cout << "\t2. Inform the name of the ROM (Ex.: dump.rom);\n";
  std::cout << "\t3. Get the corrected file in the directory specified after the proccess;\n";
  _getch();
}

int main()
{
  char keyPressed = '0';
  while (keyPressed != '3') {
    printMainMenu();
    keyPressed = _getch();
    system("cls");
    if (keyPressed == '1') {
      runCorrector();
    }
    else if (keyPressed == '2') {
      printHelp();
    }
    system("cls");
  }

  return 0;
}