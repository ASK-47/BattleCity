#pragma once

#include <string>
#include <memory>
#include <map>
//#include <vector>

namespace Renderer {
    class ShaderProgram;
}

class ResourceManager {
public:
    ResourceManager(const std::string& executablePath);
    ~ResourceManager() = default;  
    
    ResourceManager() = delete;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    
    //func for shaders loading
    std::shared_ptr<Renderer::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
   
    std::shared_ptr<Renderer::ShaderProgram> getShaderProgram(const std::string& shaderName);
    
    
    void loadTexture(const std::string& textureName, const std::string& texturePath);

private:
    std::string getFileString(const std::string& relativeFilePath) const;
    
    typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
    ShaderProgramsMap m_shaderPrograms;

    std::string m_path;    
};