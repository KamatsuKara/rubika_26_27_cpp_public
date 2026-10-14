#include "IDrawable.h"

class RectangleShape : public IDrawable
{
public:
	RectangleShape(sf::Vector2f);

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Destroy();
private:
};