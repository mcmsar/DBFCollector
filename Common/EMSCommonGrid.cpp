///////////////////////////////////////////////////////////////////////////////
//  EMSCommonGrid.cpp
//
//  PATH: C:\Dev\LutServer\common
//
//  CREATED: 1/28/2003 2:59:28 PM by Christiaan Burchell
//
//  PURPOSE:  The Common Grid Control
//
//  COPYRIGHT NOTICE: Copyright (c) 2003 by EMS Technologies, Inc., All rights reserved
//
//  LAST CHANGED: $Date:2/17/03 5:38:05 PM$
//
//  REVISION HISTORY:
//  $Log:
//   4    LUTServer 1.3         2/17/03 5:38:05 PM     Christian Burchell more
//         changes to make the project complie in unicode
//   3    LUTServer 1.2         2/6/03 12:01:20 PM     Christian Burchell added
//         some comments and fixed refresh bug
//   2    LUTServer 1.1         1/28/03 3:04:04 PM     Christian Burchell Fixed
//         Resource Leak
//   1    LUTServer 1.0         12/11/02 1:18:02 PM    Christian Burchell 
//  $
// 
//  1/28/2003 3:00:03 PM: CBurchell: fixed resource leek and added comments

// EMSCommonGridCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "EMSCommonGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEMSCommonGridCtrl


IMPLEMENT_CONTROL(CGXIconControl, CGXStatic);



////////////////////////////////////////////////
//
// NAME: CGXIconControl
//
// CLASS: CGXIconControl
//
// DESCRIPTION: Class Constructor
//
// CREATED:     1/28/2003 3:00:06 PM
//
// PARAMETERS: 
//             CGXGridCore* pGrid
//             UINT nBitmapID
//             int cx
//             int nGrow
//             COLORREF crMask
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
CGXIconControl::CGXIconControl(CGXGridCore* pGrid,UINT nBitmapID, int cx, int nGrow, COLORREF crMask): CGXStatic(pGrid) 
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    m_Images.Create(nBitmapID,  cx,  nGrow,  crMask);
}



////////////////////////////////////////////////
//
// NAME: ~CGXIconControl
//
// CLASS: CGXIconControl
//
// DESCRIPTION: Class Destructor
//
// CREATED:     1/28/2003 3:00:09 PM
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
CGXIconControl::~CGXIconControl()
{

}



////////////////////////////////////////////////
//
// NAME: Draw
//
// CLASS: CGXIconControl
//
// DESCRIPTION: Draws the Icon
//
// CREATED:     1/28/2003 3:00:16 PM
//
// PARAMETERS: 
//             CDC* pDC
//             CRect rect
//             ROWCOL nRow
//             ROWCOL nCol
//             const CGXStyle& style
//             const CGXStyle* pStandardStyle
//
// RETURN: void 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
void CGXIconControl::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{

    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    ASSERT(pDC != NULL && pDC->IsKindOf(RUNTIME_CLASS(CDC)));
    // ASSERTION-> Invalid Device Context ->END
    ASSERT(nRow <= Grid()->GetRowCount() && nCol <= Grid()->GetColCount());
    // ASSERTION-> Cell coordinates out of range ->END
    ASSERT_VALID(pDC);
    DrawBackground(pDC, rect, style);

    if (rect.right <= rect.left || rect.Width() <= 1 || rect.Height() <= 1)
          return; 
        CString str = style.GetIncludeValue() ? style.GetValue() : _T("");
    if(str.Left(4) == _T("#ICO"))
    {

        int n = str.Find(_T(")"));
        CString strIDResource = str.Mid(5,n-5);
        UINT nIDResource = _ttoi(strIDResource);

        HICON hIcon = m_Images.ExtractIcon(nIDResource);
        CRect r = CGXControl::GetCellRect(nRow, nCol, rect, &style);

        int cxIcon = GetSystemMetrics(SM_CXICON)/2;
        int x = (r.Width() - cxIcon + 1) / 2;

        ::DrawIconEx(pDC->GetSafeHdc(),r.left+x, r.top, hIcon,16,16,0,NULL,DI_NORMAL);

        DestroyIcon(hIcon); 

        // child Controls: spin-buttons, hotspot, combobox btn, ...
        CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
    }
} 





