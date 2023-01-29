#include <iostream>
#include <memory>
#include <optional>
#include <fstream>
#include "src/Common/Automat.h"
#include "src/TextParser/CSVTextParser.h"
#include "src/Converter/MachineConverter.h"
#include "src/MachineSaver/MachineSaver.h"

struct Args
{
    MachineType machineType;
    std::string inputFile;
    std::string outputFile;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    Args args = {};
    const std::string MEALY_MOORE_COMMAND = "mealy-to-moore";
    const std::string MOORE_MEALY_COMMAND = "moore-to-mealy";

    if (argc != 4)
    {
        return std::nullopt;
    }

    if (argv[1] == MEALY_MOORE_COMMAND)
    {
        args.machineType = MachineType::Mealy;
    }
    else if (argv[1] == MOORE_MEALY_COMMAND)
    {
        args.machineType = MachineType::Moore;
    }
    else
    {
        return std::nullopt;
    }

    args.inputFile = argv[2];
    args.outputFile = argv[3];
    return args;
}

bool PrepareStreams(std::ifstream& input, std::ofstream& output, const Args& args)
{
    input.open(args.inputFile);

    if (!input.is_open())
    {
        std::cout << "Input file couldn't be opened" << std::endl;
        return false;
    }

    output.open(args.outputFile);

    if (!output.is_open())
    {
        std::cout << "Output file couldn't be opened" << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        std::cout << "Wrong usage. Example: .exe mealy-to-moore input.csv output.csv" << std::endl;
        return 1;
    }


    std::ifstream input;
    std::ofstream output;
    if (!PrepareStreams(input, output, *args))
    {
        return 1;
    }

    Machine machine;
    if (args->machineType == MachineType::Mealy)
    {
        machine = CSVTextParser::GetMealy(input);
        MachineSaver::SaveMooreMachine(output, MachineConverter::GetMooreMachineFromMealy(machine));
    }
    else
    {
        machine = CSVTextParser::GetMoore(input);
        MachineSaver::SaveMealyMachine(output, MachineConverter::GetMealyMachineFromMoore(machine));
    }

    return 0;
}
