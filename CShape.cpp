#include "pch.h"
#include "CShape.h"
IMPLEMENT_SERIAL(CSquare, CObject, 1)//实现类CSquare的序列化，指定版本为1
IMPLEMENT_SERIAL(CRectangle, CObject, 1)
IMPLEMENT_SERIAL(CCircle, CObject, 1)
IMPLEMENT_SERIAL(CEllipse, CObject, 1)
IMPLEMENT_SERIAL(CTriangle, CObject, 1)
IMPLEMENT_SERIAL(CText, CObject, 1)//同上

const double PI = 3.1415;
//基类
CShape::CShape()
{
	Type = NOTSET;
	OrgX = 0;
	OrgY = 0;
	BorderType = 0;
	FillType = 6;
	BorderWidth = 0;
	BorderColor = RGB(255, 255, 255);
	FillColor = RGB(255, 255, 255);
}
shape CShape::GetShape() 
{
	shape t;
	t.Type = Type;
	t.OrgX = OrgX;
	t.OrgY = OrgY;
	t.BorderType = BorderType;
	t.FillType = FillType;
	t.BorderColor = BorderColor;
	t.BorderWidth = BorderWidth;
	t.BorderColor = BorderColor;
	t.FillColor = FillColor;
	t.Str = "";
	t.Height = 0;
	t.Width = 0;
	return t;
}
//正方形
CSquare::CSquare() :CShape::CShape()
{
	Type = SQUARE; width = 0;
};
CSquare::CSquare(int x, int y, int w) :CShape::CShape()
{
	Type = SQUARE;
	OrgX = x;
	OrgY = y;
	width = w;
}
void CSquare::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD)Type;
		ar << OrgX << OrgY;
		ar << BorderColor;
		ar << BorderType;
		ar << BorderWidth;
		ar << FillColor;
		ar << FillType;
		ar << width;
	}
	else
	{
		WORD w;
		ar >> w;
		Type = (ElementType)w;
		ar >> OrgX >> OrgY;
		ar >> BorderColor;
		ar >> BorderType;
		ar >> BorderWidth;
		ar >> FillColor;
		ar >> FillType;
		ar >> width;
	}
}
void CSquare::Draw(CDC* pDC)//绘制图形函数
{
	CPen pen, * pOldPen;//画笔 对象和指针
	pen.CreatePen(BorderType, BorderWidth, BorderColor);//初始化画笔的属性
	pOldPen = (CPen*)pDC->SelectObject(&pen);//保存 画笔原来的数据 等会要还原原来的属性
	CBrush brush, * pOldBrush;
	if (FillType >= HS_HORIZONTAL && FillType <= HS_DIAGCROSS)	//HS_HORIZONTAL = 0;HS_DIAGCROSS = 5; 宏定义 最大为5 代表每一个 填充的方式
		brush.CreateHatchBrush(FillType, FillColor);
	else
		brush.CreateSolidBrush(FillColor);
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);
	pDC->Rectangle(OrgX - width / 2, OrgY - width / 2, OrgX + width / 2, OrgY + width / 2);//两个顶点的坐标
	pDC->SelectObject(pOldPen);//Old还原。这样做是为了其它Windows程序，因为有的Windows程序直接使用默认的画笔和画刷进行绘图
	pDC->SelectObject(pOldBrush);
}

bool CSquare::IsMatched(CPoint pnt)//图元匹配函数
{
	if (pnt.x > (OrgX - width / 2) && pnt.x < (OrgX + width / 2))
		if (pnt.y > (OrgY - width / 2) && pnt.y < (OrgY + width / 2))
			return true;
	return false;
}
void CSquare::SetShapePos(int x, int y, int w, int h=0, CString s = L"")
{
	OrgX = x;
	OrgY = y;
	width = w;
}
void CSquare::SetPen(int w = 0, int c = 0, COLORREF cc= RGB(255, 255, 255))
{
	BorderColor = cc;
	BorderType = c;
	BorderWidth=w;
}
void CSquare::SetBrush( int c = 0, COLORREF cc = RGB(0, 0, 0))
{
	FillColor = cc;
	FillType = c;
}
shape CSquare::GetShape()
{
	shape t=CShape::GetShape();
	t.Width = width;
	return t;
}
//长方形
CRectangle::CRectangle() :CShape::CShape()
{
	Type = RECTANGLE;
	width = 0; Height = 0;
}
CRectangle::CRectangle(int x, int y, int w, int h) : CShape::CShape()
{
	Type = RECTANGLE;
	OrgX = x;
	OrgY = y;
	width = w;
	Height = h;
}
void CRectangle::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD)Type;
		ar << OrgX << OrgY;//原点坐标
		ar << BorderColor;//边界颜色
		ar << BorderType;
		ar << BorderWidth;//边界宽度
		ar << FillColor;//
		ar << FillType;
		ar << width;
		ar << Height;
	}
	else
	{
		WORD w;
		ar >> w;
		Type = (ElementType)w;
		ar >> OrgX >> OrgY;//原点坐标
		ar >> BorderColor;//边界颜色
		ar >> BorderType;
		ar >> BorderWidth;//边界宽度
		ar >> FillColor;//
		ar >> FillType;
		ar >> width;
		ar >> Height;
	}
}

