#pragma once

#include <glm/vec2.hpp>
#include <memory>

namespace RenderEngine {
    class AnimatedSprite;
}

class Tank {
public:
    enum class EOrientation {//tank orientation
        Top,
        Bottom,
        Left,
        Right
    };

    Tank(std::shared_ptr<RenderEngine::AnimatedSprite> pSprite, const float velocity, const glm::vec2& position);//sprite, velocity, starting position

    void render() const;//tank render
    void setOrientation(const EOrientation eOrientation);
    void move(const bool move);//if true => animation is on
    void update(const uint64_t delta);

private://varibles
    EOrientation m_eOrientation;//variable for tank orientation
    std::shared_ptr<RenderEngine::AnimatedSprite> m_pSprite;//variable for sprite
    bool m_move;
    float m_velocity;
    glm::vec2 m_position;
    glm::vec2 m_moveOffset;//varible for direction of move
};