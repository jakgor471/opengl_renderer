#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

out vec4 vertexColor;

void main()
{
	mat4 matrix = projection * view * transform;
	vec3 color = aColor;
    gl_Position = matrix * vec4(aPos, 1.0);
    vertexColor = vec4(abs(color.x), abs(color.y), abs(color.z), 1.0); 
}