void CRectangle::Draw(CDC* pDC)//绘制图形函数
{
	CPen pen, * pOldPen;//画笔 对象和指针
	pen.CreatePen(BorderType, BorderWidth, BorderColor);//初始化画笔的属性
	pOldPen = (CPen*)pDC->SelectObject(&pen);//保存 画笔原来的数据 等会要还原原来的属性
	CBrush brush, * pOldBrush;
	if (FillType >= HS_HORIZONTAL && FillType <= HS_DIAGCROSS)	//HS_HORIZONTAL = 0;HS_DIAGCROSS = 5; 宏定义 最大为5 代表每一个 填充的方式
		brush.CreateHatchBrush(FillType, FillColor);
	else
		brush.CreateSolidBrush(FillColor);
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);
	pDC->Rectangle(OrgX - width / 2, OrgY - Height / 2, OrgX + width / 2, OrgY + Height / 2);//两个顶点的坐标
	pDC->SelectObject(pOldPen);//Old还原。这样做是为了其它Windows程序，因为有的Windows程序直接使用默认的画笔和画刷进行绘图
	pDC->SelectObject(pOldBrush);
}
bool CRectangle::IsMatched(CPoint pnt)//图元匹配函数
{
	if (pnt.x > (OrgX - width / 2) && pnt.x < (OrgX + width / 2))
		if (pnt.y > (OrgY - Height / 2) && pnt.y < (OrgY + Height / 2))
			return true;
	return false;
}
void CRectangle::SetShapePos(int x, int y, int w, int h=0, CString s = L"")
{
	OrgX = x;
	OrgY = y;
	width = w;
	Height = h;
}
void CRectangle::SetPen(int w = 0, int c = 0, COLORREF cc = RGB(255, 255, 255))
{
	BorderColor = cc;
	BorderType = c;
	BorderWidth = w;
}
void CRectangle::SetBrush(int c = 0, COLORREF cc = RGB(0, 0, 0))
{
	FillColor = cc;
	FillType = c;
}
shape CRectangle::GetShape()
{
	shape t = CShape::GetShape();
	t.Width = width;
	t.Height = Height;
	return t;
}

//圆形
CCircle::CCircle() :CShape::CShape()
{
	Type = CIRCLE;
	R = 0;
};
CCircle::CCircle(int x, int y, int w) :CShape::CShape()
{
	Type = CIRCLE;
	OrgX = x;
	OrgY = y;
	R = w;
}
void CCircle::CCircle::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD)Type;
		ar << OrgX << OrgY;//原点坐标
		ar << BorderColor;//边界颜色
		ar << BorderType;
		ar << BorderWidth;//边界宽度
		ar << FillColor;//
		ar << FillType;
		ar << R;
	}
	else
	{
		WORD w;
		ar >> w;
		Type = (ElementType)w;
		ar >> OrgX >> OrgY;//原点坐标
		ar >> BorderColor;//边界颜色
		ar >> BorderType;
		ar >> BorderWidth;//边界宽度
		ar >> FillColor;//
		ar >> FillType;
		ar >> R;
	}
}
void CCircle::Draw(CDC* pDC)//绘制图形函数
{
	CPen pen, * pOldPen;//画笔 对象和指针
	pOldPen = (CPen*)pDC->SelectObject(&pen);//保存 画笔原来的数据 等会要还原原来的属性
	pen.CreatePen(BorderType, BorderWidth, BorderColor);//初始化画笔的属性
	CBrush brush, * pOldBrush;
	if (FillType >= HS_HORIZONTAL && FillType <= HS_DIAGCROSS)	//HS_HORIZONTAL = 0;HS_DIAGCROSS = 5; 宏定义 最大为5 代表每一个 填充的方式
		brush.CreateHatchBrush(FillType, FillColor);
	else
		brush.CreateSolidBrush(FillColor);
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);
	pDC->Ellipse(OrgX - R, OrgY - R, OrgX + R, OrgY + R);
	pDC->SelectObject(pOldPen);//Old还原。这样做是为了其它Windows程序，因为有的Windows程序直接使用默认的画笔和画刷进行绘图
	pDC->SelectObject(pOldBrush);
}

