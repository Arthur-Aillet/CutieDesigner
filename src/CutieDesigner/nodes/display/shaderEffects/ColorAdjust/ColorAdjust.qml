import QtQuick
import CutieDesigner.Nodes.Display

Item {
    id: colorAdjust
    required property ColorAdjustNode node

    anchors.fill: parent

    SurfaceLoader {
        id: sourceLoader
        surfaceData: colorAdjust.node.source

        visible: false
        layer.enabled: true
    }

    ShaderEffect {
        id: shader

        visible: sourceLoader.surface !== null

        anchors.fill: source

        property alias source: sourceLoader
        property rect sourceRect: Qt.rect(sourceLoader.x, sourceLoader.y, sourceLoader.width, sourceLoader.height)

        property real brightness: colorAdjust.node.brightness
        property real contrast: colorAdjust.node.contrast
        property real saturation: colorAdjust.node.saturation

        vertexShader: 'colorAdjust.vert.qsb'
        fragmentShader: 'colorAdjust.frag.qsb'
    }
}
