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

#ifndef HPXSTACKEDPANEL_COMPONENTS_TABVIEWWIDGET_H_
#define HPXSTACKEDPANEL_COMPONENTS_TABVIEWWIDGET_H_

#include <QWidget>

#include "global.h"  // NOLINT(build/include)

namespace HPX {
  class LIBHPXSTACKEDPANEL_EXPORT StackedPanelWidget: public QWidget {
    Q_OBJECT

    public:
      explicit StackedPanelWidget(QWidget* parent = nullptr);

      virtual void setFocus();

    signals:
      void focusIn();
      void focusOut();
  };
} // namespace HPX

Q_DECLARE_METATYPE(HPX::StackedPanelWidget*)

#endif // HPXSTACKEDPANEL_COMPONENTS_TABVIEWWIDGET_H_
