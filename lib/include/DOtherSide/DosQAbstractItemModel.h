#pragma once

// Qt
#include <QAbstractItemModel>
// DOtherSide
#include "DOtherSide/DOtherSideTypes.h"
#include "DOtherSide/DosIQAbstractItemModelImpl.h"
#include "DOtherSide/OnSlotExecutedHandler.h"

namespace DOS {

template<class T>
class DosQAbstractGenericModel : public T, public DosIQAbstractItemModelImpl
{
public:
    /// Constructor
    DosQAbstractGenericModel(void *modelObject,
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
                             ParentCallback parentCallback);

    /// @see IDynamicQObject::emitSignal
    bool emitSignal(QObject *emitter, const QString &name, const std::vector<QVariant> &argumentsValues) override;

    /// @see QAbstractItemModel::metaObject()
    const QMetaObject *metaObject() const override;

    /// @see QAbstractItemModel::qt_metacall
    int qt_metacall(QMetaObject::Call, int, void **) override;

    /// Return the model's row count
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /// Return the model's column count
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /// Return the QVariant at the given index
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /// Sets the QVariant value at the given index and role
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    /// Return the item flags for the given index
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /// Return the data for the given role and section in the header with the specified orientation
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    /// Return the index associated at the given row and column
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;

    /// Return the parent for the given child index
    QModelIndex parent(const QModelIndex &child) const override;

    /// Return the dModelPointer
    void *modelObject();

    /// Return the roleNames
    QHash<int, QByteArray> roleNames() const override;

    /// Expose beginInsertRows
    void publicBeginInsertRows(const QModelIndex &index, int first, int last) override;

    /// Expose endInsertRows
    void publicEndInsertRows() override;

    /// Expose beginRemoveRows
    void publicBeginRemoveRows(const QModelIndex &index, int first, int last) override;

    /// Expose endInsertRows
    void publicEndRemoveRows() override;

    /// Expose beginInsertColumns
    void publicBeginInsertColumns(const QModelIndex &index, int first, int last) override;

    /// Expose endInsertColumns
    void publicEndInsertColumns() override;

    /// Expose beginRemoveColumns
    void publicBeginRemoveColumns(const QModelIndex &index, int first, int last) override;

    /// Expose endInsertColumns
    void publicEndRemoveColumns() override;

    /// Expose beginResetModel
    void publicBeginResetModel() override;

    /// Expose endResetModel
    void publicEndResetModel() override;

    /// Expose dataChanged
    void publicDataChanged(const QModelIndex &topLeft,
                           const QModelIndex &bottomRight,
                           const QVector<int> &roles = QVector<int>()) override;

    /// Expose createIndex
    QModelIndex publicCreateIndex(int row, int column, void *data = nullptr) const override;

private:
    std::unique_ptr<DosIQObjectImpl> m_impl;
    void *m_modelObject;
    RowCountCallback m_rowCountCallback;
    ColumnCountCallback m_columnCountCallback;
    DataCallback m_dataCallback;
    SetDataCallback m_setDataCallback;
    RoleNamesCallback m_roleNamesCallback;
    FlagsCallback m_flagsCallback;
    HeaderDataCallback m_headerDataCallback;
    IndexCallback m_indexCallback;
    ParentCallback m_parentCallback;
};


using DosQAbstractItemModel = DosQAbstractGenericModel<QAbstractItemModel>;
using DosQAbstractListModel = DosQAbstractGenericModel<QAbstractListModel>;
using DosQAbstractTableModel = DosQAbstractGenericModel<QAbstractTableModel>;

} // namespace DOS
