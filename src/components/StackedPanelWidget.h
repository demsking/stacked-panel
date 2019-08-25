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

#include <QMap>
#include <QFrame>
#include <QWidget>
#include "global.h"  // NOLINT(build/include)

class QVBoxLayout;
class QStackedWidget;

namespace HPX {
  class StackedPanel;
  class StackedPanelToolbox;

  class LIBHPXSTACKEDPANEL_EXPORT StackedPanelWidget: public QFrame {
    Q_OBJECT

    public:
      enum class State {
        None,
        Loading,
        Empty,
        Ready
      };

    private:
      QVBoxLayout* _layout = nullptr;
      QStackedWidget* _stackedWidget = nullptr;

      QSharedPointer<StackedPanelToolbox> _toolbox;
      bool _active = false;

    public:
      explicit StackedPanelWidget(QWidget* parent = nullptr);

      QSharedPointer<StackedPanelToolbox> toolbox();
      virtual void setFocus();

      bool isActive() const;

      void setStateWidget(State, QWidget*);
      State currentState() const;

    public slots:
      void setCurrentState(State);

    signals:
      void focusIn();
      void focusOut();
      void currentStateChanged(State);
  };
} // namespace HPX

Q_DECLARE_METATYPE(HPX::StackedPanelWidget*)

#endif // HPXSTACKEDPANEL_COMPONENTS_TABVIEWWIDGET_H_
