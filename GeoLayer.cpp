#include "stdafx.h"
#include "GeoLayer.h"


CGeoLayer::CGeoLayer(CString layerName,bool isVisible)
{

}
CGeoLayer::~CGeoLayer(){
	int size = geoObjects.GetSize();
	for(int i=0;i<size;i++)
	  delete geoObjects.ElementAt(i);
}
CGeoLayer::CGeoLayer(const CGeoLayer &layer)
{	
	this->crRect = layer.crRect;
	this->layerName = layer.layerName;
	this->isVisible = layer.isVisible;
	//TODO
}

CGeoLayer::CGeoLayer(CString layerName,bool isVisible,CRect crRect){
	this->layerName = layerName;
	this->isVisible = isVisible;
	this->crRect = crRect;
}

/*CGeoLayer::CGeoLayer(CString layerName,bool isVisible,CRect crRect,CArray<CGeoObject *,CGeoObject *> geoObjects){
	this->layerName = layerName;
	this->isVisible = isVisible;
	this->crRect = crRect;
	this->geoObjects = geoObjects;
}*/



void CGeoLayer::setName(CString layerName){
	this->layerName = layerName;
}

CString CGeoLayer::getLayerName(){
	return this->layerName;
}

void CGeoLayer::setRect(CRect rect){
	this->crRect = rect;
}

CRect CGeoLayer::getRect(){
	return this->crRect;
}

void CGeoLayer::setVisible(bool isVisible){
	this->isVisible = isVisible;
}

bool CGeoLayer::getVisible(){
	return this->isVisible;
}

/*void CGeoLayer::setGeoObjects(CArray<CGeoObject *,CGeoObject *> geoObjects){
	this->geoObjects = geoObjects;
}

CArray<CGeoObject *,CGeoObject *> CGeoLayer::getGeoObjects(){
	return this->geoObjects;
}*/
void CGeoLayer::addObjects(CGeoObject *obj){
	geoObjects.Add(obj);
}
/*void CGeoLayer::addPolylines(CGeoPolyline *poly){
	geoPolyLines.Add(poly);
}
void CGeoLayer::addPoints(CGeoPoint *point){
	geoPoints.Add(point);
}*/
void CGeoLayer::deleteObjectAt(int index){
	geoObjects.RemoveAt(index);
}
void CGeoLayer::deleteObjectAll(){
	geoObjects.RemoveAll();
}
/*void CGeoLayer::draw(CDC *pDC){
	for(int i=0;i<geoPolyLines.GetSize();i++)
		geoPolyLines.GetAt(i)->draw(pDC);
}
void CGeoLayer::draw2(CDC *pDC){

	for(int i=0;i<geoPoints.GetSize();i++)
		geoPoints.GetAt(i)->draw(pDC);
}*/
void CGeoLayer::draw3(CDC *pDC){
	int x = geoObjects.GetSize();
	this->crRect;
	for(int i=0;i<geoObjects.GetSize();i++)
		geoObjects.GetAt(i)->draw(pDC);
}

void CGeoLayer::clipLayer(CRect clipRect1){
 	for(int i=0;i<geoObjects.GetSize();i++)
		geoObjects.GetAt(i)->clipObj(clipRect1);
}

void CGeoLayer::makeIndex(void)
{
	
}
