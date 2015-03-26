//
//  characterControl.cpp
//  Game
//
//  Created by Ms.natureQ on 15/3/22.
//
//

#include "characterControl.h"

USING_NS_CC;

character::character()
{
    CCLOG("character::character()");
    m_pcharacter = NULL;
    m_pcharacterControl = NULL;
    m_iCharacterTid = 0;
    m_Name.clear();
    m_ResourceName.clear();
    for (int i = MOVE_STAY; i <= MOVE_MAX; i++)
    {
        m_MoveResourceInfo[i].begin = 0;
        m_MoveResourceInfo[i].end = 0;
    }
}

character::~character()
{
    CCLOG("character::~character()");
}

bool character::init()
{
    // 初始化一些数据
    CCLOG("character init");
    
    if (!Node::init())
    {
        return false;
    }
    
    m_pcharacter = this;
    m_pcharacterControl = characterControl::create();
    m_Name.clear();
    m_ResourceName.clear();
    m_iCharacterTid = 0;
    //m_Name = "test";
    //m_ResourceName = "test";
    setCharacter(this);
    return true;
}


void character::ControlMove(int tid,MOVE_CONTROL type)
{
    // 初始化一些数据
    CCLOG("character::ControlMove tid = %d", getCharacterTid());
    
    setCharacterTid( tid );
    
    
    CCASSERT(m_iCharacterTid, "m_iCharacterTid error");
    CCASSERT(!m_Name.empty(), "Name error");
    CCASSERT(!m_ResourceName.empty(), "ResourceName error");
    
    // 通过tid 查询这些数据
    
    m_pcharacterControl = characterControl::create();
    m_pcharacterControl->createAnimation(m_ResourceName.c_str(), m_MoveResourceInfo[type].begin, m_MoveResourceInfo[type].end, 0, 0);
    addChild(m_pcharacterControl);
}



void characterControl::characterAnimation()
{
    CCLOG("characterControl");
    
    Texture2D::PVRImagesHavePremultipliedAlpha(true);
    
    SpriteFrameCache * spriteFrameCache = SpriteFrameCache::sharedSpriteFrameCache();
    
    spriteFrameCache->addSpriteFramesWithFile("res/archer.plist");
    
    //此处是一种优化做法，但是具体的优化度，本人尚未测试，待后期给大家一个答复
    CCSpriteBatchNode *spriteBatchNode = CCSpriteBatchNode::create("res/archer.png");
    addChild(spriteBatchNode);
    
    //利用帧缓存创建精灵
    Sprite* sp = Sprite::createWithSpriteFrameName("1.0.png");
    sp->setPosition(ccp(170, 200));
    spriteBatchNode->addChild(sp);
    //创建一个序列帧的vector
    Vector<SpriteFrame *>  spriteFrame;
    char str[100] = { 0 };
    for (int i = 1; i <= 52; i++){
        sprintf(str, "%d.0.png", i);
        SpriteFrame *frame = spriteFrameCache->getSpriteFrameByName(str);
        //将每帧的动画信息存入vector
        spriteFrame.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(spriteFrame, 0.2f);
    animation->setLoops(-1);
    
    sp->runAction(Animate::create(animation));
    spriteFrameCache->removeSpriteFrameByName("archer.plist");
}


void characterControl::barbarianAnimation()
{
    CCLOG("characterControl::barbarianAnimation");
    
    Texture2D::PVRImagesHavePremultipliedAlpha(true);
    
    SpriteFrameCache * spriteFrameCache = SpriteFrameCache::sharedSpriteFrameCache();
    
    spriteFrameCache->addSpriteFramesWithFile("res/barbarian.plist");
    
    //此处是一种优化做法，但是具体的优化度，本人尚未测试，待后期给大家一个答复
    CCSpriteBatchNode *spriteBatchNode = CCSpriteBatchNode::create("res/barbarian.png");
    addChild(spriteBatchNode);
    
    //利用帧缓存创建精灵
    Sprite* sp = Sprite::createWithSpriteFrameName("683.0.png");
    sp->setPosition(ccp(270, 200));
    spriteBatchNode->addChild(sp);
    //创建一个序列帧的vector
    Vector<SpriteFrame *>  spriteFrame;
    char str[100] = { 0 };
    for (int i = 683; i <= 856; i++){
        sprintf(str, "%d.0.png", i);
        SpriteFrame *frame = spriteFrameCache->getSpriteFrameByName(str);
        //将每帧的动画信息存入vector
        spriteFrame.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(spriteFrame, 0.2f);
    animation->setLoops(-1);
    
    sp->runAction(Animate::create(animation));
    spriteFrameCache->removeSpriteFrameByName("barbarian.plist");
}

void characterControl::createAnimation(const char * pname, int fromnum, int endnum, float posx, float posy)
{
    CCLOG("characterControl::createAnimation");
    
    Texture2D::PVRImagesHavePremultipliedAlpha(true);
    
    SpriteFrameCache * spriteFrameCache = SpriteFrameCache::sharedSpriteFrameCache();
    
    char buf[1024] = {0};
    sprintf(buf, "res/%s.plist", pname);
    CCLOG("buf = %s", buf);
    spriteFrameCache->addSpriteFramesWithFile(buf);
    
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "res/%s.png", pname);
    //此处是一种优化做法，但是具体的优化度，本人尚未测试，待后期给大家一个答复
    CCLOG("buf = %s", buf);
    CCSpriteBatchNode *spriteBatchNode = CCSpriteBatchNode::create(buf);
    addChild(spriteBatchNode);
    
    //利用帧缓存创建精灵
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%d.0.png", fromnum);
    CCLOG("buf = %s", buf);
    Sprite* sp = Sprite::createWithSpriteFrameName(buf);
    sp->setPosition(ccp(posx, posy));
    spriteBatchNode->addChild(sp);
    //创建一个序列帧的vector
    Vector<SpriteFrame *>  spriteFrame;
    char str[1024] = { 0 };
    for (int i = fromnum; i <= endnum; i++)
    {
        memset(str, 0, sizeof(str));
        sprintf(str, "%d.0.png", i);
        CCLOG("str = %s", str);
        SpriteFrame *frame = spriteFrameCache->getSpriteFrameByName(str);
        
        //将每帧的动画信息存入vector
        spriteFrame.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(spriteFrame, 0.2f);
    animation->setLoops(-1);
    
    sp->runAction(Animate::create(animation));
    sp->setScale(2);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "res/%s.plist", pname);
    CCLOG("buf = %s", buf);
    spriteFrameCache->removeSpriteFrameByName(buf);
}
