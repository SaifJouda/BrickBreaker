#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "physics.h"
#include "paddle.h"


using namespace sf;
using namespace std;

struct Ball : public CircleShape {
    Ball(b2World &world, float x, float y, float r) {
        b2BodyDef bodyDef;
        bodyDef.position.Set(x/pixels_per_meter, y/pixels_per_meter);
        bodyDef.type = b2_dynamicBody;
        bodyDef.linearDamping = 0.0;
        b2CircleShape b2shape;

        b2shape.m_radius = r/pixels_per_meter;

        b2FixtureDef fixtureDef;
        fixtureDef.density = 1.0;
        fixtureDef.friction = 0.1;
        fixtureDef.restitution = 1.0;
        fixtureDef.shape = &b2shape;

        res = world.CreateBody(&bodyDef);
        res->CreateFixture(&fixtureDef);

        this->setRadius(r);
        this->setOrigin(r,r);
        this->setPosition(x, y);
        this->setFillColor(Color::White);

        res->SetUserData(this);

        speed = 500.0;
        angle = 220.0/deg_per_rad;
        res->SetLinearVelocity(b2Vec2(speed*cos(angle)/pixels_per_meter,speed*sin(angle)/pixels_per_meter));
    }

    sf::Vector2f getVelocity(Block b) {
        b2Vec2 vel = b->GetLinearVelocity();
        sf::Vector2f sfml_vel(vel.x*pixels_per_meter, vel.y*pixels_per_meter);
        return sfml_vel;
    }


    //member functions
    bool checkCollision()
    {
        for (b2ContactEdge* edge = res->GetContactList(); edge; edge = edge->next) {
            if (edge->contact->IsTouching()) return true;
        }
        return false;
    }

    bool checkCollision(Block b)
    {
        for (b2ContactEdge* edge = res->GetContactList(); edge; edge = edge->next) {
            if (edge->other == b) {
                if (edge->contact->IsTouching()) {
                   return true;
                }
            }
        }
        return false;
    }

    void deleteBlock(b2World &world,Block b) {
        world.DestroyBody(b);
        b->SetUserData(0);
    }

//    void setBlockTexture(const sf::Texture *t1) {
//        sf::this* shape = static_cast<sf::this*>(res->GetUserData());
//        this->setTexture(t1);
//    }

//    void setBlockTexture(const sf::Texture &t) {
//        sf::Shape* shape = static_cast<sf::Shape*>(res->GetUserData());
//        shape->setTexture(&);
//    }

    void setVelocity( sf::Vector2f vel) {
        res->SetLinearVelocity(b2Vec2(vel.x/pixels_per_meter,vel.y/pixels_per_meter));
    }

    void setVelocity(float speed, float angle) {
        res->SetLinearVelocity(b2Vec2(speed*cos(angle)/pixels_per_meter,speed*sin(angle)/pixels_per_meter));
    }

    void removeBody()
    {
        res->GetWorld()->DestroyBody(res);
        res->SetUserData(0);
    }

    float getAngle() {
        return res->GetAngle();
    }

//    void spin(Block b, float amp) {
//        b->ApplyAngularImpulse(amp,1);
//    }

    void updatePosition()
    {
        b2Vec2 velocity = res->GetLinearVelocity();
        res->SetLinearVelocity((speed/pixels_per_meter)/velocity.Length()*velocity);
        this->setPosition(res->GetPosition().x*pixels_per_meter, res->GetPosition().y*pixels_per_meter);
        this->setRotation(res->GetAngle()*deg_per_rad);
        if (velocity.y < 1.25&&velocity.y>0)
        {
            b2Vec2 vel(velocity.x, velocity.y + 4);
            res->SetLinearVelocity(vel);
        }
        if (velocity.y > -1.25&&velocity.y<=0)
        {
            b2Vec2 vel(velocity.x, velocity.y -4);
            res->SetLinearVelocity(vel);
        }
        if (velocity.x < 0.95&&velocity.x>0)
        {
            b2Vec2 vel(velocity.x+4, velocity.y );
            res->SetLinearVelocity(vel);
        }
        if (velocity.x > -0.95&&velocity.x<=0)
        {
            b2Vec2 vel(velocity.x-4, velocity.y );
            res->SetLinearVelocity(vel);
        }
    }



    void PaddleBounce(const Paddle &pb)
    {
        float d=0.0;
        if (checkCollision(pb.res))
        {
            d = (getPosition().x - pb.getPosition().x)/pb.getSize().x*2.0;
            angle= (d*55.0 - 90.0)/deg_per_rad;
            setVelocity(speed, angle);
        }

    }

    bool isDestroyed(Block b) {
        if (b->GetUserData() == 0) return true;
        else return false;
    }



//    void limitVelocity(Block b, float speed)
//    {
//        b2Vec2 velocity = b->GetLinearVelocity();
//        b->SetLinearVelocity((speed/pixels_per_meter)/velocity.Length()*velocity);
//    }


    //member variable
    b2Body* res;
    float speed;
    float angle;

};
