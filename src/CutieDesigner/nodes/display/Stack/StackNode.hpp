#pragma once

#include "SurfaceData.hpp"

#include <QAbstractItemModel>

#include <NodeEditor/NodeModel>

class SurfaceList : public QAbstractListModel {
  Q_OBJECT
  QML_ELEMENT

  public:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int portsCount() const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  void setPort(std::shared_ptr<SurfaceData> surface, int portIndex);
  void addEmptyPort();
  void removeLastPort();

  protected:
  std::vector<std::weak_ptr<SurfaceData>> _surfaces = {{}};
};

class StackNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(SurfaceList *surfaceList READ getSurfaceList CONSTANT)

  StackNode(QQmlEngine *engine);
  ~StackNode() = default;

  public:
  bool captionVisible() const override { return true; }
  QString name() const override { return "Stack"; }

  QJsonObject save() const override;
  void load(QJsonObject const &) override;

  QString portCaption(NodeEditor::PortSide portSide,
                      NodeEditor::PortIndex portIndex) const override;
  bool portCaptionVisible(NodeEditor::PortSide _portSide,
                          NodeEditor::PortIndex _portIndex) const override {
    return true;
  }

  QQmlComponent embeddedComponent(QQmlEngine *engine) override {
    return QQmlComponent(engine, "CutieDesigner.Nodes.Display", "StackControl");
  }

  QVariantMap componentInitialProperties() override {
    return QVariantMap{{"node", QVariant::fromValue(this)}};
  }

  unsigned int nPorts(NodeEditor::PortSide portSide) const override;
  NodeEditor::NodeDataType dataType(NodeEditor::PortSide portSide,
                                    NodeEditor::PortIndex portIndex) const override;
  std::shared_ptr<NodeEditor::NodeData> outData(NodeEditor::PortIndex port) override;
  void setInData(std::shared_ptr<NodeEditor::NodeData> data,
                 NodeEditor::PortIndex portIndex) override;

  Q_INVOKABLE void addEmptyPort();
  Q_INVOKABLE void removeLastPort();

  SurfaceList *getSurfaceList() { return &_surfaceList; }

  private:
  SurfaceList _surfaceList;
  std::shared_ptr<SurfaceData> _content;
};
