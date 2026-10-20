#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main() {
    RenderWindow window(VideoMode(800, 600), "Lab 07 - Bounce");
    window.setFramerateLimit(60);
    World world(Vector2f(0, 1));

    PhysicsCircle ball;
    ball.setSize(Vector2f(40, 40));
    ball.setCenter(Vector2f(400, 100));
    world.AddPhysicsBody(ball);
    ball.applyImpulse(Vector2f(0, 0.4f));

    PhysicsRectangle floor;
    floor.setSize(Vector2f(800, 20));
    floor.setCenter(Vector2f(400, 590));
    floor.setStatic(true);
    world.AddPhysicsBody(floor);

    PhysicsRectangle ceiling;
    ceiling.setSize(Vector2f(800, 20));
    ceiling.setCenter(Vector2f(400, 10));
    ceiling.setStatic(true);
    world.AddPhysicsBody(ceiling);
    PhysicsRectangle leftWall;
    leftWall.setSize(Vector2f(20, 560));
    leftWall.setCenter(Vector2f(10, 300));
    leftWall.setStatic(true);
    world.AddPhysicsBody(leftWall);

    PhysicsRectangle rightWall;
    rightWall.setSize(Vector2f(20, 560));
    rightWall.setCenter(Vector2f(790, 300));
    rightWall.setStatic(true);
    world.AddPhysicsBody(rightWall);

    PhysicsRectangle centerBox;
    centerBox.setSize(Vector2f(160, 20));
    centerBox.setCenter(Vector2f(400, 300));
    centerBox.setStatic(true);
    centerBox.setFillColor(Color::Red);
    world.AddPhysicsBody(centerBox);

    int thudCount(0);
    int bang(0);
    const int hitsToExit(3);

    floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        thudCount++;
        cout << "thud " << thudCount << endl;
        };
    ceiling.onCollision = floor.onCollision;
    leftWall.onCollision = floor.onCollision;
    rightWall.onCollision = floor.onCollision;

    centerBox.onCollision = [&bang, hitsToExit](PhysicsBodyCollisionResult result) {
        bang++;
        cout << "bang " << bang << endl;
        if (bang >= hitsToExit) {
            exit(0);
        }
        };

    Clock clock;
    Time lastTime(clock.getElapsedTime());

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        if (!window.isOpen()) {
            break;
        }

        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime);
        int deltaTimeMS(deltaTime.asMilliseconds());
        if (deltaTimeMS > 0) {
            world.UpdatePhysics(deltaTimeMS, 1);
            lastTime = currentTime;
        }

        window.clear(Color::Black);
        window.draw(ball);
        window.draw(floor);
        window.draw(ceiling);
        window.draw(leftWall);
        window.draw(rightWall);
        window.draw(centerBox);
        window.display();
    }

    return 0;
}

