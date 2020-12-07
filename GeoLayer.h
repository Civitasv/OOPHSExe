#pragma once
#include "afxtempl.h" //模板类头文件
#include "geopoint.h"
#include "geopolyline.h"
#include "geopolygon.h"
#include "geoobject.h"
#include "geoanno.h"
#include "convexhull.h"
class CGeoLayer
{
private:
	//图层名称
	CString layerName;
	//是否可见
	bool isVisible;
	//图层范围
	CRect crRect;
	
public:
	//缺省构造函数
	CGeoLayer(CString layerName = _T("Test"),bool isVisible=true);
	//拷贝构造函数
	CGeoLayer(const CGeoLayer &layer);
	//带参构造函数
	CGeoLayer(CString layerName,bool isVisible,CRect crRect);
	//CGeoLayer(CString layerName,bool isVisible,CRect crRect,CArray<CGeoObject *,CGeoObject *> geoObjects);
	virtual ~CGeoLayer(void);
	//地理目标数组，与CGeoObjects建立关联
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

