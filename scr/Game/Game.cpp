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


Game::Game(const glm::uvec2& windowSize) : m_windowSize(windowSize), m_eCurrentGameState(EGameState::StartScreen) {//CTOR to init state and window size
    m_keys.fill(false);//set all keys to 0,0,0...(see set key for action)
}

void Game::setWindowSize(const glm::uvec2& windowSize) {
    m_windowSize = windowSize;
    updateViewport();
}

Game::~Game() {}

void Game::render() {      
    //switch (m_eCurrentGameState) {
    //    case EGameState::StartScreen:
    //        m_pStartScreen->render();
    //        break;

    //    case EGameState::Level:
    //        if (m_pTank) {
    //            m_pTank->render();
    //        }
    //        if (m_pLevel) {
    //            m_pLevel->render();
    //        }
    //        break;
    //}
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

void Game::startNewLevel(const size_t level) {
    auto pLevel = std::make_shared<Level>(ResourceManager::getLevels()[0]);
    m_pCurrentGameState = pLevel;
    Physics::PhysicsEngine::setCurrentLevel(pLevel);
    updateViewport();
}

void Game::update(const double delta) {
    m_pCurrentGameState->processInput(m_keys);
    m_pCurrentGameState->update(delta);
    /*
    switch (m_eCurrentGameState) {
    case EGameState::StartScreen:
        if (m_keys[GLFW_KEY_ENTER]) {
            m_eCurrentGameState = EGameState::Level;
            startNewLevel(0);
        }
    break;
    case EGameState::Level:
       /* if (m_pLevel)  {
            m_pLevel->update(delta);
        }
        if (m_pTank) {
            if (m_keys[GLFW_KEY_W]) {
                m_pTank->setOrientation(Tank::EOrientation::Top);
                m_pTank->setVelocity(m_pTank->getMaxVelocity());
            }
            else if (m_keys[GLFW_KEY_A]) {
                m_pTank->setOrientation(Tank::EOrientation::Left);
                m_pTank->setVelocity(m_pTank->getMaxVelocity());
            }
            else if (m_keys[GLFW_KEY_D]) {
                m_pTank->setOrientation(Tank::EOrientation::Right);
                m_pTank->setVelocity(m_pTank->getMaxVelocity());
            }
            else if (m_keys[GLFW_KEY_S]) {
                m_pTank->setOrientation(Tank::EOrientation::Bottom);
                m_pTank->setVelocity(m_pTank->getMaxVelocity());
            }
            else {
                m_pTank->setVelocity(0);
            }
            if (m_pTank && m_keys[GLFW_KEY_SPACE]) {
                m_pTank->fire();
            }
            m_pTank->update(delta);
        }
        break;*/
        //m_pCurrentGameState->processInput(m_keys);
        //m_pCurrentGameState->update(delta);
        // }    
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

    /*m_pStartScreen = std::make_shared<StartScreen>(ResourceManager::getStartScreen());

    m_pLevel = std::make_shared<Level>(ResourceManager::getLevels()[0]);    
   
    m_windowSize.x = static_cast<int>(m_pLevel->getStateWidth());
    m_windowSize.y = static_cast<int>(m_pLevel->getStateHeight());

    Physics::PhysicsEngine::setCurrentLevel(m_pLevel);
    
    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);
        
    pSpriteShaderProgram->use();
    
    pSpriteShaderProgram->setInt("tex", 0);

    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);
    
    m_pTank = std::make_shared<Tank>(0.05, m_pLevel->get_playerRespawn_1(), glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE), 0.f);
    
    Physics::PhysicsEngine::addDynamicGameObject(m_pTank);*/

    //m_pCurrentGameState = std::make_shared<StartScreen>(ResourceManager::getStartScreen());
    m_pCurrentGameState = std::make_shared<StartScreen>(ResourceManager::getStartScreen(), this);
    
    setWindowSize(m_windowSize);
    return true;//INIT SUCCESS
}

unsigned int Game::getCurrentWidth() const {    
    /*switch (m_eCurrentGameState){
    case EGameState::StartScreen:
        return m_pStartScreen->getStateWidth();

    case EGameState::Level:
        return m_pLevel->getStateWidth();
    }*/
    return m_pCurrentGameState->getStateWidth();
}

unsigned int Game::getCurrentHeight() const { 
   /* switch (m_eCurrentGameState) {
    case EGameState::StartScreen:
        return m_pStartScreen->getStateHeight();
    case EGameState::Level:
        return m_pLevel->getStateHeight();
    }*/
    return m_pCurrentGameState->getStateHeight();
}