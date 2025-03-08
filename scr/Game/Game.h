#pragma once

#include <glm/vec2.hpp>
#include <array>
#include <memory>

//class StartScreen;
//class Tank;
//class Level;

class IGameState;

namespace RenderEngine {
    class ShaderProgram;
}

class Game {
public:
    Game(const glm::uvec2& windowSize);
    
    ~Game();
    
    void render();
    void update(const double delta);
    void setKey(const int key, const int action);//pressing key treatment
    bool init();//true if all resourses are loaded

    unsigned int getCurrentWidth() const;
    unsigned int getCurrentHeight() const;
    
    void startNewLevel(const size_t level);
    void updateViewport();
    void setWindowSize(const glm::uvec2& windowSize);

private:    
    enum class EGameState {//states of the game
        StartScreen,
        LevelStart,
        Level,
        Pause,
        Scores,
        GameOver
    }; 
    
    std::array<bool, 349> m_keys;//to catch 349 keys from GLFW_KEY...
    glm::ivec2 m_windowSize;//window size
    EGameState m_eCurrentGameState;;

    /*std::shared_ptr<Tank> m_pTank;
    std::shared_ptr<Level> m_pLevel;
    std::shared_ptr<StartScreen> m_pStartScreen;*/

    std::shared_ptr<IGameState> m_pCurrentGameState;
    std::shared_ptr<RenderEngine::ShaderProgram> m_pSpriteShaderProgram;
};