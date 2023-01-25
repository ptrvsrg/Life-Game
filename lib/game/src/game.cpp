#include "game.h"
#include "abstract_mode.h"

Game::Game(std::string input_file,
           std::string output_file,
           int iterations)
    : m_input_file(std::move(input_file)),
      m_output_file(std::move(output_file)),
      m_iterations(iterations) {}

void Game::Launch()
{
    // Create mode
    ModePtr mode = AbstractMode::CreateMode(m_input_file,
                                            m_output_file,
                                            m_iterations);
    // Launch mode
    mode->Launch();
}
