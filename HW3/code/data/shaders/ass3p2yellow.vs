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

// Position of the light source
uniform vec4 light_position;

// New parameters for the spotlight
uniform float cone_angle;
uniform vec3 cone_direction;

// The intensity values for the reflection equations
uniform float diffuse_intensity;
uniform float ambient_intensity;
uniform float specular_intensity;
uniform float shininess;
uniform float attenuationCoefficient;

// Position of the light source
uniform vec4 light_position0;

// The intensity values for the reflection equations
uniform float diffuse_intensity0;
uniform float ambient_intensity0;
uniform float specular_intensity0;
uniform float shininess0;
uniform float attenuationCoefficient0;

// Position of the light source
uniform vec4 light_position2;

// New parameters for the spotlight
uniform float cone_angle2;
uniform vec3 cone_direction2;

// The intensity values for the reflection equations
uniform float diffuse_intensity2;
uniform float ambient_intensity2;
uniform float specular_intensity2;
uniform float shininess2;
uniform float attenuationCoefficient2;

// Position of the light source
uniform vec4 light_position3;

// New parameters for the spotlight
uniform float cone_angle3;
uniform vec3 cone_direction3;

// The intensity values for the reflection equations
uniform float diffuse_intensity3;
uniform float ambient_intensity3;
uniform float specular_intensity3;
uniform float shininess3;
uniform float attenuationCoefficient3;

// The output color
out vec3 pass_Color;

vec3 getLight1() {
	 vec3 normal = normalize(in_Normal);
    vec4 transformedNormal =  normalize(transpose(inverse(modelMatrixBox)) * vec4( normal, 1.0 ));
    vec4 surfacePostion = modelMatrixBox * vec4(in_Position, 1.0);

    vec4 surface_to_light =   normalize( light_position -  surfacePostion );

    // Diffuse color
    float diffuse_coefficient = max( dot(transformedNormal, surface_to_light), 0.0);
    vec3 out_diffuse_color = specular_color  * diffuse_coefficient * diffuse_intensity;

    // Ambient color
    vec3 out_ambient_color = vec3(ambient_color) * ambient_intensity;

    // Specular color
    vec3 incidenceVector = -surface_to_light.xyz;
    vec3 reflectionVector = reflect(incidenceVector, transformedNormal.xyz);
    vec3 cameraPosition = vec3( -viewMatrixBox[3][0], -viewMatrixBox[3][1], -viewMatrixBox[3][2]);
    vec3 surfaceToCamera = normalize(cameraPosition - surfacePostion.xyz);
    float cosAngle = max( dot(surfaceToCamera, reflectionVector), 0.0);
    float specular_coefficient = pow(cosAngle, shininess);
    vec3 out_specular_color = specular_color * specular_coefficient * specular_intensity;


	//attenuation
    float distanceToLight = length(light_position.xyz - surfacePostion.xyz);
    float attenuation = 1.0 / (1.0 + attenuationCoefficient * pow(distanceToLight, 2));

    // 1. Normalize the cone direction
    vec3 cone_direction_norm = normalize(cone_direction);

    // 2. Calculate the ray direction. We already calculated the surface to light direction.
    // 	  All what we need to do is to inverse this value
    vec3 ray_direction = -surface_to_light.xyz;

    // 3. Calculate the angle between light and surface using the dot product again.
    //    To simplify our understanding, we use the degrees
    float light_to_surface_angle = degrees(acos(dot(ray_direction, cone_direction_norm))) ;

    // 4. Last, we compare the angle with the current direction and
    //    reduce the attenuation to 0.0 if the light is outside the angle.
    float spotEffect  = 1.0;
	if(light_to_surface_angle > cone_angle){
  		attenuation = 0.0;
	} else {
    spotEffect = 1 - smoothstep(cone_angle - 1.3, cone_angle, light_to_surface_angle);

    // if(spotEffect == 0) {
    //   spotEffect = 100;
    // }
  }

	// Calculate the linear color
	vec3 linearColor = out_ambient_color  + spotEffect * attenuation * ( out_diffuse_color + out_specular_color);

	return linearColor;
}

