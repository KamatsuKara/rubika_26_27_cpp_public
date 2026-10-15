#include "IDrawable.h"

class RectangleShape : public IDrawable
{
public:
	RectangleShape();
	
	void setFillColor(sf::Color);

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Destroy();
private:

};