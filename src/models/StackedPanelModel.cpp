/**
 * HPX Stacked Panel - A fully stylized StackedWidget implementation
 *
 * Copyright (C) 2019  Sébastien Demanou
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "components/StackedPanelWidget.h"
#include "components/StackedPanelToolbox.h"
#include "models/StackedPanelModel.h"
#include "models/StackedPanelItem.h"

namespace HPX {
  StackedPanelModel::StackedPanelModel(QObject* parent): QStandardItemModel(parent) {
    setItemRoleNames({
      { StackedPanelItem::NameRole, "name" },
      { StackedPanelItem::WidgetRole, "widget" }
    });
  }

  void StackedPanelModel::appendRow(StackedPanelItem* item) {
    QStandardItemModel::appendRow(item);
  }

  QString StackedPanelModel::name(int pos) const {
    return name(index(pos, 0));
  }

  QString StackedPanelModel::name(const QModelIndex& index) const {
    return data(index, StackedPanelItem::NameRole).value<QString>();
  }

  StackedPanelWidget* StackedPanelModel::widget(int pos) const {
    return widget(index(pos, 0));
  }

  StackedPanelWidget* StackedPanelModel::widget(const QModelIndex& index) const {
    return data(index, StackedPanelItem::WidgetRole).value<StackedPanelWidget*>();
  }

  QModelIndex StackedPanelModel::sibling(int row, int column, const QModelIndex& idx) const {
    if (rowCount() == 0) {
      return QStandardItemModel::sibling(row, column, idx);
    }

    if (row >= rowCount()) {
      return sibling(row - 1, column, idx);
    }

    if (row < 0) {
      return sibling(row + 1, column, idx);
    }

    return QStandardItemModel::sibling(row, column, idx);
  }
}  // namespace HPX
