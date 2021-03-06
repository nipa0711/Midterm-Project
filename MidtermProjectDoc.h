// MidtermProjectDoc.h : CMidtermProjectDoc 클래스의 인터페이스
//


#pragma once

#include "dib.h"

class CMidtermProjectDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMidtermProjectDoc();
	DECLARE_DYNCREATE(CMidtermProjectDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 구현입니다.
public:
	virtual ~CMidtermProjectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

public:
	// 이미지 객체
	CDib m_Dib;

	// 파일 불러오기 & 저장하기
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);

public:
	afx_msg void OnWindowDuplicate();
	afx_msg void OnEditCopy();
};
