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

#ifndef HPXSTACKEDPANEL_COMPONENTS_EMPTYWIDGET_H_
#define HPXSTACKEDPANEL_COMPONENTS_EMPTYWIDGET_H_

#include <QWidget>
#include "global.h"  // NOLINT(build/include)

class QLabel;
class QBoxLayout;
class QVBoxLayout;
class QHBoxLayout;
class QAbstractButton;

namespace HPX {
  class LIBHPXSTACKEDPANEL_EXPORT LandingWidget: public QWidget {
    Q_OBJECT

    protected:
      QVBoxLayout* _vboxLayout = nullptr;
      QHBoxLayout* _hboxLayout = nullptr;
      QHBoxLayout* _actionsLayout = nullptr;

      QLabel* _imageLabel = nullptr;
      QLabel* _titleLabel = nullptr;
      QLabel* _textLabel = nullptr;

    public:
      explicit LandingWidget(QWidget* parent = nullptr);
      explicit LandingWidget(const QString& title, QWidget* parent = nullptr);
      explicit LandingWidget(const QString& title, const QString& text, QWidget* parent = nullptr);
      virtual ~LandingWidget();

      QLabel* imageLabel() const;
      QLabel* titleLabel() const;
      QLabel* textLabel() const;

      void addButton(QAbstractButton*);
      void removeButton(QAbstractButton*);
  };
} // namespace HPX

#endif // HPXSTACKEDPANEL_COMPONENTS_EMPTYWIDGET_H_
