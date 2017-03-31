#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>

#include <QObject>
#include <map>
class ImageProvider : public QQuickImageProvider
{

public:
    explicit ImageProvider():QQuickImageProvider(QQuickImageProvider::Image){

    }
    QImage requestImage(const QString &id, QSize *size, const QSize &) override
    {
        auto&& t=image_map[id];
        *size=t.size();
        return t;
    }
    std::map<QString,QImage> image_map;
signals:

public slots:
};

#endif // IMAGEPROVIDER_H
