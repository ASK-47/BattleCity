#include "Tank.h"
#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"


//Tank::Tank(std::shared_ptr<RenderEngine::Sprite> pSprite_top
//    , std::shared_ptr<RenderEngine::Sprite> pSprite_bottom
//    , std::shared_ptr<RenderEngine::Sprite> pSprite_left
//    , std::shared_ptr<RenderEngine::Sprite> pSprite_right    
//    , const float velocity
    
Tank::Tank(const float velocity      
    , const glm::vec2& position
    , const glm::vec2& size) : IGameObject(position, size, 0.f)
    , m_eOrientation(EOrientation::Top)
    //, m_pSprite_top(std::move(pSprite_top))
    //, m_pSprite_bottom(std::move(pSprite_bottom))
    //, m_pSprite_left(std::move(pSprite_left))
    //, m_pSprite_right(std::move(pSprite_right))
        
    , m_pSprite_top(ResourceManager::getSprite("tankSprite_top"))
    , m_pSprite_bottom(ResourceManager::getSprite("tankSprite_bottom"))
    , m_pSprite_left(ResourceManager::getSprite("tankSprite_left"))
    , m_pSprite_right(ResourceManager::getSprite("tankSprite_right"))

    , m_spriteAnimator_top(m_pSprite_top)
    , m_spriteAnimator_bottom(m_pSprite_bottom)
    , m_spriteAnimator_left(m_pSprite_left)
    , m_spriteAnimator_right(m_pSprite_right)

    , m_move(false)
    , m_velocity(velocity)
    , m_moveOffset(glm::vec2(0.f, 1.f)) {}


void Tank::render() const {
    //m_pSprite->render();
    //m_pSprite->render(m_position, m_size, m_rotation);
    switch (m_eOrientation) {
    case Tank::EOrientation::Top:
        m_pSprite_top->render(m_position, m_size, m_rotation, m_spriteAnimator_top.getCurrentFrame());
        break;
    case Tank::EOrientation::Bottom:
        m_pSprite_bottom->render(m_position, m_size, m_rotation, m_spriteAnimator_bottom.getCurrentFrame());
        break;
    case Tank::EOrientation::Left:
        m_pSprite_left->render(m_position, m_size, m_rotation, m_spriteAnimator_left.getCurrentFrame());
        break;
    case Tank::EOrientation::Right:
        m_pSprite_right->render(m_position, m_size, m_rotation, m_spriteAnimator_right.getCurrentFrame());
        break;
    }
}

void Tank::setOrientation(const EOrientation eOrientation) {
    if (m_eOrientation == eOrientation) {//if orientation is the same => nothing TODO
        return;
    }

    m_eOrientation = eOrientation;//else => new orientation
    
    switch (m_eOrientation) {
    
    case Tank::EOrientation::Top:
        //m_pSprite->setState("tankTopState");
        m_moveOffset.x = 0.f;
        m_moveOffset.y = 1.f;
        break;
    
    case Tank::EOrientation::Bottom:
        //m_pSprite->setState("tankBottomState");
        m_moveOffset.x = 0.f;
        m_moveOffset.y = -1.f;
        break;
    
    case Tank::EOrientation::Left:
        //m_pSprite->setState("tankLeftState");
        m_moveOffset.x = -1.f;
        m_moveOffset.y = 0.f;
        break;
    
    case Tank::EOrientation::Right:
        //m_pSprite->setState("tankRightState");
        m_moveOffset.x = 1.f;
        m_moveOffset.y = 0.f;
        break;
    
    default:
        break;
    }
}

void Tank::move(const bool move) {
    m_move = move;
}

void Tank::update(const uint64_t delta) {
    if (m_move) {//if move is on => update
        m_position += delta * m_velocity * m_moveOffset;
        //m_pSprite->setPosition(m_position);
        //m_pSprite->update(delta);
    }
}
