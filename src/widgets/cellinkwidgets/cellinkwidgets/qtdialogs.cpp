#include "cellinkwidgets_stable.h"

#include "cellinkwidgets/qtdialogs.h"

Q_LOGGING_CATEGORY(lcDlgMgr, "cellink.ui.dialogmanager", QtInfoMsg);

QtDialogs::QtDialogs(QObject* parent) : QObject(parent) {}
QtDialogs::~QtDialogs() = default;

int QtDialogs::execDialog(QDialog* dlg)
{
    // TODO: Remove this function, use only show

    qDebug() << __FUNCTION__ << dlg;
    const auto result = dlg->exec();
    qDebug() << "Result:" << result;
    return result;
}

void QtDialogs::showDialog(QDialog* dlg)
{
    qDebug() << __FUNCTION__ << dlg;
    dlg->show();
}

QString QtDialogs::getExistingDirectory(QWidget *parent,
                                            const QString &caption,
                                            const QString &dir,
                                            QFileDialog::Options options)
{
    qDebug() << __FUNCTION__ << parent << caption << dir << options;
    // Native dialog crashes with media player
    const auto result = QFileDialog::getExistingDirectory(parent, caption, dir,
                                                          options | QFileDialog::DontUseNativeDialog);
    qDebug() << "Result:" << result;
    return result;
}

QString QtDialogs::getSaveFileName(QWidget *parent,
                        const QString &caption,
                        const QString &dir,
                        const QString &filter,
                        QString *selectedFilter,
                        QFileDialog::Options options)
{
    qDebug() << __FUNCTION__ << parent << caption << dir << filter << selectedFilter << options;

    auto acceptedResult = false;
    QString result;

    // if the replace is not accepted, save file dialog should be visible again
    while (!acceptedResult) {
        // Native dialog crashes with media player
        result = QFileDialog::getSaveFileName(parent, caption, dir, filter,
                                              selectedFilter, options | QFileDialog::DontUseNativeDialog);

        // because of DontUseNativeDialog, the extension is not checked automatically
        QString extension;
        QRegExp extensionExp("^.*\\(\\*(.*)\\);$");
        if(extensionExp.exactMatch(filter)) {
            extension = extensionExp.cap(1);
        }

        if (!extension.isEmpty() && !result.endsWith(extension)) {
            QFileInfo info(QString("%0%1").arg(result, extension));
            if (info.exists()) {
                auto res = showWarningMessageBox(parent, tr("File already exists"),
                                                 tr("%0 already exists.\nDo you want to replace it?").arg(info.fileName()),
                                                 QMessageBox::Yes | QMessageBox::No,
                                                 QMessageBox::Yes);
                acceptedResult = res == QMessageBox::Yes;
                continue;
            }
        }
        acceptedResult = true;
    }

    qDebug() << "Result:" << result;
    return result;
}

QString QtDialogs::getOpenFileName(QWidget *parent, const QString &caption,
                                     const QString &dir, const QString &filter,
                                     QString *selectedFilter, QFileDialog::Options options)
{
    qDebug() << __FUNCTION__ << parent << caption << dir << options << selectedFilter << options;
    // Native dialog crashes with media player
    auto result = QFileDialog::getOpenFileName(parent, caption, dir, filter,
                                               selectedFilter, options | QFileDialog::DontUseNativeDialog);
    qDebug() << "Result:" << result;
    return result;
}

QStringList QtDialogs::getOpenFileNames(QWidget *parent, const QString &caption,
                                        const QString &dir, const QString &filter,
                                        QString *selectedFilter, QFileDialog::Options options)
{
    qDebug() << __FUNCTION__ << parent << caption << dir << options << selectedFilter << options;
    // Native dialog crashes with media player
    const auto result = QFileDialog::getOpenFileNames(parent, caption, dir, filter,
                                                      selectedFilter, options | QFileDialog::DontUseNativeDialog);
    qDebug() << "Result:" << result;
    return result;
}

QMessageBox::StandardButton QtDialogs::showCriticalMessageBox(
        QWidget *parent, const QString &title, const QString &text,
        QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
    qCritical() << __FUNCTION__ << parent << title << text << buttons << defaultButton;
    const auto result = QMessageBox::critical(parent, title, text, buttons, defaultButton);
    qDebug() << "Result:" << result;
    return result;
}

