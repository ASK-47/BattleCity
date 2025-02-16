#include "AnimatedSprite.h"
#include "Texture2D.h"
#include <iostream>

namespace Renderer {
    AnimatedSprite::AnimatedSprite(std::shared_ptr<Texture2D> pTexture
        , std::string initialSubTexture
        , std::shared_ptr<ShaderProgram> pShaderProgram
        , const glm::vec2& position
        , const glm::vec2& size
        , const float rotation)
        : Sprite (std::move(pTexture)
            , std::move(initialSubTexture)
            , std::move(pShaderProgram)
            , position
            , size
            , rotation)
    {
        m_pCurrentAnimationDurations = m_statesMap.end();//intialization of invalid state for iterator (see update())
    }
    void AnimatedSprite::insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration) {
        m_statesMap.emplace(std::move(state), std::move(subTexturesDuration));
    }
    
    void AnimatedSprite::setState(const std::string& newState) {
        auto it = m_statesMap.find(newState);
        if (it == m_statesMap.end()) {
            std::cout << "Can't find animation state: " << newState << std::endl;
            return;
        }
        if (it != m_pCurrentAnimationDurations) {//starting new state only if state is not current
            m_currentAnimationTime = 0;//reset time since state was inserted
            m_currentFrame = 0; // reset frame counter
            m_pCurrentAnimationDurations = it;//current state is mew state
            m_dirty = true;//state is changed, now we are ready to change bufffer of cordinates (see render())
        }
    }

    void AnimatedSprite::update(const uint64_t delta) {//lag to render next frame
        if (m_pCurrentAnimationDurations != m_statesMap.end()) {//if map state iterator is not invalid => make update
            m_currentAnimationTime += delta;//time since state was inserted +=lag
            while (m_currentAnimationTime >= m_pCurrentAnimationDurations->second[m_currentFrame].second) {
                m_currentAnimationTime -= m_pCurrentAnimationDurations->second[m_currentFrame].second;//correction for excess of time
                ++m_currentFrame;
                m_dirty = true;//state is changed, now we are ready to change bufffer of cordinates (see render())
                if (m_currentFrame == m_pCurrentAnimationDurations->second.size()) {//in case of current frame is last in vector of frames
                    m_currentFrame = 0;//start again
                }
            }
        }
    }
    void AnimatedSprite::render() const {
        if (m_dirty) {//we change buffer of coordinates if only frame is changed
            auto subTexture = m_pTexture->getSubTexture(m_pCurrentAnimationDurations->second[m_currentFrame].first);
            //const GLfloat textureCoords[] = {//get new coordinates of the subtecture U  V
            //    subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
            //    subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
            //    subTexture.rightTopUV.x,   subTexture.rightTopUV.y,
            //    subTexture.rightTopUV.x,   subTexture.rightTopUV.y,
            //    subTexture.rightTopUV.x,   subTexture.leftBottomUV.y,
            //    subTexture.leftBottomUV.x, subTexture.leftBottomUV.y
            const GLfloat textureCoords[] = {                    
                    subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
                    subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
                    subTexture.rightTopUV.x, subTexture.rightTopUV.y,                    		
                    subTexture.rightTopUV.x, subTexture.leftBottomUV.y
            };            
            
            //glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);//bind buffer //removed to VertexBuffer::update
            //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textureCoords), &textureCoords);//pass coordinates to buffer//removed to VertexBuffer::update
            //glBindBuffer(GL_ARRAY_BUFFER, 0);//debind buffer//removed to VertexBuffer::unbind
            m_textureCoordsBuffer.update(textureCoords, 2 * 4 * sizeof(GLfloat));
            m_dirty = false;
        }
        Sprite::render();//invoke render from base class
    }
}