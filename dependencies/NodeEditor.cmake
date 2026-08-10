FetchContent_Declare(NodeEditor
    GIT_REPOSITORY  https://github.com/Arthur-Aillet/NodeEditor-QML.git
    GIT_TAG         ec72e100c6c1f5e87e690184d8658dcc4a0613b7
)

FetchContent_GetProperties(NodeEditor)
if(NOT NodeEditor_POPULATED)
 FetchContent_MakeAvailable(NodeEditor)
endif()
