FROM ubuntu:19.10

ARG QT_VERSION=dev
ARG QT_MODULES=qt3d,qtbase,qtdeclarative,qtgraphicaleffects,qtimageformats,qtmultimedia,qtquickcontrols2,qtserialport,qtsvg,qtvirtualkeyboard,qtxmlpatterns,uiplugin
ARG QT_ADDONS=qtmqtt

RUN echo "Building Qt ${QT_VERSION}"

USER root

RUN sed -i -- 's/# deb-src/deb-src/g' /etc/apt/sources.list
RUN apt update
RUN apt -y upgrade
RUN apt -y install git-core
RUN apt -y build-dep qtbase-opensource-src
RUN update-alternatives --install /usr/bin/python python /usr/bin/python3 100

RUN mkdir /build
WORKDIR /build

RUN git clone git://code.qt.io/qt/qt5.git /build/qt5 && \
    cd /build/qt5 && git checkout ${QT_VERSION} && ./init-repository -module-subset=${QT_MODULES} && \
    git submodule foreach git checkout ${QT_VERSION}
RUN for qt_module in $(echo ${QT_ADDONS} | sed "s/,/ /g"); do \
        git clone git://code.qt.io/qt/${qt_module}.git /build/qt5/${qt_module} && \
        cd /build/qt5/${qt_module} && git checkout ${QT_VERSION}; done

WORKDIR /build/qt5
RUN ./configure -opensource -confirm-license -prefix /opt/qt5 -nomake examples -nomake tests -no-use-gold-linker
RUN make -j9 && make install
RUN for qt_module in $(echo ${QT_ADDONS} | sed "s/,/ /g"); do \
        cd /build/qt5/${qt_module} && /opt/qt5/bin/qmake && \
        make -j9 && make install; done

WORKDIR /
RUN rm -rf /build
