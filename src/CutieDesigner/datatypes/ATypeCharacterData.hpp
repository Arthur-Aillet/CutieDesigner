#pragma once

#include "ATypeCharacterNodeModel.hpp"

#include <NodeEditor/NodeData>

class ATypeCharacterData : public NodeEditor::NodeData {
  public:
  ATypeCharacterData() {}
  ATypeCharacterData(ATypeCharacterNodeModel *character) : _character(character) {}

  NodeEditor::NodeDataType type() const override {
    return NodeEditor::NodeDataType("atypeCharacter", "Atype Character");
  }

  ATypeCharacterNodeModel *getCharacter() { return _character; }

  protected:
  ATypeCharacterNodeModel *_character;
};
