#include <iostream>
#include <conio.h>

#include "DataHazardCorrector.h"
#include "DataHazardCorrectorFactory.h"

void printMainMenu()
{
  std::cout << "******************************************************************************\n";
  std::cout << "**                                                                          **\n";
  std::cout << "**                                                                          **\n";
  std::cout << "**  DATA HAZARD CORRECTOR                                                   **\n";
  std::cout << "**                                                                          **\n";
  std::cout << "**                       BY FELIPE LUZ, FILIPI DA COSTA & JOAO P PRUDENCIO  **\n";
  std::cout << "******************************************************************************\n";
  std::cout << "\n\n";
  std::cout << "MAIN MENU:\n\n";
  std::cout << "1 - Correct dump file with NOP\n";
  std::cout << "2 - Help\n";
  std::cout << "3 - Quit\n";
}

void printPerformanceMetrics(DataHazardCorrector* corrector, double clockTime)
{
    if (corrector == nullptr) {
        std::cerr << "Error: Data hazard corrector is not initialized." << std::endl;
        return;
    }

    // Display performance metrics
    std::cout << "Original Instructions: " << corrector->OriginalInstructionCount() << "\n";
    std::cout << "Corrected Instructions: " << corrector->CorrectedInstructionCount() << "\n";
    std::cout << "Performance Overhead: " << corrector->CalculatePerformanceOverhead() << "%\n";
    std::cout << "New Estimated Execution Time: " << corrector->CalculateExecutionTime(clockTime) << " ns\n";
}


float getClockTime()
{
    double clockTime = 0;

    std::cout << "Insert pipeline's clock time (ns): ";
    std::cin >> clockTime;

    if (std::cin.fail()) {
        std::cin.clear(); // Clear error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore incorrect input until the end of the line
        std::cerr << "Invalid value, please enter a valid numeric value." << std::endl;
        system("cls"); // Clear the screen
        return getClockTime(); // Recursively call getClockTime
    }

    std::cout << "Clock time configured for: " << clockTime << " ns" << std::endl;
    return clockTime;
}

std::string getResourcePath()
{
  std::cout << "Insert filename:\n\tEx.: dump-file.txt\n\n";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore any leftover characters in the buffer
  std::string line;
  std::getline(std::cin, line);
  std::string resourcePath(".\\resource\\" + line); //"C:\Users\felip\data-hazard-corrector\main\resource\instructions.txt"

  return resourcePath;
}

int getTypeOfCorrector()
{
  std::cout << "\nInsert which option of Data Hazard Corrector you want:\n\n";
  std::cout << "\t1 - No Hardware Solutions for Conflicts (NOPs Only)\n";
  std::cout << "\t2 - Forwarding Implemented (Use NOPs as Needed)\n";
  std::cout << "\t3 - No Hardware Solutions for Conflicts (Reorder and NOPs)\n";
  std::cout << "\t4 - Forwarding Implemented (Reorder and NOPs)\n";

  int typeOfCorrector;
  std::cin >> typeOfCorrector;

  if (std::cin.fail() || typeOfCorrector < 1 || typeOfCorrector > 4) {
    std::cin.clear(); // Clear error state
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore incorrect input until the end of the line
    std::cerr << "Invalid value, please enter a valid option." << std::endl;
    system("cls"); // Clear the screen
    return getTypeOfCorrector();
  }

  return typeOfCorrector;
}

void runCorrector()
{
  const float clockTime = getClockTime();
  const std::string resourcePath = getResourcePath();
  const int type = getTypeOfCorrector();
  DataHazardCorrector* corrector = DataHazardCorrectorFactory::CreateCorrector(type, resourcePath);
  corrector->Correct();

  std::cout << "\nCorrected file can be found in " << corrector->CorrectedPath() << "\n";
  printPerformanceMetrics(corrector, clockTime);

  delete corrector;
  _getch();
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