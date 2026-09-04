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
    return 2;
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
    case 1:
      return SurfaceData().type();
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
    case 1:
      _surface.reset();
      emit surfaceChanged();
      return;
    }
  } else {
    switch (portIndex) {
    case 0:
      _points = data;
      emit pointsChanged();
      break;
    case 1:
      _surface = std::dynamic_pointer_cast<SurfaceData>(data);
      emit surfaceChanged();
      return;
    }
  }
}

QString MapPointsNode::portCaption(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::In:
    switch (portIndex) {
    case 0:
      return "points";
    case 1:
      return "in";
    }
  default:
    return "out";
  }
}

PointsData::PointCollection MapPointsNode::points() {
  if (_points.expired()) {
    return PointsData::PointCollection();
  }
  return _points.lock()->repr<PointsData::PointCollection>();
}
