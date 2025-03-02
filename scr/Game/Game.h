#pragma once

#include <glm/vec2.hpp>
#include <array>
#include <memory>

class Tank;
class Level;

class Game {
public:
    Game(const glm::ivec2& windowSize);
    
    ~Game();
    
    void render();
    void update(const double delta);
    void setKey(const int key, const int action);//pressing key treatment
    bool init();//true if all resourses are loaded

    size_t getCurrentLevelWidth() const;
    size_t getCurrentLevelHeight() const;

private:
    std::array<bool, 349> m_keys;//to catch 349 keys from GLFW_KEY...
    enum class EGameState {Active, Pause}; //states of the game
    glm::ivec2 m_windowSize;//window size
    EGameState m_eCurrentGameState;

    //std::unique_ptr <Tank> m_pTank;        
    //std::unique_ptr<Level> m_pLevel;

    std::shared_ptr<Tank> m_pTank;
    std::shared_ptr<Level> m_pLevel;
};