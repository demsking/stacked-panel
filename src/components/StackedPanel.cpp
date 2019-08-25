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

#include "components/StackedPanel.h"

#include <QStyle>
#include <QEvent>
#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QCoreApplication>

#include <stdexcept>

#include "components/StackedPanelBar.h"
#include "components/StackedPanelWidget.h"

#include "models/StackedPanelItem.h"
#include "models/StackedPanelModel.h"

namespace HPX {
  StackedPanel::StackedPanel(QWidget* parent): QFrame(parent) {
    setProperty("StackedPanel", true);

    _mainLayout = new QVBoxLayout(this);
    _panelBar = new StackedPanelBar(this);
    _stackedWidget = new QStackedWidget(this);

    _mainLayout->setMargin(0);
    _mainLayout->setSpacing(0);
    _mainLayout->setContentsMargins(QMargins());
    _mainLayout->addWidget(_panelBar);
    _mainLayout->addWidget(_stackedWidget);

    _stackedWidget->setProperty("StackedPanelContainer", true);

    connect(_panelBar, &StackedPanelBar::currentChanged, _stackedWidget, &QStackedWidget::setCurrentIndex);
    connect(_panelBar, &StackedPanelBar::currentChanged, this, &StackedPanel::currentChanged);
    connect(_stackedWidget, &QStackedWidget::currentChanged, this, [this](int pos) {
      QWidget* widget = _stackedWidget->widget(pos);

      if (widget) {
        setFocusProxy(widget);
        widget->setFocus();
      }
    });
  }

  StackedPanelModel* StackedPanel::model() const {
    return _model;
  }

  void StackedPanel::setModel(StackedPanelModel* model) {
    if (_model != nullptr) {
      _model->disconnect(this);
    }

    _model = model;

    connect(model, &StackedPanelModel::rowsInserted, this, &StackedPanel::onDataInsert);
    connect(model, &StackedPanelModel::rowsAboutToBeRemoved, this, &StackedPanel::onDataAboutRemove);
    connect(model, &StackedPanelModel::rowsRemoved, this, &StackedPanel::onDataRemove);
    connect(model, &StackedPanelModel::dataChanged, this, &StackedPanel::onDataChange);

    _panelBar->setModel(model);
  }

  StackedPanelWidget* StackedPanel::widget(int index) const {
    return _model->widget(index);
  }

  StackedPanelWidget* StackedPanel::currentWidget() const {
    return widget(currentIndex());
  }

  int StackedPanel::indexOf(StackedPanelWidget* widget) {
    return _stackedWidget->indexOf(widget);
  }

  int StackedPanel::currentIndex() const {
    return _stackedWidget->currentIndex();
  }

  void StackedPanel::setCurrentIndex(int index) {
    _panelBar->setCurrentIndex(index);
  }

  void StackedPanel::setCurrentWidget(StackedPanelWidget* widget) {
    const int index = indexOf(widget);

    if (index > -1) {
      setCurrentIndex(index);
    }
  }

  void StackedPanel::setFocus(bool focused) {
    setProperty("focused", focused);

    style()->unpolish(this);
    style()->polish(this);

    currentWidget()->style()->unpolish(this);
    currentWidget()->style()->polish(this);

    if (focused) {
      emit focusIn();
    } else {
      emit focusOut();
    }
  }

  void StackedPanel::connectWidget(StackedPanelWidget* widget) {
    connect(widget, &StackedPanelWidget::focusIn, this, [this, widget]() {
      const int pos = _stackedWidget->indexOf(widget);

      if (pos != currentIndex()) {
        setCurrentIndex(pos);
      }

      setFocus(true);
    });

    connect(widget, &StackedPanelWidget::focusOut, this, [this]() {
      setFocus(false);
    });
  }

  void StackedPanel::onDataInsert(const QModelIndex& parent, int first, int last) {
    Q_UNUSED(parent)

    for (int i = first; i <= last; i++) {
      StackedPanelWidget* widget = _model->widget(i);

      if (widget == nullptr) {
        throw std::invalid_argument("StackedPanelItem::widget cannot be a nullptr");
      }

      _stackedWidget->insertWidget(i, widget);
      connectWidget(widget);
    }
  }

  void StackedPanel::onDataAboutRemove(const QModelIndex& parent, int first, int last) {
    Q_UNUSED(parent)

    for (int i = last; i >= first; i--) {
      StackedPanelWidget* widget = _model->widget(i);

      widget->disconnect(this);
      _stackedWidget->removeWidget(widget);
    }
  }

  void StackedPanel::onDataRemove(const QModelIndex& parent, int first, int last) {
    Q_UNUSED(parent)
    Q_UNUSED(first)
    Q_UNUSED(last)

    if (_panelBar->currentIndex() > -1) {
      setCurrentIndex(_panelBar->currentIndex());
    }
  }

  void StackedPanel::onDataChange(const QModelIndex& topLeft,
                                  const QModelIndex& bottomRight,
                                  const QVector<int>& roles) {
    Q_UNUSED(bottomRight)

    if (!topLeft.isValid()) {
      return;
    }

    for (const int& role: roles) {
      auto roleEnum = static_cast<StackedPanelItem::Role>(role);

      if (roleEnum == StackedPanelItem::Role::WidgetRole) {
        const int pos = topLeft.row();
        QWidget* widget = _stackedWidget->widget(pos);
        StackedPanelWidget* newWidget = _model->widget(topLeft);
        const int currentPos = currentIndex();

        widget->disconnect(this);

        _stackedWidget->insertWidget(pos, newWidget);
        _stackedWidget->setCurrentIndex(pos + 1);
        _stackedWidget->removeWidget(widget);
        _stackedWidget->setCurrentIndex(currentPos);

        connectWidget(newWidget);
      }
    }
  }
}  // namespace HPX
