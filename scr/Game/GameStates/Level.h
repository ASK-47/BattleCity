#pragma once

#include <vector>
#include <string>
#include <memory>
#include <set>

#include <glm/vec2.hpp>
#include "IGameState.h"
#include "../Game.h"

class IGameObject;
class Tank;

class Level : public IGameState {
public:
    static constexpr unsigned int BLOCK_SIZE = 16;

    Level(const std::vector<std::string>& levelDescription, const Game::EGameMode eGameMode);
    
    virtual void render() const override;
    virtual void update(const double delta) override;
    
    virtual unsigned int getStateWidth() const override;
    virtual unsigned int getStateHeight() const override;

    virtual void processInput(const std::array<bool, 349>& keys) override;

    const glm::ivec2& get_playerRespawn_1() const;
    const glm::ivec2& get_playerRespawn_2() const;

    const glm::ivec2& get_enemyRespawn_1() const;
    const glm::ivec2& get_enemyRespawn_2() const;
    const glm::ivec2& get_enemyRespawn_3() const;

    std::vector<std::shared_ptr<IGameObject>> getObjectsInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight) const;
    
    //void initPhysics();
    void initLevel();

private:
    size_t m_widthBlocks = 0;
    size_t m_heightBlocks = 0;
    unsigned int m_widthPixels = 0;
    unsigned int m_heightPixels = 0;

    std::vector<std::shared_ptr<IGameObject>> m_levelObjects;

    glm::ivec2 m_playerRespawn_1;
    glm::ivec2 m_playerRespawn_2;

    glm::ivec2 m_enemyRespawn_1;
    glm::ivec2 m_enemyRespawn_2;
    glm::ivec2 m_enemyRespawn_3;

    //std::shared_ptr<Tank> m_pTank;
    std::shared_ptr<Tank> m_pTank1;
    std::shared_ptr<Tank> m_pTank2;

    std::set<std::shared_ptr<Tank>> m_enemyTanks;

    Game::EGameMode m_eGameMode;
};