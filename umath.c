#include "umath.h"
#include <tgmath.h>
#include <string.h>

#define _USE_MATH_DEFINES
#include <math.h>

#define DEG_TO_RAD 0.01745329251f

#ifdef __cplusplus
extern "C" {
#endif

umat4 util_perspective(float aspect, float fov, float znear, float zfar) {
	float zm = zfar - znear;
	float zp = zfar + znear;
	fov = fov * (M_PI / 360);
	float x = 1.0f / (tan(fov));

	umat4 mat = {
		x / aspect, 0, 0, 0,
		0, x, 0, 0,
		0, 0, -(zp / zm), -1,
		0, 0, -(2 * zfar * znear) / zm, 1
	};

	return mat;
}

umat4 mat4_identity(void) {
	umat4 identity = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	return identity;
}

void mat4_setidentity(umat4* mat) {
	memset(mat, 0, 16 * sizeof(float));

	mat->col0[0] = 1;
	mat->col1[1] = 1;
	mat->col2[2] = 1;
	mat->col3[3] = 1;
}

void mat4_translate(umat4* mat, uvec3 vec) {
	mat->col3[0] += vec.x;
	mat->col3[1] += vec.y;
	mat->col3[2] += vec.z;
}

void mat4_settranslation(umat4* mat, uvec3 vec){
	mat->col3[0] = vec.x;
	mat->col3[1] = vec.y;
	mat->col3[2] = vec.z;
}

void mat4_mul(umat4* m1, umat4* m2, umat4* result) {
	umat4 res;
	res.col0[0] = m1->col0[0] * m2->col0[0] + m1->col1[0] * m2->col0[1] + m1->col2[0] * m2->col0[2] + m1->col3[0] * m2->col0[3];
	res.col1[0] = m1->col0[0] * m2->col1[0] + m1->col1[0] * m2->col1[1] + m1->col2[0] * m2->col1[2] + m1->col3[0] * m2->col1[3];
	res.col2[0] = m1->col0[0] * m2->col2[0] + m1->col1[0] * m2->col2[1] + m1->col2[0] * m2->col2[2] + m1->col3[0] * m2->col2[3];
	res.col3[0] = m1->col0[0] * m2->col3[0] + m1->col1[0] * m2->col3[1] + m1->col2[0] * m2->col3[2] + m1->col3[0] * m2->col3[3];

	res.col0[1] = m1->col0[1] * m2->col0[0] + m1->col1[1] * m2->col0[1] + m1->col2[1] * m2->col0[2] + m1->col3[1] * m2->col0[3];
	res.col1[1] = m1->col0[1] * m2->col1[0] + m1->col1[1] * m2->col1[1] + m1->col2[1] * m2->col1[2] + m1->col3[1] * m2->col1[3];
	res.col2[1] = m1->col0[1] * m2->col2[0] + m1->col1[1] * m2->col2[1] + m1->col2[1] * m2->col2[2] + m1->col3[1] * m2->col2[3];
	res.col3[1] = m1->col0[1] * m2->col3[0] + m1->col1[1] * m2->col3[1] + m1->col2[1] * m2->col3[2] + m1->col3[1] * m2->col3[3];

	res.col0[2] = m1->col0[2] * m2->col0[0] + m1->col1[2] * m2->col0[1] + m1->col2[2] * m2->col0[2] + m1->col3[2] * m2->col0[3];
	res.col1[2] = m1->col0[2] * m2->col1[0] + m1->col1[2] * m2->col1[1] + m1->col2[2] * m2->col1[2] + m1->col3[2] * m2->col1[3];
	res.col2[2] = m1->col0[2] * m2->col2[0] + m1->col1[2] * m2->col2[1] + m1->col2[2] * m2->col2[2] + m1->col3[2] * m2->col2[3];
	res.col3[2] = m1->col0[2] * m2->col3[0] + m1->col1[2] * m2->col3[1] + m1->col2[2] * m2->col3[2] + m1->col3[2] * m2->col3[3];

	res.col0[3] = m1->col0[3] * m2->col0[0] + m1->col1[3] * m2->col0[1] + m1->col2[3] * m2->col0[2] + m1->col3[3] * m2->col0[3];
	res.col1[3] = m1->col0[3] * m2->col1[0] + m1->col1[3] * m2->col1[1] + m1->col2[3] * m2->col1[2] + m1->col3[3] * m2->col1[3];
	res.col2[3] = m1->col0[3] * m2->col2[0] + m1->col1[3] * m2->col2[1] + m1->col2[3] * m2->col2[2] + m1->col3[3] * m2->col2[3];
	res.col3[3] = m1->col0[3] * m2->col3[0] + m1->col1[3] * m2->col3[1] + m1->col2[3] * m2->col3[2] + m1->col3[3] * m2->col3[3];

	*result = res;
}

void mat4_mulvec3(umat4* m1, uvec3* vec) {
	uvec3 res;
	//res.x =
}

void mat4_scale(umat4* mat1, uvec3 vec) {
	mat1->col0[0] *= vec.x;

	mat1->col1[1] *= vec.y;

	mat1->col2[2] *= vec.z;
}

void rotation_matrix(umat3* mat, uvec3 rotation) {
	umat3 y;
	umat3 z;

	mat3_setidentity(mat);
	mat3_setidentity(&y);
	mat3_setidentity(&z);

	float cos;
	float sin;

	if(rotation.x > 0.001f || rotation.x < -0.001f){
		cos = cosf(rotation.x * DEG_TO_RAD);
		sin = sinf(rotation.x * DEG_TO_RAD);

		(*mat).col1[1] = cos;
		(*mat).col2[1] = -sin;
		(*mat).col2[2] = cos;
		(*mat).col1[2] = sin;
	}

	if(rotation.y > 0.001f || rotation.y < -0.001f || 1){
		cos = cosf(rotation.y * DEG_TO_RAD);
		sin = sinf(rotation.y * DEG_TO_RAD);

		y.col0[0] = cos;
		y.col0[2] = -sin;
		y.col2[0] = sin;
		y.col2[2] = cos;
	}

	if(rotation.z > 0.001f || rotation.z < -0.001f){
		cos = cosf(rotation.z * DEG_TO_RAD);
		sin = sinf(rotation.z * DEG_TO_RAD);

		z.col0[0] = cos;
		z.col1[0] = -sin;
		z.col1[1] = cos;
		z.col0[1] = sin;
	}

	mat3_mul(mat, &y);
	mat3_mul(mat, &z);
}

umat3 mat4_tomat3(umat4* mat) {
	umat3 m = {
		mat->col0[0], mat->col0[1], mat->col0[2],
		mat->col1[0], mat->col1[1], mat->col1[2],
		mat->col3[0], mat->col3[1], mat->col3[2]
	};

	return m;
}

void mat4_transpose(umat4* mat) {
	float buffer;

	buffer = mat->col0[1];
	mat->col0[1] = mat->col1[0];
	mat->col1[0] = buffer;

	buffer = mat->col0[2];
	mat->col0[2] = mat->col2[0];
	mat->col2[0] = buffer;

	buffer = mat->col0[3];
	mat->col0[3] = mat->col3[0];
	mat->col3[0] = buffer;

	buffer = mat->col1[2];
	mat->col1[2] = mat->col2[1];
	mat->col2[1] = buffer;

	buffer = mat->col1[3];
	mat->col1[3] = mat->col3[1];
	mat->col3[1] = buffer;

	buffer = mat->col2[3];
	mat->col2[3] = mat->col3[2];
	mat->col3[2] = buffer;
}

umat3 mat3_identity(void) {
	umat3 identity = {
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};

	return identity;
}

void mat3_setidentity(umat3* mat) {
	memset(mat, 0, 9 * sizeof(float));
	mat->col0[0] = 1;
	mat->col1[1] = 1;
	mat->col2[2] = 1;
}

void mat3_mul(umat3* m1, umat3* m2) {
	umat3 m3;
	m3.col0[0] = m1->col0[0] * m2->col0[0] + m1->col1[0] * m2->col0[1] + m1->col2[0] * m2->col0[2];
	m3.col1[0] = m1->col0[0] * m2->col1[0] + m1->col1[0] * m2->col1[1] + m1->col2[0] * m2->col1[2];
	m3.col2[0] = m1->col0[0] * m2->col2[0] + m1->col1[0] * m2->col2[1] + m1->col2[0] * m2->col2[2];

	m3.col0[1] = m1->col0[1] * m2->col0[0] + m1->col1[1] * m2->col0[1] + m1->col2[1] * m2->col0[2];
	m3.col1[1] = m1->col0[1] * m2->col1[0] + m1->col1[1] * m2->col1[1] + m1->col2[1] * m2->col1[2];
	m3.col2[1] = m1->col0[1] * m2->col2[0] + m1->col1[1] * m2->col2[1] + m1->col2[1] * m2->col2[2];

	m3.col0[2] = m1->col0[2] * m2->col0[0] + m1->col1[2] * m2->col0[1] + m1->col2[2] * m2->col0[2];
	m3.col1[2] = m1->col0[2] * m2->col1[0] + m1->col1[2] * m2->col1[1] + m1->col2[2] * m2->col1[2];
	m3.col2[2] = m1->col0[2] * m2->col2[0] + m1->col1[2] * m2->col2[1] + m1->col2[2] * m2->col2[2];

	*m1 = m3;
}

void mat3_emplacemat4(umat3* mat, umat4* target) {
	target->col0[0] = mat->col0[0];
	target->col0[1] = mat->col0[1];
	target->col0[2] = mat->col0[2];

	target->col1[0] = mat->col1[0];
	target->col1[1] = mat->col1[1];
	target->col1[2] = mat->col1[2];

	target->col2[0] = mat->col2[0];
	target->col2[1] = mat->col2[1];
	target->col2[2] = mat->col2[2];
}

uvec3 vec3_scale(uvec3 vec, float scalar) {
	return (uvec3) { vec.x * scalar, vec.y * scalar, vec.z * scalar };
}

void mat4_mul3(umat4* m1, umat3* m2, umat4* res) {
	*res = *m1;

	res->col0[0] = m1->col0[0] * m2->col0[0] + m1->col1[0] * m2->col0[1] + m1->col2[0] * m2->col0[2];
	res->col1[0] = m1->col0[0] * m2->col1[0] + m1->col1[0] * m2->col1[1] + m1->col2[0] * m2->col1[2];
	res->col2[0] = m1->col0[0] * m2->col2[0] + m1->col1[0] * m2->col2[1] + m1->col2[0] * m2->col2[2];

	res->col0[1] = m1->col0[1] * m2->col0[0] + m1->col1[1] * m2->col0[1] + m1->col2[1] * m2->col0[2];
	res->col1[1] = m1->col0[1] * m2->col1[0] + m1->col1[1] * m2->col1[1] + m1->col2[1] * m2->col1[2];
	res->col2[1] = m1->col0[1] * m2->col2[0] + m1->col1[1] * m2->col2[1] + m1->col2[1] * m2->col2[2];

	res->col0[2] = m1->col0[2] * m2->col0[0] + m1->col1[2] * m2->col0[1] + m1->col2[2] * m2->col0[2];
	res->col1[2] = m1->col0[2] * m2->col1[0] + m1->col1[2] * m2->col1[1] + m1->col2[2] * m2->col1[2];
	res->col2[2] = m1->col0[2] * m2->col2[0] + m1->col1[2] * m2->col2[1] + m1->col2[2] * m2->col2[2];
}
void mat3_mul4(umat3* mat1, umat4* mat2, umat4* res) {
	*res = *mat2;

	res->col0[0] = mat2->col0[0] * mat1->col0[0] + mat2->col1[0] * mat1->col0[1] + mat2->col2[0] * mat1->col0[2];
	res->col1[0] = mat2->col0[0] * mat1->col1[0] + mat2->col1[0] * mat1->col1[1] + mat2->col2[0] * mat1->col1[2];
	res->col2[0] = mat2->col0[0] * mat1->col2[0] + mat2->col1[0] * mat1->col2[1] + mat2->col2[0] * mat1->col2[2];

	res->col0[1] = mat2->col0[1] * mat1->col0[0] + mat2->col1[1] * mat1->col0[1] + mat2->col2[1] * mat1->col0[2];
	res->col1[1] = mat2->col0[1] * mat1->col1[0] + mat2->col1[1] * mat1->col1[1] + mat2->col2[1] * mat1->col1[2];
	res->col2[1] = mat2->col0[1] * mat1->col2[0] + mat2->col1[1] * mat1->col2[1] + mat2->col2[1] * mat1->col2[2];

	res->col0[2] = mat2->col0[2] * mat1->col0[0] + mat2->col1[2] * mat1->col0[1] + mat2->col2[2] * mat1->col0[2];
	res->col1[2] = mat2->col0[2] * mat1->col1[0] + mat2->col1[2] * mat1->col1[1] + mat2->col2[2] * mat1->col1[2];
	res->col2[2] = mat2->col0[2] * mat1->col2[0] + mat2->col1[2] * mat1->col2[1] + mat2->col2[2] * mat1->col2[2];
}

void mat3_transpose(umat3* mat) {
	float buffer;

	buffer = mat->col0[1];
	mat->col0[1] = mat->col1[0];
	mat->col1[0] = buffer;

	buffer = mat->col0[2];
	mat->col0[2] = mat->col2[0];
	mat->col2[0] = buffer;

	buffer = mat->col1[2];
	mat->col1[2] = mat->col2[1];
	mat->col2[1] = buffer;
}

void mat4_transposemat3(umat4* mat) {
	float buffer;

	buffer = mat->col0[1];
	mat->col0[1] = mat->col1[0];
	mat->col1[0] = buffer;

	buffer = mat->col0[2];
	mat->col0[2] = mat->col2[0];
	mat->col2[0] = buffer;

	buffer = mat->col1[2];
	mat->col1[2] = mat->col2[1];
	mat->col2[1] = buffer;
}

void mat4_copymat4transposedmat3(umat4* from, umat4* target){
	target->col0[0] = from->col0[0];
	target->col1[1] = from->col1[1];
	target->col2[2] = from->col2[2];

	target->col0[1] = from->col1[0];
	target->col1[0] = from->col0[1];

	target->col0[2] = from->col2[0];
	target->col2[0] = from->col0[2];

	target->col1[2] = from->col2[1];
	target->col2[1] = from->col1[2];
}

uvec3 vec3_negate(uvec3 vec){
	return (uvec3){-vec.x, -vec.y, -vec.z};
}

#ifdef __cplusplus
}
#endif
