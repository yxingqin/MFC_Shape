
// DrawingView.cpp: CDrawingView 类的实现
//

#include "pch.h"
#include "framework.h"
#include"CShape.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Drawing.h"
#endif

#include "DrawingDoc.h"
#include "DrawingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawingView

IMPLEMENT_DYNCREATE(CDrawingView, CView)

BEGIN_MESSAGE_MAP(CDrawingView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_LBUTTONDBLCLK()
ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONDBLCLK()
ON_WM_RBUTTONDBLCLK()
END_MESSAGE_MAP()

// CDrawingView 构造/析构

CDrawingView::CDrawingView() noexcept
{
	// TODO: 在此处添加构造代码
	//shapeDlg.DoModal();
}

CDrawingView::~CDrawingView()
{
}

BOOL CDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDrawingView 绘图

void CDrawingView::OnDraw(CDC* pDC)
{
	CDrawingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO:  在此处为本机数据添加绘制代码
	for (int i = 0; i < pDoc->m_Elements.GetCount(); i++)
	{
		CShape* p = (CShape*)pDoc->m_Elements[i];
		p->Draw(pDC);
	}
	
}



// CDrawingView 打印

BOOL CDrawingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDrawingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDrawingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDrawingView 诊断

#ifdef _DEBUG
void CDrawingView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawingDoc* CDrawingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawingDoc)));
	return (CDrawingDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawingView 消息处理程序
void CDrawingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDrawingDoc* pDoc = GetDocument();//获取文档指针
	ASSERT_VALID(pDoc);
	if (!pDoc)	return;
	CClientDC dc(this);
	CPoint pntLogical = point;
	OnPrepareDC(&dc);
	dc.DPtoLP(&pntLogical);//转坐标
	if ((nFlags & MK_CONTROL) == MK_CONTROL)//Ctrl键按下,按位与运算，如果 nFlags== MK_CONTROL 的话 那么就 (nFlags & MK_CONTROL) == MK_CONTROL
	{
		shapeDlg.m_X = pntLogical.x;
		shapeDlg.m_Y = pntLogical.y;
		shapeDlg.m_ShapeType = 0;
		if (shapeDlg.DoModal() == IDOK)
		{ 
			CShape* p = nullptr;
			
			switch (shapeDlg.m_ShapeType)
			{
			case 0:
				break;
			case 1:
				p = new CSquare;
				break;
			case 2:
				p = new CRectangle;
				break;
			case 3:
				p = new CCircle;
				break;
			case 4:
				p = new CEllipse;
				break;
			case 5:
				p = new CTriangle;
				break;
			case 6:
				p = new CText;
				break;
			default:
				
				break;
			}
			if (p)
			{
				p->SetShapePos(shapeDlg.m_X, shapeDlg.m_Y, shapeDlg.m_W, shapeDlg.m_H, shapeDlg.m_Text);
				p->SetPen(shapeDlg.m_L, shapeDlg.m_LineType, shapeDlg.m_ColorButton_Line.GetColor());
				p->SetBrush(shapeDlg.m_FillType,shapeDlg.m_ColorButton_Fill.GetColor());

				pDoc->m_Elements.Add(p);
				pDoc->SetModifiedFlag();
				pDoc->UpdateAllViews(NULL);
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CDrawingView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDrawingDoc* pDoc = GetDocument();//获取窗口指针
	ASSERT_VALID(pDoc);
	if (!pDoc)	return;
	CClientDC dc(this);
	CPoint pntLogical = point;
	OnPrepareDC(&dc);
	dc.DPtoLP(&pntLogical);
	for (int i = 0; i < pDoc->m_Elements.GetSize(); i++)
	{
		CShape* p = (CShape*)pDoc->m_Elements[i];
		if (p->IsMatched(pntLogical))
		{
			shape t = p->GetShape();
			shapeDlg.m_ShapeType = t.Type;
			shapeDlg.m_X = t.OrgX;
			shapeDlg.m_Y=t.OrgY;
			shapeDlg.m_W = t.Width;
			shapeDlg.m_H = t.Height;
			shapeDlg.m_L = t.BorderWidth;
			shapeDlg.m_LineType = t.BorderType;
			shapeDlg.m_LineColor = t.BorderColor;
			shapeDlg.m_FillType = t.FillType;
			shapeDlg.m_FillColor = t.FillColor;
			shapeDlg.m_Text = t.Str;
			if (shapeDlg.DoModal() == IDOK)
			{
				p->SetShapePos(shapeDlg.m_X, shapeDlg.m_Y, shapeDlg.m_W, shapeDlg.m_H, shapeDlg.m_Text);
				p->SetPen(shapeDlg.m_L, shapeDlg.m_LineType, shapeDlg.m_ColorButton_Line.GetColor());
				p->SetBrush(shapeDlg.m_FillType, shapeDlg.m_ColorButton_Fill.GetColor());
				pDoc->SetModifiedFlag();
				pDoc->UpdateAllViews(NULL);
			}
		}	
	}
	CView::OnLButtonDblClk(nFlags, point);
}


void CDrawingView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDrawingDoc* pDoc = GetDocument();//获取窗口指针
	ASSERT_VALID(pDoc);
	if (!pDoc)	return;
	CClientDC dc(this);
	CPoint pntLogical = point;
	OnPrepareDC(&dc);
	dc.DPtoLP(&pntLogical);
	for (int i = 0; i < pDoc->m_Elements.GetSize(); i++)
	{
		CShape* p = (CShape*)pDoc->m_Elements[i];
		if (p->IsMatched(pntLogical))
		{
			pDoc->m_Elements.RemoveAt(i);
			pDoc->SetModifiedFlag();
			pDoc->UpdateAllViews(NULL);
		}
	}
	CView::OnRButtonDblClk(nFlags, point);
}
