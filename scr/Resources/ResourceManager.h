#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace RenderEngine {
    class ShaderProgram;
    class Texture2D;
    class Sprite;
    //class AnimatedSprite;
}

class ResourceManager {
public:    
    //CTOR DO NOT NEED ANYMORE IS CHANGED BY STATIC setExecutablePath
    //ResourceManager(const std::string& executablePath);        
    static void setExecutablePath(const std::string& executablePath);     

    //DTOR DO NOT NEED ANYMORE
    //~ResourceManager() = default;  
     //DTOR IS CHANGED BY STATIC unloadAllResources
    ~ResourceManager() = delete;
    static void unloadAllResources();

    ResourceManager() = delete;    
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    
    //func for shaders loading
    //std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
    //std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);
    
    //std::shared_ptr<Renderer::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
    //std::shared_ptr<Renderer::Texture2D> getTexture(const std::string& textureName);

    //ALL METHODS BECOMES  STATIC TO INVOKE W/O ANY ResourceManager OBJECT
    static std::shared_ptr<RenderEngine::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
    static std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string& shaderName);
    
    static std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
    static std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string& textureName);
    
    //std::shared_ptr<Renderer::Sprite> loadSprite(const std::string& spriteName
    //    //, const std::string& textureName
    //    //, const std::string& shaderName
    //    //, const unsigned int spriteWidth
    //    //, const unsigned int spriteHeight);
    //    , const std::string& textureName
    //    , const std::string& shaderName
    //    , const unsigned int spriteWidth
    //    , const unsigned int spriteHeight
    //    , const std::string& subTextureName = "default");

    //std::shared_ptr<Renderer::Sprite> getSprite(const std::string& spriteName);

    static std::shared_ptr<RenderEngine::Sprite> loadSprite(const std::string& spriteName
        , const std::string& textureName
        , const std::string& shaderName
        //, const unsigned int spriteWidth
        //, const unsigned int spriteHeight
        , const std::string& subTextureName = "default");

    static std::shared_ptr<RenderEngine::Sprite> getSprite(const std::string& spriteName);

    //std::shared_ptr<Renderer::Texture2D> loadTextureAtlas(const std::string textureName
        //, const std::string texturePath
        //, const std::vector<std::string> subTextures

    /*std::shared_ptr<Renderer::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName
        , const std::string& textureName
        , const std::string& shaderName
        , const unsigned int spriteWidth
        , const unsigned int spriteHeight
        , const std::string& subTextureName = "default");
    
    std::shared_ptr<Renderer::AnimatedSprite> getAnimatedSprite(const std::string& spriteName);*/

    //static std::shared_ptr<RenderEngine::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName
    //    , const std::string& textureName
    //    , const std::string& shaderName
    //    //, const unsigned int spriteWidth
    //    //, const unsigned int spriteHeight
    //    , const std::string& subTextureName = "default");
    //
    //static std::shared_ptr<RenderEngine::AnimatedSprite> getAnimatedSprite(const std::string& spriteName);

    /*std::shared_ptr<Renderer::Texture2D> loadTextureAtlas(std::string textureName,
        std::string texturePath,
        std::vector<std::string> subTextures
        , const unsigned int subTextureWidth
        , const unsigned int subTextureHeight);*/

    static std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas(std::string textureName,
        std::string texturePath,
        std::vector<std::string> subTextures,
        const unsigned int subTextureWidth,
        const unsigned int subTextureHeight);

    static bool loadJSONResources(const std::string& JSONPath);

    static const std::vector<std::vector<std::string>>& getLevels() { return m_levels; }

private:
    //RESOURCES
    //ALL OBJECTS  BECOMES  STATIC TO INVOKE W/O ANY ResourceManager OBJECT
    //std::string getFileString(const std::string& relativeFilePath) const;
    static std::string getFileString(const std::string& relativeFilePath);
    
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramsMap;
    //ShaderProgramsMap m_shaderPrograms;
    static ShaderProgramsMap m_shaderPrograms;

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> TexturesMap;
    //TexturesMap m_textures;
    static TexturesMap m_textures;

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpritesMap;
    //SpritesMap m_sprites;//map for staic sprites
    static SpritesMap m_sprites;
    
    //typedef std::map<const std::string, std::shared_ptr<RenderEngine::AnimatedSprite>> AnimatedSpritesMap;
    //AnimatedSpritesMap m_animatedSprites;//map for dynamic (updated) sprites
    //static AnimatedSpritesMap m_animatedSprites;

    static std::vector<std::vector<std::string>> m_levels;

    //std::string m_path;
    static std::string m_path;
};