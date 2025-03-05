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
#include "Level.h"
#include "../Physics/PhysicsEngine.h"
#include "GameObjects/Bullet.h"

#include <GLFW/glfw3.h>


Game::Game(const glm::ivec2& windowSize) : m_windowSize(windowSize), m_eCurrentGameState(EGameState::Active) {//CTOR to init state and window size
    m_keys.fill(false);//set all keys to 0,0,0...(see set key for action)
}

Game::~Game() {}

void Game::render() {    
    if (m_pTank) {
        m_pTank->render();
    }
    if (m_pLevel) {
        m_pLevel->render();
    }
}

void Game::update(const double delta) {
    if (m_pLevel) {
        m_pLevel->update(delta);
    }    
    if (m_pTank) {
        if (m_keys[GLFW_KEY_W]) {//UP
            m_pTank->setOrientation(Tank::EOrientation::Top);          
            m_pTank->setVelocity(m_pTank->getMaxVelocity());
        }
        else if (m_keys[GLFW_KEY_A]) {//LEFT
            m_pTank->setOrientation(Tank::EOrientation::Left);            
            m_pTank->setVelocity(m_pTank->getMaxVelocity());
        }
        else if (m_keys[GLFW_KEY_D]) {//DOWN
            m_pTank->setOrientation(Tank::EOrientation::Right);            
            m_pTank->setVelocity(m_pTank->getMaxVelocity());
        }
        else if (m_keys[GLFW_KEY_S]) {//RIGH
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
}
void Game::setKey(const int key, const int action) {
    m_keys[key] = action;//press key =>  m_keys == true, unpress key =>  m_keys == false (see g_game.setKey(key, action) in main())
}

bool Game::init() { 
    ResourceManager::loadJSONResources("res/resources.json");
    auto pSpriteShaderProgram = ResourceManager::getShaderProgram("spriteShader");
    if (!pSpriteShaderProgram) {
        std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
        return false;//-1 was changed for false
    }
    m_pLevel = std::make_shared<Level>(ResourceManager::getLevels()[0]);    
    m_windowSize.x = static_cast<int>(m_pLevel->getLevelWidth());
    m_windowSize.y = static_cast<int>(m_pLevel->getLevelHeight());

    Physics::PhysicsEngine::setCurrentLevel(m_pLevel);
    
    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);
        
    pSpriteShaderProgram->use();
    
    pSpriteShaderProgram->setInt("tex", 0);

    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);
    
    m_pTank = std::make_shared<Tank>(0.05, m_pLevel->get_playerRespawn_1(), glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE), 0.f);
    
    //PhysicsEngine::addDynamicGameObject(m_pTank);
    Physics::PhysicsEngine::addDynamicGameObject(m_pTank);
    return true;//INIT SUCCESS
}

size_t Game::getCurrentLevelWidth() const {
    return m_pLevel->getLevelWidth();
}

size_t Game::getCurrentLevelHeight() const {
    return m_pLevel->getLevelHeight();
}