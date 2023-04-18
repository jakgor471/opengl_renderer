#ifndef UMATH_H_
#define UMATH_H_

#ifdef __cplusplus
struct umat4 {
	float col0[4];
	float col1[4];
	float col2[4];
	float col3[4];
};

struct umat3 {
	float col0[3];
	float col1[3];
	float col2[3];
};

struct uvec3 {
	float x, y, z;

	uvec3 operator-(uvec3 vec2){
		return (uvec3){this->x - vec2.x, this->y - vec2.y, this->z - vec2.z};
	}

	uvec3 operator+(uvec3 vec2){
		return (uvec3){this->x + vec2.x, this->y + vec2.y, this->z + vec2.z};
	}

	uvec3 operator-(){
		return (uvec3){-this->x, -this->y, -this->z};
	}

	uvec3 operator*(float scalar){
		return (uvec3){this->x * scalar, this->y * scalar, this->z * scalar};
	}
};
extern "C" {
#endif

#ifndef __cplusplus
typedef struct mat4 {
	float col0[4];
	float col1[4];
	float col2[4];
	float col3[4];
}umat4;

typedef struct mat3 {
	float col0[3];
	float col1[3];
	float col2[3];
}umat3;

typedef struct vec3 {
	float x, y, z;
} uvec3;
#endif

umat4 util_perspective(float aspect, float fov, float znear, float zfar);
umat4 mat4_identity(void);
void mat4_setidentity(umat4* mat);
void mat4_translate(umat4* mat, uvec3 vec);
void mat4_settranslation(umat4* mat, uvec3 vec);
void mat4_mul(umat4* m1, umat4* m2, umat4* res);
void mat4_scale(umat4* mat1, uvec3 vec);
void rotation_matrix(umat3* mat, uvec3 rotation);
void mat4_transpose(umat4* mat);
void mat4_transposemat3(umat4* mat);
void mat4_copymat4transposedmat3(umat4* from, umat4* target);
void mat4_mul3(umat4* m1, umat3* m2, umat4* res);
void mat3_mul4(umat3* m1, umat4* m2, umat4* res);

umat3 mat4_tomat3(umat4* mat);
umat3 mat3_identity(void);
void mat3_setidentity(umat3* mat);
void mat3_mul(umat3* mat1, umat3* mat2);
void mat3_emplacemat4(umat3* mat, umat4* target);
void mat3_transpose(umat3* mat);
uvec3 vec3_scale(uvec3 vec, float scalar);
uvec3 vec3_negate(uvec3 vec);

#ifdef __cplusplus
}
#endif

#endif
