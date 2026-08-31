import QtQuick

Item {
    id: noise
    anchors.fill: parent
    required property NoiseNode node

    ShaderEffect {
        id: shader
        anchors.fill: parent

        property vector3d iResolution: Qt.vector3d(noise.width, noise.height, 1.0)
        property real iTime: noise.node.time
        property int mode: noise.node.mode
        vertexShader: 'noise.vert.qsb'
        fragmentShader: 'noise.frag.qsb'
    }
}
