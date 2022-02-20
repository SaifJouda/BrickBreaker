#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

struct Brick : public sf:: RectangleShape {
    //Constructor
    Brick (b2World &world, float x, float y, float width, float height) {
            b2BodyDef bodyDef;
            bodyDef.position.Set((x + width/2.0)/pixels_per_meter, (y + height/2.0)/pixels_per_meter);
            bodyDef.type = b2_staticbody;
            bodyDef.linearDamping = 0.05;
            b2PolygonShape b2shape;
            b2shape.SetAsBox(width/pixels_per_meter/2.0, height/pixels_per_meter/2.0);
            b2FixtureDef fixtureDef;
            fixtureDef.density = 1.0;
            fixtureDef.friction = 0.4;
            fixtureDef.restitution = 0.5;
            fixtureDef.shape = &b2shape;

            b2Body* res = world.CreateBody(&bodyDef);
            res->CreateFixture(&fixtureDef);

            sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(width, height));
            this->setOrigin(width/2.0, height/2.0);
            this->setPosition(x, y);
            this->setFillColor(sf::Color::White);

            res->SetUserData(shape);


    }
};
