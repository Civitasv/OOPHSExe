#include "stdafx.h"
#include "GeoMap.h"


CGeoMap::CGeoMap(void):mapScale(mapScale)
{
}


CGeoMap::~CGeoMap(void)
{
	int size = geoLayers.GetSize();
	for(int i=0;i<size;i++)
		delete geoLayers.ElementAt(i);
}

void CGeoMap::setName(CString mapName){
	this->name =mapName;
}
CString CGeoMap::getName(){
	return this->name;
}


/*void CGeoMap::setGeoLayers(CArray<CGeoLayer *,CGeoLayer *> geoLayers){
	this->geoLayers = geoLayers;
}
CArray<CGeoLayer *,CGeoLayer *> CGeoMap::getGeoLayers(){
	return this->geoLayers;
}*/


int CGeoMap::getScale(){
	return this->mapScale;
}

void CGeoMap::setRect(CRect crRect){
	this->crRect = crRect;
}


CRect CGeoMap::getRect(){
	return this->crRect;
}


void CGeoMap::addLayer(CGeoLayer *layer){
	geoLayers.Add(layer);
}
void CGeoMap::deleteLayerAt(int index){
	geoLayers.RemoveAt(index);
}
void CGeoMap::deleteLayerAll(){
	geoLayers.RemoveAll();
}
void CGeoMap::setLayerVisible(CString layerName,bool isVisible){

}
void CGeoMap::draw(CDC *pDC){
	for(int i=0;i<geoLayers.GetSize();i++)
		geoLayers.GetAt(i)->draw3(pDC);
	//mapProj->draw(pDC);
}

CGeoLayer* CGeoMap::getLayerByName(CString layerName){
	for(int i=0;i<geoLayers.GetSize();i++){
		if(!layerName.CompareNoCase(geoLayers.GetAt(i)->getLayerName())){
			return geoLayers.GetAt(i);
		}
	}
	return NULL;
}

void CGeoMap::clipMap(CRect clipRect1){
	for(int i=0;i<geoLayers.GetSize();i++)
		geoLayers.GetAt(i)->clipLayer(clipRect1);
}

void CGeoMap::makeIndex(void)
{
	for(int i=0;i<geoLayers.GetSize();i++){
		geoLayers.GetAt(i)->setRect(this->getRect());
		geoLayers.GetAt(i)->makeIndex();
	}
}
