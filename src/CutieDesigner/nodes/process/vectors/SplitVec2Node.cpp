#include "SplitVec2Node.hpp"
#include "DecimalData.hpp"
#include "Vec2Data.hpp"
#include <memory>
#include <qcolor.h>
#include <qvectornd.h>

SplitVec2Node::SplitVec2Node(QQmlEngine *engine)
    : NodeDelegateModel(engine), _xData(std::make_shared<DecimalData>(_x)),
      _yData(std::make_shared<DecimalData>(_y)) {}

unsigned int SplitVec2Node::nPorts(PortSide portSide) const {
  switch (portSide) {
  case PortSide::In:
    return 1;
  default:
    return 2;
  }
}

QString SplitVec2Node::portCaption(PortSide portSide, PortIndex portIndex) const {
  switch (portSide) {
  case PortSide::Out:
    switch (portIndex) {
    case 0:
      return "x";
    default:
      return "y";
    }
  default:
    return "in";
  }
}

NodeDataType SplitVec2Node::dataType(PortSide portSide, PortIndex _portIndex) const {
  switch (portSide) {
  case PortSide::In:
    return Vec2Data().type();
  default:
    return DecimalData().type();
  }
}

std::shared_ptr<NodeData> SplitVec2Node::outData(PortIndex portIndex) {
  switch (portIndex) {
  case 0:
    return _xData;
  default:
    return _yData;
  }
}

void SplitVec2Node::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) {
  if (!data) {
    _x = 0.0;
    _y = 0.0;
    emit dataInvalidated(0);
    emit dataInvalidated(1);
  } else {
    const auto &vec = data->repr<QVector2D>();
    _x = vec.x();
    _y = vec.y();
    emit dataUpdated(0);
    emit dataUpdated(1);
  }
};