vec3 getLight2() {
	// Spot light 2
    vec4 surfacePostion = modelMatrixBox * vec4(in_Position, 1.0);
	 vec3 normal = normalize(in_Normal);
    vec4 transformedNormal =  normalize(transpose(inverse(modelMatrixBox)) * vec4( normal, 1.0 ));

    vec4 surface_to_light2 =   normalize( light_position2 -  surfacePostion );

    // Diffuse color
    float diffuse_coefficient2 = max( dot(transformedNormal, surface_to_light2), 0.0);
    vec3 out_diffuse_color2 = specular_color  * diffuse_coefficient2 * diffuse_intensity2;

    // Ambient color
    vec3 out_ambient_color2 = vec3(ambient_color) * ambient_intensity2;

    // Specular color
    vec3 incidenceVector2 = -surface_to_light2.xyz;
    vec3 reflectionVector2 = reflect(incidenceVector2, transformedNormal.xyz);
    vec3 cameraPosition = vec3( -viewMatrixBox[3][0], -viewMatrixBox[3][1], -viewMatrixBox[3][2]);
    vec3 surfaceToCamera2 = normalize(cameraPosition - surfacePostion.xyz);
    float cosAngle2 = max( dot(surfaceToCamera2, reflectionVector2), 0.0);
    float specular_coefficient2 = pow(cosAngle2, shininess);
    vec3 out_specular_color2 = specular_color * specular_coefficient2 * specular_intensity2;


	//attenuation
    float distanceToLight2 = length(light_position2.xyz - surfacePostion.xyz);
    float attenuation2 = 1.0 / (1.0 + attenuationCoefficient2 * pow(distanceToLight2, 2));

    // 1. Normalize the cone direction
    vec3 cone_direction_norm2 = normalize(cone_direction2);

    // 2. Calculate the ray direction. We already calculated the surface to light direction.
    // 	  All what we need to do is to inverse this value
    vec3 ray_direction2 = -surface_to_light2.xyz;

    // 3. Calculate the angle between light and surface using the dot product again.
    //    To simplify our understanding, we use the degrees
    float light_to_surface_angle2 = degrees(acos(dot(ray_direction2, cone_direction_norm2))) ;

    // 4. Last, we compare the angle with the current direction and
    //    reduce the attenuation to 0.0 if the light is outside the angle.
    float spotEffect2  = 1.0;
   if(light_to_surface_angle2 > cone_angle2){
  	 attenuation2 = 0.0;
   } else {
    spotEffect2 = 1 - smoothstep(cone_angle2 - 2.3, cone_angle2, light_to_surface_angle2);

    // if(spotEffect == 0) {
    //   spotEffect = 100;
    // }
  }


  // sum iwth previous color
	return out_ambient_color2  + spotEffect2 * attenuation2 * ( out_diffuse_color2 + out_specular_color2);
	// vec3 linearColor =  out_ambient_color0  + attenuation0 * ( out_diffuse_color0 + out_specular_color0);

}

vec3 getLight0() {

	// second light source

    vec4 surfacePostion = modelMatrixBox * vec4(in_Position, 1.0);
	vec3 normal = normalize(in_Normal);

    vec4 surface_to_light0 =   normalize( light_position0 -  surfacePostion );
    vec4 transformedNormal =  normalize(transpose(inverse(modelMatrixBox)) * vec4( normal, 1.0 ));

    // Diffuse color
    float diffuse_coefficient0 = max( dot(transformedNormal, surface_to_light0), 0.0);
    vec3 out_diffuse_color0 = diffuse_color  * diffuse_coefficient0 * diffuse_intensity0;

    // Ambient color
    vec3 out_ambient_color0 = vec3(ambient_color) * ambient_intensity0;

    // Specular color
    vec3 incidenceVector0 = -surface_to_light0.xyz;
    vec3 cameraPosition = vec3( -viewMatrixBox[3][0], -viewMatrixBox[3][1], -viewMatrixBox[3][2]);
    vec3 surfaceToCamera = normalize(cameraPosition - surfacePostion.xyz);
    vec3 reflectionVector0 = reflect(incidenceVector0, transformedNormal.xyz);
    float cosAngle0 = max( dot(surfaceToCamera, reflectionVector0), 0.0);
    float specular_coefficient0 = pow(cosAngle0, shininess);
    vec3 out_specular_color0 = specular_color * specular_coefficient0 * specular_intensity0;


	//attenuation
    float distanceToLight0 = length(light_position0.xyz - surfacePostion.xyz);
    float attenuation0 = 1.0 / (1.0 + attenuationCoefficient * pow(distanceToLight0, 2));

	return out_ambient_color0  + attenuation0 * ( out_diffuse_color0 + out_specular_color0);

}

