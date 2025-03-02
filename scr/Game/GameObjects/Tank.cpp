#include "Tank.h"
#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"
  
Tank::Tank(const double maxVelocity
    , const glm::vec2& position
    , const glm::vec2& size    
    , const float layer)
    : IGameObject(position, size, 0.f, layer)    
    
    , m_eOrientation(EOrientation::Top)
    
    , m_pSprite_top(ResourceManager::getSprite("tankSprite_top"))
    , m_pSprite_bottom(ResourceManager::getSprite("tankSprite_bottom"))
    , m_pSprite_left(ResourceManager::getSprite("tankSprite_left"))
    , m_pSprite_right(ResourceManager::getSprite("tankSprite_right"))

    , m_spriteAnimator_top(m_pSprite_top)
    , m_spriteAnimator_bottom(m_pSprite_bottom)
    , m_spriteAnimator_left(m_pSprite_left)
    , m_spriteAnimator_right(m_pSprite_right)

    , m_pSprite_respawn(ResourceManager::getSprite("respawn"))
    , m_spriteAnimator_respawn(m_pSprite_respawn)
    , m_pSprite_shield(ResourceManager::getSprite("shield"))
    , m_spriteAnimator_shield(m_pSprite_shield)

    //, m_move(false)
    //, m_velocity(velocity)
    //, m_moveOffset(glm::vec2(0.f, 1.f)) 
    , m_maxVelocity(maxVelocity)

    , m_isSpawning(true)
    , m_hasShield(false) {
        m_respawnTimer.setCallback([&](){
                m_isSpawning = false;
                m_hasShield = true;
                m_shieldTimer.start(2000);
            }
        );

        m_respawnTimer.start(1500);
        m_shieldTimer.setCallback([&]() {
                m_hasShield = false;
            }
        );
}

void Tank::setVelocity(const double velocity) {
    if (!m_isSpawning) {
        m_velocity = velocity;
    }
}

void Tank::render() const {
    if (m_isSpawning) {
        m_pSprite_respawn->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_respawn.getCurrentFrame());
    }
    else {
        switch (m_eOrientation) {
        case Tank::EOrientation::Top:
            m_pSprite_top->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_top.getCurrentFrame());
            break;
        case Tank::EOrientation::Bottom:
            m_pSprite_bottom->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_bottom.getCurrentFrame());
            break;
        case Tank::EOrientation::Left:
            m_pSprite_left->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_left.getCurrentFrame());
            break;
        case Tank::EOrientation::Right:
            m_pSprite_right->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_right.getCurrentFrame());
            break;
        }
        if (m_hasShield) {
                m_pSprite_shield->render(m_position, m_size, m_rotation, m_layer + 0.1f, m_spriteAnimator_shield.getCurrentFrame());
        }
    }
}

void Tank::setOrientation(const EOrientation eOrientation) {
    if (m_eOrientation == eOrientation) {//if orientation is the same => nothing TODO
        return;
    }

    m_eOrientation = eOrientation;//else => new orientation
    
    switch (m_eOrientation) {    
    case Tank::EOrientation::Top:
        //m_moveOffset.x = 0.f;
        //m_moveOffset.y = 1.f;
        m_direction.x = 0.f;
        m_direction.y = 1.f;
        break;    
    case Tank::EOrientation::Bottom:        
        //m_moveOffset.x = 0.f;
        //m_moveOffset.y = -1.f;
        m_direction.x = 0.f;
        m_direction.y = -1.f;
        break;    
    case Tank::EOrientation::Left:        
        //m_moveOffset.x = -1.f;
        //m_moveOffset.y = 0.f;
        m_direction.x = -1.f;
        m_direction.y = 0.f;
        break;    
    case Tank::EOrientation::Right:        
        //m_moveOffset.x = 1.f;
        //m_moveOffset.y = 0.f;
        m_direction.x = 1.f;
        m_direction.y = 0.f;
        break;    
    default:
        break;
    }
}

//void Tank::move(const bool move) {
//    m_move = move;
//}

void Tank::update(const double delta) {    
    if (m_isSpawning) {        
        m_spriteAnimator_respawn.update(delta);
        m_respawnTimer.update(delta);
    }
    else {
        if (m_hasShield) {
            m_spriteAnimator_shield.update(delta);
            m_shieldTimer.update(delta);
        }
    }
    //if (m_move) {
    if (m_velocity > 0) {
        //m_position.x += static_cast<float>(delta * m_velocity * m_moveOffset.x);
        //m_position.y += static_cast<float>(delta * m_velocity * m_moveOffset.y);        
        switch (m_eOrientation) {
        case Tank::EOrientation::Top:
            m_spriteAnimator_top.update(delta);
            break;
        case Tank::EOrientation::Bottom:
            m_spriteAnimator_bottom.update(delta);
            break;
        case Tank::EOrientation::Left:
            m_spriteAnimator_left.update(delta);
            break;
        case Tank::EOrientation::Right:
            m_spriteAnimator_right.update(delta);
            break;
        }
    }
}
double  Tank::getMaxVelocity() const { return m_maxVelocity; }