// HistogramDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MidtermProject.h"
#include "HistogramDlg.h"


// CHistogramDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CHistogramDlg, CDialog)

CHistogramDlg::CHistogramDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHistogramDlg::IDD, pParent)
    
{
    memset(m_Histogram, 0, sizeof(int)*256);
}

CHistogramDlg::~CHistogramDlg()
{
}

void CHistogramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistogramDlg, CDialog)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CHistogramDlg 메시지 처리기입니다.

void CHistogramDlg::SetImage(float histo[256])
{
  // m_Histogram 배열의 최대값을 구한다.
	register int i;
	float max_value = histo[0];
	for( i = 1 ; i < 256 ; i++ ) 
	{
		if( histo[i] > max_value ) 
		max_value = histo[i];
	}

	// m_Histogram 배열의 최대값이 100이 되도록 전체 배열의 값을 조절한다.
	for( i = 0 ; i < 256 ; i++ ) 
	{
		m_Histogram[i] = 
		(int)(histo[i]*100/max_value);
	}
}

void CHistogramDlg::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    register int i;

	// 히스토그램 박스 출력
	dc.MoveTo(20, 30);
	dc.LineTo(20, 130);
	dc.LineTo(275, 130);
	dc.LineTo(275, 30);

	// 각 그레이스케일에 해당하는 히스토그램 출력
	for( i = 0 ; i < 256 ; i++ ) 
	{
		dc.MoveTo( 20+i, 130 );
		dc.LineTo( 20+i, 130 - m_Histogram[i] );
	}

	// 그레이스케일 레벨 출력
	for( i = 0 ; i < 256 ; i++ ) 
	{
		dc.SelectStockObject(DC_PEN);
		dc.SetDCPenColor(RGB(i, i, i));

		dc.MoveTo( 20+i, 140 );
		dc.LineTo( 20+i, 155 );
	}

	dc.SelectStockObject(DC_PEN);
	dc.SetDCPenColor(RGB(128, 128, 128));

	int sum[256] = {0, };
	sum[0] = m_Histogram[0];
	for( i = 1 ; i < 256 ; i++ )
		sum[i] = sum[i-1] + m_Histogram[i];

	dc.MoveTo( 20, 130 );
	for( i = 0 ; i < 256 ; i++ )
	{
		dc.LineTo( 20+i, 130 - sum[i]*100/sum[255] );
	}
    // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
}
