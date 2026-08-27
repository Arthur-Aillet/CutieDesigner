#include "DecimalData.hpp"

#include <NodeEditor/NodeData>

#include <QColor>
#include <QGradient>
#include <QVector2D>

DecimalDataType::DecimalDataType()
    : NodeDataType("decimal", "Decimal", {"decimal", "text", "col", "gradient-01", "vec2-01"}) {}

DecimalData::DecimalData(const double &v) {
  registerConvert([&v]() { return v; });
  registerConvert([&v]() { return QString::number(v, 'f', 2); });
  registerConvert([&v]() {
    return QColor::fromRgbF(std::clamp(v, 0.0, 1.0), std::clamp(v, 0.0, 1.0),
                            std::clamp(v, 0.0, 1.0), 1);
  });
  registerConvert([&v]() {
    QColor col = QColor::fromRgbF(std::clamp(v, 0.0, 1.0), std::clamp(v, 0.0, 1.0),
                                  std::clamp(v, 0.0, 1.0), 1);
    QGradient g;
    g.setColorAt(0, col);
    return g;
  });
  registerConvert([&v]() { return QVector2D(v, v); });
}
