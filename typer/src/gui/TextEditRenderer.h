#pragma once

#include <QTextEdit>
#include <QColor>

namespace typer
{
    namespace gui
    {
        class TextEditRenderer : public QObject
        {
            Q_OBJECT
        public:
            TextEditRenderer(const QString & textToType,
                                 QTextEdit * textEdit,
                                 QObject * parent);

            TextEditRenderer(const QStringList & wordsToType,
                                 QTextEdit * textEdit,
                                 QObject * parent);

            void setCorrectWordColor( const QColor & color) {
                m_correctWordColor = color;
            }

            void setIncorrectWordColor( const QColor & color) {
                m_incorrectWordColor = color;
            }

            void setNotTypedWordColor( const QColor & color) {
                m_notTypedWord = color;
            }

        protected slots:
            void textChanged();

        protected:
            void startRendering();
            void stopRendering();
            bool isRendering();
            void splitLines( const QStringList & words);
            void setInitText();

        protected:
            QTextEdit * m_textEdit;
            // @todo trouble with naming here
            QColor m_correctWordColor;
            QColor m_incorrectWordColor;
            QColor m_notTypedWord;


        private:

            enum class WordTypeMode {
                CorrectTypedWord,
                IncorrectTypedWord,
                NotTypedWord
            };

            using LineNumber = int;
            using WordNumber = int;
            using LineText   = QString;
            using WordIndex  = QPair<LineNumber, WordNumber>;

            friend class RendereeGuard;
            struct RendererGuard {
                RendererGuard(TextEditRenderer * renderer) : m_renderer(renderer) {
                    if ( m_renderer ) m_renderer->startRendering();
                }
                ~RendererGuard() {
                    if ( m_renderer ) m_renderer->stopRendering();
                }

            private:
                TextEditRenderer * m_renderer;
            };

        private:

            bool m_isRendering;
            QMap<WordIndex, WordTypeMode> m_typedWordInfo;
            QMap<LineNumber, LineText> m_lines;
            LineNumber m_currentLine;
            WordNumber m_typedWordInLine;
            LineText m_typedText;
        };
    }
}
