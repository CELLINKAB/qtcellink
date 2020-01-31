# Qt 5 Docker images

Pre-built images available on [Docker Hub](https://hub.docker.com/repository/docker/cellink/qt5).

## About

The parent image is `ubuntu:19.10`. Qt is installed to `/opt/qt5`.

Available Qt modules:
- qt3d
- qtbase
- qtdeclarative
- qtgraphicaleffects
- qtimageformats
- qtmultimedia
- qtmqtt
- qtquickcontrols2
- qtserialport
- qtsvg
- qtxmlpatterns
- qtvirtualkeyboard

## Pull

    docker pull cellink/qt5:latest

## Usage

    FROM cellink/qt5:latest
    RUN /opt/qt5/bin/qmake --version

## Build

    docker build -t cellink/qt5:5.14.1 --build-arg QT_VERSION=v5.14.1 .

NOTE: QT_VERSION can be specified as any tag or branch name in Qt
      repositories. The default value is "dev" if left unspecified!

## Push

    docker login docker.io
    docker push cellink/qt5:5.14.1

## Tag

    docker tag cellink/qt5:5.14.1 cellink/qt5:latest
    docker push cellink/qt5:latest
