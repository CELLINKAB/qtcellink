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

#ifndef TESTCASE_H
#define TESTCASE_H

#include <QtTest/qtest.h>
#include <QtCore/qcoreapplication.h>
#include <QtCore/qstandardpaths.h>
#include "qtest_fuzzy.h"
#include "qtest_json.h"

class TestCase : public QObject
{
    Q_OBJECT

public:
    explicit TestCase(QObject *parent = nullptr) : QObject(parent)
    {
        initTestApp();
    }

    static void initTestApp()
    {
        QStringList libraryPaths = QCoreApplication::libraryPaths();
        libraryPaths.prepend(PLUGIN_PATH);
        QCoreApplication::setLibraryPaths(libraryPaths);

        QStandardPaths::setTestModeEnabled(true);
        qAddPostRoutine(cleanupTestApp);
        cleanupTestApp();
    }

    static void cleanupTestApp()
    {
        // ~/.qttest/share/<app>
        QDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)).removeRecursively();
    }

    static QString findTestDataFile(const QString &fileName)
    {
        return QFINDTESTDATA("data/" + fileName);
    }
};

#endif // TESTCASE_H
