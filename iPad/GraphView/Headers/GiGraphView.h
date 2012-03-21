// GiGraphView.h
// Copyright (c) 2012, Zhang Yungui <rhcad@hotmail.com>
// License: LGPL, https://github.com/rhcad/graph2d

#import <Graph2d/GiMotionHandler.h>

// ��ռ��ʾ��ͼ����ͼ��
@interface GiGraphView : UIView<GiView, GiMotionHandler> {
    MgShapes*       _shapes;                // ͼ���б�
    GiTransform*    _xform;                 // ����ϵ����
    GiGraphics*     _graph;                 // ͼ����ʾ����
    id              _drawingDelegate;       // ��̬��ͼ�õ�ί�п���������
    
    CGPoint         _firstPoint;            // ��̬�����õĿ�ʼ��
    CGPoint         _lastPoint;             // ��̬�����õ��ϴε�
    
    BOOL            _zooming;               // �Ƿ����ڶ�̬������ƽ��
    double          _lastViewScale;         // ��̬����ǰ����ʾ����
    CGPoint         _lastCenterW;           // ��̬����ǰ����ͼ������������
    
    BOOL            _doubleZoomed;          // �Ƿ�Ϊ�ֲ��Ŵ�״̬
    double          _scaleBeforeDbl;        // �ֲ��Ŵ�ǰ����ʾ����
    CGPoint         _centerBeforeDbl;       // �ֲ��Ŵ�ǰ����ͼ������������
}

@property (nonatomic,readonly) MgShapes*    shapes;     // ͼ���б�
@property (nonatomic,readonly) GiTransform* xform;      // ����ϵ����
@property (nonatomic,readonly) GiGraphics*  graph;      // ͼ����ʾ����
@property (nonatomic,readonly) BOOL         zooming;    // �Ƿ����ڶ�̬������ƽ��

- (void)afterCreated;
- (void)draw:(GiGraphics*)gs;

@end

