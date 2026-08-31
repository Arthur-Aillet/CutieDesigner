FetchContent_Declare(NodeEditor
    GIT_REPOSITORY  https://github.com/Arthur-Aillet/NodeEditor-QML.git
    GIT_TAG         09efe7d7ae1295e15d39ac0f953a26805eb128a6
)

FetchContent_GetProperties(NodeEditor)
if(NOT NodeEditor_POPULATED)
 FetchContent_MakeAvailable(NodeEditor)
endif()
