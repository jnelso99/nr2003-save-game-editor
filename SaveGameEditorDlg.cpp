// SaveGameEditorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SaveGameEditor.h"
#include "SaveGameEditorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveGameEditorDlg dialog

CSaveGameEditorDlg::CSaveGameEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveGameEditorDlg::IDD, pParent), m_SaveGameFile(0)
{
	//{{AFX_DATA_INIT(CSaveGameEditorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSaveGameEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveGameEditorDlg)
	DDX_Control(pDX, IDC_BTN_MOVEUP, m_BtnMoveUp);
	DDX_Control(pDX, IDC_BTN_MOVEDN, m_BtnMoveDn);
	DDX_Control(pDX, ID_FILE_SAVE_AS, m_BtnSaveAs);
	DDX_Control(pDX, ID_FILE_SAVE, m_BtnSave);
	DDX_Control(pDX, IDC_BTN_RANDOMIZE, m_BtnRandomize);
	DDX_Control(pDX, IDC_BTN_REVERSE, m_BtnReverseOrder);
	DDX_Control(pDX, IDC_LIST_DRIVERS, m_DriverList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSaveGameEditorDlg, CDialog)
	//{{AFX_MSG_MAP(CSaveGameEditorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_FILE_OPEN, OnFileOpen)
	ON_BN_CLICKED(IDC_BTN_MOVEUP, OnBtnMoveup)
	ON_BN_CLICKED(IDC_BTN_MOVEDN, OnBtnMovedn)
	ON_BN_CLICKED(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_BN_CLICKED(ID_FILE_SAVE, OnFileSave)
	ON_BN_CLICKED(IDC_BTN_RANDOMIZE, OnRandomize)
	ON_BN_CLICKED(IDC_BTN_REVERSE, OnReverseOrder)
	ON_LBN_SELCHANGE(IDC_LIST_DRIVERS, OnLbnSelchangeDriverList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveGameEditorDlg message handlers

CSaveGameEditorDlg::~CSaveGameEditorDlg()
{
	if (m_SaveGameFile)
	{
		delete m_SaveGameFile;
	}
}

BOOL CSaveGameEditorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	m_BtnSave.EnableWindow(FALSE);
	m_BtnSaveAs.EnableWindow(FALSE);
	m_BtnMoveDn.EnableWindow(FALSE);
	m_BtnMoveUp.EnableWindow(FALSE);
	m_BtnRandomize.EnableWindow(FALSE);
	m_BtnReverseOrder.EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSaveGameEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSaveGameEditorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSaveGameEditorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSaveGameEditorDlg::OnFileOpen() 
{
	// Open file dialog

	CFileDialog cfd(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, "Save Files (*.svg)|*.svg|All Files (*.*)|*.*||");
	int response = cfd.DoModal();

	if (response == IDOK)
	{
		if (m_SaveGameFile)
		{
			delete m_SaveGameFile;
		}

		m_SaveGameFile = new CSaveFile();

		if (!m_SaveGameFile->read((LPCTSTR)cfd.GetPathName()))
		{
			// TODO:  Get the exception cause and display it in this message box

			AfxMessageBox("The save game file could not be opened");

			m_DriverList.ResetContent();
			m_BtnSave.EnableWindow(FALSE);
			m_BtnSaveAs.EnableWindow(FALSE);
			m_BtnMoveDn.EnableWindow(FALSE);
			m_BtnMoveUp.EnableWindow(FALSE);
			m_BtnRandomize.EnableWindow(FALSE);
			m_BtnReverseOrder.EnableWindow(FALSE);
		}
		else
		{
			m_DriverList.ResetContent();

			for (int i = 0; i < m_SaveGameFile->GetNumDrivers(); i++)
			{
				int index = m_SaveGameFile->m_Order[i];

				CString s;
				s.Format("%d - %s %s (%d)", int(i + 1), m_SaveGameFile->m_Drivers[index]->m_FirstName, m_SaveGameFile->m_Drivers[index]->m_LastName, m_SaveGameFile->m_Drivers[index]->m_CarNumber);

				m_DriverList.AddString((LPCTSTR)s);
			}

			m_BtnSave.EnableWindow(TRUE);
			m_BtnSaveAs.EnableWindow(TRUE);
			m_BtnMoveDn.EnableWindow(TRUE);
			m_BtnMoveUp.EnableWindow(TRUE);
			m_BtnRandomize.EnableWindow(TRUE);
			m_BtnReverseOrder.EnableWindow(TRUE);
		}
	}
}

void CSaveGameEditorDlg::OnFileSave() 
{
	if (!m_SaveGameFile->write(0))
	{
		// TODO:  Get the exception cause and display it in this message box

		AfxMessageBox("The save game file could not be saved");
	}
}

void CSaveGameEditorDlg::OnFileSaveAs() 
{
	// Save file dialog

	CFileDialog cfd(FALSE, NULL, NULL, OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, "Save Files (*.svg)|*.svg|All Files (*.*)|*.*||");
	int response = cfd.DoModal();

	if (response == IDOK)
	{
		BOOL doWrite = FALSE;
		CFileStatus status;

		if (CFile::GetStatus((LPCTSTR)cfd.GetPathName(), status))
		{
			response = AfxMessageBox("File already exists.  Do you wish to overwrite?", MB_YESNO);

			if (response == IDYES)
			{
				doWrite = TRUE;
			}
		}
		else
		{
			doWrite = TRUE;
		}

		if (doWrite && !m_SaveGameFile->write((LPCTSTR)cfd.GetPathName()))
		{
			// TODO:  Get the exception cause and display it in this message box

			AfxMessageBox("The save game file could not be saved");
		}
	}
}

void CSaveGameEditorDlg::OnBtnMoveup() 
{
	int sel = m_DriverList.GetCurSel();
	
	if (sel != LB_ERR && sel > 0)
	{
		int curIndex = m_SaveGameFile->m_Order[sel];
		int prevIndex = m_SaveGameFile->m_Order[sel - 1];

		m_SaveGameFile->m_Order[sel] = prevIndex;
		m_SaveGameFile->m_Order[sel - 1] = curIndex;

		int top = m_DriverList.GetTopIndex();
		m_DriverList.ResetContent();

		for (int i = 0; i < m_SaveGameFile->GetNumDrivers(); i++)
		{
			int index = m_SaveGameFile->m_Order[i];

			CString s;
			s.Format("%d - %s %s (%d)", int(i + 1), m_SaveGameFile->m_Drivers[index]->m_FirstName, m_SaveGameFile->m_Drivers[index]->m_LastName, m_SaveGameFile->m_Drivers[index]->m_CarNumber);

			m_DriverList.AddString((LPCTSTR)s);
		}

		m_DriverList.SetCurSel(sel - 1);

		sel--;

		SCROLLINFO info;
		m_DriverList.GetScrollInfo(SB_VERT, &info);

		int halfPage = info.nPage / 2;
		int limit = m_DriverList.GetScrollLimit(SB_VERT);

		if (sel <= (sel - top))
		{
			m_DriverList.SetTopIndex(0);
		}
		else if (sel >= (limit + halfPage))
		{
			m_DriverList.SetTopIndex(limit);
		}
		else
		{
			m_DriverList.SetTopIndex(top - 1);
		}
	}
}

void CSaveGameEditorDlg::OnBtnMovedn() 
{
	int sel = m_DriverList.GetCurSel();
	
	if (sel != LB_ERR && sel < (m_SaveGameFile->GetNumDrivers() - 1))
	{
		int curIndex = m_SaveGameFile->m_Order[sel];
		int prevIndex = m_SaveGameFile->m_Order[sel + 1];

		m_SaveGameFile->m_Order[sel] = prevIndex;
		m_SaveGameFile->m_Order[sel + 1] = curIndex;

		int top = m_DriverList.GetTopIndex();
		m_DriverList.ResetContent();

		for (int i = 0; i < m_SaveGameFile->GetNumDrivers(); i++)
		{
			int index = m_SaveGameFile->m_Order[i];

			CString s;
			s.Format("%d - %s %s (%d)", int(i + 1), m_SaveGameFile->m_Drivers[index]->m_FirstName, m_SaveGameFile->m_Drivers[index]->m_LastName, m_SaveGameFile->m_Drivers[index]->m_CarNumber);

			m_DriverList.AddString((LPCTSTR)s);
		}

		m_DriverList.SetCurSel(sel + 1);

		sel++;

		SCROLLINFO info;
		m_DriverList.GetScrollInfo(SB_VERT, &info);

		int halfPage = info.nPage / 2;
		int limit = m_DriverList.GetScrollLimit(SB_VERT);

		if (sel <= halfPage)
		{
			m_DriverList.SetTopIndex(0);
		}
		else if (sel >= (limit + (sel - top)))
		{
			m_DriverList.SetTopIndex(limit);
		}
		else
		{
			m_DriverList.SetTopIndex(top + 1);
		}
	}
}

void CSaveGameEditorDlg::OnRandomize()
{
	int sel = m_DriverList.GetCurSel();
	int top = m_DriverList.GetTopIndex();

	int numDrivers = m_SaveGameFile->GetNumDrivers();

	randomize(m_SaveGameFile->m_Order, numDrivers);

	m_DriverList.ResetContent();

	for (int i = 0; i < numDrivers; i++)
	{
		int index = m_SaveGameFile->m_Order[i];

		CString s;
		s.Format("%d - %s %s (%d)", int(i + 1), m_SaveGameFile->m_Drivers[index]->m_FirstName, m_SaveGameFile->m_Drivers[index]->m_LastName, m_SaveGameFile->m_Drivers[index]->m_CarNumber);

		m_DriverList.AddString((LPCTSTR)s);
	}

	if (sel != LB_ERR && sel < (numDrivers - 1))
	{
		m_DriverList.SetCurSel(sel);
	}

	m_DriverList.SetTopIndex(top);
}

void CSaveGameEditorDlg::OnReverseOrder()
{
	int sel = m_DriverList.GetCurSel();
	int top = m_DriverList.GetTopIndex();

	int numDrivers = m_SaveGameFile->GetNumDrivers();

	reverse(m_SaveGameFile->m_Order, numDrivers);

	m_DriverList.ResetContent();

	for (int i = 0; i < numDrivers; i++)
	{
		int index = m_SaveGameFile->m_Order[i];

		CString s;
		s.Format("%d - %s %s (%d)", int(i + 1), m_SaveGameFile->m_Drivers[index]->m_FirstName, m_SaveGameFile->m_Drivers[index]->m_LastName, m_SaveGameFile->m_Drivers[index]->m_CarNumber);

		m_DriverList.AddString((LPCTSTR)s);
	}

	if (sel != LB_ERR && sel < (numDrivers - 1))
	{
		m_DriverList.SetCurSel(sel);
	}

	m_DriverList.SetTopIndex(top);
}

void CSaveGameEditorDlg::swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void CSaveGameEditorDlg::randomize(int arr[], int n)
{
	srand(time(NULL));

	for (int i = n - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		swap(&arr[i], &arr[j]);
	}
}

void CSaveGameEditorDlg::reverse(int arr[], int n)
{
	int start = 0;
	int end = n - 1;

	while (start < end)
	{
		int temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;

		start++;
		end--;
	}
}

void CSaveGameEditorDlg::move(int arr[], int n, int src, int dest)
{
	int start = src;
	int end = dest;

	if (start < end)
	{
		int temp = arr[start];

		for (int i = start; i < end; ++i)
		{
			arr[i] = arr[i + 1];
		}

		arr[end] = temp;
	}
	else if (start > end)
	{
		int temp = arr[start];

		for (int i = start; i > end; i--)
		{
			arr[i] = arr[i - 1];
		}

		arr[end] = temp;
	}
}

void CSaveGameEditorDlg::OnLbnSelchangeDriverList()
{
	int indexTo = m_DriverList.GetCurSel();
	int indexFrom = m_DriverList.GetMovingIndex();

	int sel = m_DriverList.GetCurSel();
	int top = m_DriverList.GetTopIndex();

	int numDrivers = m_SaveGameFile->GetNumDrivers();

	move(m_SaveGameFile->m_Order, numDrivers, indexFrom, indexTo);

	m_DriverList.ResetContent();

	for (int i = 0; i < numDrivers; i++)
	{
		int index = m_SaveGameFile->m_Order[i];

		CString s;
		s.Format("%d - %s %s (%d)", int(i + 1), m_SaveGameFile->m_Drivers[index]->m_FirstName, m_SaveGameFile->m_Drivers[index]->m_LastName, m_SaveGameFile->m_Drivers[index]->m_CarNumber);

		m_DriverList.AddString((LPCTSTR)s);
	}

	if (sel != LB_ERR && sel < (numDrivers - 1))
	{
		m_DriverList.SetCurSel(sel);
	}

	m_DriverList.SetTopIndex(top);
}