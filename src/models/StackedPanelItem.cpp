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

#include "models/StackedPanelItem.h"
#include "models/StandarItemType.h"
#include "components/StackedPanel.h"
#include "components/StackedPanelWidget.h"
#include "components/StackedPanelToolbox.h"

namespace HPX {
  int StackedPanelItem::type() const {
    return StandarItemType::StackedPanel;
  }

  QString StackedPanelItem::name() const {
    return data(Role::NameRole).value<QString>();
  }

  void StackedPanelItem::setName(const QString& value) {
    setData(value, Role::NameRole);
  }

  StackedPanelWidget* StackedPanelItem::widget() const {
    return data(Role::WidgetRole).value<StackedPanelWidget*>();
  }

  void StackedPanelItem::setWidget(StackedPanelWidget* widget) {
    setData(QVariant::fromValue(widget), Role::WidgetRole);
  }
} // namespace HPX
