#ifndef MARKER_H
#define MARKER_H

#include <QObject>
#include <QString>
#include <QFileInfo>
#include <QDir>
#include <iostream>
#include "imageprovider.h"

class Marker : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString aDir READ aDir WRITE setADir NOTIFY aDirChanged)
	Q_PROPERTY(QString bDir READ bDir WRITE setBDir NOTIFY bDirChanged)
	Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)

	QString m_aDir = "";
	QString m_bDir = "";
	QString m_filename = "";
	ImageProvider* ip;
public:
	explicit Marker(ImageProvider* i, QObject* parent = 0): ip(i)
	{
	}

	Q_INVOKABLE void draw(int x, int y)
	{
		std::cout << x << " " << y << std::endl;
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

	signals :

	void aDirChanged(QString aDir);

	void bDirChanged(QString bDir);

	void filenameChanged(QString filename);

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
};

#endif // MARKER_H
