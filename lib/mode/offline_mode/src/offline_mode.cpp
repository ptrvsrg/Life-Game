#include "offline_mode.h"

OfflineMode::OfflineMode(std::string input_file,
                         std::string output_file,
                         size_t iterations)
    : m_input_file(std::move(input_file)),
      m_output_file(std::move(output_file)),
      m_iterations(iterations) {}

void OfflineMode::Launch()
{
    // Init universe
    InitUniverse();

    // Generate some next generations
    for (size_t i = 0; i < m_iterations; ++i)
        m_universe.GenerateNextGeneration();

    // Save to output file
    SaveToFile();
}

void OfflineMode::InitUniverse()
{
    // Create input life file stream
    ILifeFile i_life_file(m_input_file);

    // Read universe from life file
    m_universe = i_life_file.ReadUniverse();
}

void OfflineMode::SaveToFile()
{
    // Create output life file stream
    OLifeFile o_life_file(m_output_file);

    // Write universe to life file
    o_life_file.WriteUniverse(m_universe);
}