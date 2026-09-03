set(ONNX_DIR "~/dev/onnxruntime-linux-x64-1.20.1")

find_package(OpenCV 4.0.0 REQUIRED)

qt_add_qml_module(display
  URI CutieDesigner.Nodes.Display
  SHARED
  QML_FILES
  AType/Ukrug/Ukrug.qml
  AType/Ukrug/UkrugShader.qml
  AType/Ukrug/UkrugControl.qml
  AType/Ukrug/UkrugCharacter.qml
  AType/AType.qml
  Dimension/Dimension.qml
  fill/FillSurface.qml
  shaderEffects/Blend/Blend.qml
  shaderEffects/Blend/BlendControl.qml
  shaderEffects/Blur/Blur.qml
  shaderEffects/ColorAdjust/ColorAdjust.qml
  shaderEffects/Mask/Mask.qml
  shaderEffects/Mask/MaskControl.qml
  shaderEffects/Displacement/Displacement.qml
  shaderEffects/Dithering/Dithering.qml
  shaderEffects/Dithering/DitheringControl.qml
  camera/CameraOutput.qml
  camera/CameraHandler.qml
  image/ImageDisplay.qml
  image/ImageDisplayControl.qml
  noise/Noise.qml
  noise/NoiseControl.qml
  video/VideoDisplay.qml
  video/VideoDisplayControl.qml
  Stack/Stack.qml
  Stack/StackControl.qml
  mapPoints/MapPoints.qml

  SOURCES
  ${QT_AVPLAYER_SOURCES}
  AType/Ukrug/UkrugNode.hpp
  AType/Ukrug/UkrugNode.cpp
  AType/Ukrug/UkrugPointsList.hpp
  AType/Ukrug/UkrugPointsList.cpp
  AType/ATypeCharacterNodeModel.hpp
  AType/ATypeCharacterNodeModel.cpp
  AType/ATypeNode.hpp
  AType/ATypeNode.cpp
  Dimension/DimensionNode.hpp
  Dimension/DimensionNode.cpp
  fill/FillNode.hpp
  fill/FillNode.cpp
  Stack/StackNode.cpp
  Stack/StackNode.cpp
  surface/SurfaceDisplayNode.hpp
  surface/SurfaceDisplayNode.cpp
  surface/SurfaceLoader.hpp
  surface/SurfaceLoader.cpp
  shaderEffects/Blend/BlendNode.cpp
  shaderEffects/Blend/BlendNode.hpp
  shaderEffects/Blur/BlurNode.cpp
  shaderEffects/Blur/BlurNode.hpp
  shaderEffects/ColorAdjust/ColorAdjustNode.cpp
  shaderEffects/ColorAdjust/ColorAdjustNode.hpp
  shaderEffects/Mask/MaskNode.cpp
  shaderEffects/Mask/MaskNode.hpp
  shaderEffects/Displacement/DisplacementNode.cpp
  shaderEffects/Displacement/DisplacementNode.hpp
  shaderEffects/Dithering/DitheringNode.cpp
  shaderEffects/Dithering/DitheringNode.hpp
  camera/CameraNode.hpp
  camera/CameraNode.cpp
  image/ImageDisplayNode.hpp
  image/ImageDisplayNode.cpp
  noise/NoiseNode.cpp
  noise/NoiseNode.hpp
  video/VideoDisplayNode.hpp
  video/VideoDisplayNode.cpp
  opencv/OpenCVNode.cpp
  opencv/OpenCVNode.hpp
  mapPoints/MapPointsNode.cpp
  mapPoints/MapPointsNode.hpp

  DEPENDENCIES QtQuick QtQuick.Layout NodeEditor CutieUiModule CutieDesigner.Datatypes
  RESOURCES
  AType/Ukrug/UkrugPointsData.json
)

  qt6_add_shaders(display "display_shaders"
  PREFIX
  "/qt/qml/CutieDesigner/Nodes/Display"
  FILES
  AType/Ukrug/ukrug.vert
  AType/Ukrug/ukrug.frag
  shaderEffects/Blend/blend.vert
  shaderEffects/Blend/blend.frag
  shaderEffects/ColorAdjust/colorAdjust.vert
  shaderEffects/ColorAdjust/colorAdjust.frag
  shaderEffects/Mask/mask.vert
  shaderEffects/Mask/mask.frag
  shaderEffects/Displacement/displacement.vert
  shaderEffects/Displacement/displacement.frag
  shaderEffects/Dithering/dithering.vert
  shaderEffects/Dithering/dithering.frag
  noise/noise.vert
  noise/noise.frag
)

target_link_directories(display
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(display
  PUBLIC
  Dimension
  AType
  AType/Ukrug
  surface
  fill
  Stack
  shaderEffects
  shaderEffects/Blend
  shaderEffects/Blur
  shaderEffects/ColorAdjust
  shaderEffects/Mask
  shaderEffects/Displacement
  shaderEffects/Dithering
  camera
  image
  video
  noise
  opencv
  mapPoints
  ${ONNX_DIR}/include
  ${QT_AVPLAYER_DIR}/..
  ${Qt6MultimediaQuick_PRIVATE_INCLUDE_DIRS}
  ${Qt6Multimedia_PRIVATE_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

target_compile_definitions(display PRIVATE QT_AVPLAYER_MULTIMEDIA)

target_link_libraries(display PUBLIC
  Qt6::Core
  Qt6::Gui
  Qt6::Quick
  Qt6::QuickWidgets
  Qt6::Qml
  Qt6::Multimedia
  Qt6::MultimediaQuickPrivate
  Qt6::OpenGL
  NodeEditor
  CutieUiModule
  vivid
  datatypes
  ${QT_AVPLAYER_LIBS}
  ${ONNX_DIR}/lib/libonnxruntime.so
  PRIVATE
  ${OpenCV_LIBS}
)
