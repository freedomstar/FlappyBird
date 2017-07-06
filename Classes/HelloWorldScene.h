#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
private:
    float upImpulse=150000.0f;
    bool isPass=false;
    int score=0;
    float pipeDistance=200;
    Sprite* pipe1;
    Sprite* pipe2;
    Node* rootNode;
    Sprite* spBird;
    Label* scoreLable;
    bool onTouchesBegan();
    void update(float dt);
    bool ContactBegin(const PhysicsContact &contact);
    void playAgainCallback();
};

#endif // __HELLOWORLD_SCENE_H__
