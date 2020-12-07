#include "stdafx.h"
#include "ConvexHull.h"


CConvexHull::CConvexHull(void)
{

}


CConvexHull::~CConvexHull(void)
{

}

void CConvexHull::setConvexHull(){
	Chpts.RemoveAll();
	CPoint pt,tmpPt;
	int idx;
	int size = pts.GetSize();
	if(size<1)
		return;
	tmpPt.x = pts.GetAt(0).x;
	tmpPt.y = pts.GetAt(0).y;
	for(int i=1;i<size;i++){
		pt.x = pts.GetAt(i).x;
		pt.y = pts.GetAt(i).y;
		if(tmpPt.y>pt.y){
			tmpPt.x = pt.x;
			tmpPt.y = pt.y;
			idx = i;
		}
	}
	tmpPt.x = pts.GetAt(idx).x;
	tmpPt.y = pts.GetAt(idx).y;
	this->Chpts.Add(tmpPt);
	pt.x = tmpPt.x;
	pt.y = tmpPt.y;
	tmpPt.x = tmpPt.x - 10;
	CPoint originPt;
	originPt.x= pt.x;
	originPt.y= pt.y;
	float cosDelt1;
	CPoint tt;
	do{
		float cosDelt = INT_MIN;
		size = pts.GetSize();
		for(int j=0;j<size;j++){
			tt.x = pts.GetAt(j).x;
			tt.y = pts.GetAt(j).y;
			cosDelt1 = ((pt.x-tmpPt.x)*1.0*(tt.x-pt.x)+(pt.y-tmpPt.y)*1.0*(tt.y-pt.y))/(sqrt((tt.x-pt.x)*1.0*(tt.x-pt.x)+(tt.y-pt.y)*1.0*(tt.y-pt.y))*sqrt((pt.x-tmpPt.x)*1.0*(pt.x-tmpPt.x)+(pt.y-tmpPt.y)*1.0*(pt.y-tmpPt.y)));
			if(cosDelt1>=cosDelt){
				cosDelt = cosDelt1;
				idx = j;
			}
		}
		tmpPt.x = pt.x;
		tmpPt.y = pt.y;
		pt.y = pts.GetAt(idx).y;
		pt.x = pts.GetAt(idx).x;
		Chpts.Add(pt);
	}while(originPt.x!=pt.x||originPt.y!=pt.y);
}

void CConvexHull::draw(CDC *pDC){
	setConvexHull();

	int size = Chpts.GetSize();
	for(int i=0;i<size;i++)
	{
		if(i==0)
			pDC->MoveTo(Chpts[i]);
		else
			pDC->LineTo(Chpts[i]);
	}
}