////////////////////////////////////////////////
//
// NAME: CEMSCommonGridCtrl
//
// CLASS: CEMSCommonGridCtrl
//
// DESCRIPTION: Class Constructor
//
// CREATED:     1/28/2003 3:00:20 PM
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
CEMSCommonGridCtrl::CEMSCommonGridCtrl()
{
    m_DataCol = 0;
    m_GridName = "Grid";
    m_NumbCol = 1;
    m_bFirstTime = TRUE;

}



////////////////////////////////////////////////
//
// NAME: ~CEMSCommonGridCtrl
//
// CLASS: CEMSCommonGridCtrl
//
// DESCRIPTION: Class Destructor
//
// CREATED:     1/28/2003 3:00:22 PM
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
CEMSCommonGridCtrl::~CEMSCommonGridCtrl()
{
}


BEGIN_MESSAGE_MAP(CEMSCommonGridCtrl, CGXGridView)
	//{{AFX_MSG_MAP(CEMSCommonGridCtrl)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CEMSCommonGridCtrl message handlers


////////////////////////////////////////////////
//
// NAME: OnInitialUpdate
//
// CLASS: CEMSCommonGridCtrl
//
// DESCRIPTION: Initializes the window
//
// CREATED:     1/28/2003 3:00:24 PM
//
// RETURN: void 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
void CEMSCommonGridCtrl::OnInitialUpdate() 
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    CGXGridView::OnInitialUpdate();
    SetColCount(m_NumbCol);
    SetRowCount(0);
    HideCols(0,0);
    HideCols(m_DataCol,m_DataCol);

    EnableMouseWheel();

    SetScrollBarMode(SB_BOTH,gxnAutomatic);
    
    GetParam()->SetSortRowsOnDblClk(TRUE);  //sorting by COLUMNS
    GetParam()->SetActivateCellFlags(FALSE);
    GetParam()->EnableMoveCols(FALSE);
    GetParam()->EnableSelection(GX_SELROW|GX_SELCELL);
    GetParam()->SetSpecialMode(GX_MODELBOX_SS);
    GetParam()->SetHideCurrentCell(GX_HIDE_ALLWAYS);

    m_bFirstTime = FALSE;

    //TODO: Add Coloum Init
}



////////////////////////////////////////////////
//
// NAME: OnMouseMove
//
// CLASS: CEMSCommonGridCtrl
//
// DESCRIPTION: Mouse Has Moved
//
// CREATED:     1/28/2003 3:00:34 PM
//
// PARAMETERS: 
//             UINT nFlags
//             CPoint point
//
// RETURN: void 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
void CEMSCommonGridCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())	
	CGXGridView::OnMouseMove(nFlags, point);
}



////////////////////////////////////////////////
//
// NAME: Refresh
//
// CLASS: CEMSCommonGridCtrl
//
// DESCRIPTION: Refreshes the Grid
//
// CREATED:     1/28/2003 3:00:43 PM
//
// RETURN: void 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
void CEMSCommonGridCtrl::Refresh() 
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
    BOOL bOldLock = LockUpdate(TRUE);
    ROWCOL nRow, nCol;
    GetCurrentCell(nRow, nCol);
    if(GetRowCount() != 0)
        SetRowCount(0);

    DoRefresh();
    
    // fill up array with sort order
	CGXSortInfoArray sortInfo;
	sortInfo.SetSize(1); // only 1 column (you can also sort by several columns)
	sortInfo[0].nRC = GetParam()->m_nLastSortedCol;
	sortInfo[0].sortType = CGXSortInfo::autodetect;

	if (GetParam()->m_bSortAscending)
		sortInfo[0].sortOrder = CGXSortInfo::ascending;
	else
		sortInfo[0].sortOrder = CGXSortInfo::descending;

    

    if(m_bFirstTime && GetRowCount() > 0)
	    SortRows(CGXRange().SetTable(), sortInfo);

    if(nRow > 0)
    {
            SetSelection(NULL);
            SelectRange(CGXRange().SetRows(nRow), TRUE);
    }
    
    Invalidate();
    LockUpdate(bOldLock);
}



////////////////////////////////////////////////
//
// NAME: OnLButtonDblClk
//
// CLASS: CEMSCommonGridCtrl
//
// DESCRIPTION: Left button Double Click
//
// CREATED:     1/28/2003 3:01:03 PM
//
// PARAMETERS: 
//             UINT nFlags
//             CPoint point
//
// RETURN: void 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
void CEMSCommonGridCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CGXGridView::OnLButtonDblClk(nFlags, point);
}



