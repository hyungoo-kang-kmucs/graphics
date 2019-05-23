#version 120                  // GLSL 1.20

uniform mat4 u_PVM;           // Proj * View * Model

attribute vec3 a_position;    // per-vertex position (per-vertex input)
attribute vec3 a_normal;       // per-vertex color (per-vertex input)

//새로 추가한것 , 남길것
varying vec3 v_position;
varying vec3 v_normal;

void main()
{
  gl_Position = u_PVM * vec4(a_position, 1.0f);

  v_position = a_position;
  v_normal = a_normal;

}
