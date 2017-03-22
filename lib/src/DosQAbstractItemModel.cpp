#include "DOtherSide/DosQAbstractItemModel.h"
#include "DOtherSide/DosQObjectImpl.h"

namespace {

template<class T>
DOS::DosQObjectImpl::ParentMetaCall createParentMetaCall(DOS::DosQAbstractGenericModel<T> *parent)
{
    return [parent](QMetaObject::Call callType, int index, void **args)->int {
        return parent->T::qt_metacall(callType, index, args);
    };
}

}

namespace DOS {

template<class T>
DosQAbstractGenericModel<T>::DosQAbstractGenericModel(void *modelObject,
                                                      DosIQMetaObjectPtr metaObject,
                                                      OnSlotExecuted onSlotExecuted,
                                                      RowCountCallback rowCountCallback,
                                                      ColumnCountCallback columnCountCallback,
                                                      DataCallback dataCallback,
                                                      SetDataCallback setDataCallback,
                                                      RoleNamesCallback roleNamesCallback,
                                                      FlagsCallback flagsCallback,
                                                      HeaderDataCallback headerDataCallback,
                                                      IndexCallback indexCallback,
                                                      ParentCallback parentCallback)
    : m_impl(new DosQObjectImpl(this, ::createParentMetaCall(this), std::move(metaObject), std::move(onSlotExecuted)))
    , m_modelObject(std::move(modelObject))
    , m_rowCountCallback(std::move(rowCountCallback))
    , m_columnCountCallback(std::move(columnCountCallback))
    , m_dataCallback(std::move(dataCallback))
    , m_setDataCallback(std::move(setDataCallback))
    , m_roleNamesCallback(std::move(roleNamesCallback))
    , m_flagsCallback(std::move(flagsCallback))
    , m_headerDataCallback(std::move(headerDataCallback))
    , m_indexCallback(std::move(indexCallback))
    , m_parentCallback(std::move(parentCallback))
{}

template<class T>
bool DosQAbstractGenericModel<T>::emitSignal(QObject *emitter, const QString &name, const std::vector<QVariant> &argumentsValues)
{
    Q_ASSERT(m_impl);
    return m_impl->emitSignal(emitter, name, argumentsValues);
}

template<class T>
const QMetaObject *DosQAbstractGenericModel<T>::metaObject() const
{
    Q_ASSERT(m_impl);
    return m_impl->metaObject();
}

template<class T>
int DosQAbstractGenericModel<T>::qt_metacall(QMetaObject::Call call, int index, void **args)
{
    Q_ASSERT(m_impl);
    return m_impl->qt_metacall(call, index, args);
}

template<class T>
int DosQAbstractGenericModel<T>::rowCount(const QModelIndex &parent) const
{
    int result;
    m_rowCountCallback(m_modelObject, &parent, &result);
    return result;
}

template<class T>
int DosQAbstractGenericModel<T>::columnCount(const QModelIndex &parent) const
{
    int result;
    m_columnCountCallback(m_modelObject, &parent, &result);
    return result;
}

template<class T>
QVariant DosQAbstractGenericModel<T>::data(const QModelIndex &index, int role) const
{
    QVariant result;
    m_dataCallback(m_modelObject, &index, role, &result);
    return result;
}

template<class T>
bool DosQAbstractGenericModel<T>::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool result = false;
    m_setDataCallback(m_modelObject, &index, &value, role, &result);
    return result;
}

template<class T>
Qt::ItemFlags DosQAbstractGenericModel<T>::flags(const QModelIndex &index) const
{
    int result;
    m_flagsCallback(m_modelObject, &index, &result);
    return Qt::ItemFlags(result);
}

template<class T>
QVariant DosQAbstractGenericModel<T>::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant result;
    m_headerDataCallback(m_modelObject, section, orientation, role, &result);
    return result;
}

template<class T>
QModelIndex DosQAbstractGenericModel<T>::index(int row, int column, const QModelIndex &parent) const
{
    QModelIndex result;
    m_indexCallback(m_modelObject, row, column, &parent, &result);
    return result;
}

template<class T>
QModelIndex DosQAbstractGenericModel<T>::parent(const QModelIndex &child) const
{
    QModelIndex result;
    m_parentCallback(m_modelObject, &child, &result);
    return result;
}

template<class T>
void *DosQAbstractGenericModel<T>::modelObject()
{
    return m_modelObject;
}

template<class T>
QHash<int, QByteArray> DosQAbstractGenericModel<T>::roleNames() const
{
    QHash<int, QByteArray> result;
    m_roleNamesCallback(m_modelObject, &result);
    return result;
}

template<class T>
void DosQAbstractGenericModel<T>::publicBeginInsertColumns(const QModelIndex &index, int first, int last)
{
    T::beginInsertColumns(index, first, last);
}

template<class T>
void DosQAbstractGenericModel<T>::publicEndInsertColumns()
{
    T::endInsertColumns();
}

template<class T>
void DosQAbstractGenericModel<T>::publicBeginRemoveColumns(const QModelIndex &index, int first, int last)
{
    T::beginRemoveColumns(index, first, last);
}

template<class T>
void DosQAbstractGenericModel<T>::publicEndRemoveColumns()
{
    T::endRemoveColumns();
}
template<class T>
void DosQAbstractGenericModel<T>::publicBeginInsertRows(const QModelIndex &index, int first, int last)
{
    T::beginInsertRows(index, first, last);
}

template<class T>
void DosQAbstractGenericModel<T>::publicEndInsertRows()
{
    T::endInsertRows();
}

template<class T>
void DosQAbstractGenericModel<T>::publicBeginRemoveRows(const QModelIndex &index, int first, int last)
{
    T::beginRemoveRows(index, first, last);
}

template<class T>
void DosQAbstractGenericModel<T>::publicEndRemoveRows()
{
    T::endRemoveRows();
}

template<class T>
void DosQAbstractGenericModel<T>::publicBeginResetModel()
{
    T::beginResetModel();
}

template<class T>
void DosQAbstractGenericModel<T>::publicEndResetModel()
{
    T::endResetModel();
}

template<class T>
void DosQAbstractGenericModel<T>::publicDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    emit T::dataChanged(topLeft, bottomRight, roles);
}

template<class T>
QModelIndex DosQAbstractGenericModel<T>::publicCreateIndex(int row, int column, void *data) const
{
    return T::createIndex(row, column, data);
}

} // namespace DOS

// Force instantiation
template class DOS::DosQAbstractGenericModel<QAbstractItemModel>;
template class DOS::DosQAbstractGenericModel<QAbstractListModel>;
template class DOS::DosQAbstractGenericModel<QAbstractTableModel>;
