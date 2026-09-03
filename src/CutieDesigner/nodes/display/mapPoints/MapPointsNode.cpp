#include "MapPointsNode.hpp"
#include "PointsData.hpp"
#include "SurfaceData.hpp"

using namespace NodeEditor;

MapPointsNode::MapPointsNode(QQmlEngine *engine) : NodeModel(engine) {
  auto comp = std::make_unique<QQmlComponent>(engine, "CutieDesigner.Nodes.Display", "MapPoints");
  QVariantMap map;
  map["node"] = QVariant::fromValue(this);
  _content = std::make_shared<SurfaceData>(std::move(comp), map);
  _defaultGradient = QLinearGradient();
  _defaultGradient.setColorAt(0, "red");
}

unsigned int MapPointsNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::In:
    return 1;
  default:
    return 1;
  };
}

NodeDataType MapPointsNode::dataType(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::In:
    switch (portIndex) {
    case 0:
      return PointsData().type();
    }
  default:
    return SurfaceData().type();
  }
}

std::shared_ptr<NodeData> MapPointsNode::outData(PortIndex _portIndex) { return _content; }

void MapPointsNode::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) {
  if (!data) {
    switch (portIndex) {
    case 0:
      _points.reset();
      emit pointsChanged();
      break;
    }
  } else {
    switch (portIndex) {
    case 0:
      _points = data;
      emit pointsChanged();
      break;
    }
  }
}

QString MapPointsNode::portCaption(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::In:
    switch (portIndex) {
    case 0:
      return "points";
    }
  default:
    return "out";
  }
}

QList<QVector2D> MapPointsNode::points() {
  if (_points.expired()) {
    return QList<QVector2D>();
  }
  return _points.lock()->repr<QList<QVector2D>>();
}