////////////////////////////////////////////////
//
// NAME: OnLButtonDblClkRowCol
//
// CLASS: CEMSCommonGridCtrl
//
// DESCRIPTION: Left Button Double click on a Row and Col
//
// CREATED:     1/28/2003 3:01:40 PM
//
// PARAMETERS: 
//             ROWCOL nRow
//             ROWCOL nCol
//             UINT nFlags
//             CPoint pt
//
// RETURN: BOOL 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
BOOL CEMSCommonGridCtrl::OnLButtonDblClkRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    CGXGridView::OnLButtonDblClkRowCol( nRow,  nCol,  nFlags,  pt);
    if(nRow >0)
    {
        DblClkItem();
    }
    else
    {
        SetStyleRange(CGXRange(0,0,0,GetColCount()),
                CGXStyle().SetTextColor(RGB(0,0,0))
            );

         SetStyleRange(CGXRange(0,nCol),
                CGXStyle().SetTextColor(RGB(255,0,0))
            );

    }
    return TRUE;
}



////////////////////////////////////////////////
//
// NAME: ExportCSV
//
// CLASS: CEMSCommonGridCtrl
//
// DESCRIPTION: Exports the grid to CSV
//
// CREATED:     1/28/2003 3:01:56 PM
//
// RETURN: void 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
void CEMSCommonGridCtrl::ExportCSV() 
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CFileDialog dlgFile(
      FALSE,
      _T(".csv"),
      NULL,
      OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
      _T("CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||"));

   if (dlgFile.DoModal( ) == IDCANCEL)
      return;

   CFile textFile;

   if (!textFile.Open(dlgFile.GetFileName( ),
      CFile::modeCreate | CFile::modeWrite))
   {
      TCHAR sz[255];
      wsprintf(sz, _T("File %s could not be opened!"), dlgFile.GetFileName( ));
      AfxMessageBox(sz);
      return;
   }

   m_sExportTabDelim = ',';
   CopyTextToFile( textFile, CGXRange(0, 2, GetRowCount( ), GetColCount( )-1) );
   

   textFile.Close( );
	
}



