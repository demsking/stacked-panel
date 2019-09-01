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

#ifndef HPXSTACKEDPANEL_MODELS_TABVIEWITEM_H_
#define HPXSTACKEDPANEL_MODELS_TABVIEWITEM_H_

#include <QStandardItem>

#include "global.h"  // NOLINT(build/include)

namespace HPX {
  class StackedPanelToolbox;
  class StackedPanelWidget;

  class LIBHPXSTACKEDPANEL_EXPORT StackedPanelItem: public QStandardItem {
    public:
      enum Role {
        NameRole = Qt::DisplayRole,
        WidgetRole = Qt::UserRole + 9099,
        UserRole
      };

    public:
      StackedPanelItem(const QString& name, StackedPanelWidget*);

      StackedPanelItem() = delete;
      explicit StackedPanelItem(const QString &text) = delete;
      StackedPanelItem(const QIcon &icon, const QString &text) = delete;
      explicit StackedPanelItem(int rows, int columns = 1) = delete;

      int type() const override;

      QString name() const;
      void setName(const QString&);

      StackedPanelWidget* widget() const;
      void setWidget(StackedPanelWidget*);
  };
} // namespace HPX

#endif // HPXSTACKEDPANEL_MODELS_TABVIEWITEM_H_
