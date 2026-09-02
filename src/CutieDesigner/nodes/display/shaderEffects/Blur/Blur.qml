import QtQuick
import CutieDesigner.Nodes.Display
import Qt5Compat.GraphicalEffects

Item {
    id: blur
    required property BlurNode node

    anchors.fill: parent

    SurfaceLoader {
        id: sourceLoader
        surfaceData: blur.node.source

        visible: false
        layer.enabled: true
    }

    FastBlur {
        anchors.fill: sourceLoader
        source: sourceLoader
        radius: blur.node.radius
    }
}