////////////////////////////////////////////////
//
// NAME: OnCreate
//
// CLASS: CEMSCommonGridCtrl
//
// DESCRIPTION: Creates the window
//
// CREATED:     1/28/2003 3:01:59 PM
//
// PARAMETERS: 
//             LPCREATESTRUCT lpCreateStruct
//
// RETURN: int 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
int CEMSCommonGridCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (CGXGridView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	OnInitialUpdate();
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// Printing Dialog

_AFX_WIN_STATE g_afxWinState;

class CMyPrintingDialog : public CDialog
{
public:
	//{{AFX_DATA(CMyPrintingDialog)
	enum { IDD = AFX_IDD_PRINTDLG };
	//}}AFX_DATA
	CMyPrintingDialog::CMyPrintingDialog(CWnd* pParent)
		{
			Create(CMyPrintingDialog::IDD, pParent);      // modeless !
			g_afxWinState.m_bUserAbort = FALSE;
		}
	virtual ~CMyPrintingDialog() { }

	virtual BOOL OnInitDialog();
	virtual void OnCancel();
};

BOOL CALLBACK MyAfxAbortProc(HDC, int)
{
	_AFX_WIN_STATE* pWinState = &g_afxWinState;
	MSG msg;
	while (!pWinState->m_bUserAbort &&
		::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
	{
		if (!AfxGetThread()->PumpMessage())
			return FALSE;   // terminate if WM_QUIT received
	}
	return !pWinState->m_bUserAbort;
}

BOOL CMyPrintingDialog::OnInitDialog()
{
	SetWindowText(AfxGetAppName());
	CenterWindow();
	return CDialog::OnInitDialog();
}

void CMyPrintingDialog::OnCancel()
{
	g_afxWinState.m_bUserAbort = TRUE;  // flag that user aborted print
	CDialog::OnCancel();
}

UINT AFXAPI AfxGetFileTitle(LPCTSTR lpszPathName, LPTSTR lpszTitle, UINT nMax);

void CEMSCommonGridCtrl::Print() 
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState())
	// get default print info
	CPrintInfo printInfo;
	ASSERT(printInfo.m_pPD != NULL);    // must be set

	if (OnPreparePrinting(&printInfo))
	{
		// hDC must be set (did you remember to call DoPreparePrinting?)
		ASSERT(printInfo.m_pPD->m_pd.hDC != NULL);

		// gather file to print to if print-to-file selected
		CString strOutput;
		if (printInfo.m_pPD->m_pd.Flags & PD_PRINTTOFILE && !printInfo.m_bDocObject)
		{
			// construct CFileDialog for browsing
			CString strDef(MAKEINTRESOURCE(AFX_IDS_PRINTDEFAULTEXT));
			CString strPrintDef(MAKEINTRESOURCE(AFX_IDS_PRINTDEFAULT));
			CString strFilter(MAKEINTRESOURCE(AFX_IDS_PRINTFILTER));
			CString strCaption(MAKEINTRESOURCE(AFX_IDS_PRINTCAPTION));
			CFileDialog dlg(FALSE, strDef, strPrintDef,
				OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter);
			dlg.m_ofn.lpstrTitle = strCaption;

			if (dlg.DoModal() != IDOK)
				return;

			// set output device to resulting path name
			strOutput = dlg.GetPathName();
		}

		// set up document info and start the document printing process
		CString strTitle = m_GridName;
		DOCINFO docInfo;
		memset(&docInfo, 0, sizeof(DOCINFO));
		docInfo.cbSize = sizeof(DOCINFO);
		docInfo.lpszDocName = strTitle;
		CString strPortName;
		int nFormatID;
		if (strOutput.IsEmpty())
		{
			docInfo.lpszOutput = NULL;
			strPortName = printInfo.m_pPD->GetPortName();
			nFormatID = AFX_IDS_PRINTONPORT;
		}
		else
		{
			docInfo.lpszOutput = strOutput;
			AfxGetFileTitle(strOutput,
				strPortName.GetBuffer(_MAX_PATH), _MAX_PATH);
			nFormatID = AFX_IDS_PRINTTOFILE;
		}

		// setup the printing DC
		CDC dcPrint;
		if (!printInfo.m_bDocObject)
		{
			dcPrint.Attach(printInfo.m_pPD->m_pd.hDC);  // attach printer dc
			dcPrint.m_bPrinting = TRUE;
		}
		OnBeginPrinting(&dcPrint, &printInfo);

		if (!printInfo.m_bDocObject)
			dcPrint.SetAbortProc(MyAfxAbortProc);

		// disable main window while printing & init printing status dialog
		EnableWindow(FALSE);
		CMyPrintingDialog dlgPrintStatus(this);

		CString strTemp;
		dlgPrintStatus.SetDlgItemText(AFX_IDC_PRINT_DOCNAME, strTitle);
		dlgPrintStatus.SetDlgItemText(AFX_IDC_PRINT_PRINTERNAME,
			printInfo.m_pPD->GetDeviceName());
		AfxFormatString1(strTemp, nFormatID, strPortName);
		dlgPrintStatus.SetDlgItemText(AFX_IDC_PRINT_PORTNAME, strTemp);
		dlgPrintStatus.ShowWindow(SW_SHOW);
		dlgPrintStatus.UpdateWindow();

		// start document printing process
		if (!printInfo.m_bDocObject && dcPrint.StartDoc(&docInfo) == SP_ERROR)
		{
			// enable main window before proceeding
			EnableWindow(TRUE);

			// cleanup and show error message
			OnEndPrinting(&dcPrint, &printInfo);
			dlgPrintStatus.DestroyWindow();
			dcPrint.Detach();   // will be cleaned up by CPrintInfo destructor
			AfxMessageBox(AFX_IDP_FAILED_TO_START_PRINT);
			return;
		}

		// Guarantee values are in the valid range
		UINT nEndPage = printInfo.GetToPage();
		UINT nStartPage = printInfo.GetFromPage();

		if (nEndPage < printInfo.GetMinPage())
			nEndPage = printInfo.GetMinPage();
		if (nEndPage > printInfo.GetMaxPage())
			nEndPage = printInfo.GetMaxPage();

		if (nStartPage < printInfo.GetMinPage())
			nStartPage = printInfo.GetMinPage();
		if (nStartPage > printInfo.GetMaxPage())
			nStartPage = printInfo.GetMaxPage();

		int nStep = (nEndPage >= nStartPage) ? 1 : -1;
		nEndPage = (nEndPage == 0xffff) ? 0xffff : nEndPage + nStep;

		VERIFY(strTemp.LoadString(AFX_IDS_PRINTPAGENUM));

		// If it's a doc object, we don't loop page-by-page
		// because doc objects don't support that kind of levity.

		BOOL bError = FALSE;
		if (printInfo.m_bDocObject)
		{
			OnPrepareDC(&dcPrint, &printInfo);
			OnPrint(&dcPrint, &printInfo);
		}
		else
		{
			// begin page printing loop
			for (printInfo.m_nCurPage = nStartPage;
				printInfo.m_nCurPage != nEndPage; printInfo.m_nCurPage += nStep)
			{
				OnPrepareDC(&dcPrint, &printInfo);

				// check for end of print
				if (!printInfo.m_bContinuePrinting)
					break;

				// write current page
				TCHAR szBuf[80];
				wsprintf(szBuf, strTemp, printInfo.m_nCurPage);
				dlgPrintStatus.SetDlgItemText(AFX_IDC_PRINT_PAGENUM, szBuf);

				// set up drawing rect to entire page (in logical coordinates)
				printInfo.m_rectDraw.SetRect(0, 0,
					dcPrint.GetDeviceCaps(HORZRES),
					dcPrint.GetDeviceCaps(VERTRES));
				dcPrint.DPtoLP(&printInfo.m_rectDraw);

				// attempt to start the current page
				if (dcPrint.StartPage() < 0)
				{
					bError = TRUE;
					break;
				}

				// must call OnPrepareDC on newer versions of Windows because
				// StartPage now resets the device attributes.
				//if (afxData.bMarked4) // we know this will not be on an 95 computer
				OnPrepareDC(&dcPrint, &printInfo);

				ASSERT(printInfo.m_bContinuePrinting);

				// page successfully started, so now render the page
				OnPrint(&dcPrint, &printInfo);
				if (dcPrint.EndPage() < 0 || !MyAfxAbortProc(dcPrint.m_hDC, 0))
				{
					bError = TRUE;
					break;
				}
			}
		}

		// cleanup document printing process
		if (!printInfo.m_bDocObject)
		{
			if (!bError)
				dcPrint.EndDoc();
			else
				dcPrint.AbortDoc();
		}

		EnableWindow(TRUE);    // enable main window

		OnEndPrinting(&dcPrint, &printInfo);    // clean up after printing
		dlgPrintStatus.DestroyWindow();

		dcPrint.Detach();   // will be cleaned up by CPrintInfo destructor
	}
}