bool CCircle::IsMatched(CPoint pnt)//图元匹配函数
{
	if ((pow(pnt.x - OrgX, 2) + pow(pnt.y - OrgY, 2)) < pow(R, 2))
		return true;
	return false;
}
void CCircle::SetShapePos(int x, int y, int w, int h=0, CString s = L"")
{
	OrgX = x;
	OrgY = y;
	R = w;
}
void CCircle::SetPen(int w = 0, int c = 0, COLORREF cc = RGB(255, 255, 255))
{
	BorderColor = cc;
	BorderType = c;
	BorderWidth = w;
}
void CCircle::SetBrush(int c = 0, COLORREF cc = RGB(0, 0, 0))
{
	FillColor = cc;
	FillType = c;
}
shape CCircle::GetShape()
{
	shape t = CShape::GetShape();
	t.Width = R;
	return t;
}

//椭圆
CEllipse::CEllipse() :CShape::CShape()
{
	Type = ELLIPSE;
	width = height = 0;
};
CEllipse::CEllipse(int x, int y, int w, int h) :CShape::CShape()
{
	Type = ELLIPSE;
	OrgX = x;
	OrgY = y;
	width = w;
	height = h;
}
void CEllipse::CEllipse::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD)Type;
		ar << OrgX << OrgY;//原点坐标
		ar << BorderColor;//边界颜色
		ar << BorderType;
		ar << BorderWidth;//边界宽度
		ar << FillColor;//
		ar << FillType;
		ar << width;
		ar << height;
	}
	else
	{
		WORD w;
		ar >> w;
		Type = (ElementType)w;
		ar >> OrgX >> OrgY;//原点坐标
		ar >> BorderColor;//边界颜色
		ar >> BorderType;
		ar >> BorderWidth;//边界宽度
		ar >> FillColor;//
		ar >> FillType;
		ar >> width;
		ar >> height;
	}
}
void CEllipse::Draw(CDC* pDC)//绘制图形函数
{
	CPen pen, * pOldPen;//画笔 对象和指针
	pen.CreatePen(BorderType, BorderWidth, BorderColor);//初始化画笔的属性
	pOldPen = (CPen*)pDC->SelectObject(&pen);//保存 画笔原来的数据 等会要还原原来的属性
	CBrush brush, * pOldBrush;
	if (FillType >= HS_HORIZONTAL && FillType <= HS_DIAGCROSS)	//HS_HORIZONTAL = 0;HS_DIAGCROSS = 5; 宏定义 最大为5 代表每一个 填充的方式
		brush.CreateHatchBrush(FillType, FillColor);
	else
		brush.CreateSolidBrush(FillColor);
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);

	pDC->Ellipse(OrgX - width / 2, OrgY - height / 2, OrgX + width / 2, OrgY + height / 2);
	pDC->SelectObject(pOldPen);//Old还原。这样做是为了其它Windows程序，因为有的Windows程序直接使用默认的画笔和画刷进行绘图
	pDC->SelectObject(pOldBrush);
}

