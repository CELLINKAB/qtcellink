/****************************************************************************
**
** Copyright (C) 2020 CELLINK AB <info@cellink.com>
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

#ifndef SERIALTESTCASE_H
#define SERIALTESTCASE_H

#include "testcase.h"
#include <QtCore/qfile.h>
#include <QtCore/qprocess.h>

class SerialTestCase : public TestCase
{
    Q_OBJECT

public:
    static inline const int TestSerialTimeout = 500;
    static inline const QString VirtualBoardPort = QStringLiteral("/tmp/serialtestboard");
    static inline const QString VirtualServicePort = QStringLiteral("/tmp/serialtestservice");

public slots:
    void initTestCase()
    {
#ifndef Q_OS_UNIX
        QSKIP("This test requires a Unix platform.");
#endif

        process.start("socat", { "PTY,link=" + VirtualServicePort, "PTY,link=" + VirtualBoardPort });
        if (!process.waitForStarted(2000))
            QSKIP("This test requires socat to emulate serial ports. Try `sudo apt install socat`.");

        QTRY_VERIFY(QFile::exists(VirtualBoardPort));
        QTRY_VERIFY(QFile::exists(VirtualServicePort));
    }

    void cleanupTestCase()
    {
        process.terminate();
        process.waitForFinished(2000);
    }

private:
    QProcess process;
};

#endif // SERIALTESTCASE_H
