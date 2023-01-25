#include "online_mode.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <regex>
#include <unistd.h>

// Life file examples
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
    // Set input file if it is missing
    SetInputFile();

    // Init universe
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

            // Case: some next generations need to be printed
            if (std::regex_search(command, smatch, std::regex("^(tick )(\\S*)")))
                iterations = std::strtoul(smatch[2].str().c_str(),
                                          nullptr,
                                          0);

            // Print some next generations
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
        // Warnings
        std::clog << "Warning: Input file is missing, "
                     "it will be selected from default examples\n";

        // Choose random life file example
        srandom(time(nullptr));
        int idx = random() % examples.size();
        m_input_file = examples[idx];
    }
}

void OnlineMode::InitUniverse()
{
    // Create input life file stream
    ILifeFile i_life_file(m_input_file);

    // Read universe from life file
    m_universe = i_life_file.ReadUniverse();

    // Print universe name
    std::cout << "Universe name: " << m_universe.GetName() << std::endl;

    // Print universe size
    std::cout << "Universe height: " << m_universe.GetHeight() << std::endl;
    std::cout << "Universe width: " << m_universe.GetWidth() << std::endl;
}

void OnlineMode::PrintGeneration()
{
    // Clear screen
    std::cout << "\x1B[2J\x1B[H";

    // Print cells
    auto cells = m_universe.GetCells();
    for (size_t i = 0; i < m_universe.GetHeight(); ++i)
    {
        for (size_t j = 0; j < m_universe.GetWidth(); ++j)
        {
            Cell cell = {j, i};
            if (cells.find(cell) != cells.end())
                std::cout << "#";
            else
                std::cout << " ";
        }

        std::cout << std::endl;
    }

    // Timeout
    sleep(1);

    // Generate next generation
    m_universe.GenerateNextGeneration();
}

void OnlineMode::SaveToFile(const std::string & output_file)
{
    // Create output life file stream
    OLifeFile o_life_file(output_file);

    // Write universe to life file
    o_life_file.WriteUniverse(m_universe);
}
