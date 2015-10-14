// MidtermProjectDoc.cpp : CMidtermProjectDoc 클래스의 구현
//

#include "stdafx.h"
#include "MidtermProject.h"

#include "MidtermProjectDoc.h"

#include "FileNewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMidtermProjectDoc

IMPLEMENT_DYNCREATE(CMidtermProjectDoc, CDocument)

BEGIN_MESSAGE_MAP(CMidtermProjectDoc, CDocument)
	ON_COMMAND(ID_WINDOW_DUPLICATE, &CMidtermProjectDoc::OnWindowDuplicate)
	ON_COMMAND(ID_EDIT_COPY, &CMidtermProjectDoc::OnEditCopy)
END_MESSAGE_MAP()


// CMidtermProjectDoc 생성/소멸

CMidtermProjectDoc::CMidtermProjectDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMidtermProjectDoc::~CMidtermProjectDoc()
{
}

BOOL CMidtermProjectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	BOOL bSuccess = TRUE;

	if( theApp.m_pNewDib == NULL )
	{
		CFileNewDlg dlg;
		if( dlg.DoModal() == IDOK )
		{
			if( dlg.m_nType == 0 ) // 그레이스케일 이미지
				bSuccess = m_Dib.CreateGrayImage(dlg.m_nWidth, dlg.m_nHeight);
			else // 트루칼라 이미지
				bSuccess = m_Dib.CreateRGBImage(dlg.m_nWidth, dlg.m_nHeight);
		}
		else
		{
			bSuccess = FALSE;
		}
	}
	else
	{
		m_Dib.Copy(theApp.m_pNewDib);
		theApp.m_pNewDib = NULL;
	}

	return bSuccess;
}

// CMidtermProjectDoc serialization

void CMidtermProjectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CMidtermProjectDoc 진단

#ifdef _DEBUG
void CMidtermProjectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMidtermProjectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMidtermProjectDoc 명령


BOOL CMidtermProjectDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	return  m_Dib.Load(lpszPathName);
}

BOOL CMidtermProjectDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return  m_Dib.Save(lpszPathName);
}

void CMidtermProjectDoc::OnEditCopy()
{
	if( m_Dib.IsValid() )
		m_Dib.CopyToClipboard();
}

void CMidtermProjectDoc::OnWindowDuplicate()
{
	AfxNewImage(m_Dib);
}

