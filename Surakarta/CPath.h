/*!@file CPath.h
*******************************************************************************
功能: 路径类的声明部分, 包括机器方的路径类, 有方的路径类
******************************************************************************/

#pragma once

#include "surakarta.h"

/*!@class CMachinePath
*******************************************************************************
功能: 封装机器棋子走子时所产生路径的所有相关操作和属性
作者: rookie2(rookie2@163.com)
描述: 
******************************************************************************/
class CMachinePath
{
protected:
    PATH m_vectPath[12]; // 4个飞行方向的路径，加8个行走方向,共12个方向的路径
    PATH m_vectFinalPath; // 存放4个路径中价值最大的一条
public:
    /*!@function Push
    ***************************************************************************
    功能: 将位置点压入对应方向的路径中
    参数: c_direct [in] 指定方向
          c_pos [in] 要压入路径的位置点
    **************************************************************************/
    void Push(const DIRECTION c_direct, const POSITION c_pos);
    
    /*!@function SetFinalPath
    ***************************************************************************
    功能: 设置最终的路径
    参数: c_direct [in] 指定方向
          c_pos [in] 最后的那个位置点,加入指定方向的路径中,形成最终的走子路径
    **************************************************************************/
    void SetFinalPath(const DIRECTION c_direct, POSITION &m_pos);
    
    /*!@function SetFinalPath
    ***************************************************************************
    功能: 设置最终的路径
    参数: path [in] 路径值
          m_pos [in] 最后的位置点,该点会加入路径值中,形成最终的走子路径
    **************************************************************************/
    void SetFinalPath(PATH path, POSITION &m_pos);
 
    /*!@function GetFinalPath
    ***************************************************************************
    功能: 返回最终的走子路径
    参数: [out] path 路径的引用
    返回值: void
    **************************************************************************/
    void GetFinalPath(PATH &path);

    /*!@function GetPath
    ***************************************************************************
    功能: 返回指定方向上的路径
    参数: [in] cdirect 指定所要获取的路径的方向
          [out] path 指定方向上的路径的引用
    返回值: void
    **************************************************************************/
    void GetPath(const DIRECTION c_direct, PATH &path);
    
    /*!@funtion Condition
    ***************************************************************************
    功能: 判断当前位置是否是最外面的位置,是否需要转向飞行,进入下一轨道
    参数: pos [in] 位置值
          c_direct [out] 转向下一轨道飞行的方向值
    返回值: 如果棋子已到边缘,要转向下一轨道,则返回true,否则返回false
    **************************************************************************/
    bool Condition(POSITION &pos, const DIRECTION &c_direct);
    
    /*!@function FlagEatablePath
    ***************************************************************************
    功能: 标记可吃子的路径, 用于显示出玩家可走的地方,供玩家选择
    参数: c_posLast [in] 最后一点的位置
          c_directOriginal [in] 棋子最初走动时的方向
    **************************************************************************/
    virtual void FlagEatablePath(const POSITION c_posLast,
        const DIRECTION c_directOriginal);
    
    /*!@function FlyEngine
    ***************************************************************************
    功能: 飞行引擎, 用于搜索当前棋子所有的可走的路径
    参数: c_posOriginal [in] 棋子最初的位置, 常量
          posCur [in] 棋子此次调用的位置
          c_directOriginal [in] 棋子最初走动时的方向, 常量
          directCur [in] 棋子此次调用的方向
          bAlreadFly [in] 标记棋子是否飞行过
    **************************************************************************/
    void FlyEngine(const POSITION c_posOriginal, POSITION posCur,
	               const DIRECTION c_directOriginal, DIRECTION directCur,
                   bool bAlreadyFly
                  );
    
    /*!@function Fly
    ***************************************************************************
    功能: 将指定位置处的棋子,启动上下左右的飞行
    参数: c_pos [in] 指定棋子所在位置
    **************************************************************************/
	void Fly(const POSITION c_pos);
};

/*!@class CPath
*******************************************************************************
作者: rookie2(rookie2@163.com)
描述: 路径类, 继承至机器路径类(CMachinePath), 此路径类对象,人和机器均可调用
******************************************************************************/
class CPath: public CMachinePath
{
private:
    HWND m_hPathWnd[12]; // 标记可起子
public:
    /*!@function Walk
    ***************************************************************************
    功能: 往指定位置行走,一步走子
    参数: c_pos [in] 指定目标位置
    **************************************************************************/
    void Walk(const POSITION c_pos);
    
    /*!@function FlagEatablePath
    ***************************************************************************
    功能: 标记可吃子的路径, 用于显示出玩家可走的地方,供玩家选择
    参数: c_posLast [in] 最后一点的位置
          c_directOriginal [in] 棋子最初走动时的方向
    **************************************************************************/
	void FlagEatablePath(const POSITION c_posLast,
        const DIRECTION c_nOriginalDirect);
    
    /*!@function DestroyPathWnd
    ***************************************************************************
    功能: 销毁标记路径时用到的窗口
    **************************************************************************/
    void DestroyPathWnd();
};