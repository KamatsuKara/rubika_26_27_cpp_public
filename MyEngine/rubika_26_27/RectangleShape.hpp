#include "IDrawable.h"

#include "TextureMgr.h"

class RectangleShape : public IDrawable
{
public:
	RectangleShape();
	
	void setFillColor(sf::Color);

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Destroy();

	bool SetTexture(const std::string&);
	bool SetStaticTile(const std::string&);
	bool SetTextureAndStaticTile(const std::string&, const std::string&);
private:
	const TextureData* textureData = nullptr;
	const StaticTileData* staticTileData = nullptr;

};