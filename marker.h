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
	double m_realHeight=0;
	double m_realWidth=0;
	int m_r = 0;
	int m_g = 0;
	int m_b = 0;
	int m_penSize = 0;
    QColor c;
    bool m_dirty=false;
public:
	explicit Marker(ImageProvider* i);

    Q_INVOKABLE void saveImageB();

	Q_INVOKABLE void draw(int x, int y);

	QString aDir() const;

	QString bDir() const;

	QString filename() const;

	double realHeight() const;

	double realWidth() const;

	int r() const;

	int g() const;

	int b() const;

	int penSize() const;

	bool dirty() const;

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
	void setADir(QString aDir);

	void setBDir(QString bDir);
	
	void loadImageB();

	void setFilename(QString filename);

	void setRealHeight(double realHeight);

	void setRealWidth(double realWidth);

	void setR(int r);

	void setG(int g);

	void setB(int b);

	void setPenSize(int penSize);

	void setDirty(bool dirty);
};

#endif // MARKER_H
