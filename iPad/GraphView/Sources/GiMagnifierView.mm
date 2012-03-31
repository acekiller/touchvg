// GiMagnifierView.mm
// Copyright (c) 2012, Zhang Yungui <rhcad@hotmail.com>
// License: LGPL, https://github.com/rhcad/graph2d

#import "GiGraphView.h"
#include "GiGraphIos.h"
#include <Graph2d/mgshapes.h>

@implementation GiMagnifierView

@synthesize graph = _graph;
@synthesize pointW = _pointW;
@synthesize scale = _scale;

- (id)initWithFrame:(CGRect)frame graphView:(id<GiView>)gview
{
    self = [super initWithFrame:frame];
    if (self) {
        _xform = new GiTransform();
        _graph = new GiGraphIos(*_xform);
        _xform->setViewScaleRange(1, 50);
        _graph->setMaxPenWidth(10);
        _gview = gview;
        _drawingDelegate = Nil;
        _scale = 3;
        
        self.multipleTouchEnabled = YES;
        self.contentMode = UIViewContentModeRedraw;
    }
    return self;
}

- (void)dealloc
{
    if (_graph) {
        delete _graph;
        _graph = NULL;
    }
    if (_xform) {
        delete _xform;
        _xform = NULL;
    }
    [super dealloc];
}

- (void)setPointW:(CGPoint)pt {
    _pointW = pt;
    Point2d ptd = Point2d(pt.x, pt.y) * _xform->worldToDisplay();
    
    if (!CGRectContainsPoint(CGRectInset(self.bounds, 20, 20), CGPointMake(ptd.x, ptd.y))) { 
        _xform->zoom(Point2d(pt.x, pt.y), _xform->getViewScale());
    }
}

- (MgShapes*)getShapes {
    return [_gview getShapes];
}

- (GiTransform*)getXform {
    return _xform;
}

- (GiGraphics*)getGraph {
    return _graph;
}

- (void)setShapes:(MgShapes*)data {
}

- (void)setAnimating:(BOOL)animated {
}

- (void)setDrawingDelegate:(id)d {
    _drawingDelegate = (UIResponder*)d;
}

- (void)regen {
    _graph->clearCachedBitmap();
    [self setNeedsDisplay];
    [_gview regen];
}

- (void)redraw {
    [self setNeedsDisplay];
}

- (void)drawRect:(CGRect)rect
{
    CGContextRef context = UIGraphicsGetCurrentContext();
    GiGraphIos* gs = (GiGraphIos*)_graph;
    
    _xform->setWndSize(CGRectGetWidth(self.bounds), CGRectGetHeight(self.bounds));
    _xform->zoom(_xform->getCenterW(), [_gview getXform]->getViewScale() * _scale);
    _graph->setBkColor(giFromCGColor(self.backgroundColor.CGColor));
    
    if (gs->beginPaint(context))
    {
        if ([[self gestureRecognizers]count] > 0 && !gs->drawCachedBitmap(0, 0)) {
            [self draw:gs];
            gs->saveCachedBitmap();
        }
        [self dynDraw:gs];
        gs->endPaint();
    }
}

- (void)draw:(GiGraphics*)gs
{
    if ([_gview getShapes]) {
        [_gview getShapes]->draw(*gs);
    }
}

- (void)dynDraw:(GiGraphics*)gs
{
    if ([_drawingDelegate respondsToSelector:@selector(dynDraw:)]) {
        [_drawingDelegate performSelector:@selector(dynDraw:) withObject:self];
    }
    
    GiContext ctx(0, GiColor(64, 64, 64, 172));
    Point2d ptd(Point2d(_pointW.x, _pointW.y) * _xform->worldToDisplay());
    gs->rawLine(&ctx, ptd.x - 20, ptd.y, ptd.x + 20, ptd.y);
    gs->rawLine(&ctx, ptd.x, ptd.y - 20, ptd.x, ptd.y + 20);
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [_drawingDelegate touchesBegan:touches withEvent:event];
    [super touchesBegan:touches withEvent:event];
}

@end