bool CEllipse::IsMatched(CPoint pnt)//图元匹配函数
{
	if ((pow(pnt.x - OrgX, 2) / pow(width / 2, 2) + pow(pnt.y - OrgY, 2) / pow(height / 2, 2)) < 1)
		return true;
	return false;
}
void CEllipse::SetShapePos(int x, int y, int w, int h = 0, CString s = L"")
{
	OrgX = x;
	OrgY = y;
	width = w;
	height = h;
}
void CEllipse::SetPen(int w = 0, int c = 0, COLORREF cc = RGB(255, 255, 255))
{
	BorderColor = cc;
	BorderType = c;
	BorderWidth = w;
}
void CEllipse::SetBrush(int c = 0, COLORREF cc = RGB(0, 0, 0))
{
	FillColor = cc;
	FillType = c;
}
shape CEllipse::GetShape()
{
	shape t = CShape::GetShape();
	t.Width = width;
	t.Height = height;
	return t;
}
//三角形
CTriangle::CTriangle() :CShape::CShape()
{
	Type = TRIANGLE;
	width = 0;
};
CTriangle::CTriangle(int x, int y, int w) :CShape::CShape()
{
	Type = TRIANGLE;
	OrgX = x;
	OrgY = y;
	width = w;
}
void CTriangle::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD)Type;
		ar << OrgX << OrgY;//原点坐标
		ar << BorderColor;//边界颜色
		ar << BorderType;
		ar << BorderWidth;//边界宽度
		ar << FillColor;//
		ar << FillType;
		ar << width;
	}
	else
	{
		WORD w;
		ar >> w;
		Type = (ElementType)w;
		ar >> OrgX >> OrgY;//原点坐标
		ar >> BorderColor;//边界颜色
		ar >> BorderType;
		ar >> BorderWidth;//边界宽度
		ar >> FillColor;//
		ar >> FillType;
		ar >> width;
	}
}
void CTriangle::Draw(CDC* pDC)//绘制图形函数
{
	CPen pen, * pOldPen;//画笔 对象和指针
	pen.CreatePen(BorderType, BorderWidth, BorderColor);//初始化画笔的属性
	pOldPen = (CPen*)pDC->SelectObject(&pen);//保存 画笔原来的数据 等会要还原原来的属性
	CBrush brush, * pOldBrush;
	if (FillType >= HS_HORIZONTAL && FillType <= HS_DIAGCROSS)	//HS_HORIZONTAL = 0;HS_DIAGCROSS = 5; 宏定义 最大为5 代表每一个 填充的方式
		brush.CreateHatchBrush(FillType, FillColor);
	else
		brush.CreateSolidBrush(FillColor);
	pOldBrush = (CBrush*)pDC->SelectObject(&brush);
	POINT Polygon[3] = { {OrgX + width / 2,int(OrgY + width / sqrt(3) / 2)},{OrgX - width / 2,int(OrgY + width / sqrt(3) / 2)} ,{OrgX ,int(OrgY - width / sqrt(3))} };
	pDC->Polygon(Polygon, 3);
	pDC->SelectObject(pOldPen);//Old还原。这样做是为了其它Windows程序，因为有的Windows程序直接使用默认的画笔和画刷进行绘图
	pDC->SelectObject(pOldBrush);
}

bool CTriangle::IsMatched(CPoint pnt)//图元匹配函数
{
	Vector2 AC(width / 2, (int)(-width / sqrt(3) - width / sqrt(3) / 2)); //CB(), BA();
	Vector2 CB(width / 2, (int)(width / sqrt(3) + width / sqrt(3) / 2));
	Vector2 BA(-width, 0);
	Vector2 AM(pnt.x - OrgX + width / 2, pnt.y - int(OrgY + width / sqrt(3) / 2));
	Vector2 BM(pnt.x - OrgX - width / 2, pnt.y - int(OrgY + width / sqrt(3) / 2));
	Vector2 CM(pnt.x - OrgX, pnt.y - int(OrgY - width / sqrt(3)));
	if (AC.Cross((-BA)) * AC.Cross(AM) > 0)
		if (CB.Cross((-AC)) * CB.Cross(CM) > 0)
			if (BA.Cross((-CB)) * BA.Cross(BM) > 0)
				return true;
	return false;
}
void CTriangle::SetShapePos(int x, int y, int w, int h = 0, CString s = L"")
{
	OrgX = x;
	OrgY = y;
	 width= w;
}
void CTriangle::SetPen(int w = 0, int c = 0, COLORREF cc = RGB(255, 255, 255))
{
	BorderColor = cc;
	BorderType = c;
	BorderWidth = w;
}
void CTriangle::SetBrush(int c = 0, COLORREF cc = RGB(0, 0, 0))
{
	FillColor = cc;
	FillType = c;
}
shape CTriangle::GetShape()
{
	shape t = CShape::GetShape();
	t.Width = width;
	return t;
}
//字体
CText::CText() :CShape::CShape()
{
	Type = TEXT; height = 0; angle = 0; str = "";
};
CText::CText(int x, int y, int h, int a, const char* s) :CShape::CShape()
{
	Type = TEXT;
	OrgX = x;
	OrgY = y;
	height = h;
	angle = a;
	str = s;
}
void CText::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD)Type;
		ar << OrgX << OrgY;//原点坐标
		ar << BorderColor;//边界颜色
		ar << BorderType;
		ar << BorderWidth;//边界宽度
		ar << FillColor;//
		ar << FillType;
		ar << height;
		ar << angle;
		ar << str;
	}
	else
	{
		WORD w;
		ar >> w;
		Type = (ElementType)w;
		ar >> OrgX >> OrgY;//原点坐标
		ar >> BorderColor;//边界颜色
		ar >> BorderType;
		ar >> BorderWidth;//边界宽度
		ar >> FillColor;//
		ar >> FillType;
		ar >> height;
		ar >> angle;
		ar >> str;
	}
}
void CText::Draw(CDC* pDC)//绘制图形函数
{
	CString t = str;
	CFont* pNewFont, * pOldFont;
	pNewFont = new CFont;
	pNewFont->CreateFont(
		height/*高度*/, 25/*宽度*/, angle/*出口矢量和字符的夹角*/, 0/*字符基线和x轴的夹角*/, 400 /*一般这个值设为400*/,
		FALSE/*不带斜体*/, FALSE/*不带下划线*/, FALSE/*不带删除线*/,
		DEFAULT_CHARSET,  //这里我们使用默认字符集，还有其他以 _CHARSET 结尾的常量可用
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,  //这行参数不用管
		DEFAULT_QUALITY,  //默认输出质量
		FF_DONTCARE,  //不指定字体族*/
		L"微软雅黑"  //字体名
	);
	pOldFont = (CFont*)pDC->SelectObject(pNewFont);
	size = pDC->GetTextExtent(str, str.GetLength());
	pDC->SetTextColor(BorderColor);
	pDC->SetBkColor(FillColor);
	pDC->TextOut(OrgX, OrgY, str);
	pDC->SelectObject(pOldFont);
	/*测试
	CPen pen, * pOldPen;//画笔 对象和指针
	pen.CreateStockObject(BLACK_PEN);
	pOldPen = (CPen*)pDC->SelectObject(&pen);//保存 画笔原来的数据 等会要还原原来的属性
	pDC->Ellipse(OrgX - 10, OrgY - 10, OrgX + 10, OrgY + 10);
	pDC->SelectObject(pOldPen);//Old还原。这样做是为了其它Windows程序，因为有的Windows程序直接使用默认的画笔和画刷进行绘图*/

}

