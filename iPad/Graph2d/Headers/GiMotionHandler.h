// GiMotionHandler.h
// Copyright (c) 2012, Zhang Yungui <rhcad@hotmail.com>
// License: LGPL, https://github.com/rhcad/graph2d

#import <UIKit/UIKit.h>

struct MgShapes;
class GiTransform;
class GiGraphics;

// ͼ����ͼЭ��
@protocol GiView

- (MgShapes*)getShapes;                 // �õ�ͼ���б�
- (GiTransform*)getXform;               // �õ�����ϵ����
- (GiGraphics*)getGraph;                // �õ�ͼ����ʾ����

- (void)setAnimating:(BOOL)animated;    // ��ת�򶯻���ʾʱ֪ͨ��ͼ
- (void)setDrawingDelegate:(id)d;       // ���ö�̬��ͼ�õĿ���������

- (void)redraw;                         // �����ͼ��������ʾ

@end

// ͼ����ͼ��������Э��
@protocol GiMotionHandler
@optional

- (void)dynDraw:(GiGraphics*)gs;        // ��̬��ʾͼ��
- (BOOL)undoMotion:(id)view;            // �ζ���������
- (BOOL)twoFingersPinch:(UIPinchGestureRecognizer *)sender;
- (BOOL)twoFingersPan:(UIPanGestureRecognizer *)sender;
- (BOOL)oneFingerPan:(UIPanGestureRecognizer *)sender;
- (BOOL)oneFingerTwoTaps:(UITapGestureRecognizer *)sender;
- (BOOL)oneFingerOneTap:(UITapGestureRecognizer *)sender;

@end
