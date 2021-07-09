#ifndef QTDIALOGS_H
#define QTDIALOGS_H

#include "cellinkwidgets_global.h"
#include <QFileDialog>

#include <QMessageBox>
#include <QVariant>
#include <memory>

class QDialog;

/** @brief Interface for static dialog functions to make them mock/testable
 *
 * Extend with messageboxes, file dialogs etc as necessary.
 *
 * @note This class is stateless so it serves as both interface and base implementation
 */
class CELLINKWIDGETS_EXPORT QtDialogs : public QObject
{
    Q_OBJECT

public:
    QtDialogs(QObject* parent = nullptr);
    virtual ~QtDialogs() override;

    /**
     * @brief execDialog runs @fn QDialog::exec() by default, but should be avoided
     * @param dialog
     * @return dialog result
     *
     * @note Since this blocks execution until dialog has finished, it makes writing tests harder.
     * Prefer to use @fn showDialog instead
     */
    virtual int execDialog(QDialog* dialog);
    /**
     * @brief showDialog runs @fn QDialog::show() and returns immediately
     * @param dialog
     */
    virtual void showDialog(QDialog* dialog);

    virtual QString getExistingDirectory(
            QWidget *parent = nullptr,
            const QString &caption = QString(),
            const QString &dir = QString(),
            QFileDialog::Options options = QFileDialog::ShowDirsOnly);

    virtual QString getSaveFileName(
            QWidget *parent = nullptr,
            const QString &caption = QString(),
            const QString &dir = QString(),
            const QString &filter = QString(),
            QString *selectedFilter = nullptr,
            QFileDialog::Options options = QFileDialog::Options());

    virtual QString getOpenFileName(QWidget *parent = nullptr,
                                    const QString &caption = QString(),
                                    const QString &dir = QString(),
                                    const QString &filter = QString(),
                                    QString *selectedFilter = nullptr,
                                    QFileDialog::Options options = {});

    virtual QStringList getOpenFileNames(
            QWidget *parent = nullptr,
            const QString &caption = QString(),
            const QString &dir = QString(),
            const QString &filter = QString(),
            QString *selectedFilter = nullptr,
            QFileDialog::Options options = QFileDialog::Options());

