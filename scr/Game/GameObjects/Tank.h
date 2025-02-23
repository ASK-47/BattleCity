#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"

namespace RenderEngine {
    class AnimatedSprite;
}

class Tank : public IGameObject {
public:
    enum class EOrientation {//tank orientation
        Top,
        Bottom,
        Left,
        Right
    };

    //Tank(std::shared_ptr<RenderEngine::AnimatedSprite> pSprite, const float velocity, const glm::vec2& position);//sprite, velocity, starting position
    Tank(std::shared_ptr<RenderEngine::AnimatedSprite> pSprite, const float velocity, const glm::vec2& position, const glm::vec2& size);

    //void render() const;//tank render
    void render() const override;

    void setOrientation(const EOrientation eOrientation);
    void move(const bool move);//if true => animation is on

    //void update(const uint64_t delta);
    void update(const uint64_t delta) override;

private://varibles
    EOrientation m_eOrientation;//variable for tank orientation
    std::shared_ptr<RenderEngine::AnimatedSprite> m_pSprite;//variable for sprite
    bool m_move;
    float m_velocity;
    //glm::vec2 m_position;
    glm::vec2 m_moveOffset;//varible for direction of move
};