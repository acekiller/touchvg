//! \file GiGraphView.h
//! \brief 定义图形视图类 GiGraphView
// Copyright (c) 2012, Zhang Yungui <rhcad@hotmail.com>
// License: LGPL, https://github.com/rhcad/touchvg

#import "GiMotionHandler.h"

class GiGraphIos;

//! 图形视图类
/*! \ingroup GRAPH_IOS
*/
@interface GiGraphView : UIView<GiView, GiMotionHandler> {
@protected
    MgShapes*       _shapes;                //!< 图形列表
    GiGraphIos*     _graph;                 //!< 图形显示对象
    id              _drawingDelegate;       //!< 动态绘图用的委托控制器对象
    MgShape*        _shapeAdded;            //!< 待添加显示的图形
    BOOL            _cachedDraw;            //!< 刷新显示时是否使用缓冲图
    
    CGPoint         _firstPoint;            //!< 动态放缩用的开始点    
    BOOL            _enableZoom;            //!< 是否允许放缩或平移
    BOOL            _zooming;               //!< 是否正在动态放缩或平移
    float           _lastViewScale;         //!< 动态放缩前的显示比例
    CGPoint         _lastCenterW;           //!< 动态放缩前的视图中心世界坐标
    float           _lastDistPan;           //!< 上次的平移双指距离，用于放缩
    float           _lastScalePan;          //!< 上次的平移双指放大倍数
    
    BOOL            _doubleZoomed;          //!< 是否为局部放大状态
    float           _scaleBeforeDbl;        //!< 局部放大前的显示比例
    CGPoint         _centerBeforeDbl;       //!< 局部放大前的视图中心世界坐标
}

@property (nonatomic)          BOOL         enableZoom; //!< 是否允许放缩或平移
@property (nonatomic,readonly) BOOL         zooming;    //!< 是否正在动态放缩或平移

- (CGImageRef)cachedBitmap:(BOOL)invert;    //!< 当前缓存位图，上下翻转时由调用者释放

- (void)afterCreated;                                   //!< 视图窗口后内部调用
- (BOOL)draw:(GiGraphics*)gs;                           //!< 显示全部图形内部调用

@end

//! 放大镜视图类
/*! \ingroup GRAPH_IOS
 */
@interface GiMagnifierView : UIView<GiView> {
@protected
    GiGraphIos*     _graph;                 //!< 图形显示对象
    id<GiView>      _gview;                 //!< 实际图形视图
    UIResponder*    _drawingDelegate;       //!< 动态绘图用的委托控制器对象
    MgShape*        _shapeAdded;            //!< 待添加显示的图形
    BOOL            _cachedDraw;            //!< 刷新显示时是否使用缓冲图
    CGPoint         _pointW;                //!< 实际图形视图的当前点，世界坐标
    CGFloat         _scale;                 //!< 放大倍数
    BOOL            _lockRedraw;            //!< 禁止放大镜动态显示
    BOOL            _zooming;               //!< 是否正在动态放缩或平移
}

@property (nonatomic)          CGPoint      pointW;     //!< 实际图形视图的当前点，世界坐标
@property (nonatomic)          CGFloat      scale;      //!< 放大倍数
@property (nonatomic)          BOOL         lockRedraw; //!< 禁止放大镜动态显示

//! 给定视图外框和实际图形视图初始化本视图对象
- (id)initWithFrame:(CGRect)frame graphView:(id<GiView>)gview;

//! 在本视图内平移显示
- (void)zoomPan:(CGPoint)ranslation;

- (BOOL)twoFingersPan:(UIPanGestureRecognizer *)sender;

//! 设置实际图形视图的当前点（世界坐标）并刷新显示
- (void)setPointWandRedraw:(CGPoint)ptw;

//! 根据实际图形视图中的当前位置自动移动上级视图，以便当前位置不被本视图遮挡
- (BOOL)automoveSuperview:(CGPoint)point fromView:(UIView*)view;

- (BOOL)draw:(GiGraphics*)gs;                           //!< 显示全部图形内部调用
- (void)dynDraw:(GiGraphics*)gs;                        //!< 动态显示时内部调用
- (BOOL)isActiveView;                                   //!< 返回本视图是否为当前交互视图

@end
