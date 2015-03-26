//
//  characterControl.h
//  Game
//
//  Created by Ms.natureQ on 15/3/22.
//
//

#ifndef __Game__characterControl__
#define __Game__characterControl__

#include <stdio.h>
#include <string>
#include "cocos2d.h"


// 角色控制
// 抽象出共性
// 现在看来至少是需要角色四个方向移动
USING_NS_CC;

typedef struct Interval
{
    int begin;
    int end;
    
}Interval;

class characterControl;

class character: public cocos2d::Node
{
public:
    enum MOVE_CONTROL
    {
        MOVE_STAY = 0,
        MOVE_RIGHT,
        MOVE_LEFT,
        MOVE_TOP,
        MOVE_DOWN,
        MOVE_RIGHT_TOP,
        MOVE_RIGHT_DOWN,
        MOVE_LEFT_TOP,
        MOVE_LEFT_DOWN,
        MOVE_MAX,
    };
    
public:
    CREATE_FUNC(character);
    bool init();
    character();
    ~character();
public:
    void ControlMove(int tid, MOVE_CONTROL type);
public:
    CC_SYNTHESIZE(character* , m_pcharacter, Character);
    CC_SYNTHESIZE(characterControl*, m_pcharacterControl, characterControl);
    

    //int m_iTid;// 类型 -> 图片资源 名称
private:
    CC_SYNTHESIZE( int, m_iCharacterTid, CharacterTid);
    Point m_rigin;// 记录自己的起始位置
    int m_NowStatus;// 当前的状态 对应 9 总状态
    
// 简化 应该是有 tid 得来的数据
    // 成员 精灵对象的成员
    //char m_cName[256];
    //char m_cResourceName[256];
    CC_SYNTHESIZE(std::string, m_Name, Name)
    CC_SYNTHESIZE(std::string, m_ResourceName, ResourceName)
    Interval m_MoveResourceInfo[MOVE_MAX];// 这里应该是一个区间
    
};




// 动画的播放
// 角色的移动
// 这个类应该只是负责 动画的播放 同时资源的加载应该也剥离出来
// 这边的资源应该如果管理  创建出来的动画 不应该不停的release
//资源控制  这里应该是一个 组合 关系
class characterControl: public cocos2d::Sprite
{
public:
    CREATE_FUNC(characterControl);
    
    void characterAnimation();
    void barbarianAnimation();
    
    // 首先我需要资源的异步加载 把这个函数做的东西 分开来
    // 然后我需要内存管理
    // 我需要配置文件在 lua 或是其他文件内部 主要是各个动作的拆分
    void createAnimation(const char * m, int fromnum, int endnum, float posx, float posy);
};

#endif /* defined(__Game__characterControl__) */
