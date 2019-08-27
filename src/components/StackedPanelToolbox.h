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

#ifndef HPXSTACKEDPANEL_COMPONENTS_TOOLBOX_H_
#define HPXSTACKEDPANEL_COMPONENTS_TOOLBOX_H_

#include <QFrame>
#include "global.h"  // NOLINT(build/include)

class QWidget;
class QHBoxLayout;
class QAbstractButton;

namespace HPX {
  class LIBHPXSTACKEDPANEL_EXPORT StackedPanelToolbox: public QFrame {
    Q_OBJECT

    QHBoxLayout* _layout = nullptr;
    bool _enabled = true;

    public:
      explicit StackedPanelToolbox(QWidget* parent = nullptr);

      int count() const;
      QSize sizeHint() const override;
      QSize minimumSizeHint() const override;
      QAbstractButton* takeAt(int index) const;

      void addButton(QAbstractButton*);
      void removeButton(QAbstractButton*);

      void enable();
      void disable();

      void setEnabled(bool enabled);
      void setDisabled(bool disabled);
  };
}  // namespace HPX

#endif  // HPXSTACKEDPANEL_COMPONENTS_TOOLBOX_H_
