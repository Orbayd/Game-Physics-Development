#version 400 core

layout (location = 0) in vec4 position;

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
uniform mat4 data_matrix;
             
void main(void)
{
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
