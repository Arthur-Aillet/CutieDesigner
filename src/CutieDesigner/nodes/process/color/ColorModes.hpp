#pragma once

#include <QtQmlIntegration>

namespace CutieDesigner {
Q_NAMESPACE
QML_ELEMENT

enum ColorMode {
  RGBA,
  HSLA,
  HSVA,
  CMYKA,
  OKLAB,
  LCH,
};
Q_ENUM_NS(ColorMode)

QStringList getColorModeNames();
std::string getColorModeComponents(ColorMode mode);

} // namespace CutieDesigner
