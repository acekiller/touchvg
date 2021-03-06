//! \file mgcmd.h
//! \brief 定义绘图命令接口
// Copyright (c) 2004-2012, Zhang Yungui
// License: LGPL, https://github.com/rhcad/touchvg

#ifndef __GEOMETRY_MGCOMMAND_H_
#define __GEOMETRY_MGCOMMAND_H_

#include <gigraph.h>
#include <mgshapes.h>

//! 图形视图接口
/*! \ingroup GEOM_SHAPE
    \interface MgView
*/
struct MgView {
    virtual MgShapes* shapes() = 0;             //!< 得到图形列表
    virtual GiTransform* xform() = 0;           //!< 得到坐标系对象
    virtual GiGraphics* graph() = 0;            //!< 得到图形显示对象
    virtual void regen() = 0;                   //!< 标记视图待重新构建显示
    virtual void redraw(bool fast) = 0;         //!< 标记视图待更新显示
    virtual GiContext* context() = 0;           //!< 得到当前绘图属性
    virtual bool shapeWillAdded(MgShape* shape) = 0;    //!< 通知将添加图形
    virtual void shapeAdded(MgShape* shape) = 0;        //!< 通知已添加图形，由视图重新构建显示
    virtual bool shapeWillDeleted(MgShape* shape) = 0;  //!< 通知将删除图形
};

//! 命令参数
/*! \ingroup GEOM_SHAPE
*/
struct MgMotion {
    MgView*     view;                           //!< 图形视图
    float       velocity;                       //!< 移动速度，像素每秒
    int         touchCount;                     //!< 触摸点数
    Point2d     startPoint;                     //!< 开始点，视图坐标
    Point2d     startPointM;                    //!< 开始点，模型坐标
    Point2d     lastPoint;                      //!< 上次点，视图坐标
    Point2d     lastPointM;                     //!< 上次点，模型坐标
    Point2d     point;                          //!< 当前点，视图坐标
    Point2d     pointM;                         //!< 当前点，模型坐标
    MgMotion() : view(NULL), velocity(0), touchCount(1) {}
};

//! 命令接口
/*! \ingroup GEOM_SHAPE
    \interface MgCommand
*/
struct MgCommand {
    virtual const char* getName() const = 0;                //!< 返回命令名称
    virtual void release() = 0;                             //!< 销毁对象
    virtual bool cancel(const MgMotion* sender) = 0;        //!< 取消命令
    virtual bool initialize(const MgMotion* sender) = 0;    //!< 开始命令
    virtual bool undo(bool &enableRecall, const MgMotion* sender) = 0;  //!< 回退一步
    virtual bool draw(const MgMotion* sender, GiGraphics* gs) = 0;  //!< 显示动态图形
    virtual bool click(const MgMotion* sender) = 0;         //!< 点击
    virtual bool doubleClick(const MgMotion* sender) = 0;   //!< 双击
    virtual bool longPress(const MgMotion* sender) = 0;     //!< 长按
    virtual bool touchBegan(const MgMotion* sender) = 0;    //!< 开始滑动
    virtual bool touchMoved(const MgMotion* sender) = 0;    //!< 正在滑动
    virtual bool touchEnded(const MgMotion* sender) = 0;    //!< 滑动结束
};

//! 命令管理器接口
/*! \ingroup GEOM_SHAPE
    \interface MgCommandManager
    \see mgGetCommandManager
*/
struct MgCommandManager {
    virtual const char* getCommandName() = 0;               //!< 得到当前命令名称
    virtual MgCommand* getCommand() = 0;                    //!< 得到当前命令
    virtual bool setCommand(const MgMotion* sender, const char* name) = 0;  //!< 启动命令
    virtual bool cancel(const MgMotion* sender) = 0;        //!< 取消当前命令
    virtual void unloadCommands() = 0;                      //!< 退出时卸载命令
    
    //! 得到当前选择的图形
    /*!
        \param view 当前操作的视图
        \param count 最多获取多少个图形，为0时返回实际个数
        \param shapes 填充当前选择的图形对象
        \param forChange 是否用于修改，用于修改时将复制临时图形，动态修改完后要调用 dynamicChangeEnded()
        \return 获取多少个图形，或实际个数
    */
    virtual UInt32 getSelection(MgView* view, UInt32 count, MgShape** shapes, bool forChange) = 0;
    
    //! 结束动态修改，提交或放弃所改的临时图形
    virtual bool dynamicChangeEnded(MgView* view, bool apply) = 0;
};

//! 返回命令管理器
/*! \ingroup GEOM_SHAPE
*/
MgCommandManager* mgGetCommandManager();

#endif // __GEOMETRY_MGCOMMAND_H_
