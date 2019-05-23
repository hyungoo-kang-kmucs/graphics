#version 120                  // GLSL 1.20

varying vec3 v_position;
varying vec3 v_normal;
varying vec3 v_color;

uniform mat4 u_M;

uniform   vec3 u_light_position;
uniform   vec3 u_light_diffuse;
uniform   vec3 u_material_diffuse;

uniform   vec3 u_camera_position;
uniform   vec3 u_light_specular;
uniform   vec3 u_material_specular;

uniform   vec3 u_light_ambient;
uniform   vec3 u_material_ambient;

vec3 calc_color()
{
  // 0th step) initialization
  vec3 color = vec3(0);

  // 1st step) diffuse reflection
  vec3 p_wc = (u_M * vec4(v_position, 1)).xyz;
  vec3 n_wc = (u_M * vec4(v_normal, 0)).xyz;
  vec3 l_wc = normalize(u_light_position - p_wc);

  float ndotl = max(0, dot(n_wc, l_wc));
  // TODO 03-1) 오른쪽 피연산자 출력하기 
  color += (u_material_diffuse * (ndotl * u_light_diffuse));

  // second step) specular reflection (alpha is 5)
  vec3 r_wc = normalize((2 * dot(l_wc, n_wc) *n_wc) - l_wc);
  vec3 v_wc = normalize(u_camera_position - p_wc);

  float rdotv = max(0, pow(dot(r_wc, v_wc), 5));
  // TODO 03-2) 오른쪽 피연산자 출력하기
  color += (u_material_specular * (rdotv * u_light_specular));

  // third step) ambient reflection
  color += (u_material_ambient * u_light_ambient);

  return color;
}

void main()
{
	vec3 color = calc_color();
	gl_FragColor = vec4(color, 1.0f);
}