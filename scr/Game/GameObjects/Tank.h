#pragma once

#include <glm/vec2.hpp>
#include <memory>

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"
#include "../../System/Timer.h"

namespace RenderEngine {    
    class Sprite;
}

class Tank : public IGameObject {
public:
    enum class EOrientation : uint8_t {//tank orientation
        Top,
        Bottom,
        Left,
        Right
    };

    Tank(const double maxVelocity
        , const glm::vec2& position
        , const glm::vec2& size
        , const float layer);
        
        void render() const override;
        void setOrientation(const EOrientation eOrientation);
        //void move(const bool move);//if true => animation is on        
        void update(const double delta) override;

        double getMaxVelocity() const;
        void setVelocity(const double velocity) override;

private://varibles
    EOrientation m_eOrientation;//variable for tank orientation    
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_top;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_bottom;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_left;
    std::shared_ptr<RenderEngine::Sprite> m_pSprite_right;
    RenderEngine::SpriteAnimator m_spriteAnimator_top;
    RenderEngine::SpriteAnimator m_spriteAnimator_bottom;
    RenderEngine::SpriteAnimator m_spriteAnimator_left;
    RenderEngine::SpriteAnimator m_spriteAnimator_right;

    std::shared_ptr<RenderEngine::Sprite> m_pSprite_respawn;
    RenderEngine::SpriteAnimator m_spriteAnimator_respawn;

    std::shared_ptr<RenderEngine::Sprite> m_pSprite_shield;
    RenderEngine::SpriteAnimator m_spriteAnimator_shield;

    Timer m_respawnTimer;
    Timer m_shieldTimer;

    //bool m_move;
    //double m_velocity;    
    //glm::vec2 m_moveOffset;//varible for direction of move

    double m_maxVelocity;
    bool m_isSpawning;
    bool m_hasShield;
};