#include "stdafx.h"
#include "GeoObject.h"


CGeoObject::CGeoObject(void)
{
	this->lineWidth = 1;
	this->lineType = 0;
	this->r = 0;
	this->b = 0;
	this->g = 0;
	this->areaType = 0;
	this->r2 = 0;
	this->b2 = 0;
	this->g2 = 0;
}


CGeoObject::~CGeoObject(void)
{
}

void CGeoObject::setName(CString name){
	this->name = name;
}

CString CGeoObject::getName(){
	return this->name;
}

void CGeoObject::setId(int id){
	this->id = id;
}

int CGeoObject::getId(){
	return this->id;
}

void CGeoObject::setRect(CRect rect){
	this->crRect = rect;
}

CRect CGeoObject::getRect(){
	return this->crRect;
}

/*void CGeoObject::setRect(int left,int right,int width,int height){
	this->crRect.left = left;
	this->crRect.right = left;
}*/

//ÉèÖÃÀàÐÍ
void CGeoObject::setType(int type){
	this->type = type;
}

int CGeoObject::getType(){
	return this->type;
}
void CGeoObject::draw(CDC *pDC){
	
}

void CGeoObject::clipObj(CRect wcRect1){

}

