#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"


#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

//ResourceManager::ResourceManager (const std::string& executablePath) {//DELETED, IS CHANGED BY STATIC setExecutablePath (see below)

//RESOURCES
ResourceManager::ShaderProgramsMap ResourceManager::m_shaderPrograms;
ResourceManager::TexturesMap ResourceManager::m_textures;
ResourceManager::SpritesMap ResourceManager::m_sprites;
ResourceManager::AnimatedSpritesMap ResourceManager::m_animatedSprites;
std::string ResourceManager::m_path;

//CTOR DO NOT NEED ANYMORE IS CHANGED BY STATIC setExecutablePath
void ResourceManager::setExecutablePath(const std::string& executablePath) {
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

//DTOR DO NOT NEED ANYMORE IS CHANGED BY STATIC unloadAllResources => to clear all RESOURCES
void ResourceManager::unloadAllResources() {
	m_shaderPrograms.clear();
	m_textures.clear();
	m_sprites.clear();
	m_animatedSprites.clear();
}

//const deleted
//std::string ResourceManager::getFileString(const std::string& relativeFilePath) const {
std::string ResourceManager::getFileString(const std::string& relativeFilePath) {
	std::ifstream f;
	f.open(m_path + '/' + relativeFilePath.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open()) {
		std::cerr << "Failed to open file: " << relativeFilePath << std::endl;
		return std::string{};
	}
	std::stringstream buffer;//if f is open reaf all texto buffer
	buffer << f.rdbuf();
	return buffer.str();
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath) {
	std::string vertexString = getFileString(vertexPath);
	if (vertexString.empty()) {
		std::cerr << "No vertex shader!" << std::endl;
		return nullptr;
	}
	
	std::string fragmentString = getFileString(fragmentPath);
	if (fragmentString.empty()) {
		std::cerr << "No frragment shader!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<RenderEngine::ShaderProgram>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<RenderEngine::ShaderProgram> (vertexString, fragmentString)).first->second;
	//emplace returns pair <iter, true/fals> first=iter, iter is pair <shaderName, Path> iter->second == Path
	if (newShader->isCompiled()) {	
		return newShader;
	}
	std::cerr << "Can't load shader program!\n"
		<< "Vertex:" << vertexPath << '\n'
		<< "Fragment:" << fragmentPath << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::ShaderProgram>  ResourceManager::getShaderProgram(const std::string& shaderName) {
	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
	if (it != m_shaderPrograms.end()) {
		return it->second;
	}
	std::cerr << "Can't find shader program: " << shaderName << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath) {
	int channels = 0;
	int width = 0;
	int height = 0;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);

	if (!pixels) {
		std::cerr << "Can't load image: " << texturePath << std::endl;
		return nullptr;
	}

	std::shared_ptr<RenderEngine::Texture2D> newTexture = m_textures.emplace(textureName,
		std::make_shared<RenderEngine::Texture2D>(width, height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixels);
	return newTexture;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::getTexture (const std::string& textureName) {
	TexturesMap::const_iterator it = m_textures.find(textureName);
	if (it != m_textures.end()) {
		return it->second;
	}
	std::cerr << "Can't find texture: " << textureName << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::loadSprite(const std::string& spriteName
	, const std::string& textureName
	, const std::string& shaderName
	, const unsigned int spriteWidth
	, const unsigned int spriteHeight
	, const std::string& subTextureName) {
	auto pTexture = getTexture(textureName);
		if (!pTexture) {
			std::cerr << "Can't find the texture: " << textureName << " for the sprite: " << spriteName << std::endl;
		}
	auto pShader = getShaderProgram(shaderName);
		if (!pShader) {
		std::cerr << "Can't find shader: " << shaderName << " for the sprite^ " << spriteName << std::endl;
	}
	std::shared_ptr<RenderEngine::Sprite> newSprite = m_sprites.emplace(textureName, std::make_shared<RenderEngine::Sprite>(pTexture, subTextureName, pShader, glm::vec2(0.f, 0.f), glm::vec2(spriteWidth, spriteHeight))).first->second;
	return newSprite;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::getSprite(const std::string& spriteName) {
	SpritesMap::const_iterator it = m_sprites.find(spriteName);
	if (it != m_sprites.end()) {
		return it->second;
	}
	std::cerr << "Can't find the sprite: " << spriteName << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::AnimatedSprite> ResourceManager::getAnimatedSprite(const std::string& spriteName) {//like getSprite
	auto it = m_animatedSprites.find(spriteName);
	if (it != m_animatedSprites.end()) 	{
		return it->second;
	}
	std::cerr << "Can't find animated sprite: " << spriteName << std::endl;
	return nullptr;
}
std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTextureAtlas(std::string textureName,
	std::string texturePath,
	std::vector<std::string> subTextures
	, const unsigned int subTextureWidth
	, const unsigned int subTextureHeight) {
		auto pTexture = loadTexture(std::move(textureName), std::move(texturePath));
		if (pTexture) {
			const unsigned int textureWidth = pTexture->width();
			const unsigned int textureHeight = pTexture->height();
			unsigned int currentTextureOffsetX = 0;
			unsigned int currentTextureOffsetY = textureHeight;

			for (auto& currentSubTextureName : subTextures)	{
				glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX) / textureWidth, static_cast<float>(currentTextureOffsetY - subTextureHeight) / textureHeight);
				glm::vec2 rightTopUV(static_cast<float>(currentTextureOffsetX + subTextureWidth) / textureWidth, static_cast<float>(currentTextureOffsetY) / textureHeight);
				pTexture->addSubTexture(std::move(currentSubTextureName), leftBottomUV, rightTopUV);
				currentTextureOffsetX += subTextureWidth;
					if (currentTextureOffsetX >= textureWidth) {
						currentTextureOffsetX = 0;
						currentTextureOffsetY -= subTextureHeight;
					}
			}
		}
	return pTexture;
}

std::shared_ptr<RenderEngine::AnimatedSprite> ResourceManager::loadAnimatedSprite(const std::string& spriteName//like loadSprite
	, const std::string& textureName
	, const std::string& shaderName
	, const unsigned int spriteWidth
	, const unsigned int spriteHeight
	, const std::string& subTextureName) {
	
	auto pTexture = getTexture(textureName);
	if (!pTexture) {
		std::cerr << "Can't find the texture: " << textureName << " for the sprite: " << spriteName << std::endl;
	}
	
	auto pShader = getShaderProgram(shaderName);
	if (!pShader) {
		std::cerr << "Can't find the shader: " << shaderName << " for the sprite: " << spriteName << std::endl;
	}
		
	//std::shared_ptr<Renderer::AnimatedSprite> newSprite = m_animatedSprites.emplace(textureName, std::make_shared<Renderer::AnimatedSprite>(pTexture,
	std::shared_ptr<RenderEngine::AnimatedSprite> newSprite = m_animatedSprites.emplace(spriteName, std::make_shared<RenderEngine::AnimatedSprite>(pTexture, subTextureName, pShader, glm::vec2(0.f, 0.f), glm::vec2(spriteWidth, spriteHeight))).first->second;
	return newSprite;
}