vec3 getLight3() {
	// Spot light 2
    vec4 surfacePostion = modelMatrixBox * vec4(in_Position, 1.0);
	 vec3 normal = normalize(in_Normal);
    vec4 transformedNormal =  normalize(transpose(inverse(modelMatrixBox)) * vec4( normal, 1.0 ));

    vec4 surface_to_light3 =   normalize( light_position3 -  surfacePostion );

    // Diffuse color
    float diffuse_coefficient3 = max( dot(transformedNormal, surface_to_light3), 0.0);
    vec3 out_diffuse_color3 = ambient_color  * diffuse_coefficient3 * diffuse_intensity3;

    // Ambient color
    vec3 out_ambient_color3 = vec3(ambient_color) * ambient_intensity3;

    // Specular color
    vec3 incidenceVector3 = -surface_to_light3.xyz;
    vec3 reflectionVector3 = reflect(incidenceVector3, transformedNormal.xyz);
    vec3 cameraPosition = vec3( -viewMatrixBox[3][0], -viewMatrixBox[3][1], -viewMatrixBox[3][2]);
    vec3 surfaceToCamera3 = normalize(cameraPosition - surfacePostion.xyz);
    float cosAngle3 = max( dot(surfaceToCamera3, reflectionVector3), 0.0);
    float specular_coefficient3 = pow(cosAngle3, shininess);
    vec3 out_specular_color3 = specular_color * specular_coefficient3 * specular_intensity3;


	//attenuation
    float distanceToLight3 = length(light_position3.xyz - surfacePostion.xyz);
    float attenuation3 = 1.0 / (1.0 + attenuationCoefficient3 * pow(distanceToLight3, 2));

    // 1. Normalize the cone direction
    vec3 cone_direction_norm3 = normalize(cone_direction3);

    // 2. Calculate the ray direction. We already calculated the surface to light direction.
    // 	  All what we need to do is to inverse this value
    vec3 ray_direction3 = -surface_to_light3.xyz;

    // 3. Calculate the angle between light and surface using the dot product again.
    //    To simplify our understanding, we use the degrees
    float light_to_surface_angle3 = degrees(acos(dot(ray_direction3, cone_direction_norm3))) ;

    // 4. Last, we compare the angle with the current direction and
    //    reduce the attenuation to 0.0 if the light is outside the angle.
    float spotEffect3  = 1.0;
   if(light_to_surface_angle3 > cone_angle3){
  	 attenuation3 = 0.0;
   } else {
    spotEffect3 = 1 - smoothstep(cone_angle3 - 15.15, cone_angle3, light_to_surface_angle3) + 0.003;

  }


  // sum iwth previous color
	return out_ambient_color3  + spotEffect3 * attenuation3 * ( out_diffuse_color3 + out_specular_color3);
}
void main(void)
{
	vec3 linearColor = getLight0();
	linearColor = linearColor + getLight2() + getLight1() + getLight3();



	// Gamma correction
	vec3 gamma = vec3(1.0/2.2);
	vec3 finalColor = pow(linearColor, gamma);

	// Pass the color
	pass_Color =  finalColor;

	// Passes the projected position to the fragment shader / rasterization process.
    gl_Position = projectionMatrixBox * viewMatrixBox * modelMatrixBox * vec4(in_Position, 1.0);

}
