#include "NoiseNode.hpp"
#include "DecimalData.hpp"
#include "SurfaceData.hpp"

using namespace NodeEditor;

NoiseNode::NoiseNode(QQmlEngine *engine) : NodeModel(engine) {
  _content = std::make_shared<SurfaceData>(
      std::make_unique<QQmlComponent>(engine, "CutieDesigner.Nodes.Display", "Noise"),
      QVariantMap{{"node", QVariant::fromValue(this)}});
}

QJsonObject NoiseNode::save() const { return QJsonObject({{"mode", _mode}}); }

void NoiseNode::load(QJsonObject const &json) {
  QJsonValue valueMode = json["mode"];

  if (!valueMode.isUndefined()) {
    _mode = valueMode.toInt();
  }
}

unsigned int NoiseNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::In:
    return 2;
  default:
    return 1;
  }
}

NodeDataType NoiseNode::dataType(PortSide portSide, PortIndex portIndex) const {
  if (portSide == PortSide::In) {
    switch (portIndex) {
    case (0):
    case (1):
      return DecimalData().type();
    default:
      return DecimalData().type();
    }
  } else {
    return SurfaceData().type();
  }
}

std::shared_ptr<NodeData> NoiseNode::outData(PortIndex _portIndex) { return _content; }

void NoiseNode::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) {
  if (data == nullptr) {
    if (portIndex == 0) {
      _scale = 1.0;
      emit scaleChanged();
    } else {
      _time = 1.0;
      emit timeChanged();
    }
  } else {
    if (portIndex == 0) {
      _scale = data->repr<double>();
      emit scaleChanged();
    } else {
      _time = data->repr<double>();
      emit timeChanged();
    }
  }
}

QString NoiseNode::portCaption(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::In:
    if (portIndex == 0) {
      return "scale";
    } else {
      return "time";
    }
  default:
    return "out";
  }
}

QQmlComponent NoiseNode::embeddedComponent(QQmlEngine *engine) {
  return QQmlComponent(engine, "CutieDesigner.Nodes.Display", "NoiseControl");
};
QVariantMap NoiseNode::componentInitialProperties() {
  return {{"node", QVariant::fromValue(this)}};
};
