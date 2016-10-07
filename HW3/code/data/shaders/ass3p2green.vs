#version 330 core

// The vertex buffer input
in vec3 in_Color;
in vec3 in_Position;
in vec3 in_Normal;

// Transformations for the projections
uniform mat4 projectionMatrixBox;
uniform mat4 viewMatrixBox;
uniform mat4 modelMatrixBox;

// The material parameters
uniform vec3 diffuse_color;
uniform vec3 ambient_color;
uniform vec3 specular_color;
uniform float shininess;

// Position of the light source
uniform vec4 light_position0;

// Parameters for the spotlight
uniform float cone_angle0;
uniform vec3 cone_direction0;

// The intensity values for the reflection equations
uniform float diffuse_intensity0;
uniform float ambient_intensity0;
uniform float specular_intensity0;
uniform float shininess0;
uniform float attenuationCoefficient10;

// Position of the light source
uniform vec4 light_position1;

// Parameters for the spotlight
uniform float cone_angle1;
uniform vec3 cone_direction1;

// The intensity values for the reflection equations
uniform float diffuse_intensity1;
uniform float ambient_intensity1;
uniform float specular_intensity1;
uniform float attenuationCoefficient1;

// The output color
out vec3 pass_Color;


vec3 getSpotLight0() {
	// Spot light 0
	vec4 surfacePostion = modelMatrixBox * vec4(in_Position, 1.0);
	vec3 normal = normalize(in_Normal);
	vec4 transformedNormal =  normalize(transpose(inverse(modelMatrixBox)) * vec4( normal, 1.0 ));
	
	vec4 surface_to_light =   normalize( light_position0 -  surfacePostion );
	
	// Diffuse color
	float diffuse_coefficient = max( dot(transformedNormal, surface_to_light), 0.0);
	vec3 out_diffuse_color = diffuse_color  * diffuse_coefficient * diffuse_intensity0;
	
	// Ambient color
	vec3 out_ambient_color = vec3(ambient_color) * ambient_intensity0;
	
	// Specular color
	vec3 incidenceVector = -surface_to_light.xyz;
	vec3 reflectionVector = reflect(incidenceVector, transformedNormal.xyz);
	vec3 cameraPosition = vec3( -viewMatrixBox[3][0], -viewMatrixBox[3][1], -viewMatrixBox[3][2]);
	vec3 surfaceToCamera = normalize(cameraPosition - surfacePostion.xyz);
	float cosAngle = max( dot(surfaceToCamera, reflectionVector), 0.0);
	float specular_coefficient = pow(cosAngle, shininess);
	vec3 out_specular_color = specular_color * specular_coefficient * specular_intensity0;
	
	// 1. Normalize the cone direction
	vec3 cone_direction_norm = normalize(cone_direction0);
	
	// 2. Calculate the ray direction. We already calculated the surface to light direction.
	// 	  All what we need to do is to inverse this value
	vec3 ray_direction = -surface_to_light.xyz;
	
	// 3. Calculate the angle between light and surface using the dot product again.
	//    To simplify our understanding, we use the degrees
	float light_to_surface_angle = degrees(acos(dot(ray_direction, cone_direction_norm))) ;
	
	// 4. Last, we compare the angle with the current direction and
	//    reduce the attenuation to 0.0 if the light is outside the angle.
	float attenuation  = 1.0;
	if(light_to_surface_angle > cone_angle0) {
		attenuation = 0.0;
	}
	
	// sum iwth previous color
	return out_ambient_color  + attenuation * (out_diffuse_color + out_specular_color);
}

vec3 getSpotLight1() {
	// Spotlight 1
	vec3 normal = normalize(in_Normal);
	vec4 transformedNormal =  normalize(transpose(inverse(modelMatrixBox)) * vec4( normal, 1.0 ));
	vec4 surfacePostion = modelMatrixBox * vec4(in_Position, 1.0);
	
	vec4 surface_to_light = normalize( light_position1 -  surfacePostion );
	
	// Diffuse color
	float diffuse_coefficient = max( dot(transformedNormal, surface_to_light), 0.0);
	vec3 out_diffuse_color = specular_color  * diffuse_coefficient * diffuse_intensity1;
	
	// Ambient color
	vec3 out_ambient_color = vec3(ambient_color) * ambient_intensity1;
	
	// Specular color
	vec3 incidenceVector = -surface_to_light.xyz;
	vec3 reflectionVector = reflect(incidenceVector, transformedNormal.xyz);
	vec3 cameraPosition = vec3( -viewMatrixBox[3][0], -viewMatrixBox[3][1], -viewMatrixBox[3][2]);
	vec3 surfaceToCamera = normalize(cameraPosition - surfacePostion.xyz);
	float cosAngle = max( dot(surfaceToCamera, reflectionVector), 0.0);
	float specular_coefficient = pow(cosAngle, shininess);
	vec3 out_specular_color = specular_color * specular_coefficient * specular_intensity1;
	
	// Attenuation
	float distanceToLight = length(light_position1.xyz - surfacePostion.xyz);
	float attenuation = 1.0 / (1.0 + attenuationCoefficient1 * pow(distanceToLight, 2));
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	// Spotlight
	// 1. Normalize the cone direction
	vec3 cone_direction_norm = normalize(cone_direction1);
	
	// 2. Calculate the ray direction. We already calculated the surface to light direction.
	// 	  All what we need to do is to inverse this value
	vec3 ray_direction = -surface_to_light.xyz;
	
	// 3. Calculate the angle between light and surface using the dot product again.
	//    To simplify our understanding, we use the degrees
	float light_to_surface_angle = degrees(acos(dot(ray_direction, cone_direction_norm))) ;
	
	// 4. Last, we compare the angle with the current direction and
	//    reduce the attenuation to 0.0 if the light is outside the angle.
	float spotEffect  = 1.0;
	if(light_to_surface_angle > cone_angle1){
		attenuation = 0.0;
	} else {
		spotEffect = 1 - smoothstep(cone_angle1 - 0.7, cone_angle1, light_to_surface_angle);
	}
	
	// Calculate the linear color
	 return out_ambient_color  + spotEffect * attenuation * ( out_diffuse_color + out_specular_color);
}

void main(void)
{
	// Calculate the linear color
	vec3 linearColor = getSpotLight0() + getSpotLight1();

	// Gamma correction
	vec3 gamma = vec3(1.0/2.2);
	vec3 finalColor = pow(linearColor, gamma);
	
	// Pass the color
	pass_Color =  finalColor;
	
	// Passes the projected position to the fragment shader / rasterization process.
	gl_Position = projectionMatrixBox * viewMatrixBox * modelMatrixBox * vec4(in_Position, 1.0);
	
}
