#include "DitheringNode.hpp"
#include "DecimalData.hpp"
#include "SurfaceData.hpp"

#include <NodeEditor/NodeModel>

using namespace NodeEditor;

DitheringNode::DitheringNode(QQmlEngine *engine) : NodeModel(engine) {
  auto comp = std::make_unique<QQmlComponent>(engine, "CutieDesigner.Nodes.Display", "Dithering");
  _content = std::make_shared<SurfaceData>(std::move(comp),
                                           QVariantMap{{"node", QVariant::fromValue(this)}});
}

QJsonObject DitheringNode::save() const { return QJsonObject({{"mode", _mode}}); }

void DitheringNode::load(QJsonObject const &json) {
  QJsonValue value = json["mode"];

  if (!value.isUndefined()) {
    _mode = value.toInt();
  }
}

unsigned int DitheringNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::In:
    return 2;
  default:
    return 1;
  }
}

NodeDataType DitheringNode::dataType(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::In:
    if (portIndex == 0)
      return SurfaceData().type();
    else
      return DecimalData().type();
  default:
    return SurfaceData().type();
  }
}

std::shared_ptr<NodeData> DitheringNode::outData(PortIndex _portIndex) {
  if (_surface.expired())
    return nullptr;
  return _content;
}

void DitheringNode::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) {
  if (data == nullptr) {
    if (portIndex == 0) {
      _surface.reset();
      emit surfaceChanged();
      emit dataInvalidated(0);
    } else {
      _resolution = 1;
      emit resolutionChanged();
    }
  } else {
    if (portIndex == 0) {
      _surface = std::dynamic_pointer_cast<SurfaceData>(data);
      emit surfaceChanged();
      emit dataUpdated(0);
    } else {
      _resolution = int(data->repr<double>());
      emit resolutionChanged();
    }
  }
}

QString DitheringNode::portCaption(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::In:
    switch (portIndex) {
    case 0:
      return QString("in");
    default:
      return QString("resolution");
    }
  default:
    return QString("out");
  }
}
