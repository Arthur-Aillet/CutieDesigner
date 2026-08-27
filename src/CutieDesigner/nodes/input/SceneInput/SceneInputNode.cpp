#include "SceneInputNode.hpp"
#include "CutieWindow.hpp"

using namespace NodeEditor;

SceneInputNode::SceneInputNode(QQmlEngine *engine)
    : NodeModel(engine), _posData(std::make_shared<Vec2Data>(_pos)),
      _sizeData(std::make_shared<Vec2Data>(_size)) {
  auto window = CutieWindow::getCutieWindow(engine);
  if (window == nullptr)
    return;

  _frame = qvariant_cast<QQuickItem *>(window->property("sceneContent"));

  _pos = QVector2D(_frame->position());
  _size = QVector2D(_frame->width(), _frame->height());

  QObject::connect(_frame, SIGNAL(xChanged()), this, SLOT(posChanged()));
  QObject::connect(_frame, SIGNAL(yChanged()), this, SLOT(posChanged()));
  QObject::connect(_frame, SIGNAL(widthChanged()), this, SLOT(sizeChanged()));
  QObject::connect(_frame, SIGNAL(heightChanged()), this, SLOT(sizeChanged()));
}

unsigned int SceneInputNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::Out:
    return 2;
  default:
    return 0;
  }
}

QString SceneInputNode::portCaption(PortSide portSide, PortIndex portIndex) const {
  switch (portIndex) {
  case 0:
    return "pos";
  default:
    return "size";
  }
}

NodeDataType SceneInputNode::dataType(PortSide _portSide, PortIndex _portIndex) const {
  return Vec2Data().type();
}

std::shared_ptr<NodeData> SceneInputNode::outData(PortIndex portIndex) {
  switch (portIndex) {
  case 0:
    return _posData;
  default:
    return _sizeData;
  }
}

void SceneInputNode::posChanged() {
  if (QVector2D(_frame->position()) != _pos) {
    _pos = QVector2D(_frame->position());
    emit dataUpdated(0);
  }
}

void SceneInputNode::sizeChanged() {
  if (QVector2D(_frame->width(), _frame->height()) != _size) {
    _size = QVector2D(_frame->width(), _frame->height());
    emit dataUpdated(1);
  }
}
