#include "IDrawable.h"

class Sprite : public IDrawable
{
public:
	Sprite(const sf::Texture&);

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Destroy();
private:
};