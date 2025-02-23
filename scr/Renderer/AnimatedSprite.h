#pragma once

#include "Sprite.h"
#include <map>
#include <vector>

namespace RenderEngine {
    class AnimatedSprite : public Sprite {
    public:
        AnimatedSprite(std::shared_ptr<Texture2D> pTexture
            , std::string initialSubTexture
            //, std::shared_ptr<ShaderProgram> pShaderProgram
            //, const glm::vec2& position = glm::vec2(0.f)
            //, const glm::vec2& size = glm::vec2(1.f)
            //, const float rotation = 0.f);
            , std::shared_ptr<ShaderProgram> pShaderProgram);
        
        void insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration); //function to insert [state, vec of pair(subtexture,frame duration)...]
        //void render() const override;
        void render(const glm::vec2& position, const glm::vec2& size, const float rotation) const override;
        void setState(const std::string& newState);
        void update(const uint64_t delta);//for animation
    
    private:
        std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> m_statesMap;//map for state ==sit run ... f(texture, frame duration)
        size_t m_currentFrame = 0;//frame counter
        uint64_t m_currentAnimationTime = 0;//time since state was inserted
        std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::iterator m_pCurrentAnimationDurations;//iterator for map for state
        mutable bool m_dirty = false;//mutable - to change -m_dirty in const functions (see render() const)
    };
}