#ifndef CALLRECORDROLES_H
#define CALLRECORDROLES_H

#include <QAbstractListModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <ec20.h>


class CallRecordModel : public QAbstractListModel
{
  Q_OBJECT

public:
  enum CallRecordRoles {
    IdRole = Qt::UserRole + 1,
    CallTypeRole,
    PhoneNumberRole,
    CallTimeRole,
    CallDurationRole
  };

  struct CallRecord {
    int id;
    QString callType;
    QString phoneNumber;
    QString callTime;
    QString callDuration;
  };


  explicit CallRecordModel(QObject *parent = nullptr){};

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

  Q_INVOKABLE void getCallRecords();

private:
  QList<CallRecord> m_records; // Assume CallRecord is a struct or class that holds one record's data
};


#endif // CALLRECORDROLES_H