////////////////////////////////////////////////
//
// NAME: GetRowData
//
// CLASS: CEMSCommonGridCtrl
//
// DESCRIPTION: Gets the Data From a row
//
// CREATED:     2/6/2003 11:59:46 AM
//
// PARAMETERS: 
//             ROWCOL nRow
//
// RETURN: int 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
int CEMSCommonGridCtrl::GetRowData(ROWCOL nRow)
{
    if(nRow > 0)
        return _ttoi(GetValueRowCol(nRow,m_DataCol));
    else
        return -1;
}



////////////////////////////////////////////////
//
// NAME: SetRowData
//
// CLASS: CEMSCommonGridCtrl
//
// DESCRIPTION: Sets the Rows data
//
// CREATED:     2/6/2003 11:59:57 AM
//
// PARAMETERS: 
//             ROWCOL nRow
//             int data
//
// RETURN: void 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
void CEMSCommonGridCtrl::SetRowData(ROWCOL nRow, int data)
{
    SetStyleRange(CGXRange(nRow,m_DataCol),
        CGXStyle()
          .SetValue((UINT)data)
        );
}



////////////////////////////////////////////////
//
// NAME: SetRowColour
//
// CLASS: CEMSCommonGridCtrl
//
// DESCRIPTION: Sets teh Rows colour
//
// CREATED:     2/6/2003 12:00:06 PM
//
// PARAMETERS: 
//             ROWCOL nRow
//             COLORREF c
//
// RETURN: void 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
void CEMSCommonGridCtrl::SetRowColour(ROWCOL nRow, COLORREF c)
{
    SetStyleRange(CGXRange(nRow,0,nRow,GetColCount()),
                CGXStyle().SetInterior(c)
                .SetReadOnly(TRUE)
            );
}