QMessageBox::StandardButton QtDialogs::showWarningMessageBox(
        QWidget *parent, const QString &title, const QString &text,
        QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
    qCritical() << __FUNCTION__ << parent << title << text << buttons << defaultButton;
    const auto result = QMessageBox::warning(parent, title, text, buttons, defaultButton);
    qDebug() << "Result:" << result;
    return result;
}

QMessageBox::StandardButton QtDialogs::showQuestionMessageBox(
        QWidget *parent, const QString &title, const QString &text,
        QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
    return QMessageBox::question(parent, title, text, buttons, defaultButton);
}

void QtDialogs::openQmlDialog(QObject *qmlDialog)
{
    Q_ASSERT(qmlDialog->metaObject()->indexOfMethod("open") >= 0);

    QMetaObject::invokeMethod(qmlDialog, "open");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

class MockQtDialogsPrivate
{
public:
    struct DialogResponse {
        QString property;
        QVariant value;
    };

    QVector<QString> m_getExistingDirectoryResponses;
    QVector<MockQtDialogs::GetExistingDirectoryArgs> m_getExistingDirectoryArgs;

    QVector<QString> m_getSaveFileNameResponses;
    QVector<MockQtDialogs::GetSaveFileNameArgs> m_getSaveFileNameArgs;

    QVector<QString> m_getOpenFileNameResponses;
    QVector<MockQtDialogs::GetOpenFileNameArgs> m_getOpenFileNameArgs;

    QStringList m_getOpenFileNamesResponse;

    QVector<QMessageBox::StandardButton> m_criticalMessageBoxResponses;
    QVector<MockQtDialogs::MessageBoxArgs> m_criticalMessageBoxArgs;

    QVector<QMessageBox::StandardButton> m_warningMessageBoxResponses;
    QVector<MockQtDialogs::MessageBoxArgs> m_warningMessageBoxArgs;

    QVector<QMessageBox::StandardButton> m_questionMessageBoxResponses;
    QVector<MockQtDialogs::MessageBoxArgs> m_questionMessageBoxArgs;

    QVector<QPointer<QDialog>> m_shownDlgs;  // History of shown dialogs
    QVector<QPointer<QDialog>> m_activeDlgs; // Currently active dialogs

    QHash<QString, DialogResponse> m_qmlDialogResponses;

    template<class T> auto popResponse(T& vec) -> typename T::value_type
    {
        if (vec.empty())
            return {};

        auto r = vec.front();
        vec.pop_front();
        return r;
    }

    void reset()
    {
        m_getExistingDirectoryResponses.clear();
        m_getExistingDirectoryArgs.clear();

        m_getSaveFileNameResponses.clear();
        m_getSaveFileNameArgs.clear();

        m_getOpenFileNameResponses.clear();
        m_getOpenFileNameArgs.clear();

        m_getOpenFileNamesResponse.clear();

        m_criticalMessageBoxResponses.clear();
        m_criticalMessageBoxArgs.clear();

        m_warningMessageBoxResponses.clear();
        m_warningMessageBoxArgs.clear();

        m_questionMessageBoxResponses.clear();
        m_questionMessageBoxArgs.clear();

        m_shownDlgs.clear();
        m_qmlDialogResponses.clear();
    }
};

MockQtDialogs::MockQtDialogs(QObject* parent) :
    QtDialogs(parent),
    d_ptr(new MockQtDialogsPrivate)
{}

MockQtDialogs::~MockQtDialogs() = default;

int MockQtDialogs::execDialog(QDialog* dlg)
{
    qCDebug(lcDlgMgr) << "Only showing dialog" << dlg << "(not executing modally).";
    showDialog(dlg);
    dlg->raise();
    dlg->activateWindow();

    return m_execDialogResult;
}

void MockQtDialogs::showDialog(QDialog* dlg)
{
    Q_D(MockQtDialogs);
    d->m_shownDlgs.push_back(dlg);
    d->m_activeDlgs.push_back(dlg);
    dlg->show();
    connect(dlg, &QDialog::finished, this, [d, dlg](){
        auto it = std::find(d->m_activeDlgs.begin(), d->m_activeDlgs.end(), dlg);
        if (it != d->m_activeDlgs.end()) {
            d->m_activeDlgs.erase(it);
        }
        else {
            qWarning() << "Previously open dialog not present in list of open dialogs.";
        }
    });
}


QVector<QPointer<QDialog>> MockQtDialogs::getShownDialogs() const
{
    return d_ptr->m_shownDlgs;
}

void MockQtDialogs::resetShownDialog()
{
    d_ptr->m_shownDlgs.clear();
}

QVector<QPointer<QDialog> > MockQtDialogs::getActiveDialogs() const
{
    return d_ptr->m_activeDlgs;
}

QString MockQtDialogs::getExistingDirectory(QWidget *parent,
                                            const QString &caption,
                                            const QString &dir,
                                            QFileDialog::Options options)
{
    d_ptr->m_getExistingDirectoryArgs.push_back({parent, caption, dir, options});
    return d_ptr->popResponse(d_ptr->m_getExistingDirectoryResponses);
}

void MockQtDialogs::setExistingDirectoryResponses(QVector<QString> responses)
{
    d_ptr->m_getExistingDirectoryResponses = std::move(responses);
}

QVector<MockQtDialogs::GetExistingDirectoryArgs>& MockQtDialogs::getExistingDirectoryArgs() const
{
    return d_ptr->m_getExistingDirectoryArgs;
}

QString MockQtDialogs::getSaveFileName(QWidget *parent,
                                       const QString &caption,
                                       const QString &dir,
                                       const QString &filter,
                                       QString *selectedFilter,
                                       QFileDialog::Options options)
{
    d_ptr->m_getSaveFileNameArgs.push_back({parent, caption, dir, filter, selectedFilter, options});
    return d_ptr->popResponse(d_ptr->m_getSaveFileNameResponses);
}

void MockQtDialogs::setSaveFileResponses(QVector<QString> responses)
{
    d_ptr->m_getSaveFileNameResponses = std::move(responses);
}

QVector<MockQtDialogs::GetSaveFileNameArgs>& MockQtDialogs::getSaveFileArgs() const
{
    return d_ptr->m_getSaveFileNameArgs;
}

QString MockQtDialogs::getOpenFileName(QWidget *parent, const QString &caption,
                                     const QString &dir, const QString &filter,
                                     QString *selectedFilter, QFileDialog::Options options)
{
    d_ptr->m_getOpenFileNameArgs.push_back({parent, caption, dir, filter, selectedFilter, options});
    return d_ptr->popResponse(d_ptr->m_getOpenFileNameResponses);
}

void MockQtDialogs::setOpenFileNameResponses(QVector<QString> fileNames)
{
    d_ptr->m_getOpenFileNameResponses = std::move(fileNames);
}

QVector<MockQtDialogs::GetOpenFileNameArgs>& MockQtDialogs::getOpenFileNameArgs() const
{
    return d_ptr->m_getOpenFileNameArgs;
}

QStringList MockQtDialogs::getOpenFileNames(QWidget *parent, const QString &caption,
                                            const QString &dir, const QString &filter,
                                            QString *selectedFilter, QFileDialog::Options options)
{
    // TODO: Store this in arg vec like everything else!
    Q_UNUSED(parent)
    Q_UNUSED(caption)
    Q_UNUSED(dir)
    Q_UNUSED(filter)
    Q_UNUSED(selectedFilter)
    Q_UNUSED(options)
    return d_ptr->m_getOpenFileNamesResponse;
}

void MockQtDialogs::setOpenFileNamesResponse(QStringList fileNames)
{
    d_ptr->m_getOpenFileNamesResponse = std::move(fileNames);
}

QStringList& MockQtDialogs::getOpenFileNamesResponse() const
{
    return d_ptr->m_getOpenFileNamesResponse;
}

QMessageBox::StandardButton MockQtDialogs::showCriticalMessageBox(
        QWidget *parent,
        const QString &title,
        const QString &text,
        QMessageBox::StandardButtons buttons,
        QMessageBox::StandardButton defaultButton)
{
    Q_D(MockQtDialogs);
    d->m_criticalMessageBoxArgs.push_back({parent, title, text, buttons, defaultButton});
    return d->popResponse(d->m_criticalMessageBoxResponses);
}

QMessageBox::StandardButton MockQtDialogs::showWarningMessageBox(
        QWidget *parent,
        const QString &title,
        const QString &text,
        QMessageBox::StandardButtons buttons,
        QMessageBox::StandardButton defaultButton)
{
    Q_D(MockQtDialogs);
    d->m_warningMessageBoxArgs.push_back({parent, title, text, buttons, defaultButton});
    return d->popResponse(d->m_warningMessageBoxResponses);
}

QMessageBox::StandardButton MockQtDialogs::showQuestionMessageBox(
        QWidget *parent,
        const QString &title,
        const QString &text,
        QMessageBox::StandardButtons buttons,
        QMessageBox::StandardButton defaultButton)
{
    Q_D(MockQtDialogs);
    d->m_questionMessageBoxArgs.push_back({parent, title, text, buttons, defaultButton});
    return d->popResponse(d->m_questionMessageBoxResponses);
}

void MockQtDialogs::setCriticalMessageBoxResponses(QVector<QMessageBox::StandardButton> buttons)
{
    d_ptr->m_criticalMessageBoxResponses = std::move(buttons);
}

QVector<MockQtDialogs::MessageBoxArgs>& MockQtDialogs::getCriticalMessageBoxArgs() const
{
    return d_ptr->m_criticalMessageBoxArgs;
}

void MockQtDialogs::setWarningMessageBoxResponses(QVector<QMessageBox::StandardButton> buttons)
{
    d_ptr->m_warningMessageBoxResponses = std::move(buttons);
}

QVector<MockQtDialogs::MessageBoxArgs> &MockQtDialogs::getWarningMessageBoxArgs() const
{
    return d_ptr->m_warningMessageBoxArgs;
}

void MockQtDialogs::setQuestionMessageBoxResponses(QVector<QMessageBox::StandardButton> buttons)
{
    d_ptr->m_questionMessageBoxResponses = std::move(buttons);
}

QVector<MockQtDialogs::MessageBoxArgs> &MockQtDialogs::getQuestionMessageBoxArgs() const
{
    return d_ptr->m_questionMessageBoxArgs;
}

void MockQtDialogs::reset()
{   
    d_ptr->reset();
}


void MockQtDialogs::openQmlDialog(QObject* qmlDialog)
{
    // TODO: Move to QtDialogs?

    const auto r = d_ptr->m_qmlDialogResponses.value(qmlDialog->objectName());

    if (!r.property.isNull()) {
        qInfo() << "Setting property" << r.property << "to" << r.value<< "for dialog" << qmlDialog;
        qDebug() << "Previous value" << qmlDialog->property(qPrintable(r.property));

        const auto propOk = qmlDialog->setProperty(qPrintable(r.property), r.value);
        if (!propOk) {
            qCritical() << "Failed to set property" << r.property << "on" << qmlDialog;
        }
        Q_ASSERT(propOk);
    } else {
        qWarning() << "No response recorded for dialog, accepting anyway." << qmlDialog;
    }

    QMetaObject::invokeMethod(qmlDialog, "accepted");
}

void MockQtDialogs::addQmlDialogResponse(const QString& dialogName, const QString& property, QVariant value)
{
#ifdef QT_QML_LIB
    if (value.canConvert<QJSValue>()) {
        // convert from jsvalue to stringlist-ish
        value = qvariant_cast<QJSValue>(value).toVariant();

        if (property == "files") { // hack for FileDialog
            QList<QUrl> list;
            for(const auto& url : value.toList()) {
                list.push_back(QUrl(url.toString()));
            }
            value = QVariant::fromValue(list);
        }
    }
#endif

    qDebug() << "Adding response" << property << "=" << value << "for" << dialogName;
    d_ptr->m_qmlDialogResponses[dialogName] = {property, value};
}

void MockQtDialogs::clearQmlDialogResponses()
{
    d_ptr->m_qmlDialogResponses.clear();
}


QDebug operator<<(QDebug debug, const MockQtDialogs::MessageBoxArgs& args)
{
    return debug << "parent:" << args.parent
                 << "title:" << args.title
                 << "text:" << args.text
                 << "buttons:" << args.buttons
                 << "defaultButton:" << args.defaultButton;
}
