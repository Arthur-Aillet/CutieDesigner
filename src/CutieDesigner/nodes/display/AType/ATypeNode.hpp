#pragma once

#include "ATypeCharacterNodeModel.hpp"
#include "SurfaceData.hpp"

#include <QQmlComponent>
#include <QtCore/QObject>

#include <memory>

#include <NodeEditor/NodeModel>

class ATypeNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  Q_PROPERTY(QString text READ getText NOTIFY textChanged)
  Q_PROPERTY(ATypeCharacterNodeModel *character MEMBER _charModel NOTIFY charChanged)

  public:
  ATypeNode(QQmlEngine *engine);
  ~ATypeNode() = default;

  QString caption() const override { return QStringLiteral("AType font display"); }
  bool captionVisible() const override { return true; }
  QString name() const override { return QStringLiteral("AType"); }

  unsigned int nPorts(NodeEditor::PortSide portSide) const override;
  NodeEditor::NodeDataType dataType(NodeEditor::PortSide portSide,
                                    NodeEditor::PortIndex portIndex) const override;
  std::shared_ptr<NodeEditor::NodeData> outData(NodeEditor::PortIndex port) override;
  void setInData(std::shared_ptr<NodeEditor::NodeData> data,
                 NodeEditor::PortIndex portIndex) override;
  std::shared_ptr<SurfaceData> createATypeSurfaceData(QQmlEngine *engine);

  QString getText() {
    if (_text.expired()) {
      return "";
    }
    return _text.lock()->repr<QString>();
  }

  signals:
  void valueUpdated(QQmlComponent *component);
  void textChanged();
  void charChanged();

  private:
  std::weak_ptr<NodeEditor::NodeData> _text;
  ATypeCharacterNodeModel *_charModel = nullptr;
  std::shared_ptr<SurfaceData> _content;
};
