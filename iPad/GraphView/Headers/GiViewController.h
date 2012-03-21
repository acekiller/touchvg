// GiViewController.h
// Copyright (c) 2012, Zhang Yungui <rhcad@hotmail.com>
// License: LGPL, https://github.com/rhcad/graph2d

#import <UIKit/UIKit.h>

@class GiSelectController;

// ͼ����ͼ�Ŀ�������
@interface GiViewController : UIViewController {
    GiSelectController* _selector;  // ѡ��༭����
    id      _command;               // ��ǰ��ͼ�������֧�� GiMotionHandler
}

- (void)clearCachedData;            // �����������
- (void)dynDraw;                    // ��ͼ����ͼ��̬��ʾʱ����

// ���õ�ǰ��ͼ�������֧�� GiMotionHandler����ΪNil
- (id)setCommand:(id)cmd;

@end
