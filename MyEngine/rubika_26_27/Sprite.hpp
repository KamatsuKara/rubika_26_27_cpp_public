#include "IDrawable.h"
#include "TextureMgr.h"

class Sprite : public IDrawable
{
public:
	Sprite(const sf::Texture&);

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Destroy();
	bool SetTexture(const std::string&);
	bool SetAnimation(const std::string&);
	bool SetTextureAndAnimation(const std::string&, const std::string&);
private:
	sf::Sprite* sprite;
	const TextureData* textureData = nullptr;
	const AnimationData* animationData = nullptr;
	unsigned animationStep = 0;
};