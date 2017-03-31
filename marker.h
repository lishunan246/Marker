#ifndef MARKER_H
#define MARKER_H

#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

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
	QString m_aDir = "";
	QString m_bDir = "";
	QString m_filename = "";
    ImageProvider* ip;
    double m_realHeight;

    double m_realWidth;

public:
	explicit Marker(ImageProvider* i, QObject* parent = nullptr): ip(i)
	{
	}

	Q_INVOKABLE void draw(int x, int y)
	{
        qDebug()<< x << " " << y;
		auto&& image_a = ip->image_map["a"];
		auto&& image_b = ip->image_map["b"];
        x=x/m_realWidth*(image_a.size().width());
		y = y / m_realHeight*image_a.size().height();

		image_b.setPixel(x, y, 0xffffff);

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

signals :

	void aDirChanged(QString aDir);

	void bDirChanged(QString bDir);

	void filenameChanged(QString filename);

    void realHeightChanged(double realHeight);

    void realWidthChanged(double realWidth);

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
		auto b = m_bDir.startsWith("file:///")?m_bDir.mid(8):m_bDir;
		ip->image_map["b"].save(QDir(b).filePath(m_filename));
		m_filename = filename;

		if (m_filename.isEmpty() == false)
		{
			auto&& image = ip->image_map["a"];

			auto a_path = QDir(a).filePath(m_filename);
			QFileInfo c(a_path);
			if (c.exists() == false)
				throw "can not open file";
			image.load(a_path);

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
};

#endif // MARKER_H
