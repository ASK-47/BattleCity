#include "Game.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "GameObjects/Tank.h"
#include "GameObjects/Bullet.h"
#include "GameStates/Level.h"
#include "GameStates/StartScreen.h"
#include "../Physics/PhysicsEngine.h"
#include "../Renderer/Renderer.h"

#include "GameObjects/Bullet.h"
#include <GLFW/glfw3.h>


Game::Game(const glm::uvec2& windowSize)
    : m_windowSize(windowSize)
    , m_eCurrentGameState(EGameState::StartScreen)
    , m_currentLevelIndex(0) {//CTOR to init state and window size    
    m_keys.fill(false);//set all keys to 0,0,0...(see set key for action)
}

void Game::setWindowSize(const glm::uvec2& windowSize) {
    m_windowSize = windowSize;
    updateViewport();
}

Game::~Game() {}

void Game::render() {      
    m_pCurrentGameState->render();
}

void Game::updateViewport() {
    const float level_aspect_ratio = static_cast<float>(getCurrentWidth()) / getCurrentHeight();
    unsigned int viewPortWidth = m_windowSize.x;
    unsigned int viewPortHeight = m_windowSize.y;
    unsigned int viewPortLeftOffset = 0;
    unsigned int viewPortBottomOffset = 0;

    if (static_cast<float>(m_windowSize.x) / m_windowSize.y > level_aspect_ratio) {
        viewPortWidth = static_cast<unsigned int>(m_windowSize.y * level_aspect_ratio);
        viewPortLeftOffset = (m_windowSize.x - viewPortWidth) / 2;
    }
    else {
        viewPortHeight = static_cast<unsigned int>(m_windowSize.x / level_aspect_ratio);
        viewPortBottomOffset = (m_windowSize.y - viewPortHeight) / 2;
    }

    RenderEngine::Renderer::setViewport(viewPortWidth, viewPortHeight, viewPortLeftOffset, viewPortBottomOffset);

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(getCurrentWidth()), 0.f, static_cast<float>(getCurrentHeight()), -100.f, 100.f);
    m_pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);
}

void Game::startNewLevel(const size_t level, const EGameMode eGameMode) {
    //auto pLevel = std::make_shared<Level>(ResourceManager::getLevels()[0]);
    m_currentLevelIndex = level;
    auto pLevel = std::make_shared<Level>(ResourceManager::getLevels()[m_currentLevelIndex], eGameMode);
    m_pCurrentGameState = pLevel;
    Physics::PhysicsEngine::setCurrentLevel(pLevel);
    updateViewport();
}

void Game::nextLevel(const EGameMode eGameMode) {
    startNewLevel(++m_currentLevelIndex, eGameMode);
}

void Game::update(const double delta) {
    m_pCurrentGameState->processInput(m_keys);
    m_pCurrentGameState->update(delta); 
}

void Game::setKey(const int key, const int action) {
    m_keys[key] = action;//press key =>  m_keys == true, unpress key =>  m_keys == false (see g_game.setKey(key, action) in main())
}

bool Game::init() { 
    ResourceManager::loadJSONResources("res/resources.json");
    m_pSpriteShaderProgram = ResourceManager::getShaderProgram("spriteShader");
    if (!m_pSpriteShaderProgram) {
        std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
        return false;//-1 was changed for false
    }
    
    m_pSpriteShaderProgram->use();
    
    m_pSpriteShaderProgram->setInt("tex", 0);    
    
    m_pCurrentGameState = std::make_shared<StartScreen>(ResourceManager::getStartScreen(), this);
    
    setWindowSize(m_windowSize);
    return true;//INIT SUCCESS
}

unsigned int Game::getCurrentWidth() const {        
    return m_pCurrentGameState->getStateWidth();
}

unsigned int Game::getCurrentHeight() const {    
    return m_pCurrentGameState->getStateHeight();
}