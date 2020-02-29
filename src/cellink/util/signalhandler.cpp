/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
** Copyright (C) 2016 The Qt Company Ltd.
**
** This file is part of QtCellink (based on Qt docs).
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**
** 1. Redistributions of source code must retain the above copyright notice,
**    this list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright notice,
**    this list of conditions and the following disclaimer in the documentation
**    and/or other materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its contributors
**    may be used to endorse or promote products derived from this software
**    without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
** POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************/

#include "signalhandler.h"
#include <QtCore/qdebug.h>
#include <QtCore/qsocketnotifier.h>

#ifdef Q_OS_UNIX
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

namespace {
int sigIntFd[2];
int sigHupFd[2];
int sigTermFd[2];
}

QT_WARNING_PUSH
QT_WARNING_DISABLE_GCC("-Wunused-result")

static void sigHupHandler(int)
{
    char a = 1;
    ::write(sigHupFd[0], &a, sizeof(a));
}

static void sigIntHandler(int)
{
    char a = 1;
    ::write(sigIntFd[0], &a, sizeof(a));
}

static void sigTermHandler(int)
{
    char a = 1;
    ::write(sigTermFd[0], &a, sizeof(a));
}

QT_WARNING_POP

#endif

SignalHandler::SignalHandler(QObject *parent) : QObject(parent)
{
#ifdef Q_OS_UNIX
    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigIntFd))
        qFatal("Couldn't create SIGINT socketpair");

    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigHupFd))
        qFatal("Couldn't create SIGHUP socketpair");

    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigTermFd))
        qFatal("Couldn't create SIGTERM socketpair");

    sigHupNotifier = new QSocketNotifier(sigHupFd[1], QSocketNotifier::Read, this);
    connect(sigHupNotifier, &QSocketNotifier::activated, [&]() { handleSignal(sigHupFd[1], sigHupNotifier); });

    sigIntNotifier = new QSocketNotifier(sigIntFd[1], QSocketNotifier::Read, this);
    connect(sigIntNotifier, &QSocketNotifier::activated, [&]() { handleSignal(sigIntFd[1], sigIntNotifier); });

    sigTermNotifier = new QSocketNotifier(sigTermFd[1], QSocketNotifier::Read, this);
    connect(sigTermNotifier, &QSocketNotifier::activated, [&]() { handleSignal(sigTermFd[1], sigTermNotifier); });
#endif
}

void SignalHandler::setup(std::function<void()> func)
{
    callback = func;

#ifdef Q_OS_UNIX
    const struct Signal {
        int num;
        __sighandler_t handler;
    } handlers[] = {
        { SIGHUP, sigHupHandler },
        { SIGINT, sigIntHandler },
        { SIGTERM, sigTermHandler }
    };

    for (const Signal sig : handlers) {
        struct sigaction act;
        act.sa_handler = sig.handler;
        sigemptyset(&act.sa_mask);
        act.sa_flags |= SA_RESTART;
        if (sigaction(sig.num, &act, 0))
           qWarning() << "SignalHandler: failed to register" << sig.num;
    }
#endif
}

QT_WARNING_PUSH
QT_WARNING_DISABLE_GCC("-Wunused-result")

void SignalHandler::handleSignal(int fd, QSocketNotifier *socket)
{
#ifdef Q_OS_UNIX
    socket->setEnabled(false);
    char tmp;
    ::read(fd, &tmp, sizeof(tmp));
    if (callback)
        callback();
    socket->setEnabled(true);
#endif
}

QT_WARNING_POP
