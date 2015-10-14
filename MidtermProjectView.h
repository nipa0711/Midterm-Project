// MidtermProjectView.h : CMidtermProjectView 클래스의 인터페이스
//


#pragma once


class CMidtermProjectView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CMidtermProjectView();
	DECLARE_DYNCREATE(CMidtermProjectView)

// 특성입니다.
public:
	CMidtermProjectDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMidtermProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	// 이미지 확대 배율
	int m_nZoom;

protected:
	void SetScrollSizeToFit(void);
	void ShowImageInfo(CPoint point);

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnViewZoom1();
	afx_msg void OnViewZoom2();
	afx_msg void OnViewZoom3();
	afx_msg void OnViewZoom4();

	afx_msg void OnUpdateViewZoom1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewZoom2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewZoom3(CCmdUI *pCmdUI);
	afx_msg void OnUpdateViewZoom4(CCmdUI *pCmdUI);
    afx_msg void OnDibinverse();
    afx_msg void OnDibcontrast();
    afx_msg void OnGammacorrection();
    afx_msg void OnHistogram();
    afx_msg void OnHistoEqualize();
	afx_msg void OnKMean();
	afx_msg void K_Mean_Clustering(BYTE** image, int* ME, int K, int T, int w, int h); // , float* saveMean
	afx_msg void K_Mean_Clustering(BYTE** image, int* ME, int K, int T, int w, int h, float* saveMean); // 
	afx_msg void OnLBG();
	afx_msg void LBG_Clustering(BYTE** image, int* ME, int K, int T, int w, int h, float* saveMean);
	afx_msg int CalcMidHist(BYTE** image, int w, int h);
};

#ifndef _DEBUG  // MidtermProjectView.cpp의 디버그 버전
inline CMidtermProjectDoc* CMidtermProjectView::GetDocument() const
   { return reinterpret_cast<CMidtermProjectDoc*>(m_pDocument); }
#endif

