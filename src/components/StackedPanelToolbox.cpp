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
#include <QWidgetItem>
#include <QHBoxLayout>
#include <QAbstractButton>

namespace HPX {
  StackedPanelToolbox::StackedPanelToolbox(QWidget* parent): QFrame(parent) {
    _layout = new QHBoxLayout(this);

    _layout->setMargin(0);
    _layout->setSpacing(0);
    _layout->setContentsMargins(QMargins());

    setProperty("StackedPanelToolBox", true);
    setFocusPolicy(Qt::FocusPolicy::NoFocus);
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

  QWidget* StackedPanelToolbox::takeAt(int index) const {
    return _layout->takeAt(index)->widget();
  }

  void StackedPanelToolbox::insertWidget(int index, QWidget* widget, int stretch) {
    widget->setProperty("StackedPanelToolBoxWidget", true);
    widget->setEnabled(_enabled);

    if (dynamic_cast<QAbstractButton*>(widget)) {
      widget->setProperty("StackedPanelToolBoxButton", true);
    }

    _layout->insertWidget(index, widget, stretch);
  }

  void StackedPanelToolbox::addWidget(QWidget* widget, int stretch) {
    insertWidget(0, widget, stretch);
  }

  void StackedPanelToolbox::removeWidget(QWidget* widget) {
    _layout->removeWidget(widget);
  }

  void StackedPanelToolbox::enable() {
    setEnabled(true);
  }

  void StackedPanelToolbox::disable() {
    setDisabled(true);
  }

  void StackedPanelToolbox::setEnabled(bool enabled) {
    _enabled = enabled;

    for (int i = 0; i < _layout->count(); i++) {
      QLayoutItem * const item = _layout->itemAt(i);

      if (dynamic_cast<QWidgetItem*>(item)) {
        item->widget()->setEnabled(enabled);
      }
    }
  }

  void StackedPanelToolbox::setDisabled(bool disabled) {
    setEnabled(!disabled);
  }
}  // namespace HPX
