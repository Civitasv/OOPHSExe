#include "stdafx.h"
#include "GeoAnno.h"


CGeoAnno::CGeoAnno(void)
{

}


CGeoAnno::~CGeoAnno(void)
{
}

/*int CGeoPolyline::getSize(void)
{
return 0;
}*/


void CGeoAnno::draw(CDC* pDC)
{
	CFont font;
	font.CreatePointFont(300000,CString("�����п�"),NULL);
	pDC->SelectObject(&font);
	//���ñ���͸��
	pDC->SetBkMode(TRANSPARENT);
	pDC->TextOut(point.x, point.y, annoName);//����ַ���StringData    
	CSize sz = pDC->GetTextExtent(annoName);
	SetCaretPos(point.x+sz.cx,point.y-sz.cy);
	//pDC->SelectObject( pOldFont );
}