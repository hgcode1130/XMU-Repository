#include "callrecordroles.h"

int CallRecordModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return m_records.size();
}

QVariant CallRecordModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_records.size())
      return QVariant();

    const CallRecord &record = m_records.at(index.row());
    switch (role) {
      case IdRole: return record.id;
      case CallTypeRole: return record.callType;
      case PhoneNumberRole: return record.phoneNumber;
      case CallTimeRole: return record.callTime;
      case CallDurationRole: return record.callDuration;
      default: return QVariant();
    }
}

QHash<int, QByteArray> CallRecordModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[CallTypeRole] = "callType";
    roles[PhoneNumberRole] = "phoneNumber";
    roles[CallTimeRole] = "callTime";
    roles[CallDurationRole] = "callDuration";
    return roles;
}

void CallRecordModel::getCallRecords() {
    EC20*ec20 = new EC20();
    QString imei = ec20->getImei();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("imei_db.db");
    if (!db.open()) {
      qDebug() << "Can't open database:" << db.lastError();
      return;
    }

    QString call_info_table = QString("CALL_INFO_%1").arg(imei);
    QSqlQuery query(QString("SELECT * FROM '%1';").arg(call_info_table), db);

    beginResetModel();
    m_records.clear();

    while (query.next()) {
      CallRecord record;
      record.id = query.value("ID").toInt();
      record.callType = query.value("CallType").toString();
      record.phoneNumber = query.value("PhoneNumber").toString();
      record.callTime = query.value("CallTime").toString();
      record.callDuration = query.value("CallDuration").toString();
      m_records.append(record);
    }

    endResetModel();
    db.close();
}
