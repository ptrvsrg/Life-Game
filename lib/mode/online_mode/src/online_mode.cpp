#include "online_mode.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <regex>
#include <termcap.h>
#include <unistd.h>

std::vector<std::string> examples = {
    "examples/beacon.life",
    "examples/blinker.life",
    "examples/block.life",
    "examples/glider.life",
    "examples/pentadecathlon.life",
    "examples/sraceship.life",
    "examples/tub.life"
};

OnlineMode::OnlineMode(std::string input_file)
    : m_input_file(std::move(input_file)) {}

void OnlineMode::Launch()
{
    SetInputFile();
    InitUniverse();

    while (true)
    {
        std::smatch smatch;
        std::string command;
        std::getline(std::cin, command);

        if (command.empty())
            continue;
        else if (command == "exit")
            break;
        else if (std::regex_search(command, smatch, std::regex("^(dump )(\\S*)")))
            SaveToFile(smatch[2].str());
        else if (std::regex_search(command, std::regex("^tick")))
        {
            int iterations = 1;
            if (std::regex_search(command, smatch, std::regex("^(tick )(\\S*)")))
                iterations = std::strtoul(smatch[2].str().c_str(),
                                          nullptr,
                                          0);

            for (int i = 0; i < iterations; ++i)
                PrintGeneration();
        }
        else if (command == "help")
            std::cout << "dump <filename> - save universe to file;\n"
                         "tick <n> - calculate n (default 1) iterations and print result;\n"
                         "exit - finish game;\n"
                         "help - print help about commands;\n";
        else
            std::clog << "Warning: Unrecognized command, "
                         "enter \"help\" to find out about the recognized commands\n";
    }
}

void OnlineMode::SetInputFile()
{
    if (m_input_file.empty())
    {
        std::clog << "Warning: Input file is missing, "
                     "it will be selected from default examples\n";
        srandom(time(nullptr));
        int idx = random() % examples.size();
        m_input_file = examples[idx];
    }
}

void OnlineMode::InitUniverse()
{
    LifeFile life_file(m_input_file, LifeFile::Mode::IN);
    m_universe = life_file.ReadUniverse();
}

void OnlineMode::PrintGeneration()
{
    char buffer[256];
    tgetent(buffer, getenv("TERM"));
    system("cls");
    std::cout << m_universe;
    m_universe.GenerateNextGeneration();
    usleep(1);
}

void OnlineMode::SaveToFile(const std::string & output_file)
{
    LifeFile life_file(output_file, LifeFile::Mode::OUT);
    life_file.WriteUniverse(m_universe);
}
