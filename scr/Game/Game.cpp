#include "Game.h"

#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "GameObjects/Tank.h"
#include "Level.h"

#include <GLFW/glfw3.h>


Game::Game(const glm::ivec2& windowSize) : m_eCurrentGameState(EGameState::Active), m_windowSize(windowSize) {//CTOR to init state and window size
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

void Game::update(const uint64_t delta) {    
    if (m_pLevel) {
        m_pLevel->update(delta);
    }
    
    if (m_pTank) {
        if (m_keys[GLFW_KEY_W]) {//UP
            m_pTank->setOrientation(Tank::EOrientation::Top);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_A]) {//LEFT
            m_pTank->setOrientation(Tank::EOrientation::Left);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_D]) {//DOWN
            m_pTank->setOrientation(Tank::EOrientation::Right);
            m_pTank->move(true);
        }
        else if (m_keys[GLFW_KEY_S]) {//RIGH
            m_pTank->setOrientation(Tank::EOrientation::Bottom);
            m_pTank->move(true);
        }
        else {
            m_pTank->move(false);
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

    
    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_windowSize.x), 0.f, static_cast<float>(m_windowSize.y), -100.f, 100.f);
        
    pSpriteShaderProgram->use();
    
    pSpriteShaderProgram->setInt("tex", 0);

    pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    m_pTank = std::make_unique<Tank>(0.0000001f, glm::vec2(0), glm::vec2(16.f, 16.f));
    
    //m_pLevel = std::make_unique<Level>(ResourceManager::getLevels()[0]);
    m_pLevel = std::make_unique<Level>(ResourceManager::getLevels()[1]);

    return true;//INIT SUCCESS
}