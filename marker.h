#ifndef MARKER_H
#define MARKER_H

#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QColor>
#include <iostream>
#include "imageprovider.h"

class Marker : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString aDir READ aDir WRITE setADir NOTIFY aDirChanged)
	Q_PROPERTY(QString bDir READ bDir WRITE setBDir NOTIFY bDirChanged)
	Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)
	Q_PROPERTY(double realHeight READ realHeight WRITE setRealHeight NOTIFY realHeightChanged)
	Q_PROPERTY(double realWidth READ realWidth WRITE setRealWidth NOTIFY realWidthChanged)
	Q_PROPERTY(int r READ r WRITE setR NOTIFY rChanged)
	Q_PROPERTY(int g READ g WRITE setG NOTIFY gChanged)
	Q_PROPERTY(int b READ b WRITE setB NOTIFY bChanged)
	Q_PROPERTY(int penSize READ penSize WRITE setPenSize NOTIFY penSizeChanged)
    Q_PROPERTY(bool dirty READ dirty WRITE setDirty NOTIFY dirtyChanged)
	QString m_aDir = "";
	QString m_bDir = "";
	QString m_filename = "";
	ImageProvider* ip;
	double m_realHeight;

	double m_realWidth;

	int m_r = 0;

	int m_g = 0;

	int m_b = 0;

	int m_penSize = 0;
    QColor c;
    bool m_dirty=false;

public:
	explicit Marker(ImageProvider* i, QObject* parent = nullptr): ip(i), c(0, 0, 0)
	{
	}
    Q_INVOKABLE void saveImageB()
    {
        auto b = m_bDir.startsWith("file:///") ? m_bDir.mid(8) : m_bDir;
        ip->image_map["b"].save(QDir(b).filePath(m_filename));
        setDirty(false);
    }

	Q_INVOKABLE void draw(int x, int y)
	{
		qDebug() << x << " " << y;
		auto&& image_a = ip->image_map["a"];
		auto&& image_b = ip->image_map["b"];
		auto&& image_origin = ip->image_map["c"];
		x = round(1.0*x / m_realWidth * image_a.size().width());
		y = round(1.0*y / m_realHeight * image_a.size().height());
		for (int i = x - penSize(); i <= x + penSize(); ++i)
			for (int j = y - penSize(); j <= y + penSize(); ++j)
			{
				image_b.setPixelColor(i, j, c);
				image_a.setPixelColor(i, j, c == QColor(255, 255, 255) ? image_origin.pixelColor(i, j) : c);
			}
        setDirty(true);
	}

	QString aDir() const
	{
		return m_aDir;
	}

	QString bDir() const
	{
		return m_bDir;
	}

	QString filename() const
	{
		return m_filename;
	}

	double realHeight() const
	{
		return m_realHeight;
	}

	double realWidth() const
	{
		return m_realWidth;
	}

	int r() const
	{
		return m_r;
	}

	int g() const
	{
		return m_g;
	}

	int b() const
	{
		return m_b;
	}

	int penSize() const
	{
		return m_penSize;
	}

    bool dirty() const
    {
        return m_dirty;
    }

signals :

	void aDirChanged(QString aDir);

	void bDirChanged(QString bDir);

	void filenameChanged(QString filename);

	void realHeightChanged(double realHeight);

	void realWidthChanged(double realWidth);

	void rChanged(int r);

	void gChanged(int g);

	void bChanged(int b);

	void penSizeChanged(int penSize);

    void dirtyChanged(bool dirty);

public slots:
	void setADir(QString aDir)
	{
		if (m_aDir == aDir)
			return;

		m_aDir = aDir;
		emit aDirChanged(aDir);
	}

	void setBDir(QString bDir)
	{
		if (m_bDir == bDir)
			return;

		m_bDir = bDir;
		emit bDirChanged(bDir);
	}

	void setFilename(QString filename)
	{
		if (m_filename == filename)
			return;
		auto a = m_aDir.startsWith("file:///") ? m_aDir.mid(8) : m_aDir;
		auto b = m_bDir.startsWith("file:///") ? m_bDir.mid(8) : m_bDir;
		ip->image_map["b"].save(QDir(b).filePath(m_filename));
        setDirty(false);
		m_filename = filename;

		if (m_filename.isEmpty() == false)
		{
			auto&& image = ip->image_map["a"];

			auto a_path = QDir(a).filePath(m_filename);
			QFileInfo c(a_path);
			if (c.exists() == false)
				throw "can not open file";
			image.load(a_path);
			ip->image_map["c"] = image.copy();
			auto b_path = QDir(b).filePath(m_filename);
			QFileInfo check_file(b_path);
			if (check_file.exists() && check_file.isFile())
			{
				ip->image_map["b"].load(b_path);
			}
			else
			{
				ip->image_map["b"] = QImage(ip->image_map["a"].size(), ip->image_map["a"].format());
			}
		}
		emit filenameChanged(filename);
	}

	void setRealHeight(double realHeight)
	{
		if (m_realHeight == realHeight)
			return;

		m_realHeight = realHeight;
		emit realHeightChanged(realHeight);
	}

	void setRealWidth(double realWidth)
	{
		if (m_realWidth == realWidth)
			return;

		m_realWidth = realWidth;
		emit realWidthChanged(realWidth);
	}

	void setR(int r)
	{
		if (m_r == r)
			return;

		m_r = r;
		c = QColor(m_r, m_g, m_b);
		emit rChanged(r);
	}

	void setG(int g)
	{
		if (m_g == g)
			return;

		m_g = g;
		c = QColor(m_r, m_g, m_b);
		emit gChanged(g);
	}

	void setB(int b)
	{
		if (m_b == b)
			return;

		m_b = b;
		c = QColor(m_r, m_g, m_b);
		emit bChanged(b);
	}

	void setPenSize(int penSize)
	{
		if (m_penSize == penSize)
			return;

		m_penSize = penSize;
		emit penSizeChanged(penSize);
    }
    void setDirty(bool dirty)
    {
        if (m_dirty == dirty)
            return;

        m_dirty = dirty;
        emit dirtyChanged(dirty);
    }
};

#endif // MARKER_H
