#pragma once
#include<afxwin.h>
#include "Vector2.h"
#include <cmath>

enum  ElementType { NOTSET = 0, SQUARE, RECTANGLE, CIRCLE, ELLIPSE, TRIANGLE, TEXT };
struct shape
{
	int Type;
	int OrgX;
	int OrgY;
	COLORREF   BorderColor;
	int BorderType;
	int BorderWidth;
	COLORREF  FillColor;
	int FillType;
	int Height;
	int Width;
	CString Str;
};

class CShape : public CObject
{
public:
	CShape();
	//virtual ~CShape()=0;
	virtual void Draw(CDC* pDC) = 0;//绘制
	virtual bool IsMatched(CPoint pnt) = 0;//点是否落在图形内部
	virtual void Serialize(CArchive& ar) = 0;//序列化存储到数组里面
	virtual void SetShapePos(int x,int y,int w,int h=0, CString s = L"")=0;
	virtual void SetPen(int w=0, int c=0, COLORREF cc=RGB(255,0,255)) = 0;
	virtual void SetBrush(int c = 0, COLORREF cc = RGB(0, 0, 0)) = 0;
	virtual shape GetShape();
protected:
	ElementType Type;//图元类型
	int OrgX;//原点坐标
	int OrgY;
	COLORREF   BorderColor;//边界颜色
	int BorderType;//边界线型--实线、虚线、虚点线等
	int BorderWidth;//边界宽度
	COLORREF  FillColor;//填充颜色
	int FillType;//填充类型--实心、双对角、十字交叉等
};

class CSquare : public CShape
{
public:
	CSquare();
	CSquare(int x, int y, int w);
	void Draw(CDC* pDC);//绘制正方形
	bool IsMatched(CPoint pnt);//重载点pnt是否落在图元内
	virtual void Serialize(CArchive& ar);//序列化正方形图元
	virtual void SetShapePos(int x, int y, int w, int h, CString s);
	virtual void SetPen(int w, int c, COLORREF cc);
	virtual void SetBrush(int c, COLORREF cc );
	virtual shape GetShape();
private:
	int width;

	DECLARE_SERIAL(CSquare)//声明类CSquare支持序列化
};

//矩形
class CRectangle : public CShape
{
private:
	int width, Height;
public:
	DECLARE_SERIAL(CRectangle)
	CRectangle();
	CRectangle(int x, int y, int w, int h);
	void Draw(CDC* pDC);//绘制长方形
	bool IsMatched(CPoint pnt);//重载点pnt是否落在图元内
	virtual void Serialize(CArchive& ar);//序列化正方形图元
	virtual void SetShapePos(int x, int y, int w, int h, CString s);
	virtual void SetPen(int w, int c, COLORREF cc);
	virtual void SetBrush(int c, COLORREF cc);
	virtual shape GetShape();
};
//圆形
class CCircle : public CShape
{
public:
	CCircle();
	CCircle(int x, int y, int R);
	void Draw(CDC* pDC);
	bool IsMatched(CPoint pnt);//重载点pnt是否落在图元内
	virtual void Serialize(CArchive& ar);//序列化正方形图元
	virtual void SetShapePos(int x, int y, int w, int h, CString s);
	virtual void SetPen(int w, int c, COLORREF cc);
	virtual void SetBrush( int c, COLORREF cc);
	virtual shape GetShape();
private:
	int R;
	DECLARE_SERIAL(CCircle)//声明类CSquare支持序列化
};
//椭圆形
class CEllipse : public CShape
{
public:
	CEllipse();
	CEllipse(int x, int y, int w, int h);
	void Draw(CDC* pDC);
	bool IsMatched(CPoint pnt);
	virtual void Serialize(CArchive& ar);
	virtual void SetShapePos(int x, int y, int w, int h, CString s);
	virtual void SetPen(int w, int c, COLORREF cc);
	virtual void SetBrush( int c, COLORREF cc);
	virtual shape GetShape();
private:
	int width, height;
	DECLARE_SERIAL(CEllipse)//声明类CSquare支持序列化
};

//三角形
class CTriangle : public CShape
{
public:
	CTriangle();
	CTriangle(int x, int y, int w);
	void Draw(CDC* pDC);
	bool IsMatched(CPoint pnt);//重载点pnt是否落在图元内
	virtual void Serialize(CArchive& ar);//序列化正方形图元
	virtual void SetShapePos(int x, int y, int w, int h, CString s);
	virtual void SetPen(int w, int c, COLORREF cc);
	virtual void SetBrush(int c, COLORREF cc);
	virtual shape GetShape();
private:
	int width;

	DECLARE_SERIAL(CTriangle)//声明类CSquare支持序列化
};
//文字
class CText : public CShape
{
public:
	CText();
	CText(int x, int y, int h, int a, const char* s);
	void Draw(CDC* pDC);
	bool IsMatched(CPoint pnt);//重载点pnt是否落在图元内
	virtual void Serialize(CArchive& ar);//序列化正方形图元
	virtual void SetShapePos(int x, int y, int w, int h, CString s);
	virtual void SetPen(int w, int c, COLORREF cc);
	virtual void SetBrush( int c, COLORREF cc);
	virtual shape GetShape();
private:
	int height;
	int angle;
	CString str;
	CSize  size;
	DECLARE_SERIAL(CText)//声明类CSquare支持序列化
};

