#pragma once
#include "afxtempl.h" //模板类头文件
#include "GeoLayer.h"
#include "MapProjection.h"
class CGeoMap
{
private:
	//地图名称
	CString name;
	//地图比例尺
	const int mapScale;
	//地图范围
	CRect crRect;
	
public:
	CGeoMap(void);
	virtual ~CGeoMap(void);
	void setName(CString mapName);
	CString getName();
	//地图包含图层
	CArray<CGeoLayer *,CGeoLayer *> geoLayers;
	//地图投影
	CMapProjection *mapProj;
	//裁切范围
	CRect clipRect;
	/*void setGeoLayers(CArray<CGeoLayer *,CGeoLayer *> geoLayers);
	CArray<CGeoLayer *,CGeoLayer *> getGeoLayers();*/

	/*void setScale(int mapScale);*/
	int getScale();
	void setRect(CRect crRect);
	CRect getRect();
	void addLayer(CGeoLayer *layer);
	void deleteLayerAt(int index);
	void deleteLayerAll();
	void setLayerVisible(CString layerName,bool isVisible);
	void draw(CDC *pDC);
	//给定矩形，裁切图形
	void clipMap(CRect clipRect1);
	CGeoLayer* getLayerByName(CString layerName); 
	void makeIndex(void);
};

