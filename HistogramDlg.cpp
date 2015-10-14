// HistogramDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MidtermProject.h"
#include "HistogramDlg.h"


// CHistogramDlg ��ȭ �����Դϴ�.

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


// CHistogramDlg �޽��� ó�����Դϴ�.

void CHistogramDlg::SetImage(float histo[256])
{
  // m_Histogram �迭�� �ִ밪�� ���Ѵ�.
	register int i;
	float max_value = histo[0];
	for( i = 1 ; i < 256 ; i++ ) 
	{
		if( histo[i] > max_value ) 
		max_value = histo[i];
	}

	// m_Histogram �迭�� �ִ밪�� 100�� �ǵ��� ��ü �迭�� ���� �����Ѵ�.
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

	// ������׷� �ڽ� ���
	dc.MoveTo(20, 30);
	dc.LineTo(20, 130);
	dc.LineTo(275, 130);
	dc.LineTo(275, 30);

	// �� �׷��̽����Ͽ� �ش��ϴ� ������׷� ���
	for( i = 0 ; i < 256 ; i++ ) 
	{
		dc.MoveTo( 20+i, 130 );
		dc.LineTo( 20+i, 130 - m_Histogram[i] );
	}

	// �׷��̽����� ���� ���
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
    // �׸��� �޽����� ���ؼ��� CDialog::OnPaint()��(��) ȣ������ ���ʽÿ�.
}