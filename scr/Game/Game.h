#pragma once

#include <glm/vec2.hpp>
#include <array>
#include <memory>

class Tank;

class Game {
public:
    Game(const glm::ivec2& windowSize);
    
    ~Game();
    
    void render();
    void update(const uint64_t delta);
    void setKey(const int key, const int action);//pressing key treatment
    bool init();//true if all resourses are loaded

private:
    std::array<bool, 349> m_keys;//to catch 349 keys from GLFW_KEY...
    enum class EGameState {Active, Pause}; //states of the game
    glm::ivec2 m_windowSize;//window size
    EGameState m_eCurrentGameState;
    std::unique_ptr <Tank> m_pTank;    
};