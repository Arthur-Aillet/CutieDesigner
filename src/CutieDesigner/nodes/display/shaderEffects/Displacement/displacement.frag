#version 440
layout(location = 0) in vec2 texCoord;
layout(location = 1) in vec2 fragCoord;
layout(location = 0) out vec4 fragColor;

layout(std140, binding = 0) uniform buf {
  mat4 qt_Matrix;
  float qt_Opacity;
  vec4 imageRect;
  vec4 mapRect;
  float minDisp;
  float maxDisp;
};

layout(binding = 1) uniform sampler2D image;
layout(binding = 2) uniform sampler2D map;

// chromatic dispersion samples
#define SAMPLES 32

vec2 normz(vec2 x) {
	return x == vec2(0) ? vec2(0) : normalize(x);
}

/*
	This function supplies a weight vector for each color channel.
	It's analogous to (but not a physically accurate model of)
	the response curves for each of the 3 cone types in the human eye.
	The three functions for red, green, and blue have the same integral
    over [0, 1], which is 1/3.
    Here are some other potential terms for the green weight that
	integrate to 1/3:
        2.0*(1-x)*x
        10.0*((1-x)*x)^2
        46.667*((1-i)*i)^3
        210.0*((1-x)*x)^4
        924.0*((1-x)*x)^5
    By the way, this series of coefficients is OEIS A004731 divided by 3,
    which is a pretty interesting series: https://oeis.org/A002457
*/
vec3 sampleWeights(float i) {
	return vec3(i * i, 46.6666*pow((1.0-i)*i,3.0), (1.0 - i) * (1.0 - i));
}

float lerp(float fac) {
  return minDisp + (maxDisp - minDisp) * fac;
}

vec3 sampleDisp(vec2 uv, vec2 dispNorm) {
    vec3 col = vec3(0);
    const float SD = 1.0 / float(SAMPLES);
    float wl = 0.0;
    vec3 denom = vec3(0);
    for(int i = 0; i < SAMPLES; i++) {
        vec3 sw = vec3(wl);
        // vec3 sw = sampleWeights(wl);
        denom += sw;
        vec2 displacement = vec2(lerp(dispNorm.x * wl) / imageRect.z, lerp(dispNorm.y * wl) / imageRect.w);
        col += sw * texture(image, uv + displacement).xyz;
        wl  += SD;
    }

    // For a large enough number of samples,
    // the return below is equivalent to 3.0 * col * SD;
    return col / denom;
}

void main() {
  vec2 mappedCoord = fragCoord + (imageRect.xy - mapRect.xy);
  vec4 mapText = texture(map, mappedCoord / imageRect.zw);

  fragColor.rgb = sampleDisp(texCoord, mapText.rg);
  fragColor.a = 1.0;
  fragColor *= qt_Opacity;
}

