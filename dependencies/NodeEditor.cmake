FetchContent_Declare(NodeEditor
    GIT_REPOSITORY  https://github.com/Arthur-Aillet/NodeEditor-QML.git
    GIT_TAG         da7d6b33e60acb4f523d85c7289154870e310d67
)

FetchContent_GetProperties(NodeEditor)
if(NOT NodeEditor_POPULATED)
 FetchContent_MakeAvailable(NodeEditor)
endif()
