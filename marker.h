#ifndef MARKER_H
#define MARKER_H

#include <QObject>
#include <QString>

class Marker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString aDir READ aDir WRITE setADir NOTIFY aDirChanged)
    Q_PROPERTY(QString bDir READ bDir WRITE setBDir NOTIFY bDirChanged)
    Q_PROPERTY(QString filename READ filename WRITE setFilename NOTIFY filenameChanged)

    QString m_aDir="";
    QString m_bDir="";
    QString m_filename="";

public:
    explicit Marker(QObject *parent = 0);

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

signals:

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

        m_filename = filename;
        emit filenameChanged(filename);
    }
};

#endif // MARKER_H
