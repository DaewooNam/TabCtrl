
// TabCtrlDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "TabCtrl.h"
#include "TabCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTabCtrlDlg 대화 상자



CTabCtrlDlg::CTabCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TABCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTabCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTabCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CTabCtrlDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CTabCtrlDlg 메시지 처리기

BOOL CTabCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.


	CTabCtrl* pCtrl = (CTabCtrl*)GetDlgItem(IDC_TAB1);

	pCtrl->InsertItem(0, "Test1"); //현재 어떤 tab이 클릭 된지만 확인 할 수 있다. 
	pCtrl->InsertItem(1, "Test2");
	pCtrl->InsertItem(2, "Test3"); 

	// 모든 값들 초기화
	for (int i = 0; i < 3; i++)
	{
		m_pStatics[i] = GetDlgItem(IDC_STATIC_FIRST+i);
		m_pStatics[i]->ShowWindow(SW_HIDE);

	}

	
	m_pCurrStatic = m_pStatics[0];//현재 스태틱
	m_pCurrStatic->SetWindowPos(NULL,100,100,0,0,SWP_SHOWWINDOW|SWP_NOSIZE);






	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTabCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTabCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTabCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTabCtrlDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	CTabCtrl* pTab = (CTabCtrl*)GetDlgItem(IDC_TAB1);
	int idx = pTab->GetCurSel();

	//예외 처리
	if (m_pCurrStatic == m_pStatics[idx])
		return ;

	m_pCurrStatic->ShowWindow(SW_HIDE); //\현재 스타틱 숨기기
	m_pCurrStatic = m_pStatics[idx]; //변경된 스타틱 주소 갱신
	m_pCurrStatic->SetWindowPos(NULL,100,100,0,0,SWP_SHOWWINDOW|SWP_NOSIZE);




	/*

	CWnd* one  = GetDlgItem(IDC_STATIC_FIRST);
	CWnd* two  = GetDlgItem(IDC_STATIC_SECOND);
	CWnd* three = GetDlgItem(IDC_STATIC_THIRD);

	one->ShowWindow(SW_HIDE);
	two->ShowWindow(SW_HIDE);
	three->ShowWindow(SW_HIDE);


	if (idx == 0)
		one->ShowWindow(SW_SHOW);
	if (idx == 1)
		two->ShowWindow(SW_SHOW);
	if (idx ==2)
		three->ShowWindow(SW_SHOW);
	*/



	TRACE("OnTcnSelchangeTab1 : %d %d %d \n",idx,pNMHDR->code, pNMHDR->idFrom);

	*pResult = 0;
}
