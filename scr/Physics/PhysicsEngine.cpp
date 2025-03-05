#include "PhysicsEngine.h"
#include "../Game/GameObjects/IGameObject.h"
#include "../Game/GameStates/Level.h"

namespace Physics {
    std::unordered_set<std::shared_ptr<IGameObject>> PhysicsEngine::m_dynamicObjects;
    std::shared_ptr<Level> PhysicsEngine::m_pCurrentLevel;

    void PhysicsEngine::init() {}

    void PhysicsEngine::terminate() {
        m_dynamicObjects.clear();
        m_pCurrentLevel.reset();
    }   

    void PhysicsEngine::setCurrentLevel(std::shared_ptr<Level> pLevel) {
        m_pCurrentLevel.swap(pLevel);
    }
    
    void PhysicsEngine::update(const double delta) {     
        for (auto& currentDynamicObject : m_dynamicObjects) {
            if (currentDynamicObject->getCurrentVelocity() > 0) {
                // align position to multiple of 4 pixels
                if (currentDynamicObject->getCurrentDirection().x != 0.f) {// right and left
                    currentDynamicObject->getCurrentPosition() = glm::vec2(currentDynamicObject->getCurrentPosition().x, static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().y / 4.f + 0.5f) * 4.f);
                }
                else if (currentDynamicObject->getCurrentDirection().y != 0.f) {// top and bottom
                    currentDynamicObject->getCurrentPosition() = glm::vec2(static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().x / 4.f + 0.5f) * 4.f, currentDynamicObject->getCurrentPosition().y);
                }
                
                const auto newPosition = currentDynamicObject->getCurrentPosition() + currentDynamicObject->getCurrentDirection() * static_cast<float>(currentDynamicObject->getCurrentVelocity() * delta);
                std::vector<std::shared_ptr<IGameObject>> objectsToCheck = m_pCurrentLevel->getObjectsInArea(newPosition, newPosition + currentDynamicObject->getSize());
                const auto& colliders = currentDynamicObject->getColliders();

                bool hasCollision = false;

                ECollisionDirection dynamicObjectCollisionDirection = ECollisionDirection::Right;
                if (currentDynamicObject->getCurrentDirection().x < 0) dynamicObjectCollisionDirection = ECollisionDirection::Left;
                else if (currentDynamicObject->getCurrentDirection().y > 0) dynamicObjectCollisionDirection = ECollisionDirection::Top;
                else if (currentDynamicObject->getCurrentDirection().y < 0) dynamicObjectCollisionDirection = ECollisionDirection::Bottom;

                ECollisionDirection objectCollisionDirection = ECollisionDirection::Left;
                if (currentDynamicObject->getCurrentDirection().x < 0) objectCollisionDirection = ECollisionDirection::Right;
                else if (currentDynamicObject->getCurrentDirection().y > 0) objectCollisionDirection = ECollisionDirection::Bottom;
                else if (currentDynamicObject->getCurrentDirection().y < 0) objectCollisionDirection = ECollisionDirection::Top;

                for (const auto& currentDynamicObjectCollider : colliders) {
                    //const auto& collidersToCheck = currentObjectToCheck->getColliders();
                    //if (currentObjectToCheck->collides(currentObject->getObjectType()) && !collidersToCheck.empty()) {
                    for (const auto& currentObjectToCheck : objectsToCheck) {
                        //if (hasIntersection(colliders, newPosition, collidersToCheck, currentObjectToCheck->getCurrentPosition())) {
                        const auto& collidersToCheck = currentObjectToCheck->getColliders();
                        if (currentObjectToCheck->collides(currentDynamicObject->getObjectType()) && !collidersToCheck.empty()) {
                            //hasCollision = true;
                            //currentObjectToCheck->onCollision();
                            //break;
                            for (const auto& currentObjectCollider : currentObjectToCheck->getColliders()) {
                                if (currentObjectCollider.isActive && hasIntersection(currentDynamicObjectCollider, newPosition, currentObjectCollider, currentObjectToCheck->getCurrentPosition())) {
                                    hasCollision = true;
                                    if (currentObjectCollider.onCollisionCallback) {
                                        currentObjectCollider.onCollisionCallback(*currentDynamicObject, objectCollisionDirection);
                                    }
                                    if (currentDynamicObjectCollider.onCollisionCallback) {
                                        currentDynamicObjectCollider.onCollisionCallback(*currentObjectToCheck, dynamicObjectCollisionDirection);
                                    }
                                }
                            }
                        }
                    }
                }
                if (!hasCollision) {
                    currentDynamicObject->getCurrentPosition() = newPosition;
                }

                else {// align position to multiple of 8 pixels                    
                    if (currentDynamicObject->getCurrentDirection().x != 0.f) {// right and left
                        currentDynamicObject->getCurrentPosition() = glm::vec2(static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().x / 8.f + 0.5f) * 8.f, currentDynamicObject->getCurrentPosition().y);
                    }
                    else if (currentDynamicObject->getCurrentDirection().y != 0.f) {// top and bottom
                        currentDynamicObject->getCurrentPosition() = glm::vec2(currentDynamicObject->getCurrentPosition().x, static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().y / 8.f + 0.5f) * 8.f);
                    }
                    //currentDynamicObject->onCollision();
                }
            }
        }
    }
    
    
    void PhysicsEngine::addDynamicGameObject(std::shared_ptr<IGameObject> pGameObject) {
        m_dynamicObjects.insert(std::move(pGameObject));
    }

    //bool PhysicsEngine::hasIntersection(const std::vector<AABB>& colliders1, const glm::vec2& position1
    //, const std::vector<AABB>& colliders2
    //, const glm::vec2& position2) {
    
    bool PhysicsEngine::hasIntersection(const Collider& collider1
        , const glm::vec2& position1
        , const Collider& collider2
        , const glm::vec2& position2) {        
            //for (const auto& currentCollider1 : colliders1) {
        const glm::vec2 collider1_bottomLeft_world = collider1.boundingBox.bottomLeft + position1;
        const glm::vec2 collider1_topRight_world = collider1.boundingBox.topRight + position1;
                //for (const auto& currentCollider2 : colliders2) {
                    //const glm::vec2 currentCollider2_bottomLeft_world = currentCollider2.bottomLeft + position2;
                    //const glm::vec2 currentCollider2_topRight_world = currentCollider2.topRight + position2;                         
                    
                    //if (currentCollider1_bottomLeft_world.x >= currentCollider2_topRight_world.x) {
                    //    //return false;
                    //    continue;
                    //}
                    //if (currentCollider1_topRight_world.x <= currentCollider2_bottomLeft_world.x) {
                    //    //return false;
                    //    continue;
                    //}

        const glm::vec2 collider2_bottomLeft_world = collider2.boundingBox.bottomLeft + position2;
        const glm::vec2 collider2_topRight_world = collider2.boundingBox.topRight + position2;
                    //if (currentCollider1_bottomLeft_world.y >= currentCollider2_topRight_world.y) {
                    //    //return false;
                    //    continue;
                    //}
                    //if (currentCollider1_topRight_world.y <= currentCollider2_bottomLeft_world.y) {
                    //    //return false;
                    //    continue;
                    //}                 
        if (collider1_bottomLeft_world.x >= collider2_topRight_world.x) {
            return false;
        }
        if (collider1_topRight_world.x <= collider2_bottomLeft_world.x) {
            return false;        }
                    //return true;
        if (collider1_bottomLeft_world.y >= collider2_topRight_world.y) {
            return false;
                    }
        
        if (collider1_topRight_world.y <= collider2_bottomLeft_world.y) {
            return false;
        }
        return true;
    }
}