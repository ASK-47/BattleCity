#pragma once

#include <vector>
#include <string>
#include <memory>

#include <glm/vec2.hpp>



class IGameObject;

class Level {
public:
    static constexpr unsigned int BLOCK_SIZE = 16;

    Level(const std::vector<std::string>& levelDescription);
    void render() const;
    void update(const double delta);
    size_t getLevelWidth() const;
    size_t getLevelHeight() const;

    const glm::ivec2& get_playerRespawn_1 () const;
    const glm::ivec2& get_playerRespawn_2() const;

    const glm::ivec2& get_enemyRespawn_1() const;
    const glm::ivec2& get_enemyRespawn_2() const;
    const glm::ivec2& get_enemyRespawn_3() const;

private:
    size_t m_width = 0;
    size_t m_height = 0;
    std::vector<std::shared_ptr<IGameObject>> m_levelObjects;

    glm::ivec2 m_playerRespawn_1;
    glm::ivec2 m_playerRespawn_2;

    glm::ivec2 m_enemyRespawn_1;
    glm::ivec2 m_enemyRespawn_2;
    glm::ivec2 m_enemyRespawn_3;
};