bool CText::IsMatched(CPoint pnt)//图元匹配函数
{


	float Angle = angle * PI / 1800;
	if (tan(Angle) == 0)
	{
		if (cos(Angle) == 1)
			if (pnt.x > OrgX && pnt.x < (OrgX + size.cx))
				if (pnt.y > OrgY && pnt.y < (OrgY + size.cy))
					return true;
		if (cos(Angle) == -1)
			if (pnt.x < OrgX && pnt.x >(OrgX - size.cx))
				if (pnt.y < OrgY && pnt.y >(OrgY - size.cy))
					return true;
	}
	else {
		// 求对应点坐标
		float Ax = OrgX;
		float Ay = OrgY;
		float Bx = OrgX + (size.cy / tan(Angle) + size.cx) * cos(Angle) - size.cy / sin(Angle) + size.cy * sin(Angle);
		float By = OrgY - (size.cy / tan(Angle) + size.cx) * sin(Angle) + size.cy * cos(Angle);
		float Cx = OrgX + size.cx * cos(Angle) + size.cy * sin(Angle);
		float Cy = OrgY - size.cx * sin(Angle) + size.cy * cos(Angle);
		float Dx = OrgX + size.cy * sin(Angle);
		float Dy = OrgY + size.cy * cos(Angle);
		//求对应向量
		Vector2 AB(Bx - Ax, By - Ay);
		Vector2 BC(Cx - Bx, Cy - By);
		Vector2 CD(Dx - Cx, Dy - Cy);
		Vector2 AD(Dx - Ax, Dy - Ay);
		Vector2 AM(pnt.x - Ax, pnt.y - Ay);
		Vector2 BM(pnt.x - Bx, pnt.y - By);
		Vector2 CM(pnt.x - Cx, pnt.y - Cy);
		Vector2 DM(pnt.x - Dx, pnt.y - Dy);
		//叉乘法判断
		if (AB.Cross(AM) * AB.Cross(AD) > 0)
			if (BC.Cross(BM) * BC.Cross(-AB) > 0)
				if (CD.Cross(CM) * (CD.Cross(-BC)) > 0)
					if (-AD.Cross(DM) * (-AD.Cross(-CD)) > 0)
						return true;
	}

	return false;
}
void CText::SetShapePos(int x, int y, int w, int h = 0, CString s = L"")
{
	OrgX = x;
	OrgY = y;
	angle = w*10;
	height = h;
	str = s;
}
void CText::SetPen(int w = 0, int c = 0, COLORREF cc = RGB(255, 255, 255))
{
	BorderColor = cc;
	BorderType = c;
	BorderWidth = w;
}
void CText::SetBrush(int c = 0, COLORREF cc = RGB(0, 0, 0))
{
	FillColor = cc;
	FillType = c;
}
shape CText::GetShape()
{
	shape t = CShape::GetShape();
	t.Width = angle/10;
	t.Height = height;
	t.Str = str;
	return t;
}
