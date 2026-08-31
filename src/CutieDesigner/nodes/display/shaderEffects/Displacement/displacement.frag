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

float lerp(float min, float max, float fac) {
  return min + (max - min) * fac;
}

void main() {
  vec2 mappedCoord = fragCoord + (imageRect.xy - mapRect.xy);

  bool inside = mappedCoord.x < mapRect.z && mappedCoord.y < mapRect.w;

  vec4 mapText = texture(map, mappedCoord / imageRect.zw);
  vec2 displacement = vec2(lerp(minDisp, maxDisp, mapText.r) / imageRect.w, lerp(minDisp, maxDisp, mapText.g) / imageRect.z);
  vec4 colorSource = texture(image, texCoord + displacement);

  fragColor = colorSource * qt_Opacity;
}
