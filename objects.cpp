#include "objects.h"

void Object::setPos(uvec3 pos){
	position = pos;
	transform(false);
}

uvec3 Object::getPos(){
	return position;
}

void Object::setAngle(uvec3 angle){
	this->angle = angle;
	transform(true);
}

uvec3 Object::getAngle(){
	return angle;
}

void Object::setScale(uvec3 scale){
	this->scale = scale;
	mat4_scale(&matrix, scale);
}

uvec3 Object::getScale(){
	return this->scale;
}

const umat4* Object::getTransformMatrix(){
	return &matrix;
}

void Camera::transform(bool updateRot){
	Object::transform(updateRot);

	scale = (const uvec3){1, 1, 1};

	mat4_setidentity(&view);
	mat4_settranslation(&view, -position);

	umat4 rot;
	mat4_setidentity(&rot);
	mat4_copymat4transposedmat3(&matrix, &rot);

	mat4_mul(&rot, &view, &view);
}

const umat4* Camera::getViewMatrix(){
	return &view;
}
