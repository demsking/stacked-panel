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
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include "components/StackedPanelToolbox.h"

namespace HPX {
  StackedPanelWidget::StackedPanelWidget(QWidget* parent): QFrame(parent) {
    _layout = new QVBoxLayout(this);
    _stackedWidget = new QStackedWidget(this);

    setProperty("StackedPanelFrame", true);
    setStateWidget(State::None, new QWidget(this));
    setStateWidget(State::Loading, new QWidget(this));
    setStateWidget(State::Empty, new QWidget(this));
    setStateWidget(State::Ready, new QWidget(this));

    _layout->setMargin(0);
    _layout->setSpacing(0);
    _layout->setContentsMargins(QMargins());
    _layout->addWidget(_stackedWidget);

    _stackedWidget->setProperty("StackedPanelFrameContainer", true);
    _stackedWidget->setCurrentIndex(0);

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

  void StackedPanelWidget::setStateWidget(State state, QWidget* widget) {
    auto index = static_cast<int>(state);
    auto deadWidget = _stackedWidget->widget(index);

    widget->setProperty("StackedPanelFrameWidget", true);
    widget->setProperty("state", index);

    _stackedWidget->insertWidget(index, widget);
    _stackedWidget->setCurrentIndex(index + 1);
    _stackedWidget->removeWidget(deadWidget);
    _stackedWidget->setCurrentIndex(index);
  }

  StackedPanelWidget::State StackedPanelWidget::currentState() const {
    auto index = _stackedWidget->currentIndex();

    return static_cast<State>(index);
  }

  void StackedPanelWidget::setCurrentState(State state) {
    auto index = static_cast<int>(state);

    _stackedWidget->setCurrentIndex(index);
  }
}  // namespace HPX
