#pragma once
#include "geoobject.h"
#include  "afxtempl.h"
class CConvexHull :
	public CGeoObject
{
public:
	CConvexHull(void);
	virtual ~CConvexHull(void);
	// ��ɢ�㼯���괮
	CArray<CPoint ,CPoint > pts;
	// ͹�����괮
	CArray<CPoint ,CPoint > Chpts;
	// �㼯������
	CRect crWCRect;
	// ���õ㼯͹��
	void setConvexHull();
	// ���Ƶ㼯��͹��
	void draw(CDC *pDC);
};

