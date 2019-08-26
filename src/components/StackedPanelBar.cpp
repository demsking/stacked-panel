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

#include "components/StackedPanelBar.h"

#include <QTimer>
#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QStackedWidget>

#include "components/StackedPanelFrame.h"
#include "components/StackedPanelToolbox.h"

#include "models/StackedPanelItem.h"
#include "models/StackedPanelModel.h"

static const char* PROPERTY_TOOLBOX_CONTAINER = "StackedPanelBarToolboxContainer";

namespace HPX {
  StackedPanelBar::StackedPanelBar(QWidget* parent): QFrame(parent) {
    setFixedHeight(33);
    setProperty("StackedPanelBar", true);

    _layout = new QHBoxLayout(this);
    _panelCombobox = new QComboBox(this);
    _stackedToolbox = new QStackedWidget(this);

    _panelCombobox->setProperty("StackedPanelBarCombobox", true);
    _stackedToolbox->setProperty(PROPERTY_TOOLBOX_CONTAINER, true);

    _layout->setSpacing(0);
    _layout->setMargin(0);
    _layout->setContentsMargins(QMargins());
    _layout->addWidget(_panelCombobox, 1);
    _layout->addWidget(_stackedToolbox, 0);

    connect(_panelCombobox, qOverload<int>(&QComboBox::currentIndexChanged),
            this, &StackedPanelBar::setCurrentIndex);

    connect(_panelCombobox, qOverload<int>(&QComboBox::currentIndexChanged),
            _stackedToolbox, &QStackedWidget::setCurrentIndex);

    connect(_panelCombobox, qOverload<int>(&QComboBox::currentIndexChanged),
            this, &StackedPanelBar::currentChanged);

    connect(_panelCombobox, qOverload<int>(&QComboBox::currentIndexChanged),
            this, &StackedPanelBar::updateStackedToolboxSize);
  }

  StackedPanelModel* StackedPanelBar::model() const {
    return _model;
  }

  void StackedPanelBar::setModel(StackedPanelModel* model) {
    if (_model != nullptr) {
      _model->disconnect(this);
    }

    _model = model;

    connect(model, &StackedPanelModel::rowsInserted, this, &StackedPanelBar::onRowsInsert);
    connect(model, &StackedPanelModel::rowsRemoved, this, &StackedPanelBar::onRowsRemove);
  }

  int StackedPanelBar::currentIndex() const {
    return _panelCombobox->currentIndex();
  }

  void StackedPanelBar::setCurrentIndex(int index) {
    _panelCombobox->setCurrentIndex(index);
  }

  void StackedPanelBar::insert(const QModelIndex& index, int pos) {
    const QString name = _model->name(index);
    StackedPanelWidget* widget = _model->widget(index);

    _panelCombobox->insertItem(pos, name);
    _stackedToolbox->insertWidget(pos, widget->toolbox().get());
  }

  void StackedPanelBar::updateStackedToolboxSize(int pos) {
    auto widget = _stackedToolbox->widget(pos);
    int width = 0;
    int count = 0;

    auto toolbox = dynamic_cast<StackedPanelToolbox*>(widget);

    if (toolbox) {
      count = toolbox->count();
      width = toolbox->sizeHint().width();

      if (count) {
        width++;
      }
    }

    _stackedToolbox->setFixedWidth(width);
    _stackedToolbox->setProperty(PROPERTY_TOOLBOX_CONTAINER, count);
  }

  void StackedPanelBar::onRowsInsert(const QModelIndex& parent, int first, int last) {
    Q_UNUSED(parent)

    for (int i = first; i <= last; i++) {
      const QModelIndex index = _model->index(i, 0, parent);

      insert(index, i);
    }

    setCurrentIndex(last);
  }

  void StackedPanelBar::onRowsRemove(const QModelIndex& parent, int first, int last) {
    for (int i = last; i >= first; i--) {
      _panelCombobox->removeItem(i);
      _stackedToolbox->removeWidget(_stackedToolbox->widget(i));
    }

    const int step = first <= currentIndex() ? -1 : 0;
    const QModelIndex& index = _model->sibling(currentIndex() + step, 0, parent);

    if (index.isValid()) {
      setCurrentIndex(index.row());
    }
  }

  void StackedPanelBar::onDataChange(
    const QModelIndex& topLeft,
    const QModelIndex& bottomRight,
    const QVector<int>& roles
  ) {
    Q_UNUSED(bottomRight)

    if (!topLeft.isValid()) {
      return;
    }

    for (const int& role: roles) {
      auto roleEnum = static_cast<StackedPanelItem::Role>(role);

      if (roleEnum == StackedPanelItem::Role::NameRole) {
        const int pos = topLeft.row();
        const QString name = _model->name(pos);

        _panelCombobox->setItemText(pos, name);
      }
    }
  }
}  // namespace HPX
