qt_add_qml_module(fileManager
  STATIC
  URI CutieDesigner.App.FileManager

  SOURCES
  FileManager.cpp
  FileManager.hpp
)

target_link_directories(fileManager
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(fileManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(fileManager PRIVATE
  Qt6::Core
  Qt6::Quick
  Qt6::Qml
  NodeEditor
)
