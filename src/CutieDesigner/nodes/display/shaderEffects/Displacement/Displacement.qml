import QtQuick
import CutieDesigner.Nodes.Display

Item {
    id: displacement
    required property DisplacementNode node

    anchors.fill: parent

    SurfaceLoader {
        id: imageLoader
        surfaceData: displacement.node.image

        visible: false
        layer.enabled: true
    }

    SurfaceLoader {
        id: mapLoader
        surfaceData: displacement.node.map

        visible: false
        layer.enabled: true
    }

    ShaderEffect {
        id: shader

        visible: imageLoader.surface !== null && mapLoader.surface !== null

        anchors.fill: image

        property alias image: imageLoader
        property alias map: mapLoader

        property rect imageRect: Qt.rect(imageLoader.x, imageLoader.y, imageLoader.width, imageLoader.height)
        property rect mapRect: Qt.rect(mapLoader.x, mapLoader.y, mapLoader.width, mapLoader.height)

        property real minDisp: displacement.node.min
        property real maxDisp: displacement.node.max

        vertexShader: 'displacement.vert.qsb'
        fragmentShader: 'displacement.frag.qsb'
    }
}
