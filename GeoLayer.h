#pragma once
#include "afxtempl.h" //ģ����ͷ�ļ�
#include "geopoint.h"
#include "geopolyline.h"
#include "geopolygon.h"
#include "geoobject.h"
#include "geoanno.h"
#include "convexhull.h"
class CGeoLayer
{
private:
	//ͼ������
	CString layerName;
	//�Ƿ�ɼ�
	bool isVisible;
	//ͼ�㷶Χ
	CRect crRect;
	
public:
	//ȱʡ���캯��
	CGeoLayer(CString layerName = _T("Test"),bool isVisible=true);
	//�������캯��
	CGeoLayer(const CGeoLayer &layer);
	//���ι��캯��
	CGeoLayer(CString layerName,bool isVisible,CRect crRect);
	//CGeoLayer(CString layerName,bool isVisible,CRect crRect,CArray<CGeoObject *,CGeoObject *> geoObjects);
	virtual ~CGeoLayer(void);
	//����Ŀ�����飬��CGeoObjects��������
	CArray<CGeoObject *,CGeoObject *> geoObjects;
	//CArray<CGeoPolyline *,CGeoPolyline *> geoPolyLines;
	//CArray<CGeoPoint *,CGeoPoint *> geoPoints;
	void setRect(CRect crRect);
	CRect getRect();

	void setName(CString layerName);
	CString getLayerName();

	void setVisible(bool isVisible);
	bool getVisible();

	/*void setGeoObjects(CArray<CGeoObject *,CGeoObject *> geoObjects);
	CArray<CGeoObject *,CGeoObject *> getGeoObjects();*/

	void addObjects(CGeoObject *obj);
	//void addPolylines(CGeoPolyline *poly);
	//void addPoints(CGeoPoint *point);
	void deleteObjectAt(int index);
	void deleteObjectAll();


	//void draw(CDC *pDC);
	//void draw2(CDC *pDC);
	void draw3(CDC *pDC);
	void clipLayer(CRect clipRect1);
	void makeIndex(void);
};

