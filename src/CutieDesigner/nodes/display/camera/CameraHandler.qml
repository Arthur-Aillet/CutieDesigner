import QtQuick
import QtMultimedia

Item {
    id: handler
    property alias out: out
    property alias captureSession: captureSession

    property int refCount: 0

    signal cameraStarted
    signal cameraStopped
    property bool capturing: false

    onRefCountChanged: () => {
        if (refCount == 0) {
            camera.stop();
            cameraStopped();
            capturing = false;
        }
        if (refCount > 0 && !camera.active) {
            camera.start();
            cameraStarted();
            capturing = true;
        }
    }

    CaptureSession {
        id: captureSession
        camera: Camera {
            id: camera
        }
        imageCapture: ImageCapture {}
        videoOutput: out
    }

    VideoOutput {
        id: out
        width: 1280
        height: 720
        opacity: 0
    }
}
