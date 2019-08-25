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

#include <QVariant> // required for setProperty
#include "components/StackedPanelToolbox.h"

namespace HPX {
  StackedPanelWidget::StackedPanelWidget(QWidget* parent): QWidget(parent) {
    setProperty("StackedPanelWidget", true);
    _toolbox.reset(new StackedPanelToolbox(this));

    connect(this, &StackedPanelWidget::focusIn, this, [this]() {
      _active = true;
    });

    connect(this, &StackedPanelWidget::focusOut, this, [this]() {
      _active = false;
    });
  }

  QSharedPointer<StackedPanelToolbox> StackedPanelWidget::toolbox() {
    return _toolbox;
  }

  void StackedPanelWidget::setFocus() {
    QWidget::setFocus();
    emit focusIn();
  }

  bool StackedPanelWidget::isActive() const {
    return _active;
  }
}  // namespace HPX
