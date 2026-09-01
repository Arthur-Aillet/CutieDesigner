#include "ColorAdjustNode.hpp"
#include "DecimalData.hpp"
#include "SurfaceData.hpp"

#include <NodeEditor/NodeModel>

using namespace NodeEditor;

ColorAdjustNode::ColorAdjustNode(QQmlEngine *engine) : NodeModel(engine) {
  auto comp = std::make_unique<QQmlComponent>(engine, "CutieDesigner.Nodes.Display", "ColorAdjust");
  _content = std::make_shared<SurfaceData>(std::move(comp),
                                           QVariantMap{{"node", QVariant::fromValue(this)}});
}

unsigned int ColorAdjustNode::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::In:
    return 4;
  default:
    return 1;
  }
}

NodeDataType ColorAdjustNode::dataType(PortSide portSide, PortIndex portIndex) const {
  if (portSide == PortSide::In) {
    if (portIndex >= 1)
      return DecimalData().type();
    return SurfaceData().type();
  } else {
    return SurfaceData().type();
  }
}

std::shared_ptr<NodeData> ColorAdjustNode::outData(PortIndex _portIndex) {
  if (_source.expired())
    return nullptr;
  return _content;
}

void ColorAdjustNode::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) {
  if (data == nullptr) {
    switch (portIndex) {
    case 0:
      _source.reset();
      emit sourceChanged();
      emit dataInvalidated(0);
      return;
    case 1:
      _brightness = 0.0;
      emit brightnessChanged();
      return;
    case 2:
      _contrast = 1.0;
      emit contrastChanged();
      return;
    case 3:
      _saturation = 1.0;
      emit saturationChanged();
      return;
    }
  } else {
    switch (portIndex) {
    case 0:
      _source = std::dynamic_pointer_cast<SurfaceData>(data);
      emit sourceChanged();
      emit dataUpdated(0);
      return;
    case 1:
      _brightness = data->repr<double>();
      emit brightnessChanged();
      return;
    case 2:
      _contrast = data->repr<double>();
      emit contrastChanged();
      return;
    case 3:
      _saturation = data->repr<double>();
      emit saturationChanged();
      return;
    }
  }
}

QString ColorAdjustNode::portCaption(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::In:
    switch (portIndex) {
    case 0:
      return "source";
    case 1:
      return "brigthness";
    case 2:
      return "contrast";
    case 3:
      return "saturation";
    }
  default:
    return "out";
  }
}
