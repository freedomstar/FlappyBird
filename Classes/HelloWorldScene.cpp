#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace::ui;
using namespace cocostudio;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0,-200));
   // scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_SHAPE);
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //获得rootNode，创建brid
    rootNode=CSLoader::createNode("MainScene.csb");
    addChild(rootNode);
    auto bird=CSLoader::createTimeline("Node.csb");
    rootNode->runAction(bird);
    bird->gotoFrameAndPlay(0,20,true);
    spBird=static_cast<Sprite*>(rootNode->getChildByName("FileNode_1"));
    spBird->setScale(1.5);
    auto Birdbody = PhysicsBody::createCircle(rootNode->getChildByName("FileNode_1")->getChildByName("Sprite_1")->getBoundingBox().size.width/3.5);
    Birdbody->setContactTestBitmask(1);
    Birdbody->setCategoryBitmask(1);
    spBird->setPhysicsBody(Birdbody);
    this->addChild(spBird);
    

    //创建pipe1
    pipe1=Sprite::create("pipe1.png");
    pipe1->setScale(1.5);
    pipe1->setAnchorPoint(Vec2(0,0));
    auto pipe1body = PhysicsBody::createBox(pipe1->getBoundingBox().size/1.5);
    pipe1body->setDynamic(false);
    pipe1body->setCategoryBitmask(1);
    pipe1body->setContactTestBitmask(1);
    pipe1->setPhysicsBody(pipe1body);
    addChild(pipe1);
    

    //创建pipe2
    pipe2=Sprite::create("pipe2.png");
    pipe2->setAnchorPoint(Vec2(0,0));
    pipe2->setScale(1.5);
    auto pipe2body = PhysicsBody::createBox(pipe2->getContentSize());
    pipe2body->setDynamic(false);
    pipe2body->setCategoryBitmask(1);
    pipe2body->setContactTestBitmask(1);
    pipe2->setPhysicsBody(pipe2body);
    addChild(pipe2);
    
    //初始化pipe位置
    int h=rand()%(int)pipeDistance+pipe2->getBoundingBox().size.height+pipe1->getBoundingBox().size.height-Director::getInstance()->getWinSize().height;
    pipe1->setPosition(Vec2(Director::getInstance()->getWinSize().width,-h));
    pipe2->setPosition(Vec2(Director::getInstance()->getWinSize().width,-h+pipe1->getBoundingBox().size.height+pipeDistance));

    //添加触摸事件监听
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    auto listen = EventListenerTouchAllAtOnce::create();
    listen->onTouchesBegan = CC_CALLBACK_0(HelloWorld::onTouchesBegan,this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(listen,this);
    
    //添加碰撞事件监听
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::ContactBegin, this);
    eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    //创建成绩lable
    scoreLable= Label::create();
    scoreLable->setString("成绩:0");
    scoreLable->setSystemFontSize(50);
    scoreLable->setAnchorPoint(Vec2(0,0));
    scoreLable->setPosition(Vec2(Director::getInstance()->getWinSize().width-scoreLable->getBoundingBox().size.width,Director::getInstance()->getWinSize().height-scoreLable->getBoundingBox().size.height));
    addChild(scoreLable);
    scheduleUpdate();
    return true;
}

void HelloWorld::update(float dt)
{
    pipeMove(pipeSpeed, dt);
    
    bgMove(bgSpeed, dt);
    
    if(spBird->getPosition().y>Director::getInstance()->getWinSize().height || spBird->getPosition().y+spBird->getBoundingBox().size.height<0)
        gameOver();
    
    if(!isPass&&spBird->getPosition().x>pipe1->getPosition().x+pipe1->getBoundingBox().size.width)
        changeScore();
}

//碰撞回调函数
bool HelloWorld::ContactBegin(const PhysicsContact &contact)
{
    this->gameOver();
    return true;
}

//游戏结束
void HelloWorld::gameOver()
{
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->removeAllEventListeners();
    unscheduleUpdate();
    Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
    auto layer=CSLoader::createNode("Layer.csb");
    Text* scoreLables=static_cast<Text*>(layer->getChildByName("scoreText"));
    char str[10000] = {'0'};
    sprintf(str, "成绩:%d", score);
    scoreLables->setString(str);
    Button* Btn = dynamic_cast<Button*>(layer->getChildByName("Button_1"));
    Btn->addClickEventListener(CC_CALLBACK_0(HelloWorld::playAgainCallback, this));
    addChild(layer);
}

//更改成绩
void HelloWorld::changeScore()
{
    isPass=!isPass;
    score++;
    char str[10000] = {'0'};
    sprintf(str, "成绩:%d", score);
    scoreLable->setString(str);
    scoreLable->setPosition(Vec2(Director::getInstance()->getWinSize().width-scoreLable->getBoundingBox().size.width,Director::getInstance()->getWinSize().height-scoreLable->getBoundingBox().size.height));
}

//再玩一次（重新加载场景）
void HelloWorld::playAgainCallback()
{
    Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1);
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

//pipe移动
void HelloWorld::pipeMove(float pipeSpeed,float dt)
{
    pipe1->setPosition(Vec2(pipe1->getPosition().x-pipeSpeed*dt,pipe1->getPosition().y));
    pipe2->setPosition(Vec2(pipe1->getPosition().x,pipe2->getPosition().y));
    if (pipe1->getPosition().x <= -pipe1->getBoundingBox().size.width)
    {
        isPass=!isPass;
        int h =random(0, (int)(pipeDistance+pipe2->getBoundingBox().size.height+pipe1->getBoundingBox().size.height-Director::getInstance()->getWinSize().height));
        pipe1->setPosition(Director::getInstance()->getWinSize().width,-h);
        pipe2->setPosition(Vec2(pipe1->getPosition().x,-h+pipe1->getBoundingBox().size.height+pipeDistance));
    }
}

//背景移动
void HelloWorld::bgMove(float bgSpeed,float dt)
{
    Sprite* bg=static_cast<Sprite*> (rootNode->getChildByName("bg"));
    Sprite* bg2=static_cast<Sprite*> (rootNode->getChildByName("bg2"));
    bg->setPosition(Vec2(bg->getPosition().x-bgSpeed*dt,bg->getPosition().y));
    bg2->setPosition(Vec2(bg2->getPosition().x-bgSpeed*dt,bg2->getPosition().y));
    if (bg2->getPosition().x<=0)
    {
        bg->setPosition(Vec2(bg2->getPosition().x+bg2->getContentSize().width,bg->getPosition().y));
    }
    if (bg->getPosition().x<=0)
    {
        bg2->setPosition(Vec2(bg->getPosition().x+bg->getContentSize().width,bg2->getPosition().y));
    }
}

//触摸事件回调方法
bool HelloWorld::onTouchesBegan()
{
    spBird->getPhysicsBody()->applyImpulse(Vect(0.0f,upImpulse));
    return true;
}
