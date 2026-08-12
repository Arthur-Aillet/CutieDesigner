#include "MouseInputNode.hpp"
#include "NodeDelegateModel.hpp"
#include "Vec2Data.hpp"

#include <QQmlContext>

static CutieWindow *getCutieWindow(QApplication *application) {
  for (auto w : application->allWindows()) {
    CutieWindow *cutieWindow = qobject_cast<CutieWindow *>(w);
    if (cutieWindow != nullptr)
      return cutieWindow;
  }
  return nullptr;
}

MouseInputNode::MouseInputNode(QQmlEngine *engine)
    : NodeDelegateModel(engine), _posData(std::make_shared<Vec2Data>(_pos)) {
  auto app = qvariant_cast<QApplication *>(engine->rootContext()->contextProperty("app"));

  _window = getCutieWindow(app);
  if (_window == nullptr)
    return;

  _pos = QVector2D(QCursor::pos());
  QObject::connect(_window, SIGNAL(mouseMoveEventForward(QMouseEvent *)), this,
                   SLOT(mouseMoveEvent(QMouseEvent *)));
}

unsigned int MouseInputNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::Out:
    return 1;
  default:
    return 0;
  }
}

QString MouseInputNode::portCaption(PortSide portSide, PortIndex portIndex) const { return "pos"; }

NodeDataType MouseInputNode::dataType(PortSide _portSide, PortIndex _portIndex) const {
  return Vec2Data().type();
}

std::shared_ptr<NodeData> MouseInputNode::outData(PortIndex portIndex) { return _posData; }

void MouseInputNode::mouseMoveEvent(QMouseEvent *event) {
  if (event->pos().x() != _pos.x()) {
    _pos.setX(event->pos().x());
    emit dataUpdated(0);
  }
  if (event->pos().y() != _pos.y()) {
    _pos.setY(event->pos().y());
    emit dataUpdated(0);
  }
}