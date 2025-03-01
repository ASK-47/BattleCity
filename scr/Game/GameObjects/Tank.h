#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"

namespace RenderEngine {
    //class AnimatedSprite;
    class Sprite;
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
    //Tank(std::shared_ptr<RenderEngine::AnimatedSprite> pSprite, const float velocity, const glm::vec2& position, const glm::vec2& size);

    Tank(std::shared_ptr<RenderEngine::Sprite> pSprite_top,
        std::shared_ptr<RenderEngine::Sprite> pSprite_bottom,
        std::shared_ptr<RenderEngine::Sprite> pSprite_left,
        std::shared_ptr<RenderEngine::Sprite> pSprite_right,
        const float velocity,
        const glm::vec2& position,
        const glm::vec2& size);
        //void render() const;//tank render
        void render() const override;
        void setOrientation(const EOrientation eOrientation);
        void move(const bool move);//if true => animation is on
        //void update(const uint64_t delta);
        void update(const uint64_t delta) override;
private://varibles
    EOrientation m_eOrientation;//variable for tank orientation
    //std::shared_ptr<RenderEngine::AnimatedSprite> m_pSprite;//variable for sprite
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_top;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_bottom;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_left;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_right;
    RenderEngine::SpriteAnimator m_spriteAnimator_top;
    RenderEngine::SpriteAnimator m_spriteAnimator_bottom;
    RenderEngine::SpriteAnimator m_spriteAnimator_left;
    RenderEngine::SpriteAnimator m_spriteAnimator_right;
    bool m_move;
    float m_velocity;
    //glm::vec2 m_position;
    glm::vec2 m_moveOffset;//varible for direction of move
};