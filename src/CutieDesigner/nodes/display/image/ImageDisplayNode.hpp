#pragma once

#include "SurfaceData.hpp"
#include <NodeEditor/NodeModel>

#include <QUrl>
#include <optional>

class ImageDisplayNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
  Q_PROPERTY(QString sourceFileName READ sourceFileName NOTIFY sourceChanged)
  Q_PROPERTY(QVector2D pos MEMBER _pos NOTIFY posChanged)
  Q_PROPERTY(QVector2D size MEMBER _size NOTIFY sizeChanged)
  Q_PROPERTY(bool sizeSet MEMBER _sizeSet NOTIFY sizeChanged)
  Q_PROPERTY(bool tile READ tile WRITE setTile NOTIFY tileChanged)

  ImageDisplayNode(QQmlEngine *engine);
  ~ImageDisplayNode() = default;

  bool captionVisible() const override { return true; }
  QString name() const override { return "Image"; }

  QJsonObject save() const override;
  void load(QJsonObject const &p) override;

  QString portCaption(NodeEditor::PortSide portSide,
                      NodeEditor::PortIndex portIndex) const override;
  bool portCaptionVisible(NodeEditor::PortSide _portSide,
                          NodeEditor::PortIndex _portIndex) const override {
    return true;
  }

  unsigned int nPorts(NodeEditor::PortSide portSide) const override;
  NodeEditor::NodeDataType dataType(NodeEditor::PortSide portSide,
                                    NodeEditor::PortIndex portIndex) const override;
  std::shared_ptr<NodeEditor::NodeData> outData(NodeEditor::PortIndex port) override;
  void setInData(std::shared_ptr<NodeEditor::NodeData> data,
                 NodeEditor::PortIndex portIndex) override;

  QQmlComponent embeddedComponent(QQmlEngine *engine) override;
  QVariantMap componentInitialProperties() override;

  QUrl source();
  void setSource(QUrl url);
  QString sourceFileName();

  bool tile();
  void setTile(bool tile);

  signals:
  void sourceChanged();
  void posChanged();
  void sizeChanged();
  void tileChanged();

  private:
  bool _tile = true;
  bool _sizeSet = false;
  QVector2D _pos = QVector2D(0, 0);
  QVector2D _size = QVector2D(1, 1);
  int _fillMode = 0;
  std::optional<QUrl> _sourceUrl = std::nullopt;
  std::shared_ptr<SurfaceData> _content = nullptr;
};
