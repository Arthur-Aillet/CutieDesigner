FetchContent_Declare(NodeEditor
    GIT_REPOSITORY  https://github.com/Arthur-Aillet/NodeEditor-QML.git
    GIT_TAG         66957999d27bc74c2f732f87d71573812d07d1ed
)

FetchContent_GetProperties(NodeEditor)
if(NOT NodeEditor_POPULATED)
 FetchContent_MakeAvailable(NodeEditor)
endif()
