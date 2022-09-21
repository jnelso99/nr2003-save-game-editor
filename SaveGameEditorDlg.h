// SaveGameEditorDlg.h : header file
//

#if !defined(AFX_SAVEGAMEEDITORDLG_H__8DEDDE31_AC6C_4753_AC0F_8EFB90309D9E__INCLUDED_)
#define AFX_SAVEGAMEEDITORDLG_H__8DEDDE31_AC6C_4753_AC0F_8EFB90309D9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SaveFile.h"
#include "DragAndDropListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CSaveGameEditorDlg dialog

class CSaveGameEditorDlg : public CDialog
{
// Construction
public:
	CSaveGameEditorDlg(CWnd* pParent = NULL);	// standard constructor
	~CSaveGameEditorDlg();

private:
	CSaveFile *m_SaveGameFile;

	void swap(int* a, int* b);
	void randomize(int arr[], int n);
	void reverse(int arr[], int n);
	void move(int arr[], int n, int src, int dest);


// Dialog Data
	//{{AFX_DATA(CSaveGameEditorDlg)
	enum { IDD = IDD_SAVEGAMEEDITOR_DIALOG };
	CButton	m_BtnMoveUp;
	CButton	m_BtnMoveDn;
	CButton	m_BtnSaveAs;
	CButton	m_BtnSave;
	CButton m_BtnRandomize;
	CButton m_BtnReverseOrder;
	CDragAndDropListBox m_DriverList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveGameEditorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSaveGameEditorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileOpen();
	afx_msg void OnBtnMoveup();
	afx_msg void OnBtnMovedn();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileSave();
	afx_msg void OnRandomize();
	afx_msg void OnReverseOrder();
	afx_msg void OnLbnSelchangeDriverList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVEGAMEEDITORDLG_H__8DEDDE31_AC6C_4753_AC0F_8EFB90309D9E__INCLUDED_)
