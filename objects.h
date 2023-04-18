#ifndef OBJECTS_H_
#define OBJECTS_H_

#include "umath.h"

class Object{
protected:
	umat4 matrix;
	uvec3 position;
	uvec3 angle;
	uvec3 scale;

	virtual void transform(bool updateRot){
		mat4_settranslation(&matrix, position);

		if(updateRot){
			umat3 rotate;
			rotation_matrix(&rotate, angle);
			mat3_emplacemat4(&rotate, &matrix);
			mat4_scale(&matrix, scale);
		}
	}
public:
	Object(){
		matrix = mat4_identity();
		position = (const uvec3){0, 0, 0};
		angle = (const uvec3){0, 0, 0};
		scale = (const uvec3){1, 1, 1};
	}
	void setPos(uvec3 pos);
	uvec3 getPos();

	void setAngle(uvec3 angle);
	uvec3 getAngle();

	void setScale(uvec3 scale);
	uvec3 getScale();

	const umat4* getTransformMatrix();

	virtual ~Object(){

	}
};

class Camera : public Object{
protected:
	umat4 view;

	void transform(bool updateRot);
public:
	Camera() : Object(){
		view = mat4_identity();
	}
	const umat4* getViewMatrix();
};

#endif
