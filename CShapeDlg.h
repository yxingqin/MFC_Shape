#pragma once
#include"DrawingDoc.h"

// CShapeDlg 对话框

class CShapeDlg : public CDialog
{
	DECLARE_DYNAMIC(CShapeDlg)

public:
	CShapeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CShapeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CShapeDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	int m_H;
	int m_L;
	int m_W;
	int m_X;
	int m_Y;
	CString m_Text;
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	int m_LineType;
	int m_FillType;
	int m_ShapeType;
	CMFCColorButton m_ColorButton_Fill;
	CMFCColorButton m_ColorButton_Line;
	COLORREF m_FillColor;
	COLORREF m_LineColor;
	afx_msg void OnCbnSelchangeShapeType();
};
