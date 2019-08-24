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

#include "components/StackedPanelToolbox.h"

#include <QFrame>
#include <QWidget>
#include <QVariant> // required for setProperty
#include <QHBoxLayout>
#include <QAbstractButton>

namespace HPX {
  StackedPanelToolbox::StackedPanelToolbox(QWidget* parent): QFrame(parent) {
    _layout = new QHBoxLayout(this);

    _layout->setMargin(0);
    _layout->setSpacing(0);
    _layout->setContentsMargins(QMargins());

    setProperty("StackedPanelToolBox", true);
  }

  StackedPanelToolbox::~StackedPanelToolbox() {
    delete _layout;
  }

  int StackedPanelToolbox::count() const {
    return _layout->count();
  }

  QSize StackedPanelToolbox::sizeHint() const {
    return QSize(count() * 35, height());
  }

  QSize StackedPanelToolbox::minimumSizeHint() const {
    return QSize(count() * 35, height());
  }

  QAbstractButton* StackedPanelToolbox::takeAt(int index) const {
    auto widget = _layout->takeAt(index)->widget();

    return static_cast<QAbstractButton*>(widget);
  }

  void StackedPanelToolbox::addButton(QAbstractButton* button) {
    button->setProperty("StackedPanelToolBoxButton", true);

    _layout->insertWidget(0, button);
  }

  void StackedPanelToolbox::removeButton(QAbstractButton* button) {
    _layout->removeWidget(button);
  }
}  // namespace HPX
