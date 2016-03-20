#version 400 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform mat4 data_matrix;
uniform mat4 uv_matrix;

out VS_OUT
{
    vec2 textCoordinate;
	mat4 uv_mat;
} vs_out;

void main(void)
{
	// squirrel away the texture and the uv matrix to the fragment stage
    vs_out.textCoordinate = tc;
	vs_out.uv_mat = uv_matrix;

	// Since the shader can be repeat and divided on a per vertex basis
	// we have no control which one gets attack first, so make it agnostic
	// I can just use v[gl_VertexID] directly

	vec4 vin;

	if(gl_VertexID < 4)
	{
		vin.x = data_matrix[gl_VertexID].x;
		vin.y = data_matrix[gl_VertexID].y;
		vin.z = 0.0f;
		vin.w = 1.0f;
	}
	else
	{		
		vin.x = data_matrix[gl_VertexID-4].z;
		vin.y = data_matrix[gl_VertexID-4].w;
		vin.z = 0.0f;
		vin.w = 1.0f;
	}

	// create the transformed vert
    gl_Position = proj_matrix * view_matrix * world_matrix *  vin;

}
