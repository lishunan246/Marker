#include "marker.h"

Marker::Marker(ImageProvider* i): ip(i), c(0, 0, 0)
{
}

void Marker::saveImageB()
{
	auto b = m_bDir.startsWith("file:///") ? m_bDir.mid(8) : m_bDir;
	ip->image_map["b"].save(QDir(b).filePath(m_filename));
	setDirty(false);
}

void Marker::draw(int x, int y)
{
	qDebug() << x << " " << y;
	auto&& image_a = ip->image_map["a"];
	auto&& image_b = ip->image_map["b"];
	auto&& image_origin = ip->image_map["c"];
	x = round(1.0 * x / m_realWidth * image_a.size().width());
	y = round(1.0 * y / m_realHeight * image_a.size().height());
	for (int i = x - penSize(); i <= x + penSize(); ++i)
		for (int j = y - penSize(); j <= y + penSize(); ++j)
		{
			image_b.setPixelColor(i, j, c);
			image_a.setPixelColor(i, j, c == QColor(255, 255, 255) ? image_origin.pixelColor(i, j) : c);
		}
	setDirty(true);
}

QString Marker::aDir() const
{
	return m_aDir;
}

QString Marker::bDir() const
{
	return m_bDir;
}

QString Marker::filename() const
{
	return m_filename;
}

double Marker::realHeight() const
{
	return m_realHeight;
}

double Marker::realWidth() const
{
	return m_realWidth;
}

int Marker::r() const
{
	return m_r;
}

int Marker::g() const
{
	return m_g;
}

int Marker::b() const
{
	return m_b;
}

int Marker::penSize() const
{
	return m_penSize;
}

bool Marker::dirty() const
{
	return m_dirty;
}

void Marker::setADir(QString aDir)
{
	if (m_aDir == aDir)
		return;

	m_aDir = aDir;
	emit aDirChanged(aDir);
}

void Marker::setBDir(QString bDir)
{
	if (m_bDir == bDir)
		return;

	m_bDir = bDir;
	emit bDirChanged(bDir);
}

void Marker::setFilename(QString filename)
{
	if (m_filename == filename)
		return;
	auto a = m_aDir.startsWith("file:///") ? m_aDir.mid(8) : m_aDir;
	auto b = m_bDir.startsWith("file:///") ? m_bDir.mid(8) : m_bDir;
	auto&& image_b = ip->image_map["b"];
	auto&& image_a = ip->image_map["a"];
	auto old_path_b = QDir(b).filePath(m_filename);
	auto old_path_a = QDir(a).filePath(m_filename);
	image_b.save(old_path_b);
	setDirty(false);
	m_filename = filename;

	if (m_filename.isEmpty() == false)
	{
		
		auto path_a = QDir(a).filePath(m_filename);
		auto path_b = QDir(b).filePath(m_filename);
		QFileInfo c(path_a);
		if (c.exists() == false)
			throw "can not open file";
		image_a.load(path_a);
		ip->image_map["c"] = image_a.copy();

		QFileInfo check_file(path_b);
		if (check_file.exists() && check_file.isFile())
		{
			image_b.load(path_b);
			if (image_a.size() != image_b.size())
			{
				qDebug() << image_a.size() << " " << image_b.size();
				image_b = QImage(image_a.size(), image_a.format());
				image_b.fill(QColor(255, 255, 255));
			}
			else
			{
				for (int i = 0; i < image_a.size().width(); ++i)
					for (int j = 0; j < image_b.size().height(); ++j)
					{
						auto&& pixel_color = image_b.pixelColor(i, j);
						if (pixel_color != QColor(255, 255, 255))
							image_a.setPixelColor(i, j, pixel_color);
					}
			}
		}
		else
		{
			image_b = QImage(image_a.size(), image_a.format());
			image_b.fill(QColor(255, 255, 255));
		}
	}
	emit filenameChanged(filename);
}

void Marker::setRealHeight(double realHeight)
{
	if (m_realHeight == realHeight)
		return;

	m_realHeight = realHeight;
	emit realHeightChanged(realHeight);
}

void Marker::setRealWidth(double realWidth)
{
	if (m_realWidth == realWidth)
		return;

	m_realWidth = realWidth;
	emit realWidthChanged(realWidth);
}

void Marker::setR(int r)
{
	if (m_r == r)
		return;

	m_r = r;
	c = QColor(m_r, m_g, m_b);
	emit rChanged(r);
}

void Marker::setG(int g)
{
	if (m_g == g)
		return;

	m_g = g;
	c = QColor(m_r, m_g, m_b);
	emit gChanged(g);
}

void Marker::setB(int b)
{
	if (m_b == b)
		return;

	m_b = b;
	c = QColor(m_r, m_g, m_b);
	emit bChanged(b);
}

void Marker::setPenSize(int penSize)
{
	if (m_penSize == penSize)
		return;

	m_penSize = penSize;
	emit penSizeChanged(penSize);
}

void Marker::setDirty(bool dirty)
{
	if (m_dirty == dirty)
		return;

	m_dirty = dirty;
	emit dirtyChanged(dirty);
}
