#pragma once

#include "TextData.hpp"
#include "TextTyperEventList.hpp"

#include <NodeEditor/NodeModel>

#include <QTimer>
#include <qnamespace.h>
#include <qqmlengine.h>
#include <qtmetamacros.h>
#include <qvariant.h>

class TextTyperNode : public NodeEditor::NodeModel {
  Q_OBJECT
  QML_ELEMENT
  QML_UNCREATABLE("NodeModel")

  public:
  Q_PROPERTY(bool play READ getPlay WRITE setPlay NOTIFY playChanged)
  Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)
  Q_PROPERTY(TextTyperEventList *model READ getModel CONSTANT)

  TextTyperNode(QQmlEngine *engine);
  ~TextTyperNode() = default;

  bool captionVisible() const override { return true; }
  QString name() const override { return QStringLiteral("Text Typer"); }

  QJsonObject save() const override;
  void load(QJsonObject const &) override;

  QString portCaption(NodeEditor::PortSide type, NodeEditor::PortIndex index) const override;
  bool portCaptionVisible(NodeEditor::PortSide, NodeEditor::PortIndex) const override {
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

  TextTyperEventList *getModel();
  bool getPlay();
  void setPlay(bool playState);
  QString getText();
  void setText(QString newText);

  void processEvent();

  signals:
  void textChanged();
  void playChanged();

  protected slots:
  void processNextEvent();
  void processWait();
  void processErase();
  void processReplace();
  void processInsert();

  private:
  int _currentEventIdx = 0;
  TextTypeEvent _currentEvent;
  TextTyperEventList _eventList;
  QTimer _timer;
  bool _playing = false;
  QString _text = "...";
  std::shared_ptr<TextData> _content;
};
