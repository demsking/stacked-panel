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

#include "components/LandingWidget.h"

#include <QLabel>
#include <QWidget>
#include <QVariant> // required for setProperty
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QAbstractButton>

namespace HPX {
  static void resetLayout(QBoxLayout* layout) {
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(QMargins());
  }

  LandingWidget::LandingWidget(QWidget* parent): QWidget(parent) {
    setProperty("LandingWidget", true);

    _vboxLayout = new QVBoxLayout(this);
    _hboxLayout = new QHBoxLayout;
    _actionsLayout = new QHBoxLayout;

    _imageLabel = new QLabel(this);
    _titleLabel = new QLabel(this);
    _textLabel = new QLabel(this);

    _imageLabel->setProperty("LandingWidgetImageLabel", true);
    _titleLabel->setProperty("LandingWidgetTitleLabel", true);
    _textLabel->setProperty("LandingWidgetTextLabel", true);

    resetLayout(_vboxLayout);
    resetLayout(_hboxLayout);
    resetLayout(_actionsLayout);

    _hboxLayout->addStretch(1);
    _hboxLayout->addWidget(_imageLabel);
    _hboxLayout->addStretch(1);

    _actionsLayout->setSpacing(10);
    _actionsLayout->addStretch(1);
    _actionsLayout->addStretch(1);

    _vboxLayout->addStretch(1);
    _vboxLayout->addLayout(_hboxLayout);
    _vboxLayout->addWidget(_titleLabel);
    _vboxLayout->addWidget(_textLabel);
    _vboxLayout->addLayout(_actionsLayout);
    _vboxLayout->addStretch(1);
  }

  LandingWidget::LandingWidget(const QString& title, QWidget* parent): LandingWidget(parent) {
    _titleLabel->setText(title);
  }

  LandingWidget::LandingWidget(
    const QString& title,
    const QString& text,
    QWidget* parent
  ): LandingWidget(title, parent) {
    _textLabel->setText(text);
  }

  LandingWidget::~LandingWidget() {
    delete _hboxLayout;
    delete _actionsLayout;
  }

  QLabel* LandingWidget::imageLabel() const {
    return _imageLabel;
  }

  QLabel* LandingWidget::titleLabel() const {
    return _titleLabel;
  }

  QLabel* LandingWidget::textLabel() const {
    return _textLabel;
  }

  void LandingWidget::addButton(QAbstractButton* button) {
    button->setProperty("LandingWidgetActionButton", true);

    _actionsLayout->insertWidget(_actionsLayout->count() - 1, button);
  }

  void LandingWidget::removeButton(QAbstractButton* button) {
    _actionsLayout->removeWidget(button);
  }
}  // namespace HPX
