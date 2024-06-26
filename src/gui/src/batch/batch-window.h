#ifndef BATCH_WINDOW_H
#define BATCH_WINDOW_H

#include <QDialog>
#include <QList>
#include <QMap>
#include <QSize>
#include "exponential-moving-average.h"
#include "loader/downloadable.h"


class QProgressBar;
class QSettings;
#ifdef Q_OS_WIN
	class QWinTaskbarButton;
	class QWinTaskbarProgress;
#endif


namespace Ui
{
	class BatchWindow;
}


class QElapsedTimer;

class BatchWindow : public QDialog
{
	Q_OBJECT

	public:
		explicit BatchWindow(QSettings *settings, QWidget *parent = nullptr);
		~BatchWindow() override;
		int currentValue() const;
		int currentMax() const;
		int totalValue() const;
		int totalMax() const;
		int endAction() const;
		int indexOf(const QUrl &url);
		int batch(const QUrl &url);
		void setCount(int);
		void updateColumns();
		bool endRemove() const;
		bool cancelled() const;
		bool isPaused() const;

	public slots:
		void clear();
		void clearImages();
		void setText(const QString &text);
		void setCurrentValue(int val);
		void setCurrentMax(int max);
		void setTotalValue(int val);
		void setTotalMax(int max);
		void addImage(const QUrl &url, int batch, double size);
		void sizeImage(const QUrl &url, double size);
		void loadingImage(const QUrl &url);
		void statusImage(const QUrl &url, int percent);
		void speedImage(const QUrl &url, double speed);
		void loadedImage(const QUrl &url, Downloadable::SaveResult result);
		void toggleDetails(bool visible);
		void closeEvent(QCloseEvent *event) override;
		void copyToClipboard();
		void cancel();
		void drawSpeed();
		void imageUrlChanged(const QUrl &before, const QUrl &after);
		void scrollTo(int i);
		void pause();
		void skip();

	signals:
		void closed();
		void paused();
		void skipped();

	private:
		Ui::BatchWindow *ui;
		QSettings *m_settings;
		QSize m_currentSize;
		int m_imagesCount, m_items, m_images, m_maxSpeeds, m_lastDownloading;
		QMap<QUrl, QList<int>> m_urls;
		QList<QProgressBar*> m_progressBars;
		QMap<QUrl, ExponentialMovingAverage> m_speeds;
		ExponentialMovingAverage m_mean;
		bool m_cancel, m_paused;
		QElapsedTimer *m_time, *m_start;
		#ifdef Q_OS_WIN
			QWinTaskbarButton *m_taskBarButton;
			QWinTaskbarProgress *m_taskBarProgress;
		#endif
};

#endif // BATCH_WINDOW_H