    virtual QMessageBox::StandardButton showCriticalMessageBox(
            QWidget *parent,
            const QString &title,
            const QString &text,
            QMessageBox::StandardButtons buttons = QMessageBox::Ok,
            QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

    virtual QMessageBox::StandardButton showWarningMessageBox(
            QWidget *parent,
            const QString &title,
            const QString &text,
            QMessageBox::StandardButtons buttons = QMessageBox::Ok,
            QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

    virtual QMessageBox::StandardButton showQuestionMessageBox(
            QWidget *parent,
            const QString &title,
            const QString &text,
            QMessageBox::StandardButtons buttons = QMessageBox::Ok,
            QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

    Q_INVOKABLE virtual void openQmlDialog(QObject* qmlDialog);
};

class MockQtDialogsPrivate;

class CELLINKWIDGETS_EXPORT MockQtDialogs : public QtDialogs
{
    Q_OBJECT

public:
    explicit MockQtDialogs(QObject* parent = nullptr);
    ~MockQtDialogs() override;

    int execDialog(QDialog* dialog) override;
    void showDialog(QDialog* dlg) override;
    QVector<QPointer<QDialog>> getShownDialogs() const;
    void resetShownDialog();

    QVector<QPointer<QDialog>> getActiveDialogs() const;

    int m_execDialogResult = -1;

    struct GetExistingDirectoryArgs
    {
        QWidget *parent = nullptr;
        QString caption = {};
        QString dir = {};
        QFileDialog::Options options = QFileDialog::ShowDirsOnly;
    };

    QString getExistingDirectory(QWidget *parent = nullptr,
                                 const QString &caption = QString(),
                                 const QString &dir = QString(),
                                 QFileDialog::Options options = QFileDialog::ShowDirsOnly) override;

    void setExistingDirectoryResponses(QVector<QString> responses);
    [[nodiscard]] QVector<GetExistingDirectoryArgs>& getExistingDirectoryArgs() const;

    struct GetSaveFileNameArgs
    {
        QWidget *parent = nullptr;
        QString caption = {};
        QString dir = {};
        QString filter = {};
        QString *selectedFilter = nullptr;
        QFileDialog::Options options = {};
    };

    QString getSaveFileName(QWidget *parent = nullptr,
                            const QString &caption = QString(),
                            const QString &dir = QString(),
                            const QString &filter = QString(),
                            QString *selectedFilter = nullptr,
                            QFileDialog::Options options = {}) override;

    void setSaveFileResponses(QVector<QString> responses);
    [[nodiscard]] QVector<GetSaveFileNameArgs>& getSaveFileArgs() const;

    struct GetOpenFileNameArgs
    {
        QWidget* parent = nullptr;
        QString caption = {};
        QString dir = {};
        QString filter = {};
        QString* selectedFilter = nullptr;
        QFileDialog::Options options = {};
    };

    QString getOpenFileName(QWidget *parent = nullptr,
                            const QString &caption = QString(),
                            const QString &dir = QString(),
                            const QString &filter = QString(),
                            QString *selectedFilter = nullptr,
                            QFileDialog::Options options = {}) override;

    void setOpenFileNameResponses(QVector<QString> fileNames);
    [[nodiscard]] QVector<GetOpenFileNameArgs>& getOpenFileNameArgs() const;

    QStringList getOpenFileNames(QWidget *parent = nullptr,
                            const QString &caption = QString(),
                            const QString &dir = QString(),
                            const QString &filter = QString(),
                            QString *selectedFilter = nullptr,
                            QFileDialog::Options options = {}) override;

    void setOpenFileNamesResponse(QStringList fileNames);
    [[nodiscard]] QStringList& getOpenFileNamesResponse() const;

    struct MessageBoxArgs
    {
        QWidget *parent = nullptr;
        QString title = {};
        QString text = {};
        QMessageBox::StandardButtons buttons = QMessageBox::Ok;
        QMessageBox::StandardButton defaultButton = QMessageBox::NoButton;
    };

    QMessageBox::StandardButton showCriticalMessageBox(
            QWidget *parent,
            const QString &title,
            const QString &text,
            QMessageBox::StandardButtons buttons = QMessageBox::Ok,
            QMessageBox::StandardButton defaultButton = QMessageBox::NoButton) override;

    QMessageBox::StandardButton showWarningMessageBox(
            QWidget *parent,
            const QString &title,
            const QString &text,
            QMessageBox::StandardButtons buttons = QMessageBox::Ok,
            QMessageBox::StandardButton defaultButton = QMessageBox::NoButton) override;

    QMessageBox::StandardButton showQuestionMessageBox(
            QWidget *parent,
            const QString &title,
            const QString &text,
            QMessageBox::StandardButtons buttons = QMessageBox::Ok,
            QMessageBox::StandardButton defaultButton = QMessageBox::NoButton) override;

    void setCriticalMessageBoxResponses(QVector<QMessageBox::StandardButton> buttons);
    [[nodiscard]] QVector<MessageBoxArgs>& getCriticalMessageBoxArgs() const;

    void setWarningMessageBoxResponses(QVector<QMessageBox::StandardButton> buttons);
    [[nodiscard]] QVector<MessageBoxArgs>& getWarningMessageBoxArgs() const;

    void setQuestionMessageBoxResponses(QVector<QMessageBox::StandardButton> buttons);
    [[nodiscard]] QVector<MessageBoxArgs>& getQuestionMessageBoxArgs() const;

    void openQmlDialog(QObject* qmlDialog) override;
    Q_INVOKABLE void addQmlDialogResponse(const QString& dialogName, const QString& property, QVariant value);
    Q_INVOKABLE void clearQmlDialogResponses();

    void reset();

private:
    Q_DECLARE_PRIVATE(MockQtDialogs);
    std::unique_ptr<MockQtDialogsPrivate> d_ptr;
};

CELLINKWIDGETS_EXPORT QDebug operator<<(QDebug debug, const MockQtDialogs::MessageBoxArgs& args);

#endif // QTDIALOGS_H
