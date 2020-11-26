// CShapeDlg.cpp: 实现文件
//

#include "pch.h"
#include "Drawing.h"
#include "CShapeDlg.h"
#include "afxdialogex.h"
//表数据
CString ps[7] = { L"实线",L"虚线",L"点笔线",L"虚线和点线交替2",L"虚线和点交替2",L"空画笔",L"直线画笔" };
CString hs[7] = { L"水平阴影",L"垂直阴影",L"45度向下斜线阴影",L"45度向上斜线阴影",L"水平垂直交叉阴影",L"斜线交叉阴影",L"实心"};
CString ctype[7] = { L"请选择",L"正方形",L"长方形",L"圆形",L"椭圆形",L"三角形",L"文字" };

// CShapeDlg 对话框

IMPLEMENT_DYNAMIC(CShapeDlg, CDialog)

CShapeDlg::CShapeDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CShapeDlg, pParent)
	, m_H(100)
	, m_L(0)
	, m_W(100)
	, m_X(0)
	, m_Y(0)
	, m_Text(_T(""))
{
	m_LineType = 0;
	m_FillType = 6;
	m_ShapeType = 0;
	m_LineColor = RGB(0, 0, 0);
	m_FillColor = RGB(255,255,255);
}

CShapeDlg::~CShapeDlg()
{
}

void CShapeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_H, m_H);
	DDX_Text(pDX, IDC_EDIT_Line, m_L);
	DDX_Text(pDX, IDC_EDIT_W, m_W);
	DDX_Text(pDX, IDC_EDIT_X, m_X);
	DDX_Text(pDX, IDC_EDIT_Y, m_Y);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_Text);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_Fill, m_ColorButton_Fill);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON_Line, m_ColorButton_Line);
	DDX_Text(pDX, IDC_MFCCOLORBUTTON_Fill, m_FillColor);

	DDX_Text(pDX, IDC_MFCCOLORBUTTON_Line, m_LineColor);
}


BEGIN_MESSAGE_MAP(CShapeDlg, CDialog)
	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDC_BUTTON_OK, &CShapeDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_Cancel, &CShapeDlg::OnBnClickedButtonCancel)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_COMBO_Class, &CShapeDlg::OnCbnSelchangeShapeType)
END_MESSAGE_MAP()


// CShapeDlg 消息处理程序





BOOL CShapeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化 每个空间的数据
	CEdit* pCEditText = (CEdit*)GetDlgItem(IDC_EDIT_TEXT);//文字框
	CEdit* pCEditH = (CEdit*)GetDlgItem(IDC_EDIT_H);//文字框
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_Class);//组合框
	CListBox* pListBoxLine = (CListBox*)GetDlgItem(IDC_LIST_Line);//线的列表
	CListBox* pListBoxFill = (CListBox*)GetDlgItem(IDC_LIST_Fill);//填充列表
	CEdit* pCEditLw = (CEdit*)GetDlgItem(IDC_EDIT_Line);//线宽度
	pCEditText->EnableWindow(true);
	pComboBox->EnableWindow(true);
	pListBoxLine->EnableWindow(true);
	pListBoxFill->EnableWindow(true);
	pCEditH->EnableWindow(true);
	//填入某些数据
	for (int i = 0; i < 7; i++)
	{
		pComboBox->AddString(ctype[i]);
		pListBoxLine->AddString(ps[i]);
		pListBoxFill->AddString(hs[i]);
	}
	pComboBox->SetCurSel(m_ShapeType);
	pListBoxLine->SetCurSel(m_LineType);
	pListBoxFill->SetCurSel(m_FillType);
	//颜色选择控制器的初始化
	m_ColorButton_Line.EnableOtherButton(_T("其余颜色"));
	m_ColorButton_Line.SetColor(m_LineColor);
	m_ColorButton_Fill.EnableOtherButton(_T("其余颜色"));
	m_ColorButton_Fill.SetColor(m_FillColor);
	//如果 是修改数据 锁定某些控件
	if (m_ShapeType)
	{
		pComboBox->EnableWindow(false);
		if(!(m_ShapeType==6))
			pCEditText->EnableWindow(false);
		else
		{
			pCEditText->EnableWindow(true);
			pListBoxLine->EnableWindow(false);
			pListBoxFill->EnableWindow(false);
			pCEditLw->EnableWindow(false);
		}
		if(m_ShapeType==1||m_ShapeType == 3||m_ShapeType==5)
			pCEditH->EnableWindow(false);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CShapeDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码
	if (nState == WA_ACTIVE) //窗口被激活
		UpdateData(FALSE);
	else
	{
		UpdateData(TRUE);
	}
}


void CShapeDlg::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
	/*赋值，为和View数据交换做准备*/
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_Class);//组合框
	CListBox* pListBoxLine = (CListBox*)GetDlgItem(IDC_LIST_Line);//线的列表
	CListBox* pListBoxFill = (CListBox*)GetDlgItem(IDC_LIST_Fill);//填充列表
	m_ShapeType = pComboBox->GetCurSel();
	m_LineType = pListBoxLine->GetCurSel();
	m_FillType = pListBoxFill->GetCurSel();
	COLORREF t = m_ColorButton_Fill.GetColor();
	/*没有选择图形就不退出*/
	if (m_ShapeType == 0)
		MessageBox(L"请选择图形类别");
	else
		OnOK();
}


void CShapeDlg::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}


void CShapeDlg::OnCbnSelchangeShapeType()
{
	// TODO: 在此添加控件通知处理程序代码
	CComboBox* pComboBox = (CComboBox*)GetDlgItem(IDC_COMBO_Class);//组合框
	CEdit* pCEditText = (CEdit*)GetDlgItem(IDC_EDIT_TEXT);//文字框
	CEdit* pCEditH = (CEdit*)GetDlgItem(IDC_EDIT_H);//高度框
	CEdit* pCEditLw = (CEdit*)GetDlgItem(IDC_EDIT_Line);//线宽度
	CListBox* pListBoxLine = (CListBox*)GetDlgItem(IDC_LIST_Line);//线的列表
	CListBox* pListBoxFill = (CListBox*)GetDlgItem(IDC_LIST_Fill);//填充列表
	//如果不是文字和未选择
	if (!(pComboBox->GetCurSel()==6)|| pComboBox->GetCurSel() == 0)
	{
		pCEditText->EnableWindow(false);
		pListBoxLine->EnableWindow(true);
		pListBoxFill->EnableWindow(true);
		pCEditLw->EnableWindow(true);
	}
	else
	{
		pCEditText->EnableWindow(true);
		pListBoxLine->EnableWindow(false);
		pListBoxFill->EnableWindow(false);
		pCEditLw->EnableWindow(false);
	}
		
	if(pComboBox->GetCurSel() == 1 || pComboBox->GetCurSel() == 3 || pComboBox->GetCurSel() == 5)
	{ 
		pCEditH->EnableWindow(false);
	}else
		pCEditH->EnableWindow(true);


	
	
}
