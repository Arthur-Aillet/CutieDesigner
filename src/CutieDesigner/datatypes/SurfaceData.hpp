#pragma once

#include <NodeEditor/NodeData>

#include <QQmlComponent>
#include <QQuickItem>

#include <memory>

class SurfaceData : public NodeEditor::NodeData {
  Q_OBJECT
  QML_IMPLEMENTS_INTERFACES(NodeEditor::NodeData)
  QML_ELEMENT
  QML_UNCREATABLE("")

  public:
  SurfaceData() {}
  SurfaceData(std::unique_ptr<QQmlComponent> &&object, QVariantMap initialProps = {});

  NodeEditor::NodeDataType type() const override {
    return NodeEditor::NodeDataType("object", "2D Surface");
  }

  const std::unique_ptr<QQmlComponent> &component() { return _component; };
  const QVariantMap &initialProps() { return _initialProps; };

  protected:
  std::unique_ptr<QQmlComponent> _component;
  QVariantMap _initialProps;

  signals:
  void componentLoaded(QQuickItem *object);
  void componentDestroyed(QObject *object);
};
