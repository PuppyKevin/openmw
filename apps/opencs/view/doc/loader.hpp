#ifndef CSV_DOC_LOADER_H
#define CSV_DOC_LOADER_H

#include <map>

#include <QObject>
#include <QWidget>
#include <QSignalMapper>

class QLabel;
class QProgressBar;
class QDialogButtonBox;
class QListWidget;
class QVBoxLayout;

namespace CSMDoc
{
    class Document;
}

namespace CSVDoc
{
    class LoadingDocument : public QWidget
    {
            Q_OBJECT

            CSMDoc::Document *mDocument;
            QLabel *mFile;
            QProgressBar *mFileProgress;
            QProgressBar *mRecordProgress;
            bool mAborted;
            QDialogButtonBox *mButtons;
            QLabel *mError;
            QListWidget *mMessages;
            QVBoxLayout *mLayout;

        private:

            void closeEvent (QCloseEvent *event);

        public:

            LoadingDocument (CSMDoc::Document *document);

            void nextStage (const std::string& name, int steps);

            void nextRecord();

            void abort (const std::string& error);

            void addMessage (const std::string& message);

        private slots:

            void cancel();

        signals:

            void cancel (CSMDoc::Document *document);
            ///< Stop loading process.

            void close (CSMDoc::Document *document);
            ///< Close stopped loading process.
    };

    class Loader : public QObject
    {
            Q_OBJECT

            std::map<CSMDoc::Document *, LoadingDocument *> mDocuments;

        public:

            Loader();

            virtual ~Loader();

        signals:

            void cancel (CSMDoc::Document *document);

            void close (CSMDoc::Document *document);

        public slots:

            void add (CSMDoc::Document *document);

            void loadingStopped (CSMDoc::Document *document, bool completed,
                const std::string& error);

            void nextStage (CSMDoc::Document *document, const std::string& name, int steps);

            void nextRecord (CSMDoc::Document *document);

            void loadMessage (CSMDoc::Document *document, const std::string& message);
    };
}

#endif
