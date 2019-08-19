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

#ifndef HPXSTACKEDPANEL_MODELS_TABVIEWMODEL_H_
#define HPXSTACKEDPANEL_MODELS_TABVIEWMODEL_H_

#include <QStandardItemModel>

#include "global.h"  // NOLINT(build/include)

namespace HPX {
  class StackedPanelToolbox;
  class StackedPanelItem;
  class StackedPanelWidget;

  class LIBHPXSTACKEDPANEL_EXPORT StackedPanelModel: public QStandardItemModel {
    Q_OBJECT

    public:
      explicit StackedPanelModel(QObject* parent = nullptr);

      void add(StackedPanelItem*);
      int count() const;

      QString name(int pos) const;
      QString name(const QModelIndex&) const;

      StackedPanelToolbox* toolbox(int pos) const;
      StackedPanelToolbox* toolbox(const QModelIndex&) const;

      StackedPanelWidget* widget(int pos) const;
      StackedPanelWidget* widget(const QModelIndex&) const;

      QModelIndex sibling(int row, int column, const QModelIndex& = QModelIndex()) const override;
  };
} // namespace HPX

#endif // HPXSTACKEDPANEL_MODELS_TABVIEWMODEL_H_
