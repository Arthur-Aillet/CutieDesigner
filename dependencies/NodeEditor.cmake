FetchContent_Declare(NodeEditor
    GIT_REPOSITORY  https://github.com/Arthur-Aillet/NodeEditor-QML.git
    GIT_TAG         ebf16b33e700d932883526d3069a36b176d311d5
)

FetchContent_GetProperties(NodeEditor)
if(NOT NodeEditor_POPULATED)
 FetchContent_MakeAvailable(NodeEditor)
endif()
