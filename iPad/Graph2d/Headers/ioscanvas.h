//! \file ioscanvas.h
//! \brief Define the graphics class for iOS: GiCanvasIos
// Copyright (c) 2004-2012, Zhang Yungui
// License: LGPL, https://github.com/rhcad/touchvg

#ifndef __GEOMETRY_CANVASIOS_H_
#define __GEOMETRY_CANVASIOS_H_

#include <gicanvas.h>
#include <CoreGraphics/CGContext.h>

class GiCanvasIosImpl;

//! Convert color from CGColor.
/*! \ingroup GRAPH_IOS
*/
GiColor giFromCGColor(CGColorRef color);

//! The graphics class for iOS.
/*! getCanvasType() of this class returns 10.
    \ingroup GRAPH_IOS
    \see giFromCGColor
*/
class GiCanvasIos : public GiCanvas
{
public:
    //! Constructor with a graphics object.
    /*!
        \param gs a graphics object.
        \param dpi dots per inches. 0: use the result of setScreenDpi(). PDF: 72 dpi.
     */
    GiCanvasIos(GiGraphics* gs, float dpi = 0);
    
    virtual ~GiCanvasIos();

public:
    //! Set the screen's DPI and scale.
    /*!
        \param dpi dots per inches. iPad:132, iPhone or iPod Touch: 163.
        \param scale 
     */
    static void setScreenDpi(float dpi, float scale);
    
    //! Ready to draw shapes.
    /*!
        \param context drawing target.
        \param fast true if drawing with sketchy details.
        \param buffered true if drawing on a cached bitmap, otherwise drawing directly on the target context.
        \return true if successful.
     */
    bool beginPaint(CGContextRef context, bool fast = false, bool buffered = true);
    
    //! Ready to draw shapes on a cached bitmap.
    bool beginPaintBuffered(bool fast);
    
    //! End to draw shapes and output to the view.
    void endPaint(bool draw = true);
    
    //! Create a bitmap inverted or get the original cached bitmap.
    CGImageRef cachedBitmap(bool invert = true);

// Implement the GiCanvas interface.
public:
    virtual void clearWindow();
    virtual bool drawCachedBitmap(float x = 0, float y = 0, bool secondBmp = false);
    virtual bool drawCachedBitmap2(const GiCanvas* p, 
        float x = 0, float y = 0, bool secondBmp = false);
    virtual void saveCachedBitmap(bool secondBmp = false);
    virtual bool hasCachedBitmap(bool secondBmp = false) const;
    virtual void clearCachedBitmap();
    virtual bool isBufferedDrawing() const;
    virtual int getCanvasType() const { return 10; }
    virtual float getScreenDpi() const;
    
    virtual GiColor getBkColor() const;
    virtual GiColor setBkColor(const GiColor& color);
    virtual const GiContext* getCurrentContext() const;
    virtual void _clipBoxChanged(const RECT2D& clipBox);
    virtual void _antiAliasModeChanged(bool antiAlias);

    virtual bool rawLine(const GiContext* ctx, float x1, float y1, float x2, float y2);
    virtual bool rawLines(const GiContext* ctx, const Point2d* pxs, int count);
    virtual bool rawBeziers(const GiContext* ctx, const Point2d* pxs, int count);
    virtual bool rawPolygon(const GiContext* ctx, const Point2d* pxs, int count);
    virtual bool rawRect(const GiContext* ctx, float x, float y, float w, float h);
    virtual bool rawEllipse(const GiContext* ctx, float x, float y, float w, float h);
    virtual bool rawPath(const GiContext* ctx, 
        int count, const Point2d* pxs, const UInt8* types);
    
    virtual bool rawBeginPath();
    virtual bool rawEndPath(const GiContext* ctx, bool fill);
    virtual bool rawMoveTo(float x, float y);
    virtual bool rawLineTo(float x, float y);
    virtual bool rawBezierTo(const Point2d* pxs, int count);
    virtual bool rawClosePath();

private:
    GiCanvasIos();
    GiCanvasIosImpl*   m_draw;
};

#endif // __GEOMETRY_CANVASIOS_H_
